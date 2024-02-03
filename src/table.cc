#include <cstdlib>
#include <cstring>
#include "table.h"

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
