#ifndef __CORE_COMPONENT_H__
#define __CORE_COMPONENT_H__

#include "common.h"
#include "Core/CoreAdapter.h"

class CoreComponent : public QObject {

    Q_OBJECT;

public:
    CoreComponent(CoreAdapter *_adapter);
    CoreComponent(CoreComponent &&) = default;
    CoreComponent(const CoreComponent &) = default;
    CoreComponent &operator=(CoreComponent &&) = default;
    CoreComponent &operator=(const CoreComponent &) = default;
    ~CoreComponent();

protected:
    CoreAdapter *adapter;
    
};

#endif // !__CORE_COMPONENT_H__
