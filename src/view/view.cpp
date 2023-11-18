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
    setGraphInfo();
    ui->lineEdit_input->setFocus();
}

View::~View() {
    delete ui;
}

//SmartCalc:

void View::cleanSmartLabelsAndGraphs() {
    ui->label_result->setText("");
    ui->label_x_result->setText("");
    model_info_.label_tokens = "";
    model_info_.x_label_tokens = "";
    ui->label_notation->setText(QString::fromStdString(model_info_.label_tokens));
    ui->label_x_notation->setText(QString::fromStdString(model_info_.x_label_tokens));
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
}

void View::startSmartCalculator_SignalToModel() {
    ViewInfo new_view_info;

    new_view_info.old_main_input_str = view_info_.main_input;
    new_view_info.old_x_input_str = view_info_.x_input;
    view_info_ = new_view_info;
    ui->statusbar->showMessage("");

    view_info_.main_input = ui->lineEdit_input->text().toStdString();
    if (!view_info_.main_input.empty()) {
        view_info_.main_input_exists = true;
        view_info_.x_in_main_input = ui->lineEdit_input->text().contains("x", Qt::CaseSensitive);
    }
    view_info_.x_input = ui->lineEdit_x->text().toStdString();
    if (!view_info_.x_input.empty()) {
        view_info_.x_input_exists = true;
        if (ui->lineEdit_x->text().contains("x", Qt::CaseSensitive)) {
            ui->statusbar->showMessage("Invalid expression: can't calculate x value\n"
                                            "recursively out of itself");
            ui->label_x_result->setText("nan");
            error_ = false;
            cleanSmartLabelsAndGraphs();
            return;
        }
    }
    if (!view_info_.main_input_exists) {
        ui->statusbar->showMessage("Main input is empty");
        error_ = false;
        cleanSmartLabelsAndGraphs();
        return;
    }
    if (view_info_.x_in_main_input && !view_info_.x_input_exists) {
        ui->statusbar->showMessage("X in main input, but x input is empty");
        error_ = false;
        cleanSmartLabelsAndGraphs();
        return;
    }

    if (view_info_.main_input == view_info_.old_main_input_str &&
        view_info_.x_input == view_info_.old_x_input_str)
        return;

    cleanSmartLabelsAndGraphs();
    setGraphInfo();
    if (!error_)
        emit signalSmartToModel(view_info_);
    error_ = false;
}

void View::startSmartCalculator_InputNotChanged_SignalToModel() {
    ui->statusbar->showMessage("");
    cleanSmartLabelsAndGraphs();
    setGraphInfo();

    if (!error_)
            emit signalSmartToModel(view_info_);
    error_ = false;
}

void View::startSmartCalculator_SignalFromModel() {
    error_ = false;
    if (!model_info_.error.empty()) {
        ui->statusbar->showMessage(tr(model_info_.error.c_str()));
        return;
    }

    if (!view_info_.x_input_exists) {
        model_info_.x_label_tokens = "";
        ui->label_x_notation->setText(QString::fromStdString(model_info_.x_label_tokens));
    }
    ui->label_result->setText(QString::number(model_info_.result, 'd', 7));
    if (view_info_.x_input_exists)
        ui->label_x_result->setText(QString::number(model_info_.x_input_value, 'd', 7));
    if (toggle_notation_) {
        ui->label_notation->setText(QString::fromStdString(model_info_.label_tokens));
        if (view_info_.x_input_exists)
            ui->label_x_notation->setText(QString::fromStdString(model_info_.x_label_tokens));
    }
    if (model_info_.graph_mode)
        buildGraph();
}

void View::setGraphInfo() {
    bool no_error = true;

    view_info_.points_density = ui->verticalSlider_graph->sliderPosition();
    view_info_.x_max = ui->lineEdit_x_max->text().toInt(&no_error);
    if (no_error) view_info_.x_min = ui->lineEdit_x_min->text().toInt(&no_error);
    if (no_error) view_info_.y_max = ui->lineEdit_y_max->text().toInt(&no_error);
    if (no_error) view_info_.y_min = ui->lineEdit_y_min->text().toInt(&no_error);
    error_ = !no_error;
    if (!error_) {
        ui->customPlot->xAxis->setRange(view_info_.x_min, view_info_.x_max);
        ui->customPlot->yAxis->setRange(view_info_.y_min, view_info_.y_max);
        ui->customPlot->replot();
    }
    else {
        ui->statusbar->showMessage(QString("Wrong min/max axis input: must be int value"));
        cleanSmartLabelsAndGraphs();
    }
}

void View::buildGraph() {
    size_t max_size = model_info_.x_coord.size();

    ui->customPlot->xAxis->setRange(view_info_.x_min, view_info_.x_max);
    ui->customPlot->yAxis->setRange(view_info_.y_min, view_info_.y_max);
    ui->customPlot->xAxis->scaleRange(ui->horizontalSlider_graph_x->sliderPosition());
    ui->customPlot->yAxis->scaleRange(ui->horizontalSlider_graph_y->sliderPosition());
    for (size_t i = 0; i < max_size; ++i) {
        QVector<double> x, y;
        for (size_t j = 0; j < model_info_.x_coord[i].size(); ++j) {
            x.push_back(model_info_.x_coord[i][j]);
            y.push_back(model_info_.y_coord[i][j]);
        }
        if ((!(x.empty() || y.empty())) && model_info_.error.empty()) {
            ui->customPlot->addGraph();
            ui->customPlot->graph(i)->addData(x, y);
            ui->customPlot->graph(i)->setPen(graph_pen_);
            ui->customPlot->replot();
        }
    }
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
        if (key_pressed == "÷")
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

//CreditCalc:

void View::startCreditCalculator_SignalToModel() {
    ViewInfo new_view_info;
    bool no_error_ = true;

    if (credit_table_) {
        delete credit_table_;
        credit_table_ = nullptr;
    }

    view_info_ = new_view_info;
    ui->statusbar->showMessage("");
    view_info_.annuity = toggle_annuity_;
    view_info_.differentiated = toggle_differentiated_;

    if (!toggle_annuity_ && !toggle_differentiated_) {
        ui->statusbar->showMessage("Choose repayment type");
        return;
    }

    if (ui->lineEdit_loan_amount->text().isEmpty()) {
        ui->statusbar->showMessage("Loan amount is empty");
        return;
    }
    else {
        view_info_.loan_amount = ui->lineEdit_loan_amount->text().toULong(&no_error_);
        if (!no_error_ || view_info_.loan_amount > 1000000000000) {
            ui->statusbar->showMessage("Incorrect loan amount value");
            return;
        }
    }
    if (ui->lineEdit_loan_term->text().isEmpty()) {
        ui->statusbar->showMessage("Loan term is empty");
        return;
    }
    else {
        view_info_.loan_term = ui->lineEdit_loan_term->text().toUInt(&no_error_);
        if (!no_error_ || (view_info_.loan_term < 1 || view_info_.loan_term > 1000)) {
            ui->statusbar->showMessage("Incorrect loan term value");
            return;
        }
    }
    if (ui->lineEdit_interest_rate->text().isEmpty()) {
        ui->statusbar->showMessage("Interest rate is empty");
        return;
    }
    else {
        view_info_.interest_rate = ui->lineEdit_interest_rate->text().toUInt(&no_error_);
        if (!no_error_ || (view_info_.interest_rate <= 0 || view_info_.interest_rate > 100)) {
            ui->statusbar->showMessage("Incorrect interest rate value");
            return;
        }
    }

    if (!error_)
            emit signalCreditToModel(view_info_);
    error_ = false;
}

void View::startCreditCalculator_SignalFromModel() {
    ui->label_total_interest_result->setText(QString::number(model_info_.total_interest, 'd', 2));
    ui->label_total_payment_result->setText(QString::number(model_info_.total_payment, 'd', 2));
    buildCreditTable();
}

void View::buildCreditTable() {
    credit_table_ = new QStandardItemModel(view_info_.loan_term, 5, this);
    credit_table_->setHorizontalHeaderLabels(QStringList()  << "Beginning balance" << "Monthly payment" <<
                                                            "Interest" << "Principal" << "Ending balance");
    ui->tableView_payment->setModel(credit_table_);
    ui->tableView_payment->setColumnWidth(0, 130);
    ui->tableView_payment->setColumnWidth(1, 125);
    ui->tableView_payment->setColumnWidth(2, 125);
    ui->tableView_payment->setColumnWidth(3, 125);
    ui->tableView_payment->setColumnWidth(4, 130);
    QModelIndex index[5];

    for (int i = 0; i < view_info_.loan_term; ++i) {
        index[0] = credit_table_->index(i, 0);
        credit_table_->setData(index[0], QString::number(model_info_.credit_table[i][0], 'd', 2), 0);

        index[1] = credit_table_->index(i, 1);
        credit_table_->setData(index[1], QString::number(model_info_.credit_table[i][1], 'd', 2), 0);

        index[2] = credit_table_->index(i, 2);
        credit_table_->setData(index[2], QString::number(model_info_.credit_table[i][2], 'd', 2), 0);

        index[3] = credit_table_->index(i, 3);
        credit_table_->setData(index[3], QString::number(model_info_.credit_table[i][3], 'd', 2), 0);

        index[4] = credit_table_->index(i, 4);
        credit_table_->setData(index[4], QString::number(model_info_.credit_table[i][4], 'd', 2), 0);
    }
}

//General or purely visual style methods:

void View::setTheme() {
    int font_id = QFontDatabase::addApplicationFont(":/fonts/LucidaGrande.ttc");
    QString family = QFontDatabase::applicationFontFamilies(font_id).at(0);
    QFont monospace(family);

    graph_pen_.setColor(QColor(QColorConstants::Black));
    graph_pen_.setStyle(Qt::SolidLine);
    graph_pen_.setCapStyle(Qt::RoundCap);
    graph_pen_.setJoinStyle(Qt::RoundJoin);
    graph_pen_.setWidth(2);

    ui->customPlot->setInteraction(QCP::iRangeZoom, true);
    ui->customPlot->setInteraction(QCP::iRangeDrag, true);

    ui->gridLayout_loan->setAlignment(ui->pushButton_annuity, Qt::AlignHCenter);
    ui->gridLayout_loan->setAlignment(ui->pushButton_differentiated, Qt::AlignHCenter);
    ui->gridLayout_loan->setAlignment(ui->pushButton_calculate, Qt::AlignHCenter);
}

void View::connectAll() {
    connect(ui->buttonGroup_print, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(printInLineEdit(QAbstractButton*)));

    connect(ui->pushButton_equals, SIGNAL(clicked()), this, SLOT(startSmartCalculator_SignalToModel()));
    connect(ui->lineEdit_input, SIGNAL(returnPressed()), this, SLOT(startSmartCalculator_SignalToModel()));

    connect(line_edit_filter_, &LineEditClickFilter::signalLineEdit_Input, this, [this]() {line_edit_index_=1;});
    connect(line_edit_filter_, &LineEditClickFilter::signalLineEdit_X, this, [this]() {line_edit_index_=2;});

    connect(ui->lineEdit_input, &QLineEdit::textChanged, this, [this]() {line_edit_index_=1;});
    connect(ui->lineEdit_x, &QLineEdit::textChanged, this, [this]() {line_edit_index_=2;});

    connect(ui->verticalSlider_graph, SIGNAL(sliderMoved(int)), this, SLOT(startSmartCalculator_InputNotChanged_SignalToModel()));
    connect(ui->lineEdit_x_min, SIGNAL(editingFinished()), this, SLOT(startSmartCalculator_InputNotChanged_SignalToModel()));
    connect(ui->lineEdit_x_max, SIGNAL(editingFinished()), this, SLOT(startSmartCalculator_InputNotChanged_SignalToModel()));
    connect(ui->lineEdit_y_min, SIGNAL(editingFinished()), this, SLOT(startSmartCalculator_InputNotChanged_SignalToModel()));
    connect(ui->lineEdit_y_max, SIGNAL(editingFinished()), this, SLOT(startSmartCalculator_InputNotChanged_SignalToModel()));
    connect(ui->horizontalSlider_graph_x, SIGNAL(sliderMoved(int)), this, SLOT(buildGraph()));
    connect(ui->horizontalSlider_graph_y, SIGNAL(sliderMoved(int)), this, SLOT(buildGraph()));

    connect(ui->pushButton_calculate, SIGNAL(clicked()), this, SLOT(startCreditCalculator_SignalToModel()));
    connect(ui->pushButton_notation, SIGNAL(clicked()), this, SLOT(toggleNotationLabel()));
    connect(ui->pushButton_annuity, SIGNAL(clicked()), this, SLOT(toggleAnnuity()));
    connect(ui->pushButton_differentiated, SIGNAL(clicked()), this, SLOT(toggleDifferentiated()));

}

void View::toggleNotationLabel() {
    toggle_notation_ = !toggle_notation_;
    if (toggle_notation_) {
        ui->label_notation->setText(QString::fromStdString(model_info_.label_tokens));
        ui->label_x_notation->setText(QString::fromStdString(model_info_.x_label_tokens));
        ui->pushButton_notation->setStyleSheet("QPushButton {\n"
                                               "background-color: rgb(13, 170, 170);\n"
                                               "border-bottom: 3px solid rgb(15, 90, 110);\n"
                                               "border-left: 2px solid rgb(15, 135, 165);\n"
                                               "border-radius: 4px;}\n"
                                               "QPushButton:hover {\n"
                                               "background-color: rgb(11, 150, 150);\n"
                                               "border-bottom: 3px solid rgb(12, 70, 90);\n"
                                               "border-left: 2px solid rgb(12, 115, 145);\n"
                                               "border-radius: 4px;}");
    }
    else {
        ui->label_notation->setText("");
        ui->label_x_notation->setText("");
        ui->pushButton_notation->setStyleSheet("QPushButton:hover {\n"
                                               "background-color: rgb(13, 170, 170);\n"
                                               "border-bottom: 3px solid rgb(15, 90, 110);\n"
                                               "border-left: 2px solid rgb(15, 135, 165);\n"
                                               "border-radius: 4px;}");
    }
}

void View::toggleAnnuity() {
    toggle_annuity_ = !toggle_annuity_;
    if (toggle_annuity_) {
        if (toggle_differentiated_)
            toggleDifferentiated();
        ui->pushButton_annuity->setStyleSheet("QPushButton {\n"
                                              "background-color: rgb(15, 195, 227);\n"
                                              "border-bottom: 3px solid rgb(15, 110, 130);\n"
                                              "border-left: 2px solid rgb(15, 150, 180);\n"
                                              "color: rgb(255, 255, 255);\n"
                                              "border-radius: 4px;}\n"
                                              "QPushButton:hover {\n"
                                              "background-color: rgb(13, 170, 200);\n"
                                              "border-bottom: 3px solid rgb(15, 90, 110);\n"
                                              "border-left: 2px solid rgb(15, 135, 165);\n"
                                              "color: rgb(255, 255, 255);\n"
                                              "border-radius: 4px;}");
    }
    else {
        ui->pushButton_annuity->setStyleSheet("QPushButton:hover {\n"
                                              "background-color: rgb(15, 195, 227);\n"
                                              "border-bottom: 3px solid rgb(15, 110, 130);\n"
                                              "border-left: 2px solid rgb(15, 150, 180);\n"
                                              "color: rgb(255, 255, 255);\n"
                                              "border-radius: 4px;}");
    }
}

void View::toggleDifferentiated() {
    toggle_differentiated_ = !toggle_differentiated_;
    if (toggle_differentiated_) {
        if (toggle_annuity_)
            toggleAnnuity();
        ui->pushButton_differentiated->setStyleSheet("QPushButton {\n"
                                               "background-color: rgb(15, 195, 227);\n"
                                               "border-bottom: 3px solid rgb(15, 110, 130);\n"
                                               "border-left: 2px solid rgb(15, 150, 180);\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border-radius: 4px;}\n"
                                               "QPushButton:hover {\n"
                                               "background-color: rgb(13, 170, 200);\n"
                                               "border-bottom: 3px solid rgb(15, 90, 110);\n"
                                               "border-left: 2px solid rgb(15, 135, 165);\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border-radius: 4px;}");
    }
    else {
        ui->pushButton_differentiated->setStyleSheet("QPushButton:hover {\n"
                                               "background-color: rgb(15, 195, 227);\n"
                                               "border-bottom: 3px solid rgb(15, 110, 130);\n"
                                               "border-left: 2px solid rgb(15, 150, 180);\n"
                                               "color: rgb(255, 255, 255);\n"
                                               "border-radius: 4px;}");
    }
}

void View::slotModelToSmart(ModelInfo& model_info){
    model_info_ = model_info;
    startSmartCalculator_SignalFromModel();
}

void View::slotModelToCredit(ModelInfo& model_info) {
    model_info_ = model_info;
    startCreditCalculator_SignalFromModel();
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
