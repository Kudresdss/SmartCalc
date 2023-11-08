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

    double getResult();
    string getStatus();
//    void getModelInfoSmartCalc(const string input_string, const string x_string_value);

    Model(Model const&) = delete;
    Model& operator=(Model const&) = delete;

public slots:
    void slotSmartToModel(const ViewInfo& view_info);

signals:
    void signalModelToSmart(ModelInfo& model_info);

private:
    Model() = default;
    ~Model() = default;

    void startSmartCalc(const ViewInfo& view_info, ModelInfo& model_info);
    void manageInputString(const ViewInfo& view_info);
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
    void calculateXGraph(const ViewInfo& view_info, ModelInfo& model_info);
    double evaluatePostfixNotation(ModelInfo& model_info, const vector_node& tokens);
    void evaluatePostfixNotationForX(const ViewInfo& view_info, ModelInfo& model_info);
    void turnTokensToLabel(ModelInfo& model_info, const vector_node& tokens) noexcept;
    void handleRuntimeExceptions(const string& exception);

    double result_;
    string input_str_;
    string output_status_;
    bool   error_ = false;
    bool   new_str_ = false;
    bool   graph_mode_ = false;
    bool   x_string_calculate_ = false;
    vector_node tokens_ = {};
    std::vector<char> functional_tokens_ = {'+', '-', '*', '/', '^', '(', ')', 'e', 'x'};
    std::vector<string> functions_ = {"π", "ln", "mod", "log", "sin", "cos", "tan", "asin", "acos", "atan", "√"};
    std::vector<string> binary_functions_ = {"+", "-", "*", "/", "^", "mod"};
    std::map<string, int> priority_map_ = {
            {"x", -1},   {"e", -1},  {"π", -1}, {"(", 0},    {")", 0},
            {"+", 1},    {"-", 1},   {"*", 2},   {"/", 2},    {"mod", 2},
            {"sin", 3},  {"cos", 3}, {"tan", 3}, {"atan", 3}, {"acos", 3},
            {"asin", 3}, {"ln", 3},  {"log", 3}, {"√", 3}, {"^", 4}};
};

}  // namespace s21

#endif //SMARTCALC1_MODEL_H
