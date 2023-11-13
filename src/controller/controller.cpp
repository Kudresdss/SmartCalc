#include "controller.h"

namespace s21 {

Controller::Controller(View *View, Model *Model) : View_(View), Model_(Model) {
    View_->show();
    View_->setWindowTitle("SmartCalculator");

    connect(View_, &View::signalSmartToModel, Model_, &Model::slotSmartToModel);
    connect(Model_, &Model::signalModelToSmart, View_, &View::slotModelToSmart);

    connect(View_, &View::signalCreditToModel, Model_, &Model::slotCreditToModel);
    connect(Model_, &Model::signalModelToCredit, View_, &View::slotModelToCredit);
}

}  // namespace s21
