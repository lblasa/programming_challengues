//
// UVA 100 The 3n+1 problem
// Source: 100_the_3n_plus_1_problem.c
// URL: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=36
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
#include <stdlib.h>

#define kN_MAX 1000000

int cache[kN_MAX];

int algorithm(int n)
{
    int length = 0;
    
    while (n != 1) {
        if (n % 2 != 0) {
            n = 3*n+1;
        }
        else {
            n /= 2;
        }
        
        length++;
    }
    
    return ++length;
}

int main()
{
    int i, j;
    
    while (scanf("%i %i", &i, &j) != EOF) {
        
        int start = i;
        int end = j;
        
        if (end < start) {
            int temp = start;
            start = end;
            end = temp;
        }
        
        int max = -1;
        
        for (int k = start; k <= end; k++) {
            int value = cache[k];
            
            if (!value) {
                value = algorithm(k);
                cache[k] = value;
            }
            
            if (value > max) {
                max = value;
            }
        }
        
        printf("%i %i %i\n", i, j, max);
    }
    
    return 0;
}