#ifndef SMARTCALC1_QLABELHORIZONTAL_H
#define SMARTCALC1_QLABELHORIZONTAL_H

#include "view.h"

class QLabelHorizontal : public QLabel {
Q_OBJECT

public:
    explicit QLabelHorizontal(QWidget* parent = nullptr);
    ~QLabelHorizontal(){};

protected:
    void paintEvent(QPaintEvent *paint_event) override;
};

#endif //SMARTCALC1_QLABELHORIZONTAL_H
