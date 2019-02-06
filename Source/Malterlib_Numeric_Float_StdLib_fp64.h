// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

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

#ifndef DDocumentation_Doxygen

namespace NMib::NNumeric
{
#ifdef DCompiler_MSVC
	#pragma warning(disable : 4725) // Disable warning about erronous pentiums
#endif
	
	template <> inline_small CIEEEFloat64::TCFloat(TCFloat const &_Other)
		: m_DataImplicit(_Other.m_DataImplicit)
	{
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::fs_0()
	{
		return 0.0;
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::fs_0_5()
	{
		return 0.5;
	}
	
	template <> inline_small CIEEEFloat64 CIEEEFloat64::fs_1()
	{
		return 1.0;
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::fs_2()
	{
		return 2.0;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_0()
	{
		f_Get() = 0.0;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_0_5()
	{
		f_Get() = 0.5;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_1()
	{
		f_Get() = 1.0;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_2()
	{
		f_Get() = 2.0;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_E()
	{
		f_Get() = 2.71828182845904523536028747135266249775724709369995;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_Pi()
	{
		f_Get() = 3.14159265358979323846264338327950288419716939937510;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_Euler()
	{
		f_Get() = 0.57721566490153286060651209008240243104215933593992;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_GoldenRatio()
	{
		f_Get() = 1.61803398874989484820458683436563811772030917980576;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_Sqrt2()
	{
		f_Get() = 1.4142135623730950488016887242097;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_Log2_10()
	{
		f_Get() = 3.3219280948873623478703194294894;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_Log10_2()
	{
		f_Get() = 0.30102999566398119521373889472449;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_Log2_E()
	{
		f_Get() = 1.4426950408889634073599246810019;
	}

	template <> inline_small void CIEEEFloat64::fp_Set_LogE_2()
	{
		f_Get() = 0.69314718055994530941723212145818;
	}

#ifdef DMibPCanDo_fp32
	template < > 
	template < > 
	inline_always void CIEEEFloat64 ::f_Assign(const CIEEEFloat32 &_SetValue)
	{
		f_Get() = _SetValue.f_Get();
	}

	template < > 
	template < > 
	inline_always bool CIEEEFloat64 :: operator < (const CIEEEFloat32 &_SetValue) const
	{
		return f_Get() < _SetValue.f_Get();
	}

	template < > 
	template < > 
	inline_always bool CIEEEFloat64 :: operator == (const CIEEEFloat32 &_SetValue) const
	{
		return f_Get() == _SetValue.f_Get();
	}
	template < > 
	template < > 
	inline_always void CIEEEFloat32 ::f_Assign(const CIEEEFloat64 &_SetValue)
	{
		f_Get() = _SetValue.f_Get();
	}

	template < > 
	template < > 
	inline_always bool CIEEEFloat32 :: operator < (const CIEEEFloat64 &_SetValue) const
	{
		return f_Get() < _SetValue.f_Get();
	}

	template < > 
	template < > 
	inline_always bool CIEEEFloat32 :: operator == (const CIEEEFloat64 &_SetValue) const
	{
		return f_Get() == _SetValue.f_Get();
	}
#endif


	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by value operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> inline_small CIEEEFloat64 CIEEEFloat64::operator + (const CIEEEFloat64 &_Value) const
	{
		return f_Get() + ((pfp64 &)_Value.m_Data);
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::operator - (const CIEEEFloat64 &_Value) const
	{
		return f_Get() - ((pfp64 &)_Value.m_Data);
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::operator * (const CIEEEFloat64 &_Value) const
	{
		return f_Get() * ((pfp64 &)_Value.m_Data);
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::operator / (const CIEEEFloat64 &_Value) const
	{
		return f_Get() / ((pfp64 &)_Value.m_Data);
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::operator - () const
	{
		return -f_Get();
	}



	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by reference operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> inline_small CIEEEFloat64 &CIEEEFloat64::operator += (const CIEEEFloat64 &_Value)
	{
		f_Get() += ((pfp64 &)_Value.m_Data);
		return *this;
	}

	template <> inline_small CIEEEFloat64 &CIEEEFloat64::operator -= (const CIEEEFloat64 &_Value)
	{
		f_Get() -= ((pfp64 &)_Value.m_Data);
		return *this;
	}

	template <> inline_small CIEEEFloat64 &CIEEEFloat64::operator /= (const CIEEEFloat64 &_Value)
	{
		f_Get() /= ((pfp64 &)_Value.m_Data);
		return *this;
	}

	template <> inline_small CIEEEFloat64 &CIEEEFloat64::operator *= (const CIEEEFloat64 &_Value)
	{
		f_Get() *= ((pfp64 &)_Value.m_Data);
		return *this;
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Trigomethric
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Sin() const
	{
		return NSys::NNumeric::fg_Sin(f_Get());
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Cos() const
	{
		return NSys::NNumeric::fg_Cos(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Tan() const
	{
		return NSys::NNumeric::fg_Tan(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_SinH() const
	{
		return NSys::NNumeric::fg_SinH(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_CosH() const
	{
		return NSys::NNumeric::fg_CosH(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_TanH() const
	{
		return NSys::NNumeric::fg_TanH(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_ArcSin() const
	{
		return NSys::NNumeric::fg_ArcSin(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_ArcCos() const
	{
		return NSys::NNumeric::fg_ArcCos(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_ArcTan() const
	{
		return NSys::NNumeric::fg_ArcTan(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_ArcTan(const CIEEEFloat64 &_Source) const
	{
		return NSys::NNumeric::fg_ArcTan(f_Get(), ((pfp64 &)_Source.m_Data));
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_ExpN() const
	{
		return NSys::NNumeric::fg_ExpN(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_LogN() const
	{
		return NSys::NNumeric::fg_LogN(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Exp10() const
	{
		return NSys::NNumeric::fg_Exp10(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Log10() const
	{
		return NSys::NNumeric::fg_Log10(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Exp2() const
	{
		return NSys::NNumeric::fg_Exp2(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Log2() const
	{
		return NSys::NNumeric::fg_Log2(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Exp(const CIEEEFloat64 & _Base) const
	{
		return NSys::NNumeric::fg_Exp(f_Get(), ((pfp64 &)_Base.m_Data));
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Log(const CIEEEFloat64 & _Base) const
	{
		return NSys::NNumeric::fg_Log(f_Get(), ((pfp64 &)_Base.m_Data));
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Power
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Sqrt() const
	{
		return NSys::NNumeric::fg_Sqrt(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Sqr() const
	{
		return (f_Get()) * (f_Get());
	}

	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Pow(const CIEEEFloat64 &_Power) const
	{
		return NSys::NNumeric::fg_Pow(f_Get(), ((pfp64 &)_Power.m_Data));
	}


	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Integer functions
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> inline_small CIEEEFloat64::CInteger CIEEEFloat64::f_ToInt() const
	{
		pfp64 ToLoad = f_Get();
		return (CIEEEFloat64::CInteger)ToLoad;
	}

	template <> inline_small CIEEEFloat64::CUnsignedInteger CIEEEFloat64::f_ToUnsignedInt() const
	{
		pfp64 ToLoad = f_Get();
		
		return (CIEEEFloat64::CUnsignedInteger)ToLoad;
	}


	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Floor() const
	{
		return NSys::NNumeric::fg_Floor(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Ceil() const
	{
		return NSys::NNumeric::fg_Ceil(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Abs() const
	{
		return NSys::NNumeric::fg_Abs(f_Get());
	}
	template <> inline_small CIEEEFloat64 CIEEEFloat64::f_Mod(const TCFloat &_Modulu) const
	{
		return NSys::NNumeric::fg_Mod(f_Get(), ((pfp64 &)_Modulu.m_Data));
	}


	template <> inline_small bool CIEEEFloat64::operator == (const CIEEEFloat64 &_Value) const
	{
		return f_Get() == ((pfp64 &)_Value.m_Data);
	}

	template <> inline_small bool CIEEEFloat64::operator < (const CIEEEFloat64 &_Value) const
	{
		return f_Get() < ((pfp64 &)_Value.m_Data);
	}
}

#endif

namespace NMib
{

#define DMibDirectConvert(_FromType, _ToType) \
	template <>\
	class TCConvert< _ToType, _FromType>\
	{\
	public:\
		static inline_small _ToType fs_Convert( _FromType const &_From)\
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

#define DMibMathFloatConvertNative(_FromType, _ToType) \
	template <>\
	class TCConvert< _ToType, _FromType>\
	{\
	public:\
		static inline_small _ToType fs_Convert( _FromType const &_From)\
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

#define DMibMathFloatConvertInt(_FromType, _ToType) \
	template <>\
	class TCConvert< _ToType, _FromType >\
	{\
	public:\
		static inline_small _ToType fs_Convert( _FromType const &_From)\
		{\
			return NMib::fg_Convert<_ToType>(_From.f_ToInt());\
		}\
	};\
	template <>\
	class TCConvert< _FromType, _ToType >\
	{\
	public:\
		static inline_small _FromType fs_Convert( _ToType const &_From)\
		{\
			_FromType Ret;\
			((_FromType::CImplicitFloat &)Ret) = _From;\
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


#ifdef DMibPUniqueType_mint
	DMibMathFloatConvertInt(CIEEEFloat64, mint);
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
