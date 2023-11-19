#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QButtonGroup>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QRect>
#include <QRegion>
#include <QStandardItemModel>
#include "line_edit_click_filter.h"
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

    void SetTheme();

public slots:
    void SlotModelToSmart(ModelInfo& model_info);
    void SlotModelToCredit(ModelInfo& model_info);

    //SmartCalc:

    void BuildGraph();

private slots:
    void on_actionOpen_project_triggered();
    void on_actionOpen_project_2_triggered();
    void on_actionOpen_project_3_triggered();

    //SmartCalc:

    void StartSmartCalculator_SignalToModel();
    void StartSmartCalculator_InputNotChanged_SignalToModel();
    void ToggleNotationLabel();
    void PrintInLineEdit(QAbstractButton *button_pressed);

    //CreditCalc:

    void StartCreditCalculator_SignalToModel();
    void ToggleAnnuity();
    void ToggleDifferentiated();


signals:
    void SignalSmartToModel(ViewInfo& view_info);
    void SignalCreditToModel(ViewInfo& view_info_);


private:
    void ConnectAll();

    //SmartCalc:

    void StartSmartCalculator_SignalFromModel();
    void SetGraphInfo();
    void CleanSmartLabelsAndGraphs();

    //CreditCalc:

    void StartCreditCalculator_SignalFromModel();
    void BuildCreditTable();

private:
    Ui::View *ui;
    ViewInfo view_info_;
    ModelInfo model_info_;

    //SmartCalc:

    QPen    graph_pen_;
    LineEditClickFilter *line_edit_filter_;
    bool error_ = false;
    bool toggle_notation_ = false;
    size_t line_edit_index_ = 0;
    std::vector<QString> generic_tokens_ = {".", "0", "1", "2", "3", "4", "5", "6", "7", "8",
                                            "9", "+", "-", "*", "÷", "(", ")"};
    std::vector<QString> bracket_tokens_ = {"^", "√", "ln", "log", "mod", "sin", "asin",
                                            "cos", "acos", "tan", "atan"};
    std::vector<QString> special_tokens_ = {"X", "e", "π", "AC", "←"};

    //CreditCalc:

    QStandardItemModel *credit_table_ = {nullptr};
    bool toggle_annuity_ = false;
    bool toggle_differentiated_ = false;
};

}  // namespace s21

#endif // VIEW_H
