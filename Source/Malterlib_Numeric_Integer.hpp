// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{
	template <typename t_CUpper, typename t_CLower>
	constexpr TCInt<t_CUpper, t_CLower>::TCInt(t_CUpper _Upper, t_CLower _Lower)
		: m_Upper(_Upper)
		, m_Lower(_Lower)
	{
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr TCInt<t_CUpper, t_CLower>::TCInt(t_CLower _Lower)
		: m_Lower(_Lower)
	{
	}

	template <typename t_CUpper, typename t_CLower>
	template <typename tf_CUpper2, typename tf_CLower2>
	constexpr auto TCInt<t_CUpper, t_CLower>::f_GetAsTCInt() const -> TCInt<tf_CUpper2, tf_CLower2>
	{
		if constexpr (sizeof(tf_CUpper2) + sizeof(tf_CLower2) <= sizeof(t_CLower))
		{
			// Less than lower
			return m_Lower;
		}
		else
		{
			using CType = TCInt<tf_CUpper2, tf_CLower2>;
			CType Ret;
			if constexpr (sizeof(tf_CUpper2) > sizeof(TCInt))
			{
				TCConditional<NTraits::cIsSigned<t_CUpper>, NTraits::TCSigned<tf_CUpper2>, tf_CUpper2> Temp{*this};
				Temp >>= CType::mc_LowerBits - 1;
				Temp >>= 1;
				Ret.m_Upper = tf_CUpper2(Temp);
			}
			else
				Ret.m_Upper = tf_CUpper2((((*this) >> uaint(CType::mc_LowerBits - 1) >> uaint(1))));
			if constexpr (sizeof(tf_CLower2) > sizeof(TCInt))
			{
				TCConditional<NTraits::cIsSigned<t_CUpper>, NTraits::TCSigned<tf_CLower2>, tf_CLower2> Temp{*this};
				Ret.m_Lower = tf_CLower2(Temp);
			}
			else
			{
				constexpr TCInt c_LowerMask = fg_BitRange<TCInt>(0, CType::mc_LowerBits - 1);
				Ret.m_Lower = tf_CLower2(((*this) & c_LowerMask));
			}
			return Ret;
		}
	}

	template <typename t_CUpper, typename t_CLower>
	template <typename tf_CInt>
	constexpr TCInt<t_CUpper, t_CLower>::operator tf_CInt () const
	{
		static_assert(NTraits::cIsInteger<tf_CInt>, "Must be an integer type");
		if constexpr (sizeof(tf_CInt) <= sizeof(t_CLower))
		{
			// Less than lower
			return tf_CInt(m_Lower);
		}
		else
		{
			tf_CInt Ret;
			using CLargestInt = NTraits::TCLargestType<tf_CInt, t_CUpper>;
			Ret = tf_CInt((CLargestInt(m_Upper) << (fg_Min((umint)mc_LowerBits, sizeof(CLargestInt) * 8) - 1)) << 1);
			Ret = Ret | tf_CInt(m_Lower);
			return Ret;
		}
	}

	template <typename t_CUpper, typename t_CLower>
	template <typename tf_CType>
	constexpr TCInt<t_CUpper, t_CLower>::TCInt(tf_CType const &_Convert, TCEnableIf<NTraits::cIsFundamental<tf_CType>, NPrivate::CDummy &> _Dummy)
		: m_Upper(((_Convert >> (fg_Min((umint)mc_LowerBits, sizeof(tf_CType) * 8) - 1)) >> 1))
		, m_Lower((_Convert & fg_BitRange<tf_CType>(0, fg_Min((umint)mc_LowerBits - 1, sizeof(tf_CType) * 8 - 1))))
	{
	}

	template <typename t_CUpper, typename t_CLower>
	template <typename tf_CUpper2, typename tf_CLower2>
	constexpr TCInt<t_CUpper, t_CLower>::TCInt(TCInt<tf_CUpper2, tf_CLower2> const &_Other)
	{
		*this = _Other.template f_GetAsTCInt<t_CUpper, t_CLower>();
	}

	template <typename t_CUpper, typename t_CLower>
	template <typename tf_CType>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator = (tf_CType const &_Convert) -> TCInt &
	{
		constexpr tf_CType c_LowerMask = fg_BitRange<tf_CType>(0, fg_Min((umint)mc_LowerBits - 1, sizeof(tf_CType) * 8 - 1));
		m_Upper = t_CUpper(((_Convert >> (fg_Min((umint)mc_LowerBits, sizeof(tf_CType) * 8) - 1)) >> 1));
		m_Lower = t_CLower((_Convert & c_LowerMask));
		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator - () const -> TCInt
	{
		return CConstants::mc_Zero - (*this);
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator + () const -> TCInt
	{
		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator ~ () const -> TCInt
	{
		TCInt Ret;
		Ret.m_Upper = ~m_Upper;
		Ret.m_Lower = ~m_Lower;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr TCInt<t_CUpper, t_CLower>::operator bool () const
	{
		return m_Upper != mc_UpperZero || m_Lower != mc_LowerZero;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator ++ () -> TCInt &
	{
		*this = *this + CConstants::mc_One;
		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator -- () -> TCInt &
	{
		*this = *this - CConstants::mc_One;
		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator ++ (int) -> TCInt
	{
		TCInt Ret = *this;
		++(*this);
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator -- (int) -> TCInt
	{
		TCInt Ret = *this;
		--(*this);
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator + (TCInt const &_Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret += _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator - (TCInt const &_Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret -= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator * (TCInt const &_Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret *= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator / (TCInt const &_Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret /= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator >> (uaint _Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret >>= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator << (uaint _Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret <<= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator % (TCInt const &_Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret %= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator & (TCInt const &_Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret &= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator | (TCInt const &_Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret |= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator ^ (TCInt const &_Value) const -> TCInt
	{
		TCInt Ret = *this;
		Ret ^= _Value;
		return Ret;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr bool TCInt<t_CUpper, t_CLower>::operator && (TCInt const &_Value) const
	{
		return (m_Upper != mc_UpperZero || m_Lower != mc_LowerZero) && (_Value.m_Upper != mc_UpperZero || _Value.m_Lower != mc_LowerZero);
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr bool TCInt<t_CUpper, t_CLower>::operator || (TCInt const &_Value) const
	{
		return (m_Upper != mc_UpperZero || m_Lower != mc_LowerZero) || (_Value.m_Upper != mc_UpperZero || _Value.m_Lower != mc_LowerZero);
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator += (TCInt const &_Value) -> TCInt &
	{
		t_CLower Lower0 = m_Lower;
		t_CLower Lower1 = _Value.m_Lower;
		m_Lower = Lower0 + Lower1;

		m_Upper += _Value.m_Upper;

		constexpr t_CLower c_HalfLower = (t_CLower(1) << (aint)(mc_LowerLastBit));
		constexpr t_CLower c_BelowHalfMask = ((t_CLower(1) << (aint)(mc_LowerLastBit)) - t_CLower(1));
		if (Lower0 >= c_HalfLower)
		{
			if (Lower1 >= c_HalfLower)
				m_Upper += 1;
			else if (((Lower0 & c_BelowHalfMask) + (Lower1 & c_BelowHalfMask)) >= c_HalfLower)
				m_Upper += 1;
		}
		else if (Lower1 >= c_HalfLower)
		{
			if (((Lower0 & c_BelowHalfMask) + (Lower1 & c_BelowHalfMask)) >= c_HalfLower)
				m_Upper += 1;
		}

		/*
		static const t_CLower And0 = (t_CLower(1) << ELowerLastBit);
		static const t_CLower And1 = ((t_CLower(1) << ELowerLastBit) - t_CLower(1));

		if ((((((Lower0 ^ Lower1) & ((Lower0 & And1) + (Lower1 & And1))) | (Lower0 & Lower1)) & And0)) != 0)
		{
			m_Upper += _Value.m_Upper;
			m_Upper += 1;
		}
		else
			m_Upper += _Value.m_Upper;*/

		// m_Upper += _Value.m_Upper + ((((((Lower0 ^ Lower1) & ((Lower0 & And1) + (Lower1 & And1))) | (Lower0 & Lower1)) & And0)) >> ELowerLastBit);

		// m_Upper += _Value.m_Upper + ((((((Lower0 ^ Lower1) & ((Lower0 & ((t_CLower(1) << ELowerLastBit) - t_CLower(1)))
		// 	+ (Lower1 & ((t_CLower(1) << ELowerLastBit) - t_CLower(1))))) | (Lower0 & Lower1)) & (t_CLower(1) << ELowerLastBit))) >> ELowerLastBit);

		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator -= (TCInt const &_Value) -> TCInt &
	{
		t_CLower Lower0 = m_Lower;
		t_CLower Lower1 = _Value.m_Lower;
#ifdef DCompiler_MSVC_Workaround
		m_Lower = t_CLower(m_Lower - Lower1) & TCLimitsInt<t_CLower>::mc_AllBits;
#else
		m_Lower -= Lower1;
#endif
		m_Upper -= _Value.m_Upper;
		if (Lower1 > Lower0)
			m_Upper -= 1;

		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator *= (TCInt const &_Value) -> TCInt &
	{
		bool bSigned = false;
		TCInt Val0 = *this;
		TCInt Val1 = _Value;
		if (NTraits::cIsSigned<t_CUpper> && Val0 < CConstants::mc_Zero)
		{
			Val0 = -Val0;
			if (Val1 < CConstants::mc_Zero)
				Val1 = -Val1;
			else
				bSigned = true;
		}
		else if (NTraits::cIsSigned<t_CUpper> && Val1 < CConstants::mc_Zero)
		{
			Val1 = -Val1;
			bSigned = true;
		}

		TCInt Result = CConstants::mc_Zero;

		// // Multiply half the bits first
		t_CLower And0 = DMibBitRangeOne(0, (mc_LowerBits / 2) - 1, mc_LowerOne);
		t_CLower Lower0 = Val0.m_Lower & And0;
		t_CLower Lower1 = Val1.m_Lower & And0;

		Result += TCInt(mc_UpperZero, (Lower0) * (Lower1));

		t_CLower Lower2 = Val1.m_Lower >> (mc_LowerBits / 2);
		t_CLower Lower3 = Val0.m_Lower >> (mc_LowerBits / 2);

		// Multily lower with upper bits and add
		Result += TCInt(mc_UpperZero, Lower0 * Lower2) << uaint(mc_LowerBits / 2);
		Result += TCInt(mc_UpperZero, Lower1 * Lower3) << uaint(mc_LowerBits / 2);

		// // Multily upper bits and add
		Result += TCInt(mc_UpperZero, Lower2 * Lower3) << uaint(mc_LowerBits);

		// Multiply Upper by lower and let it owerflow
		Result += TCInt(Val0.m_Upper * Val1.m_Lower, mc_LowerZero);
		Result += TCInt(Val1.m_Upper * Val0.m_Lower, mc_LowerZero);
		if constexpr (sizeof(t_CLower) < sizeof(t_CUpper))
			Result += TCInt(Val0.m_Upper * Val1.m_Upper, 0) << mc_LowerBits;

		if (NTraits::cIsSigned<t_CUpper> && bSigned)
			*this = -Result;
		else
			*this = Result;

		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr bool TCInt<t_CUpper, t_CLower>::fs_IsBitSet(uaint _Bit)
	{
		return false;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator /= (TCInt const &_Value) -> TCInt &
	{
		bool bSigned = false;
		TCInt Val0 = *this;
		TCInt Val1 = _Value;
		if (NTraits::cIsSigned<t_CUpper> && Val0 < CConstants::mc_Zero)
		{
			Val0 = -Val0;
			if (Val1 < CConstants::mc_Zero)
				Val1 = -Val1;
			else
				bSigned = true;
		}
		else if (NTraits::cIsSigned<t_CUpper> && Val1 < CConstants::mc_Zero)
		{
			Val1 = -Val1;
			bSigned = true;
		}

		// Do dumb divide
		TCInt Result = Val0;
		TCInt Remainder = CConstants::mc_Zero;
		t_CUpper UppestBit = mc_UpperOne << (mc_UpperBits - 1);
		int iBit = 0;
		for (; iBit < (mc_LowerBits + mc_UpperBits); ++iBit)
		{
			if ((Result.m_Upper & UppestBit) != mc_UpperZero)
				break;
			Result <<= 1;
		}

		for (; iBit < (mc_LowerBits + mc_UpperBits); ++iBit)
		{
			Remainder <<= 1;
			if ((Result.m_Upper & UppestBit) != mc_UpperZero)
				Remainder.m_Lower |= mc_LowerOne;
			Result <<= 1;

			if (Remainder >= Val1)
			{
				Remainder -= Val1;
				++Result;
			}
		}

		if (NTraits::cIsSigned<t_CUpper> && bSigned)
			*this = -Result;
		else
			*this = Result;

		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator %= (TCInt const &_Value) -> TCInt &
	{
		bool bSigned = false;
		TCInt Val0 = *this;
		TCInt Val1 = _Value;
		if (NTraits::cIsSigned<t_CUpper> && Val0 < CConstants::mc_Zero)
		{
			Val0 = -Val0;
			bSigned = true;
		}

		if (NTraits::cIsSigned<t_CUpper> && Val1 < CConstants::mc_Zero)
			Val1 = -Val1;

		// Do dumb divide
		TCInt Result = Val0;
		TCInt Remainder = CConstants::mc_Zero;
		t_CUpper UppestBit = mc_UpperOne << (mc_UpperBits - 1);
		int iBit = 0;
		for (; iBit < (mc_LowerBits + mc_UpperBits); ++iBit)
		{
			if ((Result.m_Upper & UppestBit) != mc_UpperZero)
				break;
			Result <<= 1;
		}

		for (; iBit < (mc_LowerBits + mc_UpperBits); ++iBit)
		{
			Remainder <<= 1;
			if ((Result.m_Upper & UppestBit) != mc_UpperZero)
				Remainder.m_Lower |= mc_LowerOne;
			Result <<= 1;

			if (Remainder >= Val1)
			{
				Remainder -= Val1;
				++Result;
			}
		}

		if (NTraits::cIsSigned<t_CUpper> && bSigned)
			*this = -Remainder;
		else
			*this = Remainder;

		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	template <typename tf_CDummy>
	constexpr inline_small void TCInt<t_CUpper, t_CLower>::fp_SignExtendUpper(TCEnableIf<NTraits::cIsSigned<tf_CDummy> && NTraits::cIsFundamental<tf_CDummy>, tf_CDummy> *_pDummy)
	{
		m_Upper = (m_Upper >> (mc_UpperBits - 1)) >> 1;
	}

	template <typename t_CUpper, typename t_CLower>
	template <typename tf_CDummy>
	constexpr inline_small void TCInt<t_CUpper, t_CLower>::fp_SignExtendUpper(TCEnableIf<!NTraits::cIsSigned<tf_CDummy>, tf_CDummy> *_pDummy)
	{
		m_Upper = mc_UpperZero;
	}

	template <typename t_CUpper, typename t_CLower>
	template <typename tf_CDummy>
	constexpr inline_small void TCInt<t_CUpper, t_CLower>::fp_SignExtendUpper(TCEnableIf<NTraits::cIsSigned<tf_CDummy> && !NTraits::cIsFundamental<tf_CDummy>, tf_CDummy> *_pDummy)
	{
		m_Upper = m_Upper >> (mc_UpperBits);
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator >>= (uaint _Value) -> TCInt &
	{
		aint Value = _Value;
		t_CUpper Upper0 = m_Upper;
		if (Value < aint(mc_LowerBits))
			m_Lower >>= Value;
		else
			m_Lower = mc_LowerZero;

		if (Value < aint(mc_UpperBits))
			m_Upper >>= Value;
		else
			fp_SignExtendUpper<t_CUpper>();

		if (Value > 0)
		{
			if (aint(mc_LowerBits) >= Value)
				m_Lower |= t_CLower(Upper0 << (aint(mc_LowerBits) - Value));
			else
			{
				auto Bits = Value - aint(mc_LowerBits);
				auto Test = (Upper0 >> (Bits - 1)) >> 1;
				m_Lower |= t_CLower(Test);
			}
		}

		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator <<= (uaint _Value) -> TCInt &
	{
		aint Value = _Value;
		t_CLower Lower0 = m_Lower;
		if (Value < aint(mc_LowerBits))
			m_Lower <<= Value;
		else
			m_Lower = mc_LowerZero;

		if (Value < aint(mc_UpperBits))
			m_Upper <<= Value;
		else
			m_Upper = mc_UpperZero;

		if (Value > 0)
		{
			if (Value < aint(mc_LowerBits))
				m_Upper |= t_CUpper(Lower0 >> (aint(mc_LowerBits) - Value));
			else if (Value - aint(mc_LowerBits) < aint(mc_UpperBits))
				m_Upper |= t_CUpper(Lower0) << (Value - aint(mc_LowerBits));
		}

		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator &= (TCInt const &_Value) -> TCInt &
	{
		m_Lower &= _Value.m_Lower;
		m_Upper &= _Value.m_Upper;
		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator ^= (TCInt const &_Value) -> TCInt &
	{
		m_Lower ^= _Value.m_Lower;
		m_Upper ^= _Value.m_Upper;
		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr auto TCInt<t_CUpper, t_CLower>::operator |= (TCInt const &_Value) -> TCInt &
	{
		m_Lower |= _Value.m_Lower;
		m_Upper |= _Value.m_Upper;
		return *this;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr bool TCInt<t_CUpper, t_CLower>::operator == (TCInt const &_Value) const noexcept
	{
		return m_Lower == _Value.m_Lower && m_Upper == _Value.m_Upper;
	}

	template <typename t_CUpper, typename t_CLower>
	constexpr COrdering_Strong TCInt<t_CUpper, t_CLower>::operator <=> (TCInt const &_Value) const noexcept
	{
		if (auto Result = m_Upper <=> _Value.m_Upper; Result != 0)
			return Result;

		return m_Lower <=> _Value.m_Lower;
	}
}

namespace NMib
{
	template <typename tf_CInt>
	constexpr NTraits::TCSmallerType<tf_CInt> fg_GetLower(tf_CInt const &_Integer) noexcept
	{
		return _Integer;
	}

	template <typename tf_CInt>
	constexpr NTraits::TCSmallerType<tf_CInt> fg_GetUpper(tf_CInt const &_Integer) noexcept
	{
		return NTraits::TCSmallerType<tf_CInt>(_Integer >> (sizeof(tf_CInt) * 4));
	}

	template <typename tf_CUpper, typename tf_CLower>
	constexpr typename NNumeric::TCInt<tf_CUpper, tf_CLower>::CLower const &fg_GetLower(NNumeric::TCInt<tf_CUpper, tf_CLower> const &_Integer) noexcept
	{
		return _Integer.m_Lower;
	}

	template <typename tf_CUpper, typename tf_CLower>
	constexpr typename NNumeric::TCInt<tf_CUpper, tf_CLower>::CUpper const &fg_GetUpper(NNumeric::TCInt<tf_CUpper, tf_CLower> const &_Integer) noexcept
	{
		return _Integer.m_Upper;
	}

	template <typename tf_CInteger>
	NTraits::TCUnsigned<tf_CInteger> &fg_Unsigned(tf_CInteger &_Integer)
	{
		return reinterpret_cast<NTraits::TCUnsigned<tf_CInteger> &>(_Integer);
	}

	template <typename tf_CInteger>
	NTraits::TCSigned<tf_CInteger> &fg_Signed(tf_CInteger &_Integer)
	{
		return reinterpret_cast<NTraits::TCSigned<tf_CInteger> &>(_Integer);
	}
}
