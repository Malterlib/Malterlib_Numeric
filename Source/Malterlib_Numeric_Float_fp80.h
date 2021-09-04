// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#ifdef DMibPCanDo_fp80
typedef NMib::NNumeric::TCFloat<1, 15, 63, pfp80> CIEEEFloat80;
typedef NMib::NNumeric::TCFloat<1, 15, 63, pfp80, 0> CIEEEFloat80Emu;
#else
typedef NMib::NNumeric::TCFloat<1, 15, 63> CIEEEFloat80;
typedef NMib::NNumeric::TCFloat<1, 15, 63, NMib::NNumeric::CNoImplicit, 0> CIEEEFloat80Emu;
#endif
typedef CIEEEFloat80 fp80;
typedef NMib::TCAutoClear<fp80> zfp80;
//typedef NMib::TCAutoClear<ufp80> zufp80;

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp80);
}
