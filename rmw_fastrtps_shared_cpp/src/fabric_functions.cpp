// Copyright 2019 ADLINK Technology via Rover Robotics and Dan Rose
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fabric_rmw/fabric_functions.hpp"

#include <sstream>

namespace fabric_functions
{
FabricLogger::FabricLogger(
  const dds_sample_info_t info_,
  const rmw_subscription_t * subscription_,
  const std::string dds_name_)
: timestamp(info_.source_timestamp), subscription(subscription_), dds_name(dds_name_) {}
FabricLogger::FabricLogger(
  const rmw_message_info_t * info_,
  const rmw_subscription_t * subscription_,
  const std::string dds_name_)
: timestamp(info_->source_timestamp), subscription(subscription_), dds_name(dds_name_) {}

void FabricLogger::get_log()
{
  auto now = std::chrono::system_clock::now();
  int64_t now_timestamp =
    std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
  int64_t timestamp_diff = now_timestamp - timestamp;

  std::ostringstream log_stream;
  log_stream << "Topic: " << subscription->topic_name <<
    ", rmw xmt time ns: " << timestamp_diff <<
    ". RMWPUB TS: " << timestamp <<
    ", RMWSUB TS: " << now_timestamp;

  RCUTILS_LOG_DEBUG_NAMED(dds_name.c_str(), log_stream.str().c_str());
}
}
