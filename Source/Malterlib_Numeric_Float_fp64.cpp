// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp64.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp64
			template class TCFloat<1, 11, 52, pfp64, 0>;
			template class TCFloat<1, 11, 52, pfp64>;
		#else
			template class TCFloat<1, 11, 52>;
			template class TCFloat<1, 11, 52, CNoImplicit, 0>;
		#endif
	}
}
