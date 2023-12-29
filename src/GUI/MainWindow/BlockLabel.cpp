#include "GUI/MainWindow/BlockLabel.h"

BlockLabel::BlockLabel(QWidget *parent, int _x, int _y) :
    QLabel(parent), x(_x), y(_y), lbl_top(nullptr)
{
}

void BlockLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    emit signal_labelClicked(ev);
    //if (ev != nullptr && ev->button() == Qt::LeftButton)
    //{
    //}
}

void BlockLabel::wheelEvent(QWheelEvent *wv) {
    emit signal_wheelRoll(wv);
}
