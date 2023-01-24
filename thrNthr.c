/*
* Name: thrNthr..c
* Creator: Paula Vondrlik 
* Date of last Change: 27.11.2022
* Purpose: Project 2 of CMPE 322.01
*/
//includes necessary librarys and declares global variables
#include "prep.h"

// inserts the results in outputfile
void output(char* file, float time){
    FILE *output;
    output = fopen(file, "w"); 
    for (int pos = 0; pos < NUMBER_OPERATION; pos++){
        fprintf(output,"%.5f\n", result_arr[pos]);
    }
    fprintf(output,"%.5f\n", time);
    fclose(output);
}
// runner receives an id to calculate the threads task
// depending on total ammount of threads it willperform different tasl
// runner saves the results in a global result array
void *runner(void* args){
    int id =*((int*)args);
    int n_tasks = (int)floor(NUMBER_OPERATION/n_threads);
    int start_task = (id-1)*n_tasks;
    int last_task = start_task+n_tasks-1;
    int leftovers = NUMBER_OPERATION - (n_tasks*n_threads);

    // this is just to cath wrong number of entries(not a divisor of NUMB_operation)
    // the last thread executes leftovers
    if ((leftovers > 0) && (id == n_threads)){
        last_task += leftovers;
    }

    // selects the correct tasks per thread
    int n_funct; // the index of the function
    for(n_funct = 0; n_funct < NUMBER_OPERATION; n_funct++ ){
        if (start_task <= n_funct && last_task >= n_funct){
            // calls function 
            float f = funct[n_funct](int_list, len_list);
            // write result in global array
            result_arr[n_funct] = f;
         }
    };
    pthread_exit(0);
}



// the main function will take the arguments and create the respective threads 
// main also measures execution time and creates a result file 
// Outputfile: "output1.txt" or "output2.txt""
// function call: ./thrNthr <list_size> >number_threads>
int main(int argc, char *argv[]){
    // error handling
    if(argc != 3){//if ther is not one argument
        printf("thrNthr: wrong number of arguments - should be 2\n");
        return -1;
    }

     // globally declares in prep.h
    n_threads = atoi(argv[2]);
    len_list = atoi(argv[1]);

    // error handling
    if (len_list < 1){
        printf("thrNthr: first argument must be greater zero\n");
        return -1;
    } 
    if (n_threads < 1){
        printf("thrNthr: No thread is created. To use this function please run \"./noThread \"\n");
        return -1;
    }

    // initialization and declaration list 
    int_list = malloc(len_list*sizeof(int));

    // create list of n intergers  <= MAX_VALUE and => MIN_VALUE#
    time_t t;
    srand(0);// alternatively (unsigned) time(&t)) for real randomization;
    for(int pos = 0; pos < len_list; pos++){
        int_list[pos] = rand()%(MAX_VALUE-MIN_VALUE+1) + MIN_VALUE;
    }

    struct timespec wt_start, wt_stop;
    clock_t clockstart, clockend;
    // START: measure time
    clock_gettime(CLOCK_MONOTONIC, &wt_start);
    clockstart = clock();

    // sort list 
    qsort(int_list, len_list, (sizeof(int)),cmpfunc);

    // create thread with personal ids
    pthread_t tid[n_threads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int *id = malloc(sizeof(int)*n_threads);

    
    for (int i = 0; i < n_threads; i++){
        id[i] = i+1;
        pthread_create(&tid[i], &attr, &runner, &id[i]);
    }

    for (int i = 0; i < n_threads; i++){ 
        pthread_join(tid[i], NULL);
    } 

    clockend = clock();
    clock_gettime(CLOCK_MONOTONIC, &wt_stop);
     // END: measure cpu-time

    float wall_time = wt_stop.tv_sec + 1e-9*wt_stop.tv_nsec - (wt_start.tv_sec + 1e-9*wt_start.tv_nsec);
    float cpu_time_used = ((float) (clockend - clockstart)) / CLOCKS_PER_SEC;

    //put resuts into file and print them
    if (n_threads == 1){
        output("output1.txt", cpu_time_used);
    } else {
        output("output2.txt", cpu_time_used) ;
    }
    return 1;
}