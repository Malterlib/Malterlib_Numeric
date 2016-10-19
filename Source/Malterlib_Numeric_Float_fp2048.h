// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp1024.h"

typedef NMib::NMath::TCFloat<1, 63, 2048-64> CIEEEFloat2048;
typedef NMib::NMath::TCFloat<1, 63, 2048-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat2048Emu;
typedef CIEEEFloat2048 fp2048;
typedef NMib::TCAutoClear<fp2048> zfp2048;
//typedef NMib::TCAutoClear<ufp2048> zufp2048;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp2048)
#	include "Malterlib_Numeric_Float_StdLib_fp2048.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp2048);
	DMibTraitsImplementSizePair(fp1024, fp2048);
}

namespace NMib::NMath
{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
	extern template class TCFloat<1, 63, 2048-64>;
	extern template class TCFloat<1, 63, 2048-64, CNoImplicit, 0>;
#endif
}

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
