#include "gtest/gtest.h"
#include <memory>
#include "utils.h"
#include "interface.h"
#include "compiler.h"

using namespace std;

PrepareState func(string& input, Statement& statement) {
    std::unique_ptr<InputBuffer> inputBuffer = newInputBuffer();
    ostringstream out;
    istringstream in(input);
    readInput(inputBuffer, out, in);
    return prepareStatement(inputBuffer, &statement);
}

TEST(readInputTests, wrongIdType) {
    Statement statement;
    string inp = "insert abc foo foo@bar.com";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, SYNTAX_ERROR);
}

TEST(readInputTests, correctInsert) {
    Statement statement;
    string inp = "insert 1 foo foo@bar.com";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, SUCCESS);
}

TEST(readInputTests, correctSelect) {
    Statement statement;
    string inp = "select";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, SUCCESS);
}

TEST(readInputTests, correctExit) {
    Statement statement;
    string inp = ".exit";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, SUCCESS);
}

TEST(readInputTests, idOutOfBounds) {
    Statement statement;
    string inp = "insert 4294967296 foo foo@bar.com";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, ID_OUT_OF_BOUNDS);
}

TEST(readInputTests, usernameOutOfBounds) {
    Statement statement;
    string inp = "insert 1 f";
    for (int i = 0; i < COLUMN_USERNAME_SIZE; i++) {
        inp.push_back('f');
    }
    inp += " foo@bar.com";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, USERNAME_OUT_OF_BOUNDS);
}

TEST(readInputTests, emailOutOfBounds) {
    Statement statement;
    string inp = "insert 1 foo f";
    for (int i = 0; i < COLUMN_EMAIL_SIZE; i++) {
        inp.push_back('f');
    }
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, EMAIL_OUT_OF_BOUNDS);
}

TEST(readInputTests, idNegative) {
    Statement statement;
    string inp = "insert -1 foo foo@bar.com";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, ID_NEGATIVE);
}

TEST(readInputTests, correctInsertStatementType) {
    Statement statement;
    string inp = "insert 1 foo foo@bar.com";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(statement.type, INSERT);
}

TEST(readInputTests, correctMetaExitStatementType) {
    Statement statement;
    string inp = ".exit";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(statement.type, META_EXIT);
}

TEST(readInputTests, correctSelectStatementType) {
    Statement statement;
    string inp = "select";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(statement.type, SELECT);
}

TEST(readInputTests, unrecognizedCommand) {
    Statement statement;
    string inp = "asdffgg 1 foo foo@bar.com";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, UNRECOGNIZED_STATEMENT);
}

TEST(readInputTests, unrecognizedMetaCommand) {
    Statement statement;
    string inp = ".view";
    PrepareState result = func(inp, statement);
    EXPECT_EQ(result, UNRECOGNIZED_STATEMENT);
}
