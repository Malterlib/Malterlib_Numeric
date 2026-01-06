// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp64.h"

#ifdef DMibPCanDo_fp128
using CIEEEFloat128 = NMib::NNumeric::TCFloat<1, 15, 112, 0, pfp128>;
using CIEEEFloat128Emu = NMib::NNumeric::TCFloat<1, 15, 112, 0, pfp128, 0>;
DMibNumericImplementImplicitFloatFromParams(1, 15, 112, 0, pfp128);
#else
using CIEEEFloat128 = NMib::NNumeric::TCFloat<1, 15, 112, 0>;
using CIEEEFloat128Emu = NMib::NNumeric::TCFloat<1, 15, 112, 0, NMib::NNumeric::CNoImplicit, 0>;
#endif
using fp128 = CIEEEFloat128;
using zfp128 = NMib::TCAutoClear<fp128>;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp128)
#	include "Malterlib_Numeric_Float_StdLib_fp128.h"
#endif

DMibTraitsImplementFloatFromSize(fp128);
DMibTraitsImplementSizePair(fp64, fp128);

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp128
		extern template class TCFloat<1, 15, 112, 0, pfp128>;
		extern template class TCFloat<1, 15, 112, 0, pfp128, 0>;
	#else
		extern template class TCFloat<1, 15, 112, 0>;
		extern template class TCFloat<1, 15, 112, 0, CNoImplicit, 0>;
	#endif
#endif
}
