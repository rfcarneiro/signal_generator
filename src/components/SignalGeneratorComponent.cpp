#include <hyro/SignalGeneratorComponent.h>

using namespace hyro;

namespace signal_generator
{

std::shared_ptr<hyro::HyroLogger> SignalGeneratorComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("SignalGeneratorComponent");

hyro::Result
SignalGeneratorComponent::init(const hyro::ComponentConfiguration &config)
{
  m_amplitude = 15.0;
  m_frequency = 30.0;
  m_cosine = true;
  m_name = "Name 1";

  m_signal.setAmp(m_amplitude);
  m_signal.setDeg(m_frequency);
  m_signal.setStep(5);

  signal_output = this->registerOutput<hyro::SignalMsgs>("analog_output"_uri, config);

  std::shared_ptr<ChannelOutput<std::vector<int>>>
  m_dummy = this->registerOutput<std::vector<int>>("fix_dynamic"_uri, config);

  registerDynamicProperty<float>("Amplitude",
                                  &SignalGeneratorComponent::setAmplitude,
                                  &SignalGeneratorComponent::getAmplitude,
                                  this);
  registerDynamicProperty<float>("Frequency",
                                  &SignalGeneratorComponent::setFrequency,
                                  &SignalGeneratorComponent::getFrequency,
                                  this);
  registerDynamicProperty<bool>("Cosine",
                                  &SignalGeneratorComponent::setCosine,
                                  &SignalGeneratorComponent::getCosine,
                                  this);

  return hyro::Result::RESULT_OK;
}

hyro::Result
SignalGeneratorComponent::reset()
{
  signal_output.reset();

  return hyro::Result::RESULT_OK;
}

hyro::Result
SignalGeneratorComponent::check()
{
  // Check everything is OK here
  return hyro::Result::RESULT_OK;
}

hyro::Result
SignalGeneratorComponent::start()
{
  // Start spinners and drivers (if any) here
  return hyro::Result::RESULT_OK;
}

hyro::Result
SignalGeneratorComponent::update()
{
  double analog_signal;
  hyro::SignalMsgs signal_msg;
  analog_signal = m_signal.getSignalValue(m_cosine);

  // Build the message
  signal_msg.frame_id = m_name;
  signal_msg.timestamp = (TimeUtils::Now_TimeSinceEpoch().count());
  signal_msg.value = analog_signal;

  signal_output->sendAsync(signal_msg);
  s_logger->info("\n frame id: {}, \n timestamp: {}, \n Signal: {} \n", signal_msg.frame_id, signal_msg.timestamp, signal_msg.value);
  return hyro::Result::RESULT_OK;
}

bool SignalGeneratorComponent::setAmplitude(float amp){
  m_amplitude = amp;
  m_signal.setAmp(m_amplitude);
  return true;
}
float SignalGeneratorComponent::getAmplitude(void){
  return m_amplitude;
}
bool SignalGeneratorComponent::setFrequency(float freq){
  m_frequency = freq;
  m_signal.setDeg(m_frequency);
  return true;
}
float SignalGeneratorComponent::getFrequency(void){
  return m_frequency;
}
bool SignalGeneratorComponent::setCosine(bool cosine){
  m_cosine = cosine;
  return true;
}
bool SignalGeneratorComponent::getCosine(void){
  return m_cosine;
}

} // namespace signal_generator