#ifndef __DRV_KEY_H__
#define __DRV_KEY_H__


void drv_key_init(void);

int drv_read_cfg_value(void);

void key1_pressed_proc(void);
void key2_pressed_proc(void);
void key3_pressed_proc(void);
void key4_pressed_proc(void);

void button1_pressed_proc(void);
void button2_pressed_proc(void);
void button3_pressed_proc(void);
void button4_pressed_proc(void);

void start_key_pressed_proc(void);

void ptonc0_pressed_proc(void);
void ptono0_pressed_proc(void);

#endif // !__DRV_KEY_H__



