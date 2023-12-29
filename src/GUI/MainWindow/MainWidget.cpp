#include "GUI/MainWindow/MainWidget.h"
#include "GUI/GUIAdapter.h"
#include "GUI/GUI.h"
#include <QMouseEvent>

MainWidget::MainWidget(QWidget *parent, GUIAdapter *_adapter) :
    QWidget(parent),
    adapter(_adapter),
    float_map(nullptr)
{
    pixmap[1] = adapter->gui->trashbin;
    pixmap[2] = adapter->gui->belt_forward[0][0];
    pixmap[3] = adapter->gui->belt_left[0][0];
    pixmap[4] = adapter->gui->belt_right[0][0];
    pixmap[5] = adapter->gui->com_cutter[0];
    pixmap[6] = adapter->gui->miner[0];
    pixmap[7] = adapter->gui->remove;
    pixmap[8] = adapter->gui->upgrade;
    pixmap[9] = adapter->gui->virt_belt_forward[0];
    pixmap[10] = adapter->gui->rotater[0];
    pixmap[11] = adapter->gui->rotater_ccw[0];
    //pixmap[9] = adapter->gui->red_spot;
    float_map = new BlockLabel(this, 0, 0);
    float_map->installEventFilter(this);
    //float_map->setCursor(Qt::SizeAllCursor);
    connect(float_map, SIGNAL(signal_labelClicked(QMouseEvent*)),
            this, SLOT(slot_setTool(QMouseEvent*)));
    connect(float_map, SIGNAL(signal_wheelRoll(QWheelEvent*)),
            this, SLOT(slot_rotateTool(QWheelEvent*)));
}

MainWidget::~MainWidget() {
}

bool MainWidget::event(QEvent *e) {
    if (adapter->gui->mouse_status == 0 && float_map != nullptr)
        float_map->hide();
    if(QEvent::HoverMove == e->type()) {
        QHoverEvent *hoverEvent = static_cast<QHoverEvent*>(e);
        auto mouse_pos = hoverEvent->pos();
        if (adapter->gui->mouse_status) {
            if (adapter->gui->mouse_status == -1) {
                auto now_pos = adapter->gui->pre_pos + mouse_pos - adapter->gui->mouse_pos;
                if (now_pos.x() > 0) now_pos.setX(0);
                if (now_pos.y() > 0) now_pos.setY(0);
                auto wid = adapter->gui->play_widget;
                if (now_pos.x() + wid->width() < width()) now_pos.setX(width() - wid->width());
                if (now_pos.y() + wid->height() < height()) now_pos.setY(height() - wid->height());
                wid->move(now_pos);
            } else {
                if (float_map->isHidden()) {
                    float_map->setPixmap(*pixmap[adapter->gui->mouse_status]);
                    float_map->adjustSize();
                    float_map->show();
                    float_map->raise();
                }
                if (adapter->gui->mouse_status == 5) {
                    switch (adapter->gui->dir_device % 4) {
                    case 0:
                        float_map->move(mouse_pos.x() - 25, mouse_pos.y() - 25);
                        break;
                    case 1:
                        float_map->move(mouse_pos.x() - 25, mouse_pos.y() - 75);
                        break;
                    case 2:
                        float_map->move(mouse_pos.x() - 75, mouse_pos.y() - 25);
                        break;
                    case 3:
                        float_map->move(mouse_pos.x() - 25, mouse_pos.y() - 25);
                        break;
                    }
                } else
                    float_map->move(mouse_pos.x() - 25, mouse_pos.y() - 25);

                if (adapter->gui->drag_pipe) {
                    auto abs_pos = mouse_pos - adapter->gui->play_widget->pos();
                    int i = abs_pos.x() / 50 + 1, j = abs_pos.y() / 50 + 1;
                    adapter->gui->play_widget->updateStk(std::make_pair(i, j));
                }
                if (adapter->gui->drag_tool) {
                    auto abs_pos = mouse_pos - adapter->gui->play_widget->pos();
                    int i = abs_pos.x() / 50 + 1, j = abs_pos.y() / 50 + 1;
                    adapter->GUI_setDevice(i, j, 7, 0); // remove
                    //adapter->gui->play_widget->updateStk(std::make_pair(i, j));
                }
            }
        }
    }
    return QWidget::event(e);
}

void MainWidget::slot_setTool(QMouseEvent *ev) {
    //printf("release\n");
    if (ev->button() == Qt::LeftButton) {
        if (adapter->gui->mouse_status > 0) {
            auto pos = ev->pos();
            auto off1 = float_map->pos();
            auto off2 = adapter->gui->play_widget->pos();
            auto tmp = off1 + pos - off2;
            adapter->GUI_setDevice(tmp.x() / 50 + 1, tmp.y() / 50 + 1, adapter->gui->mouse_status, adapter->gui->dir_device);
        }
        adapter->gui->play_widget->clearVirt();
        adapter->gui->mouse_status = 0;
        adapter->gui->drag_pipe = 0;
        adapter->gui->drag_tool = 0;
        float_map->hide();
    } else if (ev->button() == Qt::RightButton) {
        adapter->gui->play_widget->clearVirt();
        adapter->gui->mouse_status = 0;
        adapter->gui->drag_pipe = 0;
        adapter->gui->drag_tool = 0;
        float_map->hide();
    } else if (ev->button() == Qt::MiddleButton) {
        if (adapter->gui->mouse_status == 10) {
            adapter->gui->mouse_status = 11;
            float_map->setPixmap(*adapter->gui->rotater_ccw[adapter->gui->dir_device % 4]);
        } else {
            adapter->gui->mouse_status = 10;
            float_map->setPixmap(*adapter->gui->rotater[adapter->gui->dir_device % 4]);
        }
    }
}

void MainWidget::slot_rotateTool(QWheelEvent *wv) {
    auto d = wv->angleDelta();
    auto tmp = float_map->pos() + wv->position();
    if (d.y() < 0) adapter->gui->dir_device += 3;
    else adapter->gui->dir_device += 1;

    switch(adapter->gui->mouse_status) {
    case 2:
        float_map->setPixmap(*adapter->gui->belt_forward[adapter->gui->dir_device % 4][0]);
        float_map->adjustSize();
        //float_map->show();
        //float_map->raise();
        break;
    case 3:
        float_map->setPixmap(*adapter->gui->belt_left[adapter->gui->dir_device % 4][0]);
        float_map->adjustSize();
        //float_map->show();
        //float_map->raise();
        break;
    case 4:
        float_map->setPixmap(*adapter->gui->belt_right[adapter->gui->dir_device % 4][0]);
        float_map->adjustSize();
        //float_map->show();
        //float_map->raise();
        break;
    case 5:
        float_map->setPixmap(*adapter->gui->com_cutter[adapter->gui->dir_device % 4]);
        switch (adapter->gui->dir_device % 4) {
        case 0:
            float_map->move(tmp.x() - 25, tmp.y() - 25);
            break;
        case 1:
            float_map->move(tmp.x() - 25, tmp.y() - 75);
            break;
        case 2:
            float_map->move(tmp.x() - 75, tmp.y() - 25);
            break;
        case 3:
            float_map->move(tmp.x() - 25, tmp.y() - 25);
            break;
        }
        //auto pos = float_map->pos();
        //float_map->move(pos);
        float_map->adjustSize();
        //float_map->show();
        //float_map->raise();
        break;
    case 6:
        float_map->setPixmap(*adapter->gui->miner[adapter->gui->dir_device % 4]);
        float_map->adjustSize();
        break;
    case 10:
        float_map->setPixmap(*adapter->gui->rotater[adapter->gui->dir_device % 4]);
        float_map->adjustSize();
        break;
    case 11:
        float_map->setPixmap(*adapter->gui->rotater_ccw[adapter->gui->dir_device % 4]);
        float_map->adjustSize();
        break;

    }
}

bool MainWidget::eventFilter(QObject *target, QEvent *ev) {
    if (target == float_map && ev->type() == QEvent::MouseButtonPress) {
        switch (adapter->gui->mouse_status) {
        case 7:
            adapter->gui->drag_tool = 1;
            break;
        case 9:
            adapter->gui->play_widget->clearStk();
            adapter->gui->drag_pipe = 1;
            break;
        }
    }
    return QWidget::eventFilter(target, ev);
}

