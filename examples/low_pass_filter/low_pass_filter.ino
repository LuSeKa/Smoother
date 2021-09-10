/*
 * Low pass filter demo.
 * 
 * The purpose is to show the effect of low pass filtering on higher
 * frequency components, as well as signal attenuation and phase lag.
 */ 

#include "Smoother.h"

#define DIST true
#define NOISE true

#define SIGNAL_FREQ 0.5
#define SIGNAL_AMPL 4.0

#define DIST_FREQ 20.0
#define DIST_AMPL 0.2

#define NOISE_AMPL 0.5

#define SMOOTHER_STRENGTH_LOW 0.9
#define SMOOTHER_STRENGTH_HIGH 0.98

#define PRINT_INTERVAL_MS 10

Smoother a(SMOOTHER_STRENGTH_LOW);
Smoother b(SMOOTHER_STRENGTH_HIGH);

void setup() {
  delay(500);
	Serial.begin(115200);
}

void loop() {
	// assume our input signal is orignially sinusoid
	float signal = a.sinewave(SIGNAL_AMPL, SIGNAL_FREQ);
	float input = signal;
	
	// the signal might contain some unwanted higher frequency disturbance
	if (DIST) {
		input += a.sinewave(DIST_AMPL, DIST_FREQ);
	}
	
	// the signal might also have picked up some unwanted noise
	if (NOISE) {
		input += a.noise(NOISE_AMPL);
	}
	
	// we'll try to recover the original signal via low-pass filtering
	float smoothed_a = a.smooth(input);
	float smoothed_b = b.smooth(input);
	
	// print in a plotter-friendly format
	if (millis() % PRINT_INTERVAL_MS == 0) {
		Serial.print("Signal:");
		Serial.print(signal);
		Serial.print(',');
		Serial.print("Disturbed:");
		Serial.print(input);
		Serial.print(',');
		Serial.print("Smoothed_weak:");
		Serial.print(smoothed_a);
		Serial.print(',');
		Serial.print("Smoothed_strong:");
		Serial.print(smoothed_b);
		Serial.print('\n');
	}	
}
