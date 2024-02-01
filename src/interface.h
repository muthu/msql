/* https://www.reddit.com/r/C_Programming/comments/sbp0k4/if_i_define_my_structs_in_the_h_file_what_do_i/ 
 * super useful thread that explains the use of ifndef
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__


#include <cstddef>
#include <cstdio>
#include <string>

/*
 * InputBuffer is a wrapper around the buffer that is used for reading user input.
 * @buffer : stores the user input
 * @bufferLength: 
 * @inputLength: 
 */
typedef struct {
    std::string buffer;
    size_t bufferLength;
    ssize_t inputLength;
}InputBuffer;

/*
 * This function returns a pointer to the wrapper object InputBuffer
 * Initializes the buffer as an empty string, bufferLength and inputLength to 0
 */
InputBuffer* newInputBuffer(); 

/*
 * freeInputBuffer: frees in the inputBuffer object we created for storing the user input
 */
void freeInputBuffer(InputBuffer* inputBuffer); 

/*
 * readInput function reads a line of input and stores the information accordingly into the inputBuffer
 *  @inputBuffer: Pointer the inputBuffer object which is used for storing the user input
 *   if user input is empty then the program exits
 */
void readInput(InputBuffer* inputBuffer); 

#endif
