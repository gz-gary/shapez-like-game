#include "GUI/MainWindow/PlayWidget.h"
#include "GUI/GUIAdapter.h"
#include "GUI/GUI.h"
#include "qevent.h"
#include "qnamespace.h"
#include <QPixmap>
#include <QCursor>

PlayWidget::PlayWidget(QWidget *parent, GUIAdapter *_adapter, QPixmap *default_empty) :
    QWidget(parent),
    adapter(_adapter),
    w(50),
    h(50)
{
    setAutoFillBackground(true);
    //resize(1200, 750);
    //resize(2400, 1500);
    resize(w * 50, h * 50);
    //show();
    int w0 = 50;
    int h0 = 50;
    for (int i = 1; i <= w; ++i)
        for (int j = 1; j <= h; ++j)
        {
            lbl_mat[i][j] = new BlockLabel(this, i, j);
            lbl_mat[i][j]->move(w0 * (i - 1), h0 * (j - 1));
            lbl_mat[i][j]->type = 0;
            lbl_mat[i][j]->installEventFilter(this);
        }
    for (int i = 1; i <= w; ++i)
        for (int j = 1; j <= h; ++j)
        {
            lbl_bkg[i][j] = new BlockLabel(this, i, j);
            lbl_bkg[i][j]->setPixmap(*default_empty);
            lbl_bkg[i][j]->adjustSize();
            lbl_bkg[i][j]->move(w0 * (i - 1), h0 * (j - 1));
            lbl_bkg[i][j]->lower();
            lbl_bkg[i][j]->installEventFilter(this);
        }
    setCursor(Qt::OpenHandCursor);
}

PlayWidget::~PlayWidget() {
}

bool PlayWidget::event(QEvent *e) {
    return QWidget::event(e);
}
void PlayWidget::mouseReleaseEvent(QMouseEvent *ev) {
}

bool PlayWidget::eventFilter(QObject *target, QEvent *ev) {
    if (ev->type() == QEvent::MouseButtonPress) {
        if (adapter->gui->mouse_status == 0) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(ev);
            auto widget = qobject_cast<QWidget*>(target);
            adapter->gui->mouse_pos = widget->pos() + mouseEvent->pos() + pos();
            adapter->gui->pre_pos = pos();
            adapter->gui->mouse_status = -1;
            setCursor(Qt::ClosedHandCursor);
        } else if (adapter->gui->mouse_status == 2) {
            //while (!pipe_lis.empty()) pipe_lis.pop();
            //in_lis.clear();
            //adapter->gui->drag_pipe = 1;
        }
    } else if (ev->type() == QEvent::MouseButtonRelease) {
        adapter->gui->mouse_status = 0;
        adapter->gui->play_widget->setCursor(Qt::OpenHandCursor);
    }
    return QWidget::eventFilter(target, ev);
}

void PlayWidget::updateStk(std::pair<int, int> p) {
    auto iter = pipe_set.find(p);
    if (iter == pipe_set.end()) {
        pipe_stk.push(p);
        pipe_set.insert(p);
        adapter->GUI_drawPipeLis(pipe_stk);
        //printf("in (%d,%d)\n", pipe_lis.top().first, pipe_lis.top().second);
    } else if (*iter != pipe_stk.top()) {
        while (*iter != pipe_stk.top()) {
            pipe_set.erase(pipe_stk.top());
            //printf("out (%d,%d)\n", pipe_lis.top().first, pipe_lis.top().second);
            pipe_stk.pop();
        }
        adapter->GUI_drawPipeLis(pipe_stk);
    }
}

void PlayWidget::clearStk() {
    while (!pipe_stk.empty()) pipe_stk.pop();
    pipe_set.clear();
}

void PlayWidget::drawVirtPipe(std::stack<PipeLisObj> stk) {
    clearVirt();
    while (!stk.empty()) {
        auto tmp = new QLabel(this);
        auto tp = stk.top();
        switch (tp.dir_to - tp.dir_frm) {
        case 2:
        case -2:
            tmp->setPixmap(*adapter->gui->virt_belt_forward[(tp.dir_to + 3) % 4]);
            break;
        case 3:
        case -1:
            tmp->setPixmap(*adapter->gui->virt_belt_left[(tp.dir_to + 2) % 4]);
            break;
        case 1:
        case -3:
            tmp->setPixmap(*adapter->gui->virt_belt_right[tp.dir_to]);
            break;
        }
        tmp->adjustSize();
        tmp->move((tp.x - 1) * 50, (tp.y - 1) * 50);
        tmp->show();
        lbl_virt_pipe.push(tmp);
        stk.pop();
    }
}

void PlayWidget::clearVirt() {
    while (!lbl_virt_pipe.empty()) {
        delete lbl_virt_pipe.top();
        lbl_virt_pipe.pop();
    }
}
