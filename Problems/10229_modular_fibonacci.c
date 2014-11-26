//
// UVA 10229 Modular Fibonacci
// Source: 10229_modular_fibonacci.c
// URL: http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1170
//
// Links:
//    http://zobayer.blogspot.co.uk/search/label/matrix%20exponentiation
//    http://www.mathblog.dk/uva-10229-modular-fibonacci/
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

#define kM_SIZE 10

typedef struct matrix
{
    long long int values[kM_SIZE][kM_SIZE];
    
    int rowCount;
    int colCount;
}
matrix;

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

long long int modularFibonacci(int n, int m)
{
    /**
        M * [f(n) f(n-1)] = [f(n+1) f(n)]
     */
    matrix fibonacci;
    
    fibonacci.rowCount = 2;
    fibonacci.colCount = 2;
    
    fibonacci.values[0][0] = 1;
    fibonacci.values[0][1] = 1;
    fibonacci.values[1][0] = 1;
    fibonacci.values[1][1] = 0;
    
    matrix result = power(fibonacci, n, m);

    return result.values[1][0];
}

int main()
{
    int n, m;
    
    while (scanf("%i %i", &n, &m) != EOF) {
        printf("%lld\n", modularFibonacci(n, pow(2, m)));
    }
    
    return 0;
}