#include <internal/SignalGenerator.h>

SignalGenerator::SignalGenerator (void){
}

double SignalGenerator::getSignalValue (bool cosine){
  double rad;

  rad = m_deg / 180.0 * M_PI;
  m_deg += m_step;
  if (cosine)
    return m_amp * cos(rad);
  return m_amp * sin(rad); 
}

int SignalGenerator::setAmp (double amp){
  m_amp = amp;
  return 0;
}

int SignalGenerator::setDeg (double deg){
  m_deg = deg;
  return 0;
}

int SignalGenerator::setStep (double step){
  m_step = step;
  return 0;
}