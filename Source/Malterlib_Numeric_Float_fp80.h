// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

#ifdef DMibPCanDo_fp80
constexpr static umint gc_FloatPaddingBits_fp80 = sizeof(pfp80) * 8 - 80;
using CIEEEFloat80 = NMib::NNumeric::TCFloat<1, 15, 63, gc_FloatPaddingBits_fp80, pfp80>;
using CIEEEFloat80Emu = NMib::NNumeric::TCFloat<1, 15, 63, gc_FloatPaddingBits_fp80, pfp80, 0>;
DMibNumericImplementImplicitFloatFromParams(1, 15, 63, gc_FloatPaddingBits_fp80, pfp80);
#else
constexpr static umint gc_FloatPaddingBits_fp80 = 0;
using CIEEEFloat80 = NMib::NNumeric::TCFloat<1, 15, 63, 0>;
using CIEEEFloat80Emu = NMib::NNumeric::TCFloat<1, 15, 63, 0, NMib::NNumeric::CNoImplicit, 0>;
#endif
using fp80 = CIEEEFloat80;
using zfp80 = NMib::TCAutoClear<fp80>;

template <>
struct NMib::NTraits::NPrivate::TCFloatFromSize<80/8>
{
	using CType = fp80;
};
