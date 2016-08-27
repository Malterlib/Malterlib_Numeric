// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp4096)
#	include "Malterlib_Numeric_Float_StdLib_fp4096.h"
#endif

namespace NMib
{
	namespace NMath
	{
		extern template class TCFloat<1, 63, 4096-64>;
		extern template class TCFloat<1, 63, 4096-64, CNoImplicit, 0>;
	}
}
