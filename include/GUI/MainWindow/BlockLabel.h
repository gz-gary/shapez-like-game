#ifndef __BLOCK_LABEL_H__
#define __BLOCK_LABEL_H__

#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>

class BlockLabel : public QLabel
{
    Q_OBJECT;

    friend class PlayWidget;
    friend class GUIAdapter;
    friend class GUI;

public:
    explicit BlockLabel(QWidget *parent, int _x, int _y);

private:
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *wv) override;
    int x, y;
    int type, dir;
    QLabel *lbl_top;

signals:
    void signal_labelClicked(QMouseEvent *ev);
    void signal_wheelRoll(QWheelEvent *wv);

};

#endif
