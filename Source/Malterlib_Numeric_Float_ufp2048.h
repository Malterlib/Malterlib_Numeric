// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp1024.h"

using ufp2048 = NMib::NNumeric::TCFloat<0, 63, 2048-63, 0>;
using zufp2048 = NMib::TCAutoClear<ufp2048>;

DMibTraitsImplementSizePair(ufp1024, ufp2048);

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
