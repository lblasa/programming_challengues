//
// UVA 10189 Minesweeper
// Source: 10189_minesweeper.c
// URL: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1130
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

#define kN_LENGTH 100
#define kM_LENGTH 100

#define kBOMB  '*'
#define kEMPTY '.'

#define kOUTPUT_MESSAGE "Field #%i:\n"

char field[kN_LENGTH][kM_LENGTH];
int n, m;

void clearField()
{
    for (int row = 0; row < kN_LENGTH; row++) {
        for (int col = 0; col < kM_LENGTH; col++) {
            field[row][col] = '\0';
        }
    }
}

void printField(int i)
{
    printf(kOUTPUT_MESSAGE, i);
    
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            printf("%c", field[row][col]);
        }
        printf("\n");
    }
}

void readField()
{
    // newline characters '\n' must be manually read when using %c to
    // read, afterall '\n' is a 'character'
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            scanf("%c", &field[row][col]);
        }
        scanf("\n");
    }
}

int isValid(int row, int col)
{
    if (row < 0 || row >= n) {
        return 0;
    }
    
    if (col < 0 || col >= m) {
        return 0;
    }
    
    return 1;
}

void increment(int row, int col)
{
    if (!isValid(row, col) || field[row][col] == kBOMB) {
        return;
    }
    
    if (field[row][col] == kEMPTY) {
        field[row][col] = '1';
    }
    else {
        field[row][col] = field[row][col] + 1;
    }
}

void processField()
{
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            
            if (field[row][col] == kBOMB) {
                
                /**
                    8 position are affected by each bomb found
                    
                    [row-1][col-1] [row-1][col] [row-1][col+1]
                    [row]  [col-1] [row]  [col] [row]  [col+1]
                    [row+1][col-1] [row+1][col] [row+1][col+1]
                 
                    Field boundaries must be checked
                 */
                
                increment(row-1, col-1);
                increment(row-1, col);
                increment(row-1, col+1);
                
                increment(row, col-1);
                increment(row, col+1);
                
                increment(row+1, col-1);
                increment(row+1, col);
                increment(row+1, col+1);
            }
        }
    }
    
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (field[row][col] == kEMPTY) {
                field[row][col] = '0';
            }
        }
    }
}

int main()
{
    int f = 1;
    
    while (scanf("%i %i\n", &n, &m)) {
        
        if (n == 0 && m == 0) {
            break;
        }
        
        // add a new line to the previous printed field, it is not
        // done inmediately after printing because it might
        // give a wrong answer leaving an empty line at the end of
        // the execution
        if (f != 1) {
            printf("\n");
        }
        
        clearField();
        readField();
        processField();
        printField(f++);
    }
    
    return 0;
}