// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp16.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp16
		template class TCFloat<1, 5, 10, pfp16>;
		template class TCFloat<1, 4, 11, pfp16, 0>;
	#else
		template class TCFloat<1, 5, 10>;
		template class TCFloat<1, 4, 11, CNoImplicit, 0>;
	#endif
	template class TCFloat<0, 5, 11>;
#endif
}
