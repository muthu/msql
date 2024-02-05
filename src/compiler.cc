#include "compiler.h"
#include <sstream>
#include <stdexcept>
#include <string>

/*
 * prepareStatement is a function that sets the type of sql statement that is being requested by the user
 * @inputBuffer: buffer storing the user input 
 * @statement: stores the type of statement being requested by the user
 */
PrepareState prepareStatement(std::unique_ptr<InputBuffer>& inputBuffer, Statement* statement) {
    std::stringstream stream(inputBuffer->buffer);
    std::string command;
    stream >> command;

    if (command == ".exit") {
        statement->type = META_EXIT;
        return SUCCESS;
    }
    if (command == "insert") {
        statement->type = INSERT;
        std::string id;

        stream >> id;
        if (id[0] == '-') {
            return ID_NEGATIVE;
        }
        if (stream.fail()) {
            stream.clear();
            return SYNTAX_ERROR;
        }
        try {
            unsigned long temp = std::stoul(id);
            uint32_t val = temp;
            if (val != temp) {
                throw std::out_of_range("Limit Exceeded");
            }
            statement->recordToInsert.id = val;
        }
        catch (std::invalid_argument& e) {
            return SYNTAX_ERROR;
        }
        catch (std::out_of_range& e) {
            return ID_OUT_OF_BOUNDS;
        }


        stream >> statement->recordToInsert.username;
        if (stream.fail()) {
            stream.clear();
            return SYNTAX_ERROR;
        }
        else if (statement->recordToInsert.username.size() > COLUMN_USERNAME_SIZE) {
            return USERNAME_OUT_OF_BOUNDS;
        }
        stream >> statement->recordToInsert.email;
        if (stream.fail()) {
            stream.clear();
            return SYNTAX_ERROR;
        }
        else if (statement->recordToInsert.email.size() > COLUMN_EMAIL_SIZE) {
            return EMAIL_OUT_OF_BOUNDS;
        }
        return SUCCESS;
    }
    if (command == "select") {
        statement->type = SELECT;
        return SUCCESS;
    }
    
    return UNRECOGNIZED_STATEMENT; 
}
