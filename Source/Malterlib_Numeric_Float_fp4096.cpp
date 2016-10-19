// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp4096.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib
{
	namespace NMath
	{
#ifndef DMibFloattDoInline_NoExternTemplate
		template class TCFloat<1, 63, 4096-64>;
		template class TCFloat<1, 63, 4096-64, CNoImplicit, 0>;
#endif
	}
}
