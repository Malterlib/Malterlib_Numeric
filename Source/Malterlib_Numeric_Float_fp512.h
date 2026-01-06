// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp256.h"

using CIEEEFloat512 = NMib::NNumeric::TCFloat<1, 63, 512-64, 0>;
using CIEEEFloat512Emu = NMib::NNumeric::TCFloat<1, 63, 512-64, 0, NMib::NNumeric::CNoImplicit, 0>;
using fp512 = CIEEEFloat512;
using zfp512 = NMib::TCAutoClear<fp512>;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp512)
#	include "Malterlib_Numeric_Float_StdLib_fp512.h"
#endif

DMibTraitsImplementFloatFromSize(fp512);
DMibTraitsImplementSizePair(fp256, fp512);

namespace NMib::NNumeric
{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
	extern template class TCFloat<1, 63, 512-64, 0>;
	extern template class TCFloat<1, 63, 512-64, 0, CNoImplicit, 0>;
#endif
}

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
