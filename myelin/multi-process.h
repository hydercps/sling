// Copyright 2017 Google Inc.
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

#ifndef MYELIN_MULTI_PROCESS_H_
#define MYELIN_MULTI_PROCESS_H_

#include "myelin/compute.h"

#include <condition_variable>
#include <mutex>
#include <thread>

namespace sling {
namespace myelin {

class Worker;

// Myelin runtime for multi-processor execution.
class MultiProcessorRuntime : public Runtime {
 public:
  ~MultiProcessorRuntime();
  string Description() override { return "Multi-processor"; }

  // Instance data allocation.
  void AllocateInstance(Instance *instance) override;
  void FreeInstance(Instance *instance) override;
  void ClearInstance(Instance *instance) override;

  // Multi-processor runtime support.
  bool SupportsAsync() override { return true; }
  TaskFunc StartTaskFunc() override;
  TaskFunc WaitTaskFunc() override;

 private:
  // Mutex for synchronizing access to worker pool.
  std::mutex mu_;

  // Worker pool.
  std::vector<Worker *> workers_;
};

}  // namespace myelin
}  // namespace sling

#endif  // MYELIN_MULTI_PROCESS_H_

