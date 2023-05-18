#include <zephyr/sys/printk.h>
#include <string.h>

#include "data_sys.h"

uint8_t part_seq_table[6][3] = {
    {PART_TYPE_CIRCLE,PART_TYPE_SQUARE,PART_TYPE_TRIANGLE},
    {PART_TYPE_CIRCLE,PART_TYPE_TRIANGLE,PART_TYPE_SQUARE},
    {PART_TYPE_SQUARE,PART_TYPE_CIRCLE,PART_TYPE_TRIANGLE},
    {PART_TYPE_SQUARE,PART_TYPE_TRIANGLE,PART_TYPE_CIRCLE},
    {PART_TYPE_TRIANGLE,PART_TYPE_CIRCLE,PART_TYPE_SQUARE},
    {PART_TYPE_TRIANGLE,PART_TYPE_SQUARE,PART_TYPE_CIRCLE},
};

uint8_t rotary_tab_seq_table[8] = {
    PART_TYPE_CIRCLE,PART_TYPE_SQUARE,PART_TYPE_TRIANGLE,PART_TYPE_SQUARE,
    PART_TYPE_CIRCLE,PART_TYPE_TRIANGLE,PART_TYPE_SQUARE,PART_TYPE_TRIANGLE
};

uint8_t rotary_tab_fill_table[8] = {0,0,0,0,0,0,0,0};

data_sys_node_t data_sys_node;

void data_sys_init(void)
{
    data_sys_node.init_type = SYS_INIT_TYPE_0;
    data_sys_node.run_state = RUN_STATE_NULL;
    data_sys_node.work_state = WORK_STATE_NULL;
    data_sys_node.part_type = PART_TYPE_NULL;
    data_sys_node.part_seq_cfg = PART_SEQ_0;
    data_sys_node.part_seq = 0;
    data_sys_node.rotary_tab_seq = 0;
    printk("data init done!\n");
}

void change_run_state(run_state_code_t next_state)
{
    switch(data_sys_node.run_state){
        case RUN_STATE_NULL:
        break;
        case RUN_STATE_POWER_UP:
        break;
        case RUN_STATE_INIT:
        break;
        case RUN_STATE_AUTO_RUN:
        break;
        case RUN_STATE_MANUAL_RUN:
        break;
        case RUN_STATE_STOP:
        break;
        default:
        break;
    }
    data_sys_node.run_state = next_state;
    printk("change run state to %d\n", next_state);
}

void change_work_state(work_state_code_t next_state)
{
    switch(data_sys_node.work_state){
        case WORK_STATE_NULL:
        break;
        case WORK_STATE_CLIP:
        break;
        case WORK_STATE_ROTATE1:
        break;
        case WORK_STATE_PLACE:
        break;
        case WORK_STATE_ROTATE2:
        break;
        default:
        break;
    }
    data_sys_node.work_state = next_state;
}

void select_part_type(part_type_code_t part_type)
{
    switch(data_sys_node.part_type){
        case PART_TYPE_CIRCLE:
        break;
        case PART_TYPE_SQUARE:
        break;
        case PART_TYPE_TRIANGLE:
        break;
        default:
        break;
    }
}

void set_init_type(int type)
{
    if(type >= SYS_INIT_TYPE_COUNT){
        printk("init type error!\n");
        return;
    }

    type = ~type;
    
    uint8_t val = type & 0x07;
    if(val >= 7){
        printk("part_seq_cfg error!\n");
    }
    printk("part_seq_cfg val = %d\n",val);
    data_sys_node.part_seq_cfg = val;

    data_sys_node.init_type = (sys_init_type_code_t)type;
}