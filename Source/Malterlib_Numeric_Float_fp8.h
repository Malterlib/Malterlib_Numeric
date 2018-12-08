// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#ifdef DMibPCanDo_fp8
typedef NMib::NNumeric::TCFloat<1, 3, 4, pfp8> CIEEEFloat8;
typedef NMib::NNumeric::TCFloat<1, 2, 5, pfp8, 0> CIEEEFloat8Emu;
#else
typedef NMib::NNumeric::TCFloat<1, 3, 4> CIEEEFloat8;
typedef NMib::NNumeric::TCFloat<1, 2, 5, NMib::NNumeric::CNoImplicit, 0> CIEEEFloat8Emu;
#endif
typedef NMib::NNumeric::TCFloat<0, 3, 5> ufp8;
typedef CIEEEFloat8 fp8;
typedef NMib::TCAutoClear<fp8> zfp8;
typedef NMib::TCAutoClear<ufp8> zufp8;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp8)
#	include "Malterlib_Numeric_Float_StdLib_fp8.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp8);
}

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp8
		extern template class TCFloat<1, 3, 4, pfp8>;
		extern template class TCFloat<1, 2, 5, pfp8, 0>;
	#else
		extern template class TCFloat<1, 3, 4>;
		extern template class TCFloat<1, 2, 5, CNoImplicit, 0>;
	#endif
	extern template class TCFloat<0, 3, 5>;
#endif
}
