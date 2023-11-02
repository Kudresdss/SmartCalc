#include "controller.h"

namespace s21 {

Controller::Controller(View *View, Model *Model) : View_(View), Model_(Model) {
    View_->show();
    View_->setWindowTitle("SmartCalculator");

    connect(View_, &View::signalSmartToModel, Model_, &s21::Model::slotSmartToModel);
    connect(Model_, &s21::Model::signalModelToSmart, View_, &View::slotModelToSmart);
}

}  // namespace s21
