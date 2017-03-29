//
// UVA 10137 The Trip
// Source: 10137_the_trip.c
// URL: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1078
//
//
// Created by Lorenzo Blasa on 19/03/2017.
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

#define MAX_STUDENTS 1000

double expenses[MAX_STUDENTS];

int main()
{
    int students = 0;
    
    while (scanf("%i", &students) != EOF) {
        
        if (students == 0) {
            break;
        }
        
        double total = 0;
        for (int index = 0; index < students; index++) {
            scanf("%lf", &expenses[index]);
            total += expenses[index];
        }
        
        double avg = total / students;
        
        double negative = 0;
        double positive = 0;
        
        for (int index = 0; index < students; index++) {
            
            /**
             * To ensure 0.01 precision we need to perform the following operation:
             *
             * 1. Calculate the numerator
             * 2. Cast the numerator to long
             * 3. Perform division
             * 4. Cast the result to double
             */
            double res = (double) (long)((expenses[index] - avg) * 100.0) / 100.0;
            
            if (res > 0) {
                positive += res;
            }
            else {
                negative += res;
            }
        }
        
        /**
         * If the total amount is even then there's a balance between the positives and negatives.
         * If not, these values differ and they do by $.01
         */
        double exchange = (-negative > positive) ? -negative : positive;
        
        printf("$%.2lf\n", exchange);
    }
    
    return 0;
}
