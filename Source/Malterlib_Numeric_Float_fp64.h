// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp64)
#	include "Malterlib_Numeric_Float_StdLib_fp64.h"
#endif

namespace NMib
{
	namespace NMath
	{
		#ifdef DMibPCanDo_fp64
			extern template class TCFloat<1, 11, 52, pfp64, 0>;
			extern template class TCFloat<1, 11, 52, pfp64>;
		#else
			extern template class TCFloat<1, 11, 52>;
			extern template class TCFloat<1, 11, 52, CNoImplicit, 0>;
		#endif
	}
}
