// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp8.h"

#ifdef DMibPCanDo_fp16
using CIEEEFloat16 = NMib::NNumeric::TCFloat<1, 5, 10, 0, pfp16>;
using CIEEEFloat16Emu = NMib::NNumeric::TCFloat<1, 4, 11, 0, pfp16, 0>;
DMibNumericImplementImplicitFloatFromParams(1, 4, 11, 0, pfp16);
#else
using CIEEEFloat16 = NMib::NNumeric::TCFloat<1, 5, 10, 0>;
using CIEEEFloat16Emu = NMib::NNumeric::TCFloat<1, 4, 11, 0, NMib::NNumeric::CNoImplicit, 0>;
#endif
using fp16 = CIEEEFloat16;
using zfp16 = NMib::TCAutoClear<fp16>;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp16)
#	include "Malterlib_Numeric_Float_StdLib_fp16.h"
#endif

DMibTraitsImplementFloatFromSize(fp16);
DMibTraitsImplementSizePair(fp8, fp16);

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp16
		extern template class TCFloat<1, 5, 10, 0, pfp16>;
		extern template class TCFloat<1, 4, 11, 0, pfp16, 0>;
	#else
		extern template class TCFloat<1, 5, 10, 0>;
		extern template class TCFloat<1, 4, 11, 0, CNoImplicit, 0>;
	#endif
	extern template class TCFloat<0, 5, 11, 0>;
#endif
}
