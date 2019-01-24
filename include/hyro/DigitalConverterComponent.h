/** \brief Digital Converter Hyro Component.
 *
 * The DigitalConverterComponent reads signal values and uses Thresholding class to convert these values in two values. 
 * It simulates a component that transforms the output of a sensor. 
 * This component has an input channel to read the signal values. An output channel writes the thresholded values. 
 * This component has two parameters amplitude and threshold.
 */

#pragma once

#ifndef DIGITALCONVERTERCOMPONENT_HPP
#define DIGITALCONVERTERCOMPONENT_HPP

#include <string>

#include <hyro/utils/SpinnerDefault.h>
#include <hyro/utils/SpinnerRated.h>
#include <hyro/core/Component.h>
#include <hyro/msgs/All.h>

#include <signal_generator_components_export.h>
#include <hyro/msgs/SignalMsgs.h>
#include <internal/Thresholding.h>

namespace digital_converter
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT DigitalConverterComponent : public hyro::Component
{
public:
  using Component::Component;

  /**
   * @brief Destroy the Digital Converter Component object
   * 
   */
  virtual ~DigitalConverterComponent() override = default;
  
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
   * @brief Function triggered when msg is received
   * 
   * @param msg 
   */
  void
  callback(std::shared_ptr<const hyro::SignalMsgs> &&msg);

private:
  // Other private methods here

  /**
   * @brief Pointer for Component logger
   * 
   */
  static std::shared_ptr<hyro::HyroLogger> s_logger;

  /**
   * @brief Pointer for Component Input Channel
   * 
   */
  std::shared_ptr<hyro::ChannelInput<hyro::SignalMsgs>> signal_input;
  /**
   * @brief Pointer for Component Output Channel
   * 
   */
  std::shared_ptr<hyro::ChannelOutput<float>> signal_output;

  std::unique_ptr<hyro::ISpinner> m_spinner;

  Thresholding m_thresholding;
  /**
   * @brief Amplitude of the output converted signal
   * 
   */
  double m_amplitude;
  /**
   * @brief Threshold to convert the signal
   * 
   */
  double m_threshold;

}; //class

} // namespace digital_converter

#endif // SIGNALGENERATORCOMPONENT_HPP
