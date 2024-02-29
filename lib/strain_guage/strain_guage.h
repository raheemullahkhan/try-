#ifndef strain_guage_H
#define strain_guage_H
#include <Arduino.h>
#include <ADS1220_WE.h>
#include <SPI.h>
#define real 1
#define imagnary 0
bool object_detected_between_extremes(bool,uint8_t,uint8_t );
#define ADS1220_CS_PIN    5 // chip select pin
#define ADS1220_DRDY_PIN  34 // data ready pin 
void initialize_strian_guage();
void scale_init();

#endif
