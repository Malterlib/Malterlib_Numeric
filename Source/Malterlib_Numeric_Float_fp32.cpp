// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Numeric_Float_fp32.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
#	ifdef DMibPCanDo_fp32
	template struct TCFloat<1, 8, 23, 0, pfp32>;
	template struct TCFloat<1, 8, 23, 0, pfp32, 0>;
#	else
	template struct TCFloat<1, 8, 23, 0>;
	template struct TCFloat<1, 8, 23, 0, CNoImplicit, 0>;
#	endif
	template struct TCFloat<0, 8, 24, 0>;
#endif
}
