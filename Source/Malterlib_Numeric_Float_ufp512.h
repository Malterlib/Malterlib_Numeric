// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_ufp256.h"

using ufp512 = NMib::NNumeric::TCFloat<0, 63, 512-63, 0>;
using zufp512 = NMib::TCAutoClear<ufp512>;

DMibTraitsImplementSizePair(ufp256, ufp512);

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
