// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	namespace NMath
	{
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::CInternalFloat()
		{
			*this = fs_0();
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_LogE_2() -> CInternalFloat 
		{
			static bint bInit = false;
			static CInternalFloat Temp = fs_2();
			if (!bInit)
			{
				Temp.LogNFull();
				bInit = true;
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Log2_E() -> CInternalFloat 
		{
			static bint bInit = false;
			static CInternalFloat Temp = fs_1();
			if (!bInit)
			{
				Temp.Div(fs_LogE_2());
				bInit = true;
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_LogE_10() -> CInternalFloat 
		{
			static bint bInit = false;
			static CInternalFloat Temp;
			if (!bInit)
			{
				Temp.f_FromInt(10);
				Temp.f_LogN();
				bInit = true;
			}
			
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Log10_E() -> CInternalFloat 
		{
			static bint bInit = false;
			static CInternalFloat Temp = fs_1();
			if (!bInit)
			{
				Temp.Div(fs_LogE_10());
				bInit = true;
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Log2_10() -> CInternalFloat 
		{
			static bint bInit = false;
			static CInternalFloat Temp;
			if (!bInit)
			{
				bInit = true;
				Temp.f_FromInt(10);
				Temp.f_Log2();
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Log10_2() -> CInternalFloat 
		{
			static bint bInit = false;
			static CInternalFloat Temp = fs_1();
			if (!bInit)
			{
				Temp.Div(fs_Log2_10());
				bInit = true;
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_E() -> CInternalFloat 
		{
			static bint bInit = false;
			static CInternalFloat StaticRet;
			if (!bInit)
			{
				bInit = true;
				CInternalFloat Temp = fs_1();
				CInternalFloat Div = fs_1();
				CInternalFloat Temp2 = fs_0();
				CInternalFloat Prev = Temp2;
				CSignedMantissa Current = 1;

				while (!Prev.f_AlmostEqual(Temp, 0))
				{
					Prev = Temp;
					Temp2 = fs_1();
					Temp2.Div(Div);
					Temp.Add(Temp2);
					++Current;
					Div.Mul(CInternalFloat::fs_FromInt(Current));
				}
				StaticRet = Temp;
			}

			return StaticRet;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Euler() -> CInternalFloat
		{
			// Calculate Euler with Kluyver's series
			static bint bInit = false;
			static CInternalFloat StaticRet;
			if (!bInit)
			{
				bInit = true;
#if 0

			CInternalFloat Result = fs_0();
			CInternalFloat Prev = fs_1	();

			CSignedMantissa k = 1;
			CInternalFloat Ak = fs_0_5();
			CInternalFloat Temp = fs_0();
			CInternalFloat Temp2 = fs_0();
			CInternalFloat Temp3 = fs_0();
			CInternalFloat Temp4 = fs_0();
			CInternalFloat TempSum = fs_0();

			const mint kMax = 2000;
			CInternalFloat *kHist = DMibNew CInternalFloat[kMax];
			kHist[0] = fs_0_5();
	
			while (!Prev.f_AlmostEqual(Result, 0) && k < kMax)
			{

				Prev = Result;
				Temp4 = Ak;
				Temp2.f_FromInt(k);
				Temp3.f_FromInt(k+1);
				Temp2.Mul(Temp3);
				Temp4.Div(Temp2);
				Result.Add(Temp4);


				++k;

				Temp2 = fs_1();
				Temp3.f_FromInt(k+1);
				Temp2.Div(Temp3);

				TempSum = fs_0();
				for (CSignedMantissa i = 1; i < k; ++i)
				{
					Temp3.f_FromInt(fg_Convert<CSignedMantissa>(k-i));
					Temp4.f_FromInt(fg_Convert<CSignedMantissa>(i * (i+1)));
					Temp3.Div(Temp4);
					Temp3.Mul(kHist[k - i - 1]);
					TempSum.Add(Temp3);
				}

				Temp2.Mul(TempSum);

				Ak = Temp2;
				kHist[k-1] = Ak;
			}

			delete [] kHist;

			Result.Add(fs_1());
			Result.Sub(fs_LogE_2());

			return Result;
#else
			CInternalFloat Result = fs_0();
			CInternalFloat ResultSum = fs_0();
			CInternalFloat Prev = fs_1	();

			aint k = 1;
			CInternalFloat Ak = fs_0_5();
			CInternalFloat Temp = fs_0();
			CInternalFloat Temp2 = fs_0();
			CInternalFloat Temp3 = fs_0();
			CInternalFloat Temp4 = fs_0();
			CInternalFloat TempSum = fs_0();

			aint n = 16;
			

			CInternalFloat Sum;
			CInternalFloat Sum2 = fs_1();
			for (aint i = 1; i < n; ++i)
			{
				Temp = fs_1();
				Temp2.f_FromInt(i);
				Sum2.Mul(Temp2);
				Temp.Div(Temp2);
				Sum.Add(Temp);
			}

			const aint kMax = 2000;
			CInternalFloat *kHist = DMibNew CInternalFloat[kMax];
			kHist[0] = fs_0_5();
	
			while (!Prev.f_AlmostEqual(Result, 0) && k < kMax)
			{
				Prev = Result;
				Temp4 = Ak;
				Temp2.f_FromInt(k);
				for (aint i = 1; i < n; ++i)
				{
					Temp3.f_FromInt(k+i);
					Temp2.Mul(Temp3);
				}
				Temp4.Div(Temp2);
				ResultSum.Add(Temp4);

				Result = ResultSum;
				Result.Mul(Sum2);
				Temp.f_FromInt(n);
				Temp.f_LogN();
				Temp2 = Sum;
				Temp2.Sub(Temp);
				Result.Add(Temp2);

				++k;

				Temp2 = fs_1();
				Temp3.f_FromInt(k+1);
				Temp2.Div(Temp3);

				TempSum = fs_0();
				for (aint i = 1; i < k; ++i)
				{
					Temp3.f_FromInt(k-i);
					Temp4.f_FromInt(i * (i+1));
					Temp3.Div(Temp4);
					Temp3.Mul(kHist[k - i - 1]);
					TempSum.Add(Temp3);
				}

				Temp2.Mul(TempSum);

				Ak = Temp2;
				kHist[k-1] = Ak;
			}

			delete [] kHist;

			StaticRet = Result;
			}



			return StaticRet;
#endif
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_GoldenRatio() -> CInternalFloat
		{
			static bint bInit = false;
			static CInternalFloat StaticRet;
			if (!bInit)
			{
				bInit = true;
				CInternalFloat Temp = CInternalFloat::fs_FromInt(5);
				Temp.f_Sqrt();
				Temp.Add(fs_1());
				Temp.Mul(fs_0_5());
				StaticRet = Temp;
			}
			return StaticRet;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Pi() -> CInternalFloat
		{
			// PI = 16 * atan(1/5) - 4 * atan(1/239)

			static bint bInit = false;
			static CInternalFloat StaticRet;
			if (!bInit)
			{
				bInit = true;
				CInternalFloat Temp = fs_1();
				CInternalFloat Temp2 = CInternalFloat::fs_FromInt(5);
				Temp.Div(Temp2);
				Temp.ATan();
				Temp2 = CInternalFloat::fs_FromInt(16);
				Temp.Mul(Temp2);
				Temp2 = fs_1();
				CInternalFloat Temp3 = CInternalFloat::fs_FromInt(239);
				Temp2.Div(Temp3);
				Temp2.ATan();
				Temp3 = CInternalFloat::fs_FromInt(4);
				Temp2.Mul(Temp3);
				Temp.Sub(Temp2);
				StaticRet = Temp;
			}

			return StaticRet;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Sqrt2() -> CInternalFloat
		{
			static bint bInit = false;
			static CInternalFloat StaticRet;
			if (!bInit)
			{
				bInit = true;
				CInternalFloat Temp = fs_2();
				Temp.f_Sqrt();
				StaticRet = Temp;
			}
			return StaticRet;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::CInternalFloat(const TCFloat &_Source)
		{
			*this = _Source;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::operator = (const TCFloat &_Source) -> CInternalFloat &
		{
			CExponent Exponent = _Source.f_GetExponent();			
			CSignedMantissa Mantissa = _Source.f_GetMantissa();
			Mantissa = Mantissa << (EInternalMantissaBits - EMantissaBits);
			
			if (Mantissa)
			{
				while (Mantissa < (CSignedMantissa(1) << (aint)(EInternalMantissaBits)))
				{
					Mantissa <<= 1;
					--Exponent;
				}
			}
			
			f_SetAllRound(_Source.f_GetSignBits(), Exponent, Mantissa, 0);
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		bint TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_AlmostEqual(const CInternalFloat &_Value, int _nBits)
		{
			if (m_Sign != _Value.m_Sign)
				return false;
			if (m_Exponent != _Value.m_Exponent)
				return false;
			if (m_Mantissa > _Value.m_Mantissa && (m_Mantissa - _Value.m_Mantissa) >= (CMantissa(1) << _nBits))
				return false;
			if (m_Mantissa < _Value.m_Mantissa && (_Value.m_Mantissa - m_Mantissa) >= (CMantissa(1) << _nBits))
				return false;

			return true;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_SetAllRound(const CInteger &_Sign, const CExponent &_Exponent, const CMantissa &_Mantissa, aint _AtleastExtraBits)
		{
			CExponent Exponent = _Exponent;
			aint ToShift = _AtleastExtraBits;
			CMantissa Mantissa = _Mantissa >> ToShift;
			while (Mantissa >= CMantissa(1) << (aint)(EInternalMantissaBits+1))
			{
				++ToShift;
				++Exponent;
				Mantissa = _Mantissa >> ToShift;
			}
			static const CExponent ExponentBias = (CExponent(1) << (aint)(EInternalExponentBits - 1)) - CExponent(1);
			static const CExponent MinExponent = -ExponentBias;
			static const CExponent MaxExponent = (CExponent(1) << (aint)(EInternalExponentBits)) - ExponentBias;
			if (Exponent < MinExponent)
			{
				aint Diff = fg_Convert<aint>(MinExponent - Exponent);
				Exponent = MinExponent;
				ToShift += Diff;

				if (Diff > (aint)(EInternalMantissaBits))
				{
					ToShift = -1;
					Mantissa = 0;
				}
				else
				{
					Mantissa >>= Diff;
				}
			}
			else if (Exponent >= MaxExponent)
			{
				Exponent = MaxExponent;
				ToShift = -1;
				Mantissa = 0;
			}

			// For now lets round to nearest

			if (_Sign != CInteger(0))
			{
	//			if (ToShift > 0 && (_Mantissa & CMantissa(1) << (ToShift-1)) != 0)
	//				--Mantissa;

				if ((Mantissa & 1) != CMantissa(0))
					--Mantissa;
			}
			else
			{
//						if (ToShift > 0 && (_Mantissa & CMantissa(1) << (ToShift-1)) != 0)
//							++Mantissa;
				if ((Mantissa & 1) != CMantissa(0))
					++Mantissa;
			}
//					if (ToShift > 0 && (_Mantissa & CMantissa(1) << (ToShift-1)) != 0)
//						++Mantissa;

			m_Sign = _Sign;
			m_Exponent = Exponent;
			m_Mantissa = Mantissa;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::Mul(const CInternalFloat &_Value)
		{
			CInteger Sign = m_Sign ^ _Value.m_Sign;
			CExponent Exponent = m_Exponent + _Value.m_Exponent;
			CMantissa Mantissa0 = m_Mantissa;
			CMantissa Mantissa1 = _Value.m_Mantissa;
			CMantissa NewMantissa = Mantissa0 * Mantissa1;
			f_SetAllRound(Sign, Exponent, NewMantissa, EInternalMantissaBits);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::Div(const CInternalFloat &_Value)
		{
			CInteger Sign = m_Sign ^ _Value.m_Sign;
			CExponent Exponent = m_Exponent - _Value.m_Exponent;

			CMantissa Mantissa0 = m_Mantissa;
			Mantissa0 <<= EInternalMantissaBits+1;
			CMantissa Mantissa1 = _Value.m_Mantissa;
			CMantissa NewMantissa = (Mantissa0 / Mantissa1);
			f_SetAllRound(Sign, Exponent-1, NewMantissa, 0);

		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::Add(const CInternalFloat &_Value)
		{
			CInteger Sign0 = m_Sign;
			CInteger Sign1 = _Value.m_Sign;
			CExponent Exponent0 = m_Exponent;
			CExponent Exponent1 = _Value.m_Exponent;
			CSignedMantissa Mantissa0 = m_Mantissa;
			CSignedMantissa Mantissa1 = _Value.m_Mantissa;
			
			int StorageBits = EInternalExponentBits;
			(void)StorageBits;

			static const CExponent ExponentBias = (CExponent(1) << (aint)(EInternalExponentBits - 1)) - CExponent(1);
			static const CExponent MinExponent = -ExponentBias + CExponent(1);

			if (Exponent0 > Exponent1)
			{
				aint Diff = fg_Convert<aint>(Exponent0 - Exponent1);
				CSignedMantissa NewMantissa;
				if (Diff > EInternalMantissaBits)
				{
					if (Sign0 != 0)
						NewMantissa = -Mantissa0;
					else
						NewMantissa = Mantissa0;
				}
				else
				{
					if (Sign0 != 0)
						NewMantissa = -Mantissa0;
					else
						NewMantissa = Mantissa0;

					if (Sign1 != 0)
						NewMantissa -= (Mantissa1 >> Diff);
					else
						NewMantissa += (Mantissa1 >> Diff);
				}

				if (NewMantissa < 0)
				{
					NewMantissa = -NewMantissa;
					Sign0 = 1;
				}
				else
					Sign0 = 0;

				if (NewMantissa == 0)
				{
					Exponent0 = MinExponent;
				}
				else
				{
					while (Exponent0 > MinExponent && NewMantissa < (CSignedMantissa(1) << (aint)(EInternalMantissaBits)))
					{
						NewMantissa <<= 1;
						--Exponent0;
					}
				}

				f_SetAllRound(Sign0, Exponent0, NewMantissa, 0);
			}
			else 
			{
				aint Diff = fg_Convert<aint>(Exponent1 - Exponent0);
				CSignedMantissa NewMantissa;
				if (Diff > EInternalMantissaBits)
				{
					if (Sign1 != 0)
						NewMantissa = -Mantissa1;
					else
						NewMantissa = Mantissa1;
				}
				else
				{
					if (Sign1 != 0)
						NewMantissa = -Mantissa1;
					else
						NewMantissa = Mantissa1;

					if (Sign0 != 0)
						NewMantissa -= (Mantissa0 >> Diff);
					else
						NewMantissa += (Mantissa0 >> Diff);
				}

				if (NewMantissa < 0)
				{
					NewMantissa = -NewMantissa;
					Sign0 = 1;
				}
				else
					Sign0 = 0;

				if (NewMantissa == 0)
					Exponent1 = MinExponent;
				else
				{
					while (Exponent1 > MinExponent && NewMantissa < (CSignedMantissa(1) << (aint)(EInternalMantissaBits)))
					{
						NewMantissa <<= 1;
						--Exponent1;
					}
				}

				f_SetAllRound(Sign0, Exponent1, NewMantissa, 0);
			}
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::Sub(const CInternalFloat &_Value)
		{
			CInternalFloat Temp = _Value;
			Temp.m_Sign = !Temp.m_Sign;
			Add(Temp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::ATan()
		{
			CInternalFloat Result = *this;
			CInternalFloat Squared = Result;
			Squared.Mul(Result);
			
			CInternalFloat Term = Result;
			CInternalFloat Two = TCFloat::fs_2();
			CInternalFloat Temp = TCFloat::fs_0();
			static const CExponent ExponentBias = (CExponent(1) << (aint)(EInternalExponentBits - 1)) - CExponent(1);
			static const CExponent MinExponent = -ExponentBias;
			
			CInternalFloat Divisor = TCFloat::fs_1();
			CInternalFloat LastResult = fs_Inf();
			while ((Term.m_Mantissa != 0 || Term.m_Exponent != MinExponent) && !Result.f_AlmostEqual(LastResult, 0))
			{
				LastResult = Result;

				Divisor.Add(Two);
				Term.Mul(Squared);
				Temp = Term;
				Temp.Div(Divisor);
				Result.Sub(Temp);

				Divisor.Add(Two);
				Term.Mul(Squared);
				Temp = Term;
				Temp.Div(Divisor);
				Result.Add(Temp);
			}
			*this = Result;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::Remainder()
		{
		/*	TCFloat TempFloatte;
			TempFloatte.f_SetAllRound(m_Sign, m_Exponent - 1, m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			Sub(TCFloat(TempFloatte.f_ToInt()));
			return;*/
			if (m_Exponent > CExponent(EInternalMantissaBits + 1))
			{
				m_Exponent = 0;
				m_Mantissa = CMantissa(1) << (aint)(EInternalMantissaBits);
			}
			else
			{
				if (m_Exponent >= 0)
				{
					m_Mantissa &= DMibBitRangeOne(0, EInternalMantissaBits - (fg_Convert<aint>(m_Exponent) + 1), CMantissa(1));
					m_Mantissa <<= fg_Convert<aint>((m_Exponent + 1));
					if (m_Mantissa != 0)
					{
						m_Exponent = -1;
						while ((m_Mantissa < (CMantissa(1) << (aint)(EInternalMantissaBits))) != 0)
						{
							m_Mantissa <<= 1;
							--m_Exponent;
						}
					}
					else
					{
						*this = TCFloat::fs_0();
					}
				}
			}
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_ToInt() -> CSignedMantissa
		{
			aint f_Exp = fg_Convert<aint>(m_Exponent) - EInternalMantissaBits;
			CSignedMantissa Sign = CSignedMantissa(1) - (m_Sign << 1);
			
			if (f_Exp >= 0)
				return (m_Mantissa << f_Exp) * Sign;
			else
				return (m_Mantissa >> (-f_Exp) ) * Sign;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_FromInt(const CSignedMantissa &_Int)
		{
			CInteger Sign = 0;
			CSignedMantissa Mantissa = _Int;
			if (Mantissa < 0)
			{
				Mantissa = -Mantissa;
				Sign = 1;
			}
			CExponent Exponent = (aint)(EInternalMantissaBits);
			if (Mantissa == 0)
			{
				static const CExponent ExponentBias = (CExponent(1) << (aint)(EInternalExponentBits - 1)) - CExponent(1);
				static const CExponent MinExponent = -ExponentBias;
				Exponent = MinExponent;
			}
			else
			{
				while (Mantissa < (CSignedMantissa(1) << (aint)(EInternalMantissaBits)))
				{
					Mantissa <<= 1;
					--Exponent;
				}
			}

			f_SetAllRound(Sign, Exponent, Mantissa, 0);
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_FromInt(const CSignedMantissa &_Other) -> CInternalFloat
		{
			CInternalFloat Ret;
			Ret.f_FromInt(_Other);
			return Ret;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_ExpN()
		{
			{
				CInternalFloat Temp = *this;
				Temp.Mul(fs_Log2_E());
				Temp.f_Exp2();
				*this = Temp;
			}
			return;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Exp10()
		{
			{
				CInternalFloat Temp = *this;
				Temp.Mul(fs_Log2_10());
				Temp.f_Exp2();
				*this = Temp;
			}
			return;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::GetFloat() -> TCFloat
		{
			TCFloat Temp;
			Temp.f_SetAllRound(m_Sign, CInteger(m_Exponent - 1), CDoubleInteger(m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::LogNFull()
		{		
			CInternalFloat ResultCalc = TCFloat::fs_1();
			CInternalFloat Temp = *this;
			CInternalFloat One = TCFloat::fs_1();
			//CInternalFloat Two = TCFloat::fs_2();
			CInternalFloat Temp2 = *this;

			//y = (x-1) / (x + 1);
			Temp.Sub(One);
			Temp2.Add(One);
			
			Temp.Div(Temp2);
			CInternalFloat Y = Temp;
			CInternalFloat YSqr = Temp;
			YSqr.Mul(Temp);
			CInternalFloat YMul = YSqr;
			CSignedMantissa DivInt = 3;
			CInternalFloat Y2 = Y;
			Y2.Mul(TCFloat::fs_2());
			CInternalFloat Prev = TCFloat::fs_0();
			CInternalFloat Result = TCFloat::fs_1();

			while (!Result.f_AlmostEqual(Prev, 0))
			{
				Prev = Result;

				Temp = One;

				CInternalFloat TempFromInt;
				TempFromInt.f_FromInt(DivInt);

				Temp.Div(TempFromInt);
				Temp.Mul(YMul);

				ResultCalc.Add(Temp);

				YMul.Mul(YSqr);

				DivInt += 2;

				Result = ResultCalc;
			}

			Result.Mul(Y2);

			*this = Result;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_LogN()
		{				
			CInternalFloat Temp = TCFloat::fs_0();
			Temp.m_Mantissa = m_Mantissa;
			Temp.m_Sign = m_Sign;
			Temp.m_Exponent = 0;
			Temp.LogNFull();

			f_FromInt(m_Exponent);
			Mul(fs_LogE_2());
			Add(Temp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Log10()
		{				
			CInternalFloat Temp = TCFloat::fs_0();
			Temp.m_Mantissa = m_Mantissa;
			Temp.m_Sign = m_Sign;
			Temp.m_Exponent = 0;
			Temp.LogNFull();
			Temp.Mul(fs_Log10_E());

			f_FromInt(m_Exponent);
			Mul(fs_Log10_2());
			Add(Temp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Log2()
		{
			CExponent Exponent = m_Exponent;
			m_Exponent = 0;
			LogNFull();
			Mul(fs_Log2_E());
			CInternalFloat Temp;
			Temp.f_FromInt(Exponent);
			Add(Temp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Exp2()
		{
			if (m_Sign != 0)
			{
				CInternalFloat Temp = *this;
				Temp.m_Sign = 0;
				Temp.f_Exp2();
				*this = TCFloat::fs_1();
				Div(Temp);
				return;
			}
			CInternalFloat IntegerPart = *this;
			CInternalFloat Temp = *this;

			// This is the integer part
			Temp.Remainder();

			Temp.Mul(fs_LogE_2());

			CInternalFloat Org = Temp;
			CInternalFloat Result = TCFloat::fs_0();

			CInternalFloat Div = fs_2();
			CInternalFloat Temp2 = fs_0();
			CInternalFloat Prev = Div;
			CSignedMantissa Current = 2;
			Temp.Mul(Org);

			while (!Prev.f_AlmostEqual(Result, 0))
			{
				Prev = Result;

				Temp2 = Temp;
				Temp2.Div(Div);

				Result.Add(Temp2);

				Temp.Mul(Org);

				++Current;
				Div.Mul(CInternalFloat::fs_FromInt(Current));
			}
			Result.Add(Org);
			Result.Add(TCFloat::fs_1());

			Result.m_Exponent += fg_Convert<CExponent>(IntegerPart.f_ToInt());

			*this = Result;
			
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Sqrt()
		{
			if (m_Sign != 0)
			{
				*this = fs_NegQNan();
			}
			CInternalFloat Temp = *this;
			CInternalFloat Prev = Temp;
			CInternalFloat Two = fs_2();
			Temp.Div(Two);

			while (!Prev.f_AlmostEqual(Temp, 1))
			{
				Prev = Temp;
				Temp = *this;
				Temp.Div(Prev);
				Temp.Add(Prev);
				Temp.Div(Two);
			}
			*this = Temp;
		}
	}
}
