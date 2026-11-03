// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

namespace NMib::NSys::NNumeric
{
	pfp64 fg_Sin(pfp64 _Val);
	pfp64 fg_Cos(pfp64 _Val);
	pfp64 fg_Tan(pfp64 _Val);
	pfp64 fg_SinH(pfp64 _Val);
	pfp64 fg_CosH(pfp64 _Val);
	pfp64 fg_TanH(pfp64 _Val);
	pfp64 fg_ArcSin(pfp64 _Val);
	pfp64 fg_ArcCos(pfp64 _Val);
	pfp64 fg_ArcTan(pfp64 _Val);
	pfp64 fg_ArcTan(pfp64 _Val, pfp64 _Source);

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	pfp64 fg_ExpN(pfp64 _Val);
	pfp64 fg_LogN(pfp64 _Val);
	pfp64 fg_Exp10(pfp64 _Val);
	pfp64 fg_Log10(pfp64 _Val);
	pfp64 fg_Exp2(pfp64 _Val);
	pfp64 fg_Log2(pfp64 _Val);
	pfp64 fg_Exp(pfp64 _Val, pfp64 _Base);
	pfp64 fg_Log(pfp64 _Val, pfp64 _Base);
	pfp64 fg_Sqrt(pfp64 _Val);
	pfp64 fg_Pow(pfp64 _Val, pfp64 _Power);
	pfp64 fg_Floor(pfp64 _Val);
	pfp64 fg_Ceil(pfp64 _Val);
	pfp64 fg_Abs(pfp64 _Val);
	pfp64 fg_Mod(pfp64 _Val, pfp64 _Modulu);
}

namespace NMib::NNumeric
{
#ifdef DCompiler_MSVC
#	pragma warning(disable : 4725) // Disable warning about erronous pentiums
#endif

	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::fs_Zero();
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::fs_Half();
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::fs_One();
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::fs_Two();
	template <> DMibFloatConstexpr inline_small void CIEEEFloat64::fp_Set_0();
	template <> DMibFloatConstexpr inline_small void CIEEEFloat64::fp_Set_0_5();
	template <> DMibFloatConstexpr inline_small void CIEEEFloat64::fp_Set_1();
	template <> DMibFloatConstexpr inline_small void CIEEEFloat64::fp_Set_2();
	template <> inline_small void CIEEEFloat64::fp_Set_E();
	template <> inline_small void CIEEEFloat64::fp_Set_Pi();
	template <> inline_small void CIEEEFloat64::fp_Set_Euler();
	template <> inline_small void CIEEEFloat64::fp_Set_GoldenRatio();
	template <> inline_small void CIEEEFloat64::fp_Set_Sqrt2();
	template <> inline_small void CIEEEFloat64::fp_Set_Log2_10();
	template <> inline_small void CIEEEFloat64::fp_Set_Log10_2();
	template <> inline_small void CIEEEFloat64::fp_Set_Log2_E();
	template <> inline_small void CIEEEFloat64::fp_Set_LogE_2();

#ifdef DMibPCanDo_fp32
	template <>
	template <>
	inline_always void CIEEEFloat64::f_Assign(CIEEEFloat32 const &_SetValue);

	template <>
	template <>
	inline_always bool CIEEEFloat64::operator == (CIEEEFloat32 const &_SetValue) const noexcept;

	template <>
	template <>
	inline_always COrdering_Partial CIEEEFloat64::operator <=> (CIEEEFloat32 const &_SetValue) const noexcept;

	template <>
	template <>
	inline_always bool CIEEEFloat32::operator == (CIEEEFloat64 const &_SetValue) const noexcept;

	template <>
	template <>
	inline_always COrdering_Partial CIEEEFloat32::operator <=> (CIEEEFloat64 const &_SetValue) const noexcept;

#endif

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by value operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::operator + (CIEEEFloat64 const &_Value) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::operator - (CIEEEFloat64 const &_Value) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::operator * (CIEEEFloat64 const &_Value) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::operator / (CIEEEFloat64 const &_Value) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::operator - () const;

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by reference operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat64 &CIEEEFloat64::operator += (CIEEEFloat64 const &_Value);
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 &CIEEEFloat64::operator -= (CIEEEFloat64 const &_Value);
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 &CIEEEFloat64::operator /= (CIEEEFloat64 const &_Value);
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 &CIEEEFloat64::operator *= (CIEEEFloat64 const &_Value);

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Trigomethric
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Sin() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Cos() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Tan() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_SinH() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_CosH() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_TanH() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_ArcSin() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_ArcCos() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_ArcTan() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_ArcTan(CIEEEFloat64 const &_Source) const;

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_ExpN() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_LogN() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Exp10() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Log10() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Exp2() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Log2() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Exp(CIEEEFloat64 const &_Base) const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Log(CIEEEFloat64 const &_Base) const;

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Power
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Sqrt() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Sqr() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Pow(CIEEEFloat64 const &_Power) const;

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Integer functions
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat64::CInteger CIEEEFloat64::f_ToInt() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64::CUnsignedInteger CIEEEFloat64::f_ToUnsignedInt() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Floor() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Ceil() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Abs() const;
	template <> DMibFloatConstexpr inline_small CIEEEFloat64 CIEEEFloat64::f_Mod(TCFloat const &_Modulu) const;
	template <> DMibFloatConstexpr inline_small bool CIEEEFloat64::operator == (CIEEEFloat64 const &_Value) const noexcept;
	template <> DMibFloatConstexpr inline_small COrdering_Partial CIEEEFloat64::operator <=> (CIEEEFloat64 const &_Value) const noexcept;
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

#ifdef DMibPCanDo_fp32
	DMibDirectConvert(pfp64, CIEEEFloat32);
	DMibDirectConvert(pfp32, CIEEEFloat64);
#endif

	DMibDirectConvert(pfp64, CIEEEFloat64);

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

#ifdef DMibPCanDo_fp32
	DMibMathFloatConvertNative(CIEEEFloat32, pfp64);
	DMibMathFloatConvertNative(CIEEEFloat64, pfp32);
#endif

	DMibMathFloatConvertNative(CIEEEFloat64, pfp64);

#undef DMibMathFloatConvertNative

#define DMibMathFloatConvertInt(d_FromType, d_ToType) \
	template <>\
	struct TCConvert< d_ToType, d_FromType >\
	{\
		static DMibFloatConstexpr inline_small d_ToType fs_Convert( d_FromType const &_From)\
		{\
			return NMib::fg_Convert<d_ToType>(_From.f_ToInt());\
		}\
	};\
	template <>\
	struct TCConvert< d_FromType, d_ToType >\
	{\
		static DMibFloatConstexpr inline_small d_FromType fs_Convert( d_ToType const &_From)\
		{\
			d_FromType Ret;\
			Ret.f_GetImplicit() = _From;\
			return Ret;\
		}\
	};

	DMibMathFloatConvertInt(CIEEEFloat64, int8);

#ifdef DMibPCanDo_int16
	DMibMathFloatConvertInt(CIEEEFloat64, int16);
#endif

#ifdef DMibPCanDo_uint16
	DMibMathFloatConvertInt(CIEEEFloat64, uint16);
#endif

#ifdef DMibPCanDo_int32
	DMibMathFloatConvertInt(CIEEEFloat64, int32);
#endif

#ifdef DMibPCanDo_uint32
	DMibMathFloatConvertInt(CIEEEFloat64, uint32);
#endif

#ifdef DMibPCanDo_int64
	DMibMathFloatConvertInt(CIEEEFloat64, int64);
#endif

#ifdef DMibPCanDo_uint64
	DMibMathFloatConvertInt(CIEEEFloat64, uint64);
#endif

#ifdef DMibPCanDo_int80
	DMibMathFloatConvertInt(CIEEEFloat64, int80);
#endif

#ifdef DMibPCanDo_uint80
	DMibMathFloatConvertInt(CIEEEFloat64, uint80);
#endif

#ifdef DMibPCanDo_int96
	DMibMathFloatConvertInt(CIEEEFloat64, int96);
#endif

#ifdef DMibPCanDo_uint96
	DMibMathFloatConvertInt(CIEEEFloat64, uint96);
#endif

#ifdef DMibPCanDo_int128
	DMibMathFloatConvertInt(CIEEEFloat64, int128);
#endif

#ifdef DMibPCanDo_uint128
	DMibMathFloatConvertInt(CIEEEFloat64, uint128);
#endif

#ifdef DMibPCanDo_int160
	DMibMathFloatConvertInt(CIEEEFloat64, int160);
#endif

#ifdef DMibPCanDo_uint160
	DMibMathFloatConvertInt(CIEEEFloat64, uint160);
#endif

#ifdef DMibPCanDo_int192
	DMibMathFloatConvertInt(CIEEEFloat64, int192);
#endif

#ifdef DMibPCanDo_uint192
	DMibMathFloatConvertInt(CIEEEFloat64, uint192);
#endif

#ifdef DMibPCanDo_int256
	DMibMathFloatConvertInt(CIEEEFloat64, int256);
#endif

#ifdef DMibPCanDo_uint256
	DMibMathFloatConvertInt(CIEEEFloat64, uint256);
#endif

#ifdef DMibPCanDo_int320
	DMibMathFloatConvertInt(CIEEEFloat64, int320);
#endif

#ifdef DMibPCanDo_uint320
	DMibMathFloatConvertInt(CIEEEFloat64, uint320);
#endif

#ifdef DMibPCanDo_int384
	DMibMathFloatConvertInt(CIEEEFloat64, int384);
#endif

#ifdef DMibPCanDo_uint384
	DMibMathFloatConvertInt(CIEEEFloat64, uint384);
#endif

#ifdef DMibPCanDo_int512
	DMibMathFloatConvertInt(CIEEEFloat64, int512);
#endif

#ifdef DMibPCanDo_uint512
	DMibMathFloatConvertInt(CIEEEFloat64, uint512);
#endif

#ifdef DMibPCanDo_int1024
	DMibMathFloatConvertInt(CIEEEFloat64, int1024);
#endif

#ifdef DMibPCanDo_uint1024
	DMibMathFloatConvertInt(CIEEEFloat64, uint1024);
#endif

#ifdef DMibPCanDo_int2048
	DMibMathFloatConvertInt(CIEEEFloat64, int2048);
#endif

#ifdef DMibPCanDo_uint2048
	DMibMathFloatConvertInt(CIEEEFloat64, uint2048);
#endif

#ifdef DMibPCanDo_int4096
	DMibMathFloatConvertInt(CIEEEFloat64, int4096);
#endif

#ifdef DMibPCanDo_uint4096
	DMibMathFloatConvertInt(CIEEEFloat64, uint4096);
#endif

#ifdef DMibPCanDo_int8192
	DMibMathFloatConvertInt(CIEEEFloat64, int8192);
#endif

#ifdef DMibPCanDo_uint8192
	DMibMathFloatConvertInt(CIEEEFloat64, uint8192);
#endif

#ifdef DMibPCanDo_int16384
	DMibMathFloatConvertInt(CIEEEFloat64, int16384);
#endif

#ifdef DMibPCanDo_uint16384
	DMibMathFloatConvertInt(CIEEEFloat64, uint16384);
#endif

#ifdef DMibPUniqueType_umint
	DMibMathFloatConvertInt(CIEEEFloat64, umint);
#endif
#ifdef DMibPUniqueType_smint
	DMibMathFloatConvertInt(CIEEEFloat64, smint);
#endif
#ifdef DMibPUniqueType_int
	DMibMathFloatConvertInt(CIEEEFloat64, int);
#endif
#ifdef DMibPUniqueType_uint
	DMibMathFloatConvertInt(CIEEEFloat64, unsigned int);
#endif
#ifdef DMibPUniqueType_aint
	DMibMathFloatConvertInt(CIEEEFloat64, aint);
#endif

#ifdef DMibPUniqueType_uaint
	DMibMathFloatConvertInt(CIEEEFloat64, uaint);
#endif

#ifdef DMibPUniqueType_ch8
	DMibMathFloatConvertInt(CIEEEFloat64, ch8);
#endif
#ifdef DMibPUniqueType_ch16
	DMibMathFloatConvertInt(CIEEEFloat64, ch16);
#endif
#ifdef DMibPUniqueType_ch32
	DMibMathFloatConvertInt(CIEEEFloat64, ch32);
#endif

#undef DMibMathFloatConvertInt
}

#include "Malterlib_Numeric_Float_StdLib_fp64.hpp"
