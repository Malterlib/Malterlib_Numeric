// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp512.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib
{
	namespace NMath
	{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
		template class TCFloat<1, 63, 512-64>;
		template class TCFloat<1, 63, 512-64, CNoImplicit, 0>;
#endif
	}
}
