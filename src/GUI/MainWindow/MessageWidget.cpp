#include "GUI/MainWindow/MessageWidget.h"

void MessageWidget::pushMsg(std::string str, QColor col) {
    msg_que.push({str, col});

    /*auto tmp = new QLabel(this);
    tmp->setFixedWidth(300);
    tmp->setText(str.c_str());
    tmp->setWordWrap(true);
    tmp->adjustSize();
    tmp->show();*/
}

MessageWidget::MessageWidget(QWidget *parent, GUIAdapter *_adapter) :
    QWidget(parent),
    adapter(_adapter)
{

}

MessageWidget::~MessageWidget() {
}

void MessageWidget::update(int tick) {
    int lst_y;
    QLabel *msg_lbl;
    QPalette pe;
    while (!msg_que.empty()) {
        if (!lbl_que.empty()) lst_y = lbl_que.back().lbl->y() + lbl_que.back().lbl->height();
        else lst_y = 20;

        msg_lbl = new QLabel(this);
        msg_lbl->setFixedWidth(300);
        msg_lbl->setText(msg_que.front().first.c_str());
        pe.setColor(QPalette::WindowText, msg_que.front().second);
        msg_lbl->setPalette(pe);
        //msg_lbl->setColor
        msg_lbl->setWordWrap(true);
        msg_lbl->adjustSize();
        msg_lbl->move(0, lst_y + 20);
        msg_lbl->show();

        lbl_que.push_back({msg_lbl, tick});
        msg_que.pop();
    }
    while (!lbl_que.empty() && lbl_que.front().time + 200 < tick) {
        delete lbl_que.front().lbl;
        lbl_que.pop_front();
    }
    if (!lbl_que.empty()) {
        auto fir = lbl_que.front();
        fir.lbl->move(0, 20);
        for (auto iter = std::next(lbl_que.begin()); iter != lbl_que.end(); ++iter) {
            auto prev = std::prev(iter);
            lst_y = prev->lbl->y() + prev->lbl->height();
            iter->lbl->move(0, lst_y + 20);
        }
    }
    adjustSize();
}

