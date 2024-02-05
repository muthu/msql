#include <iostream>
#include <memory>
#include "interface.h"
#include "utils.h"
#include "compiler.h"
#include "table.h"
#include "engine.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::unique_ptr<InputBuffer> inputBuffer = newInputBuffer();
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

            case ID_NEGATIVE:
                cout << "User ID is negative\n";
                continue;

            case ID_OUT_OF_BOUNDS:
                cout << "User ID is out of bounds\n";
                continue;

            case USERNAME_OUT_OF_BOUNDS:
                cout << "Username is negative\n";
                continue;

            case EMAIL_OUT_OF_BOUNDS:
                cout << "Email is negative\n";
                continue;

              break;
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

