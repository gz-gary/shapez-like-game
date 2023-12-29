#ifndef __MAIN_WIDGET_H__
#define __MAIN_WIDGET_H__

#include "common.h"
#include "GUI/GUIAdapter.h"
#include "GUI/MainWindow/BlockLabel.h"
#include <set>
#include <stack>
#include <QWidget>
#include <QEvent>
#include <QHoverEvent>
#include <QLabel>

class MainWidget : public QWidget {

    Q_OBJECT;

    friend class PlayWidget;

public:
    MainWidget(QWidget *parent, GUIAdapter *_adapter);
    MainWidget(MainWidget &&) = default;
    MainWidget(const MainWidget &) = default;
    MainWidget &operator=(MainWidget &&) = default;
    MainWidget &operator=(const MainWidget &) = default;
    ~MainWidget();

private:
    GUIAdapter *adapter;
    QPixmap *pixmap[MAXN];
    BlockLabel *float_map;

public:
    bool eventFilter(QObject *target, QEvent *ev) override;

protected:
    bool event(QEvent *event) override;

public slots:
    void slot_setTool(QMouseEvent *ev);
    void slot_rotateTool(QWheelEvent *ev);
    
   
};

#endif
