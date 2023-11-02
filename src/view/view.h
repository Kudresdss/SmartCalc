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

public:
    explicit View(QWidget *parent = nullptr);
    ~View();

    void setTheme();
    void buildGraph(const ModelInfo& model_info);

public slots:
    void slotModelToSmart(ModelInfo& model_info);

private slots:
    void slotSmartOnClick();

signals:
    void signalSmartToModel(ViewInfo& view_info);

private:
    void connectAll();
    void setupSmartView(const ModelInfo& model_info);

    Ui::View *ui;
};

}  // namespace s21

#endif // VIEW_H
