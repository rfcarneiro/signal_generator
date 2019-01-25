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

void SignalGenerator::setAmp (double amp){
  m_amp = amp;
}

void SignalGenerator::setDeg (double deg){
  m_deg = deg;
}

void SignalGenerator::setStep (double step){
  m_step = step;
}

double SignalGenerator::getAmp (void){
  return m_amp;
}

double SignalGenerator::getDeg (void){
  return m_deg;
}

double SignalGenerator::getStep (void){
  return m_step;
}