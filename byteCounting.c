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
#include <string.h>

int converter() {
    FILE* input;
    FILE* output;
    uint8_t* buffer;
    uint8_t frameSize;

    input = fopen("input", "r");
    output = fopen("outputStuffed", "w");
    buffer = (uint8_t*) calloc(256, sizeof (uint8_t));
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    while (1) {
        frameSize = 64 + (rand() % 191);
        frameSize = fread(buffer, sizeof (uint8_t), frameSize, input);
        frameSize++;
        fwrite(&frameSize, sizeof (uint8_t), 1, output);
        fwrite(buffer, sizeof (uint8_t), frameSize, output);
        if (feof(input)) {
            break;
        }
    }

    fclose(input);
    fclose(output);

    return EXIT_SUCCESS;
}

int desconverter() {
    FILE* input;
    FILE* output;
    uint8_t* buffer;
    uint8_t frameSize;

    input = fopen("outputStuffed", "r");
    output = fopen("output", "w");
    buffer = (uint8_t*) calloc(256, sizeof (uint8_t));
    if (input == NULL) {
        return EXIT_FAILURE;
    }
    while (1) {
        fread(&frameSize, sizeof (uint8_t), 1, input);
        if (feof(input)) {
            break;
        }
        fread(buffer, sizeof (uint8_t), frameSize, input);
        fwrite(buffer, sizeof (uint8_t), frameSize, output);
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