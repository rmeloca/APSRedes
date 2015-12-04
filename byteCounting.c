/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   byteCounting.c
 * Author: romulo
 *
 * Created on December 4, 2015, 3:07 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdint.h>

/*
 * 
 */
int main(int argc, char** argv) {
    FILE* file;
    uint8_t iterator;

    /*
     * Gerar tamanho de quadro aleatório entre 64 e 1500bytes
     */
    
    /*
     * ida
     */
    file = fopen("byteCounting.txt", "r");

    while (1) {
        iterator = fgetc(file);
        if (feof(file)) {
            break;
        }
        printf("%c", iterator);
    }
    printf("\n");

    
    
    /*
     * volta
     */
    return (EXIT_SUCCESS);
}

