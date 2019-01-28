#include <iostream>
#include <hyro/common/Time.h>
#include <hyro/core/StateMachine.h>
#include <hyro/widgets/WidgetCollection.h>
#include <hyro/factory/CommandFactory.h>
#include <hyro/utils/DynamicPropertyAccess.h>

#include <../include/hyro/SignalGeneratorComponent.h>
#include <../include/hyro/DigitalConverterComponent.h>

//#define DEBUG
#define SET_VALUES_OPTION 1
#define EXIT_OPTION 2

using namespace hyro;
using namespace signal_generator;
using namespace std::string_literals;

int main(void)
{
  hyro::LogConfig config;
  config.level = hyro::LogLevel::CRITICAL;
  hyro::HyroLoggerManager::Configure(config);

  //State machine creation
  StateMachine signal_generator_sm(std::make_shared<SignalGeneratorComponent>("/generator"_uri));
  StateMachine digital_converter_sm(std::make_shared<DigitalConverterComponent>("/converter"_uri));

  std::string generator_configuration;
  std::string converter_configuration;

  // Configuration Strings
  generator_configuration = "{"
                            "parameters: {amplitude: 10, frequency: 10, cosine: true},"
                            "outputs: {"
                            "analog_output: { protocol: 'grpc', ip: '0.0.0.0',   port: '50051' },"
                            "fix_dynamic: { protocol: 'api'},"
                            "}"
                            "}";

  converter_configuration = "{"
                            "parameters: {amplitude: 1, threshold: 0.0},"
                            "inputs: {"
                            "analog_input: { protocol: 'auto' }"
                            "},"
                            "outputs: {"
                            "digital_output: { protocol: 'api' }"
                            "}"
                            "}";

  //input_proto = "grpc";

  // Dynamic Property
  signal_generator_sm.init(ComponentConfiguration(generator_configuration));
  digital_converter_sm.init(ComponentConfiguration(converter_configuration));

  auto remote_endpoint = ConnectionConfiguration("{ analog_input: { endpoint: '/generator/analog_output' } }");

  signal_generator_sm.start();
  digital_converter_sm.start();

  signal_generator_sm.connect();
  digital_converter_sm.connect(remote_endpoint);

  signal_generator_sm.check();
  digital_converter_sm.check();

  bool stop = false;
  //std::atomic<bool> stop(false);

  /* This thread is done for getting the user's input while it can be plotted */
  std::thread input_thread([&signal_generator_sm, &digital_converter_sm, &stop]() {
    float amp, freq;
    bool cosine;
    int option;
    int cosine_option;
    /* Dynamic properties Access */
    DynamicPropertyAccess dynamic_property_access("/generator"_uri);
    while (!stop)
    {
      /* Read parameters values */
      dynamic_property_access.get<float>("amplitude", amp);
      dynamic_property_access.get<float>("frequency", freq);
      dynamic_property_access.get<bool>("cosine", cosine);

      std::cout << "Current parameters" << std::endl;
      std::cout << "Amplitude: " << amp
                << " Frequency: " << freq
                << " Waveform: " << (cosine ? "Cosine" : "Sine")
                << std::endl;
      std::cout << "------------------------------------------------" << std::endl
                << SET_VALUES_OPTION << " - Choose new values" << std::endl
                << EXIT_OPTION << " - Quit" << std::endl
                << "-> ";

      std::cin >> option;

      if (option == SET_VALUES_OPTION)
      {
        std::cout << "Set Amplitude: ";
        std::cin >> amp;
        std::cout << "Set Frequency: ";
        std::cin >> freq;
        std::cout << "1 - Cosine " << std::endl
                  << "2 - Sine " << std::endl
                  << "-> ";
        std::cin >> cosine_option;
        cosine = ((cosine_option == 1) ? true : false);
        dynamic_property_access.set<float>("amplitude", amp);
        dynamic_property_access.set<float>("frequency", freq);
        dynamic_property_access.set<bool>("cosine", cosine);
      }
      stop = (option == EXIT_OPTION)?true:false;
    };
  });

  std::thread th1([&signal_generator_sm, &stop]() {
    while (!stop)
    {
      signal_generator_sm.update();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  });

  widgets::registerChannelListener<hyro::SignalMsgs>("protocol: 'grpc', ip: '0.0.0.0',   port: '50051'", "grpc", [](hyro::SignalMsgs msg) {
    widgets::plot2d<float>("Analog Signal", "/generator/analog_output", msg.value);
  });

  widgets::plot2d<float>("Digital Signal", "/converter/digital_output", widgets::Plot2dSettings::initWithProtocol("api"));

  if(!stop)
  {
    widgets::exec();
    //std::this_thread::sleep_for(2s);
  }else
  {
    signal_generator_sm.reset();
    digital_converter_sm.reset();
    widgets::reset();
  }
  return 0;
}