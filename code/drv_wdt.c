#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/drivers/watchdog.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <string.h>

#include "drv_wdt.h"


#define STACKSIZE 512               ///< size of stack area used by each thread

#define PRIORITY CONFIG_NUM_PREEMPT_PRIORITIES  ///< scheduling priority used by each thread

uint16_t feed_interval_ms = 50;     ///< feed interval. unit: ms
static int wdt_channel_id;                 ///< wdt channel id

#define WWDG_DEVICE_NODE DT_ALIAS(wwdg) ///< wwdg node
static const struct device *wdt = DEVICE_DT_GET(WWDG_DEVICE_NODE);  ///< wdg device
#define WDT_MAX_WINDOW  100U        ///< wdg windows value

#ifndef WDT_ALLOW_CALLBACK
#define WDT_ALLOW_CALLBACK 1
#endif
#define WDT_FEED_TRIES 1

static k_tid_t sys_k_tid = 0;       ///< thread ID

void drv_wwdt_feed(void)
{
    if((wdt != NULL) && (wdt_channel_id >= 0)){
        wdt_feed(wdt, wdt_channel_id);
    }
}

void drv_wwdt_set_feed_interval(uint16_t ms)
{
    feed_interval_ms = ms;
}

void drv_wwdt_stop_feed(void)
{
    if(sys_k_tid){
        k_thread_suspend(sys_k_tid);
    } else {
        printk("error: sys wwdg k_tid null\n");
    }
}

void drv_wwdt_start_feed(void)
{
    if(sys_k_tid){
        k_thread_resume(sys_k_tid);
    } else {
        printk("error: sys wwdg k_tid null\n");
    }
}

void drv_wwdt_stop(void)
{
    // TODO
}

void drv_wwdt_start(void)
{
    // TODO
}

#if WDT_ALLOW_CALLBACK
/**
* @brief wdt callback function.
*/
static void wdt_callback(const struct device *wdt_dev, int channel_id)
{
    static bool handled_event;

    if (handled_event) {
        return;
    }

    drv_wwdt_feed();

    printk("Handled things..ready to reset\n");
    handled_event = true;
}
#endif

/**
* @brief wdt init function.
*/
void wdt_init( void )
{
    int err;

    struct wdt_timeout_cfg wdt_config = {
        // Reset SoC when watchdog timer expires. 
        .flags = WDT_FLAG_RESET_SOC,
        // Expire watchdog after max window 
        .window.min = 0U,
        .window.max = WDT_MAX_WINDOW,
    };
    
#if WDT_ALLOW_CALLBACK
    // Set up watchdog callback.
    wdt_config.callback = wdt_callback;
    printk("Attempting to test pre-reset callback\n");
#else // WDT_ALLOW_CALLBACK 
    printk("Callback in RESET_SOC disabled for this platform\n");
#endif // WDT_ALLOW_CALLBACK 

    wdt_channel_id = wdt_install_timeout(wdt, &wdt_config);
    if (wdt_channel_id == -ENOTSUP){
        // IWDG driver for STM32 doesn't support callback
        printk("Callback support rejected, continuing anyway\n");
        wdt_config.callback = NULL;
        wdt_channel_id = wdt_install_timeout(wdt, &wdt_config);
    }
    
    if (wdt_channel_id < 0) {
        printk("Watchdog install error\n");
        return;
    }

    err = wdt_setup(wdt, WDT_OPT_PAUSE_HALTED_BY_DBG);
    if (err < 0) {
        printk("Watchdog setup error\n");
        return;
    }

    drv_wwdt_feed();
}

/**
* @brief wdt feed task
*/
void wdt_feed_task( void )
{
    wdt_init();
    
    sys_k_tid = k_current_get();
    if(!sys_k_tid){
        printk("get sys wwdg k_tid fail\n");
    } else {
        //printk("get sys wwdg k_tid = %d\n",(int)sys_k_tid);
    }
    
    while (1) {
        drv_wwdt_feed();
        k_msleep(feed_interval_ms);
    }
}

/**
* @brief wdt thread define.
*/
//K_THREAD_DEFINE(wdt_feed_task_id, STACKSIZE, wdt_feed_task, NULL, NULL, NULL, PRIORITY, 0, 0);


