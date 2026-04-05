// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp32)
#	include "Malterlib_Numeric_Float_StdLib_fp32.h"
#endif

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp64)
#	include "Malterlib_Numeric_Float_StdLib_fp64.h"
#endif

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp80)
#	include "Malterlib_Numeric_Float_StdLib_fp80.h"
#endif

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp32
		extern template class TCFloat<1, 8, 23, 0, pfp32>;
		extern template class TCFloat<1, 8, 23, 0, pfp32, 0>;
	#else
		extern template class TCFloat<1, 8, 23, 0>;
		extern template class TCFloat<1, 8, 23, 0, CNoImplicit, 0>;
	#endif
	extern template class TCFloat<0, 8, 24, 0>;
#endif
}

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp64
		extern template class TCFloat<1, 11, 52, 0, pfp64, 0>;
		extern template class TCFloat<1, 11, 52, 0, pfp64>;
	#else
		extern template class TCFloat<1, 11, 52, 0>;
		extern template class TCFloat<1, 11, 52, 0, CNoImplicit, 0>;
	#endif
	extern template class TCFloat<0, 11, 53, 0>;
#endif
}

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp80
		extern template class TCFloat<1, 15, 63, gc_FloatPaddingBits_fp80, pfp80>;
		extern template class TCFloat<1, 15, 63, gc_FloatPaddingBits_fp80, pfp80, 0>;
	#else
		extern template class TCFloat<1, 15, 63, 0>;
		extern template class TCFloat<1, 15, 63, 0, CNoImplicit, 0>;
	#endif
#endif
}
