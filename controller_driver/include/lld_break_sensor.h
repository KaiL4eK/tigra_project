#ifndef INCLUDE_LLD_BREAK_SENSOR_H_
#define INCLUDE_LLD_BREAK_SENSOR_H_

#include <common.h>

/*** Variables ***/

typedef int16_t breakPressPower_t;

/*** Prototypes ***/

/*
 * @brief 	Initialize periphery connected to break sensor
 */
void breakSensorInit ( void );

/*
 * @brief	Check if break is pressed
 * @return 	true  - break is pressed
 * 			false - break is not pressed
 */
bool breakSensorIsPressed ( void );

/*
 * @brief	Get press power value
 * @return	[0, 100] - Press power percentage
 * 			< 0 	 - Sensor not initialized
 */
breakPressPower_t breakSensorGetPressPower ( void );

#endif /* INCLUDE_LLD_BREAK_SENSOR_H_ */
