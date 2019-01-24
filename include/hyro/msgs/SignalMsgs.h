#pragma once

#ifndef HYRO_MSGS_SIGNALMSGS_H
#define HYRO_MSGS_SIGNALMSGS_H

#include <iostream>
#include <signal_generator_components_export.h>

#include <hyro/core/Component.h>
#include <string>

namespace hyro
{

struct SIGNAL_GENERATOR_COMPONENTS_EXPORT SignalMsgs
{
  long int timestamp;
  std::string frame_id;
  double value;
};

} // namespace hyro

// This file will created and explained in the next step
#include <../include/hyro/msgs/SignalMsgs.proto.h>

#endif //HYRO_SIGNAL_GENERATOR_MSGS_SIGNAL_H