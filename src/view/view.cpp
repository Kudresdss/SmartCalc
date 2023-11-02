#include "view.h"
#include "./ui_view.h"

namespace s21 {

View::View(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View) {
    ui->setupUi(this);
    setTheme();
    connectAll();
}

void View::setupSmartView(const ModelInfo& model_info) {
//    ui->widget->clearGraphs();
//    ui->widget->replot();
//    ui->label->setText(QString::fromStdString(model_info.label));
//    ui->label_result->setText(QString::number(model_info.result, 'f', 5));
    if (model_info.graph_mode)
        buildGraph(model_info);
}

void View::setTheme() {

}

void View::buildGraph(const ModelInfo& model_info) {

}

void View::connectAll() {

}

void View::slotModelToSmart(ModelInfo& model_info){
    setupSmartView(model_info);
}

void View::slotSmartOnClick() {

}

View::~View() {
    delete ui;
}

}  // namespace s21
