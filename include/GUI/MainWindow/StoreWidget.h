#ifndef __STORE_WIDGET_H__
#define __STORE_WIDGET_H__

#include "common.h"
#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include "GUI/MainWindow/BlockLabel.h"

class GUIAdapter;

class StoreWidget : public QWidget {

    Q_OBJECT;

    friend class GUIAdapter;
    friend class GUI;

public:
    StoreWidget(QWidget *parent, GUIAdapter *_adapter);
    StoreWidget(StoreWidget &&) = default;
    StoreWidget(const StoreWidget &) = default;
    StoreWidget &operator=(StoreWidget &&) = default;
    StoreWidget &operator=(const StoreWidget &) = default;
    ~StoreWidget();
    QPixmap makeFrame();

private:
    GUIAdapter *adapter;
    QLabel *lbl_bkg;
    QLabel *lbl_money_icon, *lbl_money_text;
    QLabel *lbl_obj_icon[4], *lbl_obj_text[4];
    QLabel *lbl_confirm, *lbl_cancel;
    QLabel *lbl_item_money;
    QLabel *lbl_item_enlarge;
    QLabel *lbl_item_mine;
    QLabel *lbl_item_expand;
    QLabel *lbl_item_rate;
    QLabel *lbl_intro;
    QLabel *lbl_rate;
    QLabel *lbl_frame[4][2];
    int selected_item;
    //std::stack<BlockLabel*> lbl_stk[MAXN][MAXN];
    //BlockLabel *lbl_mat[MAXN][MAXN];
    //BlockLabel *lbl_bkg[MAXN][MAXN];
    //int w, h;
protected:
    bool eventFilter(QObject *target, QEvent *ev) override;
    //void mouseReleaseEvent(QMouseEvent *ev) override;
    //bool event(QEvent *event) override;
    //bool eventFilter(QObject *target, QEvent *ev) override;
};

#endif // !__PLAY_WIDGET__
