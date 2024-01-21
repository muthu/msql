#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

/*
 * This enum represents the state of meta command, meta commands are commands like .exit, .help etc
 * @META_COMMAND_SUCCESS: this implies that the user input was indeed a meta command
 */
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
}metaCommandState;

/*
 * This enum represents the state of sql command, sql commands are like INSERT, SELECT etc
 */
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
}prepareState;

typedef enum {
    STATEMENT_SELECT,
    STATEMENT_INSERT
}statementType;

typedef struct {
    statementType type;
}statement;

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
 * This function prints the prompt that the user is presented with
 */
void printPrompt() {
    cout << "db > ";
}

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

/*
 * metaCommandState is a function that executes all the meta commands, and returns error response on unrecognized command
 * @inputBuffer: the input buffer which stores the meta command
 */
metaCommandState doMetaCommand(InputBuffer* inputBuffer) {
    if (inputBuffer->buffer.compare(".exit") == 0) {
        freeInputBuffer(inputBuffer);
        exit(EXIT_SUCCESS);
    }
    else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

/*
 * prepareStatement is a function that sets the type of sql statement that is being requested by the user
 * @inputBuffer: buffer storing the user input 
 * @statement: stores the type of statement being requested by the user
 */
prepareState prepareStatement(InputBuffer* inputBuffer, statement* statement) {
    if (inputBuffer->buffer.compare(0, 6, "insert") == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (inputBuffer->buffer.compare(0, 6, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    
    return PREPARE_UNRECOGNIZED_STATEMENT; 
}

void executeStatement(statement* statement) {
    switch (statement->type) {
        case STATEMENT_SELECT:
            cout << "This is where we would the execute the select statement\n";
            break;
        case STATEMENT_INSERT:
            cout << "This is where we would the execute the insert statement\n";
            break;
    }
}

int main(int argc, char *argv[]) {
    InputBuffer* inputBuffer = newInputBuffer();
    while (true) {
        printPrompt();
        readInput(inputBuffer);
        if (inputBuffer->buffer[0] == '.') {
            switch (doMetaCommand(inputBuffer)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    cout << "Unrecognized command "<<inputBuffer->buffer<<"\n";
                    continue;
            }
        }

        statement *statement;
        switch (prepareStatement(inputBuffer, statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                cout << "Unrecognized keyword at the start of "<<inputBuffer->buffer<<"\n";
                continue;
        
        }

        executeStatement(statement);
        cout << "Executed \n";
    }
    return 0;
}

