#include<freeRtos_ads_1220.h>
uint8_t ADS1220_START=0x08;
int32_t strain_guage_rtos=0;
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
     uint8_t buf[3];
    uint32_t rawResult = 0;
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE1));
    buf[0] = SPI.transfer(0x00);
    buf[1] = SPI.transfer(0x00);
    buf[2] = SPI.transfer(0x00);
    SPI.endTransaction();
    rawResult = buf[0];
    rawResult = (rawResult << 8) | buf[1];
    rawResult = (rawResult << 8) | buf[2];
    rawResult = (rawResult << 8);
     command(ADS1220_START);
     strain_guage_rtos = (static_cast<int32_t>(rawResult)) >> 8;
Serial.print("updated");
Serial.println(strain_guage_rtos);

   
    vTaskSuspend(NULL);
    }
    

}