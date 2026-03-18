// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NNumeric
{
	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_AssignRoundUp
		(
			TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_SetValue
		)
	{
		using COtherFloat = TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>;
		COtherFloat Other = _SetValue;

		auto SignBits = fg_Convert<CInteger>(Other.f_GetSignBits());

		constexpr CInteger ExponentMaxNeg = -((CInteger(1) << (aint)(mc_ExponentBits - 1)) - CInteger(1));
		constexpr CInteger ExponentMax = fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits);

		TCFloat EndMul = fs_1();
		CInteger ExponentBits;
		if (Other.f_GetExponentBits() == 0) // Check for denormalized and 0.0
			ExponentBits = fg_Convert<CInteger>(0);
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
				ExponentBits = CInteger(1);
				EndMul.f_SetAllBits(0, fs_GetExponentBits(ExpDiff), 0);
			}
			else
				ExponentBits = fs_GetExponentBits(fg_Convert<CInteger>(Exponent));
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
				ExponentBits = fs_GetExponentBits(Exponent);
			}
			Temp >>= nBits;
			f_SetAllBits(SignBits, ExponentBits, fg_Convert<CInteger>(Temp));
		}
		else
		{
			uaint nBits = (uaint(mc_MantissaBits) - uaint(COtherFloat::mc_MantissaBits));
			f_SetAllBits(SignBits, ExponentBits, fg_Convert<CInteger>(Other.f_GetMantissaBits()) << nBits);
		}

		*this *= EndMul;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Assign
		(
			TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_SetValue
		)
	{
		using COtherFloat = TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>;
		COtherFloat Other = _SetValue;

		auto SignBits = fg_Convert<CInteger>(Other.f_GetSignBits());

		using CLargestInteger = NTraits::TCLargestType<CInteger, typename COtherFloat::CInteger>;

		constexpr CLargestInteger ExponentBias = fg_PowerOfTwoMinusOne<CLargestInteger>(mc_ExponentBits - 1);
		constexpr CLargestInteger ExponentMax = fg_PowerOfTwoMinusOne<CLargestInteger>(mc_ExponentBits) - ExponentBias;
		constexpr CLargestInteger ExponentMaxNeg = -((CLargestInteger(1) << (uaint(sizeof(CInteger)*8 - 2))) - CLargestInteger(1));

		typename COtherFloat::CInteger OtherExponent;
		typename COtherFloat::CInteger OtherMantissa;
		Other.f_GetNormalized(OtherExponent, OtherMantissa);

		TCFloat EndMul = fs_1();
		if (Other.f_GetMantissaBits() == 0 && Other.f_GetExponentBits() == 0) // Check for 0.0
		{
			f_SetAllBits(SignBits, fg_Convert<CInteger>(0), fg_Convert<CInteger>(0));
			return;
		}
		else
		{
			if (!Other.f_IsInvalid())
			{
				CLargestInteger Exponent = fg_Convert<CLargestInteger>(OtherExponent);

				if (Exponent >= ExponentMax)
				{
					f_SetAllBits(SignBits, fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits), 0);
					return;
				}
				else if (Exponent < ExponentMaxNeg)
				{
					// Integer underflow
					f_SetAllBits(SignBits, 0, 0);
					return;
				}
			}
			else if (Other.f_IsInfinity())
			{
				f_SetAllBits(SignBits, fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits), 0);
				return;
			}
			else if (Other.f_IsQNan())
			{
				CInteger Mask = 1;
				if (uaint(COtherFloat::mc_MantissaBits) > uaint(mc_MantissaBits))
				{
					uaint nBits = (uaint(COtherFloat::mc_MantissaBits) - uaint(mc_MantissaBits));
					f_SetAllBits(SignBits, fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits), (fg_Convert<CInteger>(Other.f_GetMantissaBits() >> nBits)) | Mask);
				}
				else
				{
					uaint nBits = (uaint(mc_MantissaBits) - uaint(COtherFloat::mc_MantissaBits));
					f_SetAllBits(SignBits, fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits), (fg_Convert<CInteger>((Other.f_GetMantissaBits() & ~(typename COtherFloat::CInteger(1))) << nBits)) | Mask);
				}
				return;
			}
			else if (Other.f_IsSNan())
			{
				CInteger Mask = 1;
				if (uaint(COtherFloat::mc_MantissaBits) > uaint(mc_MantissaBits))
				{
					uaint nBits = (uaint(COtherFloat::mc_MantissaBits) - uaint(mc_MantissaBits));
					f_SetAllBits(SignBits, fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits), (fg_Convert<CInteger>(Other.f_GetMantissaBits() >> nBits)) | Mask);
				}
				else
				{
					uaint nBits = (uaint(mc_MantissaBits) - uaint(COtherFloat::mc_MantissaBits));
					f_SetAllBits(SignBits, fg_PowerOfTwoMinusOne<CInteger>(mc_ExponentBits), (fg_Convert<CInteger>((Other.f_GetMantissaBits() & ~(typename COtherFloat::CInteger(1))) << nBits)) | Mask);
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
			f_SetAllRound
				(
					fg_Convert<CInteger>(Other.f_GetSignBits())
					, fg_Convert<CInteger>(OtherExponent)
					, fg_Convert<CDoubleUnsignedInteger>((OtherMantissa >> nBitsLost))
					, nBits - nBitsLost
				)
			;
		}
		else
		{
			uaint nBits = (uaint(mc_MantissaBits) - uaint(COtherFloat::mc_MantissaBits));
			f_SetAllRound(fg_Convert<CInteger>(Other.f_GetSignBits()), fg_Convert<CInteger>(OtherExponent), fg_Convert<CDoubleUnsignedInteger>(OtherMantissa) << nBits, 0);
		}

		*this *= EndMul;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator =
		(
			TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_SetValue
		)
		-> TCFloat &
	{
		f_Assign(_SetValue);
		return *this;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatInlineS TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::TCFloat
		(
			TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_SetValue
		)
	{
		f_Assign(_SetValue);
#ifdef DMibDebuggerHelpers
		static_assert(TCInstantiateValue<&TCFloat::f_Debug_GetAsDouble>::mc_Value);
#endif
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename t_CInteger>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_FromInt(const t_CInteger &_Int) -> TCFloat
	{
		TCFloat Ret;
		Ret.f_FromInt(_Int);
		return Ret;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename t_CInteger>
	DMibFloatConstexpr void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_FromInt(const t_CInteger &_Int)
	{
		aint IntegerBits = sizeof(_Int) * 8;
		CInteger Sign = 0;
		using CLargestInteger = NTraits::TCLargestType<CInteger, t_CInteger>;

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

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename tf_CType>
	DMibFloatInlineS TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::TCFloat
		(
			tf_CType _Value
			, TCEnableIf<NTraits::cIsSame<tf_CType, bool>> *_pDummy
		)
	{
		*this = _Value ? fs_1() : fs_0();
#ifdef DMibDebuggerHelpers
		static_assert(TCInstantiateValue<&TCFloat::f_Debug_GetAsDouble>::mc_Value);
#endif
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename tf_CType>
	DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator = (tf_CType _Value)
		-> TCEnableIf<NTraits::cIsSame<tf_CType, bool>, TCFloat &>
	{
		*this = _Value ? fs_1() : fs_0();
		return *this;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator +
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Value
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).operator + (COperationType(_Value));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator -
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Value
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).operator - (COperationType(_Value));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator *
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Value
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).operator *(COperationType(_Value));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator /
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Value
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).operator / (COperationType(_Value));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ArcTan
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Source
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).f_ArcTan(COperationType(_Source));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Exp
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Base
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).f_Exp(COperationType(_Base));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Log
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Base
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).f_Log(COperationType(_Base));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Pow
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Power
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).f_Pow(COperationType(_Power));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Mod
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Modulu
		) const
		-> NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>>
	{
		using COperationType = NTraits::TCLargestType
			<
				TCFloat
				, NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>
			>
		;

		return COperationType(*this).f_Mod(COperationType(_Modulu));
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr bool TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator ==
		(
			NMib::NNumeric::TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Right
		) const noexcept
	{
		return (*this <=> _Right) == COrdering_Partial::equivalent;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <aint tf_SignBits, aint tf_ExponentBits, aint tf_MantissaBits, aint tf_PaddingBits, typename tf_CImplicitFloat, bool tf_bDummyOptimize, typename tf_CIntegerStorage>
	DMibFloatConstexpr COrdering_Partial TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator <=>
		(
			TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage> const &_Right
		) const noexcept
	{
		if (f_IsNan() || _Right.f_IsNan())
			return COrdering_Partial::unordered;

		using CLeftFloat = TCFloat;
		using CRightFloat = TCFloat<tf_SignBits, tf_ExponentBits, tf_MantissaBits, tf_PaddingBits, tf_CImplicitFloat, tf_bDummyOptimize, tf_CIntegerStorage>;

		using CLeftInteger = typename CLeftFloat::CInteger;
		using CRightInteger = typename CRightFloat::CInteger;
		using CBiggerInteger = TCConditional<sizeof(CLeftInteger) >= sizeof(CRightInteger), CLeftInteger, CRightInteger>;

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
