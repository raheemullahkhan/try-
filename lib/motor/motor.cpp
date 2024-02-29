#include<motor.h>
#include <Arduino.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<strain_guage.h>
#define real 1
#define imagnary 0
uint64_t real_step_with_out_strainguage_monitor; 
#define imagnary_first_time 1
#define imagnary_second_time 0
#define reversed 1
#define not_reversed 0
bool imagnary_entered=imagnary_first_time;
bool complex_flag=real;
bool direction = 0;
bool imagnary_first_entered_direction;
bool imagnary_direction=direction;
bool imagnary_direction_change_test=not_reversed;
uint64_t imagnary_step_count=0;


void cheack_first_time_entered()
{
if (imagnary_entered==imagnary_first_time)
    {
        Serial.println("imagnary entered first time");
            imagnary==imagnary_second_time;
    }
}
void cheack_imagnary_direction_reversed()
{
    Serial.print("direction");
    Serial.println(direction);
if(imagnary_entered==imagnary_first_time)
   {
     imagnary_direction=direction;
     imagnary_first_entered_direction=direction;
     imagnary_direction_change_test=not_reversed;
     Serial.println("first_direction_noted");

   }

if(imagnary_direction!=imagnary_first_entered_direction&&imagnary_entered==imagnary_second_time)
    {
        imagnary_direction=direction;
        imagnary_direction_change_test=reversed;
        Serial.println("reversed");
    
    }
 if(imagnary_direction==imagnary_first_entered_direction&&imagnary_entered==imagnary_second_time)
    {
        imagnary_direction=direction;
        imagnary_direction_change_test=not_reversed;
        Serial.println("same");

    }


}

static void real_move_one_step(int pulseDuration)
{
    
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
    Serial.println("imagnary_entered");
    if (imagnary_direction_change_test==reversed)
       { imagnary_step_count--;
                 Serial.print("imagnary_count");
         Serial.println(imagnary_step_count);
       }
    else 
       {
         imagnary_step_count++;
         Serial.print("imagnary_count");
         Serial.println(imagnary_step_count);
         imagnary_entered=imagnary_second_time;
       }
    if (imagnary_step_count==0)//imagnary round completed 
       {
        complex_flag=real;
        real_step_with_out_strainguage_monitor=0;
        Serial.println("imagnary cycle ended");
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

void update_flags(void)
{
    if(object_detected_between_extremes(complex_flag,real_step_with_out_strainguage_monitor++))//detect collision in real motion not during imagnary motion 
        complex_flag=imagnary;
    
}
void generate_steps(int number_of_steps, int pulseDuration)
 {
   for(int j=0;j<number_of_steps;j++)
   {
    update_flags();
    if(complex_flag==imagnary)
    {
       
         cheack_imagnary_direction_reversed();
          cheack_first_time_entered();
          imagnary_move_one_step(pulseDuration);

    }
    else
    real_move_one_step(pulseDuration);
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