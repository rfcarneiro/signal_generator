#ifndef _INTERNAL_SIGNAL_GENARATOR_HPP_
#define _INTERNAL_SIGNAL_GENARATOR_HPP_

#include <math.h>

class SignalGenerator{

  double m_deg;  // Waveform frequency
  double m_amp;  // Waveform amplitude
  double m_step; // Sampling step

  public:
  SignalGenerator (void);
  int setAmp (double amp);
  int setDeg (double deg);
  int setStep (double step);
  double getSignalValue (bool cosine=1);
};

#endif