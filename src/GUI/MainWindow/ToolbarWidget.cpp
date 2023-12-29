#include "GUI/MainWindow/ToolbarWidget.h"
#include "GUI/GUIAdapter.h"
#include "GUI/GUI.h"
#include <QMouseEvent>

ToolbarWidget::ToolbarWidget(QWidget *parent, GUIAdapter *_adapter) :
    QWidget(parent),
    adapter(_adapter)
{
    for (int i = 1; i <= 10; ++i) {
        lbl_tool[i] = new BlockLabel(this, i, 0);
        lbl_tool[i]->move(30 + 100 * (i - 1), 23);
        lbl_tool[i]->setText("hello");
        lbl_tool[i]->adjustSize();
        lbl_tool[i]->setCursor(Qt::PointingHandCursor);
    }
    lbl_tool[1]->setPixmap(*adapter->gui->trashbin);
    lbl_tool[1]->adjustSize();
    lbl_tool[2]->setPixmap(*adapter->gui->belt_forward[0][0]);
    lbl_tool[2]->adjustSize();
    lbl_tool[3]->setPixmap(*adapter->gui->belt_left[0][0]);
    lbl_tool[3]->adjustSize();
    lbl_tool[4]->setPixmap(*adapter->gui->belt_right[0][0]);
    lbl_tool[4]->adjustSize();
    lbl_tool[5]->setPixmap(*adapter->gui->com_cutter[0]);
    lbl_tool[5]->adjustSize();
    lbl_tool[6]->setPixmap(*adapter->gui->miner[0]);
    lbl_tool[6]->adjustSize();
    lbl_tool[7]->setPixmap(*adapter->gui->remove);
    lbl_tool[7]->adjustSize();
    lbl_tool[8]->setPixmap(*adapter->gui->upgrade);
    lbl_tool[8]->adjustSize();
    lbl_tool[9]->setPixmap(*adapter->gui->virt_belt_forward[0]);
    lbl_tool[9]->adjustSize();
    lbl_tool[10]->setPixmap(*adapter->gui->rotater[0]);
    lbl_tool[10]->adjustSize();
    connect(lbl_tool[1], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(1);});
    connect(lbl_tool[2], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(2);});
    connect(lbl_tool[3], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(3);});
    connect(lbl_tool[4], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(4);});
    connect(lbl_tool[5], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(5);});
    connect(lbl_tool[6], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(6);});
    connect(lbl_tool[7], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(7);});
    connect(lbl_tool[8], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(8);});
    connect(lbl_tool[9], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(9);});
    connect(lbl_tool[10], &BlockLabel::signal_labelClicked,
            this, [=](){slot_selectItem(10);});
    // 11 reserved for alt rotater
    lbl_redspot = new QLabel(this);
    lbl_redspot->setPixmap(*adapter->gui->red_spot);
    lbl_redspot->adjustSize();
    lbl_redspot->move(QPoint(40, 0) + lbl_tool[8]->pos());
    lbl_redspot->show();
    lbl_lvup = new QLabel(this);
    lbl_lvup->setText("1");
    lbl_lvup->adjustSize();
    lbl_lvup->move(QPoint(3, -1) + lbl_redspot->pos());
    lbl_lvup->show();

    resize(1000, 100);
    this->autoFillBackground();
    auto bkgmid = new QLabel(this), bkgleft = new QLabel(this), bkgright = new QLabel(this);
    auto pix_bkgmid = adapter->gui->frame->copy(62, 0, 450 - 62, 512).scaled(1000 - 24, 100);
    auto pix_bkgleft = adapter->gui->frame->copy(0, 0, 61, 511).scaled(12, 100);
    auto pix_bkgright = adapter->gui->frame->copy(451, 0, 512 - 451, 512).scaled(12, 100);
    //GUI::alpha(&pix_bkgleft, 127);
    //GUI::alpha(&pix_bkgright, 127);
    //GUI::alpha(&pix_bkgmid, 127);
    bkgmid->move(12, 0);
    bkgmid->setPixmap(pix_bkgmid);
    bkgmid->adjustSize();
    bkgmid->show();
    bkgmid->lower();
    bkgleft->setPixmap(pix_bkgleft);
    bkgleft->adjustSize();
    bkgleft->show();
    bkgleft->lower();
    bkgright->move(1000 - 12, 0);
    bkgright->setPixmap(pix_bkgright);
    bkgright->adjustSize();
    bkgright->show();
    bkgright->lower();
}

ToolbarWidget::~ToolbarWidget() {
}
void ToolbarWidget::slot_selectItem(int type) {
    adapter->gui->mouse_status = type;
    adapter->gui->dir_device = 0;
}
