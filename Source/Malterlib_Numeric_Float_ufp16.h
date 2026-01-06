// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp8.h"

using ufp16 = NMib::NNumeric::TCFloat<0, 5, 11, 0>;
using zufp16 = NMib::TCAutoClear<ufp16>;

DMibTraitsImplementSizePair(ufp8, ufp16);
