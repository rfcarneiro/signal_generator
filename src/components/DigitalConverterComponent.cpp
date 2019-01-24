#include <stdlib.h>
#include <time.h>

#include <hyro/DigitalConverterComponent.h>

using namespace hyro;

namespace digital_converter
{

std::shared_ptr<hyro::HyroLogger> DigitalConverterComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("DigitalConverterComponent");

hyro::Result
DigitalConverterComponent::init (const hyro::ComponentConfiguration & config)
{
  signal_input = this->registerInput<SignalMsgs>("analog_input"_uri, config);
  signal_output = this->registerOutput<float>("digital_output"_uri, config);

  m_amplitude = 10.0;
  m_threshold = -10.0;
  
  m_thresholding.setThreshold(m_threshold);
  
  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::reset ()
{
  // Reset all variables and objects like the object was just created
  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::check ()
{
  // Check everything is OK here
  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::start ()
{
  m_spinner = SpinnerDefault::Create(signal_input, &DigitalConverterComponent::callback, this, this->suspensionToken());
  //m_spinner = SpinnerRated::Create(m_input, &AdderComponent::callback, this, std::chrono::milliseconds(100));

  this->startCurrentStatusStream(2);
  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::update()
{
  return hyro::Result::RESULT_OK;
}

void DigitalConverterComponent::callback(std::shared_ptr<const SignalMsgs> &&msg)
{
  float digital_signal = (float) m_amplitude*m_thresholding.getThresholdSignal(msg->value);
  signal_output->sendAsync(digital_signal);
  s_logger->info("\n Received signal: {}, \n Converted signal: {}", msg->value, digital_signal);
  //std::cerr << signalMsg->value << " " << digital << std::endl;
}

} // namespace signal_generator