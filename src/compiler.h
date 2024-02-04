#ifndef __INTERFACE_H__
#include "interface.h"
#endif

#ifndef __RECORD_H__
#include "record.h"
#endif

#ifndef __COMPILER_H__
#define __COMPILER_H__


/* 
 * This enum represents the state of sql command, sql commands are like INSERT, SELECT etc 
 */
typedef enum {
    SUCCESS,
    SYNTAX_ERROR,
    UNRECOGNIZED_STATEMENT,
}PrepareState;

typedef enum {
    META_EXIT,
    SELECT,
    INSERT
}StatementType;

typedef struct {
    StatementType type;
    Record recordToInsert;
}Statement;

/*
 * prepareStatement is a function that sets the type of sql statement that is being requested by the user
 * @inputBuffer: buffer storing the user input 
 * @statement: stores the type of statement being requested by the user
 */
PrepareState prepareStatement(std::unique_ptr<InputBuffer>& inputBuffer, Statement* statement); 

#endif
