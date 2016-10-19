// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NSys::NMath
{
	pfp80 fg_Sin(pfp80 _Val);
	pfp80 fg_Cos(pfp80 _Val);
	pfp80 fg_Tan(pfp80 _Val);
	pfp80 fg_SinH(pfp80 _Val);
	pfp80 fg_CosH(pfp80 _Val);
	pfp80 fg_TanH(pfp80 _Val);
	pfp80 fg_ArcSin(pfp80 _Val);
	pfp80 fg_ArcCos(pfp80 _Val);
	pfp80 fg_ArcTan(pfp80 _Val);
	pfp80 fg_ArcTan(pfp80 _Val, pfp80 _Source);

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	pfp80 fg_ExpN(pfp80 _Val);
	pfp80 fg_LogN(pfp80 _Val);
	pfp80 fg_Exp10(pfp80 _Val);
	pfp80 fg_Log10(pfp80 _Val);
	pfp80 fg_Exp2(pfp80 _Val);
	pfp80 fg_Log2(pfp80 _Val);
	pfp80 fg_Exp(pfp80 _Val, pfp80 _Base);
	pfp80 fg_Log(pfp80 _Val, pfp80 _Base);
	pfp80 fg_Sqrt(pfp80 _Val);
	pfp80 fg_Pow(pfp80 _Val, pfp80 _Power);
	pfp80 fg_Floor(pfp80 _Val);
	pfp80 fg_Ceil(pfp80 _Val);
	pfp80 fg_Abs(pfp80 _Val);
	pfp80 fg_Mod(pfp80 _Val, pfp80 _Modulu);
}

#ifdef DCompiler_MSVC
	#pragma warning(disable : 4725) // Disable warning about erronous pentiums
#endif

namespace NMib
{
	namespace NMath
	{
		template <> inline_small CIEEEFloat80 CIEEEFloat80::fs_0()
		{
			return 0.0l;
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::fs_0_5()
		{
			return 0.5l;
		}
	
		template <> inline_small CIEEEFloat80 CIEEEFloat80::fs_1()
		{
			return 1.0l;
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::fs_2()
		{
			return 2.0l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_0()
		{
            f_Get() = 0.0l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_0_5()
		{
            f_Get() = 0.5l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_1()
		{
            f_Get() = 1.0l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_2()
		{
            f_Get() = 2.0l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_E()
		{
            f_Get() = 2.71828182845904523536028747135266249775724709369995l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_Pi()
		{
            f_Get() = 3.14159265358979323846264338327950288419716939937510l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_Euler()
		{
            f_Get() = 0.57721566490153286060651209008240243104215933593992l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_GoldenRatio()
		{
            f_Get() = 1.61803398874989484820458683436563811772030917980576l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_Sqrt2()
		{
            f_Get() = 1.4142135623730950488016887242097l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_Log2_10()
		{
            f_Get() = 3.3219280948873623478703194294894l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_Log10_2()
		{
            f_Get() = 0.30102999566398119521373889472449l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_Log2_E()
		{
            f_Get() = 1.4426950408889634073599246810019l;
		}

		template <> inline_small void CIEEEFloat80::fp_Set_LogE_2()
		{
            f_Get() = 0.69314718055994530941723212145818l;
		}

#ifdef DMibPCanDo_fp32
		template < > 
		template < > 
		inline_always void CIEEEFloat80 ::f_Assign(const CIEEEFloat32 &_SetValue)
		{
            f_Get() = _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat80 :: operator < (const CIEEEFloat32 &_SetValue) const
		{
            return f_Get() < _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat80 :: operator == (const CIEEEFloat32 &_SetValue) const
		{
            return f_Get() == _SetValue.f_Get();
		}
		
		template < > 
		template < > 
		inline_always void CIEEEFloat32 ::f_Assign(const CIEEEFloat80 &_SetValue)
		{
            f_Get() = _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat32 :: operator < (const CIEEEFloat80 &_SetValue) const
		{
            return f_Get() < _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat32 :: operator == (const CIEEEFloat80 &_SetValue) const
		{
            return f_Get() == _SetValue.f_Get();
		}
#endif

#ifdef DMibPCanDo_fp64
		template < > 
		template < > 
		inline_always void CIEEEFloat80 ::f_Assign(const CIEEEFloat64 &_SetValue)
		{
            f_Get() = _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat80 :: operator < (const CIEEEFloat64 &_SetValue) const
		{
            return f_Get() < _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat80 :: operator == (const CIEEEFloat64 &_SetValue) const
		{
            return f_Get() == _SetValue.f_Get();
		}
		template < > 
		template < > 
		inline_always void CIEEEFloat64 ::f_Assign(const CIEEEFloat80 &_SetValue)
		{
			f_Get() = _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat64 :: operator < (const CIEEEFloat80 &_SetValue) const
		{
			return f_Get() < _SetValue.f_Get();
		}

		template < > 
		template < > 
		inline_always bool CIEEEFloat64 :: operator == (const CIEEEFloat80 &_SetValue) const
		{
			return f_Get() == _SetValue.f_Get();
		}
#endif

        /************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by value operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat80 CIEEEFloat80::operator + (const CIEEEFloat80 &_Value) const
		{
			return f_Get() + ((pfp80 &)_Value.m_Data);
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::operator - (const CIEEEFloat80 &_Value) const
		{
			return f_Get() - ((pfp80 &)_Value.m_Data);
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::operator * (const CIEEEFloat80 &_Value) const
		{
			return f_Get() * ((pfp80 &)_Value.m_Data);
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::operator / (const CIEEEFloat80 &_Value) const
		{
			return f_Get() / ((pfp80 &)_Value.m_Data);
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::operator - () const
		{
			return -f_Get();
		}



		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by reference operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat80 &CIEEEFloat80::operator += (const CIEEEFloat80 &_Value)
		{
			f_Get() += ((pfp80 &)_Value.m_Data);
			return *this;
		}

		template <> inline_small CIEEEFloat80 &CIEEEFloat80::operator -= (const CIEEEFloat80 &_Value)
		{
			f_Get() -= ((pfp80 &)_Value.m_Data);
			return *this;
		}

		template <> inline_small CIEEEFloat80 &CIEEEFloat80::operator /= (const CIEEEFloat80 &_Value)
		{
			f_Get() /= ((pfp80 &)_Value.m_Data);
			return *this;
		}

		template <> inline_small CIEEEFloat80 &CIEEEFloat80::operator *= (const CIEEEFloat80 &_Value)
		{
			f_Get() *= ((pfp80 &)_Value.m_Data);
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Trigomethric
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Sin() const
		{
			return NSys::NMath::fg_Sin(f_Get());
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Cos() const
		{
			return NSys::NMath::fg_Cos(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Tan() const
		{
			return NSys::NMath::fg_Tan(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_SinH() const
		{
			return NSys::NMath::fg_SinH(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_CosH() const
		{
			return NSys::NMath::fg_CosH(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_TanH() const
		{
			return NSys::NMath::fg_TanH(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_ArcSin() const
		{
			return NSys::NMath::fg_ArcSin(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_ArcCos() const
		{
			return NSys::NMath::fg_ArcCos(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_ArcTan() const
		{
			return NSys::NMath::fg_ArcTan(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_ArcTan(const CIEEEFloat80 &_Source) const
		{
			return NSys::NMath::fg_ArcTan(f_Get(), ((pfp80 &)_Source.m_Data));
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Logarithm and exponent
		||______________________________________________________________________________________________||
		\************************************************************************************************/


		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_ExpN() const
		{
			return NSys::NMath::fg_ExpN(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_LogN() const
		{
			return NSys::NMath::fg_LogN(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Exp10() const
		{
			return NSys::NMath::fg_Exp10(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Log10() const
		{
			return NSys::NMath::fg_Log10(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Exp2() const
		{
			return NSys::NMath::fg_Exp2(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Log2() const
		{
			return NSys::NMath::fg_Log2(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Exp(const CIEEEFloat80 & _Base) const
		{
			return NSys::NMath::fg_Exp(f_Get(), ((pfp80 &)_Base.m_Data));
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Log(const CIEEEFloat80 & _Base) const
		{
			return NSys::NMath::fg_Log(f_Get(), ((pfp80 &)_Base.m_Data));
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Power
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Sqrt() const
		{
			return NSys::NMath::fg_Sqrt(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Sqr() const
		{
			return (f_Get()) * (f_Get());
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Pow(const CIEEEFloat80 &_Power) const
		{
			return NSys::NMath::fg_Pow(f_Get(), ((pfp80 &)_Power.m_Data));
		}


		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Integer functions
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <> inline_small CIEEEFloat80::CInteger CIEEEFloat80::f_ToInt() const
		{
			pfp80 ToLoad = f_Get();
#ifdef DMibPCanDo_int128
			return int128(ToLoad);
#else
			return int64(ToLoad);
#endif
		}

		template <> inline_small CIEEEFloat80::CUnsignedInteger CIEEEFloat80::f_ToUnsignedInt() const
		{
			pfp80 ToLoad = f_Get();
#ifdef DMibPCanDo_int128
			return uint128(ToLoad);
#else
			return uint64(ToLoad);
#endif
		}

		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Floor() const
		{
			return NSys::NMath::fg_Floor(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Ceil() const
		{
			return NSys::NMath::fg_Ceil(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Abs() const
		{
			return NSys::NMath::fg_Abs(f_Get());
		}
		template <> inline_small CIEEEFloat80 CIEEEFloat80::f_Mod(const TCFloat &_Modulu) const
		{
			return NSys::NMath::fg_Mod(f_Get(), ((pfp80 &)_Modulu.m_Data));
		}


		template <> inline_small bool CIEEEFloat80::operator == (const CIEEEFloat80 &_Value) const
		{
			return f_Get() == ((pfp80 &)_Value.m_Data);
		}

		template <> inline_small bool CIEEEFloat80::operator < (const CIEEEFloat80 &_Value) const
		{
			return f_Get() < ((pfp80 &)_Value.m_Data);
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

#ifdef DMibPCanDo_fp64
	DMibDirectConvert(pfp80, CIEEEFloat64);
	DMibDirectConvert(pfp64, CIEEEFloat80);
#endif
#ifdef DMibPCanDo_fp32
	DMibDirectConvert(pfp80, CIEEEFloat32);
	DMibDirectConvert(pfp32, CIEEEFloat80);
#endif
	DMibDirectConvert(pfp80, CIEEEFloat80);

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

#ifdef DMibPCanDo_fp64
	DMibMathFloatConvertNative(CIEEEFloat64, pfp80);
	DMibMathFloatConvertNative(CIEEEFloat80, pfp64);
#endif

#ifdef DMibPCanDo_fp32
	DMibMathFloatConvertNative(CIEEEFloat32, pfp80);
	DMibMathFloatConvertNative(CIEEEFloat80, pfp32);
#endif

	DMibMathFloatConvertNative(CIEEEFloat80, pfp80);
	
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


	DMibMathFloatConvertInt(CIEEEFloat80, int8);

#ifdef DMibPCanDo_int16
	DMibMathFloatConvertInt(CIEEEFloat80, int16);
#endif

#ifdef DMibPCanDo_uint16
	DMibMathFloatConvertInt(CIEEEFloat80, uint16);
#endif

#ifdef DMibPCanDo_int32
	DMibMathFloatConvertInt(CIEEEFloat80, int32);
#endif

#ifdef DMibPCanDo_uint32
	DMibMathFloatConvertInt(CIEEEFloat80, uint32);
#endif

#ifdef DMibPCanDo_int64
	DMibMathFloatConvertInt(CIEEEFloat80, int64);
#endif

#ifdef DMibPCanDo_uint64
	DMibMathFloatConvertInt(CIEEEFloat80, uint64);
#endif

#ifdef DMibPCanDo_int80
	DMibMathFloatConvertInt(CIEEEFloat80, int80);
#endif

#ifdef DMibPCanDo_uint80
	DMibMathFloatConvertInt(CIEEEFloat80, uint80);
#endif

#ifdef DMibPCanDo_int128
	DMibMathFloatConvertInt(CIEEEFloat80, int128);
#endif

#ifdef DMibPCanDo_uint128
	DMibMathFloatConvertInt(CIEEEFloat80, uint128);
#endif

#ifdef DMibPCanDo_int160
	DMibMathFloatConvertInt(CIEEEFloat80, int160);
#endif

#ifdef DMibPCanDo_uint160
	DMibMathFloatConvertInt(CIEEEFloat80, uint160);
#endif

#ifdef DMibPCanDo_int256
	DMibMathFloatConvertInt(CIEEEFloat80, int256);
#endif

#ifdef DMibPCanDo_uint256
	DMibMathFloatConvertInt(CIEEEFloat80, uint256);
#endif

#ifdef DMibPCanDo_int320
	DMibMathFloatConvertInt(CIEEEFloat80, int320);
#endif

#ifdef DMibPCanDo_uint320
	DMibMathFloatConvertInt(CIEEEFloat80, uint320);
#endif
	
#ifdef DMibPCanDo_int512
	DMibMathFloatConvertInt(CIEEEFloat80, int512);
#endif

#ifdef DMibPCanDo_uint512
	DMibMathFloatConvertInt(CIEEEFloat80, uint512);
#endif

#ifdef DMibPCanDo_int1024
	DMibMathFloatConvertInt(CIEEEFloat80, int1024);
#endif

#ifdef DMibPCanDo_uint1024
	DMibMathFloatConvertInt(CIEEEFloat80, uint1024);
#endif

#ifdef DMibPCanDo_int2048
	DMibMathFloatConvertInt(CIEEEFloat80, int2048);
#endif

#ifdef DMibPCanDo_uint2048
	DMibMathFloatConvertInt(CIEEEFloat80, uint2048);
#endif

#ifdef DMibPCanDo_int4096
	DMibMathFloatConvertInt(CIEEEFloat80, int4096);
#endif

#ifdef DMibPCanDo_uint4096
	DMibMathFloatConvertInt(CIEEEFloat80, uint4096);
#endif

#ifdef DMibPCanDo_int8192
	DMibMathFloatConvertInt(CIEEEFloat80, int8192);
#endif

#ifdef DMibPCanDo_uint8192
	DMibMathFloatConvertInt(CIEEEFloat80, uint8192);
#endif


#ifdef DMibPUniqueType_mint
	DMibMathFloatConvertInt(CIEEEFloat80, mint);
#endif
#ifdef DMibPUniqueType_smint
	DMibMathFloatConvertInt(CIEEEFloat80, smint);
#endif
#ifdef DMibPUniqueType_int
	DMibMathFloatConvertInt(CIEEEFloat80, int);
#endif
#ifdef DMibPUniqueType_uint
	DMibMathFloatConvertInt(CIEEEFloat80, unsigned int);
#endif
#ifdef DMibPUniqueType_aint
	DMibMathFloatConvertInt(CIEEEFloat80, aint);
#endif

#ifdef DMibPUniqueType_uaint
	DMibMathFloatConvertInt(CIEEEFloat80, uaint);
#endif


#ifdef DMibPUniqueType_ch8
	DMibMathFloatConvertInt(CIEEEFloat80, ch8);
#endif
#ifdef DMibPUniqueType_ch16
	DMibMathFloatConvertInt(CIEEEFloat80, ch16);
#endif
#ifdef DMibPUniqueType_ch32
	DMibMathFloatConvertInt(CIEEEFloat80, ch32);
#endif
}
