#include "gtest/gtest.h"
#include <memory>
#include "interface.h"
#include "utils.h"

using namespace std;


// always use full directory path for the txt file
TEST(interfaceTests, zeroInput) {
    std::unique_ptr<InputBuffer> inputBuffer = newInputBuffer();
    ostringstream out;
    string inp = "";
    istringstream in(inp);
    readInput(inputBuffer, out, in);
    EXPECT_EQ(out.str(), "Error reading input\n");
}

