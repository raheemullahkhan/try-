#include<motor.h>
#include <Arduino.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<strain_guage.h>
#define real 1
#define imagnary 0
#define imagnary 1
#define imagnary_first_time 1
#define imagnary_second_time 0
bool imagnary_entered=imagnary_first_time;
bool complex_flag=real;
bool direction = 0;
bool imagnary_first_entered_direction;
bool imagnary_direction=direction;
uint32_t imagnary_step_count=0;
void cheack_first_time_entered()
{
if (imagnary_entered==imagnary_first_time)
        imagnary==imagnary_second_time;
}
bool imagnary_direction_reversed()
{
if(imagnary_entered==imagnary_first_time)
   {
     imagnary_direction=direction;
     imagnary_first_entered_direction=direction;
    return 0;
   }
if(imagnary_direction!=imagnary_first_entered_direction)
    return 1;
else 
    return 0;

}

static void real_move_one_step(int pulseDuration)
{
    complex_flag=real;
    for (int i = 0; i < pulse_in_one_step; ++i) 
    {
        digitalWrite(Real_pulse_pin, HIGH);
         delayMicroseconds (pulseDuration);
        digitalWrite(Real_pulse_pin, LOW);
        delayMicroseconds(pulseDuration);
    }

}
static void imagnary_move_one_step(int pulseDuration)
{
    complex_flag=imagnary;
    if (imagnary_direction_reversed())
        imagnary_step_count--;
    else 
       {
         imagnary_step_count++;
         imagnary_entered=imagnary_second_time;
       }
    if (imagnary_step_count==0)//imagnary round completed 
       {
        complex_flag=0;
        imagnary_entered=imagnary_first_time;
       }



    for (int i = 0; i < pulse_in_one_step; ++i) 
    {
        digitalWrite(imagnary_pulse_pin, HIGH);
        delayMicroseconds(pulseDuration);
        digitalWrite(imagnary_pulse_pin, LOW);
        delayMicroseconds(pulseDuration);
    }

}

void generate_steps(int number_of_steps, int pulseDuration)
 {
   for(int j=0;j<number_of_steps;j++)
   {
    if(object_detected_between_extremes(complex_flag))//detect collision in real motion not during imagnary motion
     { 
        cheack_first_time_entered();
        imagnary_move_one_step(pulseDuration);
     }
    else
      {
        real_move_one_step(pulseDuration); 
      }
   }
}

void changeDirection() {
    direction = !direction;
    digitalWrite(DIRECTION_PIN, direction);  // Toggle direction
}

void set_down_direction() {
    digitalWrite(DIRECTION_PIN, LOW);
}

void set_up_direction() {
    digitalWrite(DIRECTION_PIN, HIGH);
}
void motor_init() {
    pinMode(DIRECTION_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);
    pinMode(Real_pulse_pin, OUTPUT);
    digitalWrite(DIRECTION_PIN, HIGH);  // Assuming HIGH is the initial direction
}
void enable_motor() {
    digitalWrite(ENABLE_PIN, HIGH);
}
void disable_motor() {
    digitalWrite(ENABLE_PIN, LOW);
}