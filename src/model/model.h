#ifndef SMARTCALC1_MODEL_H
#define SMARTCALC1_MODEL_H


#include <QObject>
#include "../structures.h"

namespace s21 {

// Класс модели сделан singleton'ом, так как может существовать только одна модель
class Model : public QObject {
    Q_OBJECT

    using std::string;
    using std::vector;

public:
    static Model& getInstance();

    ModelInfo startSmartCalc(ViewInfo v_info);
    double getResult();
    string getStatus();

private:
    //Приватный конструктор и деструктор, так как их нельзя давать создавать.
    Model();
    ~Model();

    //Конструктор и оператор копирования удалены, так как экземпляр класса статический.
    //Конструктор и оператор перемещения не создаются неявно, так как все, что связано с копированием объявлено вручную.
    Model(Model const&) = delete;
    Model& operator=(Model const&) = delete;

    bool manageInputString(ViewInfo v_info);
    void makeTokens(vector<Node>& tokens, string& str);
    string makeNumString(string& str, size_t *index);
    bool checkNormalizedNum(const string& str, size_t *index);
    void givePriorityValue(Node *token);
    void checkMultipleDots(const string& token_name);

    double result_;
    bool   error_str_ = 0;
    string input_str_ = "";
    string output_status_ = "";
    vector<Node> tokens_ = {};
};

}  // namespace s21

#endif //SMARTCALC1_MODEL_H
