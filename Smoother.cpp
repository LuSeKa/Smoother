#include "Smoother.h"

Smoother::Smoother(void) {
  setup();
  strength_ = 0.98;
}

Smoother::Smoother(float strength) {
  setup();
  set_strength(strength);
}

void Smoother::setup(void) {
  interval_ms_ = 5;
  last_run_time_ms_ = millis();
  input_min_ = 0.0;
  input_max_ = 1.0;
  output_min_ = 0.0;
  output_max_ = 1.0;
}

void Smoother::set_strength(float strength) {
  strength_ = constrain(strength, 0.0, 1.0);
}
void Smoother::set_interval(float interval_ms) {
  interval_ms_ = interval_ms;
}
void Smoother::set_input_range(float input_min, float input_max) {
  input_min_ = input_min;
  input_max_ = input_max;
}

void Smoother::set_output_range(float output_min, float output_max) {
  output_min_ = output_min;
  output_max_ = output_max;
}

float Smoother::smooth(float input) {
  long now = millis();
  if ((now - last_run_time_ms_) > interval_ms_) {
    last_run_time_ms_ = now;
    output_ = output_ * strength_ + input * (1.0 - strength_);
  }
  // return scaled output
  return map_float(output_, input_min_, input_max_, output_min_, output_max_);
}

void Smoother::set_starting_value (float start) {
  output_ = start;
}

float Smoother::sinewave(float amplitude, float frequency_hz) {
  long period_ms = 1000.0 / frequency_hz;
  return amplitude * sin(2.0 * PI * millis() / period_ms);
}

float Smoother::squarewave(float amplitude, float frequency_hz) {
  long period_ms = 1000.0 / frequency_hz;
  float result;
  result = (2 * millis() / period_ms % 2 == 0) ? amplitude : -1.0 * amplitude;
  return result;
}

float Smoother::noise(float amplitude) {
  return amplitude * (((float)random(2001) - 1000.0) / 1000.0);
}

float Smoother::map_float(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
