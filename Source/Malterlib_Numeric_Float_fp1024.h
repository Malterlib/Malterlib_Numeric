// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp512.h"

typedef NMib::NNumeric::TCFloat<1, 63, 1024-64> CIEEEFloat1024;
typedef NMib::NNumeric::TCFloat<1, 63, 1024-64, NMib::NNumeric::CNoImplicit, 0> CIEEEFloat1024Emu;
typedef CIEEEFloat1024 fp1024;
typedef NMib::TCAutoClear<fp1024> zfp1024;
//typedef NMib::TCAutoClear<ufp1024> zufp1024;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp1024)
#	include "Malterlib_Numeric_Float_StdLib_fp1024.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp1024);
	DMibTraitsImplementSizePair(fp512, fp1024);
}

namespace NMib::NNumeric
{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
	extern template class TCFloat<1, 63, 1024-64>;
	extern template class TCFloat<1, 63, 1024-64, CNoImplicit, 0>;
#endif
}

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
