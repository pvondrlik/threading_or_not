/*
* Name: noThread.c
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
    // write all results which were saved by threads in array 
    for (int pos = 0; pos < NUMBER_OPERATION; pos++){
        fprintf(output,"%.5f\n", result_arr[pos]);
    }
    // add time
    fprintf(output,"%.5f\n", time);
    fclose(output);
}

// the main function will take the arguments and create the respective threads 
// main also measures execution time and creates a result file 
// Outputfile: "output1.txt"
// function call: ./thrNthr <list_size> 
int main(int argc, char *argv[]){
    // error handling
    if(argc != 2){//if ther is not one argument
        printf("noThr: only takes one argument\n");
        return -1;
    } else if (atoi(argv[1]) < 1){
        printf("noThr: first argument must be greater zero\n");
        return -1;
    } 

    // globally declared in prep.h
    len_list = atoi(argv[1]);
    int_list = malloc(len_list*sizeof(int));   

    // create list of n intergers  <= MAX_VALUE and => MIN_VALUE#
    time_t t;
    srand(0);   // Seed 0 -> numbers are the same for every call of main to increase comparability
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

    // performs all calculations
    all_functions();

    // END: measure time
    clockend = clock();
    clock_gettime(CLOCK_MONOTONIC, &wt_stop);
    float wall_time = wt_stop.tv_sec + 1e-9*wt_stop.tv_nsec - (wt_start.tv_sec + 1e-9*wt_start.tv_nsec);
    float cpu_time_used = ((float) (clockend - clockstart)) / CLOCKS_PER_SEC;
    // put resuts into file and print them
    output("output1.txt", cpu_time_used);
    return 1;
}