// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Numeric_Float_fp256.h"
#include "Malterlib_Numeric_Float.hpp"

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	template class TCFloat<1, 19, 236, 0>;
	template class TCFloat<1, 19, 236, 0, CNoImplicit, 0>;
#endif
}
