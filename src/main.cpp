#include "view/view.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    s21::Model model;
    s21::View view;
    s21::Controller controller(&model, &view);
//    view.show();
    return a.exec();
}
