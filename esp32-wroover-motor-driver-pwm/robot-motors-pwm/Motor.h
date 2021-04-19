#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <analogWrite.h>

enum class MotorDirection
{
  CLOCKWISE,
  COUNTER_CLOCKWISE
};

class Motor
{
  public:
    virtual void setDirection(MotorDirection direction) = 0;
    virtual void setSpeed(int speed) = 0;
    virtual int getSpeed() const = 0;
    virtual void turnOff() = 0;
};

class MotorImpl : public Motor
{
  public:
    explicit MotorImpl(int in1, int in2, int pwm) : in1{in1}, in2{in2}, pwm{pwm}
    {
      Serial.print("Creating motor with in1 = ");
      Serial.print(in1);
      Serial.print("; in2 = ");
      Serial.print(in2);
      Serial.print("; pwm = ");
      Serial.println(pwm);
    }

    virtual void setDirection(MotorDirection direction) override
    {
      switch (direction)
      {
        case MotorDirection::CLOCKWISE:
          {
            setClockwiseDirection();
            break;
          }
        case MotorDirection::COUNTER_CLOCKWISE:
          {
            setCounterClockwiseDirection();
            break;
          }
      }
    }

    virtual void setSpeed(int speed) override
    {
      this->speed = speed;
      analogWrite(pwm, speed);
    }

    virtual int getSpeed() const override
    {
      return speed;
    }

    virtual void turnOff() override
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }

  private:
    const int in1;
    const int in2;
    const int pwm;
    int speed = 0;

    void setClockwiseDirection()
    {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    }

    void setCounterClockwiseDirection()
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
};

#endif
