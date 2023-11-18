#ifndef SMARTCALC1_MODEL_H
#define SMARTCALC1_MODEL_H

#include <QObject>
#include "../structures.h"

namespace s21 {

class Model : public QObject {
    Q_OBJECT

    using string = std::string;
    using vector_node = std::vector<Node>;

public:
    static Model& getInstance();

    Model(Model const&) = delete;
    Model& operator=(Model const&) = delete;

public slots:
    ModelInfo slotSmartToModel(const ViewInfo& view_info);
    ModelInfo slotCreditToModel(const ViewInfo& view_info);

signals:
    void signalModelToSmart(ModelInfo& model_info);
    void signalModelToCredit(ModelInfo& model_info);

private:
    Model() = default;
    ~Model() = default;

    //SmartCalc:

    void startSmartCalc(ModelInfo& model_info);
    void manageInputString();
    void makeTokens(vector_node& tokens);
    void makeFunctionTokens(vector_node& tokens, Node& current_token, const string& token_str, size_t& index);
    string makeNumString(const string& str, size_t &index) noexcept;
    bool checkNormalizedNum(const string& str, size_t &index) noexcept;
    void givePriorityAndValue(Node& token);
    void checkMultipleDots(const string& token_name);
    void cleanToken(Node& token) noexcept;
    void buildTokens(vector_node& tokens, Node& current_token, const string& sub_token, size_t& index);
    void checkTokens(vector_node& tokens);
    void checkTokensLoop(vector_node& tokens, const Node& multiply, const Node& minus_one);
    string checkTokenIdentity(const Node& token) noexcept;
    void rearrangeIntoPostfixNotation(const vector_node& tokens) noexcept;
    void calculateGraph(ModelInfo& model_info);
    double evaluatePostfixNotation(const vector_node& tokens);
    void turnTokensToLabel(ModelInfo& model_info) noexcept;
    void handleRuntimeExceptions(const string& exception);

    //CreditCalc:

    void startCreditCalc();
    void calculateAnnuity();
    void calculateDifferentiated();

private:
    ViewInfo view_info_;
    ModelInfo model_info_;

    //SmartCalc:

    bool   error_ = false;
    bool   graph_mode_ = false;
    bool   new_input_str_ = false;
    bool   x_string_calculate_ = false;
    double result_ = 0;
    string input_str_;
    string output_status_;
    vector_node tokens_ = {};
    vector_node x_tokens_ = {};
    std::vector<char> functional_tokens_char_ = {'+', '-', '*', '/', '^', '(', ')', 'e', 'x'};
    std::vector<string> functions_and_pi_string_ = {"π", "ln", "mod", "log", "sin", "cos", "tan", "asin", "acos", "atan", "√"};
    std::vector<string> binary_functions_ = {"+", "-", "*", "/", "^", "mod"};
    std::map<string, int> priority_map_ = {
            {"x", -1},   {"e", -1},  {"π", -1}, {"(", 0},    {")", 0},
            {"+", 1},    {"-", 1},   {"*", 2},   {"/", 2},    {"mod", 2},
            {"sin", 3},  {"cos", 3}, {"tan", 3}, {"atan", 3}, {"acos", 3},
            {"asin", 3}, {"ln", 3},  {"log", 3}, {"√", 3}, {"^", 4}};

    //CreditCalc:

    long double loan_amount_ = 0;
    unsigned int loan_term_ = 0;
    unsigned int interest_rate_ = 0;
};

}  // namespace s21

#endif //SMARTCALC1_MODEL_H
