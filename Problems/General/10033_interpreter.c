//
// UVA 10033 Interpreter
// Source: 10033_interpreter.c
// URL: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=12&page=show_problem&problem=974
//
//
// Created by Lorenzo Blasa on 20/03/2017.
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
#include <stdbool.h>

#define REGISTER_SIZE 10
#define RAM_SIZE 1000

int reg[REGISTER_SIZE];
int ram[RAM_SIZE][3];

/**
 * Clear the registers. Assign 0 (zero) to all entries.
 */
void clear_reg() {
    for (int i = 0; i < REGISTER_SIZE; i++) {
        reg[i] = 0;
    }
}

/**
 * Clear the ram. Assign 0 (zero) to all entries.
 */
void clear_ram() {
    for (int i = 0; i < RAM_SIZE; i++) {
        ram[i][0] = 0;
        ram[i][1] = 0;
        ram[i][2] = 0;
    }
}

int main()
{
    int cases = 0;
    scanf("%i", &cases);
    
    char instruction[5];
    
    /**
     *  Read `\n` from after the number of tests cases
     */
    fgets(instruction, sizeof(instruction), stdin);
    
    /**
     *  Read `\n` from the newline immediately after the number of test cases.
     */
    fgets(instruction, sizeof(instruction), stdin);
    
    for (int i = 0; i < cases; i++) {
        
        clear_reg();
        clear_ram();
        
        int number_of_instructions = 0;
        
        while (fgets(instruction, sizeof(instruction), stdin) != NULL) {
            
            if (instruction[0] == '\n') {
                break;
            }
            
            ram[number_of_instructions][0] = instruction[0] - '0';
            ram[number_of_instructions][1] = instruction[1] - '0';
            ram[number_of_instructions][2] = instruction[2] - '0';
            
            number_of_instructions++;
        }
        
        int executed_instructions = 0;
        int current_address = 0;
        
        int command, d, n, s, a;
        
        bool go = true;
        bool jump = false;
        
        while (go) {
            
            command = ram[current_address][0];
            jump = false;
            
            switch (command) {
                    /* 100 means halt */
                case 1:
                {
                    go = false;
                }
                    break;
                    /* 2dn means set register d to n (between 0 and 9) */
                case 2:
                {
                    d = ram[current_address][1];
                    n = ram[current_address][2];
                    
                    reg[d] = n;
                }
                    break;
                    /* 3dn means add n to register d */
                case 3:
                {
                    d = ram[current_address][1];
                    n = ram[current_address][2];
                    
                    reg[d] = (reg[d] + n) % 1000;
                }
                    break;
                    /* 4dn means multiply register d by n */
                case 4:
                {
                    d = ram[current_address][1];
                    n = ram[current_address][2];
                    
                    reg[d] = (reg[d] * n) % 1000;
                }
                    break;
                    /* 5ds means set register d to the value of register s */
                case 5:
                {
                    d = ram[current_address][1];
                    s = ram[current_address][2];
                    
                    reg[d] = reg[s];
                }
                    break;
                    /* 6ds means add the value of register s to register d */
                case 6:
                {
                    d = ram[current_address][1];
                    s = ram[current_address][2];
                    
                    reg[d] = (reg[d] + reg[s]) % 1000;
                }
                    break;
                    /* 7ds means multiply register d by the value of register s */
                case 7:
                {
                    d = ram[current_address][1];
                    s = ram[current_address][2];
                    
                    reg[d] = (reg[d] * reg[s]) % 1000;
                }
                    break;
                    /* 8da means set register d to the value in RAM whose address is in register a */
                case 8:
                {
                    d = ram[current_address][1];
                    a = ram[current_address][2];
                    
                    int address = reg[a];
                    reg[d] = (ram[address][0] * 100) + (ram[address][1] * 10) + ram[address][2];
                }
                    break;
                    /* 9sa means set the value in RAM whose address is in register a to that of register s */
                case 9:
                {
                    s = ram[current_address][1];
                    a = ram[current_address][2];
                    
                    int address = reg[a];
                    int value = reg[s];
                    
                    ram[address][2] = (value % 10);
                    value /= 10;
                    ram[address][1] = (value % 10);
                    value /= 10;
                    ram[address][0] = (value % 10);
                }
                    break;
                    /* 0ds means goto the location in register d unless register s contains 0 */
                case 0:
                {
                    d = ram[current_address][1];
                    s = ram[current_address][2];
                    
                    if (reg[s] != 0) {
                        
                        current_address = reg[d];
                        jump = true;
                    }
                }
                    break;
                default:
                    break;
            }
            
            if (!jump) {
                current_address++;
            }
            
            executed_instructions++;
        }
        
        printf("%i\n", executed_instructions);
        if (i < cases - 1) {
            printf("\n");
        }
    }
    
    return 0;
}
