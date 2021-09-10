#include "Smoother.h"

#define EMULATION false

Smoother s(0.95);

void setup() {
  Serial.begin(115200);
  pinMode(12, INPUT_PULLUP);
  delay(200); // give the serial plotter some time to get set up
}

void loop() {
  int switch_1 = 100 * digitalRead(12); // sample switch state
  if (EMULATION) {
	// switch emulation: override switch state with test signal
    switch_1 = s.squarewave(50, 0.5) + 50;
  }
  float switch_1_smoothed = s.smooth(switch_1); // smooth switch state

  if (millis()%10 == 0) { // print every 10 ms
    Serial.print("raw:");
    Serial.print(switch_1); 
    Serial.print('\t');
    Serial.print("smoothed:");   
    Serial.println(switch_1_smoothed);
  }
}
