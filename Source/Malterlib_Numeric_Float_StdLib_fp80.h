// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib::NSys::NNumeric
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

namespace NMib::NNumeric
{
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::fs_0()
	{
		return 0.0l;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::fs_0_5()
	{
		return 0.5l;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::fs_1()
	{
		return 1.0l;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::fs_2()
	{
		return 2.0l;
	}

	template <> DMibFloatConstexpr inline_small void CIEEEFloat80::fp_Set_0()
	{
		m_DataStorage = 0.0l;
	}

	template <> DMibFloatConstexpr inline_small void CIEEEFloat80::fp_Set_0_5()
	{
		m_DataStorage = 0.5l;
	}

	template <> DMibFloatConstexpr inline_small void CIEEEFloat80::fp_Set_1()
	{
		m_DataStorage = 1.0l;
	}

	template <> DMibFloatConstexpr inline_small void CIEEEFloat80::fp_Set_2()
	{
		m_DataStorage = 2.0l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_E()
	{
		m_DataStorage = 2.71828182845904523536028747135266249775724709369995l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Pi()
	{
		m_DataStorage = 3.14159265358979323846264338327950288419716939937510l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Euler()
	{
		m_DataStorage = 0.57721566490153286060651209008240243104215933593992l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_GoldenRatio()
	{
		m_DataStorage = 1.61803398874989484820458683436563811772030917980576l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Sqrt2()
	{
		m_DataStorage = 1.4142135623730950488016887242097l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Log2_10()
	{
		m_DataStorage = 3.3219280948873623478703194294894l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Log10_2()
	{
		m_DataStorage = 0.30102999566398119521373889472449l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Log2_E()
	{
		m_DataStorage = 1.4426950408889634073599246810019l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_LogE_2()
	{
		m_DataStorage = 0.69314718055994530941723212145818l;
	}

#ifdef DMibPCanDo_fp32
	template < >
	template < >
	inline_always void CIEEEFloat80::f_Assign(const CIEEEFloat32 &_SetValue)
	{
		m_DataStorage = _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always bool CIEEEFloat80::operator == (const CIEEEFloat32 &_SetValue) const
	{
		return m_DataStorage == _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always COrdering_Partial CIEEEFloat80::operator <=> (const CIEEEFloat32 &_SetValue) const
	{
		return m_DataStorage <=> _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always void CIEEEFloat32::f_Assign(const CIEEEFloat80 &_SetValue)
	{
		m_DataStorage = _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always bool CIEEEFloat32::operator == (const CIEEEFloat80 &_SetValue) const
	{
		return m_DataStorage == _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always COrdering_Partial CIEEEFloat32::operator <=> (const CIEEEFloat80 &_SetValue) const
	{
		return m_DataStorage <=> _SetValue.f_Get();
	}
#endif

#ifdef DMibPCanDo_fp64
	template < >
	template < >
	inline_always void CIEEEFloat80::f_Assign(const CIEEEFloat64 &_SetValue)
	{
		m_DataStorage = _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always bool CIEEEFloat80::operator == (const CIEEEFloat64 &_SetValue) const
	{
		return m_DataStorage == _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always COrdering_Partial CIEEEFloat80::operator <=> (const CIEEEFloat64 &_SetValue) const
	{
		return m_DataStorage <=> _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always void CIEEEFloat64::f_Assign(const CIEEEFloat80 &_SetValue)
	{
		m_DataStorage = _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always bool CIEEEFloat64::operator == (const CIEEEFloat80 &_SetValue) const
	{
		return m_DataStorage == _SetValue.f_Get();
	}

	template < >
	template < >
	inline_always COrdering_Partial CIEEEFloat64::operator <=> (const CIEEEFloat80 &_SetValue) const
	{
		return m_DataStorage <=> _SetValue.f_Get();
	}
#endif

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by value operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator + (const CIEEEFloat80 &_Value) const
	{
		return m_DataStorage + _Value.m_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator - (const CIEEEFloat80 &_Value) const
	{
		return m_DataStorage - _Value.m_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator * (const CIEEEFloat80 &_Value) const
	{
		return m_DataStorage * _Value.m_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator / (const CIEEEFloat80 &_Value) const
	{
		return m_DataStorage / _Value.m_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator - () const
	{
		return -m_DataStorage;
	}



	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by reference operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 &CIEEEFloat80::operator += (const CIEEEFloat80 &_Value)
	{
		m_DataStorage += _Value.m_DataStorage;
		return *this;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 &CIEEEFloat80::operator -= (const CIEEEFloat80 &_Value)
	{
		m_DataStorage -= _Value.m_DataStorage;
		return *this;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 &CIEEEFloat80::operator /= (const CIEEEFloat80 &_Value)
	{
		m_DataStorage /= _Value.m_DataStorage;
		return *this;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 &CIEEEFloat80::operator *= (const CIEEEFloat80 &_Value)
	{
		m_DataStorage *= _Value.m_DataStorage;
		return *this;
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Trigomethric
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Sin() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Sin();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Sin(m_DataStorage);
		}
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Cos() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Cos();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Cos(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Tan() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Tan();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Tan(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_SinH() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_SinH();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_SinH(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_CosH() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_CosH();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_CosH(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_TanH() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_TanH();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_TanH(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_ArcSin() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_ArcSin();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_ArcSin(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_ArcCos() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_ArcCos();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_ArcCos(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_ArcTan() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_ArcTan();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_ArcTan(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_ArcTan(const CIEEEFloat80 &_Source) const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_ArcTan(CEmulatedFloat(_Source));
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_ArcTan(m_DataStorage, _Source.m_DataStorage);
		}
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_ExpN() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_ExpN();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_ExpN(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_LogN() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_LogN();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_LogN(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Exp10() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Exp10();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Exp10(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Log10() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Log10();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Log10(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Exp2() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Exp2();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Exp2(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Log2() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Log2();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Log2(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Exp(const CIEEEFloat80 & _Base) const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Exp(CEmulatedFloat(_Base));
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Exp(m_DataStorage, _Base.m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Log(const CIEEEFloat80 & _Base) const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Log(CEmulatedFloat(_Base));
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Log(m_DataStorage, _Base.m_DataStorage);
		}
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Power
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Sqrt() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Sqrt();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Sqrt(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Sqr() const
	{
		return (m_DataStorage) * (m_DataStorage);
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Pow(const CIEEEFloat80 &_Power) const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Pow(CEmulatedFloat(_Power));
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Pow(m_DataStorage, _Power.m_DataStorage);
		}
	}


	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Integer functions
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat80::CInteger CIEEEFloat80::f_ToInt() const
	{
		pfp80 ToLoad = m_DataStorage;
#ifdef DMibPCanDo_int128
		return int128(ToLoad);
#else
		return int64(ToLoad);
#endif
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80::CUnsignedInteger CIEEEFloat80::f_ToUnsignedInt() const
	{
		pfp80 ToLoad = m_DataStorage;
#ifdef DMibPCanDo_int128
		return uint128(ToLoad);
#else
		return uint64(ToLoad);
#endif
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Floor() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Floor();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Floor(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Ceil() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Ceil();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Ceil(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Abs() const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Abs();
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Abs(m_DataStorage);
		}
	}
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Mod(const TCFloat &_Modulu) const
	{
#if DMibFloatConstexprEnabled
		if_consteval
		{
			CEmulatedFloat Temp(*this);
			Temp.f_Mod(CEmulatedFloat(_Modulu));
			return Temp;
		}
		else
#endif
		{
			return NSys::NNumeric::fg_Mod(m_DataStorage, _Modulu.m_DataStorage);
		}
	}

	template <> DMibFloatConstexpr inline_small bool CIEEEFloat80::operator == (const CIEEEFloat80 &_Value) const
	{
		return m_DataStorage == _Value.m_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small COrdering_Partial CIEEEFloat80::operator <=> (const CIEEEFloat80 &_Value) const
	{
		return m_DataStorage <=> _Value.m_DataStorage;
	}
}

namespace NMib
{
#define DMibDirectConvert(_FromType, _ToType) \
	template <>\
	class TCConvert< _ToType, _FromType>\
	{\
	public:\
		static DMibFloatConstexpr inline_small _ToType fs_Convert( _FromType const &_From)\
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
		static DMibFloatConstexpr inline_small _ToType fs_Convert( _FromType const &_From)\
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
		static DMibFloatConstexpr inline_small _ToType fs_Convert( _FromType const &_From)\
		{\
			return NMib::fg_Convert<_ToType>(_From.f_ToInt());\
		}\
	};\
	template <>\
	class TCConvert< _FromType, _ToType >\
	{\
	public:\
		static DMibFloatConstexpr inline_small _FromType fs_Convert( _ToType const &_From)\
		{\
			_FromType Ret;\
			Ret.f_GetImplicit() = _From;\
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

#ifdef DMibPCanDo_int96
	DMibMathFloatConvertInt(CIEEEFloat80, int96);
#endif

#ifdef DMibPCanDo_uint96
	DMibMathFloatConvertInt(CIEEEFloat80, uint96);
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

#ifdef DMibPCanDo_int192
	DMibMathFloatConvertInt(CIEEEFloat80, int192);
#endif

#ifdef DMibPCanDo_uint192
	DMibMathFloatConvertInt(CIEEEFloat80, uint192);
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

#ifdef DMibPCanDo_int384
	DMibMathFloatConvertInt(CIEEEFloat80, int384);
#endif

#ifdef DMibPCanDo_uint384
	DMibMathFloatConvertInt(CIEEEFloat80, uint384);
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

#ifdef DMibPCanDo_int16384
	DMibMathFloatConvertInt(CIEEEFloat80, int16384);
#endif

#ifdef DMibPCanDo_uint16384
	DMibMathFloatConvertInt(CIEEEFloat80, uint16384);
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
