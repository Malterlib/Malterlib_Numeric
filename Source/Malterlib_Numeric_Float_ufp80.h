// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp80.h"

using ufp80 = NMib::NNumeric::TCFloat<0, 15, 64, gc_FloatPaddingBits_fp80>;
using zufp80 = NMib::TCAutoClear<ufp80>;
