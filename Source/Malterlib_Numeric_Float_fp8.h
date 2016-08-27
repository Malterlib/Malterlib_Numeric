// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp8)
#	include "Malterlib_Numeric_Float_StdLib_fp8.h"
#endif

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp8
			extern template class TCFloat<1, 3, 4, pfp8>;
			extern template class TCFloat<1, 2, 5, pfp8, 0>;
		#else
			extern template class TCFloat<1, 3, 4>;
			extern template class TCFloat<1, 2, 5, CNoImplicit, 0>;
		#endif
		extern template class TCFloat<0, 3, 5>;
	}
}
