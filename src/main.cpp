

#include <Arduino.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freeRtos_ads_1220.h>
#include <strain_guage.h>
#include <motor.h>
#include<1256.h>
extern uint32_t step_count;
 TaskHandle_t Taskh1=NULL;
void IRAM_ATTR handleInterrupt() {
  xTaskResumeFromISR(Taskh1);
}
void motortask(void * p)
{
  while(1)
  {
    int duration=20;
    while (1) {
        generate_steps(80, duration);
        changeDirection();
        generate_steps(80, duration);
        changeDirection();
    }
  }
}

void ads1256_task(void * p)
{
  while(1)
  {
   if(digitalRead(4)==LOW)
      {
            ads_1256_interrupt_read();
      }
   else
    vTaskDelay(pdMS_TO_TICKS(2));

  }
}
void setup() {
  Serial.begin(2000000);
  motor_init();
  enable_motor();
  set_up_direction();  
  step_count=0;
  ads1256_init();

  
   pinMode(4, INPUT_PULLUP);
   
    // initialize_strian_guage();
   // xTaskCreatePinnedToCore(update_ads_dataRtos,"printing",2040,NULL,1,&Taskh1,1);
    //  xTaskCreatePinnedToCore(release_suspend_ads,"printing",2040,NULL,1,NULL,0);
      xTaskCreatePinnedToCore(ads1256_task,"ads 1256",3040,NULL,1,NULL,0);
      xTaskCreatePinnedToCore(motortask,"motor_running",3040,NULL,1,NULL,1);
}

void loop() {
  // Your main code here
 //Serial.println(ads_1256_read());
 //ads_1256_interrupt_read();
}

