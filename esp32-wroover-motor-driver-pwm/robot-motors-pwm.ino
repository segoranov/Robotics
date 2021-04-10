#include <Arduino.h>
#include <analogWrite.h>
#include <memory>

#include "Robot.h"

std::unique_ptr<Robot> robot;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting program");
  robot = std::unique_ptr<Robot>(new RobotImpl());
}

void loop()
{
  robot->moveForward(110);
  delay(5000);
  robot->stopMoving();
  delay(2000);
  robot->moveBackward(110);
  delay(5000);
  robot->stopMoving();
  delay(2000);
}
