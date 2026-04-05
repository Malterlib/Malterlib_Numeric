// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp16.h"

using ufp32 = NMib::NNumeric::TCFloat<0, 8, 24, 0>;
using zufp32 = NMib::TCAutoClear<ufp32>;

DMibTraitsImplementSizePair(ufp16, ufp32);
