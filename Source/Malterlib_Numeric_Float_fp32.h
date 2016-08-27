// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp32)
#	include "Malterlib_Numeric_Float_StdLib_fp32.h"
#endif

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp32
			extern template class TCFloat<1, 8, 23, pfp32>;
			extern template class TCFloat<1, 8, 23, pfp32, 0>;
		#else
			extern template class TCFloat<1, 8, 23>;
			extern template class TCFloat<1, 8, 23, CNoImplicit, 0>;
		#endif
		extern template class TCFloat<0, 8, 24>;
	}
}
