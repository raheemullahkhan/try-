#include<strain_guage.h>
ADS1220_WE ads = ADS1220_WE(ADS1220_CS_PIN, ADS1220_DRDY_PIN);
double force_allowed=500;


bool object_detected_between_extremes(bool complex_flag) 
{
  
  double result= ads.getRawData();
  Serial.println(result);
  if(complex_flag==real)
  return 0;
  if(  result<force_allowed)
  return 1;
  else
  return 0;

}




void initialize_strian_guage()
{
Serial.println("scale_initialize");
  if(!ads.init()){
    Serial.println("ADS1220 is not connected!");
    while(1);
  }
  ads.setDataRate(ADS1220_DR_LVL_1);
  ads.setOperatingMode( ADS1220_NORMAL_MODE);
     ads.setAvddAvssAsVrefAndCalibrate();

 ads.setCompareChannels(ADS1220_MUX_0_1);
  //ads.setConversionMode(ADS1220_CONTINUOUS);
}