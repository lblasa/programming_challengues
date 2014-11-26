//
// UVA 369 Combinations
// Source: 369_combinations.c
// URL: http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=305
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

/**
    Calculates the value of C. 
 
    C = N! / (N-M)! * M!
 
    As you can see on the C formula, there are lots of simplifications that can
    be made. 
 
    So, first check who is greater: N-M or M and use that to simplify N! such that
    N, N-1, N-2, ... (N-M)! | M!
 
    Second, once you simplify using what's being said above, then proceed to try
    and divide individual values from the numerator and denominator to prevent values
    from overflowing.
 */
long long int calculate(int n, int m)
{
    long long int a = 1, b = 1;
    long long int intermediate;
    
    if (n - m > m) {
        intermediate = n - m;
    }
    else {
        intermediate = m;
        m = n - m;
    }
    
    int k_array[m+1];
    for (int k = 1; k <= m; k++) {
        k_array[k] = k;
    }
    
    for (int i = n; i > intermediate; i--) {
        
        int value = i;
        
        for (int k = m; k > 0; k--) {
            if ((k_array[k] != 0) && (value % k_array[k] == 0)) {
                value /= k_array[k];
                k_array[k] = 0;
                break;
            }
        }
        
        a *= value;
    }
    
    for (int k = m; k > 0; k--) {
        if (k_array[k] != 0) {
            b *= k_array[k];
            k_array[k] = 0;
        }
    }
    
    return a/b;
}

int main()
{
    int n, m;

    while (scanf("%i %i", &n, &m)) {
        
        if (n == 0 && m == 0) {
            break;
        }
        
        long long int c = calculate(n, m);
        printf("%i things taken %i at a time is %lld exactly.\n", n, m, c);
    }
    
    return 0;
}
