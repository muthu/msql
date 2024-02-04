#ifndef __OSTREAM_H__
#define __OSTREAM_H__
#include <ostream>
#endif

#ifndef __UTILS_H__
#define __UTILS_H__

#define ATTRIBUTE_SIZE(struct, attribute) sizeof(((struct*) nullptr)->attribute)

/*
 * This function prints the prompt that the user is presented with
 */
void printPrompt(std::ostream& out);


/*
 * This function prints the prompt that the user is presented with
 */
void printPrompt();

#endif
