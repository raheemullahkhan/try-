
#include "motor.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <strain_guage.h>
#define STACK_SIZE 9048
#define DELAY_MS 1000
extern uint32_t step_count;





void setup() {
  Serial.begin(115200);
      motor_init();
    enable_motor();
    set_up_direction();
    initialize_strian_guage();
      Serial.begin(115200);
  step_count=0;


  
//  xTaskCreatePinnedToCore(task1, "Task1", STACK_SIZE, NULL, 1, NULL, 1);  // Run task1 on core 1
  //xTaskCreatePinnedToCore(task2, "Task2", STACK_SIZE, NULL, 1, NULL,0);
}

void loop() {
            int duration=300;
    while (1) {
        generate_steps(7, duration);
        changeDirection();
        
        generate_steps(7, duration);
        changeDirection(); 

    }
}