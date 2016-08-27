// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp32.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp32
			template class TCFloat<1, 8, 23, pfp32>;
			template class TCFloat<1, 8, 23, pfp32, 0>;
		#else
			template class TCFloat<1, 8, 23>;
			template class TCFloat<1, 8, 23, CNoImplicit, 0>;
		#endif
		template class TCFloat<0, 8, 24>;
	}
}
