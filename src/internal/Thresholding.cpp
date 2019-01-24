#include <internal/Thresholding.h>

Thresholding::Thresholding (double digital_zero,double digital_one){
  m_digital_zero = digital_zero;
  m_digital_one = digital_one;
}

int Thresholding::setThreshold (double threshold){
  m_threshold = threshold;
  return 0;

}

double Thresholding::getThreshold (void){
  return m_threshold;
}

double Thresholding::getThresholdSignal (double signal){
  if (signal > m_threshold)
    return m_digital_one;
  else
    return m_digital_zero;
}