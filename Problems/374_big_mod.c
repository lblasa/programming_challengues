//
// UVA 374 Big Mod
// Source: 374_big_mod.c
// URL: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=310
//
// Created by Lorenzo Blasa on 25/11/2014.
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
#include <math.h>

/**
    This is a mathematical formula which comes handy in this situation.
 
    R = (a*b*c) mod m = ((a mod m) * (b mod m) * (c mod m)) mod m
    R = (base^p) mod m
 
    In this case (a*b*c) can be a very big number. Also, (base^p) can be
    a very big number as well.
 
    To further explain, if a = b = c, then (a*b*c) is the same as (a^3), which
    is the same as (a^p) with p = 3.
 
    Using this principle, we know that:
 
    b^p = b^(p/2) * b^(p/2)
 
    Also, 
 
    b^p = b * b^(p-1)
 
    So, we can create an algorithm that using this principle and approach
    can calculate R for very big numbers.
 */
long long int bigmod(int b, int p, int m)
{
    if (p == 0) {
        return 1;
    }
    
    if (p % 2 == 0) {
        long long int temp = bigmod(b, p/2, m);
        return (temp * temp) % m;
    }
    else {
        return ((b % m) * bigmod(b, p-1, m)) % m;
    }
}

int main() {
    int b, p, m;
    
    while (scanf("%i %i %i", &b, &p, &m) != EOF) {
        printf("%lld\n", bigmod(b, p, m));
    }
}