#include <iostream>
#include "record.h"

void printRow(Record* row) {
    std::cout << row->id << " " << row->username << " " << row->email << "\n";
}
