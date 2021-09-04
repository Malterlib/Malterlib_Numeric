// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NNumeric
{
	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_AssignRoundUp(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue)
	{
		typedef TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> COtherFloat;
		COtherFloat Other = _SetValue;

		f_SetSignBits(fg_Convert<CInteger>(Other.f_GetSignBits()));

		constexpr CInteger ExponentMaxNeg = -((CInteger(1) << (aint)(mc_ExponentBits - 1)) - CInteger(1));
		constexpr CInteger ExponentMax = fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits);

		TCFloat EndMul = fs_1();
		if (Other.f_GetExponentBits() == 0) // Check for denormalized and 0.0
		{
			f_SetExponentBits(fg_Convert<CInteger>(0));
		}
		else
		{
			typename COtherFloat::CInteger Exponent = Other.f_GetExponent();

			if (fg_Convert<CInteger>(Exponent) >= ExponentMax)
			{
				*this = fs_Inf();
				return;
			}
			else if (fg_Convert<CInteger>(Exponent) <= ExponentMaxNeg)
			{
				CInteger ExpDiff = fg_Convert<CInteger>(Exponent) - ExponentMaxNeg - 1;
				if (ExpDiff < ExponentMaxNeg + 1)
				{
					*this = fs_0();
					return;
				}
				// Set denormalized
				f_SetExponentBits(CInteger(1));
				EndMul.f_SetExponent(ExpDiff);
				EndMul.f_SetMantissa(CInteger(0));
			}
			else
				f_SetExponent(fg_Convert<CInteger>(Exponent));
		}

		if (uaint(COtherFloat::mc_MantissaBits) > uaint(mc_MantissaBits))
		{
			uaint nBits = (uaint(COtherFloat::mc_MantissaBits) - uaint(mc_MantissaBits));
			typename COtherFloat::CInteger Temp = Other.f_GetMantissaBits() + ((typename COtherFloat::CInteger(1) << nBits) - 1);
			typename COtherFloat::CInteger Largest = typename COtherFloat::CInteger(1) << uaint(COtherFloat::mc_MantissaBits);
			if (Temp >= Largest)
			{
				CInteger Exponent = f_GetExponent() + CInteger(1);
				if (Exponent >= ExponentMax)
				{
					*this = fs_Inf();
					return;
				}
				f_SetExponent(Exponent);
			}
			Temp >>= nBits;
			f_SetMantissaBits(fg_Convert<CInteger>(Temp));
		}
		else
		{
			uaint nBits = (uaint(mc_MantissaBits) - uaint(COtherFloat::mc_MantissaBits));
			f_SetMantissaBits(fg_Convert<CInteger>(Other.f_GetMantissaBits()) << nBits);
		}

		*this *= EndMul;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Assign(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue)
	{
		typedef TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> COtherFloat;
		COtherFloat Other = _SetValue;

		f_SetSignBits(fg_Convert<CInteger>(Other.f_GetSignBits()));

		using CLargestInteger = typename NTraits::TCLargestType<CInteger, typename COtherFloat::CInteger>::CType;

		constexpr CLargestInteger ExponentBias = fg_PowerOfTwoMinusOne<CLargestInteger>(mc_ExponentBits - 1);
		constexpr CLargestInteger ExponentMax = fg_PowerOfTwoMinusOne<CLargestInteger>(mc_ExponentBits) - ExponentBias;
		constexpr CLargestInteger ExponentMaxNeg = -((CLargestInteger(1) << (uaint(sizeof(CInteger)*8 - 2))) - CLargestInteger(1));

		typename COtherFloat::CInteger OtherExponent;
		typename COtherFloat::CInteger OtherMantissa;
		Other.f_GetNormalized(OtherExponent, OtherMantissa);

		TCFloat EndMul = fs_1();
		if (Other.f_GetMantissaBits() == 0 && Other.f_GetExponentBits() == 0) // Check for 0.0
		{
			f_SetExponentBits(fg_Convert<CInteger>(0));
			f_SetMantissaBits(fg_Convert<CInteger>(0));
			return;
		}
		else
		{
			if (!Other.f_IsInvalid())
			{
				CLargestInteger Exponent = fg_Convert<CLargestInteger>(OtherExponent);

				if (Exponent >= ExponentMax)
				{
					f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits));
					f_SetMantissaBits(0);
					return;
				}
				else if (Exponent < ExponentMaxNeg)
				{
					// Integer underflow
					f_SetExponentBits(0);
					f_SetMantissaBits(0);
					return;
				}
			}
			else if (Other.f_IsInfinity())
			{
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits));
				f_SetMantissaBits(0);
				return;
			}
			else if (Other.f_IsQNan())
			{
				CInteger Mask = 1;
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits));
				if (uaint(COtherFloat::mc_MantissaBits) > uaint(mc_MantissaBits))
				{
					uaint nBits = (uaint(COtherFloat::mc_MantissaBits) - uaint(mc_MantissaBits));
					f_SetMantissaBits((fg_Convert<CInteger>(Other.f_GetMantissaBits() >> nBits)) | Mask);
				}
				else
				{
					uaint nBits = (uaint(mc_MantissaBits) - uaint(COtherFloat::mc_MantissaBits));
					f_SetMantissaBits((fg_Convert<CInteger>((Other.f_GetMantissaBits() & ~(typename COtherFloat::CInteger(1))) << nBits)) | Mask);
				}
				return;
			}
			else if (Other.f_IsSNan())
			{
				CInteger Mask = 1;
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits));
				if (uaint(COtherFloat::mc_MantissaBits) > uaint(mc_MantissaBits))
				{
					uaint nBits = (uaint(COtherFloat::mc_MantissaBits) - uaint(mc_MantissaBits));
					f_SetMantissaBits((fg_Convert<CInteger>(Other.f_GetMantissaBits() >> nBits)) | Mask);
				}
				else
				{
					uaint nBits = (uaint(mc_MantissaBits) - uaint(COtherFloat::mc_MantissaBits));
					f_SetMantissaBits((fg_Convert<CInteger>((Other.f_GetMantissaBits() & ~(typename COtherFloat::CInteger(1))) << nBits)) | Mask);
				}
				return;
			}
		}

		if (uaint(COtherFloat::mc_MantissaBits) > uaint(mc_MantissaBits))
		{
			uaint nBits = (uaint(COtherFloat::mc_MantissaBits) - uaint(mc_MantissaBits));
			uaint nBitsLost = 0;
			if constexpr (uaint(COtherFloat::mc_MantissaBits) > uaint(sizeof(CDoubleInteger)*8-1))
				nBitsLost = uaint(COtherFloat::mc_MantissaBits) - uaint(sizeof(CDoubleInteger)*8-1);
			f_SetAllRound(fg_Convert<CInteger>(Other.f_GetSignBits()), fg_Convert<CInteger>(OtherExponent), fg_Convert<CDoubleUnsignedInteger>((OtherMantissa >> nBitsLost)), nBits - nBitsLost);
		}
		else
		{
			uaint nBits = (uaint(mc_MantissaBits) - uaint(COtherFloat::mc_MantissaBits));
			f_SetAllRound(fg_Convert<CInteger>(Other.f_GetSignBits()), fg_Convert<CInteger>(OtherExponent), fg_Convert<CDoubleUnsignedInteger>(OtherMantissa) << nBits, 0);
		}

		*this *= EndMul;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator = (const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue) -> TCFloat &
	{
		f_Assign(_SetValue);
		return *this;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatInlineS TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::TCFloat(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue)
	{
		f_Assign(_SetValue);
#ifdef DMibDebuggerHelpers
		static_assert(TCInstantiateValue<&TCFloat::f_Debug_GetAsDouble>::mc_Value);
#endif
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename t_CInteger>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_FromInt(const t_CInteger &_Int) -> TCFloat
	{
		TCFloat Ret;
		Ret.f_FromInt(_Int);
		return Ret;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename t_CInteger>
	DMibFloatConstexpr void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_FromInt(const t_CInteger &_Int)
	{
		aint IntegerBits = sizeof(_Int) * 8;
		CInteger Sign = 0;
		using CLargestInteger = typename NTraits::TCLargestType<CInteger, t_CInteger>::CType;

		CLargestInteger Int;
		if (_Int < 0)
		{
			Int = fg_Convert<CLargestInteger>(-_Int);
			Sign = 1;
		}
		else
		{
			Int = fg_Convert<CLargestInteger>(_Int);
		}

		if (IntegerBits > mc_MantissaBits && (Int > (CLargestInteger(1) << (aint)(mc_MantissaBits))))
		{
			CInteger Exponent = fg_Convert<CInteger>(IntegerBits);
			CDoubleUnsignedInteger Mantissa;
			Mantissa = fg_Convert<CDoubleUnsignedInteger>((Int >> (IntegerBits - (aint)(mc_MantissaBits))));

			f_SetAllRound(Sign, Exponent, Mantissa, 0);
		}
		else if(Int == 0)
		{
			*this = fs_0();
		}
		else
		{
			CDoubleUnsignedInteger Mantissa = fg_Convert<CDoubleInteger>(Int);
			constexpr CDoubleUnsignedInteger MaxMantissa = CDoubleUnsignedInteger(1) << (aint)(mc_MantissaBits);

			CInteger Exponent = (aint)(mc_MantissaBits);
			while (Mantissa < MaxMantissa)
			{
				Mantissa <<= 1;
				--Exponent;
			}

			f_SetAllRound(Sign, Exponent, Mantissa, 0);
		}
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename tf_CType>
	DMibFloatInlineS TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::TCFloat(tf_CType _Value, typename TCEnableIf<NTraits::TCIsSame<tf_CType, bool>::mc_Value>::CType *_pDummy)
	{
		*this = _Value ? fs_1() : fs_0();
#ifdef DMibDebuggerHelpers
		static_assert(TCInstantiateValue<&TCFloat::f_Debug_GetAsDouble>::mc_Value);
#endif
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename tf_CType>
	DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator = (tf_CType _Value) -> typename TCEnableIf<NTraits::TCIsSame<tf_CType, bool>::mc_Value, TCFloat &>::CType
	{
		*this = _Value ? fs_1() : fs_0();
		return *this;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator + (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).operator + (COperationType(_Value));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator - (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).operator - (COperationType(_Value));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator * (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).operator *(COperationType(_Value));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator / (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).operator / (COperationType(_Value));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ArcTan(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Source) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).f_ArcTan(COperationType(_Source));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Exp(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).f_Exp(COperationType(_Base));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Log(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).f_Log(COperationType(_Base));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Pow(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Power) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).f_Pow(COperationType(_Power));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Mod(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Modulu) const -> typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType
	{
		typedef typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

		return COperationType(*this).f_Mod(COperationType(_Modulu));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr bool TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator ==
		(
			NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right
		) const
	{
		return (*this <=> _Right) == COrdering_Partial::equivalent;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
	DMibFloatConstexpr COrdering_Partial TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator <=>
		(
			TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right
		) const
	{
		if (f_IsNan() || _Right.f_IsNan())
			return COrdering_Partial::unordered;

		typedef TCFloat CLeftFloat;
		typedef TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> CRightFloat;

		using CLeftInteger = typename CLeftFloat::CInteger;
		using CRightInteger = typename CRightFloat::CInteger;
		using CBiggerInteger = typename TCChooseType<sizeof(CLeftInteger) >= sizeof(CRightInteger), CLeftInteger, CRightInteger>::CType;

		CLeftInteger ExponentLeftGet;
		CRightInteger ExponentRightGet;
		CLeftInteger MantissaLeft;
		CRightInteger MantissaRight;
		f_GetNormalized(ExponentLeftGet, MantissaLeft);
		_Right.f_GetNormalized(ExponentRightGet, MantissaRight);

		CBiggerInteger ExponentLeft = fg_Convert<CBiggerInteger>(ExponentLeftGet);
		CBiggerInteger ExponentRight = fg_Convert<CBiggerInteger>(ExponentRightGet);

		CBiggerInteger SignLeft = fg_Convert<CBiggerInteger>(f_GetSign());
		CBiggerInteger SignRight = fg_Convert<CBiggerInteger>(_Right.f_GetSign());

		if (MantissaLeft == 0 && MantissaRight == 0)
			return COrdering_Partial::equivalent;

		if (SignLeft < SignRight)
			return COrdering_Partial::less;
		else if (SignLeft > SignRight)
			return COrdering_Partial::greater;

		if (SignLeft > CBiggerInteger(0))
		{
			if (ExponentLeft < ExponentRight)
				return COrdering_Partial::less;
			else if (ExponentLeft > ExponentRight)
				return COrdering_Partial::greater;

			if constexpr (uaint(CLeftFloat::mc_MantissaBits) > uaint(CRightFloat::mc_MantissaBits))
			{
				uaint nBits = (uaint(CLeftFloat::mc_MantissaBits) - uaint(CRightFloat::mc_MantissaBits));
				CLeftInteger LeftMantissa = MantissaLeft;
				CLeftInteger RightMantissa = CLeftFloat::CInteger(MantissaRight) << nBits;

				if (LeftMantissa < RightMantissa)
					return COrdering_Partial::less;
				else if (LeftMantissa > RightMantissa)
					return COrdering_Partial::greater;
			}
			else
			{
				uaint nBits = (uaint(CRightFloat::mc_MantissaBits) - uaint(CLeftFloat::mc_MantissaBits));
				CRightInteger LeftMantissa = CRightInteger(MantissaLeft) << nBits;
				CRightInteger RightMantissa = MantissaRight;

				if (LeftMantissa < RightMantissa)
					return COrdering_Partial::less;
				else if (LeftMantissa > RightMantissa)
					return COrdering_Partial::greater;
			}
		}
		else
		{
			if (ExponentLeft > ExponentRight)
				return COrdering_Partial::less;
			else if (ExponentLeft < ExponentRight)
				return COrdering_Partial::greater;

			if constexpr (uaint(CLeftFloat::mc_MantissaBits) > uaint(CRightFloat::mc_MantissaBits))
			{
				uaint nBits = (uaint(CLeftFloat::mc_MantissaBits) - uaint(CRightFloat::mc_MantissaBits));
				CLeftInteger LeftMantissa = MantissaLeft;
				CLeftInteger RightMantissa = CLeftInteger(MantissaRight) << nBits;

				if (LeftMantissa > RightMantissa)
					return COrdering_Partial::less;
				else if (LeftMantissa < RightMantissa)
					return COrdering_Partial::greater;
			}
			else
			{
				uaint nBits = (uaint(CRightFloat::mc_MantissaBits) - uaint(CLeftFloat::mc_MantissaBits));
				CRightInteger LeftMantissa = CRightInteger(MantissaLeft) << nBits;
				CRightInteger RightMantissa = MantissaRight;

				if (LeftMantissa > RightMantissa)
					return COrdering_Partial::less;
				else if (LeftMantissa < RightMantissa)
					return COrdering_Partial::greater;
			}
		}

		return COrdering_Partial::equivalent;
	}
}
