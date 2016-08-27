// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp16)
#	include "Malterlib_Numeric_Float_StdLib_fp16.h"
#endif

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp16
			extern template class TCFloat<1, 5, 10, pfp16>;
			extern template class TCFloat<1, 4, 11, pfp16, 0>;
		#else
			extern template class TCFloat<1, 5, 10>;
			extern template class TCFloat<1, 4, 11, CNoImplicit, 0>;
		#endif
		extern template class TCFloat<0, 5, 11>;
	}
}
