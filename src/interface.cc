#include <iostream>
#include "interface.h"

/*
 * This function returns a pointer to the wrapper object InputBuffer
 * Initializes the buffer as an empty string, bufferLength and inputLength to 0
 */
InputBuffer* newInputBuffer() {
    InputBuffer* inputBuffer = (InputBuffer*) malloc(sizeof(InputBuffer));
    inputBuffer->buffer = "";
    inputBuffer->bufferLength = 0;
    inputBuffer->inputLength = 0;
    return inputBuffer;
}

/*
 * readInput function reads a line of input and stores the information accordingly into the inputBuffer
 * @inputBuffer: Pointer the inputBuffer object which is used for storing the user input
 * if user input is empty then the program exits
 */
void readInput(InputBuffer* inputBuffer) {
    getline(std::cin, inputBuffer->buffer);
    inputBuffer->inputLength = inputBuffer->buffer.size();
    if (inputBuffer->inputLength <= 0) {
        std::cout << "Error reading input\n";
        exit(EXIT_FAILURE);
    }
}

/*
 * freeInputBuffer: frees in the inputBuffer object we created for storing the user input
 */
void freeInputBuffer(InputBuffer* inputBuffer) {
    free(inputBuffer);
}
