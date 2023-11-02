#include "model/model.h"
#include "view/view.h"
#include "controller/controller.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication App(argc, argv);
    s21::Model* Model = &s21::Model::getInstance();
    s21::View View;
    s21::Controller Controller(&View, Model);

    return App.exec();
}
