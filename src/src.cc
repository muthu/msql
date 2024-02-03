#include <iostream>
#include "interface.h"
#include "utils.h"
#include "compiler.h"
#include "table.h"
#include "engine.h"

using namespace std;

int main(int argc, char *argv[]) {
    InputBuffer* inputBuffer = newInputBuffer();
    Table* table = createNewTable();
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

        Statement statement;
        switch (prepareStatement(inputBuffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_SYNTAX_ERROR:
                cout << "Syntax error. Could not parse statement\n";
                continue;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                cout << "Unrecognized keyword at the start of "<<inputBuffer->buffer<<"\n";
                continue;
        
        }

        switch (executeStatement(&statement, table)) {
            case EXECUTE_SUCCESS:
                cout << "Executed\n";
                break;
            case EXECUTE_TABLE_FULL:
                cout << "Error: Table full\n";
                break;
        }
    }
    return 0;
}

