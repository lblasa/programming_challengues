//
// UVA 10870 Recurrences
// Source: 10870_recurrences.c
// URL: http://uva.onlinejudge.org/external/108/10870.html
//
// Links:
//    http://zobayer.blogspot.co.uk/search/label/matrix%20exponentiation
//    http://www.mathblog.dk/uva-10229-modular-fibonacci/
//
// Created by Lorenzo Blasa on 27/11/2014.
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

#define kM_SIZE 20

typedef struct matrix
{
    long long int values[kM_SIZE][kM_SIZE];
    
    int rowCount;
    int colCount;
}
matrix;

void print(matrix m, const char* name)
{
    printf("Matrix: %s [Begin \n", name);
    for (int row = 0; row < m.rowCount; row++) {
        for (int col = 0; col < m.colCount; col++) {
            printf("%lld ", m.values[row][col]);
        }
        
        printf("\n");
    }
    printf("End]\n");
}

matrix multiply(matrix matrix1, matrix matrix2, int m)
{
    struct matrix result;
    
    result.rowCount = matrix1.rowCount;
    result.colCount = matrix2.colCount;
    
    long long int sum = 0;
    
    for (int row1 = 0 ; row1 < matrix1.rowCount ; row1++)
    {
        for (int col2 = 0 ; col2 < matrix2.colCount ; col2++)
        {
            for (int k = 0 ; k < matrix2.rowCount; k++ )
            {
                sum = (sum + matrix1.values[row1][k] * matrix2.values[k][col2]) % m;
            }
            
            result.values[row1][col2] = sum;
            sum = 0;
        }
    }
    
    return result;
}

matrix power(matrix matrix, int n, int m)
{
    if (n == 0) {
        
        struct matrix result;
        
        result.rowCount = matrix.rowCount;
        result.colCount = matrix.colCount;
        
        for (int r = 0; r < result.rowCount; r++) {
            for (int c = 0; c < result.colCount; c++) {
                if (r == c) {
                    result.values[r][c] = 1;
                }
                else {
                    result.values[r][c] = 0;
                }
            }
        }
        
        return result;
    }
    else if (n % 2 == 0)
    {
        struct matrix half = power(matrix, n/2, m);
        
        return multiply(half, half, m);
    }
    else
    {
        struct matrix p = power(matrix, n-1, m);
        struct matrix result = multiply(matrix, p, m);
        
        return result;
    }
}

long long int recurrence(matrix M, matrix A, int n, int m)
{
    matrix temp = power(M, n - M.rowCount, m);
    matrix result = multiply(temp, A, m);
    
    return result.values[0][0];
}

int main()
{
    int d, n, m;
    
    while (scanf("%d %i %i", &d, &n, &m) != EOF) {
        if (d == 0 && n == 0 && m == 0) {
            break;
        }
        
        matrix M;
        M.rowCount = d;
        M.colCount = d;
        
        matrix A;
        A.rowCount = d;
        A.colCount = 1;
        
        memset(M.values, 0, kM_SIZE * kM_SIZE);
        memset(A.values, 0, kM_SIZE * kM_SIZE);
        
        for (int i = 0; i < d; i++) {
            scanf("%lld", &M.values[0][i]);
        }
        
        for (int row = 1; row < d; row++) {
            for (int col = 0; col < d; col++) {
                if (row - 1 == col) {
                    M.values[row][col] = 1;
                }
            }
        }
        
        for (int i = d - 1; i >= 0; i--) {
            scanf("%lld", &A.values[i][0]);
        }
        
        if(n <= d){
            printf("%lli\n", A.values[n - d][0]);
        }
        else {
            printf("%lld\n", recurrence(M, A, n, m));
        }
    }
    
    return 0;
}