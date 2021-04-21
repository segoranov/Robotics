#ifndef MOTOR_FACTORY_H
#define MOTOR_FACTORY_H

#include "Motor.h"
#include <type_traits>
#include <memory>

namespace motor_factory
{

using MotorPtr = std::unique_ptr<Motor>;

template <typename... Args>
static MotorPtr create(MotorDriverType driverType, Args&&... args)
{
    switch(driverType)
    {
        case MotorDriverType::DUAL_DC:
        {
            return create<MotorImpl>(std::forward<Args>(args)...);
        }
    }
}

template <typename T, typename... Args>
std::enable_if<
    std::is_constructible<T, Args...>::value,
    std::unique_ptr<T>
>
create(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
std::enable_if<
    !std::is_constructible<T, Args...>::value,
    std::unique_ptr<T>
>
create(Args&&... args)
{
    return nullptr;
}

}

#endif
