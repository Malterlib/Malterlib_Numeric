// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Numeric_Float_fp2048.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib::NNumeric
{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
	template class TCFloat<1, 63, 2048-64, 0>;
	template class TCFloat<1, 63, 2048-64, 0, CNoImplicit, 0>;
#endif
}
