// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp32.h"

#ifdef DMibPCanDo_fp64
typedef NMib::NMath::TCFloat<1, 11, 52, pfp64, 0> CIEEEFloat64Emu;
typedef NMib::NMath::TCFloat<1, 11, 52, pfp64> CIEEEFloat64;
#else
typedef NMib::NMath::TCFloat<1, 11, 52> CIEEEFloat64;
typedef NMib::NMath::TCFloat<1, 11, 52, NMib::NMath::CNoImplicit, 0> CIEEEFloat64Emu;
#endif
typedef CIEEEFloat64 fp64;
typedef NMib::TCAutoClear<fp64> zfp64;
//typedef NMib::TCAutoClear<ufp64> zufp64;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp64)
#	include "Malterlib_Numeric_Float_StdLib_fp64.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp64);
	DMibTraitsImplementSizePair(fp32, fp64);
}

namespace NMib::NMath
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp64
		extern template class TCFloat<1, 11, 52, pfp64, 0>;
		extern template class TCFloat<1, 11, 52, pfp64>;
	#else
		extern template class TCFloat<1, 11, 52>;
		extern template class TCFloat<1, 11, 52, CNoImplicit, 0>;
	#endif
#endif
}
