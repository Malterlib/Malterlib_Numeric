// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp80)
#	include "Malterlib_Numeric_Float_StdLib_fp80.h"
#endif

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp80
			extern template class TCFloat<1, 15, 63, pfp80>;
			extern template class TCFloat<1, 15, 63, pfp80, 0>;
		#else
			extern template class TCFloat<1, 15, 63>;
			extern template class TCFloat<1, 15, 63, CNoImplicit, 0>;
		#endif
	}
}
