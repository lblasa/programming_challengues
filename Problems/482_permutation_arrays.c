//
// UVA 482 Permutation Arrays
// Source: 482_permutation_arrays.c
// URL: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=423
//
// Created by Lorenzo Blasa on 22/11/2014.
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
#include <string.h>
#include <stdlib.h>

#define kARRAY_CAPACITY 1000000
#define kINPUT_SIZE 100000

int main()
{
    int n = 0;
    
    char buffer[kINPUT_SIZE];
    
    // read the number of inputs
    fgets(buffer, sizeof(buffer), stdin);
    n = atoi(buffer);
    
    for (int i = 0; i < n; i++) {
        
        // read and empty line from stdin
        fgets(buffer, sizeof(buffer), stdin);
        
        // read the positions array
        fgets(buffer, sizeof(buffer), stdin);
        
        int positions[kARRAY_CAPACITY];
        int j = 0;
        
        char* token = strtok(buffer, " ");
        while (token) {
            positions[j++] = atoi(token);
            token = strtok(NULL, " ");
        }
        
        // read the array
        fgets(buffer, sizeof(buffer), stdin);
        
        const char *array[j];
        
        // populate the array by using the already read positions
        int k = 0;
        token = strtok(buffer, " \n");
        while (token) {
            array[--positions[k++]] = token;
            token = strtok(NULL, " \n");
        }
        
        for (int t = 0; t < j; t++) {
            printf("%s\n", array[t]);
        }
        
        // only add a new line if we have more cases to process
        if (i < n - 1) {
            printf("\n");
        }
    }
    
    return 0;
}