
#ifndef __CSTDINT_H__
#define __CSTDINT_H__ 
#include <cstdint>
#endif 

#ifndef __UTILS_H__
#include "utils.h"
#endif

#ifndef __RECORD_H__
#define __RECORD_H__ 

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
    uint32_t id;
    std::string username;
    std::string email;
}Record;

const uint32_t ID_SIZE = ATTRIBUTE_SIZE(Record, id);
const uint32_t USERNAME_SIZE = ATTRIBUTE_SIZE(Record, username);
const uint32_t EMAIL_SIZE = ATTRIBUTE_SIZE(Record, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t RECORD_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

void printRow(Record* row);

#endif
