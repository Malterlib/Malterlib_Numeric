// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp8.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp8
			template class TCFloat<1, 3, 4, pfp8>;
			template class TCFloat<1, 2, 5, pfp8, 0>;
		#else
			template class TCFloat<1, 3, 4>;
			template class TCFloat<1, 2, 5, CNoImplicit, 0>;
		#endif
		template class TCFloat<0, 3, 5>;
	}
}
