#ifndef __GUI_COMPONENT_H__
#define __GUI_COMPONENT_H__

#include "common.h"
#include "GUI/GUIAdapter.h"

class GUIComponent : public QObject {

    Q_OBJECT;

public:
    GUIComponent(GUIAdapter *_adapter);
    GUIComponent(GUIComponent &&) = default;
    GUIComponent(const GUIComponent &) = default;
    GUIComponent &operator=(GUIComponent &&) = default;
    GUIComponent &operator=(const GUIComponent &) = default;
    ~GUIComponent();

protected:
    GUIAdapter *adapter;
    
};

#endif // !__CORE_COMPONENT_H__
