#ifndef __COMPILER_H__
#include "compiler.h"
#endif

#ifndef __TABLE_H__
#include "table.h"
#endif

#ifndef __ENGINE_H__
#define __ENGINE_H__

typedef enum {
    EXECUTE_TABLE_FULL,
    EXECUTE_SUCCESS
}ExecuteResult;

/*
 * metaCommandState is a function that executes all the meta commands, and returns error response on unrecognized command
 * @inputBuffer: the input buffer which stores the meta command
 */
ExecuteResult executeMetaExit(Statement* statement);

ExecuteResult executeInsert(Statement* statement, Table* table);

ExecuteResult executeSelect(Statement* statement, Table* table);

/*
 * executeStatement: executes the statement that is passed to it
 * @statement: pointer to the statement struct that stores the type of statement to be executed
*/
ExecuteResult executeStatement(Statement* statement, Table* table);

#endif
