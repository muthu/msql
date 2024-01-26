#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

#define ATTRIBUTE_SIZE(struct, attribute) sizeof(((struct*) nullptr)->attribute)

using namespace std;


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

typedef enum {
    EXECUTE_TABLE_FULL,
    EXECUTE_SUCCESS
}ExecuteResult;

typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE];
    char email[COLUMN_EMAIL_SIZE];
}Record;

typedef struct {
    StatementType type;
    Record recordToInsert;
}Statement;

/*
 * InputBuffer is a wrapper around the buffer that is used for reading user input.
 * @buffer : stores the user input
 * @bufferLength: 
 * @inputLength: 
 */
typedef struct {
    string buffer;
    size_t bufferLength;
    ssize_t inputLength;
}InputBuffer;

const uint32_t ID_SIZE = ATTRIBUTE_SIZE(Record, id);
const uint32_t USERNAME_SIZE = ATTRIBUTE_SIZE(Record, username);
const uint32_t EMAIL_SIZE = ATTRIBUTE_SIZE(Record, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t RECORD_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t RECORDS_PER_PAGE = PAGE_SIZE / RECORD_SIZE;
const uint32_t TABLE_MAX_RECORDS = (RECORDS_PER_PAGE * TABLE_MAX_PAGES);

typedef struct {
    uint32_t numRows;
    void *pages[TABLE_MAX_PAGES];
}Table;

/*
 * This function prints the prompt that the user is presented with
 */
void printPrompt() {
    cout << "db > ";
}

/*
 * This function returns a pointer to the wrapper object InputBuffer
 * Initializes the buffer as an empty string, bufferLength and inputLength to 0
 */
InputBuffer* newInputBuffer() {
    InputBuffer* inputBuffer = (InputBuffer*) malloc(sizeof(InputBuffer));
    inputBuffer->buffer = "";
    inputBuffer->bufferLength = 0;
    inputBuffer->inputLength = 0;
    return inputBuffer;
}

/*
 * readInput function reads a line of input and stores the information accordingly into the inputBuffer
 * @inputBuffer: Pointer the inputBuffer object which is used for storing the user input
 * if user input is empty then the program exits
 */
void readInput(InputBuffer* inputBuffer) {
    getline(cin, inputBuffer->buffer);
    inputBuffer->inputLength = inputBuffer->buffer.size();
    if (inputBuffer->inputLength <= 0) {
        cout << "Error reading input\n";
        exit(EXIT_FAILURE);
    }
}

/*
 * freeInputBuffer: frees in the inputBuffer object we created for storing the user input
 */
void freeInputBuffer(InputBuffer* inputBuffer) {
    free(inputBuffer);
}

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


/*
 * serializeRecord: store the record into memory in byte format
 * source: pointer to record which needs to be stored
 * destination: pointer to location in memory where the data is to be stored
 */
void serializeRecord(Record* source, void* destination) {
    Record* dest = static_cast<Record*>(destination);
    memcpy(&(dest->id), &(source->id), ID_SIZE);
    memcpy(&(dest->username), &(source->username), USERNAME_SIZE);
    memcpy(&(dest->email), &(source->email), EMAIL_SIZE);
}

/*
 * deSerializeRecord: change the record from stored memory format into record format which we use 
 * source: pointer to location where the converted data from memory format to record format needs to be stored
 * destination: pointer to location in memory where the data is stored
 */
void deSerializeRecord(void* source, Record* destination) {
    Record* src = static_cast<Record*>(source);
    memcpy(&(destination->id), &(src->id), ID_SIZE);
    memcpy(&(destination->username), &(src->username), USERNAME_SIZE);
    memcpy(&(destination->email), &(src->email), EMAIL_SIZE);
}

/*
 * rowNumToAddress: given the table and rowNum this function returns the memory address where the record with rowNum needs to be stored
 * @table: The table in which the record needs to be stored
 * @rowNum: The row number of the record which needs to be stored
 */
void* rowNumToAddress(Table* table, uint32_t rowNum) {
    uint32_t pageNum = rowNum / RECORDS_PER_PAGE;
    void* page = table->pages[pageNum];
    if (page == nullptr) {
       page = table->pages[pageNum] = (void*) malloc(PAGE_SIZE);
    }
    uint32_t rowOffset = rowNum % RECORDS_PER_PAGE;
    Record* ptr = static_cast<Record*>(page);
    // uint32_t byteOffset = rowOffset * RECORD_SIZE;
    return static_cast<void*>(ptr + rowOffset);
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

void printRow(Record* row) {
    cout << row->id << " " << row->username << " " << row->email << "\n";
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
        case STATEMENT_SELECT:
            return executeSelect(statement, table);
            break;
        case STATEMENT_INSERT:
            return executeInsert(statement, table);
            break;
    }
}

Table* createNewTable() {
    Table* table =static_cast<Table*>(malloc(sizeof(Table)));
    table->numRows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        table->pages[i] = nullptr;
    }
    return table;
}

void freeTable(Table* table) {
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        free(table->pages[i]);
    }
    free(table);
}

int main(int argc, char *argv[]) {
    InputBuffer* inputBuffer = newInputBuffer();
    Table* table = createNewTable();
    while (true) {
        printPrompt();
        readInput(inputBuffer);
        if (inputBuffer->buffer[0] == '.') {
            switch (doMetaCommand(inputBuffer)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    cout << "Unrecognized command "<<inputBuffer->buffer<<"\n";
                    continue;
            }
        }

        Statement statement;
        switch (prepareStatement(inputBuffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_SYNTAX_ERROR:
                cout << "Syntax error. Could not parse statement\n";
                continue;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                cout << "Unrecognized keyword at the start of "<<inputBuffer->buffer<<"\n";
                continue;
        
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

