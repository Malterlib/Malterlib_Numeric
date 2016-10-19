// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	namespace NMath
	{
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::CInternalFloat()
		{
			*this = fs_0();
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_LogE_2() -> CInternalFloat 
		{
			static bool bInit = false;
			static CInternalFloat Temp = fs_2();
			if (!bInit)
			{
				Temp.f_LogNFull();
				bInit = true;
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Log2_E() -> CInternalFloat 
		{
			static bool bInit = false;
			static CInternalFloat Temp = fs_1();
			if (!bInit)
			{
				Temp.f_Div(fs_LogE_2());
				bInit = true;
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_LogE_10() -> CInternalFloat 
		{
			static bool bInit = false;
			static CInternalFloat Temp;
			if (!bInit)
			{
				Temp.f_FromInt(10);
				Temp.f_LogN();
				bInit = true;
			}
			
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Log10_E() -> CInternalFloat 
		{
			static bool bInit = false;
			static CInternalFloat Temp = fs_1();
			if (!bInit)
			{
				Temp.f_Div(fs_LogE_10());
				bInit = true;
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Log2_10() -> CInternalFloat 
		{
			static bool bInit = false;
			static CInternalFloat Temp;
			if (!bInit)
			{
				bInit = true;
				Temp.f_FromInt(10);
				Temp.f_Log2();
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Log10_2() -> CInternalFloat 
		{
			static bool bInit = false;
			static CInternalFloat Temp = fs_1();
			if (!bInit)
			{
				Temp.f_Div(fs_Log2_10());
				bInit = true;
			}
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_E() -> CInternalFloat 
		{
			static bool bInit = false;
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
					Temp2.f_Div(Div);
					Temp.f_Add(Temp2);
					++Current;
					Div.f_Mul(CInternalFloat::fs_FromInt(Current));
				}
				StaticRet = Temp;
			}

			return StaticRet;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Euler() -> CInternalFloat
		{
			// Calculate Euler with Kluyver's series
			static bool bInit = false;
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
				Sum2.f_Mul(Temp2);
				Temp.f_Div(Temp2);
				Sum.f_Add(Temp);
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
					Temp2.f_Mul(Temp3);
				}
				Temp4.f_Div(Temp2);
				ResultSum.f_Add(Temp4);

				Result = ResultSum;
				Result.f_Mul(Sum2);
				Temp.f_FromInt(n);
				Temp.f_LogN();
				Temp2 = Sum;
				Temp2.f_Sub(Temp);
				Result.f_Add(Temp2);

				++k;

				Temp2 = fs_1();
				Temp3.f_FromInt(k+1);
				Temp2.f_Div(Temp3);

				TempSum = fs_0();
				for (aint i = 1; i < k; ++i)
				{
					Temp3.f_FromInt(k-i);
					Temp4.f_FromInt(i * (i+1));
					Temp3.f_Div(Temp4);
					Temp3.f_Mul(kHist[k - i - 1]);
					TempSum.f_Add(Temp3);
				}

				Temp2.f_Mul(TempSum);

				Ak = Temp2;
				kHist[k-1] = Ak;
			}

			delete [] kHist;

			StaticRet = Result;
			}



			return StaticRet;
#endif
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_GoldenRatio() -> CInternalFloat
		{
			static bool bInit = false;
			static CInternalFloat StaticRet;
			if (!bInit)
			{
				bInit = true;
				CInternalFloat Temp = CInternalFloat::fs_FromInt(5);
				Temp.f_Sqrt();
				Temp.f_Add(fs_1());
				Temp.f_Mul(fs_0_5());
				StaticRet = Temp;
			}
			return StaticRet;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Pi() -> CInternalFloat
		{
			// PI = 16 * atan(1/5) - 4 * atan(1/239)

			static bool bInit = false;
			static CInternalFloat StaticRet;
			if (!bInit)
			{
				bInit = true;
				CInternalFloat Temp = fs_1();
				CInternalFloat Temp2 = CInternalFloat::fs_FromInt(5);
				Temp.f_Div(Temp2);
				Temp.f_ATan();
				Temp2 = CInternalFloat::fs_FromInt(16);
				Temp.f_Mul(Temp2);
				Temp2 = fs_1();
				CInternalFloat Temp3 = CInternalFloat::fs_FromInt(239);
				Temp2.f_Div(Temp3);
				Temp2.f_ATan();
				Temp3 = CInternalFloat::fs_FromInt(4);
				Temp2.f_Mul(Temp3);
				Temp.f_Sub(Temp2);
				StaticRet = Temp;
			}

			return StaticRet;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_Sqrt2() -> CInternalFloat
		{
			static bool bInit = false;
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

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::CInternalFloat(const TCFloat &_Source)
		{
			*this = _Source;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_GetSharedMantissa
			(
				CInternalFloat const &_Other
				, CMantissa &o_OtherMantissa
				, mint &o_nMantissaBits
			) 
			-> CMantissa
		{
			mint MantissaBits = m_MantissaBits;
			if (_Other.m_MantissaBits > MantissaBits)
			{
				mint Diff = _Other.m_MantissaBits - MantissaBits; 
				o_nMantissaBits = _Other.m_MantissaBits;
				o_OtherMantissa = _Other.m_Mantissa;
				return m_Mantissa << Diff;
			}
			else if (_Other.m_MantissaBits < MantissaBits)
			{
				mint Diff = MantissaBits - _Other.m_MantissaBits; 
				o_nMantissaBits = MantissaBits;
				o_OtherMantissa = _Other.m_Mantissa << Diff;
				return m_Mantissa;
			}
			else
			{
				o_nMantissaBits = MantissaBits;
				o_OtherMantissa = _Other.m_Mantissa;
				return m_Mantissa;
			}
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::operator = (const TCFloat &_Source) -> CInternalFloat &
		{
			CExponent Exponent = _Source.f_GetExponent();			
			CSignedMantissa Mantissa = _Source.f_GetMantissa();
			f_SetAllRound(_Source.f_GetSignBits(), Exponent, Mantissa, EMantissaBits);
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		bool TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_AlmostEqual(const CInternalFloat &_Value, int _nBits)
		{
			if (m_Sign != _Value.m_Sign)
				return false;
			if (m_Exponent != _Value.m_Exponent)
				return false;
			
			mint nMantissaBits;
			CMantissa Mantissa1;
			CMantissa Mantissa0 = f_GetSharedMantissa(_Value, Mantissa1, nMantissaBits);
			CMantissa MantissaDiff;
			if (Mantissa0 > Mantissa1)
				MantissaDiff = Mantissa0 - Mantissa1;
			else if (Mantissa0 < Mantissa1)
				MantissaDiff = Mantissa1 - Mantissa0;
			else
				return true;
			
			if (MantissaDiff > (CMantissa(1) << _nBits) - CMantissa(1))
				return false;

			return true;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_SetAllRound
			(
				const CInteger &_Sign
				, const CExponent &_Exponent
				, const CMantissa &_Mantissa
				, aint _nMantissaBits
			)
		{
			CExponent Exponent = _Exponent;
			CMantissa Mantissa = _Mantissa;
			if (Mantissa)
			{
				auto MinMantissa = (CMantissa(1) << (aint)(_nMantissaBits)) - 1;
				while (Mantissa <= MinMantissa)
				{
					--Exponent;
					--_nMantissaBits;
					MinMantissa >>= 1;
				}
				auto MaxMantissa = (CMantissa(1) << (aint)(_nMantissaBits+1)) - 1;
				while (Mantissa > MaxMantissa)
				{
					++Exponent;
					if (_nMantissaBits == EInternalMaxMantissaBits)
						Mantissa >>= 1;
					else
					{
						++_nMantissaBits;
						MaxMantissa <<= 1;
					}
				}
				
				auto MantissaMask = CMantissa(1);
				while ((Mantissa & MantissaMask) != MantissaMask)
				{
					Mantissa >>= 1;
					--_nMantissaBits;
				}
			}
			
			static const CExponent ExponentBias = (CExponent(1) << (aint)(EInternalExponentBits - 1)) - CExponent(1);
			static const CExponent MinExponent = -ExponentBias;
			static const CExponent MaxExponent = (CExponent(1) << (aint)(EInternalExponentBits)) - ExponentBias;
			
			if (Exponent < MinExponent)
			{
				Exponent = MinExponent;
				Mantissa = 0;
				_nMantissaBits = 0;
			}
			else if (Exponent >= MaxExponent)
			{
				Exponent = MaxExponent;
				_nMantissaBits = EInternalMaxMantissaBits;
				Mantissa = (CMantissa(1) << (aint)(EInternalMaxMantissaBits+1)) - 1;
			}

			// For now lets round to nearest
/*
			if (_Sign != CInteger(0))
			{
				if ((Mantissa & 1) != CMantissa(0))
					--Mantissa;
			}
			else
			{
				if ((Mantissa & 1) != CMantissa(0))
					++Mantissa;
			}*/

			m_Sign = _Sign;
			m_Exponent = Exponent;
			m_Mantissa = Mantissa;
			m_MantissaBits = _nMantissaBits; 
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Mul(const CInternalFloat &_Value)
		{
			CInteger Sign = m_Sign ^ _Value.m_Sign;
			CExponent Exponent = m_Exponent + _Value.m_Exponent;
			
			CQuadMantissa Mantissa0 = m_Mantissa;
			CQuadMantissa Mantissa1 = _Value.m_Mantissa;
			
			mint nTotalMantissaBits = m_MantissaBits + _Value.m_MantissaBits;
			
			if (nTotalMantissaBits > EInternalMaxQuadMantissaBits)
			{
				if (m_MantissaBits > _Value.m_MantissaBits)
				{
					mint Diff = fg_Min(nTotalMantissaBits - EInternalMaxQuadMantissaBits, m_MantissaBits - _Value.m_MantissaBits); 
					Mantissa0 >>= Diff;
					nTotalMantissaBits -= Diff; 
				}
				else if (_Value.m_MantissaBits > m_MantissaBits)
				{
					mint Diff = fg_Min(nTotalMantissaBits - EInternalMaxQuadMantissaBits, _Value.m_MantissaBits - m_MantissaBits); 
					Mantissa1 >>= Diff;
					nTotalMantissaBits -= Diff; 
				}
				if (nTotalMantissaBits > EInternalMaxQuadMantissaBits)
				{
					mint Diff = ((nTotalMantissaBits - EInternalMaxQuadMantissaBits) + 1) / 2; 
					Mantissa0 >>= Diff;
					Mantissa1 >>= Diff;
					nTotalMantissaBits -= Diff*2; 
				}
			}
			
			CQuadMantissa NewMantissa = Mantissa0 * Mantissa1;
			if (nTotalMantissaBits > EInternalMaxMantissaBits)
			{
				NewMantissa >>= nTotalMantissaBits - EInternalMaxMantissaBits;
				nTotalMantissaBits = EInternalMaxMantissaBits;
			}
			f_SetAllRound(Sign, Exponent, fg_Convert<CMantissa>(NewMantissa), nTotalMantissaBits);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Div(const CInternalFloat &_Value)
		{
			CInteger Sign = m_Sign ^ _Value.m_Sign;
			CExponent Exponent = m_Exponent - _Value.m_Exponent;

			CQuadMantissa Mantissa0 = m_Mantissa;
			CQuadMantissa Mantissa1 = _Value.m_Mantissa;
			
			if (m_MantissaBits < EInternalMaxQuadMantissaBits)
			{
				mint Diff = EInternalMaxQuadMantissaBits - m_MantissaBits;
				Mantissa0 <<= Diff;
			}
			
			mint nDivMantissaBits = _Value.m_MantissaBits;
			if (nDivMantissaBits > EInternalHalfQuadMantissaBits)
			{
				mint Diff = nDivMantissaBits - EInternalHalfQuadMantissaBits;
				nDivMantissaBits = EInternalHalfQuadMantissaBits;
				Mantissa1 >>= Diff;
			}

			
			CQuadMantissa NewMantissa = Mantissa0 / Mantissa1;
			aint Diff = aint(EInternalMaxQuadMantissaBits) - aint(nDivMantissaBits);
			if (Diff > EInternalMaxMantissaBits)
			{
				mint Diff2 = Diff - EInternalMaxMantissaBits;
				NewMantissa >>= Diff2;
				Diff = EInternalMaxMantissaBits;
			}
			f_SetAllRound(Sign, Exponent, fg_Convert<CMantissa>(NewMantissa), Diff);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Add(const CInternalFloat &_Value)
		{
			CInteger Sign0 = m_Sign;
			CInteger Sign1 = _Value.m_Sign;
			CExponent Exponent0 = m_Exponent;
			CExponent Exponent1 = _Value.m_Exponent;
			
			mint nMantissaBits;
			CMantissa MantissaGet1;
			CMantissa MantissaGet0 = f_GetSharedMantissa(_Value, MantissaGet1, nMantissaBits);
			if (nMantissaBits < mint(EInternalMaxMantissaBits - 1))
			{
				mint Diff = (EInternalMaxMantissaBits - 1) - nMantissaBits; 
				MantissaGet0 <<= Diff;
				MantissaGet1 <<= Diff;
				nMantissaBits = mint(EInternalMaxMantissaBits - 1);
			}
			
			CSignedMantissa Mantissa0 = MantissaGet0;
			CSignedMantissa Mantissa1 = MantissaGet1;
			
			if (Exponent0 > Exponent1)
			{
				mint Diff = fg_Convert<aint>(Exponent0 - Exponent1);
				CSignedMantissa NewMantissa;
				if (Diff > nMantissaBits)
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
					Exponent0 = 0;

				f_SetAllRound(Sign0, Exponent0, NewMantissa, nMantissaBits);
			}
			else 
			{
				mint Diff = fg_Convert<aint>(Exponent1 - Exponent0);
				CSignedMantissa NewMantissa;
				if (Diff > nMantissaBits)
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
					Exponent1 = 0;

				f_SetAllRound(Sign0, Exponent1, NewMantissa, nMantissaBits);
			}
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Sub(const CInternalFloat &_Value)
		{
			CInternalFloat Temp = _Value;
			Temp.m_Sign = !Temp.m_Sign;
			f_Add(Temp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_ATan()
		{
			CInternalFloat Result = *this;
			CInternalFloat Squared = Result;
			Squared.f_Mul(Result);
			
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

				Divisor.f_Add(Two);
				Term.f_Mul(Squared);
				Temp = Term;
				Temp.f_Div(Divisor);
				Result.f_Sub(Temp);

				Divisor.f_Add(Two);
				Term.f_Mul(Squared);
				Temp = Term;
				Temp.f_Div(Divisor);
				Result.f_Add(Temp);
			}
			*this = Result;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Remainder()
		{
			if (m_Exponent > CExponent(m_MantissaBits + 1))
			{
				m_Exponent = 0;
				m_Mantissa = 0;
			}
			else
			{
				if (m_Exponent >= 0)
				{
					CMantissa Mask;
					auto Bit = aint(m_MantissaBits) - (fg_Convert<aint>(m_Exponent) + 1);
					if (Bit >= 0)
						Mask = DMibBitRangeOne(0, m_MantissaBits - (fg_Convert<aint>(m_Exponent) + 1), CMantissa(1));
					else
						Mask = 0;
					m_Mantissa &= Mask;
					m_Mantissa <<= fg_Convert<aint>((m_Exponent + 1));
					if (m_Mantissa != 0)
					{
						m_Exponent = -1;
						while ((m_Mantissa < (CMantissa(1) << (aint)(m_MantissaBits))) != 0)
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

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_ToInt(bool &o_bOverflow) -> CSignedMantissa
		{
			aint Exp = fg_Convert<aint>(m_Exponent) - aint(m_MantissaBits);
			CSignedMantissa Sign = CSignedMantissa(1) - (m_Sign << 1);
			
			if (Exp >= 0)
			{
				if (Exp >= aint(sizeof(CMantissa)*8 - (m_MantissaBits + 1)))
				{
					o_bOverflow = true;
					return TCLimitsInt<CSignedMantissa>::mc_Max;
				}
				CSignedMantissa Ret = (m_Mantissa << Exp);
				if (Ret < 0)
				{
					o_bOverflow = true;
					return TCLimitsInt<CSignedMantissa>::mc_Max;
				}
				return Ret * Sign;
			}
			else
			{
				if (-Exp > aint(m_MantissaBits + 1))
					return 0;
				return (m_Mantissa >> (-Exp) ) * Sign;
			}
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_FromInt(const CSignedMantissa &_Int)
		{
			aint MantissaBits = sizeof(CSignedMantissa)*8-2;
			CInteger Sign = 0;
			CSignedMantissa Mantissa = _Int;
			if (Mantissa < 0)
			{
				Mantissa = -Mantissa;
				Sign = 1;
			}
			CExponent Exponent;
			if (Mantissa == 0)
			{
				static const CExponent ExponentBias = (CExponent(1) << (aint)(EInternalExponentBits - 1)) - CExponent(1);
				static const CExponent MinExponent = -ExponentBias;
				Exponent = MinExponent;
			}
			else
			{
				auto MinMantissa = CSignedMantissa(1) << (aint)(MantissaBits);
				while (Mantissa < MinMantissa)
				{
					--MantissaBits;
					MinMantissa >>= 1;
				}
				Exponent = MantissaBits;
				MantissaBits = fg_Max(MantissaBits, 0);
			}

			f_SetAllRound(Sign, Exponent, Mantissa, MantissaBits);
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::fs_FromInt(const CSignedMantissa &_Other) -> CInternalFloat
		{
			CInternalFloat Ret;
			Ret.f_FromInt(_Other);
			return Ret;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_ExpN()
		{
			{
				CInternalFloat Temp = *this;
				Temp.f_Mul(fs_Log2_E());
				Temp.f_Exp2();
				*this = Temp;
			}
			return;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Exp10()
		{
			{
				CInternalFloat Temp = *this;
				Temp.f_Mul(fs_Log2_10());
				Temp.f_Exp2();
				*this = Temp;
			}
			return;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		template <typename tf_CFloat>
		tf_CFloat TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_GetFloat()
		{
			tf_CFloat Temp;
			typename tf_CFloat::CDoubleUnsignedInteger Mantissa = m_Mantissa;
			mint MantissaBits = m_MantissaBits;
			if (MantissaBits < tf_CFloat::EMantissaBits)
			{
				Mantissa <<= tf_CFloat::EMantissaBits - MantissaBits;
				MantissaBits = tf_CFloat::EMantissaBits; 
			}
				
			Temp.f_SetAllRound(m_Sign, typename tf_CFloat::CInteger(m_Exponent), Mantissa, MantissaBits - tf_CFloat::EMantissaBits);
			return Temp;
		}
				
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_GetFloat() -> TCFloat
		{
			TCFloat Temp;
			CDoubleUnsignedInteger Mantissa = m_Mantissa;
			mint MantissaBits = m_MantissaBits;
			if (MantissaBits < EMantissaBits)
			{
				Mantissa <<= EMantissaBits - MantissaBits;
				MantissaBits = EMantissaBits; 
			}
			CInteger Exponent;
			if (m_Exponent > CExponent(TCLimitsInt<CInteger>::mc_Max))
				Exponent = TCLimitsInt<CInteger>::mc_Max;
			else
				Exponent = CInteger(m_Exponent);
			if (Mantissa == 0)
				Exponent = 0;
			Temp.f_SetAllRound(m_Sign, Exponent, Mantissa, MantissaBits - EMantissaBits);
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_LogNFull()
		{		
			CInternalFloat ResultCalc = TCFloat::fs_1();
			CInternalFloat Temp = *this;
			CInternalFloat One = TCFloat::fs_1();
			//CInternalFloat Two = TCFloat::fs_2();
			CInternalFloat Temp2 = *this;

			//y = (x-1) / (x + 1);
			Temp.f_Sub(One);
			Temp2.f_Add(One);
			
			Temp.f_Div(Temp2);
			CInternalFloat Y = Temp;
			CInternalFloat YSqr = Temp;
			YSqr.f_Mul(Temp);
			CInternalFloat YMul = YSqr;
			CSignedMantissa DivInt = 3;
			CInternalFloat Y2 = Y;
			Y2.f_Mul(TCFloat::fs_2());
			CInternalFloat Prev = TCFloat::fs_0();
			CInternalFloat Result = TCFloat::fs_1();

			while (!Result.f_AlmostEqual(Prev, 0))
			{
				Prev = Result;

				Temp = One;

				CInternalFloat TempFromInt;
				TempFromInt.f_FromInt(DivInt);

				Temp.f_Div(TempFromInt);
				Temp.f_Mul(YMul);

				ResultCalc.f_Add(Temp);

				YMul.f_Mul(YSqr);

				DivInt += 2;

				Result = ResultCalc;
			}

			Result.f_Mul(Y2);

			*this = Result;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_LogN()
		{				
			CInternalFloat Temp = TCFloat::fs_0();
			Temp.m_Mantissa = m_Mantissa;
			Temp.m_Sign = m_Sign;
			Temp.m_Exponent = 0;
			Temp.m_MantissaBits = m_MantissaBits;
			Temp.f_LogNFull();
			
			f_FromInt(m_Exponent);
			f_Mul(fs_LogE_2());
			f_Add(Temp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Log10()
		{				
			CInternalFloat Temp = TCFloat::fs_0();
			Temp.m_Mantissa = m_Mantissa;
			Temp.m_Sign = m_Sign;
			Temp.m_Exponent = 0;
			Temp.m_MantissaBits = m_MantissaBits;
			Temp.f_LogNFull();
			Temp.f_Mul(fs_Log10_E());

			f_FromInt(m_Exponent);
			f_Mul(fs_Log10_2());
			f_Add(Temp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Log2()
		{
			CExponent Exponent = m_Exponent;
			m_Exponent = 0;
			f_LogNFull();
			f_Mul(fs_Log2_E());
			CInternalFloat Temp;
			Temp.f_FromInt(Exponent);
			f_Add(Temp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Exp2()
		{
			if (m_Sign != 0)
			{
				CInternalFloat Temp = *this;
				Temp.m_Sign = 0;
				Temp.f_Exp2();
				*this = TCFloat::fs_1();
				f_Div(Temp);
				return;
			}
			CInternalFloat IntegerPart = *this;
			CInternalFloat Temp = *this;

			// This is the integer part
			Temp.f_Remainder();

			Temp.f_Mul(fs_LogE_2());

			CInternalFloat Org = Temp;
			CInternalFloat Result = TCFloat::fs_0();

			CInternalFloat Div = fs_2();
			CInternalFloat Temp2 = fs_0();
			CInternalFloat Prev = Div;
			CSignedMantissa Current = 2;
			Temp.f_Mul(Org);

			while (!Prev.f_AlmostEqual(Result, 0))
			{
				Prev = Result;

				Temp2 = Temp;
				Temp2.f_Div(Div);

				Result.f_Add(Temp2);

				Temp.f_Mul(Org);

				++Current;
				Div.f_Mul(CInternalFloat::fs_FromInt(Current));
			}
			Result.f_Add(Org);
			Result.f_Add(TCFloat::fs_1());

			bool bOverflow = false;
			auto ExponentAdd = IntegerPart.f_ToInt(bOverflow);
			Result.m_Exponent += fg_Convert<CExponent>(ExponentAdd);

			*this = Result;
			
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CInternalFloat::f_Sqrt()
		{
			if (m_Sign != 0)
			{
				*this = fs_NegQNan();
			}
			CInternalFloat Temp = *this;
			CInternalFloat Prev = Temp;
			CInternalFloat Two = fs_2();
			Temp.f_Div(Two);

			while (!Prev.f_AlmostEqual(Temp, 1) || (Prev.m_MantissaBits < (t_MantissaBits + 2) && !Prev.f_AlmostEqual(Temp, 0)))
			{
				Prev = Temp;
				Temp = *this;
				Temp.f_Div(Prev);
				Temp.f_Add(Prev);
				Temp.f_Div(Two);
			}
			*this = Temp;
		}
	}
}
