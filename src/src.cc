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

        Statement statement;
        switch (prepareStatement(inputBuffer, &statement)) {
            case SUCCESS:
                break;
            case SYNTAX_ERROR:
                cout << "Syntax error. Could not parse statement\n";
                continue;
            case UNRECOGNIZED_STATEMENT:
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

