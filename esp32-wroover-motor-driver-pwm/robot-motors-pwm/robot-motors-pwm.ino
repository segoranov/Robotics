#include <Arduino.h>
#include <analogWrite.h>
#include <memory>

#include "Robot.h"
#include "MotorFactory.h"

std::unique_ptr<Robot> robot;

const int MOTOR_IN_A1 = 26;
const int MOTOR_IN_A2 = 27;
const int MOTOR_PWM_A = 14;

const int MOTOR_IN_B1 = 32;
const int MOTOR_IN_B2 = 33;
const int MOTOR_PWM_B = 25;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting program");
  pinMode(MOTOR_IN_A1, OUTPUT);
  pinMode(MOTOR_IN_A2, OUTPUT);
  pinMode(MOTOR_PWM_A, OUTPUT);
  pinMode(MOTOR_IN_B1, OUTPUT);
  pinMode(MOTOR_IN_B2, OUTPUT);
  pinMode(MOTOR_PWM_B, OUTPUT);
  robot = std::unique_ptr<Robot>(new RobotImpl(
                                   motor_factory::create(MotorDriverType::DUAL_DC, MOTOR_IN_A1, MOTOR_IN_A2, MOTOR_PWM_A),
                                   motor_factory::create(MotorDriverType::DUAL_DC, MOTOR_IN_B1, MOTOR_IN_B2, MOTOR_PWM_B)));
}

void loop()
{
  robot->moveForward(RobotSpeed::NORMAL);
  delay(5000);
  robot->stopMoving();
  delay(2000);
  robot->moveBackward(RobotSpeed::NORMAL);
  delay(5000);
  robot->stopMoving();
  delay(2000);
  Serial.println("End of loop");
}
