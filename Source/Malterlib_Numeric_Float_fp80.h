// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#ifdef DMibPCanDo_fp80
typedef NMib::NMath::TCFloat<1, 15, 63, pfp80> CIEEEFloat80;
typedef NMib::NMath::TCFloat<1, 15, 63, pfp80, 0> CIEEEFloat80Emu;
#else
typedef NMib::NMath::TCFloat<1, 15, 63> CIEEEFloat80;
typedef NMib::NMath::TCFloat<1, 15, 63, NMib::NMath::CNoImplicit, 0> CIEEEFloat80Emu;
#endif
typedef CIEEEFloat80 fp80;
typedef NMib::TCAutoClear<fp80> zfp80;
//typedef NMib::TCAutoClear<ufp80> zufp80;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp80)
#	include "Malterlib_Numeric_Float_StdLib_fp80.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp80);
}

namespace NMib::NMath
{
	#ifdef DMibPCanDo_fp80
		extern template class TCFloat<1, 15, 63, pfp80>;
		extern template class TCFloat<1, 15, 63, pfp80, 0>;
	#else
		extern template class TCFloat<1, 15, 63>;
		extern template class TCFloat<1, 15, 63, CNoImplicit, 0>;
	#endif
}
