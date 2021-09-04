// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp32.h"

#ifdef DMibPCanDo_fp64
typedef NMib::NNumeric::TCFloat<1, 11, 52, pfp64, 0> CIEEEFloat64Emu;
typedef NMib::NNumeric::TCFloat<1, 11, 52, pfp64> CIEEEFloat64;
#else
typedef NMib::NNumeric::TCFloat<1, 11, 52> CIEEEFloat64;
typedef NMib::NNumeric::TCFloat<1, 11, 52, NMib::NNumeric::CNoImplicit, 0> CIEEEFloat64Emu;
#endif
typedef CIEEEFloat64 fp64;
typedef NMib::TCAutoClear<fp64> zfp64;
//typedef NMib::TCAutoClear<ufp64> zufp64;

#if defined(DArchitecture_x86) || defined(DArchitecture_x64) || defined(DArchitecture_arm64) || defined(DArchitecture_arm64e)
static_assert(NMib::NTraits::TCAlignmentOf<pfp64>::mc_Value == 8);
static_assert(NMib::NTraits::TCAlignmentOf<fp64>::mc_Value == 8);
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp64);
	DMibTraitsImplementSizePair(fp32, fp64);
}
