#include "GUI/MainWindow/StoreWidget.h"
#include "GUI/GUI.h"
#include "GUI/GUIAdapter.h"

StoreWidget::StoreWidget(QWidget *parent, GUIAdapter *_adapter) :
    QWidget(parent),
    adapter(_adapter),
    selected_item(0)
{
    QPixmap frame = makeFrame();
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 2; ++j) {
            lbl_frame[i][j] = new QLabel(this);
            lbl_frame[i][j]->setPixmap(frame);
            lbl_frame[i][j]->move(100 + i * 250, 200 + j * 250);
            lbl_frame[i][j]->adjustSize();
            lbl_frame[i][j]->lower();
            lbl_frame[i][j]->show();
            lbl_frame[i][j]->installEventFilter(this);
            lbl_frame[i][j]->setCursor(Qt::PointingHandCursor);
        }

    //this->setWindowTitle("Store");
    resize(adapter->gui->main_widget->size());
    hide();

    //lbl_bkg = new QLabel(this);
    //lbl_bkg->setPixmap(adapter->gui->wood_bkg->copy(24, 14, 989 - 24, 653 - 14).scaled(size()));
    //lbl_bkg->adjustSize();
    //lbl_bkg->lower();
    //lbl_bkg->show();

    lbl_money_icon = new QLabel(this);
    lbl_money_icon->setPixmap(*adapter->gui->coin);
    lbl_money_icon->move(10, 10);
    lbl_money_icon->adjustSize();
    lbl_money_icon->show();

    lbl_money_text = new QLabel(this);
    lbl_money_text->setText("666");
    lbl_money_text->move(lbl_money_icon->pos() + QPoint(60, 13));
    lbl_money_text->show();

    auto font = lbl_money_text->font();
    font.setPixelSize(20);
    lbl_money_text->setFont(font);

    lbl_money_text->adjustSize();
    lbl_money_text->show();

    for (int i = 0; i < 4; ++i) {
        lbl_obj_icon[i] = new QLabel(this);
        lbl_obj_icon[i]->move(160 + i * 140, 10);
        lbl_obj_icon[i]->show();

        lbl_obj_text[i] = new QLabel(this);
        lbl_obj_text[i]->setText("666");
        lbl_obj_text[i]->move(lbl_obj_icon[i]->pos() + QPoint(60, 13));
        lbl_obj_text[i]->setFont(font);
        lbl_obj_text[i]->show();
        //lbl_obj_icon[i]->installEventFilter(this);
    }
    auto mine_obj1 = new QPixmap(QPixmap("./assets/shape1.png").copy(82, 82, 429 - 82, 429 - 82).scaled(50, 50));
    auto mine_obj2 = new QPixmap(QPixmap("./assets/shape4.png").copy(82, 82, 429 - 82, 429 - 82).scaled(50, 50));
    auto mine_obj22 = new QPixmap(QPixmap("./assets/shape4.png").copy(82, 82, 173, 347).scaled(25, 50));
    auto mine_obj21 = new QPixmap(QPixmap("./assets/shape4.png").copy(82 + 173, 82, 173, 347).scaled(25, 50));
    auto shape3 = new QPixmap(QPixmap("./assets/shape3.png").scaled(150, 150));
    lbl_obj_icon[0]->setPixmap(*mine_obj1);
    lbl_obj_icon[0]->adjustSize();
    lbl_obj_icon[1]->setPixmap(*mine_obj2);
    lbl_obj_icon[1]->adjustSize();
    lbl_obj_icon[2]->setPixmap(*mine_obj21);
    lbl_obj_icon[2]->adjustSize();
    lbl_obj_icon[3]->setPixmap(*mine_obj22);
    lbl_obj_icon[3]->adjustSize();

    lbl_rate = new QLabel(this);
    lbl_rate->setText("倍率: 1.00");
    lbl_rate->setFont(font);
    lbl_rate->move(lbl_obj_icon[3]->pos() + QPoint(120, 9));
    lbl_rate->adjustSize();
    lbl_rate->show();

    lbl_confirm = new QLabel(this);
    lbl_confirm->setPixmap(adapter->gui->store_assets->copy(103, 0, 286 - 103, 91 - 0).scaled(100, 50));
    lbl_confirm->move(1000, 700);
    lbl_confirm->adjustSize();
    lbl_confirm->show();
    lbl_confirm->installEventFilter(this);
    lbl_confirm->setCursor(Qt::PointingHandCursor);

    lbl_cancel = new QLabel(this);
    lbl_cancel->setPixmap(adapter->gui->store_assets->copy(290, 0, 286 - 103, 91 - 0).scaled(100, 50));
    lbl_cancel->move(1000, 775);
    lbl_cancel->adjustSize();
    lbl_cancel->show();
    lbl_cancel->installEventFilter(this);
    lbl_cancel->setCursor(Qt::PointingHandCursor);

    lbl_item_money = new QLabel(this);
    lbl_item_money->setPixmap(adapter->gui->money->scaled(150, 150));
    lbl_item_money->move(lbl_frame[3][1]->pos() + QPoint(5, 5));
    lbl_item_money->adjustSize();
    lbl_item_money->show();
    lbl_item_money->installEventFilter(this);
    lbl_item_money->setCursor(Qt::PointingHandCursor);

    lbl_item_enlarge = new QLabel(this);
    lbl_item_enlarge->setPixmap(adapter->gui->upgrade1->scaled(150, 150));
    lbl_item_enlarge->move(lbl_frame[0][0]->pos() + QPoint(5, 5));
    lbl_item_enlarge->adjustSize();
    lbl_item_enlarge->show();
    lbl_item_enlarge->installEventFilter(this);
    lbl_item_enlarge->setCursor(Qt::PointingHandCursor);

    lbl_item_mine = new QLabel(this);
    lbl_item_mine->setPixmap(*shape3);
    lbl_item_mine->move(lbl_frame[1][0]->pos() + QPoint(5, 5));
    lbl_item_mine->adjustSize();
    lbl_item_mine->show();
    lbl_item_mine->installEventFilter(this);
    lbl_item_mine->setCursor(Qt::PointingHandCursor);
    
    lbl_item_expand = new QLabel(this);
    lbl_item_expand->setPixmap(adapter->gui->expand->scaled(150, 93));
    lbl_item_expand->move(lbl_frame[2][0]->pos() + QPoint(8, 40));
    lbl_item_expand->adjustSize();
    lbl_item_expand->show();
    lbl_item_expand->installEventFilter(this);
    lbl_item_expand->setCursor(Qt::PointingHandCursor);

    lbl_item_rate = new QLabel(this);
    lbl_item_rate->setPixmap(adapter->gui->flash->scaled(150, 150));
    lbl_item_rate->move(lbl_frame[3][0]->pos() + QPoint(5, 5));
    lbl_item_rate->adjustSize();
    lbl_item_rate->show();
    lbl_item_rate->installEventFilter(this);
    lbl_item_rate->setCursor(Qt::PointingHandCursor);

    lbl_intro = new QLabel(this);
    lbl_intro->setText("未选中商品。");
    lbl_intro->move(150, 700);
    lbl_intro->setFont(font);
    lbl_intro->adjustSize();
    lbl_intro->show();
    
}

StoreWidget::~StoreWidget() {
}

QPixmap StoreWidget::makeFrame() {
    QPixmap src = adapter->gui->store_assets->copy(0, 102, 510 - 0, 387 - 102).scaled(165, 165);
    return src;
}

bool StoreWidget::eventFilter(QObject *target, QEvent *ev) {
    if (ev->type() == QEvent::MouseButtonRelease) {
        if (target == lbl_item_money || target == lbl_frame[3][1]) {
            lbl_intro->setText("卖掉所有开采物。");
            lbl_intro->adjustSize();
            selected_item = 8;
        }
        else if (target == lbl_item_enlarge || target == lbl_frame[0][0]) {
            lbl_intro->setText("扩大交付中心。（ -$5000 ）");
            lbl_intro->adjustSize();
            selected_item = 1;
        }
        else if (target == lbl_item_mine || target == lbl_frame[1][0]) {
            lbl_intro->setText("扩大开采物所在地块数量。（ -$4000 ）");
            lbl_intro->adjustSize();
            selected_item = 2;
        }
        else if (target == lbl_item_expand || target == lbl_frame[2][0]) {
            lbl_intro->setText("扩大地图。（ -$10000 ）");
            lbl_intro->adjustSize();
            selected_item = 3;
        }
        else if (target == lbl_item_rate || target == lbl_frame[3][0]) {
            lbl_intro->setText("提高开采物售价倍率。（ -$20000 ）");
            lbl_intro->adjustSize();
            selected_item = 4;
        }
        else if (target == lbl_cancel) {
            hide();
            adapter->gui->play_widget->show();
            adapter->gui->menu_widget->show();
            adapter->gui->toolbar_widget->show();
        } else if (target == lbl_confirm) {
            adapter->Store_buyItem(selected_item);
        }
    }
    return QWidget::eventFilter(target, ev);
}
