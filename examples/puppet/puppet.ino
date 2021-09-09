#include <Servo.h>
#include "Smoother.h"

#define NUM_SERVOS 7
#define NUM_POTS 6
#define FIRST_SERVO_PIN 4
#define FIRST_ANALOG_PIN 14

#define DEBUG_OUTPUT true

Smoother smoothers[NUM_POTS];
int smoothed_pots[NUM_POTS];

Servo servos[NUM_SERVOS];
int setpoints[NUM_SERVOS];

void setup() {

  Serial.begin(115200);
  
  // set up servos
  for(int i = 0; i < NUM_SERVOS; i ++) {
	  servos[i].attach(FIRST_SERVO_PIN + i);
  }
  
  // set up smoother smoothing strengths
  smoothers[0].set_strength(0.98);
  smoothers[1].set_strength(0.98);
  smoothers[2].set_strength(0.98);
  smoothers[3].set_strength(0.95);
  smoothers[4].set_strength(0.95);
  smoothers[5].set_strength(0.98);
  smoothers[6].set_strength(0.98);
  
  // set up smoother input ranges (10 bit ADC)
  for (int i = 0; i < NUM_POTS; i ++) {
	  smoothers[i].set_input_range(0, 1023);
  }
  
  // set up smoother output ranges (servo microseconds)
  smoothers[0].set_output_range(2019.2, 382.4);
  smoothers[1].set_output_range(988, 2011);
  smoothers[2].set_output_range(988, 2011);
  smoothers[3].set_output_range(885.6, 2113.2);
  smoothers[4].set_output_range(2114.4, 886.8);
  smoothers[5].set_output_range(-768, 766.5);
  smoothers[6].set_output_range(1138, 2161);
}

void loop() {
  // sample pots and perform smoothing
  for (int i = 0; i < NUM_POTS; i ++) {
	  smoothed_pots[i] = smoothers[i].smooth(analogRead(FIRST_ANALOG_PIN + i));
	  // some values get special treatment
	  if (i == 3) {
		  smoothed_pots[i] = constrain(smoothed_pots[i], 900, 1500);
	  }
	  else if (i == 4) {
		  smoothed_pots[i] = constrain(smoothed_pots[i], 1500, 2100);
	  }
  }
  
  // print every 10 ms
  if (DEBUG_OUTPUT) {
	  if (millis() % 10 == 0) { 
		  for (int i = 0; i < NUM_POTS; i ++) {
		  	  if (i != 4) { // don't print pot "4a"
		  	      Serial.print(smoothed_pots[i]);
		  	      Serial.print('\t');
		  	  }
		  }
		  Serial.print('\n');
	  }
  }
    
  // compute setpoints
  setpoints[0] = smoothed_pots[0];
  setpoints[1] = smoothed_pots[5] - smoothed_pots[4];
  setpoints[2] = smoothed_pots[5] + smoothed_pots[4];
  
  setpoints[4] = smoothed_pots[1];
  setpoints[6] = smoothed_pots[1];
  
  setpoints[3] = smoothed_pots[3];
  setpoints[5] = smoothed_pots[4]; // "4a"
  
  // command servos
  for (int i = 0; i < NUM_SERVOS; i ++) {
	  servos[i].writeMicroseconds(setpoints[i]);
  }
  
  // no need for delay
  
}
