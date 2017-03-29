//
// UVA 10041 Vito's Family
// Source: 10041_vitos_family.cpp
// URL: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=982
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
#include <algorithm>
#include <stdlib.h>

using namespace std;

int main()
{
    /**
     * Read the number of test cases.
     */
    int n = 0;
    scanf("%i", &n);
    
    while (n > 0) {
        
        /**
         * Read the number of Vito's relatives.
         */
        int numberOfRelatives = 0;
        scanf("%d", &numberOfRelatives);
        
        /**
         * Read and store Vito's relatives addresses.
         */
        int relatives[numberOfRelatives];
        for (int relative = 0; relative < numberOfRelatives; relative++) {
            scanf("%d", &relatives[relative]);
        }
        
        /**
         * The read addresses are unsorted. So, do the sorting.
         * The idea is to quickly find the median because that's where
         * Vito's ideal home needs to be.
         */
        sort(relatives, relatives + numberOfRelatives);
        int median = relatives[numberOfRelatives / 2];
        
        /**
         * It's time to calculate the sum of the distances from this location
         * to each relative.
         */
        int sum = 0;
        for (int j = 0; j < numberOfRelatives; j++) {
            sum += abs(median - relatives[j]);
        }
        
        /**
         * Print the minimum distance.
         */
        printf("%d\n", sum);
        
        n--;
    }
    
    return 0;
}
