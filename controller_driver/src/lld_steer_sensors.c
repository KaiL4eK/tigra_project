#include <common.h>
#include <lld_steer_sensors.h>

/**************************/
/*** CONFIGURATION ZONE ***/
/**************************/

static float    steerPosPositiveRate    = 0.0;
static float    steerPosNegativeRate    = 0.0;

static int32_t  steerPosCenterAdc       = 2065;
static int32_t  steerPosMaxAdc          = 2800;
static int32_t  steerPosMinAdc          = 1190;

static int32_t  steerPosValidGap        = 100;

/******************************/
/*** CONFIGURATION ZONE END ***/
/******************************/

/***    Variable configuration     ***/

#define steerPosAnalogInputCh       COMMON_ADC_SEQ2_CH
#define steerPressAnalogInputCh     COMMON_ADC_SEQ3_CH

uint16_t lldSteerPosVal         = 0;
uint16_t lldSteerPressPowerVal  = 0;


/**
 * @brief                   Initialize periphery connected to steering sensor
 */
void lldSteerSensorsInit( void )
{
    commonADC1UnitInit();

    steerPosPositiveRate = 100.0 / ( steerPosMaxAdc - steerPosCenterAdc );
    steerPosNegativeRate = 100.0 / ( steerPosCenterAdc - steerPosMinAdc );

}

bool lldSteerSensorsIsValid( void )
{
    return ( steerPosMinAdc - steerPosValidGap < lldSteerPosVal && lldSteerPosVal < steerPosMaxAdc + steerPosValidGap );
}

int16_t lldSteerGetPosition( void )
{
    /* ADC value - [0; 4095] */
    lldSteerPosVal = commonADC1UnitGetValue( steerPosAnalogInputCh );

    /* Limit just not to break calculation */
    int16_t steerValAdc = CLIP_VALUE( lldSteerPosVal, steerPosMinAdc, steerPosMaxAdc );

    steerValAdc = steerValAdc - steerPosCenterAdc;

    int16_t steerValPerc = steerValAdc > 0 ? steerValAdc * steerPosPositiveRate :
                                             steerValAdc * steerPosNegativeRate;

    return steerValPerc;
}

/**
 * @brief                   Get steering press power
 * @return                  ADC value [0, 4096]
 */
uint16_t lldSteerPressPower( void )
{
    lldSteerPressPowerVal = commonADC1UnitGetValue( steerPressAnalogInputCh );    

    return lldSteerPressPowerVal;
}
