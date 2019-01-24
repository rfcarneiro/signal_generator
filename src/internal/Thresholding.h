#ifndef _INTERNAL_THRESHOLDING_HPP_
#define _INTERNAL_THRESHOLDING_HPP_

#include <math.h>

class Thresholding{

  double m_threshold;  // Threshold
  double m_digital_one,m_digital_zero;  // Variable to define the amplitude of the signal
  
  public:
  Thresholding (double digital_zero = 0.0,double digital_one = 1.0);
  int setThreshold (double threshold);
  double getThreshold (void);
  double getThresholdSignal (double signal);
};

#endif