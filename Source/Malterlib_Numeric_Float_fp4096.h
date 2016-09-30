// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp2048.h"

typedef NMib::NMath::TCFloat<1, 63, 4096-64> CIEEEFloat4096;
typedef NMib::NMath::TCFloat<1, 63, 4096-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat4096Emu;
typedef CIEEEFloat4096 fp4096;
typedef NMib::TCAutoClear<fp4096> zfp4096;
//typedef NMib::TCAutoClear<ufp4096> zufp4096;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp4096)
#	include "Malterlib_Numeric_Float_StdLib_fp4096.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp4096);
	DMibTraitsImplementSizePair(fp2048, fp4096);
}

namespace NMib::NMath
{
	extern template class TCFloat<1, 63, 4096-64>;
	extern template class TCFloat<1, 63, 4096-64, CNoImplicit, 0>;
}
