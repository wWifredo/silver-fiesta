#include <zephyr/sys/printk.h>
#include <string.h>

#include "ctrl_cfg.h"
#include "../../../../common/com_error/com_error.h"

#include "drv_key.h"
#include "data_sys.h"

void ctrl_cfg_init(void)
{
    int cfg_val = drv_read_cfg_value();
    set_init_type(cfg_val);
}

