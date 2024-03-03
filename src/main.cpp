
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
#include <motor.h>
extern uint32_t step_count;
 TaskHandle_t Taskh1=NULL;

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
        vTaskDelay(pdMS_TO_TICKS(1));
      

    }
  }
}
void setup() {
  Serial.begin(115200);
  motor_init();
  enable_motor();
  set_up_direction();

  
  step_count=0;
    initialize_strian_guage();
    pinMode(34, INPUT_PULLUP);
     xTaskCreatePinnedToCore(update_ads_dataRtos,"printing",2040,NULL,1,&Taskh1,0);
      xTaskCreatePinnedToCore(release_suspend_ads,"printing",2040,NULL,1,NULL,0);
    
      xTaskCreatePinnedToCore(motortask,"motor_running",3040,NULL,1,NULL,1);
}

void loop() {
  // Your main code here
}

