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
#include "limits.h"

uint8_t flag = 0b01111110;

char* chartobin(unsigned char c) {
    static char bin[CHAR_BIT + 1] = {0};
    int i;

    for (i = CHAR_BIT - 1; i >= 0; i--) {
        bin[i] = (c % 2) + '0';
        c /= 2;
    }
    return bin;
}

unsigned char bintochar(char* binstr) {
    return (unsigned char) (strtoul(binstr, NULL, 2));
}

int converter() {
    FILE* input;
    FILE* output;
    uint8_t buffer;
    uint8_t frameSize;
    uint8_t* byte;
    int continuar = 1;
    int counting = 0;

    input = fopen("input", "r");
    output = fopen("outputIntermediaria", "w");
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    while (continuar) {
        frameSize = 64 + (rand() % 191);
        fwrite(&flag, sizeof (uint8_t), 1, output);
        while (frameSize--) {
            fread(&buffer, sizeof (uint8_t), 1, input);
            if (feof(input)) {
                continuar = 0;
                break;
            }
            fwrite(chartobin(buffer), sizeof (uint8_t), 8, output);
        }
        fwrite(&flag, sizeof (uint8_t), 1, output);
    }

    fclose(input);
    fclose(output);

    input = fopen("outputIntermediaria", "r");
    output = fopen("outputStuffedIntermediaria", "w");

    continuar = 1;
    while (continuar) {
        while (1) {
            fread(&buffer, sizeof (uint8_t), 1, input);
            if (feof(input)) {
                continuar = 0;
                break;
            }
            if (buffer == flag) {
                fwrite("01111110", sizeof (uint8_t), 8, output);
                break;
            }
            if (buffer == '1') {
                counting++;
            } else if (buffer == '0') {
                counting = 0;
            }
            if (counting == 5) {
                fwrite("1", sizeof (uint8_t), 1, output);
                counting = 0;
            }
            fwrite(&buffer, sizeof (uint8_t), 1, output);
        }
    }

    fclose(input);
    fclose(output);

    input = fopen("outputStuffedIntermediaria", "r");
    output = fopen("outputStuffed", "w");

    byte = (uint8_t*) calloc(8, sizeof (uint8_t));

    while (1) {
        fread(byte, sizeof (uint8_t), 8, input);
        if (feof(input)) {
            break;
        }
        buffer = bintochar((char*) byte);
        fwrite(&buffer, sizeof (uint8_t), 1, output);
    }

    fclose(input);
    fclose(output);

    return EXIT_SUCCESS;
}

int desconverter() {
    FILE* input;
    FILE* output;
    uint8_t buffer;
    uint8_t* byte;
    int counting = 0;
    int continuar = 1;

    input = fopen("outputStuffed", "r");
    output = fopen("conversaoIntermediaria", "w");

    if (input == NULL) {
        return EXIT_FAILURE;
    }
    while (1) {
        fread(&buffer, sizeof (uint8_t), 1, input);
        if (feof(input)) {
            break;
        }
        fwrite(chartobin(buffer), sizeof (uint8_t), 8, output);
    }

    fclose(input);
    fclose(output);

    input = fopen("conversaoIntermediaria", "r");
    output = fopen("conversaoDesestufada", "w");
    while (continuar) {
        fread(&buffer, sizeof (uint8_t), 8, input);
        if (feof(input)) {
            break;
        }
        while (1) {
            fread(&buffer, sizeof (uint8_t), 1, input);
            if (buffer == '1') {
                counting++;
            } else if (buffer == '0') {
                counting = 0;
            }
            if (counting == 5) {
                fread(&buffer, sizeof (uint8_t), 1, input);
                if (buffer == '1') {
                    fread(&buffer, sizeof (uint8_t), 1, input); //0
                    break;
                    fread(&buffer, sizeof (uint8_t), 8, input); //flag
                    fseek(output, -7, SEEK_CUR); //apaga flag da saida
                }
                fread(&buffer, sizeof (uint8_t), 1, input);
                counting = 0;
            }
            fwrite(&buffer, sizeof (uint8_t), 1, output);
        }
    }

    fclose(input);
    fclose(output);

    input = fopen("conversaoDesestufada", "r");
    output = fopen("output", "w");
    byte = (uint8_t*) calloc(8, sizeof (uint8_t));

    while (1) {
        fread(byte, sizeof (uint8_t), 8, input);
        if (feof(input)) {
            break;
        }
        buffer = bintochar((char*) byte);
        fwrite(&buffer, sizeof (uint8_t), 1, output);
    }

    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    converter();
    desconverter();
    return EXIT_SUCCESS;
}