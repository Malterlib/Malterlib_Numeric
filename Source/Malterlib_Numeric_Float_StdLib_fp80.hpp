// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{
	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::fs_Zero()
	{
		return 0.0l;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::fs_Half()
	{
		return 0.5l;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::fs_One()
	{
		return 1.0l;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::fs_Two()
	{
		return 2.0l;
	}

	template <> DMibFloatConstexpr inline_small void CIEEEFloat80::fp_Set_0()
	{
		mp_DataStorage = 0.0l;
	}

	template <> DMibFloatConstexpr inline_small void CIEEEFloat80::fp_Set_0_5()
	{
		mp_DataStorage = 0.5l;
	}

	template <> DMibFloatConstexpr inline_small void CIEEEFloat80::fp_Set_1()
	{
		mp_DataStorage = 1.0l;
	}

	template <> DMibFloatConstexpr inline_small void CIEEEFloat80::fp_Set_2()
	{
		mp_DataStorage = 2.0l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_E()
	{
		mp_DataStorage = 2.71828182845904523536028747135266249775724709369995l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Pi()
	{
		mp_DataStorage = 3.14159265358979323846264338327950288419716939937510l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Euler()
	{
		mp_DataStorage = 0.57721566490153286060651209008240243104215933593992l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_GoldenRatio()
	{
		mp_DataStorage = 1.61803398874989484820458683436563811772030917980576l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Sqrt2()
	{
		mp_DataStorage = 1.4142135623730950488016887242097l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Log2_10()
	{
		mp_DataStorage = 3.3219280948873623478703194294894l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Log10_2()
	{
		mp_DataStorage = 0.30102999566398119521373889472449l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_Log2_E()
	{
		mp_DataStorage = 1.4426950408889634073599246810019l;
	}

	template <> inline_small void CIEEEFloat80::fp_Set_LogE_2()
	{
		mp_DataStorage = 0.69314718055994530941723212145818l;
	}

#ifdef DMibPCanDo_fp32
	template <>
	template <>
	inline_always void CIEEEFloat80::f_Assign(CIEEEFloat32 const &_SetValue)
	{
		mp_DataStorage = _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always bool CIEEEFloat80::operator == (CIEEEFloat32 const &_SetValue) const noexcept
	{
		return mp_DataStorage == _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always COrdering_Partial CIEEEFloat80::operator <=> (CIEEEFloat32 const &_SetValue) const noexcept
	{
		return mp_DataStorage <=> _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always void CIEEEFloat32::f_Assign(CIEEEFloat80 const &_SetValue)
	{
		mp_DataStorage = _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always bool CIEEEFloat32::operator == (CIEEEFloat80 const &_SetValue) const noexcept
	{
		return mp_DataStorage == _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always COrdering_Partial CIEEEFloat32::operator <=> (CIEEEFloat80 const &_SetValue) const noexcept
	{
		return mp_DataStorage <=> _SetValue.f_Get();
	}
#endif

#ifdef DMibPCanDo_fp64
	template <>
	template <>
	inline_always void CIEEEFloat80::f_Assign(CIEEEFloat64 const &_SetValue)
	{
		mp_DataStorage = _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always bool CIEEEFloat80::operator == (CIEEEFloat64 const &_SetValue) const noexcept
	{
		return mp_DataStorage == _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always COrdering_Partial CIEEEFloat80::operator <=> (CIEEEFloat64 const &_SetValue) const noexcept
	{
		return mp_DataStorage <=> _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always void CIEEEFloat64::f_Assign(CIEEEFloat80 const &_SetValue)
	{
		mp_DataStorage = _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always bool CIEEEFloat64::operator == (CIEEEFloat80 const &_SetValue) const noexcept
	{
		return mp_DataStorage == _SetValue.f_Get();
	}

	template <>
	template <>
	inline_always COrdering_Partial CIEEEFloat64::operator <=> (CIEEEFloat80 const &_SetValue) const noexcept
	{
		return mp_DataStorage <=> _SetValue.f_Get();
	}
#endif

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by value operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator + (CIEEEFloat80 const &_Value) const
	{
		return mp_DataStorage + _Value.mp_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator - (CIEEEFloat80 const &_Value) const
	{
		return mp_DataStorage - _Value.mp_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator * (CIEEEFloat80 const &_Value) const
	{
		return mp_DataStorage * _Value.mp_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator / (CIEEEFloat80 const &_Value) const
	{
		return mp_DataStorage / _Value.mp_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::operator - () const
	{
		return -mp_DataStorage;
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Return by reference operators
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 &CIEEEFloat80::operator += (CIEEEFloat80 const &_Value)
	{
		mp_DataStorage += _Value.mp_DataStorage;
		return *this;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 &CIEEEFloat80::operator -= (CIEEEFloat80 const &_Value)
	{
		mp_DataStorage -= _Value.mp_DataStorage;
		return *this;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 &CIEEEFloat80::operator /= (CIEEEFloat80 const &_Value)
	{
		mp_DataStorage /= _Value.mp_DataStorage;
		return *this;
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 &CIEEEFloat80::operator *= (CIEEEFloat80 const &_Value)
	{
		mp_DataStorage *= _Value.mp_DataStorage;
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
			return NSys::NNumeric::fg_Sin(mp_DataStorage);
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
			return NSys::NNumeric::fg_Cos(mp_DataStorage);
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
			return NSys::NNumeric::fg_Tan(mp_DataStorage);
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
			return NSys::NNumeric::fg_SinH(mp_DataStorage);
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
			return NSys::NNumeric::fg_CosH(mp_DataStorage);
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
			return NSys::NNumeric::fg_TanH(mp_DataStorage);
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
			return NSys::NNumeric::fg_ArcSin(mp_DataStorage);
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
			return NSys::NNumeric::fg_ArcCos(mp_DataStorage);
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
			return NSys::NNumeric::fg_ArcTan(mp_DataStorage);
		}
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_ArcTan(CIEEEFloat80 const &_Source) const
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
			return NSys::NNumeric::fg_ArcTan(mp_DataStorage, _Source.mp_DataStorage);
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
			return NSys::NNumeric::fg_ExpN(mp_DataStorage);
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
			return NSys::NNumeric::fg_LogN(mp_DataStorage);
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
			return NSys::NNumeric::fg_Exp10(mp_DataStorage);
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
			return NSys::NNumeric::fg_Log10(mp_DataStorage);
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
			return NSys::NNumeric::fg_Exp2(mp_DataStorage);
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
			return NSys::NNumeric::fg_Log2(mp_DataStorage);
		}
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Exp(CIEEEFloat80 const &_Base) const
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
			return NSys::NNumeric::fg_Exp(mp_DataStorage, _Base.mp_DataStorage);
		}
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Log(CIEEEFloat80 const &_Base) const
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
			return NSys::NNumeric::fg_Log(mp_DataStorage, _Base.mp_DataStorage);
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
			return NSys::NNumeric::fg_Sqrt(mp_DataStorage);
		}
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Sqr() const
	{
		return (mp_DataStorage) * (mp_DataStorage);
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Pow(CIEEEFloat80 const &_Power) const
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
			return NSys::NNumeric::fg_Pow(mp_DataStorage, _Power.mp_DataStorage);
		}
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Integer functions
	||______________________________________________________________________________________________||
	\************************************************************************************************/

	template <> DMibFloatConstexpr inline_small CIEEEFloat80::CInteger CIEEEFloat80::f_ToInt() const
	{
		pfp80 ToLoad = mp_DataStorage;
#ifdef DMibPCanDo_int128
		return int128(ToLoad);
#else
		return int64(ToLoad);
#endif
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80::CUnsignedInteger CIEEEFloat80::f_ToUnsignedInt() const
	{
		pfp80 ToLoad = mp_DataStorage;
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
			return NSys::NNumeric::fg_Floor(mp_DataStorage);
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
			return NSys::NNumeric::fg_Ceil(mp_DataStorage);
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
			return NSys::NNumeric::fg_Abs(mp_DataStorage);
		}
	}

	template <> DMibFloatConstexpr inline_small CIEEEFloat80 CIEEEFloat80::f_Mod(TCFloat const &_Modulu) const
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
			return NSys::NNumeric::fg_Mod(mp_DataStorage, _Modulu.mp_DataStorage);
		}
	}

	template <> DMibFloatConstexpr inline_small bool CIEEEFloat80::operator == (CIEEEFloat80 const &_Value) const noexcept
	{
		return mp_DataStorage == _Value.mp_DataStorage;
	}

	template <> DMibFloatConstexpr inline_small COrdering_Partial CIEEEFloat80::operator <=> (CIEEEFloat80 const &_Value) const noexcept
	{
		return mp_DataStorage <=> _Value.mp_DataStorage;
	}
}
