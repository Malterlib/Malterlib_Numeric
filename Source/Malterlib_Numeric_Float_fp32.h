// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp16.h"

#ifdef DMibPCanDo_fp32
typedef NMib::NNumeric::TCFloat<1, 8, 23, pfp32> CIEEEFloat32;
typedef NMib::NNumeric::TCFloat<1, 8, 23, pfp32, 0> CIEEEFloat32Emu;
#else
typedef NMib::NNumeric::TCFloat<1, 8, 23> CIEEEFloat32;
typedef NMib::NNumeric::TCFloat<1, 8, 23, NMib::NNumeric::CNoImplicit, 0> CIEEEFloat32Emu;
#endif
typedef NMib::NNumeric::TCFloat<0, 8, 24> ufp32;
typedef CIEEEFloat32 fp32;
typedef NMib::TCAutoClear<fp32> zfp32;
typedef NMib::TCAutoClear<ufp32> zufp32;

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp32);
	DMibTraitsImplementSizePair(fp16, fp32);
}

