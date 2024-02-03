#include "compiler.h"

/*
 * metaCommandState is a function that executes all the meta commands, and returns error response on unrecognized command
 * @inputBuffer: the input buffer which stores the meta command
 */
MetaCommandState doMetaCommand(InputBuffer* inputBuffer) {
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
PrepareState prepareStatement(InputBuffer* inputBuffer, Statement* statement) {
    if (inputBuffer->buffer.compare(0, 6, "insert") == 0) {
        statement->type = STATEMENT_INSERT;
        int argsAssigned = sscanf(inputBuffer->buffer.c_str(), "insert %d %s %s", &(statement->recordToInsert.id), (statement->recordToInsert.username), (statement->recordToInsert.email));
        if (argsAssigned < 3) {
            return PREPARE_SYNTAX_ERROR;
        }
        return PREPARE_SUCCESS;
    }
    if (inputBuffer->buffer.compare(0, 6, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    
    return PREPARE_UNRECOGNIZED_STATEMENT; 
}
