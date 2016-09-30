// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp128.h"

typedef NMib::NMath::TCFloat<1, 19, 236> CIEEEFloat256;
typedef NMib::NMath::TCFloat<1, 19, 236, NMib::NMath::CNoImplicit, 0> CIEEEFloat256Emu;
typedef CIEEEFloat256 fp256;
typedef NMib::TCAutoClear<fp256> zfp256;
//typedef NMib::TCAutoClear<ufp256> zufp256;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp256)
#	include "Malterlib_Numeric_Float_StdLib_fp256.h"
#endif

namespace NMib::NTraits
{
	DMibTraitsImplementFloatFromSize(fp256);
	DMibTraitsImplementSizePair(fp128, fp256);
}

namespace NMib::NMath
{
	extern template class TCFloat<1, 19, 236>;
	extern template class TCFloat<1, 19, 236, CNoImplicit, 0>;
}
