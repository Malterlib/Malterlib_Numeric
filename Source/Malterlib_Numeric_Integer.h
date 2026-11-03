// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include <Mib/Bit/Bit>
#include <Mib/Type/Traits>

namespace NMib::NNumeric::NPrivate
{
	struct CDummy
	{
		static CDummy ms_Dummy;
	};
}

namespace NMib::NNumeric
{
	template <typename t_CUpper, typename t_CLower>
	struct TCInt
	{
		using CUpper = t_CUpper;
		using CLower = t_CLower;

#ifdef DMibPLittleEndian
		t_CLower m_Lower{};
		t_CUpper m_Upper{};
#else
		t_CUpper m_Upper{};
		t_CLower m_Lower{};
#endif
		static constexpr aint mc_LowerBits = sizeof(t_CLower) * 8;
		static constexpr aint mc_LowerFirstBit = 0;
		static constexpr aint mc_LowerLastBit = mc_LowerBits - 1;
		static constexpr aint mc_UpperBits = sizeof(t_CUpper) * 8;
		static constexpr aint mc_UpperFirstBit = mc_LowerBits;
		static constexpr aint mc_UpperLastBit = mc_UpperBits + mc_LowerBits - 1;
		static constexpr aint mc_AllBits = mc_LowerBits + mc_UpperBits;
		static constexpr aint mc_HalfBits = mc_AllBits / 2;

		static_assert(mc_UpperBits >= mc_LowerBits, "If non symmetric sizes for constituent integers, the upper integer needs to be the larger one, otherwise sign extension wont work");

		static constexpr aint mc_Size = sizeof(t_CUpper) + sizeof(t_CLower);

		using CInt = TCInt;
		struct CConstants;

		static constexpr bool mc_bIsSigned = NTraits::cIsSigned<t_CUpper>;

		static constexpr t_CUpper mc_UpperZero{0};
		static constexpr t_CUpper mc_UpperOne{1};
		static constexpr t_CLower mc_LowerZero{0};
		static constexpr t_CLower mc_LowerOne{1};

		// Do nothing in default constructor
		constexpr TCInt() noexcept = default;
		constexpr TCInt(TCInt const &_Value) noexcept = default;
		constexpr TCInt(TCInt &&_Value) noexcept = default;

		constexpr TCInt &operator = (TCInt const &_Value) = default;
		constexpr TCInt &operator = (TCInt &&_Value) = default;

		constexpr TCInt(t_CUpper _Upper, t_CLower _Lower)
			: m_Upper(_Upper)
			, m_Lower(_Lower)
		{
		}

		constexpr TCInt(t_CLower _Lower)
			: m_Lower(_Lower)
		{
		}

		template <typename tf_CUpper2, typename tf_CLower2>
		constexpr TCInt<tf_CUpper2, tf_CLower2> f_GetAsTCInt() const
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

		template <typename tf_CInt>
		constexpr explicit operator tf_CInt () const
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

		template <typename tf_CType>
		constexpr TCInt(tf_CType const &_Convert, TCEnableIf<NTraits::cIsFundamental<tf_CType>, NPrivate::CDummy &> _pDummy = NPrivate::CDummy::ms_Dummy)
			: m_Upper(((_Convert >> (fg_Min((umint)mc_LowerBits, sizeof(tf_CType) * 8) - 1)) >> 1))
			, m_Lower((_Convert & fg_BitRange<tf_CType>(0, fg_Min((umint)mc_LowerBits - 1, sizeof(tf_CType) * 8 - 1))))
		{
		}

		template <typename tf_CUpper2, typename tf_CLower2>
		constexpr TCInt(TCInt<tf_CUpper2, tf_CLower2> const &_Other)
		{
			*this = _Other.template f_GetAsTCInt<t_CUpper, t_CLower>();
		}

		template <typename tf_CType>
		constexpr TCInt &operator = (tf_CType const &_Convert)
		{
			constexpr tf_CType c_LowerMask = fg_BitRange<tf_CType>(0, fg_Min((umint)mc_LowerBits - 1, sizeof(tf_CType) * 8 - 1));
			m_Upper = t_CUpper(((_Convert >> (fg_Min((umint)mc_LowerBits, sizeof(tf_CType) * 8) - 1)) >> 1));
			m_Lower = t_CLower((_Convert & c_LowerMask));
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Unary prefix operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr TCInt operator - () const
		{
			return CConstants::mc_Zero - (*this);
		}

		constexpr TCInt operator + () const
		{
			return *this;
		}

		constexpr TCInt operator ~ () const
		{
			TCInt Ret;
			Ret.m_Upper = ~m_Upper;
			Ret.m_Lower = ~m_Lower;
			return Ret;
		}

		constexpr explicit operator bool () const
		{
			return m_Upper != mc_UpperZero || m_Lower != mc_LowerZero;
		}

		constexpr TCInt &operator ++ ()
		{
			*this = *this + CConstants::mc_One;
			return *this;
		}

		constexpr TCInt &operator -- ()
		{
			*this = *this - CConstants::mc_One;
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Postfix operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr TCInt operator ++ (int)
		{
			TCInt Ret = *this;
			++(*this);
			return Ret;
		}

		constexpr TCInt operator -- (int)
		{
			TCInt Ret = *this;
			--(*this);
			return Ret;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Binary operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr TCInt operator + (TCInt const &_Value) const
		{
			TCInt Ret = *this;
			Ret += _Value;
			return Ret;
		}

		constexpr TCInt operator - (TCInt const &_Value) const
		{
			TCInt Ret = *this;
			Ret -= _Value;
			return Ret;
		}

		constexpr TCInt operator * (TCInt const &_Value) const
		{
			TCInt Ret = *this;
			Ret *= _Value;
			return Ret;
		}

		constexpr TCInt operator / (TCInt const &_Value) const
		{
			TCInt Ret = *this;
			Ret /= _Value;
			return Ret;
		}

		constexpr TCInt operator >> (uaint _Value) const
		{
			TCInt Ret = *this;
			Ret >>= _Value;
			return Ret;
		}

		constexpr TCInt operator << (uaint _Value) const
		{
			TCInt Ret = *this;
			Ret <<= _Value;
			return Ret;
		}

		constexpr TCInt operator % (TCInt const &_Value) const
		{
			TCInt Ret = *this;
			Ret %= _Value;
			return Ret;
		}

		constexpr TCInt operator & (TCInt const &_Value) const
		{
			TCInt Ret = *this;
			Ret &= _Value;
			return Ret;
		}

		constexpr TCInt operator | (TCInt const &_Value) const
		{
			TCInt Ret = *this;
			Ret |= _Value;
			return Ret;
		}

		constexpr TCInt operator ^ (TCInt const &_Value) const
		{
			TCInt Ret = *this;
			Ret ^= _Value;
			return Ret;
		}

		constexpr bool operator && (TCInt const &_Value) const
		{
			return (m_Upper != mc_UpperZero || m_Lower != mc_LowerZero) && (_Value.m_Upper != mc_UpperZero || _Value.m_Lower != mc_LowerZero);
		}

		constexpr bool operator || (TCInt const &_Value) const
		{
			return (m_Upper != mc_UpperZero || m_Lower != mc_LowerZero) || (_Value.m_Upper != mc_UpperZero || _Value.m_Lower != mc_LowerZero);
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Binary assignment operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr TCInt &operator += (TCInt const &_Value)
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

		constexpr TCInt &operator -= (TCInt const &_Value)
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

		constexpr TCInt &operator *= (TCInt const &_Value)
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

		static constexpr bool fs_IsBitSet(uaint _Bit)
		{
			return false;
		}

		constexpr TCInt &operator /= (TCInt const &_Value)
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

		constexpr TCInt &operator %= (TCInt const &_Value)
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

		constexpr TCInt &operator >>= (uaint _Value)
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

		constexpr TCInt &operator <<= (uaint _Value)
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

		constexpr TCInt &operator &= (TCInt const &_Value)
		{
			m_Lower &= _Value.m_Lower;
			m_Upper &= _Value.m_Upper;
			return *this;
		}

		constexpr TCInt &operator ^= (TCInt const &_Value)
		{
			m_Lower ^= _Value.m_Lower;
			m_Upper ^= _Value.m_Upper;
			return *this;
		}

		constexpr TCInt &operator |= (TCInt const &_Value)
		{
			m_Lower |= _Value.m_Lower;
			m_Upper |= _Value.m_Upper;
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Binary comparative operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr bool operator == (TCInt const &_Value) const noexcept
		{
			return m_Lower == _Value.m_Lower && m_Upper == _Value.m_Upper;
		}

		constexpr COrdering_Strong operator <=> (TCInt const &_Value) const noexcept
		{
			if (auto Result = m_Upper <=> _Value.m_Upper; Result != 0)
				return Result;

			return m_Lower <=> _Value.m_Lower;
		}

	private:
		template <typename tf_CDummy>
		constexpr inline_small void fp_SignExtendUpper(TCEnableIf<NTraits::cIsSigned<tf_CDummy> && NTraits::cIsFundamental<tf_CDummy>, tf_CDummy> *_pDummy = nullptr)
		{
			m_Upper = (m_Upper >> (mc_UpperBits - 1)) >> 1;
		}

		template <typename tf_CDummy>
		constexpr inline_small void fp_SignExtendUpper(TCEnableIf<!NTraits::cIsSigned<tf_CDummy>, tf_CDummy> *_pDummy = nullptr)
		{
			m_Upper = mc_UpperZero;
		}

		template <typename tf_CDummy>
		constexpr inline_small void fp_SignExtendUpper(TCEnableIf<NTraits::cIsSigned<tf_CDummy> && !NTraits::cIsFundamental<tf_CDummy>, tf_CDummy> *_pDummy = nullptr)
		{
			m_Upper = m_Upper >> (mc_UpperBits);
		}
	};

	template <typename t_CUpper, typename t_CLower>
	struct TCInt<t_CUpper, t_CLower>::CConstants
	{
		static constexpr TCInt<t_CUpper, t_CLower> mc_Zero{0};
		static constexpr TCInt<t_CUpper, t_CLower> mc_One{1};
	};
}

namespace NMib::NTraits::NPrivate
{
	template <typename t_CUpper, typename t_CLower>
	struct TCIsSigned<NMib::NNumeric::TCInt<t_CUpper, t_CLower>>
	{
		static constexpr bool mc_bValue = NMib::NTraits::cIsSigned<t_CUpper>;
	};

	template <typename t_CUpper, typename t_CLower>
	struct TCUnsigned<NMib::NNumeric::TCInt<t_CUpper, t_CLower>>
	{
		using CType = NMib::NNumeric::TCInt<NMib::NTraits::TCUnsigned<t_CUpper>, t_CLower>;
	};

	template <typename t_CUpper, typename t_CLower>
	struct TCSigned<NMib::NNumeric::TCInt<t_CUpper, t_CLower>>
	{
		using CType = NMib::NNumeric::TCInt<NMib::NTraits::TCSigned<t_CUpper>, t_CLower>;
	};

	template <typename t_CUpper, typename t_CLower>
	struct TCIsInteger<NMib::NNumeric::TCInt<t_CUpper, t_CLower>>
	{
		static constexpr bool mc_bValue = true;
	};
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

#ifndef DMibPCanDo_int16
using int16 = NMib::NNumeric::TCInt<int8, uint8>;
#endif

#ifndef DMibPCanDo_uint16
using uint16 = NMib::NNumeric::TCInt<uint8, uint8>;
#endif

#ifndef DMibPCanDo_int32
using int32 = NMib::NNumeric::TCInt<int16, uint16>;
#endif

#ifndef DMibPCanDo_uint32
using uint32 = NMib::NNumeric::TCInt<uint16, uint16>;
#endif

#ifndef DMibPCanDo_int64
using int64 = NMib::NNumeric::TCInt<int32, uint32>;
#endif

#ifndef DMibPCanDo_uint64
using uint64 = NMib::NNumeric::TCInt<uint32, uint32>;
#endif

#ifndef DMibPCanDo_int80
using int80 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<int16, uint16>, NMib::NNumeric::TCInt<uint16, uint16>>, uint16>;
#endif

#ifndef DMibPCanDo_uint80
using uint80 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<uint16, uint16>, NMib::NNumeric::TCInt<uint16, uint16>>, uint16>;
#endif

#ifndef DMibPCanDo_int96
using int96 = NMib::NNumeric::TCInt<NMib::TCConditional<alignof(int64) <= 4, int64, NMib::NNumeric::TCInt<int32, uint32>>, uint32>;
#endif

#ifndef DMibPCanDo_uint96
using uint96 = NMib::NNumeric::TCInt<NMib::TCConditional<alignof(uint64) <= 4, uint64, NMib::NNumeric::TCInt<uint32, uint32>>, uint32>;
#endif

#ifndef DMibPCanDo_int128
using int128 = NMib::NNumeric::TCInt<int64, uint64>;
#endif

#ifndef DMibPCanDo_uint128
using uint128 = NMib::NNumeric::TCInt<uint64, uint64>;
#endif

#ifndef DMibPCanDo_int160
using int160 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<int32, uint32>, NMib::NNumeric::TCInt<uint32, uint32>>, uint32>;
#endif

#ifndef DMibPCanDo_uint160
using uint160 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<uint32, uint32>, NMib::NNumeric::TCInt<uint32, uint32>>, uint32>;
#endif

#ifndef DMibPCanDo_int192
using int192 = NMib::NNumeric::TCInt<NMib::TCConditional<alignof(int128) <= 8, int128, NMib::NNumeric::TCInt<int64, uint64>>, uint64>;
#endif

#ifndef DMibPCanDo_uint192
using uint192 = NMib::NNumeric::TCInt<NMib::TCConditional<alignof(uint128) <= 8, uint128, NMib::NNumeric::TCInt<uint64, uint64>>, uint64>;
#endif

#ifndef DMibPCanDo_int256
using int256 = NMib::NNumeric::TCInt<int128, uint128>;
#endif

#ifndef DMibPCanDo_uint256
using uint256 = NMib::NNumeric::TCInt<uint128, uint128>;
#endif

#ifndef DMibPCanDo_int320
using int320 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<int64, uint64>, NMib::NNumeric::TCInt<uint64, uint64>>, uint64>;
#endif

#ifndef DMibPCanDo_uint320
using uint320 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<uint64, uint64>, NMib::NNumeric::TCInt<uint64, uint64>>, uint64>;
#endif

#ifndef DMibPCanDo_int384
using int384 = NMib::NNumeric::TCInt<int256, uint128>;
#endif

#ifndef DMibPCanDo_uint384
using uint384 = NMib::NNumeric::TCInt<uint256, uint128>;
#endif

#ifndef DMibPCanDo_int512
using int512 = NMib::NNumeric::TCInt<int256, uint256>;
#endif

#ifndef DMibPCanDo_uint512
using uint512 = NMib::NNumeric::TCInt<uint256, uint256>;
#endif

#ifndef DMibPCanDo_int1024
using int1024 = NMib::NNumeric::TCInt<int512, uint512>;
#endif

#ifndef DMibPCanDo_uint1024
using uint1024 = NMib::NNumeric::TCInt<uint512, uint512>;
#endif

#ifndef DMibPCanDo_int2048
using int2048 = NMib::NNumeric::TCInt<int1024, uint1024>;
#endif

#ifndef DMibPCanDo_uint2048
using uint2048 = NMib::NNumeric::TCInt<uint1024, uint1024>;
#endif

#ifndef DMibPCanDo_int4096
using int4096 = NMib::NNumeric::TCInt<int2048, uint2048>;
#endif

#ifndef DMibPCanDo_uint4096
using uint4096 = NMib::NNumeric::TCInt<uint2048, uint2048>;
#endif

#ifndef DMibPCanDo_int8192
using int8192 = NMib::NNumeric::TCInt<int4096, uint4096>;
#endif

#ifndef DMibPCanDo_uint8192
using uint8192 = NMib::NNumeric::TCInt<uint4096, uint4096>;
#endif

#ifndef DMibPCanDo_int16384
using int16384 = NMib::NNumeric::TCInt<int8192, uint8192>;
#endif

#ifndef DMibPCanDo_uint16384
using uint16384 = NMib::NNumeric::TCInt<uint8192, uint8192>;
#endif

#if !(defined(DMibPCanDo_uint8) && defined(DMibPCanDo_uint16))
DMibTraitsImplementSizePair(uint8, uint16);
#endif
#if !(defined(DMibPCanDo_uint16) && defined(DMibPCanDo_uint32))
DMibTraitsImplementSizePair(uint16, uint32);
#endif
#if !(defined(DMibPCanDo_uint32) && defined(DMibPCanDo_uint64))
DMibTraitsImplementSizePair(uint32, uint64);
#endif
#if !(defined(DMibPCanDo_uint64) && defined(DMibPCanDo_uint128))
DMibTraitsImplementSizePair(uint64, uint128);
#endif
#if !(defined(DMibPCanDo_uint80) && defined(DMibPCanDo_uint160))
DMibTraitsImplementSizePair(uint80, uint160);
#endif
#if !(defined(DMibPCanDo_uint96) && defined(DMibPCanDo_uint192))
DMibTraitsImplementSizePair(uint96, uint192);
#endif
#if !(defined(DMibPCanDo_uint160) && defined(DMibPCanDo_uint320))
DMibTraitsImplementSizePair(uint160, uint320);
#endif
#if !(defined(DMibPCanDo_uint192) && defined(DMibPCanDo_uint384))
DMibTraitsImplementSizePair(uint192, uint384);
#endif
#if !(defined(DMibPCanDo_uint128) && defined(DMibPCanDo_uint256))
DMibTraitsImplementSizePair(uint128, uint256);
#endif
#if !(defined(DMibPCanDo_uint256) && defined(DMibPCanDo_uint512))
DMibTraitsImplementSizePair(uint256, uint512);
#endif
#if !(defined(DMibPCanDo_uint512) && defined(DMibPCanDo_uint1024))
DMibTraitsImplementSizePair(uint512, uint1024);
#endif
#if !(defined(DMibPCanDo_uint1024) && defined(DMibPCanDo_uint2048))
DMibTraitsImplementSizePair(uint1024, uint2048);
#endif
#if !(defined(DMibPCanDo_uint2048) && defined(DMibPCanDo_uint4096))
DMibTraitsImplementSizePair(uint2048, uint4096);
#endif
#if !(defined(DMibPCanDo_uint4096) && defined(DMibPCanDo_uint8192))
DMibTraitsImplementSizePair(uint4096, uint8192);
#endif
#if !(defined(DMibPCanDo_uint8192) && defined(DMibPCanDo_uint16384))
DMibTraitsImplementSizePair(uint8192, uint16384);
#endif

#if !(defined(DMibPCanDo_int8) && defined(DMibPCanDo_int16))
DMibTraitsImplementSizePair(int8, int16);
#endif
#if !(defined(DMibPCanDo_int16) && defined(DMibPCanDo_int32))
DMibTraitsImplementSizePair(int16, int32);
#endif
#if !(defined(DMibPCanDo_int32) && defined(DMibPCanDo_int64))
DMibTraitsImplementSizePair(int32, int64);
#endif
#if !(defined(DMibPCanDo_int64) && defined(DMibPCanDo_int128))
DMibTraitsImplementSizePair(int64, int128);
#endif
#if !(defined(DMibPCanDo_int80) && defined(DMibPCanDo_int160))
DMibTraitsImplementSizePair(int80, int160);
#endif
#if !(defined(DMibPCanDo_int96) && defined(DMibPCanDo_int192))
DMibTraitsImplementSizePair(int96, int192);
#endif
#if !(defined(DMibPCanDo_int128) && defined(DMibPCanDo_int256))
DMibTraitsImplementSizePair(int128, int256);
#endif
#if !(defined(DMibPCanDo_int160) && defined(DMibPCanDo_int320))
DMibTraitsImplementSizePair(int160, int320);
#endif
#if !(defined(DMibPCanDo_int192) && defined(DMibPCanDo_int384))
DMibTraitsImplementSizePair(int192, int384);
#endif
#if !(defined(DMibPCanDo_int256) && defined(DMibPCanDo_int512))
DMibTraitsImplementSizePair(int256, int512);
#endif
#if !(defined(DMibPCanDo_int512) && defined(DMibPCanDo_int1024))
DMibTraitsImplementSizePair(int512, int1024);
#endif
#if !(defined(DMibPCanDo_int1024) && defined(DMibPCanDo_int2048))
DMibTraitsImplementSizePair(int1024, int2048);
#endif
#if !(defined(DMibPCanDo_int2048) && defined(DMibPCanDo_int4096))
DMibTraitsImplementSizePair(int2048, int4096);
#endif
#if !(defined(DMibPCanDo_int4096) && defined(DMibPCanDo_int8192))
DMibTraitsImplementSizePair(int4096, int8192);
#endif
#if !(defined(DMibPCanDo_int8192) && defined(DMibPCanDo_int16384))
DMibTraitsImplementSizePair(int8192, int16384);
#endif

#if !defined(DMibPCanDo_int8)
DMibTraitsImplementIntegerFromSize(int8);
#endif
#if !defined(DMibPCanDo_int16)
DMibTraitsImplementIntegerFromSize(int16);
#endif
#if !defined(DMibPCanDo_int32)
DMibTraitsImplementIntegerFromSize(int32);
#endif
#if !defined(DMibPCanDo_int64)
DMibTraitsImplementIntegerFromSize(int64);
#endif
#if !defined(DMibPCanDo_int80)
DMibTraitsImplementIntegerFromSize(int80);
#endif
#if !defined(DMibPCanDo_int96)
DMibTraitsImplementIntegerFromSize(int96);
#endif
#if !defined(DMibPCanDo_int128)
DMibTraitsImplementIntegerFromSize(int128);
#endif
#if !defined(DMibPCanDo_int160)
DMibTraitsImplementIntegerFromSize(int160);
#endif
#if !defined(DMibPCanDo_int192)
DMibTraitsImplementIntegerFromSize(int192);
#endif
#if !defined(DMibPCanDo_int256)
DMibTraitsImplementIntegerFromSize(int256);
#endif
#if !defined(DMibPCanDo_int320)
DMibTraitsImplementIntegerFromSize(int320);
#endif
#if !defined(DMibPCanDo_int384)
DMibTraitsImplementIntegerFromSize(int384);
#endif
#if !defined(DMibPCanDo_int512)
DMibTraitsImplementIntegerFromSize(int512);
#endif
#if !defined(DMibPCanDo_int1024)
DMibTraitsImplementIntegerFromSize(int1024);
#endif
#if !defined(DMibPCanDo_int2048)
DMibTraitsImplementIntegerFromSize(int2048);
#endif
#if !defined(DMibPCanDo_int4096)
DMibTraitsImplementIntegerFromSize(int4096);
#endif
#if !defined(DMibPCanDo_int8192)
DMibTraitsImplementIntegerFromSize(int8192);
#endif
#if !defined(DMibPCanDo_int16384)
DMibTraitsImplementIntegerFromSize(int16384);
#endif

#ifndef DMibPNoShortCuts
using namespace NMib::NNumeric;
#endif
