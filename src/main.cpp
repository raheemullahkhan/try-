



#include "motor.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <strain_guage.h>
#define STACK_SIZE 9048
#define DELAY_MS 1000

void task1(void *pulse_duration) {
  while (true) {
    Serial.println("Task 2 is running");
    vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
  }

}

void task2(void *parameter) {

          int duration=10;
    while (1) {
        generate_steps(64, duration);
        changeDirection();
        
        generate_steps(64, duration);
        changeDirection(); 
        Serial.println("task1");
    }
    vTaskDelay(40);
}

void setup() {
  Serial.begin(115200);
      motor_init();
    enable_motor();
    set_up_direction();
    initialize_strian_guage();
      Serial.begin(115200);
  

  
//  xTaskCreatePinnedToCore(task1, "Task1", STACK_SIZE, NULL, 1, NULL, 1);  // Run task1 on core 1
  //xTaskCreatePinnedToCore(task2, "Task2", STACK_SIZE, NULL, 1, NULL,0);
}

void loop() {
            int duration=20;
    while (1) {
        generate_steps(90, duration);
        changeDirection();
        
        generate_steps(90, duration);
        changeDirection(); 
        Serial.println("task1");
    }
}