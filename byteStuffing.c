/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   byteStuffing.c
 * Author: romulo
 *
 * Created on December 4, 2015, 3:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char flag = 'a';
char escape = 'b';

int converter() {
    FILE* input;
    FILE* output;
    uint8_t buffer;
    uint8_t frameSize;
    int continuar = 1;

    input = fopen("input", "r");
    output = fopen("outputStuffed", "w");
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    while (continuar) {
        fwrite(&flag, sizeof (uint8_t), 1, output);
        frameSize = 64 + (rand() % 191);

        while (frameSize--) {
            fread(&buffer, sizeof (uint8_t), 1, input);
            if (feof(input)) {
                continuar = 0;
                break;
            }
            if (buffer == flag || buffer == escape) {
                fwrite(&escape, sizeof (uint8_t), 1, output);
            }
            fwrite(&buffer, sizeof (uint8_t), 1, output);
        }
        fwrite(&flag, sizeof (uint8_t), 1, output);
    }

    fclose(input);
    fclose(output);

    return EXIT_SUCCESS;
}

int desconverter() {
    FILE* input;
    FILE* output;
    uint8_t buffer;
    int continuar = 1;

    input = fopen("outputStuffed", "r");
    output = fopen("output", "w");
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while (continuar) {
        fread(&buffer, sizeof (uint8_t), 1, input);
        while (1) {
            fread(&buffer, sizeof (uint8_t), 1, input);
            if (feof(input)) {
                continuar = 0;
                break;
            }
            if (buffer == flag) {
                break;
            }
            if (buffer == escape) {
                fread(&buffer, sizeof (uint8_t), 1, input);
            }
            fwrite(&buffer, sizeof (uint8_t), 1, output);
        }
    }

    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}

void imprimir() {
    FILE* input;
    uint8_t buffer;

    input = fopen("output", "r");

    while (1) {
        fread(&buffer, sizeof (uint8_t), 1, input);
        if (feof(input)) {
            break;
        }
        printf("%c", buffer);
    }

    fclose(input);
}

int main(int argc, char** argv) {
    converter();
    desconverter();
    imprimir();

    return EXIT_SUCCESS;
}