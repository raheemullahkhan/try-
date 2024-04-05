#include<freeRtos_ads_1220.h>
#include<1256.h>
uint8_t ADS1220_START=0x08;

extern bool extreme_taking_data;
void command(uint8_t cmd){
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE1) );
    SPI.transfer(cmd);
    SPI.endTransaction();
}  


void release_suspend_ads(void *par)
{
  while(1)
  {
    if(digitalRead(4)==LOW&&!extreme_taking_data)
    vTaskResume(Taskh1);
    vTaskDelay(pdMS_TO_TICKS(3));

  }
}
void update_ads_dataRtos(void *par)
{
    for(int i;;)
    {

      ads_1256_interrupt_read();
  
//Serial.print("updated");
//Serial.println(strain_guage_rtos);

   
   vTaskSuspend(NULL);
    }
    

}