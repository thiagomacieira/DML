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

#include <dml/detail/common/status.hpp>
#include <dml/detail/common/utils/enum.hpp>
#include <optimization_dispatcher.hpp>

#include "immintrin.h"
#include "kernels.hpp"

namespace dml::core::kernels
{
    void dualcast(dualcast_descriptor dsc, dualcast_completion_record record) noexcept
    {
        const auto src           = reinterpret_cast<byte_t *>(dsc.source_address());
        const auto dst1          = reinterpret_cast<byte_t *>(dsc.destination_1_address());
        const auto dst2          = reinterpret_cast<byte_t *>(dsc.destination_2_address());
        const auto transfer_size = dsc.transfer_size();

        dispatch::dualcast(src, dst1, dst2, transfer_size);

        _mm_mfence();
        record.status() = to_underlying(dml::detail::execution_status::success);
    }
}  // namespace dml::core::kernels
