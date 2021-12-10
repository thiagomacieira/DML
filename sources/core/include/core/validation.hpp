/*
 * Copyright 2021 Intel Corporation.
 *
 * This software and the related documents are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they
 * were provided to you ("License"). Unless the License provides otherwise,
 * you may not use, modify, copy, publish, distribute, disclose or transmit
 * this software or the related documents without Intel's prior written
 * permission.
 *
 * This software and the related documents are provided as is, with no
 * express or implied warranties, other than those that are expressly
 * stated in the License.
 *
 */

#ifndef DML_CORE_VALIDATION_HPP
#define DML_CORE_VALIDATION_HPP

#include <core/types.hpp>
#include <dml/detail/common/status.hpp>

namespace dml::core
{
    [[nodiscard]] dml::detail::validation_status validate(descriptor &dsc) noexcept;
}  // namespace dml::core

#endif  //DML_CORE_VALIDATION_HPP
