/**
 * @file SignalGeneratorComponent.h
 * @author Rodrigo Fonseca Carneiro (carneiro.rodrigo@gmail.com)
 * @brief Signal Generator Hyro Component.
 * @version 0.1
 * @date 2019-01-24
 * 
 * @copyright Copyright (c) 2019
 * 
 * It uses the SignalGenerator class to output signal values. 
 * Basically, this component simulates a sensor output . The component has one output channel
 * (SignalMsgs) that outputs the signal values. This component has four parameters: amplitude; frequency;
 * name and cosine. The cosine parameter switches between sin and cos functions. It must be possible 
 * to change the values of the parameters amplitude, frequency and cosine dynamically.
 * 
 */
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

  /**
   * @brief Destroy the Digital Converter Component object
   * 
   */
  virtual ~SignalGeneratorComponent() override = default;
  
  /**
   * @brief Initialize Component State Machine
   * 
   * @param config - String containg the component configuration
   * @return hyro::Result 
   */
  virtual hyro::Result
  init(const hyro::ComponentConfiguration &config) override;

  /**
   * @brief Reset Component methods
   * 
   * @return hyro::Result 
   */
  virtual hyro::Result
  reset() override;

  /**
   * @brief Check Component Status
   * 
   * @return hyro::Result 
   */
  virtual hyro::Result
  check() override;

  /**
   * @brief Start Component
   * 
   * @return hyro::Result 
   */
  virtual hyro::Result
  start() override;

  /**
   * @brief Updates the Component methods and variables
   * 
   * @return hyro::Result 
   */
  virtual hyro::Result
  update() override;

  /**
   * @brief Set the Signal Amplitude
   * 
   * Returns if the signal was accepted 
   * @return true 
   * @return false 
   */
  bool setAmplitude(float amp);
  /**
   * @brief Get the Signal Amplitude
   * 
   * @return float - Signal Amplitude
   */
  float getAmplitude(void);
  /**
   * @brief Set the Signal Frequency
   * 
   * Returns if the signal was accepted 
   * @return true 
   * @return false 
   */
  bool setFrequency(float freq);
  /**
   * @brief Get the Signal Frequency
   * 
   * @return float 
   */
  float getFrequency(void);
  /**
   * @brief Set the Cosine variable.
   * If True it generates a Cosine waveform if false a Sine waveform.
   * 
   * @return true 
   * @return false 
   */
  bool setCosine(bool cosine);
  /**
   * @brief Get the Cosine state
   * 
   * @return true - Cosine
   * @return false - Sine
   */
  bool getCosine(void);

  private:

  // Other private methods here

  static std::shared_ptr<hyro::HyroLogger> s_logger;

  std::shared_ptr<hyro::ChannelOutput<hyro::SignalMsgs>> m_signal_output;

  /**
   * @brief Amplitude of the waveform.
   * 
   */
  float m_amplitude;
  /**
   * @brief Frequency of the waveform.
   * 
   */
  float m_frequency;
  /**
   * @brief Waveform type.
   * 
   */
  bool m_cosine;
  /**
   * @brief Name of the waveform.
   * 
   */
  std::string m_name;
  SignalGenerator m_signal;
}; //class

} // namespace signal_generator

#endif // SIGNALGENERATORCOMPONENT_HPP
