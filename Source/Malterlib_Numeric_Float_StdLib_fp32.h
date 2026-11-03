// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NSys::NNumeric
{
	pfp32 fg_Sin(pfp32 _Val);
	pfp32 fg_Cos(pfp32 _Val);
	pfp32 fg_Tan(pfp32 _Val);
	pfp32 fg_SinH(pfp32 _Val);
	pfp32 fg_CosH(pfp32 _Val);
	pfp32 fg_TanH(pfp32 _Val);
	pfp32 fg_ArcSin(pfp32 _Val);
	pfp32 fg_ArcCos(pfp32 _Val);
	pfp32 fg_ArcTan(pfp32 _Val);
	pfp32 fg_ArcTan(pfp32 _Val, pfp32 _Source);

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	pfp32 fg_ExpN(pfp32 _Val);
	pfp32 fg_LogN(pfp32 _Val);
	pfp32 fg_Exp10(pfp32 _Val);
	pfp32 fg_Log10(pfp32 _Val);
	pfp32 fg_Exp2(pfp32 _Val);
	pfp32 fg_Log2(pfp32 _Val);
	pfp32 fg_Exp(pfp32 _Val, pfp32 _Base);
	pfp32 fg_Log(pfp32 _Val, pfp32 _Base);
	pfp32 fg_Sqrt(pfp32 _Val);
	pfp32 fg_Pow(pfp32 _Val, pfp32 _Power);
	pfp32 fg_Floor(pfp32 _Val);
	pfp32 fg_Ceil(pfp32 _Val);
	pfp32 fg_Abs(pfp32 _Val);
	pfp32 fg_Mod(pfp32 _Val, pfp32 _Modulu);
}

#ifdef DCompiler_MSVC
#	pragma warning(disable : 4725) // Disable warning about erronous pentiums
#endif

/************************************************************************************************\
|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
| |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
| | fp32 (float)
| |_______________________________________________________________________________________________
|_________________________________________________________________________________________________|
\************************************************************************************************/

namespace NMib::NNumeric
{
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::fs_Zero();
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::fs_Half();
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::fs_One();
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::fs_Two();
	template <> DMibFloatConstexpr inline_small void CIEEEFloat32::fp_Set_0();
	template <> DMibFloatConstexpr inline_small void CIEEEFloat32::fp_Set_0_5();
	template <> DMibFloatConstexpr inline_small void CIEEEFloat32::fp_Set_1();
	template <> DMibFloatConstexpr inline_small void CIEEEFloat32::fp_Set_2();
	template <> inline_small void CIEEEFloat32::fp_Set_E();
	template <> inline_small void CIEEEFloat32::fp_Set_Pi();
	template <> inline_small void CIEEEFloat32::fp_Set_Euler();
	template <> inline_small void CIEEEFloat32::fp_Set_GoldenRatio();
	template <> inline_small void CIEEEFloat32::fp_Set_Sqrt2();
	template <> inline_small void CIEEEFloat32::fp_Set_Log2_10();
	template <> inline_small void CIEEEFloat32::fp_Set_Log10_2();
	template <> inline_small void CIEEEFloat32::fp_Set_Log2_E();
	template <> inline_small void CIEEEFloat32::fp_Set_LogE_2();

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by value operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::operator + (CIEEEFloat32 const &_Value) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::operator - (CIEEEFloat32 const &_Value) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::operator * (CIEEEFloat32 const &_Value) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::operator / (CIEEEFloat32 const &_Value) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::operator - () const;

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by reference operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat32 &CIEEEFloat32::operator += (CIEEEFloat32 const &_Value);
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 &CIEEEFloat32::operator -= (CIEEEFloat32 const &_Value);
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 &CIEEEFloat32::operator /= (CIEEEFloat32 const &_Value);
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 &CIEEEFloat32::operator *= (CIEEEFloat32 const &_Value);

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Trigomethric
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Sin() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Cos() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Tan() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_SinH() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_CosH() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_TanH() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_ArcSin() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_ArcCos() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_ArcTan() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_ArcTan(CIEEEFloat32 const &_Source) const;

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_ExpN() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_LogN() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Exp10() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Log10() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Exp2() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Log2() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Exp(CIEEEFloat32 const &_Base) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Log(CIEEEFloat32 const &_Base) const;

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Power
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Sqrt() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Sqr() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Pow(CIEEEFloat32 const &_Power) const;

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Integer functions
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat32::CInteger CIEEEFloat32::f_ToInt() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32::CUnsignedInteger CIEEEFloat32::f_ToUnsignedInt() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Floor() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Ceil() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Abs() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat32 CIEEEFloat32::f_Mod(TCFloat const &_Modulu) const;
	template <> DMibFloatConstexpr inline_small bool CIEEEFloat32::operator == (CIEEEFloat32 const &_Value) const noexcept;
	template <> DMibFloatConstexpr inline_small COrdering_Partial CIEEEFloat32::operator <=> (CIEEEFloat32 const &_Value) const noexcept;
}

namespace NMib
{
#define DMibDirectConvert(d_FromType, d_ToType) \
	template <>\
	struct TCConvert< d_ToType, d_FromType>\
	{\
		static DMibFloatConstexpr inline_small d_ToType fs_Convert( d_FromType const &_From)\
		{\
			return _From;\
		}\
	};

	DMibDirectConvert(pfp32, CIEEEFloat32);

#undef DMibDirectConvert

#define DMibMathFloatConvertNative(d_FromType, d_ToType) \
	template <>\
	struct TCConvert< d_ToType, d_FromType>\
	{\
		static DMibFloatConstexpr inline_small d_ToType fs_Convert( d_FromType const &_From)\
		{\
			return _From.f_Get();\
		}\
	};

	DMibMathFloatConvertNative(CIEEEFloat32, pfp32);

#undef DMibMathFloatConvertNative

#define DMibMathFloatConvertInt(d_FromType, d_ToType) \
	template <>\
	struct TCConvert< d_ToType, d_FromType >\
	{\
		static DMibFloatConstexpr inline_small d_ToType fs_Convert(d_FromType const &_From)\
		{\
			return NMib::fg_Convert<d_ToType>(_From.f_ToInt());\
		}\
	};\
	template <>\
	struct TCConvert< d_FromType, d_ToType >\
	{\
		static DMibFloatConstexpr inline_small d_FromType fs_Convert(d_ToType const &_From)\
		{\
			d_FromType Ret;\
			Ret.f_GetImplicit() = _From;\
			return Ret;\
		}\
	};

	DMibMathFloatConvertInt(CIEEEFloat32, int8);

#ifdef DMibPCanDo_int16
	DMibMathFloatConvertInt(CIEEEFloat32, int16);
#endif

#ifdef DMibPCanDo_uint16
	DMibMathFloatConvertInt(CIEEEFloat32, uint16);
#endif

#ifdef DMibPCanDo_int32
	DMibMathFloatConvertInt(CIEEEFloat32, int32);
#endif

#ifdef DMibPCanDo_uint32
	DMibMathFloatConvertInt(CIEEEFloat32, uint32);
#endif

#ifdef DMibPCanDo_int64
	DMibMathFloatConvertInt(CIEEEFloat32, int64);
#endif

#ifdef DMibPCanDo_uint64
	DMibMathFloatConvertInt(CIEEEFloat32, uint64);
#endif

#ifdef DMibPCanDo_int80
	DMibMathFloatConvertInt(CIEEEFloat32, int80);
#endif

#ifdef DMibPCanDo_uint80
	DMibMathFloatConvertInt(CIEEEFloat32, uint80);
#endif

#ifdef DMibPCanDo_int96
	DMibMathFloatConvertInt(CIEEEFloat32, int96);
#endif

#ifdef DMibPCanDo_uint96
	DMibMathFloatConvertInt(CIEEEFloat32, uint96);
#endif

#ifdef DMibPCanDo_int128
	DMibMathFloatConvertInt(CIEEEFloat32, int128);
#endif

#ifdef DMibPCanDo_uint128
	DMibMathFloatConvertInt(CIEEEFloat32, uint128);
#endif

#ifdef DMibPCanDo_int160
	DMibMathFloatConvertInt(CIEEEFloat32, int160);
#endif

#ifdef DMibPCanDo_uint160
	DMibMathFloatConvertInt(CIEEEFloat32, uint160);
#endif

#ifdef DMibPCanDo_int192
	DMibMathFloatConvertInt(CIEEEFloat32, int192);
#endif

#ifdef DMibPCanDo_uint192
	DMibMathFloatConvertInt(CIEEEFloat32, uint192);
#endif

#ifdef DMibPCanDo_int256
	DMibMathFloatConvertInt(CIEEEFloat32, int256);
#endif

#ifdef DMibPCanDo_uint256
	DMibMathFloatConvertInt(CIEEEFloat32, uint256);
#endif

#ifdef DMibPCanDo_int320
	DMibMathFloatConvertInt(CIEEEFloat32, int320);
#endif

#ifdef DMibPCanDo_uint320
	DMibMathFloatConvertInt(CIEEEFloat32, uint320);
#endif

#ifdef DMibPCanDo_int384
	DMibMathFloatConvertInt(CIEEEFloat32, int384);
#endif

#ifdef DMibPCanDo_uint384
	DMibMathFloatConvertInt(CIEEEFloat32, uint384);
#endif

#ifdef DMibPCanDo_int512
	DMibMathFloatConvertInt(CIEEEFloat32, int512);
#endif

#ifdef DMibPCanDo_uint512
	DMibMathFloatConvertInt(CIEEEFloat32, uint512);
#endif

#ifdef DMibPCanDo_int1024
	DMibMathFloatConvertInt(CIEEEFloat32, int1024);
#endif

#ifdef DMibPCanDo_uint1024
	DMibMathFloatConvertInt(CIEEEFloat32, uint1024);
#endif

#ifdef DMibPCanDo_int2048
	DMibMathFloatConvertInt(CIEEEFloat32, int2048);
#endif

#ifdef DMibPCanDo_uint2048
	DMibMathFloatConvertInt(CIEEEFloat32, uint2048);
#endif

#ifdef DMibPCanDo_int4096
	DMibMathFloatConvertInt(CIEEEFloat32, int4096);
#endif

#ifdef DMibPCanDo_uint4096
	DMibMathFloatConvertInt(CIEEEFloat32, uint4096);
#endif

#ifdef DMibPCanDo_int8192
	DMibMathFloatConvertInt(CIEEEFloat32, int8192);
#endif

#ifdef DMibPCanDo_uint8192
	DMibMathFloatConvertInt(CIEEEFloat32, uint8192);
#endif

#ifdef DMibPCanDo_int16384
	DMibMathFloatConvertInt(CIEEEFloat32, int16384);
#endif

#ifdef DMibPCanDo_uint16384
	DMibMathFloatConvertInt(CIEEEFloat32, uint16384);
#endif

#ifdef DMibPUniqueType_umint
	DMibMathFloatConvertInt(CIEEEFloat32, umint);
#endif
#ifdef DMibPUniqueType_smint
	DMibMathFloatConvertInt(CIEEEFloat32, smint);
#endif
#ifdef DMibPUniqueType_int
	DMibMathFloatConvertInt(CIEEEFloat32, int);
#endif
#ifdef DMibPUniqueType_uint
	DMibMathFloatConvertInt(CIEEEFloat32, unsigned int);
#endif
#ifdef DMibPUniqueType_aint
	DMibMathFloatConvertInt(CIEEEFloat32, aint);
#endif

#ifdef DMibPUniqueType_uaint
	DMibMathFloatConvertInt(CIEEEFloat32, uaint);
#endif

#ifdef DMibPUniqueType_ch8
	DMibMathFloatConvertInt(CIEEEFloat32, ch8);
#endif
#ifdef DMibPUniqueType_ch16
	DMibMathFloatConvertInt(CIEEEFloat32, ch16);
#endif
#ifdef DMibPUniqueType_ch32
	DMibMathFloatConvertInt(CIEEEFloat32, ch32);
#endif

#undef DMibMathFloatConvertInt
}

#include "Malterlib_Numeric_Float_StdLib_fp32.hpp"
