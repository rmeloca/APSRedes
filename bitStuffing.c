/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bitStuffing.c
 * Author: romulo
 *
 * Created on December 4, 2015, 2:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * 
 */
int main(int argc, char** argv) {
    FILE* file;
    uint8_t iterator;

    file = fopen("bitStuffing.txt", "r");

    while (1) {
        iterator = fgetc(file);
        if (feof(file)) {
            break;
        }
        printf("%c", iterator);
    }
    printf("\n");

    return (EXIT_SUCCESS);
}

