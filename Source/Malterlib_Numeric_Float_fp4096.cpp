// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include "Malterlib_Numeric_Float_fp4096.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib::NNumeric
{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
	template class TCFloat<1, 63, 4096-64, 0>;
	template class TCFloat<1, 63, 4096-64, 0, CNoImplicit, 0>;
#endif
}
