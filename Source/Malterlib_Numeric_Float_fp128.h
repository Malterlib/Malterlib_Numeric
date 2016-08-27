// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp128)
#	include "Malterlib_Numeric_Float_StdLib_fp128.h"
#endif

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp128
			extern template class TCFloat<1, 15, 112, pfp128>;
			extern template class TCFloat<1, 15, 112, pfp128, 0>;
		#else
			extern template class TCFloat<1, 15, 112>;
			extern template class TCFloat<1, 15, 112, CNoImplicit, 0>;
		#endif
	}
}
