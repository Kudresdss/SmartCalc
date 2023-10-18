#include "view.h"
#include "./ui_view.h"

namespace s21 {

View::View(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::View)
{
    ui->setupUi(this);
}

View::~View()
{
    delete ui_;
}

}  // namespace s21
