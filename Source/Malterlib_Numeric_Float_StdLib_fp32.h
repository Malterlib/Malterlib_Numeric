// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NSys::NMath
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
	#pragma warning(disable : 4725) // Disable warning about erronous pentiums
#endif

		/************************************************************************************************\
		|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|
		| |¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
		| | fp32 (float)
		| |_______________________________________________________________________________________________
		|_________________________________________________________________________________________________|
		\************************************************************************************************/

namespace NMib
{
	namespace NMath
	{
		template <> inline_small void CIEEEFloat32::fp_Set_0()
		{
            f_Get() = 0.0f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_0_5()
		{
            f_Get() = 0.5f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_1()
		{
            f_Get() = 1.0f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_2()
		{
            f_Get() = 2.0f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_E()
		{
            f_Get() = 2.71828182845904523536028747135266249775724709369995f;			
		}

		template <> inline_small void CIEEEFloat32::fp_Set_Pi()
		{
            f_Get() = 3.14159265358979323846264338327950288419716939937510f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_Euler()
		{
            f_Get() = 0.57721566490153286060651209008240243104215933593992f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_GoldenRatio()
		{
            f_Get() = 1.61803398874989484820458683436563811772030917980576f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_Sqrt2()
		{
            f_Get() = 1.4142135623730950488016887242097f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_Log2_10()
		{
            f_Get() = 3.3219280948873623478703194294894f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_Log10_2()
		{
            f_Get() = 0.30102999566398119521373889472449f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_Log2_E()
		{
            f_Get() = 1.4426950408889634073599246810019f;
		}

		template <> inline_small void CIEEEFloat32::fp_Set_LogE_2()
		{
            f_Get() = 0.69314718055994530941723212145818f;
		}

#ifdef DMibPCanDo_fp64
		template < > 
		template < > 
		inline_always void CIEEEFloat32 ::f_Assign(const CIEEEFloat64 &_SetValue)
		{
            f_Get() = _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat32 :: operator < (const CIEEEFloat64 &_SetValue)
		{
            return f_Get() < _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat32 :: operator == (const CIEEEFloat64 &_SetValue)
		{
            return f_Get() == _SetValue.f_Get();
		}
#endif

#ifdef DMibPCanDo_fp80
		template < > 
		template < > 
		inline_always void CIEEEFloat32 ::f_Assign(const CIEEEFloat80 &_SetValue)
		{
            f_Get() = _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat32 :: operator < (const CIEEEFloat80 &_SetValue)
		{
            return f_Get() < _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat32 :: operator == (const CIEEEFloat80 &_SetValue)
		{
            return f_Get() == _SetValue.f_Get();
		}
#endif


        /************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by value operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat32 CIEEEFloat32::operator + (const CIEEEFloat32 &_Value) const
		{
			return f_Get() + ((pfp32 &)_Value.m_Data);
		}

		template <> inline_small CIEEEFloat32 CIEEEFloat32::operator - (const CIEEEFloat32 &_Value) const
		{
			return f_Get() - ((pfp32 &)_Value.m_Data);
		}

		template <> inline_small CIEEEFloat32 CIEEEFloat32::operator * (const CIEEEFloat32 &_Value) const
		{
			return f_Get() * ((pfp32 &)_Value.m_Data);
		}

		template <> inline_small CIEEEFloat32 CIEEEFloat32::operator / (const CIEEEFloat32 &_Value) const
		{
			return f_Get() / ((pfp32 &)_Value.m_Data);
		}

		template <> inline_small CIEEEFloat32 CIEEEFloat32::operator - () const
		{
			return -f_Get();
		}


		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by reference operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat32 &CIEEEFloat32::operator += (const CIEEEFloat32 &_Value)
		{
			f_Get() += ((pfp32 &)_Value.m_Data);
			return *this;
		}

		template <> inline_small CIEEEFloat32 &CIEEEFloat32::operator -= (const CIEEEFloat32 &_Value)
		{
			f_Get() -= ((pfp32 &)_Value.m_Data);
			return *this;
		}

		template <> inline_small CIEEEFloat32 &CIEEEFloat32::operator /= (const CIEEEFloat32 &_Value)
		{
			f_Get() /= ((pfp32 &)_Value.m_Data);
			return *this;
		}

		template <> inline_small CIEEEFloat32 &CIEEEFloat32::operator *= (const CIEEEFloat32 &_Value)
		{
			f_Get() *= ((pfp32 &)_Value.m_Data);
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Trigomethric
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Sin() const
		{
			return NSys::NMath::fg_Sin(f_Get());
		}

		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Cos() const
		{
			return NSys::NMath::fg_Cos(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Tan() const
		{
			return NSys::NMath::fg_Tan(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_SinH() const
		{
			return NSys::NMath::fg_SinH(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_CosH() const
		{
			return NSys::NMath::fg_CosH(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_TanH() const
		{
			return NSys::NMath::fg_TanH(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_ArcSin() const
		{
			return NSys::NMath::fg_ArcSin(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_ArcCos() const
		{
			return NSys::NMath::fg_ArcCos(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_ArcTan() const
		{
			return NSys::NMath::fg_ArcTan(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_ArcTan(const CIEEEFloat32 &_Source) const
		{
			return NSys::NMath::fg_ArcTan(f_Get(), ((pfp32 &)_Source.m_Data));
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Logarithm and exponent
		||______________________________________________________________________________________________||
		\************************************************************************************************/


		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_ExpN() const
		{
			return NSys::NMath::fg_ExpN(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_LogN() const
		{
			return NSys::NMath::fg_LogN(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Exp10() const
		{
			return NSys::NMath::fg_Exp10(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Log10() const
		{
			return NSys::NMath::fg_Log10(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Exp2() const
		{
			return NSys::NMath::fg_Exp2(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Log2() const
		{
			return NSys::NMath::fg_Log2(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Exp(const CIEEEFloat32 & _Base) const
		{
			return NSys::NMath::fg_Exp(f_Get(), ((pfp32 &)_Base.m_Data));
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Log(const CIEEEFloat32 & _Base) const
		{
			return NSys::NMath::fg_Log(f_Get(), ((pfp32 &)_Base.m_Data));
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Power
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Sqrt() const
		{
			return NSys::NMath::fg_Sqrt(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Sqr() const
		{
			return (f_Get()) * (f_Get());
		}

		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Pow(const CIEEEFloat32 &_Power) const
		{
			return NSys::NMath::fg_Pow(f_Get(), ((pfp32 &)_Power.m_Data));
		}


		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Integer functions
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat32::CInteger CIEEEFloat32::f_ToInt() const
		{
			pfp32 ToLoad = f_Get();
			return (CIEEEFloat32::CInteger)ToLoad;
		}

		template <> inline_small CIEEEFloat32::CUnsignedInteger CIEEEFloat32::f_ToUnsignedInt() const
		{
			pfp32 ToLoad = f_Get();
			return (CIEEEFloat32::CUnsignedInteger)ToLoad;
		}


		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Floor() const
		{
			return NSys::NMath::fg_Floor(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Ceil() const
		{
			return NSys::NMath::fg_Ceil(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Abs() const
		{
			return NSys::NMath::fg_Abs(f_Get());
		}
		template <> inline_small CIEEEFloat32 CIEEEFloat32::f_Mod(const TCFloat &_Modulu) const
		{
			return NSys::NMath::fg_Mod(f_Get(), ((pfp32 &)_Modulu.m_Data));
		}


		template <> inline_small bool CIEEEFloat32::operator == (const CIEEEFloat32 &_Value) const
		{
			return f_Get() == ((pfp32 &)_Value.m_Data);
		}

		template <> inline_small bool CIEEEFloat32::operator < (const CIEEEFloat32 &_Value) const
		{
			return f_Get() < ((pfp32 &)_Value.m_Data);
		}
	}
}

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

#ifdef DMibPCanDo_fp80
	DMibDirectConvert(pfp32, CIEEEFloat80);
#endif
	
#ifdef DMibPCanDo_fp64
	DMibDirectConvert(pfp32, CIEEEFloat64);
#endif

	DMibDirectConvert(pfp32, CIEEEFloat32);
	
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

#ifdef DMibPCanDo_fp80
	DMibMathFloatConvertNative(CIEEEFloat80, pfp32);
#endif

#ifdef DMibPCanDo_fp64
	DMibMathFloatConvertNative(CIEEEFloat64, pfp32);
#endif

	DMibMathFloatConvertNative(CIEEEFloat32, pfp32);
	
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


#ifdef DMibPUniqueType_mint
	DMibMathFloatConvertInt(CIEEEFloat32, mint);
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
