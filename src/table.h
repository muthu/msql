#ifndef __CSTDINT_H__
#define __CSTDINT_H__
#include <cstdint>
#endif

#ifndef __RECORD_H__
#include "record.h"
#endif

#ifndef __TABLE_H__
#define __TABLE_H__
const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t RECORDS_PER_PAGE = PAGE_SIZE / RECORD_SIZE;
const uint32_t TABLE_MAX_RECORDS = (RECORDS_PER_PAGE * TABLE_MAX_PAGES);

typedef struct {
    uint32_t numRows;
    void *pages[TABLE_MAX_PAGES];
}Table;

/*
 * serializeRecord: store the record into memory in byte format
 * source: pointer to record which needs to be stored
 * destination: pointer to location in memory where the data is to be stored
*/
void serializeRecord(Record* source, void* destination);

/*
 * deSerializeRecord: change the record from stored memory format into record format which we use 
 * source: pointer to location where the converted data from memory format to record format needs to be stored
 * destination: pointer to location in memory where the data is stored
*/
void deSerializeRecord(void* source, Record* destination);

/*
 * rowNumToAddress: given the table and rowNum this function returns the memory address where the record with rowNum needs to be stored
 * @table: The table in which the record needs to be stored
 * @rowNum: The row number of the record which needs to be stored
*/
void* rowNumToAddress(Table* table, uint32_t rowNum);

Table* createNewTable();

void freeTable(Table* table); 

#endif
