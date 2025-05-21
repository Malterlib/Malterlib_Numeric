// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#ifdef DMibPCanDo_fp80
using CIEEEFloat80 = NMib::NNumeric::TCFloat<1, 15, 63, pfp80>;
using CIEEEFloat80Emu = NMib::NNumeric::TCFloat<1, 15, 63, pfp80, 0>;
DMibNumericImplementImplicitFloatFromParams(1, 15, 63, pfp80);
#else
using CIEEEFloat80 = NMib::NNumeric::TCFloat<1, 15, 63>;
using CIEEEFloat80Emu = NMib::NNumeric::TCFloat<1, 15, 63, NMib::NNumeric::CNoImplicit, 0>;
#endif
using fp80 = CIEEEFloat80;
using zfp80 = NMib::TCAutoClear<fp80>;

DMibTraitsImplementFloatFromSize(fp80);

