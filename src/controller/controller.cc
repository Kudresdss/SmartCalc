#include "controller.h"

namespace s21 {

Controller::Controller(View *view, Model *model) : view_(view), model_(model) {
    view_->show();
    view_->setWindowTitle("SmartCalculator");

    connect(view_, &View::SignalSmartToModel, model_, &Model::SlotSmartToModel);
    connect(model_, &Model::SignalModelToSmart, view_, &View::SlotModelToSmart);

    connect(view_, &View::SignalCreditToModel, model_, &Model::SlotCreditToModel);
    connect(model_, &Model::SignalModelToCredit, view_, &View::SlotModelToCredit);
}

}  // namespace s21
