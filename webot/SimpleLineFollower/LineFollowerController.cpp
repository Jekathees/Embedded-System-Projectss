// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>

#define TIME_STEP 100
#define MAX_SPEED 5.28

using namespace webots;

int main(int argc, char **argv) {

  Robot *robot = new Robot();
 
Motor *left_motor = robot->getMotor("left wheel motor");
Motor *right_motor = robot->getMotor("right wheel motor");

DistanceSensor *left_ir = robot->getDistanceSensor("irs2");
DistanceSensor *right_ir = robot->getDistanceSensor("irs1");

left_ir->enable(TIME_STEP);
right_ir->enable(TIME_STEP);

left_motor->setPosition(INFINITY);
right_motor->setPosition(INFINITY);

left_motor->setVelocity(0.0);
right_motor->setVelocity(0.0);

double left_speed =MAX_SPEED;
double right_speed =MAX_SPEED;

std::cout <<"TIME_STEP:" << TIME_STEP<< ", MAX_SPEED: " << MAX_SPEED << std::endl;
  
  while (robot->step(TIME_STEP) != -1) {
   
double left_ir_val = left_ir->getValue();
double right_ir_val = right_ir->getValue();
    // Process sensor data here.
left_speed = MAX_SPEED;
right_speed = MAX_SPEED;

std::cout << "irs2: " << left_ir_val << ", irs1: " << right_ir_val << std::endl;

bool line_left = (7< left_ir_val) && (left_ir_val <15);
bool line_right = (7 < right_ir_val) && (right_ir_val <15);

if ((left_ir_val > right_ir_val) && line_left)
{left_speed = 0.0 ;
}
else if  ((right_ir_val > left_ir_val) && line_right)
{right_speed = 0.0 ;
}

   left_motor->setVelocity(left_speed); 
   right_motor->setVelocity(right_speed);
std::cout << "Left speed: " << left_speed << ", Right speed" << right_speed << std::endl;

  };
  delete robot;
  return 0;
}