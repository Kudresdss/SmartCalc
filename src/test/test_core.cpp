#include "test_core.h"

bool containsError(const std::string& input) {
//    bool out = false;
//    // Поиск подстроки "Ошибка" во входящей строке
//    if (input.find("Ошибка") != std::string::npos) {
//        out = true;  // Подстрока найдена
//    }
//    return out;  // Подстрока не найдена
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
