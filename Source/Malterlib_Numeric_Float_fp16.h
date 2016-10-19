// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp8.h"

#ifdef DMibPCanDo_fp16
typedef NMib::NMath::TCFloat<1, 5, 10, pfp16> CIEEEFloat16;
typedef NMib::NMath::TCFloat<1, 4, 11, pfp16, 0> CIEEEFloat16Emu;
#else
typedef NMib::NMath::TCFloat<1, 5, 10> CIEEEFloat16;
typedef NMib::NMath::TCFloat<1, 4, 11, NMib::NMath::CNoImplicit, 0> CIEEEFloat16Emu;
#endif
typedef NMib::NMath::TCFloat<0, 5, 11> ufp16;
typedef CIEEEFloat16 fp16;
typedef NMib::TCAutoClear<fp16> zfp16;
typedef NMib::TCAutoClear<ufp16> zufp16;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp16)
#	include "Malterlib_Numeric_Float_StdLib_fp16.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp16);
	DMibTraitsImplementSizePair(fp8, fp16);
}

namespace NMib::NMath
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp16
		extern template class TCFloat<1, 5, 10, pfp16>;
		extern template class TCFloat<1, 4, 11, pfp16, 0>;
	#else
		extern template class TCFloat<1, 5, 10>;
		extern template class TCFloat<1, 4, 11, CNoImplicit, 0>;
	#endif
	extern template class TCFloat<0, 5, 11>;
#endif
}
