#ifndef INPRT_THRNTHR
#define INPRT_THRNTHR

#define MIN_VALUE 1000 
#define MAX_VALUE 10000 
#define NUMBER_OPERATION 10

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

//declararion global variables
float result_arr[NUMBER_OPERATION];
int *int_list;
int len_list;
int n_threads;

#include "calc_funct.h"

#endif