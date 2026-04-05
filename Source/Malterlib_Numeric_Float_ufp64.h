// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp32.h"

using ufp64 = NMib::NNumeric::TCFloat<0, 11, 53, 0>;
using zufp64 = NMib::TCAutoClear<ufp64>;

DMibTraitsImplementSizePair(ufp32, ufp64);
