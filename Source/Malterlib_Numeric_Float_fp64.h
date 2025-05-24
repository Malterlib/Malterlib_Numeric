// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"
#include "Malterlib_Numeric_Float_fp32.h"

#ifdef DMibPCanDo_fp64
using CIEEEFloat64Emu = NMib::NNumeric::TCFloat<1, 11, 52, 0, pfp64, 0>;
using CIEEEFloat64 = NMib::NNumeric::TCFloat<1, 11, 52, 0, pfp64>;
DMibNumericImplementImplicitFloatFromParams(1, 11, 52, 0, pfp64);
#else
using CIEEEFloat64 = NMib::NNumeric::TCFloat<1, 11, 52, 0>;
using CIEEEFloat64Emu = NMib::NNumeric::TCFloat<1, 11, 52, 0, NMib::NNumeric::CNoImplicit, 0>;
#endif
using fp64 = CIEEEFloat64;
using zfp64 = NMib::TCAutoClear<fp64>;

#if defined(DArchitecture_x86) && defined(DPlatformFamily_Windows) || defined(DArchitecture_x64) || defined(DArchitecture_arm64) || defined(DArchitecture_arm64e)
static_assert(alignof(pfp64) == 8);
static_assert(alignof(fp64) == 8);
#elif defined(DArchitecture_x86)
static_assert(alignof(pfp64) == 4);
static_assert(alignof(fp64) == 4);
#endif

DMibTraitsImplementFloatFromSize(fp64);
DMibTraitsImplementSizePair(fp32, fp64);
