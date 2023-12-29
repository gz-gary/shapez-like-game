#ifndef __TOOLBAR_WIDGET_H__
#define __TOOLBAR_WIDGET_H__

#include "common.h"
#include "GUI/MainWindow/BlockLabel.h"
#include <QWidget>
#include <QPixmap>
#include <QLabel>

class GUIAdapter;

class ToolbarWidget : public QWidget {

    Q_OBJECT;

    friend class GUIAdapter;
    friend class GUI;

public:
    ToolbarWidget(QWidget *parent, GUIAdapter *_adapter);
    ToolbarWidget(ToolbarWidget &&) = default;
    ToolbarWidget(const ToolbarWidget &) = default;
    ToolbarWidget &operator=(ToolbarWidget &&) = default;
    ToolbarWidget &operator=(const ToolbarWidget &) = default;
    ~ToolbarWidget();

private:
    GUIAdapter *adapter;
    //std::stack<BlockLabel*> lbl_stk[MAXN][MAXN];
    BlockLabel *lbl_tool[MAXN];
    QLabel *lbl_lvup;
    QLabel *lbl_redspot;
    //QLabel *lbl_tool[MAXN];
    int w, h;

public slots:
    void slot_selectItem(int type);
    
};


#endif
