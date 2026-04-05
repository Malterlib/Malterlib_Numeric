// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

using ufp8 = NMib::NNumeric::TCFloat<0, 3, 5, 0>;
using zufp8 = NMib::TCAutoClear<ufp8>;
