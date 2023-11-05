#include "view.h"
#include "./ui_view.h"

namespace s21 {

View::View(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View) {
    ui->setupUi(this);
    ui->menubar->setNativeMenuBar(false);
    connectAll();
}

View::~View() {
    delete ui;
}

void View::startSmartCalculator_SignalToModel() {
    ViewInfo view_info;

    view_info.input_string = ui->lineEdit_input->text().toStdString();
    view_info.points_density = ui->verticalSlider_graph->sliderPosition();
    view_info.x_string_value = ui->lineEdit_x->text().toStdString();
    view_info.x_max = ui->customPlot->xAxis->range().upper;
    view_info.x_min = ui->customPlot->xAxis->range().lower;
    view_info.y_max = ui->customPlot->yAxis->range().upper;
    view_info.y_min = ui->customPlot->yAxis->range().lower;
    emit signalSmartToModel(view_info);
}

void View::startSmartCalculator_SignalFromModel(const ModelInfo& model_info) {
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    ui->statusbar->showMessage(tr(model_info.error.c_str()));
    ui->label_result->setText(QString::number(model_info.result, 'f', 5));
    if (model_info.graph_mode)
        buildGraph(model_info);
    if (toggle_notation_)
        ui->label_notation->setText(QString::fromStdString(model_info_.label));
}

void View::printInLineEdit() {
    auto *button = (QPushButton *)sender();
    qsizetype current_position = ui->lineEdit_input->cursorPosition();
    qsizetype new_position;
    QString current_text = ui->lineEdit_input->text();
    QString key_pressed = button->text();
    QString input_text;
    QString text_result;

    auto func_determine_key_type = [this, key_pressed] () -> int {
        for (QString& generic_key : generic_tokens_) {
            if (key_pressed == generic_key)
                return 1;
        }
        for (QString& bracketed_key : bracket_tokens_) {
            if (key_pressed == bracketed_key)
                return 2;
        }
        for (QString& special_key : special_tokens_) {
            if (key_pressed == special_key)
                return 3;
        }
        return 0;
    };

    int key_type = func_determine_key_type();
    if (key_type == 1) {
        if (key_pressed == "×")
            input_text = "*";
        else if (key_pressed == "÷")
            input_text = "/";
        else
            input_text = key_pressed;
    }
    else if (key_type == 2) {
        input_text = key_pressed;
        input_text += "()";
    }
    else if (key_type == 3) {
        if (key_pressed == "X")
            input_text = "x";
        else if (key_pressed == "AC") {
            ui->lineEdit_input->setText("");
            return;
        }
        else if (key_pressed == "←") {
            ui->lineEdit_input->backspace();
            return;
        }
        else
            input_text = key_pressed;
    }

    if (current_position < 0) current_position = current_text.length();

    text_result = current_text.insert(current_position, input_text);
    ui->lineEdit_input->setText(text_result);
    ui->lineEdit_input->setFocus();

    if (key_type == 2)
        new_position = current_position + input_text.length() - 1;
    else
        new_position = current_position + input_text.length();
    ui->lineEdit_input->setCursorPosition(new_position);
}

void View::buildGraph(const ModelInfo& model_info) {

}

void View::connectAll() {

    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_exponentiation, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_square_root, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_log10, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_modulus, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_pi, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(printInLineEdit()));
    connect(ui->pushButton_backspace, SIGNAL(clicked()), this, SLOT(printInLineEdit()));

    connect(ui->pushButton_equals, SIGNAL(clicked()), this, SLOT(startSmartCalculator_SignalToModel()));
    connect(ui->lineEdit_input, SIGNAL(returnPressed()), this, SLOT(startSmartCalculator_SignalToModel()));
//    connect(ui->lineEdit_input, SIGNAL(textChanged(QString)), this, SLOT(startSmartCalculator_SignalFromModel()));
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(startSmartCalculator_SignalToModel()));
    connect(ui->verticalSlider_graph, SIGNAL(sliderMoved(int)), this, SLOT(startSmartCalculator_SignalToModel()));

    connect(ui->pushButton_notation, SIGNAL(clicked()), this, SLOT(toggleNotationLable()));
}

void View::toggleNotationLable() {
    toggle_notation_ = !toggle_notation_;
    if (toggle_notation_)
        ui->label_notation->setText(QString::fromStdString(model_info_.label));
    else
        ui->label_notation->setText("");
}

void View::slotModelToSmart(ModelInfo& model_info){
    model_info_ = model_info;
    startSmartCalculator_SignalFromModel(model_info);
}

void View::on_actionOpen_project_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void View::on_actionOpen_project_2_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void View::on_actionOpen_project_3_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

}  // namespace s21
