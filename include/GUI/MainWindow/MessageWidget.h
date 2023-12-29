#ifndef __MESSAGE_WIDGET_H__
#define __MESSAGE_WIDGET_H__

#include "common.h"
#include "GUI/GUIAdapter.h"
#include <queue>
#include <QWidget>
#include <QEvent>
#include <QHoverEvent>
#include <QLabel>

class MessageWidget : public QWidget {

    Q_OBJECT;

    friend class PlayWidget;

public:
    MessageWidget(QWidget *parent, GUIAdapter *_adapter);
    MessageWidget(MessageWidget &&) = default;
    MessageWidget(const MessageWidget &) = default;
    MessageWidget &operator=(MessageWidget &&) = default;
    MessageWidget &operator=(const MessageWidget &) = default;
    ~MessageWidget();
    void pushMsg(std::string str, QColor col);
    void update(int tick);

private:
    GUIAdapter *adapter;

    struct MsgLabel {
        QLabel *lbl;
        int time;
    };

    std::deque<MsgLabel> lbl_que;
    std::queue<std::pair<std::string, QColor>> msg_que;

//public:
    //bool eventFilter(QObject *target, QEvent *ev) override;

//protected:
    //bool event(QEvent *event) override;

//public slots:
    //void slot_setTool(QMouseEvent *ev);
    //void slot_rotateTool(QWheelEvent *ev);
    
   
};


#endif
