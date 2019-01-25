/**
 * @file SignalGenerator.h
 * @author your name (you@domain.com)
 * @brief Sinusoidal signal generator class.
 * @version 0.1
 * @date 2019-01-24
 * 
 * @copyright Copyright (c) 2019
 * 
 * Class that generates a sinusoidal signal.
 * 
 */
#ifndef _INTERNAL_SIGNAL_GENARATOR_HPP_
#define _INTERNAL_SIGNAL_GENARATOR_HPP_

#include <math.h>

class SignalGenerator{

  /**
   * @brief Waveform frequency
   * 
   */
  double m_deg;
  /**
   * @brief Waveform amplitude
   * 
   */
  double m_amp;
  /**
   * @brief Sampling step
   * 
   */
  double m_step;

  public:
  SignalGenerator (void);

  /**
   * @brief Set the Amplitude of the waveform
   * 
   * @param amp - Desired amplitude.
   */
  void setAmp (double amp);

  /**
   * @brief Set the Frequency of the waveform
   * 
   * @param deg - Desired frequency.
   */
  void setDeg (double deg);

  /**
   * @brief Set the Sampling Step of the component.
   * 
   * @param step - Desired Samplig Step
   */
  void setStep (double step);
  
  /**
   * @brief Get the Signal Value object
   * 
   * @param cosine Selects between sin or cosine waveform.
   * @return double The imediate value of the waveform.
   */
  double getSignalValue (bool cosine=1);

  /**
   * @brief Get the Amplitude of the waveform
   * 
   * @return double 
   */
  double getAmp (void);
  
  /**
   * @brief Get the Frequency of the waveform
   * 
   * @return double 
   */
  double getDeg (void);
  
  /**
   * @brief  Set the Sampling Step of the component.
   * 
   * @return double - Sampling step value
   */
  double getStep (void);
};

#endif