#include "controller.h"

namespace s21 {

Controller::Controller(View *view, s21::Model *model) : model_(model), view_(view) {
    view_->show();
    view_->setWindowTitle("SmartCalculator");

    connect(view_, &MainView::VMsmart, model_, &s21::Model::VMsmart);
    connect(model_, &s21::Model::MVsmart, view_, &MainView::MVsmart);
}

}  // namespace s21