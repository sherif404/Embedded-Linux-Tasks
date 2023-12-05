#include <gtest/gtest.h>
#include "Requester.h"

// Test fixture for the Requester class
class RequesterTest : public ::testing::Test {
protected:
    Requester requester;
};

// Test case for the printFileContent function
TEST_F(RequesterTest, PrintFileContentTest) {
    
   requester.printFileContent("/.");
    // ASSERT_... statements to check the expected behavior
}

// Test case for the listDirectory function
TEST_F(RequesterTest, ListDirectoryTest) {
 
   requester.listDirectory("/.");
   //ASSERT_... statements to check the expected behavior
}

// Entry point for the tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
