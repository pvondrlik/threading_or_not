
#ifndef CALC_FUNCTION
#define CALC_FUNCTION

#include "prep.h"

// helper function for qsort wich is used in main
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

// funct 0
float min(int *list, int n) {
    float min = MAX_VALUE;
    int min_pos = -1;
    for(int pos = 0; pos < n; pos++){
        if (list[pos] < min){
            min = list[pos];
            min_pos = pos;
        }
    }
    return min;
}
// funct 1
// O(n)
float max(int *list, int n) {
    float max = MIN_VALUE;
    int max_pos = -1;
    for(int pos = 0; pos < n; pos++){
        if (list[pos] >= max){
            max = list[pos];
        }
    }
    return max;
}

// funct 2
// O(n)
float range(int *list, int n){
    float range = (max(list, n) - min(list,n));
    return range;
}

// funct 3
// mode: the most occuring value
// - returns first if there are multiple ones finds the most 
// - requires a sorted list
// The fuction counts the number of same values after each other 
// while iterating through the whole list. It saves the max number and the corresponding value:
float mode(int *list, int n) {
    float max_n = 0;
    float max_v = list[0];
    float cur_n = 0;
    float cur_value = list[0];

    // count same values after each other 
    for(int pos = 0; pos < n; pos++) {
        if(list[pos] == cur_value) {
            cur_n ++;
            // else: another value is on next position
        } else {
            
            // if occurances of the last counted element are higher that the current modes number
            if (cur_n > max_n){
                max_n = cur_n;
                max_v = list[pos-1];
            }
            // next round the next value will be counted 
            cur_value = list[pos];
            cur_n = 1;
        }
    }
    return max_v;
}


// funct 4
// median:  the number in the middle(or the mean of the both in the middle)
// takes the mean if list is odd
float median(int *list, int n){
    float med;
    if(n%2 == 0){
        med = (list[(n/2)-1] + list[n/2]) * 0.5;
    } else {
        med = list[(int)floor(n/2)];
    }
    return med;

}

// funct 5
// O(n)
float sum(int *list, int n){
    float sum = 0;
    for(int pos = 0; pos < n; pos++){
        sum += list[pos];
    }
    return sum;
}

// funct 6
float arithm_mean(int *list, int n){
    float s = sum(list, n);
    float a_mean = s/n;
    return a_mean;
}

// funct 7
float harmonic_mean(int *list, int n){
    float denominator = 0;
    for(int pos = 0; pos < n; pos++){   
        denominator += ((float)1/list[pos]);
    }
    float mean = (float) n/denominator;
    return mean;
}

// funct 8
// standart deviation
float std_deviation(int *list, int n){
    float sd = 0;
    float mean = arithm_mean(list,n);
    for(int pos = 0; pos < n; pos++){
        sd += (list[pos] - mean)*(list[pos] - mean);
    }
    return sqrt(sd/(float)n);
}

// funct 9
float interquantile_range(int *list, int n){
    // iqr requires at least 3 elements
    if (n<3){
        return 0;
    }
    // takes the value of median to find all occurances of it
    float med = median(list, n);
    int pos = 0;
    // find rightmost value of q1
    while((float)list[pos] < med && pos < n){
        pos ++;
    } 
    int small_right = pos;
    // find leftmost value of q3
    while(list[pos] == med && pos < n){
        pos ++;
    }
    int high_left = pos;

    // calculate median for q1 and q3
    float lower_median = median(list, small_right);
    float high_median = median(list, n + high_left);

    float iqr = high_median-lower_median;
    return iqr;
}


//create array of functions
float (*funct[NUMBER_OPERATION]) (int *arr, int n) = {min, max, range, mode, median, sum, arithm_mean, harmonic_mean, std_deviation, interquantile_range};

// function calculation everything dependent on each other, only for "noThread.c"
void all_functions(){
    float min_val = min(int_list, len_list);
    float max_val = max(int_list, len_list);
    result_arr[0] = min_val;
    result_arr[1] = max_val;
    float range = max_val-min_val;
    result_arr[2] = range;
    result_arr[3] = mode(int_list, len_list); 
    result_arr[4] = median(int_list, len_list); 
    float s = sum(int_list, len_list); 
    result_arr[5] = s;
    float arithm_mean = s/len_list;
    result_arr[6] = arithm_mean;
    result_arr[7] = harmonic_mean(int_list, len_list); 
    float sd = 0;
    for(int pos = 0; pos < len_list; pos++){
        sd += (int_list[pos] - arithm_mean)*(int_list[pos] - arithm_mean);
    }
    result_arr[8] = sqrt(sd/(float)len_list);
    result_arr[9] = interquantile_range(int_list, len_list);
}
#endif




