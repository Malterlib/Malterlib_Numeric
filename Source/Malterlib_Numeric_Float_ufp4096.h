// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp2048.h"

using ufp4096 = NMib::NNumeric::TCFloat<0, 63, 4096-63, 0>;
using zufp4096 = NMib::TCAutoClear<ufp4096>;

DMibTraitsImplementSizePair(ufp2048, ufp4096);

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
