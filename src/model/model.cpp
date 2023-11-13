#include "model.h"

namespace s21 {

Model& Model::getInstance() {
    static Model instance;
    return instance;
}

//SmartCalc:

double Model::getResult() { return result_; }

std::string Model::getStatus() { return output_status_; }

void Model::slotSmartToModel(const ViewInfo& view_info) {
    ModelInfo model_info_main_input;
    ModelInfo model_info_x_input;

    view_info_ = view_info;
    error_ = false;
    if (view_info_.x_input_exists) {
        x_string_calculate_ = true;
        manageInputString();
        startSmartCalc(model_info_x_input);
        model_info_main_input.x_input_value = model_info_x_input.result;
        model_info_main_input.x_label_tokens = "X: " + model_info_x_input.label_tokens;
        model_info_main_input.graph_mode = true;
        model_info_main_input.error = model_info_x_input.error;
        graph_mode_ = true;
        x_string_calculate_ = false;
    }
    if (!error_) {
        manageInputString();
        startSmartCalc(model_info_main_input);
    }
    model_info_main_input.label_tokens = "[]: " + model_info_main_input.label_tokens;
    emit signalModelToSmart(model_info_main_input);
}

void Model::manageInputString() {
    string str;

    if (x_string_calculate_)
        str = view_info_.x_input;
    else
        str = view_info_.main_input;

    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    if ((old_main_input_str_ != str && !x_string_calculate_) || (old_x_input_str_ != str && x_string_calculate_)) {
        input_str_ = str;
        new_input_str_ = true;
    } else
        new_input_str_ = false;
}

void Model::startSmartCalc(ModelInfo& model_info) {
    vector_node tokens;

    model_info_ = model_info;
    try {
        if (new_input_str_) {
            makeTokens(tokens);
            checkTokens(tokens);
            rearrangeIntoPostfixNotation(tokens);
            if (graph_mode_)
                calculateGraph(model_info);
            model_info.result = evaluatePostfixNotation(tokens_);
            turnTokensToLabel(model_info);
            result_ = model_info.result;
            output_status_ = model_info.label_tokens;
        }
    }
    catch (const std::exception& error) {
        string error_str = "Runtime error: ";
        model_info.error = error_str + error.what();
        error_ = true;
    }
}

void Model::makeTokens(vector_node& tokens) {
    Node    current_token;
    string& str = input_str_;

    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        if (isdigit(c) || c == '.') {
            string num_str = makeNumString(str, i);
            current_token.name = num_str;
            current_token.priority = -1;
            givePriorityAndValue(current_token);
            tokens.push_back(current_token);
        } else {
            if (!current_token.name.empty()) cleanToken(current_token);
            if (std::any_of(functional_tokens_.begin(), functional_tokens_.end(),
                            [c](char func_token){return func_token == c;}))
                buildTokens(tokens, current_token, string(1, c), i);
            else makeFunctionTokens(tokens, current_token, str, i);
        }
        cleanToken(current_token);
    }
}

void Model::makeFunctionTokens(vector_node& tokens, Node& current_token, const string& token_str, size_t& index) {
    size_t& i = index;
    size_t size_str = token_str.size();
    bool error = true;

    for (string& func_iter : functions_) {
        if (i < size_str - (func_iter.size() -1) && token_str.substr(i, func_iter.size()) == func_iter) {
            buildTokens(tokens, current_token, func_iter, i);
            error = false;
        }
    }
    if (error) handleRuntimeExceptions("invalid expression: unknown token");
}

std::string Model::makeNumString(const string& str, size_t& index) noexcept {
    string  num_str;
    size_t& i = index;

    for (; isdigit(str[i]) || str[i] == '.'; ++i)
        num_str += str[i];
    if (checkNormalizedNum(str, index)) {
        num_str += str[i++];
        num_str += str[i++];
    }
    for (; isdigit(str[i]); ++i)
        num_str += str[i];
    --i;

    return num_str;
}

bool Model::checkNormalizedNum(const string& str, size_t &index) noexcept {
    size_t& i = index;

    if (str[i] == 'E' &&
        (i + 2 <= str.size() &&
        (str[i + 1] == '+' || str[i + 1] == '-')) &&
        isdigit(str[i + 2])) {
        return true;
    }
    return false;
}

void Model::givePriorityAndValue(Node& token) {
    if (token.priority == -1) {
        checkMultipleDots(token.name); //добавить обработку строки х
        token.value = std::stod(token.name);
    } else {
        token.priority = priority_map_[token.name];
        if (token.name == "e") token.value = std::exp(1.0);
        else if (token.name == "π") token.value = std::acos(-1.0);
    }
}

void Model::checkMultipleDots(const string& token_name) {
    size_t dot_count = 0;

    for (const char& token_iter : token_name) {
        if (token_iter == '.') ++dot_count;
    }
    if (dot_count > 1) handleRuntimeExceptions("invalid expression: a number contains more than one dot");
}

void Model::cleanToken(Node& token) noexcept {
    token.name = "";
    token.priority = 0;
    token.value = 0;
}

void Model::buildTokens(vector_node& tokens, Node& current_token, const string& sub_token, size_t& index) {
    index += sub_token.length() - 1;
    current_token.name = sub_token;
    givePriorityAndValue(current_token);
    tokens.push_back(current_token);
}

void Model::checkTokens(vector_node& tokens) {
    Node                    multiply = {"*", 2, 0.0};
    Node                    minus_one = {"-1", -1, -1.0};

    auto func_check_brackets_count = [&, open_brackets = 0, close_brackets = 0]() mutable -> bool {
        for (Node& token_iter : tokens) {
            if (token_iter.name == "(") ++open_brackets;
            if (token_iter.name == ")") ++close_brackets;
        }
        if (open_brackets == close_brackets)
            return true;
        return false;
    };

    if (tokens.empty())
        handleRuntimeExceptions("can't convert input into tokens");
    if (tokens.size() > 1 && tokens[0].name == "+") tokens.erase(tokens.begin());
    if (tokens[0].name == "-") {
        tokens[0] = minus_one;
        tokens.insert(tokens.begin() + 1, multiply);
    }
    if (!(func_check_brackets_count()))
        handleRuntimeExceptions("incorrect usage of brackets: some brackets are not in pair");
    checkTokensLoop(tokens, multiply, minus_one);

    size_t last_elem = tokens.size() - 1;
    if (tokens[0].name == ")")
        handleRuntimeExceptions("incorrect usage of brackets: closing bracket in the beginning of expression");
    else if (checkTokenIdentity(tokens[0]) == "binary function")
        handleRuntimeExceptions("incorrect usage of functions: binary function in the beginning of expression");
    if (tokens[last_elem].name == "(")
        handleRuntimeExceptions("incorrect usage of brackets: opening bracket in the end of expression");
    else if (checkTokenIdentity(tokens[last_elem]) == "unary function")
        handleRuntimeExceptions("incorrect usage of functions: unary function in the end of expression");
    else if (checkTokenIdentity(tokens[last_elem]) == "binary function")
        handleRuntimeExceptions("incorrect usage of functions: binary function in the end of expression");
}

void Model::checkTokensLoop(vector_node& tokens, const Node& multiply, const Node& minus_one) {
    auto begin = tokens.begin();
    size_t i = 0;

    auto func_token_insert_multiply = [&i, &tokens, begin, multiply](const size_t count) {
        tokens.insert(begin + i + count, multiply);
        ++i;
    };

    for (; i < tokens.size(); ++i) {
        if (i + 1 < tokens.size()) {
            if ((tokens[i].priority == -1 && tokens[i + 1].priority == -1) ||
                   (tokens[i].name == "x" && tokens[i + 1].name == "x")) {
                handleRuntimeExceptions("implementation choice: can't yet process multiplication by literals"
                                        " without a corresponding function token");
            } else if (tokens[i].name == ")" && tokens[i + 1].name == "(") {
                func_token_insert_multiply(1);
            } else if (tokens[i].name == "(" && tokens[i + 1].name == "-") {
                tokens[i + 1] = minus_one;
                func_token_insert_multiply(2);
            } else if ((tokens[i].priority == -1 || tokens[i].name == ")") &&
                       checkTokenIdentity(tokens[i + 1]) == "unary function") {
                func_token_insert_multiply(1);
            } else if (tokens[i].name == "(" && tokens[i + 1].name == "+") {
                tokens.erase(begin + i + 1);
            } else if (tokens[i].name == "(" && tokens[i + 1].name == ")") {
                handleRuntimeExceptions("incorrect usage of brackets: empty brackets");
            } else if (checkTokenIdentity(tokens[i]) == "binary function" &&
                       checkTokenIdentity(tokens[i + 1]) == "binary function") {
                handleRuntimeExceptions("incorrect usage of functions: two consecutive binary functions");
            } else if (checkTokenIdentity(tokens[i]) == "unary function" &&
                       checkTokenIdentity(tokens[i + 1]) == "binary function") {
                handleRuntimeExceptions("incorrect usage of functions: binary function after an unary function");
            }
        }
    }
}

std::string Model::checkTokenIdentity(const Node& token) noexcept {
    string token_identity;

    if (token.priority == -1) token_identity = "number";
    else if (token.priority == 0) token_identity = "brackets or empty";
    else if (std::any_of(binary_functions_.begin(), binary_functions_.end(),
                         [&token](std::string& function){return token.name == function;}))
        token_identity = "binary function";
    else token_identity = "unary function";

    return token_identity;
}

void Model::rearrangeIntoPostfixNotation(const vector_node& tokens) noexcept {
    vector_node result;
    std::stack<Node>  operations;

    auto func_push_operations_to_result = [&]() {
        result.push_back(operations.top());
        operations.pop();
    };

    for (const Node& token_iter : tokens) {
        if (token_iter.priority == -1) result.push_back(token_iter);
        else if (token_iter.name == "(") operations.push(token_iter);
        else if (token_iter.name == ")") {
            while (!operations.empty() && operations.top().name != "(")
                func_push_operations_to_result();
            if (!operations.empty()) operations.pop();
        }
        else if (priority_map_.find(token_iter.name) != priority_map_.end()) {
            while (!operations.empty() && priority_map_[operations.top().name] >= priority_map_[token_iter.name])
                func_push_operations_to_result();
            operations.push(token_iter);
        }
    }
    while (!operations.empty())
        func_push_operations_to_result();

    error_ = false;
    tokens_ = result;
}

void Model::calculateGraph(ModelInfo& model_info) {
    const ViewInfo& v = view_info_;
    ModelInfo& m = model_info;
    vector_node x_tokens = tokens_;
    std::vector<double> x_temp;
    std::vector<double> y_temp;

    auto func_push_x_y_temp = [&]() {
        m.x_coord.push_back(x_temp);
        m.y_coord.push_back(y_temp);
    };

    for (double x_val = v.x_min; x_val < v.x_max; x_val += (v.x_max - v.x_min) / v.points_density) {
        for (Node& x_token : x_tokens) {
            if (x_token.name == "x") {
                x_token.value = x_val;
            }
        }
        try {
            m.y_result = evaluatePostfixNotation(x_tokens);
            if (m.y_result < v.y_min || m.y_result > v.y_max)
                handleRuntimeExceptions("y coordinate is out of bounds");
            x_temp.push_back(x_val);
            y_temp.push_back(m.y_result);
        } catch (...) {
            if (!x_temp.empty()) {
                func_push_x_y_temp();
                x_temp.clear();
                y_temp.clear();
            }
        }
    }
    if (!x_temp.empty()) func_push_x_y_temp();
}

double Model::evaluatePostfixNotation(const vector_node& tokens) {
    std::stack<double> numbers;

    if (graph_mode_){
        for (Node& x_token : tokens_)
            if (x_token.name == "x") x_token.value = model_info_.x_input_value;
    }

    for (const Node& token_iter : tokens) {
        if (token_iter.priority == -1) {
            numbers.push(token_iter.value);
        }
        else {
            if (numbers.empty()) handleRuntimeExceptions("invalid expression");

            double result = 0;
            double right_operand = numbers.top();
            numbers.pop();

            if (checkTokenIdentity(token_iter) == "unary function") {
                if (token_iter.name == "sin") result = std::sin(right_operand);
                else if (token_iter.name == "cos") result = std::cos(right_operand);
                else if (token_iter.name == "tan") result = std::tan(right_operand);
                else if (token_iter.name == "atan") result = std::atan(right_operand);
                else if (token_iter.name == "asin") {
                    if (right_operand < -1 || right_operand > 1)
                        handleRuntimeExceptions("invalid expression: asin of a number ∉ [-1;1]");
                    result = std::asin(right_operand); }
                else if (token_iter.name == "acos") {
                    if (right_operand < -1 || right_operand > 1)
                        handleRuntimeExceptions("invalid expression: acos of a number ∉ [-1;1]");
                    result = std::acos(right_operand); }
                else if (token_iter.name == "ln") {
                    if (right_operand <= 0)
                        handleRuntimeExceptions ("invalid expression: ln of a number ∈ (-∞;0]");
                    result = std::log(right_operand); }
                else if (token_iter.name == "log") {
                    if (right_operand <= 0)
                        handleRuntimeExceptions("invalid expression: log of a number ∈ (-∞;0]");
                    result = std::log10(right_operand); }
                else if (token_iter.name == "√") {
                    if (right_operand < 0)
                        handleRuntimeExceptions("invalid expression: square root of a negative number");
                    result = std::sqrt(right_operand);
                }
            }
            else if (checkTokenIdentity(token_iter) == "binary function") {
                if (numbers.empty()) handleRuntimeExceptions("invalid expression");

                double left_operand = numbers.top();
                numbers.pop();

                if (token_iter.name == "+") result = left_operand + right_operand;
                else if (token_iter.name == "-") result = left_operand - right_operand;
                else if (token_iter.name == "*") result = left_operand * right_operand;
                else if (token_iter.name == "^") result = std::pow(left_operand, right_operand);
                else if (token_iter.name == "/") {
                    if (right_operand == 0)
                        handleRuntimeExceptions("invalid expression: division by zero");
                    result = left_operand / right_operand; }
                else if (token_iter.name == "mod") {
                    if (right_operand == 0)
                        handleRuntimeExceptions("invalid expression: modulus of division by zero");
                    result = fmod(left_operand, right_operand);
                }
            }
            numbers.push(result);
        }
    }
    if (numbers.size() != 1) handleRuntimeExceptions("invalid expression");

    return numbers.top();
}

void Model::turnTokensToLabel(ModelInfo& model_info) noexcept {
    string label;

    for (const Node& token_iter : tokens_) {
        if (!label.empty())
            label += " ";
        label += token_iter.name;
    }
    model_info.label_tokens = label;
}

void Model::handleRuntimeExceptions(const string& exception) {
    error_ = true;
    throw std::runtime_error(exception);
}

//CreditCalc:

void Model::slotCreditToModel(const ViewInfo& view_info) {
    ModelInfo model_info;

    error_ = false;
    startCreditCalc(model_info);

    emit signalModelToSmart(model_info_);
}

void Model::startCreditCalc(ModelInfo& model_info) {
    CreditTable credit_table(view_info_.loan_term);
    credit_table_ = credit_table.getCreditTable();
    model_info_ = model_info;


    loan_amount_ = static_cast<long double>(view_info_.loan_amount);
    loan_term_ = view_info_.loan_term;
    interest_rate_ = view_info_.interest_rate;

    if (view_info_.annuity)
        calculateAnnuity();
    else if (view_info_.deferred)
        calculateDeferred();
}

void Model::calculateAnnuity() {
     long double monthly_interest_rate = interest_rate_ / static_cast<long double>(100 * 12);
     long double annuity_factor =
             monthly_interest_rate * pow(monthly_interest_rate + 1, loan_term_) /
                     (pow(monthly_interest_rate + 1, loan_term_) - 1);
     long double monthly_payment = std::round(annuity_factor * loan_amount_ * 100) / 100;

     for (unsigned int i = 0; i < loan_term_; ++i) {
         long double beginning_balance = loan_amount_;
         long double monthly_interest = loan_amount_ * monthly_interest_rate;
         long double principal = monthly_payment - loan_amount_ * monthly_interest_rate;
         loan_amount_ -= principal;
         long double ending_balance = loan_amount_;

         credit_table_[i][0] = i;
         credit_table_[i][1] = beginning_balance;
         credit_table_[i][2] = monthly_payment;
         credit_table_[i][3] = monthly_interest;
         credit_table_[i][4] = principal;
         credit_table_[i][5] = ending_balance;
     }
}

void Model::calculateDeferred() {

}

//CreditCalc - CreditTable embedded class:

Model::CreditTable::CreditTable(const unsigned int number_of_payments) {
    number_of_payments_ = number_of_payments;
    credit_table_ = new long double*[number_of_payments]();
    for (size_t i = 0; i < number_of_payments; ++i)
        credit_table_[i] = new long double[6]();
}

Model::CreditTable::~CreditTable() {
    if (credit_table_ != nullptr) {
        for (size_t i = 0; i < number_of_payments_; ++i)
            delete[] credit_table_[i];
        delete[] credit_table_;
    }
    credit_table_ = nullptr;
    number_of_payments_ = 0;
}

}  // namespace s21
