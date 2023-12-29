#include "GUI/GUIComponent.h"

GUIComponent::GUIComponent(GUIAdapter *_adapter) :
    QObject(nullptr),
    adapter(_adapter)
{
}

GUIComponent::~GUIComponent() {
}


