#include "gtest/gtest.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <ostream>
#include "interface.h"
#include "utils.h"
#include "compiler.h"
#include "table.h"
#include "engine.h"

using namespace std;

std::unique_ptr<InputBuffer> inputBuffer = newInputBuffer();
Table* table = createNewTable();

void insertOneRecord(std::ostream& out, std::istream& in) {
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
    cout<<out.str();
    // string output = testing::internal::GetCapturedStdout();
    // cout<<output<<"\n";
    EXPECT_EQ(out.str(), "db > Executed\n");
}

