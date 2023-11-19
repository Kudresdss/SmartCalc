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
    static Model& GetInstance();

    Model(Model const&) = delete;
    Model& operator=(Model const&) = delete;

public slots:
    ModelInfo SlotSmartToModel(const ViewInfo& view_info);
    ModelInfo SlotCreditToModel(const ViewInfo& view_info);

signals:
    void SignalModelToSmart(ModelInfo& model_info);
    void SignalModelToCredit(ModelInfo& model_info);

private:
    Model() = default;
    ~Model() = default;

    // SmartCalc:

    void StartSmartCalc(ModelInfo& model_info);
    void ManageInputString();
    void MakeTokens(vector_node& tokens);
    void MakeFunctionTokens(vector_node& tokens, Node& current_token, const string& token_str, size_t& index);
    string MakeNumString(const string& str, size_t &index) noexcept;
    bool CheckNormalizedNum(const string& str, size_t &index) noexcept;
    void GivePriorityAndValue(Node& token);
    void CheckMultipleDots(const string& token_name);
    void CleanToken(Node& token) noexcept;
    void BuildTokens(vector_node& tokens, Node& current_token, const string& sub_token, size_t& index);
    void CheckTokens(vector_node& tokens);
    void CheckTokensLoop(vector_node& tokens, const Node& multiply, const Node& minus_one);
    string CheckTokenIdentity(const Node& token) noexcept;
    void RearrangeIntoPostfixNotation(const vector_node& tokens) noexcept;
    void CalculateGraph(ModelInfo& model_info);
    double EvaluatePostfixNotation(const vector_node& tokens);
    void TurnTokensToLabel(ModelInfo& model_info) noexcept;
    void HandleRuntimeExceptions(const string& exception);

    // CreditCalc:

    void StartCreditCalc();
    void CalculateAnnuity();
    void CalculateDifferentiated();

private:
    ViewInfo view_info_;
    ModelInfo model_info_;

    // SmartCalc:

    bool   error_ = false;
    bool   graph_mode_ = false;
    bool   new_input_str_ = false;
    bool   x_string_calculate_ = false;
    double result_ = 0;
    string input_str_;
    string output_status_;
    vector_node tokens_;
    vector_node x_tokens_;
    std::vector<char> functional_tokens_char_ = {'+', '-', '*', '/', '^', '(', ')', 'e', 'x'};
    std::vector<string> functions_and_pi_string_ = {"π", "ln", "mod", "log", "sin", "cos", "tan", "asin", "acos", "atan", "√"};
    std::vector<string> binary_functions_ = {"+", "-", "*", "/", "^", "mod"};
    std::map<string, int> priority_map_ = {
            {"x", -1},   {"e", -1},  {"π", -1}, {"(", 0},    {")", 0},
            {"+", 1},    {"-", 1},   {"*", 2},   {"/", 2},    {"mod", 2},
            {"sin", 3},  {"cos", 3}, {"tan", 3}, {"atan", 3}, {"acos", 3},
            {"asin", 3}, {"ln", 3},  {"log", 3}, {"√", 3}, {"^", 4}};

    // CreditCalc:

    long double loan_amount_ = 0;
    unsigned int loan_term_ = 0;
    unsigned int interest_rate_ = 0;
};

}  // namespace s21

#endif //SMARTCALC1_MODEL_H
