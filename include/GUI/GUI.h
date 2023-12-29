#ifndef __GUI_H__
#define __GUI_H__

#include "common.h"
#include "GUI/GUIAdapter.h"
#include "GUI/MainWindow/PlayWidget.h"
#include "GUI/MainWindow/ToolbarWidget.h"
#include "GUI/MainWindow/MainWidget.h"
#include "GUI/MainWindow/MenuWidget.h"
#include "GUI/MainWindow/StoreWidget.h"
#include "GUI/MainWindow/MessageWidget.h"
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <map>

class GUI {

    friend class Game;
    friend class GUIAdapter;
    friend class PlayWidget;
    friend class MainWidget;
    friend class MenuWidget;
    friend class StoreWidget;
    friend class ToolbarWidget;

public:
    GUI();
    GUI(GUI &&) = default;
    GUI(const GUI &) = default;
    GUI &operator=(GUI &&) = default;
    GUI &operator=(const GUI &) = default;
    void update(const int &_tick);
    ~GUI();
    static void alpha(QPixmap * pix, int a);
    static QPixmap smoothScaled(QPixmap pix, float w = 50.0, float h = 50.0);
    static QPixmap smoothRotate(QPixmap pix, float a = 0.0);

private:
    GUIAdapter *adapter;
    MainWidget *main_widget;
    QWidget *intro_window;
    PlayWidget *play_widget;
    MenuWidget *menu_widget;
    StoreWidget *store_widget;
    MessageWidget *msg_widget;
    QWidget *debug_window;
    QLabel *lbl_debug_info;
    ToolbarWidget *toolbar_widget;
    std::map<int, QLabel*> obj_map;
    std::map<int, QPixmap*> obj_origin_pix;
    int tick;
    int mouse_status;
    int dir_device;
    int drag_pipe;
    int drag_tool;
    QPoint mouse_pos, pre_pos;

    QPixmap *empty_block;
    QPixmap *trashbin;
    QPixmap *belt_forward[4][14];
    QPixmap *belt_left[4][14];
    QPixmap *belt_right[4][14];
    QPixmap *cutter[4][2], *com_cutter[4];
    QPixmap *mine1, *mine2;
    QPixmap *miner[4];
    QPixmap *center;
    QPixmap *mine_obj1;
    QPixmap *mine_obj2;
    QPixmap *mine_obj21;
    QPixmap *mine_obj22;
    QPixmap *remove;
    QPixmap *upgrade;
    QPixmap *upgrade1;
    QPixmap *red_spot;
    QPixmap *frame;
    QPixmap *menu;
    QPixmap *white_bkg;
    QPixmap *black_bkg;
    QPixmap *wood_bkg;
    QPixmap *store;
    QPixmap *save;
    QPixmap *load;
    QPixmap *quit;
    QPixmap *coin;
    QPixmap *store_assets;
    QPixmap *money;
    QPixmap *expand;
    QPixmap *flash;
    QPixmap *virt_belt_forward[4];
    QPixmap *virt_belt_left[4];
    QPixmap *virt_belt_right[4];
    QPixmap *black_bkg1;
    QPixmap *rotater[4];
    QPixmap *rotater_ccw[4];
    
};

#endif
