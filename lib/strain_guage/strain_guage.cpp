#include<strain_guage.h>
ADS1220_WE ads = ADS1220_WE(ADS1220_CS_PIN, ADS1220_DRDY_PIN);
#include<freeRtos_ads_1220.h>
extern double strain_guage_rtos;
bool extreme_taking_data=0;
double force_allowed=70;

#define free_step_limit 8
double value_at_extreme=0;
void take_value_after_two_step_of_direction_change()
{
  extreme_taking_data=1;
  value_at_extreme=ads.getRawData();
  Serial.println(value_at_extreme);
  ads.start();
  extreme_taking_data=0;
}
bool object_detected_between_extremes(bool complex_flag,uint8_t free_step,uint8_t step_count) 
{
  bool a;
  double result= strain_guage_rtos;
  Serial.println(result);
  if(complex_flag==imagnary)
  {
   // Serial.println("imagnary collision not allowed");
    a=0;
  }
  
  if (complex_flag==real&&free_step>9)
      {
          if(abs(abs(result)-abs(value_at_extreme))>force_allowed)
          {
            Serial.println("collision detected");
            a= 1;
          }
            else
            {
              //Serial.println("collision not detected");
                  a= 0;
            }
    }
  if (complex_flag==real&&free_step<9)
 {
   a=0;
    value_at_extreme=ads.getRawData();   
   //Serial.print("real_free_steps");
   //Serial.println(free_step);
   }
   if (complex_flag==real&&free_step==9)
 {
   
    value_at_extreme=ads.getRawData();   

   }
   if(abs(step_count)<3)// donot detect collision -3<stepcount<3
   a=0;


return a;

}
void initialize_strian_guage()
{
Serial.println("scale_initialize");
  if(!ads.init()){
    Serial.println("ADS1220 is not connected!");
    while(1);
  }
  ads.setDataRate(ADS1220_DR_LVL_6);
  ads.setOperatingMode( ADS1220_NORMAL_MODE);
     ads.setAvddAvssAsVrefAndCalibrate();

 ads.setCompareChannels(ADS1220_MUX_0_1);
  //ads.setConversionMode(ADS1220_CONTINUOUS);
}