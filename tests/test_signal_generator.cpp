#include <hyro/SignalGeneratorComponent.h>
#include <hyro/DigitalConverterComponent.h>
#include <hyro/utils/DynamicPropertyAccess.h>

#include <hyro/test/ComponentTester.h>

#include <gtest/gtest.h>

static void
__assert_and_run_state_machine(hyro::StateMachine &sm,
                               const hyro::ComponentConfiguration &conf,
                               const hyro::ConnectionConfiguration &endpoint)
{
  ASSERT_EQ(hyro::Result::RESULT_OK, sm.init(conf));

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.start());

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.connect(endpoint));

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.check());
}

#define ASSERT_AND_RUN_STATE_MACHINE(sm, conf, endpoint) \
  __assert_and_run_state_machine(sm, conf, endpoint)

using namespace signal_generator;
using namespace digital_converter;

namespace hyro
{
namespace test
{

TEST(ExampleTest, SignalGeneratorComponentCheck)
{
  //Configuration
  auto generator_configuration = "{"
                                 "outputs: {"
                                 //"analog_output: { protocol: 'api', ip: '0.0.0.0',   port: '50051' },"
                                 "analog_output: { protocol: 'api'},"
                                 "fix_dynamic: { protocol: 'api'},"
                                 "}"
                                 "}";

  //IntGeneratorComponent state machine
  StateMachine sm(std::make_shared<SignalGeneratorComponent>("/generator"_uri));

  auto result = sm.init(ComponentConfiguration(generator_configuration));
  ASSERT_EQ(Result::RESULT_OK, result);

  result = sm.start();
  ASSERT_EQ(Result::RESULT_OK, result);

  result = sm.connect(ConnectionConfiguration());
  ASSERT_EQ(Result::RESULT_OK, result);

  result = sm.check();
  ASSERT_EQ(Result::RESULT_OK, result);

  //Fake input channels
  auto AnalogOut = std::make_shared<FakeInput<SignalMsgs>>("AnalogOut"_uri, "api", "/generator/analog_output");
  ASSERT_TRUE(AnalogOut->connect());

  DynamicPropertyAccess dynamic_property_access("/generator"_uri);

  auto ret = dynamic_property_access.set<bool>("Cosine", true);
  ASSERT_EQ(ret, true);
  ASSERT_TRUE(dynamic_property_access.set<float>("Amplitude", 100.0));
  ASSERT_TRUE(dynamic_property_access.set<float>("Frequency", 30.0));

  bool cosine;
  dynamic_property_access.get<bool>("Cosine", cosine);
  ASSERT_EQ(cosine, true);

  float amp, freq;
  dynamic_property_access.get<float>("Amplitude", amp);
  ASSERT_EQ(amp, 100.0);
  dynamic_property_access.get<float>("Frequency", freq);
  ASSERT_EQ(freq, 30.0);

  sm.update();

  auto ValueAnalogOut = std::shared_ptr<const SignalMsgs>();

  auto return_value = AnalogOut->receive(ValueAnalogOut, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, return_value);
}

TEST(ExampleTest, DigitalConverterComponentCheck)
{
  //Configuration
  auto converter_configuration = "{"
                                 "inputs: {"
                                 "analog_input: { protocol: 'api' }"
                                 "},"
                                 "outputs: {"
                                 "digital_output: { protocol: 'api' }"
                                 "}"
                                 "}";

  //Fake input channels
  auto AnalogInput = std::make_shared<FakeOutput<SignalMsgs>>("AnalogInput"_uri, "api");
  auto DigitalOutput = std::make_shared<FakeInput<float>>("DigitalOutput"_uri, "api", "/converter/digital_output");

  //IntGeneratorComponent state machine
  StateMachine sm(std::make_shared<DigitalConverterComponent>("/converter"_uri));

  auto result = sm.init(ComponentConfiguration(converter_configuration));
  ASSERT_EQ(Result::RESULT_OK, result);

  result = sm.start();
  ASSERT_EQ(Result::RESULT_OK, result);

  ASSERT_TRUE(AnalogInput->start());
  ASSERT_TRUE(DigitalOutput->connect());

  result = sm.connect(ConnectionConfiguration("{ analog_input: { endpoint: 'AnalogInput' } }"));
  ASSERT_EQ(Result::RESULT_OK, result);

  result = sm.check();
  ASSERT_EQ(Result::RESULT_OK, result);

  //TEST
  sm.update();

  auto ValueDigitalOut = std::shared_ptr<const float>();
  //auto ValueAnalogIn = std::shared_ptr<const SignalMsgs>();
  ReceiveStatus ret;

  SignalMsgs ValueAnalogIn;
  ValueAnalogIn.frame_id = "Teste 1";
  ValueAnalogIn.timestamp = 100000000000;
  ValueAnalogIn.value = -20.0;

  AnalogInput->sendAsync(ValueAnalogIn);

  ret = DigitalOutput->receive(ValueDigitalOut, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, ret);

  EXPECT_EQ(*ValueDigitalOut, 0.0);

  ValueAnalogIn.frame_id = "Teste 1";
  ValueAnalogIn.timestamp = 100000000000;
  ValueAnalogIn.value = 20.0;

  AnalogInput->sendAsync(ValueAnalogIn);

  ret = DigitalOutput->receive(ValueDigitalOut, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, ret);

  EXPECT_EQ(*ValueDigitalOut, 10.0);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

} // namespace test
} // namespace hyro
