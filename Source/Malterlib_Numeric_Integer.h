// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include <Mib/Type/Traits>

namespace NMib
{
	namespace NMath
	{
		namespace NPrivate
		{
			struct CDummy
			{
				static CDummy ms_Dummy;
			};
		}

		DMibPStartPackedStruct;
		template <typename t_CUpper, typename t_CLower>
		class TCInt
		{
		public:
			typedef t_CUpper CUpper;
			typedef t_CLower CLower;
#ifdef DMibPLittleEndian
			t_CLower m_Lower;
			t_CUpper m_Upper;
#else
			t_CUpper m_Upper;
			t_CLower m_Lower;
#endif
			enum
			{
				ELowerBits = sizeof(t_CLower)*8,
				ELowerFirstBit = 0,
				ELowerLastBit = ELowerBits - 1,
				EUpperBits = sizeof(t_CUpper)*8,
				EUpperFirstBit = ELowerBits,
				EUpperLastBit = EUpperBits + ELowerBits - 1
			};
			static_assert(EUpperBits >= ELowerBits, "If non symmetric sizes for constituent integers, the upper integer needs to be the larger one, otherwise sign extension wont work");
		public:
			enum
			{
				ESize = sizeof(t_CUpper) + sizeof(t_CLower)
			};
			typedef TCInt CInt;
			class CAggregate
			{
			public:
				uint8 m_Data[ESize];
				operator TCInt const &() const
				{
					return reinterpret_cast<TCInt const &>(*this);
				};
			};
			static const CAggregate mc_Zero;
			static TCInt const &fs_Zero()
			{
				return mc_Zero;
			}
			static const CAggregate mc_One;
			static TCInt const &fs_One()
			{
				return mc_One;
			}

			static const t_CUpper mc_UpperZero;
			static const t_CUpper mc_UpperOne;
			static const t_CLower mc_LowerZero;
			static const t_CLower mc_LowerOne;

			// Do nothing in default constructor
			TCInt()
			{
			}

			TCInt(t_CUpper _Upper, t_CLower _Lower)
			{
				m_Upper = _Upper;
				m_Lower = _Lower;
			}

			TCInt(t_CLower _Lower)
			{
				m_Upper = 0;
				m_Lower = _Lower;
			}

			template <typename t_CUpper2, typename t_CLower2>
			TCInt<t_CUpper2, t_CLower2> f_GetAsTCInt() const 
			{
				if (sizeof(t_CUpper2) + sizeof(t_CLower2) <= sizeof(t_CLower))
				{
					// Less than lower
					return m_Lower;
				}
				else
				{
					typedef TCInt<t_CUpper2, t_CLower2> CType;
					CType Ret;
					static const TCInt And1 = DMibBitRangeTyped(uaint(0), uaint(fg_Min((mint)ELowerBits - 1, sizeof(TCInt)*8 - 1)), TCInt);
					Ret.m_Upper = t_CUpper2((((*this) >> uaint(fg_Min((mint)ELowerBits, sizeof(CType)*8) - 1)) >> uaint(1)));
					Ret.m_Lower = t_CLower2(((*this) & And1));
					return Ret;
				}
			}

			template <typename t_CInt>
			explicit operator t_CInt () const
			{
				static_assert(NTraits::TCIsInteger<t_CInt>::mc_Value, "Must be an integer type");
				if (sizeof(t_CInt) <= sizeof(t_CLower))
				{
					// Less than lower
					return t_CInt(m_Lower);
				}
				else
				{
					t_CInt Ret;
					Ret = t_CInt((m_Upper << (fg_Min((mint)NMath::TCInt<t_CUpper, t_CLower>::ELowerBits, sizeof(t_CInt)*8) - 1)) << 1);
					Ret = Ret | t_CInt(m_Lower);
					return Ret;
				}
			}

			template <typename t_CType>
			TCInt(t_CType const &_Convert,
				  typename TCEnableIf<NTraits::TCIsFundamental<t_CType>::mc_Value, NPrivate::CDummy &>::CType _pDummy = NPrivate::CDummy::ms_Dummy
				)
			{
				static const t_CType And1 = DMibBitRangeTyped(0, fg_Min((mint)ELowerBits - 1, sizeof(t_CType)*8 - 1), t_CType);
				m_Upper = ((_Convert >> (fg_Min((mint)ELowerBits, sizeof(t_CType)*8) - 1)) >> 1);
				m_Lower = (_Convert & And1);
			}
			
			template <typename t_CUpper2, typename t_CLower2>
			TCInt(TCInt<t_CUpper2, t_CLower2> const &_Other)
			{
				*this = _Other.template f_GetAsTCInt<t_CUpper, t_CLower>();
			}

			template <typename t_CType>
			TCInt &operator = (t_CType const &_Convert)
			{
				static const t_CType And1 = DMibBitRangeTyped(0, fg_Min((mint)ELowerBits - 1, sizeof(t_CType)*8 - 1), t_CType);
				m_Upper = t_CUpper(((_Convert >> (fg_Min((mint)ELowerBits, sizeof(t_CType)*8) - 1)) >> 1));
				m_Lower = t_CLower((_Convert & And1));
				return *this;
			}

			TCInt(const TCInt &_Value)
			{
				m_Upper = _Value.m_Upper;
				m_Lower = _Value.m_Lower;
			}

			TCInt &operator = (const TCInt &_Value)
			{
				m_Upper = _Value.m_Upper;
				m_Lower = _Value.m_Lower;
				return *this;
			}

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Unary prefix operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCInt operator - () const
			{
				return fs_Zero() - (*this);
			}

			TCInt operator ~ () const
			{
				TCInt Ret;
				Ret.m_Upper = ~m_Upper;
				Ret.m_Lower = ~m_Lower;
				return Ret;
			}

			explicit operator bool() const
			{
				return m_Upper != mc_UpperZero || m_Lower != mc_LowerZero;
			}

			TCInt & operator ++ ()
			{
				*this = *this + fs_One();
				return *this;
			}

			TCInt & operator -- ()
			{
				*this = *this - fs_One();
				return *this;
			}

			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Postfix operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCInt operator ++ (int)
			{
				TCInt Ret = *this;
				++(*this);
				return Ret;
			}

			TCInt operator -- (int)
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

			TCInt operator + (const TCInt &_Value) const
			{
				TCInt Ret = *this;
				Ret += _Value;
				return Ret;
			}

			TCInt operator - (const TCInt &_Value) const
			{
				TCInt Ret = *this;
				Ret -= _Value;
				return Ret;
			}

			TCInt operator * (const TCInt &_Value) const
			{
				TCInt Ret = *this;
				Ret *= _Value;
				return Ret;
			}
													
			TCInt operator / (const TCInt &_Value) const
			{
				TCInt Ret = *this;
				Ret /= _Value;
				return Ret;
			}

			TCInt operator >> (uaint _Value) const
			{
				TCInt Ret = *this;
				Ret >>= _Value;
				return Ret;
			}

			TCInt operator << (uaint _Value) const
			{
				TCInt Ret = *this;
				Ret <<= _Value;
				return Ret;
			}

			TCInt operator % (const TCInt &_Value) const
			{
				TCInt Ret = *this;
				Ret %= _Value;
				return Ret;
			}

			TCInt operator & (const TCInt &_Value) const
			{
				TCInt Ret = *this;
				Ret &= _Value;
				return Ret;
			}

			TCInt operator | (const TCInt &_Value) const
			{
				TCInt Ret = *this;
				Ret |= _Value;
				return Ret;
			}

			TCInt operator ^ (const TCInt &_Value) const
			{
				TCInt Ret = *this;
				Ret ^= _Value;
				return Ret;
			}

			bint operator && (const TCInt &_Value) const
			{
				return (m_Upper != mc_UpperZero || m_Lower != mc_LowerZero) && (_Value.m_Upper != mc_UpperZero || _Value.m_Lower != mc_LowerZero);
			}

			bint operator || (const TCInt &_Value) const
			{
				return (m_Upper != mc_UpperZero || m_Lower != mc_LowerZero) || (_Value.m_Upper != mc_UpperZero || _Value.m_Lower != mc_LowerZero);
			}

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Binary assignment operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCInt &operator += (const TCInt &_Value)
			{
				t_CLower Lower0 = m_Lower;
				t_CLower Lower1 = _Value.m_Lower;
				m_Lower = Lower0 + Lower1;

				m_Upper += _Value.m_Upper;

				static const t_CLower HalfLower = (t_CLower(1) << (aint)(ELowerLastBit));
				static const t_CLower And1 = ((t_CLower(1) << (aint)(ELowerLastBit)) - t_CLower(1));
				if (Lower0 >= HalfLower)
				{
					if (Lower1 >= HalfLower)
						m_Upper += 1;
					else if (((Lower0 & And1) + (Lower1 & And1)) >= HalfLower)
						m_Upper += 1;
				}
				else if (Lower1 >= HalfLower)
				{
					if (((Lower0 & And1) + (Lower1 & And1)) >= HalfLower)
						m_Upper += 1;
				}

	/*			static const t_CLower And0 = (t_CLower(1) << ELowerLastBit);
				static const t_CLower And1 = ((t_CLower(1) << ELowerLastBit) - t_CLower(1));
				
				if ((((((Lower0 ^ Lower1) & ((Lower0 & And1) + (Lower1 & And1))) | (Lower0 & Lower1)) & And0)) != 0)
				{
					m_Upper += _Value.m_Upper;
					m_Upper += 1;
				}
				else
					m_Upper += _Value.m_Upper;*/
					


//				m_Upper += _Value.m_Upper + ((((((Lower0 ^ Lower1) & ((Lower0 & And1) + (Lower1 & And1))) | (Lower0 & Lower1)) & And0)) >> ELowerLastBit);

//				m_Upper += _Value.m_Upper + ((((((Lower0 ^ Lower1) & ((Lower0 & ((t_CLower(1) << ELowerLastBit) - t_CLower(1))) + (Lower1 & ((t_CLower(1) << ELowerLastBit) - t_CLower(1))))) | (Lower0 & Lower1)) & (t_CLower(1) << ELowerLastBit))) >> ELowerLastBit);

				return *this;
			}

			TCInt &operator -= (const TCInt &_Value)
			{
				t_CLower Lower0 = m_Lower;
				t_CLower Lower1 = _Value.m_Lower;
				m_Lower -= Lower1;
				m_Upper -= _Value.m_Upper;
				if (Lower1 > Lower0)
					m_Upper -= 1;

				return *this;
			}

			TCInt &operator *= (const TCInt &_Value)
			{
				bint bSigned = false;
				TCInt Val0 = *this;
				TCInt Val1 = _Value;
				if (NTraits::TCIsSigned<t_CUpper>::mc_Value && Val0 < fs_Zero())
				{
					Val0 = -Val0;
					if (Val1 < fs_Zero())
						Val1 = -Val1;
					else
						bSigned = true;
				}
				else if (NTraits::TCIsSigned<t_CUpper>::mc_Value && Val1 < fs_Zero())
				{
					Val1 = -Val1;
					bSigned = true;
				}

				TCInt Result = fs_Zero();

//				// Multiply half the bits first
				t_CLower And0 = DMibBitRangeOne(0, (ELowerBits / 2) - 1, mc_LowerOne);
				t_CLower Lower0 = Val0.m_Lower & And0;
				t_CLower Lower1 = Val1.m_Lower & And0;

				Result += TCInt(mc_UpperZero, (Lower0) * (Lower1));

				t_CLower Lower2 = Val1.m_Lower >> (ELowerBits / 2);
				t_CLower Lower3 = Val0.m_Lower >> (ELowerBits / 2);

				// Multily lower with upper bits and add
				Result += TCInt(mc_UpperZero, Lower0 * Lower2) << uaint(ELowerBits / 2);
				Result += TCInt(mc_UpperZero, Lower1 * Lower3) << uaint(ELowerBits / 2);

//				// Multily upper bits and add
				Result += TCInt(mc_UpperZero, Lower2 * Lower3) << uaint(ELowerBits);

				// Multiply Upper by lower and let it owerflow
				Result += TCInt(Val0.m_Upper * Val1.m_Lower, mc_LowerZero);
				Result += TCInt(Val1.m_Upper * Val0.m_Lower, mc_LowerZero);
				// Can never contribute to number (always overflows)
//				Result += TCInt(Val0.m_Upper * Val1.m_Upper, 0) << EUpperBits;

				if (NTraits::TCIsSigned<t_CUpper>::mc_Value && bSigned)
					*this = -Result;
				else
					*this = Result;

				return *this;
			}

			static bint fp_IsBitSet(uaint _Bit)
			{
				return false;
			}

			TCInt &operator /= (const TCInt &_Value)
			{
				bint bSigned = false;
				TCInt Val0 = *this;
				TCInt Val1 = _Value;
				if (NTraits::TCIsSigned<t_CUpper>::mc_Value && Val0 < fs_Zero())
				{
					Val0 = -Val0;
					if (Val1 < fs_Zero())
						Val1 = -Val1;
					else
						bSigned = true;
				}
				else if (NTraits::TCIsSigned<t_CUpper>::mc_Value && Val1 < fs_Zero())
				{
					Val1 = -Val1;
					bSigned = true;
				}

				// Do dumb divide
				TCInt Result = Val0;
				TCInt Remainder = fs_Zero();
				t_CUpper UppestBit = mc_UpperOne << (EUpperBits - 1);
				int i = 0;
				for (; i < (ELowerBits + EUpperBits); ++i)
				{
					if ((Result.m_Upper & UppestBit) != mc_UpperZero)
						break;
					Result <<= 1;
				}

				for (; i < (ELowerBits + EUpperBits); ++i)
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

				if (NTraits::TCIsSigned<t_CUpper>::mc_Value && bSigned)
					*this = -Result;
				else
					*this = Result;

				return *this;
			}
            
			TCInt &operator %= (const TCInt &_Value)
			{
				bint bSigned = false;
				TCInt Val0 = *this;
				TCInt Val1 = _Value;
				if (NTraits::TCIsSigned<t_CUpper>::mc_Value && Val0 < fs_Zero())
				{
					Val0 = -Val0;
					bSigned = true;
				}
				
				if (NTraits::TCIsSigned<t_CUpper>::mc_Value && Val1 < fs_Zero())
				{
					Val1 = -Val1;
				}

				// Do dumb divide
				TCInt Result = Val0;
				TCInt Remainder = fs_Zero();
				t_CUpper UppestBit = mc_UpperOne << (EUpperBits - 1);
				int i = 0;
				for (; i < (ELowerBits + EUpperBits); ++i)
				{
					if ((Result.m_Upper & UppestBit) != mc_UpperZero)
						break;
					Result <<= 1;
				}

				for (; i < (ELowerBits + EUpperBits); ++i)
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

				if (NTraits::TCIsSigned<t_CUpper>::mc_Value && bSigned)
					*this = -Remainder;
				else
					*this = Remainder;

				return *this;
			}

			template <typename t_CDummy>
			inline_small void fp_SignExtendUpper(typename TCEnableIf<NTraits::TCIsSigned<t_CDummy>::mc_Value && NTraits::TCIsFundamental<t_CDummy>::mc_Value, t_CDummy>::CType *_pDummy = nullptr)
			{
				m_Upper = (m_Upper >> (EUpperBits - 1)) >> 1;
			}

			template <typename t_CDummy>
			inline_small void fp_SignExtendUpper(typename TCEnableIf<!NTraits::TCIsSigned<t_CDummy>::mc_Value, t_CDummy>::CType *_pDummy = nullptr)
			{
				m_Upper = mc_UpperZero;
			}

			template <typename t_CDummy>
			inline_small void fp_SignExtendUpper(typename TCEnableIf<NTraits::TCIsSigned<t_CDummy>::mc_Value && !NTraits::TCIsFundamental<t_CDummy>::mc_Value, t_CDummy>::CType *_pDummy = nullptr)
			{
				m_Upper = m_Upper >> (EUpperBits);
			}

			TCInt &operator >>= (uaint _Value)
			{
				aint Value = _Value;
				t_CUpper Upper0 = m_Upper;
				if (Value < aint(ELowerBits))
					m_Lower >>= Value;
				else
					m_Lower = mc_LowerZero;

				if (Value < aint(EUpperBits))
					m_Upper >>= Value;
				else
					fp_SignExtendUpper<t_CUpper>();

				if (Value > 0)
				{
					if (aint(ELowerBits) >= Value)
						m_Lower |= t_CLower(Upper0 << (aint(ELowerBits) - Value));
					else
						m_Lower |= t_CLower(Upper0 >> (Value - aint(ELowerBits)));
				}

				return *this;
			}

			TCInt &operator <<= (uaint _Value)
			{
				aint Value = _Value;
				t_CLower Lower0 = m_Lower;
				if (Value < aint(ELowerBits))
					m_Lower <<= Value;
				else
					m_Lower = mc_LowerZero;

				if (Value < aint(EUpperBits))
					m_Upper <<= Value;
				else
					m_Upper = mc_LowerZero;

				if (Value > 0)
				{
					if (Value < aint(ELowerBits))
						m_Upper |= t_CUpper(Lower0 >> (aint(ELowerBits) - Value));
					else
						m_Upper |= t_CUpper(Lower0) << (Value - aint(ELowerBits));
				}
				
				return *this;
			}

			TCInt &operator &= (const TCInt &_Value)
			{
				m_Lower &= _Value.m_Lower;
				m_Upper &= _Value.m_Upper;
				return *this;
			}

			TCInt &operator ^= (const TCInt &_Value)
			{
				m_Lower ^= _Value.m_Lower;
				m_Upper ^= _Value.m_Upper;
				return *this;
			}

			TCInt &operator |= (const TCInt &_Value)
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

			bint operator == (const TCInt &_Value) const
			{
				return m_Lower == _Value.m_Lower && m_Upper == _Value.m_Upper;
			}

			bint operator < (const TCInt &_Value) const
			{
				return m_Upper < _Value.m_Upper || (m_Upper == _Value.m_Upper && m_Lower < _Value.m_Lower);
			}
		} DMibPPackedStruct;

		DMibPEndPackedStruct;

		template <typename t_CUpper, typename t_CLower>
		const typename TCInt<t_CUpper, t_CLower>::CAggregate TCInt<t_CUpper, t_CLower>::mc_Zero = {{0}};

		template <typename t_CUpper, typename t_CLower>
		const typename TCInt<t_CUpper, t_CLower>::CAggregate TCInt<t_CUpper, t_CLower>::mc_One = {{1, 0}};

		template <typename t_CUpper, typename t_CLower>
		const t_CUpper TCInt<t_CUpper, t_CLower>::mc_UpperZero = 0;

		template <typename t_CUpper, typename t_CLower>
		const t_CUpper TCInt<t_CUpper, t_CLower>::mc_UpperOne = 1;

		template <typename t_CUpper, typename t_CLower>
		const t_CLower TCInt<t_CUpper, t_CLower>::mc_LowerZero = 0;

		template <typename t_CUpper, typename t_CLower>
		const t_CLower TCInt<t_CUpper, t_CLower>::mc_LowerOne = 1;


	}

	namespace NTraits
	{
		namespace NImplementation
		{
			template <typename t_CUpper, typename t_CLower>
			class TCIsSigned<NMib::NMath::TCInt<t_CUpper, t_CLower> >
			{
			public:
				enum
				{
					EValue = NMib::NTraits::TCIsSigned<t_CUpper>::mc_Value
				};
			};

			template <typename t_CUpper, typename t_CLower>
			class TCUnsigned<NMib::NMath::TCInt<t_CUpper, t_CLower> >
			{
			public:
				typedef NMib::NMath::TCInt<typename NMib::NTraits::TCUnsigned<t_CUpper>::CType, t_CLower> CType;
			};

			template <typename t_CUpper, typename t_CLower>
			class TCSigned<NMib::NMath::TCInt<t_CUpper, t_CLower> >
			{
			public:
				typedef NMib::NMath::TCInt<typename NMib::NTraits::TCSigned<t_CUpper>::CType, t_CLower> CType;
			};

			template <typename t_CUpper, typename t_CLower>
			class TCIsInteger<NMib::NMath::TCInt<t_CUpper, t_CLower>>
			{
			public:
				enum
				{
					EValue = true
				};
			};
		}
	}

	
	/*
	template <typename t_CType0, typename t_CUpper, typename t_CLower>
	class TCConvert<t_CType0, NMath::TCInt<t_CUpper, t_CLower> >
	{
	public:
		static inline_small t_CType0 fs_Convert(NMath::TCInt<t_CUpper, t_CLower> const &_From)
		{
			t_CType0 Ret;
			Ret = (NMib::fg_Convert<t_CType0>(_From.m_Upper) << (fg_Min((mint)NMath::TCInt<t_CUpper, t_CLower>::ELowerBits, sizeof(t_CType0)*8) - 1)) << 1;
			Ret = Ret | NMib::fg_Convert<t_CType0>(_From.m_Lower);
			return Ret;
		}
	};*/

#if 0
	template <typename t_CInt>
	typename NTraits::TCSmallerType<t_CInt>::CType fg_GetLower(t_CInt const &_Integer)
	{
		return _Integer;
	}

	template <typename t_CInt>
	typename NTraits::TCSmallerType<t_CInt>::CType fg_GetUpper(t_CInt const &_Integer)
	{
		return _Integer >> (sizeof(t_CInt)*4);
	}
#else

	template <typename t_CInt>
	typename NTraits::TCSmallerType<t_CInt>::CType const &fg_GetLower(t_CInt const &_Integer)
	{
#ifdef DMibPLittleEndian
		return ((typename NTraits::TCSmallerType<t_CInt>::CType *)&_Integer)[0];
#else
		return ((typename NTraits::TCSmallerType<t_CInt>::CType *)&_Integer)[1];
#endif
	}

	template <typename t_CInt>
	typename NTraits::TCSmallerType<t_CInt>::CType const &fg_GetUpper(t_CInt const &_Integer)
	{
#ifdef DMibPLittleEndian
		return ((typename NTraits::TCSmallerType<t_CInt>::CType *)&_Integer)[1];
#else
		return ((typename NTraits::TCSmallerType<t_CInt>::CType *)&_Integer)[0];
#endif
	}
#endif

	template <typename t_CUpper, typename t_CLower>
	typename NMath::TCInt<t_CUpper, t_CLower>::CLower const & fg_GetLower(NMath::TCInt<t_CUpper, t_CLower> const &_Integer)
	{
		return _Integer.m_Lower;
	}

	template <typename t_CUpper, typename t_CLower>
	typename NMath::TCInt<t_CUpper, t_CLower>::CUpper const & fg_GetUpper(NMath::TCInt<t_CUpper, t_CLower> const &_Integer)
	{
		return _Integer.m_Upper;
	}
	
	template <typename tf_CInteger>
	typename NTraits::TCUnsigned<tf_CInteger>::CType &fg_Unsigned(tf_CInteger &_Integer)
	{
		return reinterpret_cast<typename NTraits::TCUnsigned<tf_CInteger>::CType &>(_Integer);
	}

	template <typename tf_CInteger>
	typename NTraits::TCUnsigned<tf_CInteger>::CType &fg_Signed(tf_CInteger &_Integer)
	{
		return reinterpret_cast<typename NTraits::TCUnsigned<tf_CInteger>::CType &>(_Integer);
	}
}

#ifndef DMibPCanDo_int16
typedef NMib::NMath::TCInt<int8, uint8> int16;
#endif

#ifndef DMibPCanDo_uint16
typedef NMib::NMath::TCInt<uint8, uint8> uint16;
#endif

#ifndef DMibPCanDo_int32
typedef NMib::NMath::TCInt<int16, uint16> int32;
#endif

#ifndef DMibPCanDo_uint32
typedef NMib::NMath::TCInt<uint16, uint16> uint32;
#endif

#ifndef DMibPCanDo_int64
typedef NMib::NMath::TCInt<int32, uint32> int64;
#endif

#ifndef DMibPCanDo_uint64
typedef NMib::NMath::TCInt<uint32, uint32> uint64;
#endif

#ifndef DMibPCanDo_int80
typedef NMib::NMath::TCInt<int64, uint16> int80;
#endif

#ifndef DMibPCanDo_uint80
typedef NMib::NMath::TCInt<uint64, uint16> uint80;
#endif

#ifndef DMibPCanDo_int128
typedef NMib::NMath::TCInt<int64, uint64> int128;
#endif

#ifndef DMibPCanDo_uint128
typedef NMib::NMath::TCInt<uint64, uint64> uint128;
#endif

#ifndef DMibPCanDo_int160
typedef NMib::NMath::TCInt<int128, uint32> int160;
#endif

#ifndef DMibPCanDo_uint160
typedef NMib::NMath::TCInt<uint128, uint32> uint160;
#endif


#ifndef DMibPCanDo_int256
typedef NMib::NMath::TCInt<int128, uint128> int256;
#endif

#ifndef DMibPCanDo_uint256
typedef NMib::NMath::TCInt<uint128, uint128> uint256;
#endif

#ifndef DMibPCanDo_int512
typedef NMib::NMath::TCInt<int256, uint256> int512;
#endif

#ifndef DMibPCanDo_uint512
typedef NMib::NMath::TCInt<uint256, uint256> uint512;
#endif

#ifndef DMibPCanDo_int1024
typedef NMib::NMath::TCInt<int512, uint512> int1024;
#endif

#ifndef DMibPCanDo_uint1024
typedef NMib::NMath::TCInt<uint512, uint512> uint1024;
#endif

#ifndef DMibPCanDo_int2048
typedef NMib::NMath::TCInt<int1024, uint1024> int2048;
#endif

#ifndef DMibPCanDo_uint2048
typedef NMib::NMath::TCInt<uint1024, uint1024> uint2048;
#endif

#ifndef DMibPCanDo_int4096
typedef NMib::NMath::TCInt<int2048, uint2048> int4096;
#endif

#ifndef DMibPCanDo_uint4096
typedef NMib::NMath::TCInt<uint2048, uint2048> uint4096;
#endif

#ifndef DMibPCanDo_int8192
typedef NMib::NMath::TCInt<int4096, uint4096> int8192;
#endif

#ifndef DMibPCanDo_uint8192
typedef NMib::NMath::TCInt<uint4096, uint4096> uint8192;
#endif

namespace NMib
{
	namespace NTraits
	{

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
#if !(defined(DMibPCanDo_int128) && defined(DMibPCanDo_int256))
	DMibTraitsImplementSizePair(int128, int256);
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
#if !defined(DMibPCanDo_int128)
	DMibTraitsImplementIntegerFromSize(int128);
#endif
#if !defined(DMibPCanDo_int160)
	DMibTraitsImplementIntegerFromSize(int160);
#endif
#if !defined(DMibPCanDo_int256)
	DMibTraitsImplementIntegerFromSize(int256);
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
	}
}

