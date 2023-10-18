#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QEvent>
#include <QObject>
#include <QPalette>
#include <QWidget>
#include "../structures.h"

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
    Q_OBJECT

signals:

public:
    View(QWidget *parent = nullptr);
    ~View();

private:
    Ui::View *ui_;

private slots:
};

}  // namespace s21

#endif // VIEW_H
