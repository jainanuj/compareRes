//
//  compareResults.cpp
//  compareResults
//
//  Created by Anuj Jain on 6/25/17.
//  Copyright © 2017 Anuj Jain. All rights reserved.
//

#include "compareResults.h"
#include <iostream>
#include <fstream>
using namespace std;

#define DIFF_THRESH 0.0
const unsigned long fmst_coeff = 2147483648;
const unsigned long infy = 2000000000;

void parse_results(const char *res_file, unsigned long ***file_results_ptr, int num_states)
{
    unsigned long   **f_results = *file_results_ptr;
    int     i;
    ifstream inputFile(res_file);
    string inputLine;

    f_results = (unsigned long **)malloc(sizeof(unsigned long*) * num_states);
    
    for (i = 0; i < num_states; i++)
    {
        f_results[i] = (unsigned long *)malloc(sizeof(unsigned long) * 3);  //arrival time, wt time, num Hops
        f_results[i][0] = infy;f_results[i][1] = infy;f_results[i][2] = infy;
    }
    int nodeId;//,arr,wt;
    unsigned long arr,wt;
    getline(inputFile, inputLine);
    while (getline(inputFile, inputLine))
    {
//        sscanf(inputLine.c_str(), "%d %d %d", &nodeId, &arr, &wt);
        sscanf(inputLine.c_str(), "%d %lu %lu", &nodeId, &arr, &wt);
        f_results[nodeId][0] = arr;f_results[nodeId][1] = wt;f_results[nodeId][2] = arr-wt;
    }
    *file_results_ptr = f_results;
    return;
}

void compare_results(unsigned long **file1_results,unsigned long **file2_results, int num_states)
{
    int i, max_diff_state=0;
    unsigned long **diff = (unsigned long **)malloc(sizeof(unsigned long*) * num_states);
    for (i = 0; i < num_states; i++)
    {
        diff[i] = (unsigned long *)malloc(sizeof(unsigned long) * 3);  //arrival time, wt time, num Hops
        diff[i][0] = 0;diff[i][1] = 0;diff[i][2] = 0;
    }
    unsigned long max_diff = 0;
    double mean_diff = 0;
    unsigned long sum_diff = 0;
//    unsigned long computedVal1 = 0;
    int num_diffs = 0, num_threshs = 0, file1_gr=0;
    unsigned long max_file_gr_diff = 0, max_shrtst_diff = 0; int file1_gr_maxdiff_st = 0;
    for (i = 0; i< num_states; i++)
    {
        if (file1_results[i][0] != file2_results[i][0])
        {
            cout << i << " arrival: file1 " << file1_results[i][0] << " file2 " << file2_results[i][0] << endl;
            diff[i][0] = file1_results[i][0] - file2_results[i][0];
            if (diff[i][0] < 0)
                diff[i][0] *= -1;
            if (diff[i][0] > DIFF_THRESH)
            {
               file1_gr++;
               if (diff[i][0] > max_file_gr_diff)
               {
                   max_file_gr_diff = diff[i][0];
//                   file1_gr_maxdiff_st = i;
               }
            }
        }
        if (file1_results[i][1] != file2_results[i][1])
        {
            cout << i << " length: file1 " << file1_results[i][1] << " file2 " << file2_results[i][2] << endl;
            diff[i][1] = file1_results[i][1] - file2_results[i][1];
            if (diff[i][1] < 0)
                diff[i][1] *= -1;
            if (diff[i][1] > DIFF_THRESH)
            {
               file1_gr++;
               if (diff[i][1] > max_shrtst_diff)
               {
                   max_shrtst_diff = diff[i][1];
                   file1_gr_maxdiff_st = i;
               }
            }
            num_diffs++;
            sum_diff += diff[i][1];
        }
    }
    mean_diff = sum_diff/num_states;
    
    printf("Max Diff = %lu; Max_Diff_state = %d; Mean Diff = %f; \
           Num Diffs = %d; total Diffs = %lu. Values of maxDiff: File1-arr: %lu, File1-length: %lu; File2-arr: %lu, File2-length: %lu\n",
           max_shrtst_diff, file1_gr_maxdiff_st, mean_diff, num_diffs, sum_diff, file1_results[file1_gr_maxdiff_st][0],file1_results[file1_gr_maxdiff_st][1], file2_results[file1_gr_maxdiff_st][0], file2_results[file1_gr_maxdiff_st][1]);
    
    //Num Threshs = %d; File1 bigger = %d; File2 bigger = %d,MaxDiff-File1gr = %f, maxDiffStFile1Gr = %d
    return;
}

//compareResults <num_States_in_origProb> file1 file2
int main( int argc, char *argv[] )
{
    char    *opt;
    char    *file1 = NULL, *file2 = NULL;
    unsigned long   **file1_results = NULL;
    unsigned long   **file2_results = NULL;
    int     num_states = 0;
    unsigned int checkLong = 1;
    int clMultiplier = 31;
    
    checkLong <<= clMultiplier;
 
//    sleep(10);
//    cout << checkLong << endl;
    if (argc > 1)
    {
        opt = argv[1];
        num_states = atoi(opt);
        if (argc > 2)
        {
            file1 = strdup(argv[2]);        //This will be the file with two entries. (arr numHops/wt_time)
            file2 = strdup(argv[3]);        //This will be the file with linear combination (arr*2^31+numHops/wt_time)
        }
    }
    
    parse_results(file1, &file1_results, num_states);
    parse_results(file2, &file2_results, num_states);
    
    compare_results(file1_results, file2_results, num_states);

    return 0;
}
