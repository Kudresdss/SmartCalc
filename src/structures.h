#ifndef SMARTCALC1_STRUCTURES_H
#define SMARTCALC1_STRUCTURES_H

#include <clocale>
#include <algorithm>
#include <initializer_list>
#include <string>
#include <vector>
#include <stack>

struct Node {
    // SmartCalc
    std::string  name;

    int priority = 0;
    double value = 0;

    // CreditCalc
};

struct ViewInfo {
    // SmartCalc

    std::string main_input;
    std::string x_input;

    bool main_input_exists = false;
    bool x_input_exists = false;
    bool x_in_main_input = false;

    unsigned int points_density = 1000;
    double x_max = 100;
    double x_min = -100;
    double y_max = 100;
    double y_min = -100;

    // CreditCalc

    bool annuity = 0;
    bool deferred = 0;

    unsigned long loan_amount = 0;
    unsigned int loan_term = 0;
    unsigned int interest_rate = 0;
};

struct ModelInfo {
    // SmartCalc

    std::string label_tokens;
    std::string x_label_tokens;
    std::string error;
    std::vector<std::vector<double>> x_coord = {};
    std::vector<std::vector<double>> y_coord = {};

    bool graph_mode = 0;
    double result = 0;
    double x_input_value;
    double y_result = 0;

    // CreditCalc

    long double **credit_table;
};

#endif //SMARTCALC1_STRUCTURES_H
