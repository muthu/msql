#include "gtest/gtest.h"
#include "utils.h"
#include "interface.h"
#include "compiler.h"
#include "engine.h"

using namespace std;

TEST(readInputTests, executeInsert) {
    Record record;
    Statement statement;
    statement.recordToInsert.id = 1;
    statement.recordToInsert.username = "foo";
    statement.recordToInsert.email = "foo@bar.com";
    statement.type = INSERT;
    Table* table = new Table();
    ExecuteResult result = executeStatement(&statement, table);
    freeTable(table);
    EXPECT_EQ(result, EXECUTE_SUCCESS);
}

TEST(readInputTests, executeTableFull) {
    Record record;
    Statement statement;
    statement.recordToInsert.id = 1;
    statement.recordToInsert.username = "foo";
    statement.recordToInsert.email = "foo@bar.com";
    statement.type = INSERT;
    Table* table = new Table();
    ExecuteResult result;
    for (int i = 0; i <= TABLE_MAX_RECORDS; i++) {
        result = executeStatement(&statement, table);
    }
    freeTable(table);
    EXPECT_EQ(result, EXECUTE_TABLE_FULL);
}

TEST(readInputTests, executeSelect) {
    Record record;
    Statement statement;
    statement.type = INSERT;
    Table* table = new Table();
    ExecuteResult result = executeStatement(&statement, table);
    freeTable(table);
    EXPECT_EQ(result, EXECUTE_SUCCESS);
}
