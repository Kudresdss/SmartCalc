#include "model.h"

namespace s21 {

static Model& Model::getInstance() {
    static Model instance;
    return instance;
}

ModelInfo Model::startSmartCalc(ViewInfo v_info) {
    ModelInfo       m_info;
    vector<Node>    tokens;
    bool is_old_str = 0;

    is_old_str = manageInputString(v_info);
    try {
        if (is_old_str || error_str_) {
            tokens = makeTokens(&tokens, input_str_);
        }
    }

}

bool Model::manageInputString(ViewInfo v_info) {
    string str = v_info.input_str;

    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    if (input_str_ != str) {
        input_str_ = str;
        return (1);
    }
    return (0);
}

void Model::makeTokens(vector<Node>& tokens, string& str) {
    Node current_token;

    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        if (isdigit(c) || c == '.') {
            string num_str = makeNumString(str, &i);
            current_token.name = num_str;
            current_token.priority = -1;
            givePriorityValue(&current_token);
        }
    }
}

string Model::makeNumString(string& str, size_t *index) {
    string  num_str;
    size_t& i = *index;

    for (; isdigit(str[i]) || str[i] == '.'; ++i) {
        num_str += str[i];
    }
    if (checkNormalizedNum(str, index)) {
        num_str += str[i++];
        num_str += str[i++];
    }
    for (; isdigit(str[i]); ++i){
        num_str += str[i];
    }
    --i;

    return num_str;
}

bool Model::checkNormalizedNum(const string& str, size_t *index) {
    size_t& i = *index;

    if (str[i] == "E" &&
        (i + 2 <= str.size() &&
        (str[i + 1] == '+' || str[i + 1] == '-')) &&
        isdigit(str[i + 2])) {
        return (1);
    }
    return (0);
}

void Model::givePriorityValue(Node *token) {
    if (token->priority == -1) {
        checkMultipleDots(token->name);
        token->value = std::stod(token->name);
    } else {
        if (token->name == "e") {
            token->priority
        }
    }
}

void Model::checkMultipleDots(const string& token_name) {
    size_t dot_count = 0;

    for (char& c : token_name) {
        if (c == '.') ++dot_count;
    }
    if (dot_count > 1) throw std::runtime_error("число содержит больше одной точки.");
}

}  // namespace s21