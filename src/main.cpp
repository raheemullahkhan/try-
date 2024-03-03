
/*#include "motor.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <strain_guage.h>
#include<freeRtos_ads_1220.h>
#define STACK_SIZE 9048
#define DELAY_MS 1000
extern uint32_t step_count;
*/


/*

void setup() {
  Serial.begin(115200);
  motor_init();
  enable_motor();
  set_up_direction();
  initialize_strian_guage();
  
  step_count=0;


  
 //xTaskCreatePinnedToCore(task1, "Task1", STACK_SIZE, NULL, 1, NULL, 1);  // Run task1 on core 1
  //xTaskCreatePinnedToCore(task2, "Task2", STACK_SIZE, NULL, 1, NULL,0);
}

void loop() {
    int duration=20;
    while (1) {
        generate_steps(80, duration);
        changeDirection();
        generate_steps(80, duration);
        changeDirection(); 

    }
}*/


#include <Arduino.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freeRtos_ads_1220.h>
#include <strain_guage.h>
 TaskHandle_t Taskh1=NULL;
void ads_collision(void *p)
{
  while(1)
  {
  object_detected_between_extremes(1,10,20);
 vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void setup() {
  Serial.begin(115200);
    initialize_strian_guage();
    pinMode(34, INPUT_PULLUP);
     xTaskCreate(update_ads_dataRtos,"printing",2040,NULL,1,&Taskh1);
      xTaskCreate(release_suspend_ads,"printing",2040,NULL,1,NULL);
  xTaskCreate(ads_collision,"straingurage",2030,NULL,1,NULL);
}

void loop() {
  // Your main code here
}

