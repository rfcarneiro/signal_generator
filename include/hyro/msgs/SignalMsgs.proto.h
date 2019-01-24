#pragma once

#ifndef HYRO_MSGS_SIGNALMSGS_PROTO_H
#define HYRO_MSGS_SIGNALMSGS_PROTO_H

#include <signal_generator_components_export.h>

#include <hyro/dynamic/ProtobufTraits.h>
#include <hyro/msgs/SignalMsgs.pb.h>

namespace hyro
{

template <>
struct ProtobufTraits<SignalMsgs> : public ProtobufTraitsDefault<SignalMsgs, msgs::SignalMsgs>
{
  static void
  FromMessage (const msgs::SignalMsgs & msg,
               SignalMsgs * value)
  {
    value->timestamp = msg.timestamp();
    value->frame_id = msg.frame_id();
    value->value = msg.value();
  }

  static void
  ToMessage (const SignalMsgs & value,
             msgs::SignalMsgs * msg)
  {
    msg->set_timestamp(value.timestamp);
    msg->set_frame_id(value.frame_id);
    msg->set_value(value.value);
  }

};

} // namespace hyro

#endif // MY_PACKAGE_MSG_CATEGORYA_POSE_PROTO_H
