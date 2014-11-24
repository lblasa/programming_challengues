//
// UVA 355 The bases are loaded
// Source: 355_the_bases_are_loaded.c
// URL: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=291
//
// Created by Lorenzo Blasa on 23/11/2014.
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

#define kCORRECT_ANSWER "%s base %i = %s base %i\n"
#define kINCORRECT_ANSWER "%s is an illegal base %i number\n"

#define kINPUT_LENGTH 10
#define kOUTPUT_LENGTH 1024

int getValue(char c)
{
    return (c >= '0' && c <= '9') ? (c - '0') : (c - 'A') + 10;
}

char convertValue(int c)
{
    return (c >= 0 && c <= 9) ? (c + '0') : ((c - 10) + 'A');
}

long long int convertBase10(char* input, int base)
{
    long long int value = 0;
    int length = (int)strlen(input);
    
    for (int i = 0; i < length; i++) {
        char c = input[i];
        int val = getValue(c);
        
        if (val >= base) {
            return -1;
        }
        
        value += val * pow(base, length-i-1);
    }
    
    return value;
}

int convertToBase(long long int value, char* output, int base)
{
    int n = 0;
    long long int a = 0;
    
    while (a < value) {
        
        for (int b = 0; b < base; b++) {
            
            a = b * pow(base, n);
            
            if (a > value) {
                break;
            }
        }
        
        if (a > value) {
            break;
        }
        
        n++;
    }
    
    int index = 0;
    for (int i = n; i >= 0; i--) {
        
        int min = 0;
        for (int b = base - 1; b >= 0; b--) {
            a = b * pow(base, i);
            
            if (a <= value) {
                value -= a;
                min = b;
                break;
            }
        }
        
        if (i == n && min == 0 && value != 0) {
            continue;
        }
        
        output[index++] = convertValue(min);
    }
    
    return 0;
}

int main()
{
    int input_base, output_base;
    char input[kINPUT_LENGTH];
    
    while (scanf("%d %d %s", &input_base, &output_base, input) != EOF) {
        long long int base10Input = convertBase10(input, input_base);
        
        if (base10Input != -1) {
            char output[kOUTPUT_LENGTH];
            memset(output, '\0', kOUTPUT_LENGTH);

            convertToBase(base10Input, output, output_base);
            
            printf(kCORRECT_ANSWER, input, input_base, output, output_base);
            
        } else {
            printf(kINCORRECT_ANSWER, input, input_base);
        }
        
    }
    
    return 0;
}