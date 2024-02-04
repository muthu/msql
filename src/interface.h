/* https://www.reddit.com/r/C_Programming/comments/sbp0k4/if_i_define_my_structs_in_the_h_file_what_do_i/ 
 * super useful thread that explains the use of ifndef
 */

// #ifndef __CSTDDEF_H__
// #define __CSTDDEF_H__
// #include <cstddef>
// #endif

// #ifndef __CSTDIO_H__
// #define __CSTDIO_H__
// #include <cstdio>
// #endif

#ifndef __MEMORY_H__
#define __MEMORY_H__
#include <memory>
#endif

#ifndef __STRING_H__
#define __STRING_H__
#include <string>
#endif

#ifndef __OSTREAM_H__
#define __OSTREAM_H__
#include <ostream>
#endif

#ifndef __ISTREAM_H__
#define __ISTREAM_H__
#include <istream>
#endif

#ifndef __INTERFACE_H__
#define __INTERFACE_H__
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
std::unique_ptr<InputBuffer> newInputBuffer(); 

/*
 * readInput function reads a line of input and stores the information accordingly into the inputBuffer
 *  @inputBuffer: Pointer the inputBuffer object which is used for storing the user input
 *   if user input is empty then the program exits
 */
void readInput(std::unique_ptr<InputBuffer>& inputBuffer, std::ostream& out,  std::istream& in); 


/*
 * readInput function reads a line of input and stores the information accordingly into the inputBuffer
 *  @inputBuffer: Pointer the inputBuffer object which is used for storing the user input
 *   if user input is empty then the program exits
 */
void readInput(std::unique_ptr<InputBuffer>& inputBuffer); 

#endif
