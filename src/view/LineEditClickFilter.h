#ifndef SMARTCALC1_LINEEDITCLICKFILTER_H
#define SMARTCALC1_LINEEDITCLICKFILTER_H

#include <QLineEdit>
#include <QObject>
#include <QEvent>

namespace s21 {

    class LineEditClickFilter : public QObject {
    Q_OBJECT

    public:
        explicit LineEditClickFilter();

    signals:

        void signalLineEdit_Input();

        void signalLineEdit_X();

    protected:
        bool eventFilter(QObject *obj, QEvent *event) override;
    };

}  // namespace s21

#endif //SMARTCALC1_LINEEDITCLICKFILTER_H
