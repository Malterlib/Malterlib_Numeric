// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp64.h"

#ifdef DMibPCanDo_fp128
typedef NMib::NMath::TCFloat<1, 15, 112, pfp128> CIEEEFloat128;
typedef NMib::NMath::TCFloat<1, 15, 112, pfp128, 0> CIEEEFloat128Emu;
#else
typedef NMib::NMath::TCFloat<1, 15, 112> CIEEEFloat128;
typedef NMib::NMath::TCFloat<1, 15, 112, NMib::NMath::CNoImplicit, 0> CIEEEFloat128Emu;
#endif
typedef CIEEEFloat128 fp128;
typedef NMib::TCAutoClear<fp128> zfp128;
//typedef NMib::TCAutoClear<ufp128> zufp128;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp128)
#	include "Malterlib_Numeric_Float_StdLib_fp128.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp128);
	DMibTraitsImplementSizePair(fp64, fp128);
}

namespace NMib::NMath
{
	#ifdef DMibPCanDo_fp128
		extern template class TCFloat<1, 15, 112, pfp128>;
		extern template class TCFloat<1, 15, 112, pfp128, 0>;
	#else
		extern template class TCFloat<1, 15, 112>;
		extern template class TCFloat<1, 15, 112, CNoImplicit, 0>;
	#endif
}
