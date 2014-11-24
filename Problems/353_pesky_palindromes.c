//
// UVA 353 Pesky palindromes
// Source: 353_pesky_palindromes.c
// URL: http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=289
//
// Created by Lorenzo Blasa on 24/11/2014.
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

#define kINPUT_LENGTH 1024
#define kOUTPUT_FORMAT "The string '%s' contains %i palindromes.\n"

size_t strrev(char *input, char *output, size_t length)
{
    for (int i = 0; i < length; i++) {
        output[length-i-1] = input[i];
    }
    
    return strlen(output);
}

int main()
{
    char input[kINPUT_LENGTH];
    int palindromes = 0;
    
    while (scanf("%s", input) != EOF) {
        
        int length = (int)strlen(input);
        int size = length + 1;
        char entries[length][kINPUT_LENGTH];
        
        for (int i = 0; i < length; i++) {
            for (int k = 0; k < length; k++) {
                
                char substring1[size];
                char substring2[size];
                
                memset(substring1, '\0', size);
                memset(substring2, '\0', size);
                
                memcpy(substring1, &input[i], k+1);
                
                int substringLength = (int)strlen(substring1);
                
                strrev(substring1, substring2, substringLength);
                
                if (strncmp(substring1, substring2, substringLength) == 0) {
                    
                    int found = 0;
                    for (int m = 0; m < palindromes && !found; m++) {
                        if (strncmp(substring1, entries[m], substringLength) == 0) {
                            found = 1;
                        }
                    }
                    
                    if (!found) {
                        memcpy(entries[palindromes], substring1, substringLength);
                        palindromes++;
                    }
                }
            }
        }
        
        printf(kOUTPUT_FORMAT, input, palindromes);
        
        memset(input, '\0', kINPUT_LENGTH);
        for (int m = 0; m < palindromes; m++) {
            memset(entries[m], '\0', kINPUT_LENGTH);
        }
        palindromes = 0;
    }
    
    return 0;
}