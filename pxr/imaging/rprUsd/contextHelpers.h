/************************************************************************
Copyright 2020 Advanced Micro Devices, Inc
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
************************************************************************/

#ifndef PXR_IMAGING_RPR_USD_CONTEXT_HELPERS_H
#define PXR_IMAGING_RPR_USD_CONTEXT_HELPERS_H

#include "pxr/imaging/rprUsd/api.h"
#include "pxr/imaging/rprUsd/contextMetadata.h"

#include <string>
#include <vector>

namespace rpr { class Context; }

PXR_NAMESPACE_OPEN_SCOPE

RPRUSD_API
rpr::Context* RprUsdCreateContext(RprUsdContextMetadata* metadata);

struct RprUsdDevicesInfo {
    struct CPU {
        int numThreads;
        CPU(int numThreads = 0) : numThreads(numThreads) {}
        bool operator==(CPU const& rhs) { return numThreads == rhs.numThreads; }
    };
    CPU cpu;

    struct GPU {
        int index;
        std::string name;
        GPU(int index = -1, std::string name = {}) : index(index), name(name) {}
        bool operator==(GPU const& rhs) { return index == rhs.index && name == rhs.name; }
    };
    std::vector<GPU> gpus;

    bool IsValid() const {
        return cpu.numThreads > 0 || !gpus.empty();
    }
};

RPRUSD_API
RprUsdDevicesInfo RprUsdGetDevicesInfo(RprUsdPluginType pluginType);

RPRUSD_API
bool RprUsdIsTracingEnabled();

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_IMAGING_RPR_USD_CONTEXT_HELPERS_H
