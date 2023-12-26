// Copyright (c) 2023 by Apex.AI Inc. All rights reserved.
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

#ifndef IOX_HOOFS_ERROR_REPORTING_CUSTOM_ERROR_HANDLER_HPP
#define IOX_HOOFS_ERROR_REPORTING_CUSTOM_ERROR_HANDLER_HPP

#include "iox/polymorphic_handler.hpp"
#include "iox/static_lifetime_guard.hpp"

#include "iceoryx_hoofs/error_reporting/custom/default/default_error_handler.hpp"
#include "iceoryx_hoofs/error_reporting/custom/default/error_handler_interface.hpp"

namespace iox
{
namespace er
{

using ErrorHandler = iox::PolymorphicHandler<ErrorHandlerInterface, DefaultErrorHandler>;

using DefaultErrorHandlerGuard = iox::StaticLifetimeGuard<DefaultErrorHandler>;

} // namespace er
} // namespace iox

#endif
