// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp128.h"

using ufp256 = NMib::NNumeric::TCFloat<0, 19, 237, 0>;
using zufp256 = NMib::TCAutoClear<ufp256>;

DMibTraitsImplementSizePair(ufp128, ufp256);
