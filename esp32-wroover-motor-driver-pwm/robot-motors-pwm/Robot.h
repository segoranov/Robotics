#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "Motor.h"
#include <memory>

enum class RobotSpeed
{
  SLOW,
  NORMAL,
  FAST
};

class Robot
{
  public:
    virtual void moveForward(RobotSpeed speed) = 0;
    virtual void moveBackward(RobotSpeed speed) = 0;
    virtual void turnRight(int degrees = 90) = 0;
    virtual void turnLeft(int degrees = 90) = 0;
    virtual void stopMoving() = 0;
    virtual bool isMoving() = 0;
    virtual bool isNotMoving() = 0;
};

class RobotImpl : public Robot
{
  public:
    explicit RobotImpl(std::unique_ptr<Motor> motorA, std::unique_ptr<Motor> motorB)
      : motorA{std::move(motorA)}, motorB{std::move(motorB)}
    {}

    virtual void moveForward(RobotSpeed speed) override
    {
      configureMotorsForForwardMotion();
      setMotorsSpeed(speed);
    }

    virtual void moveBackward(RobotSpeed speed) override
    {
      configureMotorsForBackwardMotion();
      setMotorsSpeed(speed);
    }

    virtual void turnRight(int degrees = 90) override
    {
      motorA->setSpeed(110);
      delay(5000);
      motorA->turnOff();
    }

    virtual void turnLeft(int degrees = 90) override
    {
      motorB->setSpeed(110);
      delay(5000);
      motorB->turnOff();
    }

    virtual void stopMoving() override
    {
      turnMotorsOff();
    }

    virtual bool isMoving() override
    {
      // TODO
      return false;
    }

    virtual bool isNotMoving() override
    {
      return !isMoving();
    }

  private:
    std::unique_ptr<Motor> motorA;
    std::unique_ptr<Motor> motorB;

    void configureMotorsForForwardMotion()
    {
      motorA->setDirection(MotorDirection::CLOCKWISE);
      motorB->setDirection(MotorDirection::CLOCKWISE);
    }

    void configureMotorsForBackwardMotion()
    {
      motorA->setDirection(MotorDirection::COUNTER_CLOCKWISE);
      motorB->setDirection(MotorDirection::COUNTER_CLOCKWISE);
    }

    void turnMotorsOff()
    {
      motorA->turnOff();
      motorB->turnOff();
    }

    void setMotorsSpeed(RobotSpeed speed)
    {
      switch (speed)
      {
        case RobotSpeed::SLOW:
          {
            setMotorsSpeed(50);
            break;
          }
        case RobotSpeed::NORMAL:
          {
            setMotorsSpeed(110);
            break;
          }
        case RobotSpeed::FAST:
          {
            setMotorsSpeed(200);
            break;
          }
      }
    }

    void setMotorsSpeed(int speed)
    {
      motorA->setSpeed(speed);
      motorB->setSpeed(speed);
    }
};

#endif
