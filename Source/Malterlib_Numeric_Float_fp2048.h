// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp1024.h"

using CIEEEFloat2048 = NMib::NNumeric::TCFloat<1, 63, 2048-64, 0>;
using CIEEEFloat2048Emu = NMib::NNumeric::TCFloat<1, 63, 2048-64, 0, NMib::NNumeric::CNoImplicit, 0>;
using fp2048 = CIEEEFloat2048;
using zfp2048 = NMib::TCAutoClear<fp2048>;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp2048)
#	include "Malterlib_Numeric_Float_StdLib_fp2048.h"
#endif

DMibTraitsImplementFloatFromSize(fp2048);
DMibTraitsImplementSizePair(fp1024, fp2048);

namespace NMib::NNumeric
{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
	extern template class TCFloat<1, 63, 2048-64, 0>;
	extern template class TCFloat<1, 63, 2048-64, 0, CNoImplicit, 0>;
#endif
}

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
