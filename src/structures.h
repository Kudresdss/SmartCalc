#ifndef SMARTCALC1_STRUCTURES_H
#define SMARTCALC1_STRUCTURES_H

#include <string>

using namespace std {

struct Node {
    string  name = "";
    int     priority = 0;
    double  value = 0;
};

struct ViewInfo {
    string input_str = "";
    string x_param = "1";
};

struct ModelInfo {
    string label = "";
    double result = 0;
    double x_result = 0;
};

}  // namespace std

#endif //SMARTCALC1_STRUCTURES_H
