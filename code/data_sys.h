#ifndef __DATA_SYS_H__
#define __DATA_SYS_H__

#include <stdint.h>

/** @brief Enumerated for run state. */
typedef enum {
    RUN_STATE_NULL = 0,     ///< default type
    RUN_STATE_POWER_UP,     ///< power up
    RUN_STATE_INIT,         ///< init
    RUN_STATE_AUTO_RUN,     ///< auto run
    RUN_STATE_MANUAL_RUN,   ///< manual operation
    RUN_STATE_STOP,         ///< stop
}run_state_code_t;

/** @brief Enumerated for work state. */
typedef enum {
    WORK_STATE_NULL = 0,     ///< default type
    WORK_STATE_CLIP,         ///< clip part
    WORK_STATE_ROTATE1,      ///< rotate to turntable
    WORK_STATE_PLACE,        ///< place part
    WORK_STATE_ROTATE2,      ///< rotate to conveyer belt
}work_state_code_t;

/** @brief Enumerated for part type. */
typedef enum {
    PART_TYPE_NULL = 0,     ///< default type
    PART_TYPE_CIRCLE,       ///< circle shap
    PART_TYPE_SQUARE,       ///< square shap
    PART_TYPE_TRIANGLE,     ///< triangle shap
    PART_TYPE_COUNT,        ///< the count of part type
}part_type_code_t;

/** @brief Enumerated for init type. */
typedef enum {
    SYS_INIT_TYPE_0 = 0,        ///< default type
    SYS_INIT_TYPE_COUNT = 16,   ///< the count of init type
}sys_init_type_code_t;

/** @brief Enumerated for part sequence. */
typedef enum {
    PART_SEQ_0 = 0,     ///< default seq
    PART_SEQ_1,         ///< CIRCLE,SQUARE,TRIANGLE
    PART_SEQ_2,         ///< CIRCLE,TRIANGLE,SQUARE
    PART_SEQ_3,         ///< SQUARE,CIRCLE,TRIANGLE
    PART_SEQ_4,         ///< SQUARE,TRIANGLE,CIRCLE
    PART_SEQ_5,         ///< RIANGLE,CIRCLE,SQUARE
    PART_SEQ_6,         ///< TRIANGLE,SQUARE,CIRCLE
}part_seq_cfg_code_t;

/** @brief data for system node. */
typedef struct  {
    sys_init_type_code_t init_type;
    run_state_code_t run_state;
    work_state_code_t work_state;
    part_type_code_t part_type;
    part_seq_cfg_code_t part_seq_cfg;
    uint8_t part_seq;
    uint8_t rotary_tab_seq;
}data_sys_node_t;

extern data_sys_node_t data_sys_node;
extern uint8_t part_seq_table[6][3];
extern uint8_t rotary_tab_seq_table[8];
extern uint8_t rotary_tab_fill_table[8];

void data_sys_init(void);

void change_run_state(run_state_code_t next_state);

void change_work_state(work_state_code_t next_state);

void select_part_type(part_type_code_t part_type);

void set_init_type(int type);

#endif // !__DATA_SYS_H__



