#ifndef __CTRL_PWM_H__
#define __CTRL_PWM_H__

#include "../../../../../common/com_algorithm/motor/stepper/com_smd.h"

void crtl_pwm_init(void);

extern com_smd_dev_t high_ctrl_motor;
extern com_smd_dev_t length_ctrl_motor;
extern com_smd_dev_t angle_ctrl_motor;
extern com_smd_dev_t turntable_ctrl_motor;

extern com_smd_dev_t timer9_ch1;
extern com_smd_dev_t timer9_ch2;

#endif // !__CTRL_PWM_H__



