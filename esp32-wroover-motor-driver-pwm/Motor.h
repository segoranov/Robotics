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
    Motor(int in1, int in2, int pwm) : in1{in1}, in2{in2}, pwm{pwm}
    {
      Serial.println("Configuring motor pins...");
      configurePins();
    }

    void setDirection(MotorDirection direction)
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

    void setSpeed(int speed)
    {
      analogWrite(pwm, speed);
    }

    void turnOff()
    {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }

  private:
    const int in1;
    const int in2;
    const int pwm;

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

    void configurePins()
    {
      pinMode(in1, OUTPUT);
      pinMode(in2, OUTPUT);
      pinMode(pwm, OUTPUT);
    }
};

#endif
