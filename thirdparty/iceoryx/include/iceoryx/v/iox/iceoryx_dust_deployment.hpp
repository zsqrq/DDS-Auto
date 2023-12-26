// Copyright (c) 2019 by Robert Bosch GmbH. All rights reserved.
// Copyright (c) 2023 by NXP. All rights reserved.
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
//
// SPDX-License-Identifier: Apache-2.0
#ifndef IOX_POSH_ICEORYX_DUST_DEPLOYMENT_HPP
#define IOX_POSH_ICEORYX_DUST_DEPLOYMENT_HPP

#include <cstdint>

namespace iox
{
namespace build
{
constexpr uint64_t IOX_MAX_NAMED_PIPE_MESSAGE_SIZE = static_cast<uint64_t>(4096);
constexpr uint32_t IOX_MAX_NAMED_PIPE_NUMBER_OF_MESSAGES =
    static_cast<uint32_t>(10);
} // namespace build
} // namespace iox

#endif // IOX_POSH_ICEORYX_DUST_DEPLOYMENT_HPP
