#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

/*
 * This function prints the prompt that the user is presented with
 */
void printPrompt() {
    cout << "db > ";
}

/*
 * InputBuffer is a wrapper around the buffer that is used for reading user input.
 * @buffer : stores the user input
 * @bufferLength: 
 * @inputLength: 
 */
typedef struct {
    string buffer;
    size_t bufferLength;
    ssize_t inputLength;
}InputBuffer;

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
    getline(cin, inputBuffer->buffer);
    inputBuffer->inputLength = inputBuffer->buffer.size();
    if (inputBuffer->inputLength <= 0) {
        cout << "Error reading input\n";
        exit(EXIT_FAILURE);
    }
}

/*
 * freeInputBuffer: frees in the inputBuffer object we created for storing the user input
 */
void freeInputBuffer(InputBuffer* inputBuffer) {
    free(inputBuffer);
}

int main(int argc, char *argv[]) {
    InputBuffer* inputBuffer = newInputBuffer();
    while (true) {
        printPrompt();
        readInput(inputBuffer);
        if (inputBuffer->buffer.compare(".exit") == 0) {
            freeInputBuffer(inputBuffer);
            exit(EXIT_SUCCESS);
        }
        else {
            cout << "Unrecognized command "<<inputBuffer->buffer<<"\n";
        }
    }
    return 0;
}

