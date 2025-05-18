// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#ifdef DMibPCanDo_fp8
using CIEEEFloat8 = NMib::NNumeric::TCFloat<1, 3, 4, pfp8>;
using CIEEEFloat8Emu = NMib::NNumeric::TCFloat<1, 2, 5, pfp8, 0>;
DMibNumericImplementImplicitFloatFromParams(1, 3, 4, pfp8);
#else
using CIEEEFloat8 = NMib::NNumeric::TCFloat<1, 3, 4>;
using CIEEEFloat8Emu = NMib::NNumeric::TCFloat<1, 2, 5, NMib::NNumeric::CNoImplicit, 0>;
#endif
using fp8 = CIEEEFloat8;
using zfp8 = NMib::TCAutoClear<fp8>;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp8)
#	include "Malterlib_Numeric_Float_StdLib_fp8.h"
#endif

DMibTraitsImplementFloatFromSize(fp8);

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
