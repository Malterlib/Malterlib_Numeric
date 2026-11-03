// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{
	template <typename t_CFloat, void (&t_fInit)(t_CFloat &_Float)>
	constexpr TCFloatConstant<t_CFloat, t_fInit>::TCFloatConstant(EAggregateInitialization _Init)
		: mp_bInit{}
		, mp_Float{_Init}
	{
	}

	template <typename t_CFloat, void (&t_fInit)(t_CFloat &_Float)>
	TCFloatConstant<t_CFloat, t_fInit>::operator t_CFloat const & ()
	{
		if (!mp_bInit)
		{
			mp_Float.f_Construct();
			t_fInit(*mp_Float);
			mp_bInit = true;
		}
		return *mp_Float;
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_0(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_0();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_0_5(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_0_5();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_1(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_1();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_2(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_2();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_E(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_E();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_Pi(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_Pi();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_Sqrt2(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_Sqrt2();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_Euler(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_Euler();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_GoldenRatio(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_GoldenRatio();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_Log10_2(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_Log10_2();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_Log2_10(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_Log2_10();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_Log10_E(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_Log10_E();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_LogE_10(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_LogE_10();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_Log2_E(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_Log2_E();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_LogE_2(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_LogE_2();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_Inf(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_Inf();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_NegInf(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_NegInf();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_QNan(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_QNan();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_SNan(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_SNan();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_NegQNan(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_NegQNan();
	}

	template <typename t_CFloat>
	void TCFloatConstants<t_CFloat>::fsp_Init_NegSNan(t_CFloat &_Float)
	{
		using CFloat = typename TCFloatFromNative<t_CFloat>::CType;
		((CFloat &)_Float).fp_Set_NegSNan();
	}

	template <typename tf_CFloat>
	tf_CFloat &fg_FInPlace0(tf_CFloat &_Float)
	{
		_Float = TCFloatConstants<tf_CFloat>::ms_Zero;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_F0()
	{
		return TCFloatConstants<tf_CFloat>::ms_Zero;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_F0_5()
	{
		return TCFloatConstants<tf_CFloat>::ms_Half;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_F1()
	{
		return TCFloatConstants<tf_CFloat>::ms_One;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_F2()
	{
		return TCFloatConstants<tf_CFloat>::ms_Two;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FE()
	{
		return TCFloatConstants<tf_CFloat>::ms_EulersNumber;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FPi()
	{
		return TCFloatConstants<tf_CFloat>::ms_Pi;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FSqrt2()
	{
		return TCFloatConstants<tf_CFloat>::ms_Sqrt2;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FEuler()
	{
		return TCFloatConstants<tf_CFloat>::ms_Euler;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FGoldenRatio()
	{
		return TCFloatConstants<tf_CFloat>::ms_GoldenRatio;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FLog10_2()
	{
		return TCFloatConstants<tf_CFloat>::ms_Log10_2;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FLog2_10()
	{
		return TCFloatConstants<tf_CFloat>::ms_Log2_10;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FLog10_E()
	{
		return TCFloatConstants<tf_CFloat>::ms_Log10_E;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FLogE_10()
	{
		return TCFloatConstants<tf_CFloat>::ms_LogE_10;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FLog2_E()
	{
		return TCFloatConstants<tf_CFloat>::ms_Log2_E;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FLogE_2()
	{
		return TCFloatConstants<tf_CFloat>::ms_LogE_2;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FInf()
	{
		return TCFloatConstants<tf_CFloat>::ms_Inf;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FNegInf()
	{
		return TCFloatConstants<tf_CFloat>::ms_NegInf;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FQNan()
	{
		return TCFloatConstants<tf_CFloat>::ms_QNan;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FSNan()
	{
		return TCFloatConstants<tf_CFloat>::ms_SNan;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FNegQNan()
	{
		return TCFloatConstants<tf_CFloat>::ms_NegQNan;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FNegSNan()
	{
		return TCFloatConstants<tf_CFloat>::ms_NegSNan;
	}

	template <typename tf_CFloat, typename tf_CInteger>
	tf_CFloat &fg_FInPlaceSetSignBits(tf_CFloat &_Float, tf_CInteger const &_Value)
	{
		using CFloat = typename TCFloatFromNative<tf_CFloat>::CType;

		CFloat &Float = (CFloat &)_Float;
		Float.f_SetSignBits(_Value);
		return _Float;
	}

	template <typename tf_CFloat0, typename tf_CFloat1>
	tf_CFloat0 &fg_FInPlaceArcTan(tf_CFloat0 &_Float, tf_CFloat1 const &_Source)
	{
		return fg_FInPlaceArcTan(_Float, (tf_CFloat0)_Source);
	}

	template <typename tf_CFloat0, typename tf_CFloat1>
	tf_CFloat0 &fg_FInPlaceExp(tf_CFloat0 &_Float, tf_CFloat1 const &_Base)
	{
		return fg_FInPlaceExp(_Float, (tf_CFloat0)_Base);
	}

	template <typename tf_CFloat0, typename tf_CFloat1>
	tf_CFloat0 &fg_FInPlaceLog(tf_CFloat0 &_Float, tf_CFloat1 const &_Base)
	{
		return fg_FInPlaceLog(_Float, (tf_CFloat0)_Base);
	}

	template <typename tf_CFloat0, typename tf_CFloat1>
	tf_CFloat0 &fg_FInPlacePow(tf_CFloat0 &_Float, tf_CFloat1 const &_Power)
	{
		return fg_FInPlacePow(_Float, (tf_CFloat0)_Power);
	}

	template <typename tf_CFloat0, typename tf_CFloat1>
	tf_CFloat0 &fg_FInPlaceMod(tf_CFloat0 &_Float, tf_CFloat1 const &_Modulu)
	{
		return fg_FInPlaceMod(_Float, (tf_CFloat0)_Modulu);
	}

	template <typename tf_CFloat, typename tf_CInteger>
	tf_CFloat fg_FSetSignBits(tf_CFloat const &_Float, tf_CInteger _Value)
	{
		tf_CFloat Ret = _Float;
		fg_FInPlaceSetSignBits(Ret, _Value);
		return Ret;
	}

	template <typename tf_CFloat, typename tf_CInteger>
	tf_CFloat fg_FSetExponentBits(tf_CFloat const &_Float, tf_CInteger _Value)
	{
		tf_CFloat Ret = _Float;
		fg_FInPlaceSetExponentBits(Ret, _Value);
		return Ret;
	}

	template <typename tf_CFloat, typename tf_CInteger>
	tf_CFloat fg_FSetMantissaBits(tf_CFloat const &_Float, tf_CInteger _Value)
	{
		tf_CFloat Ret = _Float;
		fg_FInPlaceSetMantissaBits(Ret, _Value);
		return Ret;
	}

	template <typename tf_CFloat, typename tf_CInteger>
	tf_CFloat fg_FSetSign(tf_CFloat const &_Float, tf_CInteger _Value)
	{
		tf_CFloat Ret = _Float;
		fg_FInPlaceSetSign(Ret, _Value);
		return Ret;
	}

	template <typename tf_CFloat, typename tf_CInteger>
	tf_CFloat fg_FSetExponent(tf_CFloat const &_Float, tf_CInteger _Value)
	{
		tf_CFloat Ret = _Float;
		fg_FInPlaceSetExponent(Ret, _Value);
		return Ret;
	}

	template <typename tf_CFloat, typename tf_CInteger>
	tf_CFloat fg_FSetMantissa(tf_CFloat const &_Float, tf_CInteger _Value)
	{
		tf_CFloat Ret = _Float;
		fg_FInPlaceSetMantissa(Ret, _Value);
		return Ret;
	}

	template <typename tf_CFloat0, typename tf_CFloat1>
	tf_CFloat0 fg_FConvertRoundUp(tf_CFloat1 const &_ConvertFrom)
	{
		tf_CFloat0 Ret;
		fg_FInPlaceConvertRoundUp(Ret, _ConvertFrom);
		return Ret;
	}

	template <typename tf_CFloat0, typename tf_CFloat1>
	tf_CFloat0 fg_FConvert(tf_CFloat1 const &_ConvertFrom)
	{
		tf_CFloat0 Ret;
		fg_FInPlaceConvert(Ret, _ConvertFrom);
		return Ret;
	}

	template <typename tf_CFloat>
	tf_CFloat fg_FArcTan(tf_CFloat const &_Float, tf_CFloat const &_Source)
	{
		using CFloat = typename TCFloatFromNative<tf_CFloat>::CType;

		CFloat const &Float = _Float;
		CFloat const &Source = _Source;
		return Float.f_ArcTan(Source).f_Get();
	}

	template <typename tf_CFloat0, typename tf_CFloat1>
	typename TCFloatCombinedType<tf_CFloat0, tf_CFloat1>::CType fg_FArcTan(tf_CFloat0 const &_Float, tf_CFloat1 const &_Source)
	{
		using CCombinedFloat = typename TCFloatCombinedType<tf_CFloat0, tf_CFloat1>::CType;

		CCombinedFloat Float{_Float};
		CCombinedFloat Source{_Source};
		return fg_FArcTan(Float, Source);
	}
}
