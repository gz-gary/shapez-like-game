#include "GUI/MainWindow/MenuWidget.h"
#include "GUI/GUIAdapter.h"
#include "GUI/GUI.h"
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QFileDialog>

MenuWidget::MenuWidget(QWidget *parent, GUIAdapter *_adapter) :
    QWidget(parent),
    adapter(_adapter),
    toggled(0)
{
    setCursor(Qt::PointingHandCursor);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);
    lbl_menu_icon = new QLabel(this);
    lbl_menu_icon->setPixmap(*adapter->gui->menu);
    lbl_menu_icon->adjustSize();
    lbl_menu_icon->show();
    lbl_menu_icon->installEventFilter(this);
    //lbl_menu_icon->setCursor(Qt::PointingHandCursor);
    resize(lbl_menu_icon->size());

    lbl_bkg = new QLabel(this);
    lbl_bkg->setPixmap(adapter->gui->white_bkg->scaled(175, 250));
    lbl_bkg->adjustSize();
    lbl_bkg->lower();
    lbl_bkg->show();
    lbl_bkg->installEventFilter(this);

    lbl_bkg1 = new QLabel(this);
    lbl_bkg1->setPixmap(adapter->gui->black_bkg1->scaled(175, 50));
    lbl_bkg1->adjustSize();
    lbl_bkg1->lower();
    lbl_bkg1->hide();
    lbl_bkg1->installEventFilter(this);

    lbl_menu_text = new QLabel(this);
    lbl_menu_text->setText("菜单");
    lbl_menu_text->move(lbl_menu_icon->pos() + QPoint(75, 9));

    auto font = lbl_menu_text->font();
    font.setPixelSize(20);
    lbl_menu_text->setFont(font);

    lbl_menu_text->adjustSize();
    lbl_menu_text->show();
    lbl_menu_text->installEventFilter(this);

    lbl_store_icon = new QLabel(this);
    lbl_store_icon->setPixmap(*adapter->gui->store);
    lbl_store_icon->move(0, 50);
    lbl_store_icon->adjustSize();
    lbl_store_icon->show();
    lbl_store_icon->installEventFilter(this);

    lbl_store_text = new QLabel(this);
    lbl_store_text->setText("商店");
    lbl_store_text->move(lbl_menu_icon->pos() + QPoint(75, 9 + 50));
    lbl_store_text->setFont(font);
    lbl_store_text->adjustSize();
    lbl_store_text->show();
    lbl_store_text->installEventFilter(this);

    lbl_save_icon = new QLabel(this);
    lbl_save_icon->setPixmap(*adapter->gui->save);
    lbl_save_icon->move(0, 100);
    lbl_save_icon->adjustSize();
    lbl_save_icon->show();
    lbl_save_icon->installEventFilter(this);

    lbl_save_text = new QLabel(this);
    lbl_save_text->setText("保存");
    lbl_save_text->move(lbl_menu_icon->pos() + QPoint(75, 9 + 100));
    lbl_save_text->setFont(font);
    lbl_save_text->adjustSize();
    lbl_save_text->show();
    lbl_save_text->installEventFilter(this);

    lbl_load_icon = new QLabel(this);
    lbl_load_icon->setPixmap(*adapter->gui->load);
    lbl_load_icon->move(0, 150);
    lbl_load_icon->adjustSize();
    lbl_load_icon->show();
    lbl_load_icon->installEventFilter(this);

    lbl_load_text = new QLabel(this);
    lbl_load_text->setText("载入");
    lbl_load_text->move(lbl_menu_icon->pos() + QPoint(75, 9 + 150));
    lbl_load_text->setFont(font);
    lbl_load_text->adjustSize();
    lbl_load_text->show();
    lbl_load_text->installEventFilter(this);

    lbl_quit_icon = new QLabel(this);
    lbl_quit_icon->setPixmap(*adapter->gui->quit);
    lbl_quit_icon->move(0, 200);
    lbl_quit_icon->adjustSize();
    lbl_quit_icon->show();
    lbl_quit_icon->installEventFilter(this);

    lbl_quit_text = new QLabel(this);
    lbl_quit_text->setText("退出");
    lbl_quit_text->move(lbl_menu_icon->pos() + QPoint(75, 9 + 200));
    lbl_quit_text->setFont(font);
    lbl_quit_text->adjustSize();
    lbl_quit_text->show();
    lbl_quit_text->installEventFilter(this);

    QLabel *lines[7];
    for (int i = 1; i < 6; ++i) {
        lines[i] = new QLabel(this);
        lines[i]->setPixmap(adapter->gui->black_bkg->scaled(175, 2));
        lines[i]->adjustSize();
        lines[i]->move(0, i * 50 - 3);
        lines[i]->raise();
        lines[i]->show();
    }
    lines[6] = new QLabel(this);
    lines[6]->setPixmap(adapter->gui->black_bkg->scaled(2, 250));
    lines[6]->adjustSize();
    lines[6]->move(172, 0);
    lines[6]->raise();
    lines[6]->show();

    lbl_bkg1->hide();
}

MenuWidget::~MenuWidget() {
}

void MenuWidget::toggle() {
    if (!toggled) {
        //lbl_bkg1->show();
        resize(lbl_bkg->size());
    }
    else {
        //lbl_bkg1->hide();
        resize(lbl_menu_icon->size());
    }
    toggled ^= 1;
}

bool MenuWidget::eventFilter(QObject *target, QEvent *ev) {
    if (ev->type() == QEvent::MouseButtonRelease) {
        if (target == lbl_menu_icon) {
            toggle();
        } else {
            QMouseEvent *mv = static_cast<QMouseEvent*>(ev);
            QWidget *widget = qobject_cast<QWidget*>(target);
            auto pos = widget->pos() + mv->pos();
            QString file_name;
            switch (pos.y() / 50) {
            case 0:
                toggle();
                break;
            case 1:
                adapter->gui->play_widget->hide();
                adapter->gui->menu_widget->hide();
                adapter->gui->toolbar_widget->hide();
                //adapter->gui->store_widget->raise();
                adapter->gui->store_widget->show();
                adapter->gui->msg_widget->raise();
                toggle();
                break;
            case 2:
                file_name = QFileDialog::getSaveFileName(NULL, "Save Game", "./save");
                adapter->Menu_saveGame(file_name.toStdString().c_str());
                break;
            case 3:
                file_name = QFileDialog::getOpenFileName(NULL, "Load Game", "./save");
                adapter->Menu_reloadGame(file_name.toStdString().c_str());
                break;
            case 4:
                emit signal_quit();
                break;
            }
        }
    }
    return QWidget::eventFilter(target, ev);
}
bool MenuWidget::event(QEvent *e) {
    if (QEvent::HoverMove == e->type()) {
        QMouseEvent *mv = static_cast<QMouseEvent*>(e);
        auto pos = mv->pos();
        lbl_bkg1->move(0, (pos.y() / 50) * 50 - 3);
    }
    /*if (QEvent::HoverEnter == e->type() && toggled) {
        lbl_bkg1->show();
    }
    if (QEvent::HoverLeave == e->type() && toggled) {
        lbl_bkg1->hide();
    }*/

    if (QEvent::HoverEnter == e->type()) {
        lbl_bkg1->show();
    }
    if (QEvent::HoverLeave == e->type()) {
        lbl_bkg1->hide();
    }
    return QWidget::event(e);
}
