//
// UVA 120 Stacks of Flapjacks
// Source: 120_stacks_of_flapjacks.c
// URL: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=56
//
//
// Created by Lorenzo Blasa on 29/03/2017.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_NUMBER_OF_PANCAKES  30
#define MAXIMUM_PANCAKE_DIAMETER    100

void flip(int *pancakes, int pivot) {
    
    int left = 0;
    int right = pivot;
    
    while (left <= right) {
        
        int temp = pancakes[left];
        pancakes[left] = pancakes[right];
        pancakes[right] = temp;
        
        left++;
        right--;
    }
}

void sort(int* pancakes, int pivot, int n) {
    
    flip(pancakes, pivot);
    flip(pancakes, n);
}

/**
 * Check whether the pancakes are ready to serve.
 * Iterate through the array making sure that each element from the left
 * is smaller than the one on the right.
 *
 * Example:
 * [8, 1, 2, 3, 2]
 * n = 5
 *
 */
bool is_ready_to_serve(int *pancakes, int n) {
    
    for (int i = 0; i < n - 1; i++) {
        
        if (pancakes[i] > pancakes[i+1]) {
            return false;
        }
    }
    
    return true;
}

/**
 * Find the pancake with the biggest diameter on a given
 * range.
 */
int find_max(int *pancakes, int left, int right) {
    
    int index = left;
    int max = pancakes[index];
    
    for (int i = left + 1; i <= right; i++) {
        
        if (pancakes[i] > max) {
            max = pancakes[i];
            index = i;
        }
    }
    
    return index;
}

int main()
{
    char *line = NULL;
    size_t size;
    
    size_t length = (MAXIMUM_NUMBER_OF_PANCAKES * MAXIMUM_PANCAKE_DIAMETER) + MAXIMUM_NUMBER_OF_PANCAKES;
    line = (char*)malloc(length + 1);
    memset(line, '\0', length);
    
    while (getline(&line, &size, stdin) != EOF) {
        
        int n = 0;
        
        char input[strlen(line) + 1];
        memset(input, '\0', strlen(line) + 1);
        memcpy(input, line, strlen(line));
        
        int pancakes[MAXIMUM_NUMBER_OF_PANCAKES];
        memset(pancakes, 0, sizeof(int) * MAXIMUM_NUMBER_OF_PANCAKES);
        
        char * pch;
        pch = strtok(line, " ");
        
        while (pch != NULL)
        {
            int pancake = atoi(pch);
            
            pancakes[n] = pancake;
            n++;
            
            pch = strtok (NULL, " ");
        }
        
        char output[MAXIMUM_NUMBER_OF_PANCAKES * 1000];
        memset(output, '\0', MAXIMUM_NUMBER_OF_PANCAKES * 1000);
        
        /**
         * We need to sort the pancake stack in ascending order.
         * Pancakes array top: 0, bottom: n - 1
         *
         */
        int left = 0;
        int right = n - 1;
        
        while (!is_ready_to_serve(pancakes, n)) {
            
            int index = find_max(pancakes, left, right);
            sort(pancakes, index, right);
            
            if (index != 0) {
                
                char tmp[5];
                memset(tmp, '\0', 5);
                sprintf(tmp, "%i ", n - index);
                
                strcat(output, tmp);
            }
            
            char tmp[5];
            memset(tmp, '\0', 5);
            sprintf(tmp, "%i ", n - right);
            
            strcat(output, tmp);
            
            
            right--;
        }
        
        strcat(output, "0\n");
        
        printf("%s", input);
        printf("%s", output);
        
        line[0] = '\0';
    }
    
    free(line);
    
    return 0;
}
