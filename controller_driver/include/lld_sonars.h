/*
 * lld_sonars.h
 *
 *  Created on: 05 ���� 2018 �.
 *      Author: Elena
 */

#ifndef INCLUDE_LLD_SONARS_H_
#define INCLUDE_LLD_SONARS_H_


/*
 * @brief                   Initialize periphery connected to sonars
 */
void lldSonarsInit( void );


/*
 * @brief                   Get Adc value of sonar
 * @return                  ADC value [0, 4096]
 */
uint16_t lldSonar7077AdcVal( uint8_t number );

/*
 * @brief                   Set duty of PWM9 = 20 mks to sync sensor processing
 */
void lldSonarSync( void );


#endif /* INCLUDE_LLD_SONARS_H_ */
