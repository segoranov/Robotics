#ifndef ROBOT_H
#define ROBOT_H

#include "Motor.h"

class Robot
{
  public:
    virtual void moveForward(int speed) = 0;
    virtual void moveBackward(int speed) = 0;
    virtual void turnRight(int degrees) = 0;
    virtual void turnLeft(int degrees) = 0;
    virtual void stopMoving() = 0;
    virtual bool isMoving() = 0;
    virtual bool isNotMoving() = 0;
};

// For slow movement, good speed is 110
class RobotImpl : public Robot
{
  public:
    virtual void moveForward(int speed) override
    {
      configureMotorsForForwardMotion();
      setMotorsSpeed(speed);
    }

    virtual void moveBackward(int speed) override
    {
      configureMotorsForBackwardMotion();
      setMotorsSpeed(speed);
    }

    virtual void turnRight(int degrees) override
    {

    }

    virtual void turnLeft(int degrees) override
    {

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
    Motor motorA{26, 27, 14};
    Motor motorB{32, 33, 25};

    void configureMotorsForForwardMotion()
    {
      motorA.setDirection(MotorDirection::CLOCKWISE);
      motorB.setDirection(MotorDirection::COUNTER_CLOCKWISE);
    }

    void configureMotorsForBackwardMotion()
    {
      motorA.setDirection(MotorDirection::COUNTER_CLOCKWISE);
      motorB.setDirection(MotorDirection::CLOCKWISE);
    }

    void turnMotorsOff()
    {
      motorA.turnOff();
      motorB.turnOff();
    }

    void setMotorsSpeed(int speed)
    {
      motorA.setSpeed(speed);
      motorB.setSpeed(speed);
    }
};

#endif
