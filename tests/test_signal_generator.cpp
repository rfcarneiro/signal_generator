#include <hyro/SignalGeneratorComponent.h>
#include <hyro/DigitalConverterComponent.h>
#include <hyro/utils/DynamicPropertyAccess.h>

#include <hyro/test/ComponentTester.h>

#include <gtest/gtest.h>

#define TEST_AMPLITUDE 100.0
#define TEST_FREQUENCY 30.0
#define TEST_COSINE false
#define TEST_TIMESTAMP 1000000000
#define TEST_FRAMID "Teste 1"
#define TEST_VALUE 20.0
#define TEST_RETURNED_VALUE_POS 1.0
#define TEST_RETURNED_VALUE_NEG 0.0

using namespace signal_generator;

namespace hyro
{
namespace test
{

TEST(ExampleTest, SignalGeneratorComponentCheck)
{
  //Configuration
  auto generator_configuration = "{"
                                 "parameters: {amplitude: 0.5, frequency: 0.5, cosine: true},"
                                 "outputs: {"
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
  auto analog_out = std::make_shared<FakeInput<SignalMsgs>>("AnalogOut"_uri, "api", "/generator/analog_output");
  ASSERT_TRUE(analog_out->connect());

  DynamicPropertyAccess dynamic_property_access("/generator"_uri);

  auto ret = dynamic_property_access.set<bool>("cosine", TEST_COSINE);
  ASSERT_EQ(ret, true);
  ASSERT_TRUE(dynamic_property_access.set<float>("amplitude", TEST_AMPLITUDE));
  ASSERT_TRUE(dynamic_property_access.set<float>("frequency", TEST_FREQUENCY));

  bool cosine;
  dynamic_property_access.get<bool>("cosine", cosine);
  ASSERT_EQ(cosine, TEST_COSINE);

  float amp, freq;
  dynamic_property_access.get<float>("amplitude", amp);
  ASSERT_EQ(amp, TEST_AMPLITUDE);
  dynamic_property_access.get<float>("frequency", freq);
  ASSERT_EQ(freq, TEST_FREQUENCY);

  sm.update();

  auto value_analog_out = std::shared_ptr<const SignalMsgs>();

  auto return_value = analog_out->receive(value_analog_out, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, return_value);
  ASSERT_GE(value_analog_out->value, (-TEST_AMPLITUDE));
  ASSERT_LE(value_analog_out->value, TEST_AMPLITUDE);
}

TEST(ExampleTest, DigitalConverterComponentCheck)
{
  //Configuration
  auto converter_configuration = "{"
                                 "parameters: {amplitude: 2, threshold: 0.0},"
                                 "inputs: {"
                                 "analog_input: { protocol: 'auto' }"
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

  auto value_digital_out = std::shared_ptr<const float>();
  //auto ValueAnalogIn = std::shared_ptr<const SignalMsgs>();
  ReceiveStatus ret;

  SignalMsgs value_analog_in;
  value_analog_in.frame_id = TEST_FRAMID;
  value_analog_in.timestamp = TEST_TIMESTAMP;
  value_analog_in.value = (-TEST_VALUE);

  AnalogInput->sendAsync(value_analog_in);

  ret = DigitalOutput->receive(value_digital_out, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, ret);

  ASSERT_EQ(*value_digital_out, TEST_RETURNED_VALUE_NEG);

  value_analog_in.frame_id = TEST_FRAMID;
  value_analog_in.timestamp = TEST_TIMESTAMP;
  value_analog_in.value = TEST_VALUE;

  AnalogInput->sendAsync(value_analog_in);

  ret = DigitalOutput->receive(value_digital_out, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, ret);

  ASSERT_EQ(*value_digital_out, TEST_RETURNED_VALUE_POS);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

} // namespace test
} // namespace hyro
