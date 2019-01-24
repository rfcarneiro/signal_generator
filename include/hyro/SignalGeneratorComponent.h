#pragma once

#ifndef SIGNALGENERATORCOMPONENT_HPP
#define SIGNALGENERATORCOMPONENT_HPP

#include <string>

#include <hyro/core/Component.h>
#include <hyro/utils/DynamicPropertyAccess.h>
#include <hyro/msgs/All.h>

#include <signal_generator_components_export.h>
#include <hyro/msgs/SignalMsgs.h>
#include <internal/SignalGenerator.h>

namespace signal_generator
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT SignalGeneratorComponent : public hyro::Component
{
  public:
  
  using Component::Component;

  virtual 
  ~SignalGeneratorComponent () override = default;

  virtual hyro::Result
  init (const hyro::ComponentConfiguration & config) override;

  virtual hyro::Result
  reset () override;

  virtual hyro::Result
  check () override;

  virtual hyro::Result
  start () override;

  virtual hyro::Result
  update () override;

  bool setAmplitude(float);
  float getAmplitude(void);
  bool setFrequency(float);
  float getFrequency(void);
  bool setCosine(bool);
  bool getCosine(void);

  private:

  // Other private methods here

  static std::shared_ptr<hyro::HyroLogger> s_logger;

  std::shared_ptr<hyro::ChannelOutput<hyro::SignalMsgs>> signal_output;

  float m_amplitude;
  float m_frequency;
  bool m_cosine;
  std::string m_name;
  SignalGenerator m_signal;
}; //class

} // namespace signal_generator

#endif // SIGNALGENERATORCOMPONENT_HPP
