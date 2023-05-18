#ifndef __CTRL_SERVO_H__
#define __CTRL_SERVO_H__

#include "../../../../common/com_device/servo/dev_servo.h"

void ctrl_servo_init(void);

int servo1_set_angle(float angle);
int servo2_set_angle(float angle);
int servo3_set_angle(float angle);
int servo4_set_angle(float angle);

#endif // !__CTRL_SERVO_H__



