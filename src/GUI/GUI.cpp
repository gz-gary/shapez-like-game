#include "GUI/GUI.h"
#include "GUI/GUIAdapter.h"
#include <QTransform>
#include <QColor>
#include <QImage>
#include <QPainter>

GUI::GUI() :
    adapter(new GUIAdapter(this)),
    main_widget(nullptr),
    intro_window(nullptr),
    play_widget(nullptr),
    debug_window(nullptr),
    toolbar_widget(nullptr),
    tick(0),
    mouse_status(0),
    drag_pipe(0),
    drag_tool(0)
{
    QTransform mat_rot;
    mat_rot.rotate(-90);
    char buffer[32];

    empty_block = new QPixmap("./assets/mixer.png");
    empty_block = new QPixmap(smoothScaled(empty_block->copy(16, 58, 96, 96), 50.0, 50.0));
    trashbin = new QPixmap("./assets/trash.png");
    trashbin = new QPixmap(smoothScaled(*trashbin, 50.0, 50.0));

    cutter[0][0] = new QPixmap(smoothScaled(QPixmap("./assets/cutter.png").copy(0, 0, 192, 192), 50.0, 50.0));
    cutter[0][1] = new QPixmap(smoothScaled(QPixmap("./assets/cutter.png").copy(192, 0, 192, 192), 50.0, 50.0));
    com_cutter[0] = new QPixmap(smoothScaled(QPixmap("./assets/cutter.png"), 100.0, 50.0));
    for (int i = 1; i < 4; ++i) {
        cutter[i][0] = new QPixmap(cutter[i - 1][0]->transformed(mat_rot, Qt::SmoothTransformation));
        cutter[i][1] = new QPixmap(cutter[i - 1][1]->transformed(mat_rot, Qt::SmoothTransformation));
        com_cutter[i] = new QPixmap(com_cutter[i - 1]->transformed(mat_rot, Qt::SmoothTransformation));
    }
    
    mine1 = new QPixmap(smoothScaled(QPixmap("./assets/uncolored.png"), 25, 25));
    mine2 = new QPixmap(smoothScaled(QPixmap("./assets/blue.png"), 25, 25));

    miner[0] = new QPixmap(smoothScaled(QPixmap("./assets/miner.png"), 50, 50));
    for (int i = 1; i < 4; ++i) {
        miner[i] = new QPixmap(miner[i - 1]->transformed(mat_rot, Qt::SmoothTransformation));
    }
    rotater[0] = new QPixmap(smoothScaled(QPixmap("./assets/rotater.png"), 50, 50));
    rotater_ccw[0] = new QPixmap(smoothScaled(QPixmap("./assets/rotater-ccw.png"), 50, 50));
    for (int i = 1; i < 4; ++i) {
        rotater[i] = new QPixmap(rotater[i - 1]->transformed(mat_rot, Qt::SmoothTransformation));
        rotater_ccw[i] = new QPixmap(rotater_ccw[i - 1]->transformed(mat_rot, Qt::SmoothTransformation));
    }

    center = new QPixmap(smoothScaled(QPixmap("./assets/block.png").copy(14, 14, 98, 98), 50, 50));
    remove = new QPixmap(smoothScaled(QPixmap("./assets/remove.png"), 50, 50));
    upgrade = new QPixmap(smoothScaled(QPixmap("./assets/upgrade.png"), 50, 50));
    upgrade1 = new QPixmap(QPixmap("./assets/upgrade1.png"));
    coin = new QPixmap(smoothScaled(QPixmap("./assets/coin.png"), 50, 50));
    red_spot = new QPixmap(smoothScaled(QPixmap("./assets/redspot.png"), 15, 15));
    frame = new QPixmap(QPixmap("./assets/frame2.png"));
    menu = new QPixmap(smoothScaled(QPixmap("./assets/menu.png"), 50.0, 50.0));
    store = new QPixmap(smoothScaled(QPixmap("./assets/store.png"), 50, 50));
    save = new QPixmap(smoothScaled(QPixmap("./assets/save.png"), 50, 50));
    load = new QPixmap(smoothScaled(QPixmap("./assets/load.png"), 50, 50));
    quit = new QPixmap(smoothScaled(QPixmap("./assets/quit.png"), 50, 50));
    white_bkg = new QPixmap(QPixmap("./assets/whitebkg1.png"));
    black_bkg = new QPixmap(QPixmap("./assets/blackbkg.png"));
    black_bkg1 = new QPixmap(QPixmap("./assets/blackbkg1.png"));
    wood_bkg = new QPixmap(QPixmap("./assets/woodbkg.jpg"));
    store_assets = new QPixmap(QPixmap("./assets/storeassets.png"));
    money = new QPixmap(QPixmap("./assets/money.png"));
    expand = new QPixmap(QPixmap("./assets/expand.png"));
    flash = new QPixmap(QPixmap("./assets/flash.png"));

    mine_obj1 = new QPixmap(smoothScaled(QPixmap("./assets/shape1.png").copy(82, 82, 429 - 82, 429 - 82), 20, 20));
    mine_obj2 = new QPixmap(smoothScaled(QPixmap("./assets/shape4.png").copy(82, 82, 429 - 82, 429 - 82), 20, 20));
    mine_obj22 = new QPixmap(smoothScaled(QPixmap("./assets/shape4.png").copy(82, 82, 173, 347), 10, 20));
    mine_obj21 = new QPixmap(smoothScaled(QPixmap("./assets/shape4.png").copy(82 + 173, 82, 173, 347), 10, 20));

    virt_belt_forward[0] = new QPixmap(smoothScaled(QPixmap("./assets/belt/belt_top.png"), 50, 50));
    virt_belt_left[0] = new QPixmap(smoothScaled(QPixmap("./assets/belt/belt_left.png"), 50, 50));
    virt_belt_right[0] = new QPixmap(smoothScaled(QPixmap("./assets/belt/belt_right.png"), 50, 50));
    for (int i = 1; i < 4; ++i) {
        virt_belt_forward[i] = new QPixmap(virt_belt_forward[i - 1]->transformed(mat_rot, Qt::SmoothTransformation));
        virt_belt_left[i] = new QPixmap(virt_belt_left[i - 1]->transformed(mat_rot, Qt::SmoothTransformation));
        virt_belt_right[i] = new QPixmap(virt_belt_right[i - 1]->transformed(mat_rot, Qt::SmoothTransformation));
    }
    
    for (int i = 0; i < 14; ++i) {
        sprintf(buffer, "./assets/belt/forward_%d.png", i);
        belt_forward[0][i] = new QPixmap(buffer);
        sprintf(buffer, "./assets/belt/left_%d.png", i);
        belt_left[0][i] = new QPixmap(buffer);
        sprintf(buffer, "./assets/belt/right_%d.png", i);
        belt_right[0][i] = new QPixmap(buffer);
    }
    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < 14; ++j) {
            belt_forward[i][j] = new QPixmap(belt_forward[i - 1][j]->transformed(mat_rot, Qt::SmoothTransformation));
            belt_left[i][j] = new QPixmap(belt_left[i - 1][j]->transformed(mat_rot, Qt::SmoothTransformation));
            belt_right[i][j] = new QPixmap(belt_right[i - 1][j]->transformed(mat_rot, Qt::SmoothTransformation));
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 14; ++j) {
            belt_forward[i][j] = new QPixmap(smoothScaled(*belt_forward[i][j], 50, 50));
            belt_left[i][j] = new QPixmap(smoothScaled(*belt_left[i][j], 50, 50));
            belt_right[i][j] = new QPixmap(smoothScaled(*belt_right[i][j], 50, 50));
        }
    }
 
    intro_window = new QWidget(nullptr);
    main_widget = new MainWidget(nullptr, adapter);
    main_widget->resize(1200, 900);
    main_widget->setMouseTracking(true);
    main_widget->setAttribute(Qt::WA_Hover, true);

    play_widget = new PlayWidget(main_widget, adapter, empty_block);
    play_widget->lower();
    menu_widget = new MenuWidget(main_widget, adapter);
    store_widget = new StoreWidget(main_widget, adapter);

    //debug_window = new QWidget(nullptr);
    //debug_window->resize(400, 400);
    //debug_window->show();
    //lbl_debug_info = new QLabel(debug_window);
    //lbl_debug_info->setText("No");
    //lbl_debug_info->adjustSize();
    //lbl_debug_info->show();

    msg_widget = new MessageWidget(main_widget, adapter);
    msg_widget->raise();
    msg_widget->move(875, 0);
    //msg_widget->resize(300, 500);

    toolbar_widget = new ToolbarWidget(main_widget, adapter);
    toolbar_widget->move(100, 750);
}

GUI::~GUI() {
    //delete adapter;
    //delete main_widget;
    //delete intro_window;
    //delete play_widget;
}

void GUI::update(const int &_tick) {
    tick = _tick;
    for (int i = 1; i <= (play_widget->w); ++i)
        for (int j = 1; j <= (play_widget->h); ++j) {
            auto tmp = play_widget->lbl_mat[i][j];
            switch (tmp->type) {
            case 0:
                break;
            case 1:
                tmp->setPixmap(*belt_forward[tmp->dir][tick % 14]);
                break;
            case 2:
                tmp->setPixmap(*belt_left[tmp->dir][tick % 14]);
                break;
            case 3:
                tmp->setPixmap(*belt_right[tmp->dir][tick % 14]);
                break;
            }
        }
    //if (tick % 30 == 0) {
        //msg_widget->pushMsg("lalala");
    //}
    msg_widget->update(tick);
}

void GUI::alpha(QPixmap *pix, int a) {
    QPainter painter(pix);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.fillRect(pix->rect(), QColor(0, 0, 0, a));
    painter.end();
    //QImage image = pix->toImage();
    //image.fill(qRgba(255, 255, 255, a));
    //*pix = QPixmap::fromImage(image);
}

QPixmap GUI::smoothScaled(QPixmap pix, float w, float h) {
    QTransform mat_scl;
    mat_scl.scale(w / pix.width(), h / pix.height());
    return pix.transformed(mat_scl, Qt::SmoothTransformation);
}

QPixmap GUI::smoothRotate(QPixmap pix, float a) {
    QTransform mat_rot;
    mat_rot.rotate(-a);
    return pix.transformed(mat_rot, Qt::SmoothTransformation);
}
