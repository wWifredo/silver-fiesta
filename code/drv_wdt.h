#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__

/**
* @brief feed the wwdt manually once.
*/
void drv_wwdt_feed(void);

/**
 * @brief set the interval of wwdt feed time.
 * @param  ms: the interval time. unit: ms
 */
void drv_wwdt_set_feed_interval(uint16_t ms);

/**
* @brief stop feed wwdt. warning: system will reset.
*/
void drv_wwdt_stop_feed(void);

/**
* @brief start feed wwdt.
*/
void drv_wwdt_start_feed(void);

/**
* @brief stop the wwdt device.
*/
void drv_wwdt_stop(void);

/**
* @brief start the wwdt device.
*/
void drv_wwdt_start(void);

#endif // !__DRV_WDT_H__



