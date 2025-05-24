// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp128.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	#ifdef DMibPCanDo_fp128
		template class TCFloat<1, 15, 112, 0, pfp128>;
		template class TCFloat<1, 15, 112, 0, pfp128, 0>;
	#else
		template class TCFloat<1, 15, 112, 0>;
		template class TCFloat<1, 15, 112, 0, CNoImplicit, 0>;
	#endif
#endif
}
