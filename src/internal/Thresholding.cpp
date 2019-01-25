#include <internal/Thresholding.h>

Thresholding::Thresholding (double amplitude,double digital_zero,double digital_one)
  : m_amplitude(amplitude)
  , m_digital_zero(digital_zero)
  , m_digital_one(digital_one)
{
}


void Thresholding::setThreshold (double threshold){
  m_threshold = threshold;
}

double Thresholding::getThreshold (void){
  return m_threshold;
}

double Thresholding::getThresholdSignal (double signal){
  return (signal > m_threshold) ? m_digital_one : m_digital_zero;
}