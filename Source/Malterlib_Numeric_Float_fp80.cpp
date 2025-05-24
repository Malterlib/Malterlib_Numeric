// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp80.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp80
		template class TCFloat<1, 15, 63, gc_FloatPaddingBits_fp80, pfp80>;
		template class TCFloat<1, 15, 63, gc_FloatPaddingBits_fp80, pfp80, 0>;
	#else
		template class TCFloat<1, 15, 63, 0>;
		template class TCFloat<1, 15, 63, 0, CNoImplicit, 0>;
	#endif
#endif
}
