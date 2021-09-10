#ifndef SMOOTHER_H_
#define SMOOTHER_H_

#include "Arduino.h"

class Smoother {
  public:
    Smoother(void);
    Smoother(float strength);
    void set_strength(float strength);
    void set_interval(float interval_ms);
    void set_input_range(float input_min, float input_max);
    void set_output_range(float output_min, float output_max);
    float smooth(float input);
    void set_starting_value (float start);
    
    // time-based waveform generators for testing
    float sinewave(float amplitude, float frequency_hz);
    float squarewave(float amplitude, float frequency_hz);
    float noise(float amplitude);

  private:
    void setup(void);
    float input_min_;
    float input_max_;
    float output_min_;
    float output_max_;
    int interval_ms_;
    long last_run_time_ms_;
    float strength_;
    float output_;

    float map_float(float x, float in_min, float in_max, float out_min, float out_max);
};
#endif //SMOOTHER_H_
