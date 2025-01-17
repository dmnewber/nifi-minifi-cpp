/**
 * @file ManipulateArchive.h
 * ManipulateArchive class declaration
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <string>
#include <memory>

#include "FlowFileRecord.h"
#include "ArchiveMetadata.h"
#include "core/Processor.h"
#include "core/ProcessSession.h"


namespace org {
namespace apache {
namespace nifi {
namespace minifi {
namespace processors {

using logging::Logger;

class ManipulateArchive : public core::Processor {
 public:
  explicit ManipulateArchive(const std::string& name, const utils::Identifier& uuid = {})
  : core::Processor(name, uuid),
    logger_(logging::LoggerFactory<ManipulateArchive>::getLogger()) {
  }
  virtual ~ManipulateArchive() = default;
  static constexpr char const* ProcessorName = "ManipulateArchive";

  // Supported operations
  static char const* OPERATION_REMOVE;
  static char const* OPERATION_COPY;
  static char const* OPERATION_MOVE;
  static char const* OPERATION_TOUCH;

  // Supported Properties
  static core::Property Operation;
  static core::Property Target;
  static core::Property Destination;
  static core::Property Before;
  static core::Property After;
  // Supported Relationships
  static core::Relationship Success;
  static core::Relationship Failure;

  // OnTrigger method, implemented by NiFi ManipulateArchive
  void onTrigger(core::ProcessContext *context, core::ProcessSession *session);
  void onSchedule(core::ProcessContext *context, core::ProcessSessionFactory *sessionFactory);
  // Initialize, over write by NiFi ManipulateArchive
  void initialize(void);

 private:
  // Logger
  std::shared_ptr<Logger> logger_;
  std::string before_, after_, operation_, destination_, targetEntry_;
};

REGISTER_RESOURCE(ManipulateArchive, "Performs an operation which manipulates an archive without needing to split the archive into multiple FlowFiles.");

} /* namespace processors */
} /* namespace minifi */
} /* namespace nifi */
} /* namespace apache */
} /* namespace org */
