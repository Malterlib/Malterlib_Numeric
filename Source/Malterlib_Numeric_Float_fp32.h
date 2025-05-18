// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp16.h"

#ifdef DMibPCanDo_fp32
using CIEEEFloat32 = NMib::NNumeric::TCFloat<1, 8, 23, pfp32>;
using CIEEEFloat32Emu = NMib::NNumeric::TCFloat<1, 8, 23, pfp32, 0>;
DMibNumericImplementImplicitFloatFromParams(1, 8, 23, pfp32);
#else
using CIEEEFloat32 = NMib::NNumeric::TCFloat<1, 8, 23>;
using CIEEEFloat32Emu = NMib::NNumeric::TCFloat<1, 8, 23, NMib::NNumeric::CNoImplicit, 0>;
#endif
using fp32 = CIEEEFloat32;
using zfp32 = NMib::TCAutoClear<fp32>;

DMibTraitsImplementFloatFromSize(fp32);
DMibTraitsImplementSizePair(fp16, fp32);

