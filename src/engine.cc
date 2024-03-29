#include "engine.h"


/*
 * metaCommandState is a function that executes all the meta commands, and returns error response on unrecognized command
 * @inputBuffer: the input buffer which stores the meta command
 */
ExecuteResult executeMetaExit(Statement* statement) {
    exit(EXIT_SUCCESS);
}

ExecuteResult executeInsert(Statement* statement, Table* table) {
    if (table->numRows == TABLE_MAX_RECORDS) {
        return EXECUTE_TABLE_FULL;
    }
    void* loc = rowNumToAddress(table, table->numRows);
    serializeRecord(&(statement->recordToInsert), loc);
    table->numRows++;
    return EXECUTE_SUCCESS;
}

ExecuteResult executeSelect(Statement* statement, Table* table) {
    Record record;
    for (uint32_t i = 0; i < table->numRows; i++) {
        void* source = rowNumToAddress(table, i);
        deSerializeRecord(source, &record);
        printRow(&record);
    }
    return EXECUTE_SUCCESS;
}

/*
 * executeStatement: executes the statement that is passed to it
 * @statement: pointer to the statement struct that stores the type of statement to be executed
*/
ExecuteResult executeStatement(Statement* statement, Table* table) {
    switch (statement->type) {
        case META_EXIT:
            return executeMetaExit(statement);
            break;
        case SELECT:
            return executeSelect(statement, table);
            break;
        case INSERT:
            return executeInsert(statement, table);
            break;
    }
}
