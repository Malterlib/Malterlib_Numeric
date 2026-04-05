// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp2048.h"

using CIEEEFloat4096 = NMib::NNumeric::TCFloat<1, 63, 4096-64, 0>;
using CIEEEFloat4096Emu = NMib::NNumeric::TCFloat<1, 63, 4096-64, 0, NMib::NNumeric::CNoImplicit, 0>;
using fp4096 = CIEEEFloat4096;
using zfp4096 = NMib::TCAutoClear<fp4096>;

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp4096)
#	include "Malterlib_Numeric_Float_StdLib_fp4096.h"
#endif

DMibTraitsImplementFloatFromSize(fp4096);
DMibTraitsImplementSizePair(fp2048, fp4096);

namespace NMib::NNumeric
{
#if !defined(DMibFloattDoInline_NoExternTemplate) && defined(DMibDebug)
	extern template class TCFloat<1, 63, 4096-64, 0>;
	extern template class TCFloat<1, 63, 4096-64, 0, CNoImplicit, 0>;
#endif
}

#if !defined(DMibDebug)
#include "Malterlib_Numeric_Float.hpp"
#endif
