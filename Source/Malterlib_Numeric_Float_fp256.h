// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp256)
#	include "Malterlib_Numeric_Float_StdLib_fp256.h"
#endif

namespace NMib
{
	namespace NMath
	{
		extern template class TCFloat<1, 19, 236>;
		extern template class TCFloat<1, 19, 236, CNoImplicit, 0>;
	}
}
