#ifndef SMARTCALC1_STRUCTURES_H
#define SMARTCALC1_STRUCTURES_H

#include <clocale>
#include <algorithm>
#include <initializer_list>
#include <string>
#include <vector>
#include <stack>

struct Node {
    std::string  name;

    int priority = 0;
    double value = 0;
};

struct ViewInfo {
    std::string input_string;
    std::string x_string = "0";

    unsigned int points_density = 1000;
    double x_max = 10;
    double x_min = -10;
    double y_max = 10;
    double y_min = -10;
};

struct ModelInfo {
    std::string label;
    std::string error;
    std::vector<std::vector<double>> x_coord = {};
    std::vector<std::vector<double>> y_coord = {};

    bool graph_mode = 0;
    double result = 0;
    double y_result = 0;
};

#endif //SMARTCALC1_STRUCTURES_H
