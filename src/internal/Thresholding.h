/**
 * @file Thresholding.h
 * @author your name (you@domain.com)
 * @brief Thresholding calculation class.
 * @version 0.1
 * @date 2019-01-24
 * 
 * @copyright Copyright (c) 2019
 * 
 * The input value is converted in two values. If the input value is bigger than the
 * threshold, digital_one is assigned  else digital_zero is assigned.
 * 
 */
#ifndef _INTERNAL_THRESHOLDING_HPP_
#define _INTERNAL_THRESHOLDING_HPP_

#include <math.h>

#define DIGITAL_ZERO_DEFAULT      0.0
#define DIGITAL_ONE_DEFAULT       1.0
#define DIGITAL_AMPLITUDE_DEFAULT 10.0
#define DEFAULT_THRESHOLD         0.0

class Thresholding{

  /**
   * @brief Threshold value
   * 
   */
  double m_threshold;
  /**
   * @brief Variables to define the amplitude of the thresholded signal
   * 
   */
  double m_digital_one,m_digital_zero;  
  /**
   * @brief Converted signal amplitude value
   * 
   */
  double m_amplitude;

  public:
  Thresholding (double amplitude = DIGITAL_AMPLITUDE_DEFAULT, 
                double threshold = DEFAULT_THRESHOLD,
                double digital_zero = DIGITAL_ZERO_DEFAULT,
                double digital_one = DIGITAL_ONE_DEFAULT);
  /**
   * @brief Set the Threshold value
   * 
   * @param threshold - Desired threshhold.
   * @return int - error code.
   */
  void setThreshold (double threshold);
  /**
   * @brief Get the Threshold value.
   * 
   * @return double - Threshhold value.
   */
  double getThreshold (void);
  /**
   * @brief Get the Threshold Signal 
   * 
   * @param signal - Analog value to be converted.
   * @return double - Thresholded value.
   */
  double getThresholdSignal (double signal);
};

#endif