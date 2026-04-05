// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Numeric_Float_fp8.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp8
		template class TCFloat<1, 3, 4, 0, pfp8>;
		template class TCFloat<1, 2, 5, 0, pfp8, 0>;
	#else
		template class TCFloat<1, 3, 4, 0>;
		template class TCFloat<1, 2, 5, 0, CNoImplicit, 0>;
	#endif
	template class TCFloat<0, 3, 5, 0>;
#endif
}
