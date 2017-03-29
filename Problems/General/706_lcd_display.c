//
// UVA 706 LCD Display
// Source: 706_lcd_display.c
// URL: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=647
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

#define columns(size) size + 2
#define rows(size) ((2 * size) + 3)

#define MAX_ROW 25
#define MAX_COL 120

char lcd[MAX_ROW][MAX_COL];

typedef enum {
    LCDTop          = 1 << 0,
    LCDTopLeft      = 1 << 1,
    LCDTopRight     = 1 << 2,
    LCDMiddle       = 1 << 3,
    LCDBottomLeft   = 1 << 4,
    LCDBottomRight  = 1 << 5,
    LCDBottom       = 1 << 6
} LCDPosition;

/**
 *  Clears the LCD.
 */
void clear_lcd() {
    
    for (int row = 0; row < MAX_ROW; row++) {
        for (int col = 0; col < MAX_COL; col++) {
            lcd[row][col] = ' ';
        }
    }
}

/**
 *  Prints the LCD.
 */
void print_lcd(size_t length, int size) {
    
    int rows = ((2 * size) + 3);
    size_t cols = (size + 2) * length;
    cols += length - 1;
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%c", lcd[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 *  It draws a digit at a given start position with a given size
 *  by following the passed flags.
 */
void draw_lcd(int start, int size, int flags) {
    
    int rows = rows(size);
    int cols = columns(size);
    int middle_row = (rows / 2);
    
    /**
     *  Horizontal drawing.
     */
    for (int col = start + 1; col < start + cols - 1; col++) {
        
        if (flags & LCDTop) {
            lcd[0][col] = '-';
        }
        if (flags & LCDMiddle) {
            lcd[middle_row][col] = '-';
        }
        if (flags & LCDBottom) {
            lcd[rows - 1][col] = '-';
        }
    }
    
    /**
     *  Vertical drawing.
     */
    for (int row = 0; row < rows; row++) {
        
        if (row != 0 && row != middle_row && row != rows - 1) {
            
            if (row > middle_row) {
                
                if (flags & LCDBottomLeft) {
                    lcd[row][start] = '|';
                    
                }
                if (flags & LCDBottomRight) {
                    lcd[row][start + cols - 1] = '|';
                }
                
            }
            else {
                
                if (flags & LCDTopLeft) {
                    lcd[row][start] = '|';
                    
                }
                if (flags & LCDTopRight) {
                    lcd[row][start + cols - 1] = '|';
                }
                
            }
        }
    }
}

int main()
{
    int s, number;
    
    /**
     *  Define the rules to draw each digit.
     */
    int rules[10];
    rules[0] = LCDTop | LCDBottom | LCDTopLeft  | LCDTopRight | LCDBottomLeft | LCDBottomRight;
    rules[1] = LCDTopRight | LCDBottomRight;
    rules[2] = LCDTop | LCDMiddle | LCDBottom | LCDTopRight  | LCDBottomLeft;
    rules[3] = LCDTop | LCDMiddle | LCDBottom | LCDTopRight | LCDBottomRight;
    rules[4] = LCDMiddle | LCDTopLeft | LCDTopRight | LCDBottomRight;
    rules[5] = LCDTop | LCDMiddle | LCDBottom | LCDTopLeft  | LCDBottomRight;
    rules[6] = LCDTop | LCDMiddle | LCDBottom | LCDTopLeft  | LCDBottomLeft | LCDBottomRight;
    rules[7] = LCDTop | LCDTopRight | LCDBottomRight;
    rules[8] = LCDTop | LCDMiddle | LCDBottom | LCDTopLeft  | LCDTopRight | LCDBottomLeft | LCDBottomRight;
    rules[9] = LCDTop | LCDMiddle | LCDTopLeft  | LCDTopRight | LCDBottomRight;
    
    while (scanf("%i %i", &s, &number) != EOF) {
        
        if (s == 0 && number == 0) {
            break;
        }
        
        /**
         *  Clear the previously drawn LCD.
         */
        clear_lcd();
        
        /**
         *  The number is read as an Int but is transformed to a char[] for
         *  easy digit traversal.
         */
        char str[10];
        sprintf(str, "%d", number);
        
        size_t length = strlen(str);
        int start = 0;
        
        for (int digit_index = 0; digit_index < length; digit_index++) {
            
            /**
             *  The char[] contains chars instead of the actual Int. To transform
             *  the char to Int simply substract a '0' (char).
             */
            int digit = str[digit_index] - '0';
            
            /**
             *  Draw the digit by following the defined rules.
             */
            draw_lcd(start, s, rules[digit]);
            
            /**
             *  Move the start position to the next digit.
             */
            start += (s + 2) + 1;
        }
        
        print_lcd(length, s);
    }
    return 0;
}
