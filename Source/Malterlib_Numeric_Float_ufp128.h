// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp64.h"

using ufp128 = NMib::NNumeric::TCFloat<0, 15, 113, 0>;
using zufp128 = NMib::TCAutoClear<ufp128>;

DMibTraitsImplementSizePair(ufp64, ufp128);
