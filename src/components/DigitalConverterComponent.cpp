#include <stdlib.h>
#include <time.h>

#include <hyro/DigitalConverterComponent.h>

using namespace hyro;

namespace signal_generator
{
std::shared_ptr<hyro::HyroLogger> DigitalConverterComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("DigitalConverterComponent");

hyro::Result
DigitalConverterComponent::init (const hyro::ComponentConfiguration & config)
{
  m_signal_input = this->registerInput<SignalMsgs>("analog_input"_uri, config);
  m_signal_output = this->registerOutput<float>("digital_output"_uri, config);

  double amp, thresh;
  amp    = config.parameters.getParameter<double>("amplitude", DIGITAL_AMPLITUDE_DEFAULT);
  thresh = config.parameters.getParameter<double>("threshold", DEFAULT_THRESHOLD);
  
  m_thresholding = Thresholding(amp,thresh);
  
  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::reset ()
{
  // Reset all variables and objects like the object was just created
  m_signal_input.reset();
  m_signal_output.reset();
  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::check ()
{
  // Check everything is OK here
  if (m_signal_input->connectionStatus() != ConnectionStatus::CONNECTION_UP)
    return Result::RESULT_ERROR;
  return hyro::Result::RESULT_OK;
}

hyro::Result
DigitalConverterComponent::start ()
{
  m_spinner = SpinnerDefault::Create(m_signal_input, &DigitalConverterComponent::callback, this, this->suspensionToken());

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
  float digital_signal = (float) m_thresholding.getThresholdSignal(msg->value);
  m_signal_output->sendAsync(digital_signal);

  s_logger->info("\n Received signal: {}, \n Converted signal: {}", msg->value, digital_signal);
  
}

} // namespace signal_generator