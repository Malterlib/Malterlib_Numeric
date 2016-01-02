// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

namespace NMib
{
	namespace NMath
	{
		template <int t_nBytes, int t_VariableNumber = 0>
		class TCCombineInt : public TCCombineInt<t_nBytes - sizeof(typename NTraits::TCIntFromSizeSmaller<t_nBytes, true>::CType), t_VariableNumber + 1>
		{
		public:
			typedef TCCombineInt<t_nBytes - sizeof(typename NTraits::TCIntFromSizeSmaller<t_nBytes, true>::CType), t_VariableNumber + 1> CSuper;
			typedef typename NTraits::TCIntFromSizeSmaller<t_nBytes, true>::CType CIntType;
			CIntType m_Int;

			template <int t_Var>
			class CCalculateType
			{
				typedef typename CSuper::template CCalculateType<t_Var>::CCombine CNextCombine;
			public:
				
				typedef typename TCChooseType<t_Var == t_VariableNumber, TCCombineInt, CNextCombine>::CType CCombine;
			};

/*			template <>
			class CCalculateType<t_VariableNumber>
			{
			public:
				typedef TCCombineInt CCombine;
			};*/

			template <int t_Var>
			typename CCalculateType<t_Var>::CCombine::CIntType &f_GetInt()
			{
				return CCalculateType<t_Var>::CCombine::m_Int;
			}

			template <int t_Var>
			typename CCalculateType<t_Var>::CCombine::CIntType const &f_GetInt() const
			{
				return CCalculateType<t_Var>::CCombine::m_Int;
			}
		};

		template <int t_VariableNumber>
		class TCCombineInt<0, t_VariableNumber>
		{
		public:
			template <int t_Var>
			class CCalculateType
			{
				typedef TCCombineInt CCombine;
			};
			enum
			{
				ENumVars = t_VariableNumber
			};
		};


		template <int t_VariableNumber>
		class TCAddition
		{
		public:
		};

		template <int t_nBytes, int t_VariableNumber>
		void fg_DoAddition(TCCombineInt<t_nBytes, t_VariableNumber> &_Left, const TCCombineInt<t_nBytes, t_VariableNumber> &_Right)
		{
			const static int Vars = TCCombineInt<t_nBytes, t_VariableNumber>::ENumVars;

/*				t_CLower Lower0 = m_Lower;
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
			}*/
		}


/*		template <int t_VaribaleNumber, int t_nBytes, int t_VariableNumber2>
		auto fg_GetSubInt(TCCombineInt<t_nBytes, t_VariableNumber2> &_Variable)
		{
			return TCCombineInt<t_nBytes, t_VariableNumber2>();
		}*/

		//NTraits::TCIntFromSizeSmaller

		template <mint t_nBits>
		class TCInt2
		{
		public:

			TCCombineInt<(t_nBits + 7)/8> m_Int;
#if 0

			// Do nothing in default constructor
			TCInt2()
			{
			}

			TCInt2(t_CUpper _Upper, t_CLower _Lower)
			{
				m_Upper = _Upper;
				m_Lower = _Lower;
			}

			TCInt2(t_CLower _Lower)
			{
				m_Upper = 0;
				m_Lower = _Lower;
			}

			template <typename t_CUpper2, typename t_CLower2>
			operator TCInt2<t_CUpper2, t_CLower2> () const 
			{
				if (sizeof(t_CUpper2) + sizeof(t_CLower2) <= sizeof(t_CLower))
				{
					// Less than lower
					return m_Lower;
				}
				else
				{
					typedef TCInt2<t_CUpper2, t_CLower2> CType;
					CType Ret;
					static const TCInt2 And1 = DMibBitRangeTyped(0, fg_Min((mint)ELowerBits - 1, sizeof(TCInt2)*8 - 1), TCInt2);
					Ret.m_Upper = (((*this) >> (fg_Min((mint)ELowerBits, sizeof(CType)*8) - 1)) >> 1);
					Ret.m_Lower = ((*this) & And1);
					return Ret;
				}
			}

			template <typename t_CInt>
			operator t_CInt () const
			{
				static_assert(NTraits::TCIsInteger<t_CInt>::mc_Value, "Must be an integer type");
				if (sizeof(t_CInt) <= sizeof(t_CLower))
				{
					// Less than lower
					return m_Lower;
				}
				else
				{
					t_CInt Ret;
					Ret = (m_Upper << (fg_Min((mint)NMath::TCInt2<t_CUpper, t_CLower>::ELowerBits, sizeof(t_CInt)*8) - 1)) << 1;
					Ret = Ret | t_CInt(m_Lower);
					return Ret;
				}
			}

			template <typename t_CType>
			TCInt2(t_CType const &_Convert, 
				typename TCDisableIf<!NTraits::TCIsFundamental<t_CType>::mc_Value, t_CType>::CType *_pDummy = nullptr
				)
			{
				static const t_CType And1 = DMibBitRangeTyped(0, fg_Min((mint)ELowerBits - 1, sizeof(t_CType)*8 - 1), t_CType);
				m_Upper = ((_Convert >> (fg_Min((mint)ELowerBits, sizeof(t_CType)*8) - 1)) >> 1);
				m_Lower = (_Convert & And1);
			}

			template <typename t_CType>
			TCInt2 &operator = (t_CType const &_Convert)
			{
				static const t_CType And1 = DMibBitRangeTyped(0, fg_Min((mint)ELowerBits - 1, sizeof(t_CType)*8 - 1), t_CType);
				m_Upper = ((_Convert >> (fg_Min((mint)ELowerBits, sizeof(t_CType)*8) - 1)) >> 1);
				m_Lower = (_Convert & And1);
				return *this;
			}

			TCInt2(const TCInt2 &_Value)
			{
				m_Upper = _Value.m_Upper;
				m_Lower = _Value.m_Lower;
			}

			TCInt2 &operator = (const TCInt2 &_Value)
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

			TCInt2 operator - () const
			{
				return fs_Zero() - (*this);
			}

			TCInt2 operator ~ () const
			{
				TCInt2 Ret;
				Ret.m_Upper = ~m_Upper;
				Ret.m_Lower = ~m_Lower;
				return Ret;
			}

			explicit operator bool () const
			{
				return m_Upper != mc_UpperZero || m_Lower != mc_LowerZero;
			}

			TCInt2 & operator ++ ()
			{
				*this = *this + fs_One();
				return *this;
			}

			TCInt2 & operator -- ()
			{
				*this = *this - fs_One();
				return *this;
			}

			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Postfix operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCInt2 operator ++ (int)
			{
				TCInt2 Ret = *this;
				++(*this);
				return Ret;
			}

			TCInt2 operator -- (int)
			{
				TCInt2 Ret = *this;
				--(*this);
				return Ret;
			}

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Binary operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCInt2 operator + (const TCInt2 &_Value) const
			{
				TCInt2 Ret = *this;
				Ret += _Value;
				return Ret;
			}

			TCInt2 operator - (const TCInt2 &_Value) const
			{
				TCInt2 Ret = *this;
				Ret -= _Value;
				return Ret;
			}

			TCInt2 operator * (const TCInt2 &_Value) const
			{
				TCInt2 Ret = *this;
				Ret *= _Value;
				return Ret;
			}
													
			TCInt2 operator / (const TCInt2 &_Value) const
			{
				TCInt2 Ret = *this;
				Ret /= _Value;
				return Ret;
			}

			template <typename t_CShiftType>
			TCInt2 operator >> (uaint _Value) const
			{
				TCInt2 Ret = *this;
				Ret >>= _Value;
				return Ret;
			}

			TCInt2 operator << (uaint _Value) const
			{
				TCInt2 Ret = *this;
				Ret <<= _Value;
				return Ret;
			}

			TCInt2 operator >> (aint _Value) const
			{
				TCInt2 Ret = *this;
				Ret >>= _Value;
				return Ret;
			}

			TCInt2 operator << (aint _Value) const
			{
				TCInt2 Ret = *this;
				Ret <<= _Value;
				return Ret;
			}

			TCInt2 operator % (const TCInt2 &_Value) const
			{
				TCInt2 Ret = *this;
				Ret %= _Value;
				return Ret;
			}

			TCInt2 operator & (const TCInt2 &_Value) const
			{
				TCInt2 Ret = *this;
				Ret &= _Value;
				return Ret;
			}

			TCInt2 operator | (const TCInt2 &_Value) const
			{
				TCInt2 Ret = *this;
				Ret |= _Value;
				return Ret;
			}

			TCInt2 operator ^ (const TCInt2 &_Value) const
			{
				TCInt2 Ret = *this;
				Ret ^= _Value;
				return Ret;
			}

			bint operator && (const TCInt2 &_Value) const
			{
				return (m_Upper != mc_UpperZero || m_Lower != mc_LowerZero) && (_Value.m_Upper != mc_UpperZero || _Value.m_Lower != mc_LowerZero);
			}

			bint operator || (const TCInt2 &_Value) const
			{
				return (m_Upper != mc_UpperZero || m_Lower != mc_LowerZero) || (_Value.m_Upper != mc_UpperZero || _Value.m_Lower != mc_LowerZero);
			}

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Binary assignment operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCInt2 &operator += (const TCInt2 &_Value)
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

			TCInt2 &operator -= (const TCInt2 &_Value)
			{
				t_CLower Lower0 = m_Lower;
				t_CLower Lower1 = _Value.m_Lower;
				m_Lower -= Lower1;
				m_Upper -= _Value.m_Upper;
				if (Lower1 > Lower0)
					m_Upper -= 1;

				return *this;
			}

			TCInt2 &operator *= (const TCInt2 &_Value)
			{
				bint bSigned = false;
				TCInt2 Val0 = *this;
				TCInt2 Val1 = _Value;
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

				TCInt2 Result = fs_Zero();

//				// Multiply half the bits first
				t_CLower And0 = DMibBitRangeOne(0, (ELowerBits / 2) - 1, mc_LowerOne);
				t_CLower Lower0 = Val0.m_Lower & And0;
				t_CLower Lower1 = Val1.m_Lower & And0;

				Result += TCInt2(mc_UpperZero, (Lower0) * (Lower1));

				t_CLower Lower2 = Val1.m_Lower >> (ELowerBits / 2);
				t_CLower Lower3 = Val0.m_Lower >> (ELowerBits / 2);

				// Multily lower with upper bits and add
				Result += TCInt2(mc_UpperZero, Lower0 * Lower2) << (ELowerBits / 2);
				Result += TCInt2(mc_UpperZero, Lower1 * Lower3) << (ELowerBits / 2);

//				// Multily upper bits and add
				Result += TCInt2(mc_UpperZero, Lower2 * Lower3) << (aint)(ELowerBits);

				// Multiply Upper by lower and let it owerflow
				Result += TCInt2(Val0.m_Upper * Val1.m_Lower, mc_LowerZero);
				Result += TCInt2(Val1.m_Upper * Val0.m_Lower, mc_LowerZero);
				// Can never contribute to number (always overflows)
//				Result += TCInt2(Val0.m_Upper * Val1.m_Upper, 0) << EUpperBits;

				if (NTraits::TCIsSigned<t_CUpper>::mc_Value && bSigned)
					*this = -Result;
				else
					*this = Result;

				return *this;
			}

			static bint fp_IsBitSet(uaint _Bit)
			{
			}

			TCInt2 &operator /= (const TCInt2 &_Value)
			{
				bint bSigned = false;
				TCInt2 Val0 = *this;
				TCInt2 Val1 = _Value;
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
				TCInt2 Result = Val0;
				TCInt2 Remainder = fs_Zero();
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
            
			TCInt2 &operator %= (const TCInt2 &_Value)
			{
				bint bSigned = false;
				TCInt2 Val0 = *this;
				TCInt2 Val1 = _Value;
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
				TCInt2 Result = Val0;
				TCInt2 Remainder = fs_Zero();
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

			TCInt2 &operator >>= (uaint _Value)
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
					m_Lower |= t_CLower(Upper0 >> (Value - aint(ELowerBits)));

				return *this;
			}

			TCInt2 &operator <<= (uaint _Value)
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

			TCInt2 &operator &= (const TCInt2 &_Value)
			{
				m_Lower &= _Value.m_Lower;
				m_Upper &= _Value.m_Upper;
				return *this;
			}

			TCInt2 &operator ^= (const TCInt2 &_Value)
			{
				m_Lower ^= _Value.m_Lower;
				m_Upper ^= _Value.m_Upper;
				return *this;
			}

			TCInt2 &operator |= (const TCInt2 &_Value)
			{
				m_Lower |= _Value.m_Lower;
				m_Upper |= _Value.m_Upper;
				return *this;
			}
#endif

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Binary comparative operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/
#if 0
			bint operator == (const TCInt2 &_Value) const
			{
				return m_Lower == _Value.m_Lower && m_Upper == _Value.m_Upper;
			}

			bint operator < (const TCInt2 &_Value) const
			{
				return m_Upper < _Value.m_Upper || (m_Upper == _Value.m_Upper && m_Lower < _Value.m_Lower);
			}
#endif
		};

#if 0
		template <typename t_CUpper, typename t_CLower>
		const typename TCInt2<t_CUpper, t_CLower>::CAggregate TCInt2<t_CUpper, t_CLower>::mc_Zero = {0};

		template <typename t_CUpper, typename t_CLower>
		const typename TCInt2<t_CUpper, t_CLower>::CAggregate TCInt2<t_CUpper, t_CLower>::mc_One = {1, 0};

		template <typename t_CUpper, typename t_CLower>
		const t_CUpper TCInt2<t_CUpper, t_CLower>::mc_UpperZero = 0;

		template <typename t_CUpper, typename t_CLower>
		const t_CUpper TCInt2<t_CUpper, t_CLower>::mc_UpperOne = 1;

		template <typename t_CUpper, typename t_CLower>
		const t_CLower TCInt2<t_CUpper, t_CLower>::mc_LowerZero = 0;

		template <typename t_CUpper, typename t_CLower>
		const t_CLower TCInt2<t_CUpper, t_CLower>::mc_LowerOne = 1;


		template <typename t_CUpper, typename t_CLower>
		class NMib::NTraits::NImplementation::TCIsSigned<NMib::NMath::TCInt2<t_CUpper, t_CLower> >
		{
		public:
			enum
			{
				EValue = NMib::NTraits::TCIsSigned<t_CUpper>::mc_Value
			};
		};

		template <typename t_CUpper, typename t_CLower>
		class NMib::NTraits::NImplementation::TCUnsigned<NMib::NMath::TCInt2<t_CUpper, t_CLower> >
		{
		public:
			typedef NMib::NMath::TCInt2<typename NMib::NTraits::TCUnsigned<t_CUpper>::CType, t_CLower> CType;
		};

		template <typename t_CUpper, typename t_CLower>
		class NMib::NTraits::NImplementation::TCSigned<NMib::NMath::TCInt2<t_CUpper, t_CLower> >
		{
		public:
			typedef NMib::NMath::TCInt2<typename NMib::NTraits::TCSigned<t_CUpper>::CType, t_CLower> CType;
		};

		template <typename t_CUpper, typename t_CLower>
		class NMib::NTraits::NImplementation::TCIsInteger<NMib::NMath::TCInt2<t_CUpper, t_CLower>>
		{
		public:
			enum
			{
				EValue = true
			};
		};
#endif

	}
	/*
	template <typename t_CType0, typename t_CUpper, typename t_CLower>
	class TCConvert<t_CType0, NMath::TCInt2<t_CUpper, t_CLower> >
	{
	public:
		static inline_small t_CType0 fs_Convert(NMath::TCInt2<t_CUpper, t_CLower> const &_From)
		{
			t_CType0 Ret;
			Ret = (NMib::fg_Convert<t_CType0>(_From.m_Upper) << (fg_Min((mint)NMath::TCInt2<t_CUpper, t_CLower>::ELowerBits, sizeof(t_CType0)*8) - 1)) << 1;
			Ret = Ret | NMib::fg_Convert<t_CType0>(_From.m_Lower);
			return Ret;
		}
	};*/
}

