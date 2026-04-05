// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp512.h"

using ufp1024 = NMib::NNumeric::TCFloat<0, 63, 1024-63, 0>;
using zufp1024 = NMib::TCAutoClear<ufp1024>;

DMibTraitsImplementSizePair(ufp512, ufp1024);

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
