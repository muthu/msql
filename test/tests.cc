#include "gtest/gtest.h"
#include <iostream>
#include <memory>
#include <ostream>
#include "interface.h"
#include "utils.h"
#include "compiler.h"
#include "table.h"
#include "engine.h"

using namespace std;

Table* table = createNewTable();

void insertOneRecord(std::ostream& out, std::istream& in) {
    std::unique_ptr<InputBuffer> inputBuffer = newInputBuffer();
    printPrompt(out);
    readInput(inputBuffer, out, in);

    Statement statement;
    switch (prepareStatement(inputBuffer, &statement)) {
        case SUCCESS:
            break;
        case SYNTAX_ERROR:
            out << "Syntax error. Could not parse statement\n";
            break;
        case UNRECOGNIZED_STATEMENT:
            out << "Unrecognized keyword at the start of "<<inputBuffer->buffer<<"\n";
            break;
        case ID_NEGATIVE:
            out << "User ID is negative\n";
            break;

        case ID_OUT_OF_BOUNDS:
            out << "User ID is out of bounds\n";
            break;

        case USERNAME_OUT_OF_BOUNDS:
            out << "Username is negative\n";
            break;

        case EMAIL_OUT_OF_BOUNDS:
            out << "Email is negative\n";
            break;
    }

    switch (executeStatement(&statement, table)) {
        case EXECUTE_SUCCESS:
            out << "Executed\n";
            break;
        case EXECUTE_TABLE_FULL:
            out << "Error: Table full\n";
            break;
    }
}

// always use full directory path for the txt file
TEST(tableSimulation, insertOneRecord) {
    // freopen("test/insertOneRecord.txt", "r", stdin);
    ostringstream out;
    string inp = "insert 1 foo foo@bar.com";
    istringstream in(inp);
    insertOneRecord(out, in);
    // string output = testing::internal::GetCapturedStdout();
    // cout<<output<<"\n";
    EXPECT_EQ(out.str(), "db > Executed\n");
}

