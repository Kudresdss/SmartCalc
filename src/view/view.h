#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QEvent>
#include <QObject>
#include <QPalette>
#include <QWidget>
#include "../structures.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
    Q_OBJECT

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

    void setTheme();
    void buildGraph(const ModelInfo& model_info);

public slots:
    void slotModelToSmart(ModelInfo& model_info);

private slots:
    void startSmartCalculator_SignalToModel();
    void printInLineEdit();
    void toggleNotationLable();

    void on_actionOpen_project_triggered();
    void on_actionOpen_project_2_triggered();
    void on_actionOpen_project_3_triggered();

signals:
    void signalSmartToModel(ViewInfo& view_info);

private:
    void startSmartCalculator_SignalFromModel(const ModelInfo& model_info);
    void connectAll();

    bool toggle_notation_ = false;
    Ui::View *ui;
    ModelInfo model_info_;
    std::vector<QString> generic_tokens_ = {".", "0", "1", "2", "3", "4", "5", "6", "7", "8",
                                               "9", "+", "-", "×", "÷", "(", ")"};
    std::vector<QString> bracket_tokens_ = {"^", "√", "ln", "log", "mod", "sin", "asin",
                                            "cos", "acos", "tan", "atan"};
    std::vector<QString> special_tokens_ = {"X", "e", "π", "AC", "←"};
};

}  // namespace s21

#endif // VIEW_H
