#ifndef __PLAY_WIDGET_H__
#define __PLAY_WIDGET_H__

#include "common.h"
#include <QWidget>
#include <QPixmap>
#include <set>
#include <stack>
#include "GUI/MainWindow/BlockLabel.h"
#include "Core/Map/Block/Direction.h"
#include "qcoreevent.h"
#include "qobject.h"

class GUIAdapter;

class PlayWidget : public QWidget {

    Q_OBJECT;

    friend class GUIAdapter;
    friend class GUI;

public:
    PlayWidget(QWidget *parent, GUIAdapter *_adapter, QPixmap *default_empty);
    PlayWidget(PlayWidget &&) = default;
    PlayWidget(const PlayWidget &) = default;
    PlayWidget &operator=(PlayWidget &&) = default;
    PlayWidget &operator=(const PlayWidget &) = default;
    ~PlayWidget();
    void updateStk(std::pair<int, int> p);
    void clearStk();
    void drawVirtPipe(std::stack<PipeLisObj> stk);
    void clearVirt();

private:
    GUIAdapter *adapter;
    BlockLabel *lbl_mat[MAXN][MAXN];
    BlockLabel *lbl_bkg[MAXN][MAXN];
    std::stack<QLabel*> lbl_virt_pipe;
    std::stack<std::pair<int, int>> pipe_stk;
    std::set<std::pair<int, int>> pipe_set;
    int w, h;

protected:
    void mouseReleaseEvent(QMouseEvent *ev) override;
    bool event(QEvent *event) override;
    bool eventFilter(QObject *target, QEvent *ev) override;
};

#endif // !__PLAY_WIDGET__
