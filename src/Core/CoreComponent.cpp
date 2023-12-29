#include "Core/CoreComponent.h"

CoreComponent::CoreComponent(CoreAdapter *_adapter) :
    QObject(nullptr),
    adapter(_adapter)
{
}

CoreComponent::~CoreComponent() {
}
