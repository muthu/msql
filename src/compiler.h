#ifndef __INTERFACE_H__
#include "interface.h"
#endif

#ifndef __RECORD_H__
#include "record.h"
#endif

#ifndef __COMPILER_H__
#define __COMPILER_H__
/*
 * This enum represents the state of meta command, meta commands are commands like .exit, .help etc
 * @META_COMMAND_SUCCESS: this implies that the user input was indeed a meta command
 */
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
}MetaCommandState;


/* 
 * This enum represents the state of sql command, sql commands are like INSERT, SELECT etc 
 */
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
}PrepareState;

typedef enum {
    STATEMENT_SELECT,
    STATEMENT_INSERT
}StatementType;

typedef struct {
    StatementType type;
    Record recordToInsert;
}Statement;


/*
 * metaCommandState is a function that executes all the meta commands, and returns error response on unrecognized command
 * @inputBuffer: the input buffer which stores the meta command
 */
MetaCommandState doMetaCommand(InputBuffer* inputBuffer);

/*
 * prepareStatement is a function that sets the type of sql statement that is being requested by the user
 * @inputBuffer: buffer storing the user input 
 * @statement: stores the type of statement being requested by the user
 */
PrepareState prepareStatement(InputBuffer* inputBuffer, Statement* statement); 

#endif
