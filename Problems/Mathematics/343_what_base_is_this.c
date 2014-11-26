//
// UVA 343 What base is this?
// Source: 343_what_base_is_this.c
// URL: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=279
//
// Created by Lorenzo Blasa on 15/11/2014.
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
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define kMINOR_BASE 2
#define kMAJOR_BASE 36

typedef unsigned long long ULL;

#define kINPUT_SIZE 500

/**
    Returns the proper value for a given character input. 
 
    From '0' to '9' return [0..9]
    From 'A' to 'Z' return [10..35]
 */
int getValue(char c)
{
    return (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
}

/**
    Calculates the minimum base we can use for a given input.
    The minimum must meet two conditions:
    - Must be greater than every character value belonging to the input
    - Must be equal or greater than 2
 */
int minBase(const char *input)
{
    int length = (int)strlen(input);
    int base = -1;
    
    for (int i = 0; i < length; i++) {

        int value = getValue(input[i]);
        
        if (value > base) {
            base = value;
        }
    }

    if (base < kMINOR_BASE) {
        return kMINOR_BASE;
    }

    return base + 1;
}

/**
    Calculates the value base 10 of a given input and base.
 */
ULL valueForBase(const char *input, int base)
{
    ULL value = 0;
    int length = (int)strlen(input);
    
    for (int t=length-1; t >= 0; t--) {
        
        int val = getValue(input[t]);
        value += val * pow(base, length-t-1);
    }
    
    return value;
}

int main ()
{
    char x[kINPUT_SIZE], y[kINPUT_SIZE];
    
    while (scanf("%s %s", x, y) != EOF)
    {
        int areEqual = 0;

        int minBase_x = minBase(x);
        int minBase_y = minBase(y);

        for (int i = minBase_x; i <= kMAJOR_BASE && !areEqual; i++) {
            ULL valueForBase_x = valueForBase(x, i);
            
            for (int k = minBase_y; k <= kMAJOR_BASE && !areEqual; k++)
            {
                ULL valueForBase_y = valueForBase(y, k);
                
                if (valueForBase_x == valueForBase_y) {
                    areEqual = 1;
                    printf("%s (base %d) = %s (base %d)\n", x, i, y, k);
                }
            }
        }
        
        if (!areEqual) {
            printf("%s is not equal to %s in any base %d..%d\n", x, y, kMINOR_BASE, kMAJOR_BASE);
        }
    }

    return 0;
}