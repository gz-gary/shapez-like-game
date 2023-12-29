#ifndef __MENU_WIDGET_H__
#define __MENU_WIDGET_H__

#include "common.h"
#include <QWidget>
#include <QPixmap>
#include <stack>
#include "GUI/MainWindow/BlockLabel.h"

class GUIAdapter;

class MenuWidget : public QWidget {

    Q_OBJECT;

    friend class GUIAdapter;
    friend class GUI;

public:
    MenuWidget(QWidget *parent, GUIAdapter *_adapter);
    MenuWidget(MenuWidget &&) = default;
    MenuWidget(const MenuWidget &) = default;
    MenuWidget &operator=(MenuWidget &&) = default;
    MenuWidget &operator=(const MenuWidget &) = default;
    ~MenuWidget();
    void toggle();

signals:
    void signal_quit();

private:
    GUIAdapter *adapter;
    //std::stack<BlockLabel*> lbl_stk[MAXN][MAXN];
    //BlockLabel *lbl_mat[MAXN][MAXN];
    //BlockLabel *lbl_bkg[MAXN][MAXN];
    //int w, h;
    int toggled;
    QLabel *lbl_menu_icon, *lbl_menu_text;
    QLabel *lbl_store_icon, *lbl_store_text;
    QLabel *lbl_save_icon, *lbl_save_text;
    QLabel *lbl_load_icon, *lbl_load_text;
    QLabel *lbl_quit_icon, *lbl_quit_text;
    QLabel *lbl_bkg;
    QLabel *lbl_bkg1;

protected:
    bool eventFilter(QObject *target, QEvent *ev) override;
    bool event(QEvent *event) override;
    //void mouseReleaseEvent(QMouseEvent *ev) override;
    //bool event(QEvent *event) override;
    //bool eventFilter(QObject *target, QEvent *ev) override;
};

#endif // !__PLAY_WIDGET__
