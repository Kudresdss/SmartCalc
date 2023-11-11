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
#include "qlabelhorizontal.h"
#include "LineEditClickFilter.h"
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
    void buildGraph();

public slots:
    void slotModelToSmart(ModelInfo &model_info);

private slots:
    void startSmartCalculator_SignalToModel();
    void printInLineEdit(QAbstractButton *button_pressed);
    void toggleNotationLabel();
    void on_actionOpen_project_triggered();
    void on_actionOpen_project_2_triggered();
    void on_actionOpen_project_3_triggered();

signals:
    void signalSmartToModel(ViewInfo &view_info);

private:
    void startSmartCalculator_SignalFromModel();
    void setGraphInfo();
    void connectAll();

    bool no_error_ = true; // qt toInt() sets it to false if error occurs;
    size_t line_edit_index_ = 0;
    bool toggle_notation_ = false;
    Ui::View *ui;
    ViewInfo view_info_;
    ModelInfo model_info_;
    std::vector<QString> generic_tokens_ = {".", "0", "1", "2", "3", "4", "5", "6", "7", "8",
                                            "9", "+", "-", "×", "÷", "(", ")"};
    std::vector<QString> bracket_tokens_ = {"^", "√", "ln", "log", "mod", "sin", "asin",
                                            "cos", "acos", "tan", "atan"};
    std::vector<QString> special_tokens_ = {"X", "e", "π", "AC", "←"};
    LineEditClickFilter *line_edit_filter_;
};

}  // namespace s21

#endif // VIEW_H
