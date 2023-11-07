#include "view.h"
#include "./ui_view.h"

namespace s21 {

View::View(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View) {
    ui->setupUi(this);
    ui->menubar->setNativeMenuBar(false);
    setlocale(LC_NUMERIC, "C");
    setTheme();

    line_edit_filter_ = new LineEditClickFilter();
    ui->lineEdit_input->installEventFilter(line_edit_filter_);
    ui->lineEdit_x->installEventFilter(line_edit_filter_);

    connectAll();
    ui->lineEdit_input->setFocus();
}

View::~View() {
    delete ui;
}

void View::setTheme() {
    int font_id = QFontDatabase::addApplicationFont(":/fonts/LucidaGrande.ttc");
    QString family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    QFont monospace(family);
}

void View::startSmartCalculator_SignalToModel() {
    ViewInfo view_info;

    view_info.input_string = ui->lineEdit_input->text().toStdString();
    view_info.points_density = ui->verticalSlider_graph->sliderPosition();
    view_info.x_string_value = ui->lineEdit_x->text().toStdString();
    view_info.x_max = ui->lineEdit_x_max->text().toDouble();
    view_info.x_min = ui->lineEdit_x_min->text().toDouble();
    view_info.y_max = ui->lineEdit_y_max->text().toDouble();
    view_info.y_min = ui->lineEdit_x_min->text().toDouble();
    emit signalSmartToModel(view_info);
}

void View::startSmartCalculator_SignalFromModel() {
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
    ui->statusbar->showMessage(tr(model_info_.error.c_str()));
    ui->label_result->setText(QString::number(model_info_.result, 'f', 5));
    if (model_info_.graph_mode)
        buildGraph();
    if (toggle_notation_)
        ui->label_notation->setText(QString::fromStdString(model_info_.label));
}

void View::printInLineEdit(QAbstractButton* button_pressed) {
    auto button = (QPushButton *)button_pressed;
    qsizetype new_position;
    QLineEdit *line_edit;
    QString key_pressed = button->text();
    QString input_text;
    QString text_result;

    if (line_edit_index_ == 1)
        line_edit = ui->lineEdit_input;
    else if (line_edit_index_ == 2)
        line_edit = ui->lineEdit_x;
    else
        line_edit = ui->lineEdit_input;

    qsizetype current_position = line_edit->cursorPosition();
    QString current_text = line_edit->text();

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
            line_edit->setText("");
            return;
        }
        else if (key_pressed == "←") {
            line_edit->backspace();
            return;
        }
        else
            input_text = key_pressed;
    }

    if (current_position < 0) current_position = current_text.length();

    text_result = current_text.insert(current_position, input_text);
    line_edit->setText(text_result);
    line_edit->setFocus();

    if (key_type == 2)
        new_position = current_position + input_text.length() - 1;
    else
        new_position = current_position + input_text.length();
    line_edit->setCursorPosition(new_position);
}

void View::buildGraph() {
    QPen pen;
    size_t max_size = model_info_.x_coord.size();

    for (size_t i = 0; i < max_size; ++i) {
        QVector<double> x, y;
        for (size_t j = 0; j < model_info_.x_coord[i].size(); ++j) {
            x.push_back(model_info_.x_coord[i][j]);
            y.push_back(model_info_.y_coord[i][j]);
        }
        if ((!(x.empty() || y.empty())) && model_info_.error.empty()) {
            pen.setColor(QColor(QColorConstants::Black));
            pen.setWidth(2);
            ui->customPlot->addGraph();
            ui->customPlot->graph(i)->addData(x, y);
            ui->customPlot->graph(i)->setPen(pen);
            ui->customPlot->replot();
        }
    }
}

void View::connectAll() {
    connect(ui->buttonGroup_print, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(printInLineEdit(QAbstractButton*)));

    connect(ui->pushButton_equals, SIGNAL(clicked()), this, SLOT(startSmartCalculator_SignalToModel()));
    connect(ui->lineEdit_input, SIGNAL(returnPressed()), this, SLOT(startSmartCalculator_SignalToModel()));

    connect(line_edit_filter_, &LineEditClickFilter::signalLineEdit_Input, this, [this]() {line_edit_index_=1;});
    connect(line_edit_filter_, &LineEditClickFilter::signalLineEdit_X, this, [this]() {line_edit_index_=2;});

    connect(ui->lineEdit_input, &QLineEdit::textChanged, this, [this]() {line_edit_index_=1;});
    connect(ui->lineEdit_x, &QLineEdit::textChanged, this, [this]() {line_edit_index_=2;});

    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(startSmartCalculator_SignalToModel()));
    connect(ui->verticalSlider_graph, SIGNAL(sliderMoved(int)), this, SLOT(startSmartCalculator_SignalToModel()));

    connect(ui->pushButton_notation, SIGNAL(clicked()), this, SLOT(toggleNotationLable()));
}

void View::toggleNotationLable() {
    toggle_notation_ = !toggle_notation_;
    if (toggle_notation_) {
        ui->label_notation->setText(QString::fromStdString(model_info_.label));
        ui->pushButton_notation->setStyleSheet("background-color: rgb(13, 170, 170);"
                                               "border-bottom: 3px solid rgb(15, 90, 110);"
                                               "border-left: 2px solid rgb(15, 135, 165);"
                                               "border-radius: 4px;");
    }
    else {
        ui->label_notation->setText("");
        ui->pushButton_notation->setStyleSheet("background-color: rgb(201, 201, 201);"
                                               "border-bottom: 3px solid rgb(128, 128, 128);"
                                               "border-left: 2px solid rgb(180, 180, 180);"
                                               "border-radius: 4px;");
    }
}

void View::slotModelToSmart(ModelInfo& model_info){
    model_info_ = model_info;
    startSmartCalculator_SignalFromModel();
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
