// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp128.h"

using CIEEEFloat256 = NMib::NNumeric::TCFloat<1, 19, 236>;
using CIEEEFloat256Emu = NMib::NNumeric::TCFloat<1, 19, 236, NMib::NNumeric::CNoImplicit, 0>;
using fp256 = CIEEEFloat256;
using zfp256 = NMib::TCAutoClear<fp256>;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp256)
#	include "Malterlib_Numeric_Float_StdLib_fp256.h"
#endif

DMibTraitsImplementFloatFromSize(fp256);
DMibTraitsImplementSizePair(fp128, fp256);

namespace NMib::NNumeric
{
#ifndef DMibFloattDoInline_NoExternTemplate
	extern template class TCFloat<1, 19, 236>;
	extern template class TCFloat<1, 19, 236, CNoImplicit, 0>;
#endif
}
