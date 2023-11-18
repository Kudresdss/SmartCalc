#include "test_core.h"

bool findError(const std::string& input) {
    bool out = false;
    if (input.find("Runtime error") != std::string::npos) {
        out = true;
    }
    return out;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
