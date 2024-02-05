#include <iostream>
#include <memory>
#include "interface.h"

/*
 * This function returns a pointer to the wrapper object InputBuffer
 * Initializes the buffer as an empty string, bufferLength and inputLength to 0
 */
std::unique_ptr<InputBuffer> newInputBuffer() {
    std::unique_ptr<InputBuffer> inputBuffer(new InputBuffer);
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
void readInput(std::unique_ptr<InputBuffer>& inputBuffer, std::ostream& out,  std::istream& in) {
    getline(in, inputBuffer->buffer);
    inputBuffer->inputLength = inputBuffer->buffer.size();
    if (inputBuffer->inputLength <= 0) {
        out << "Error reading input\n";
        // exit(EXIT_FAILURE);
    }
}


/*
 * readInput function reads a line of input and stores the information accordingly into the inputBuffer
 * @inputBuffer: Pointer the inputBuffer object which is used for storing the user input
 * if user input is empty then the program exits
 */
void readInput(std::unique_ptr<InputBuffer>& inputBuffer) {
    getline(std::cin, inputBuffer->buffer);
    inputBuffer->inputLength = inputBuffer->buffer.size();
    if (inputBuffer->inputLength <= 0) {
        std::cout << "Error reading input\n";
        exit(EXIT_FAILURE);
    }
}
