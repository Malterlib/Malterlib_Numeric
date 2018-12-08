// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp256.h"

typedef NMib::NNumeric::TCFloat<1, 63, 512-64> CIEEEFloat512;
typedef NMib::NNumeric::TCFloat<1, 63, 512-64, NMib::NNumeric::CNoImplicit, 0> CIEEEFloat512Emu;
typedef CIEEEFloat512 fp512;
typedef NMib::TCAutoClear<fp512> zfp512;
//typedef NMib::TCAutoClear<ufp512> zufp512;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp512)
#	include "Malterlib_Numeric_Float_StdLib_fp512.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp512);
	DMibTraitsImplementSizePair(fp256, fp512);
}

namespace NMib::NNumeric
{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
	extern template class TCFloat<1, 63, 512-64>;
	extern template class TCFloat<1, 63, 512-64, CNoImplicit, 0>;
#endif
}

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
