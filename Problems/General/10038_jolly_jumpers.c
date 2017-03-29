//
// UVA 10038 Jolly Jumpers
// Source: 10038_jolly_jumpers.c
// URL: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=979
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
#include <stdbool.h>

#define JOLLY_JUMPER_MAX_N 3000

int main()
{
    int n;
    
    while (scanf("%i", &n) != EOF) {
        
        int sequence[JOLLY_JUMPER_MAX_N];
        memset(sequence, 0, JOLLY_JUMPER_MAX_N * sizeof(int));
        
        int previous = 0;
        int start = false;
        
        int counter = n - 1;
        
        for (int i = 0; i < n; i++) {
            
            int value = 0;
            scanf("%i", &value);
            
            if (start == false) {
                previous = value;
                start = true;
                continue;
            }
            
            int difference = abs(value - previous);
            
            if (difference > 0 && difference < n) {
                
                if (sequence[difference] == 0) {
                    sequence[difference] = 1;
                    counter--;
                }
            }
            
            previous = value;
        }
        
        if (counter == 0) {
            printf("Jolly\n");
        }
        else {
            printf("Not jolly\n");
        }
    }
    
    return 0;
}
