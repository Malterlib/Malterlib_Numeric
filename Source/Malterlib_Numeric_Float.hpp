// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include "Malterlib_Numeric_Float_Internal.hpp" 

namespace NMib
{
	namespace NMath
	{
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_0()
		{
			m_Data = 0;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_0_5()
		{
			m_Data = 0;
			f_SetExponent(-1);
			f_SetMantissaBits(0);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_1()
		{
			m_Data = 0;
			f_SetExponent(0);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_2()
		{
			m_Data = 0;
			f_SetExponent(1);
			f_SetMantissaBits(0);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_E()
		{
			CInternalFloat Temp = CInternalFloat::fs_E();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_Pi()
		{
			CInternalFloat Temp = CInternalFloat::fs_Pi();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_Euler()
		{
			CInternalFloat Temp = CInternalFloat::fs_Euler();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_Sqrt2()
		{
			CInternalFloat Temp = CInternalFloat::fs_Sqrt2();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_GoldenRatio()
		{
			CInternalFloat Temp = CInternalFloat::fs_GoldenRatio();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_Log2_10()
		{
			CInternalFloat Temp = CInternalFloat::fs_Log2_10();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_Log10_2()
		{
			CInternalFloat Temp = CInternalFloat::fs_Log10_2();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_LogE_10()
		{
			CInternalFloat Temp = CInternalFloat::fs_LogE_10();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_Log10_E()
		{
			CInternalFloat Temp = CInternalFloat::fs_Log10_E();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_Log2_E()
		{
			CInternalFloat Temp = CInternalFloat::fs_Log2_E();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_LogE_2()
		{
			CInternalFloat Temp = CInternalFloat::fs_LogE_2();
			f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_Inf()
		{
			f_SetSignBits(0);
			f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
			f_SetMantissaBits(0);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_NegInf()
		{
			f_SetSignBits(1);
			f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
			f_SetMantissaBits(0);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_QNan()
		{
			f_SetSignBits(0);
			f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
			f_SetMantissaBits((CUnsignedInteger(1) << (aint)(EMantissaBits - 1)) | 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_SNan()
		{
			f_SetSignBits(0);
			f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
			f_SetMantissaBits(1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_NegQNan()
		{
			f_SetSignBits(1);
			f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
			f_SetMantissaBits((CUnsignedInteger(1) << (aint)(EMantissaBits - 1)) | 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_Set_NegSNan()
		{
			f_SetSignBits(1);
			f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
			f_SetMantissaBits(1);
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_SmallestDenormal() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.f_SetMantissaBits(1);
					Temp.f_SetSign(0);
					Temp.f_SetExponentBits(0);
					return Temp;
				}()
			;
			return Cache;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_NegSmallestDenormal() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.f_SetMantissaBits(1);
					Temp.f_SetSign(1);
					Temp.f_SetExponentBits(0);
					return Temp;
				}()
			;
			return Cache;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Smallest() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.f_SetMantissaBits(0);
					Temp.f_SetSign(0);
					Temp.f_SetExponentBits(1);
					return Temp;
				}()
			;
			return Cache;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_NegSmallest() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.f_SetMantissaBits(0);
					Temp.f_SetSign(1);
					Temp.f_SetExponentBits(1);
					return Temp;
				}()
			;
			return Cache;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_LimitMin() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					if (ESignBits)
					{
						Temp.f_SetMantissa((fg_Convert<CInteger>(1) << EMantissaBits) - fg_Convert<CInteger>(1));
						Temp.f_SetSign(1);
						Temp.f_SetExponent(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits-1));
					}
					else
					{
						Temp = fs_0();
					}
					return Temp;
				}()
			;
			return Cache;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_LimitMax() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.f_SetMantissa((fg_Convert<CInteger>(1) << EMantissaBits) - fg_Convert<CInteger>(1));
					Temp.f_SetSign(0);
					Temp.f_SetExponent(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits-1));
					return Temp;
				}()
			;
			return Cache;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_0() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_0();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_0_5() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_0_5();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_1() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_1();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_2() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_2();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_E() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_E();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Pi() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_Pi();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Sqrt2() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_Sqrt2();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Euler() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_Euler();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_GoldenRatio() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_GoldenRatio();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Log10_2() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_Log10_2();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Log2_10() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_Log2_10();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Log10_E() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_Log10_E();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_LogE_10() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_LogE_10();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Log2_E() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_Log2_E();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_LogE_2() -> TCFloat
		{
			static TCFloat Cache = []
				{
					TCFloat Temp;
					Temp.fp_Set_LogE_2();
					return Temp;
				}()
			;
			return Cache;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetSignBits() const -> CInteger
		{
			if (ESignBits)
			{
				enum
				{
					EBits = ESignBits > 0 ? ESignBits : 1,
					EBitPos = ESignBits > 0 ? ESignBitPos : 1
				};
				const CInteger And = fg_PowerOfTwoMinusOne<CInteger>(EBits);
				return (m_Data & (And << (aint)(EBitPos))) >> (aint)(EBitPos);
			}
			else
				return 0;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetExponentBits() const -> CInteger
		{
			return (m_Data & (fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) << (aint)(EExponentBitPos))) >> (aint)(EExponentBitPos);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetMantissaBits() const -> CInteger
		{
			return (m_Data & (fg_PowerOfTwoMinusOne<CInteger>(EMantissaBits) << (aint)(EMantissaBitPos))) >> (aint)(EMantissaBitPos);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetSign() const -> CInteger
		{
			return CInteger(1) - (f_GetSignBits() << 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetExponent() const -> CInteger
		{
			static CInteger ExponentBias = (CInteger(1) << (aint)(EExponentBits - 1)) - CInteger(1);
			CInteger ExponentBits = f_GetExponentBits();
			if (ExponentBits != 0)
				return ExponentBits - ExponentBias;	
			else
				return CInteger(1)-ExponentBias;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetMantissa() const -> CInteger
		{
			if (f_GetExponentBits() == 0)
				return f_GetMantissaBits();
			else
				return (CInteger(1) << (aint)(EMantissaBits)) | f_GetMantissaBits();
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetDenormalizedMantissa() const -> CInteger
		{
			return f_GetMantissaBits();
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetNormalized(CInteger &o_Exponent, CInteger &o_Mantissa) const
		{
			static CInteger ExponentBias = (CInteger(1) << (aint)(EExponentBits - 1)) - CInteger(1);
			CInteger ExponentBits = f_GetExponentBits();
			if (ExponentBits != 0)
			{
				o_Exponent = ExponentBits - ExponentBias;
				o_Mantissa = (CInteger(1) << (aint)(EMantissaBits)) | f_GetMantissaBits();
			}
			else
			{
				// Denormalized
				auto Exponent = CInteger(1)-ExponentBias;
				auto Mantissa = f_GetMantissaBits();
				
				if (Mantissa)
				{
					auto MaxMantissa = CInteger(1) << EMantissaBits;
					
					while (Mantissa < MaxMantissa)
					{
						--Exponent;
						Mantissa = Mantissa << 1;
					}
				}
				else
					Exponent = 0; // Zero
				
				o_Exponent = Exponent;
				o_Mantissa = Mantissa;
			}
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_SetSignBits(const CUnsignedInteger &_Value)
		{
			if (ESignBits)
			{
				enum
				{
					EBits = ESignBits > 0 ? ESignBits : 1,
					EBitPos = ESignBits > 0 ? ESignBitPos : 1
				};

				const CUnsignedInteger And = fg_PowerOfTwoMinusOne<CUnsignedInteger>(EBits);
				m_Data = (m_Data & ~(And << uaint(EBitPos))) | ((_Value & And) << (aint)(EBitPos));
			}
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_SetExponentBits(const CUnsignedInteger &_Value)
		{
			if (EUnusedBits)
			{
				// Emulate x86 extended format
				// 0 and denormal = 0
				// Invalid and normalized = 1
				const CUnsignedInteger UnusedMask = fg_PowerOfTwoMinusOne<CUnsignedInteger>(EUnusedBits) << EUnusedBitPos;
				if (_Value == 0)
					m_Data &= ~UnusedMask;
				else
					m_Data |= UnusedMask;
			}
			const CUnsignedInteger And = fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits);
			m_Data = (m_Data & ~(And << uaint(EExponentBitPos))) | ((_Value & And) << (aint)(EExponentBitPos));
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_SetMantissaBits(const CUnsignedInteger &_Value)
		{
			const CUnsignedInteger And = fg_PowerOfTwoMinusOne<CUnsignedInteger>(EMantissaBits);
			m_Data = (m_Data & ~(And << uaint(EMantissaBitPos))) | ((_Value & And) << (aint)(EMantissaBitPos));

		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_SetSign(const CInteger &_Value)
		{
			f_SetSignBits((_Value + 1) >> 1);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_SetExponent(const CInteger &_Value)
		{
			static const CInteger ExponentBias = (CInteger(1) << (uaint(EExponentBits - 1))) - CInteger(1);
			f_SetExponentBits(_Value + ExponentBias);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_SetMantissa(const CInteger &_Value)
		{
			f_SetMantissaBits(_Value);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_SetAllRound(const CInteger &_Sign, const CInteger &_Exponent, const CDoubleInteger &_Mantissa, aint _AtleastExtraBits)
		{
			CInteger Exponent = _Exponent;
			aint ToShift = _AtleastExtraBits;
			CDoubleInteger Mantissa = _Mantissa >> ToShift;
			while (Mantissa >= (CDoubleInteger(1) << ((aint)(EMantissaBits+1)) ))
			{
				++ToShift;
				++Exponent;
				Mantissa = _Mantissa >> ToShift;
			}
			const static CInteger ExponentBias = (CInteger(1) << (aint)(EExponentBits - 1)) - CInteger(1);
			const static CInteger MinExponent = CInteger(1) - ExponentBias;
			const static CInteger MaxExponent = (CInteger(1) << (aint)(EExponentBits)) - ExponentBias - CInteger(1);

			if (Exponent < MinExponent)
			{
				aint Diff = fg_Convert<aint>(MinExponent - Exponent);
				Exponent = MinExponent - 1;
				ToShift += Diff;

				if (Diff > EMantissaBits)
				{
					ToShift = -1;
					Mantissa = 0;
				}
				else
					Mantissa >>= Diff;
			}
			else if (Exponent >= MaxExponent)
			{
				Exponent = MaxExponent;
				ToShift = -1;
				Mantissa = 0;
			}

			// For now lets round to nearest
			
			CDoubleInteger MaxMantissa = (CDoubleInteger(1) << ((aint)(EMantissaBits+1))) - 1;

			if ((ToShift > 0) && (_Mantissa & CDoubleInteger(1) << (ToShift-1)) != 0)
			{
				++Mantissa;
				if (Mantissa > MaxMantissa)
				{
					Mantissa >>= 1;
					++Exponent;
					if (Exponent >= MaxExponent)
					{
						Exponent = MaxExponent;
						Mantissa = 0;
					}					
				}
			}

			f_SetSignBits(_Sign);
			if (Exponent == 0 && Mantissa == CInteger(0))
				f_SetExponentBits(0); // Set to 0.0
			else
				f_SetExponent(Exponent);
			f_SetMantissa(fg_Convert<CInteger>(Mantissa));
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS bint TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_IsNaN() const
		{
			return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) && f_GetMantissaBits() != 0;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS bint TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_IsQNaN() const
		{
			return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) && f_GetMantissaBits() != 0 && (f_GetMantissaBits() & (CInteger(1) << (aint)(EMantissaBits - 1))) != 0;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS bint TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_IsSNaN() const
		{
			return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) && f_GetMantissaBits() != 0 && ((f_GetMantissaBits() & (CInteger(1) << (aint)(EMantissaBits - 1))) == 0);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS bint TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_IsInfinity() const
		{
			return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) && f_GetMantissaBits() == 0;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS bint TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_IsInvalid() const
		{
			return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS bint TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_IsDenormalized() const
		{
			return f_GetExponentBits() == 0 && f_GetMantissaBits() != 0;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_Inf() -> TCFloat
		{
			TCFloat Temp;
			Temp.f_SetSignBits(0);
			Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
			Temp.f_SetMantissaBits(0);
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_NegInf() -> TCFloat
		{
			TCFloat Temp;
			Temp.f_SetSignBits(1);
			Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
			Temp.f_SetMantissaBits(0);
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_QNan() -> TCFloat
		{
			TCFloat Temp;
			Temp.f_SetSignBits(0);
			Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
			Temp.f_SetMantissaBits((CInteger(1) << (aint)(EMantissaBits - 1)) | 1);
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_SNan() -> TCFloat
		{
			TCFloat Temp;
			Temp.f_SetSignBits(0);
			Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
			Temp.f_SetMantissaBits(1);
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_NegQNan() -> TCFloat
		{
			TCFloat Temp;
			Temp.f_SetSignBits(1);
			Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
			Temp.f_SetMantissaBits((CInteger(1) << (aint)(EMantissaBits - 1)) | 1);
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInline auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fs_NegSNan() -> TCFloat
		{
			TCFloat Temp;
			Temp.f_SetSignBits(1);
			Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
			Temp.f_SetMantissaBits(1);
			return Temp;
		}


		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS void *TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetData()
		{
			return &m_Data;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS const void *TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetData() const
		{
			return &m_Data;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetStorage() -> CUnsignedInteger &
		{
			return m_Data;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_GetStorage() const -> CUnsignedInteger const &
		{
			return m_Data;
		}

		// Do nothing in default constructor
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::TCFloat()
		{
#ifdef DMibDebuggerHelpers
			(void)&CHelper::fs_GetAsDouble;
			(void)&ms_pHelper;
#endif
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ToInt() const -> CInteger
		{
			aint Exp = fg_Convert<aint>(f_GetExponent()) - EMantissaBits;
			
			CInteger Ret;
			if (Exp >= 0)
				Ret = f_GetMantissa() << Exp;
			else
				Ret = f_GetMantissa() >> (-Exp);

			if (f_GetSignBits() != 0)
				return -Ret;
			else
				return Ret;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ToUnsignedInt() const -> CUnsignedInteger
		{
			aint Exp = fg_Convert<aint>(f_GetExponent()) - EMantissaBits;
			
			if (Exp >= 0)
				return fg_Convert<CUnsignedInteger>(f_GetMantissa()) << Exp;
			else
				return fg_Convert<CUnsignedInteger>(f_GetMantissa()) >> (-Exp);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ToIntRound() const -> CInteger
		{
			if (*this < fs_0())
				return (*this - fs_0_5()).f_ToInt();
			else
				return (*this + fs_0_5()).f_ToInt();
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ToUnsignedIntRound() const -> CUnsignedInteger
		{
			if (*this < fs_0())
				return (*this - fs_0_5()).f_ToUnsignedInt();
			else
				return (*this + fs_0_5()).f_ToUnsignedInt();
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ToIntRoundTowardZero() const -> CInteger
		{
			return (*this + fs_0_5()).f_ToInt();
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ToUnsignedIntRoundTowardZero() const -> CUnsignedInteger
		{
			return (*this + fs_0_5()).f_ToUnsignedInt();
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Implicit Float
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS t_CImplicitFloat &TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Get()
		{
			return *((t_CImplicitFloat *)&m_Data);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS t_CImplicitFloat const &TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Get() const
		{
			return *((t_CImplicitFloat const *)&m_Data);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::TCFloat(const t_CImplicitFloat &_Value)
		{
			((t_CImplicitFloat &)m_Data) = _Value;
#ifdef DMibDebuggerHelpers
			(void)&CHelper::fs_GetAsDouble;
			(void)&ms_pHelper;
#endif
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator = (const t_CImplicitFloat &_Value) -> TCFloat &
		{
			((t_CImplicitFloat &)m_Data) = _Value;
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by value operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator + (const TCFloat &_Value) const -> TCFloat
		{
			TCFloat Temp = *this;
			Temp += _Value;
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator - (const TCFloat &_Value) const -> TCFloat
		{
			TCFloat Temp = *this;
			Temp -= _Value;
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator * (const TCFloat &_Value) const -> TCFloat
		{
			TCFloat Temp = *this;
			Temp *= _Value;
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator / (const TCFloat &_Value) const -> TCFloat
		{
			TCFloat Temp = *this;
			Temp /= _Value;
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator - () const -> TCFloat
		{
			TCFloat Temp = *this;
			Temp.f_SetSignBits(!Temp.f_GetSignBits());
			return Temp;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator + () const -> TCFloat
		{
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by reference operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator += (const TCFloat &_Value) -> TCFloat &
		{
			/*CInternalFloat Temp = *this;

			Temp.Add(CInternalFloat(_Value));
			f_SetAllRound(Temp.m_Sign, Temp.m_Exponent - 1, Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return *this;*/

			CInteger Sign0 = f_GetSignBits();
			CInteger Sign1 = _Value.f_GetSignBits();
			CInteger Exponent0 = f_GetExponent();
			CInteger Exponent1 = _Value.f_GetExponent();
			CInteger MantissaGet0;
			CInteger MantissaGet1;
			f_GetNormalized(Exponent0, MantissaGet0);
			_Value.f_GetNormalized(Exponent1, MantissaGet1);
			CDoubleInteger Mantissa0 = CDoubleInteger(MantissaGet0) << 2;
			CDoubleInteger Mantissa1 = CDoubleInteger(MantissaGet1) << 2;

			static const CInteger ExponentBias = (CInteger(1) << (aint)(EExponentBits - 1)) - CInteger(1);
			static const CInteger MinExponent = CInteger(1) - ExponentBias;

			if (Exponent0 > Exponent1)
			{
				aint Diff = fg_Convert<aint>(Exponent0 - Exponent1);
				CDoubleInteger NewMantissa;
				if (Diff > aint(EMantissaBits + 1))
				{
					if (Sign0!=0)
						NewMantissa = -Mantissa0;
					else
						NewMantissa = Mantissa0;
				}
				else
				{
					if (Sign0!=0)
						NewMantissa = -Mantissa0;
					else
						NewMantissa = Mantissa0;
			
					if (Sign1!=0)
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
					Exponent0 = MinExponent;
				else
				{
					while (Exponent0 > MinExponent && NewMantissa < (CDoubleInteger(1) << (aint)(EMantissaBits+2)))
					{
						NewMantissa <<= 1;
						--Exponent0;
					}
				}
				f_SetAllRound(Sign0, Exponent0, NewMantissa, 2);
			}
			else 
			{
				aint Diff = fg_Convert<aint>(Exponent1 - Exponent0);
				CDoubleInteger NewMantissa;
				if (Diff > aint(EMantissaBits + 1))
				{
					if (Sign1!=0)
						NewMantissa = -Mantissa1;
					else
						NewMantissa = Mantissa1;
				}
				else
				{
					if (Sign1!=0)
						NewMantissa = -Mantissa1;
					else
						NewMantissa = Mantissa1;
			
					if (Sign0!=0)
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
					while (Exponent1 > MinExponent && NewMantissa < (CDoubleInteger(1) << (aint)(EMantissaBits+2)))
					{
						NewMantissa <<= 1;
						--Exponent1;
					}
				}

				f_SetAllRound(Sign0, Exponent1, NewMantissa, 2);
			}
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator -= (const TCFloat &_Value) -> TCFloat &
		{
			/*CInternalFloat Temp = *this;

			Temp.Sub(CInternalFloat(_Value));
			f_SetAllRound(Temp.m_Sign, Temp.m_Exponent - 1, Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return *this;
*/
			
			TCFloat Temp = _Value;
			Temp.f_SetSignBits(!Temp.f_GetSignBits());
			*this += Temp;
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator /= (const TCFloat &_Value) -> TCFloat &
		{/*
			CInternalFloat Temp = *this;

			Temp.Div(CInternalFloat(_Value));
			f_SetAllRound(Temp.m_Sign, Temp.m_Exponent - 1, Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return *this*/

			CInteger Sign = f_GetSignBits() ^ _Value.f_GetSignBits();
			
			CInteger Exponent0; 
			CInteger Exponent1; 
			CInteger MantissaGet0; 
			CInteger MantissaGet1; 
			f_GetNormalized(Exponent0, MantissaGet0);
			_Value.f_GetNormalized(Exponent1, MantissaGet1);

			CInteger Exponent = Exponent0 - Exponent1;
			
			CDoubleInteger Mantissa0 = MantissaGet0;
			Mantissa0 <<= (aint)(EStorageBits);
			CDoubleInteger Mantissa1 = MantissaGet1;
			CDoubleInteger NewMantissa = (Mantissa0 / Mantissa1);
			f_SetAllRound(Sign, Exponent - 2, NewMantissa, (aint)(EStorageBits - EMantissaBits - 2));

			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator *= (const TCFloat &_Value) -> TCFloat &
		{
			CInteger Sign = f_GetSignBits() ^ _Value.f_GetSignBits();
			CInteger Exponent0;
			CInteger Exponent1;
			CInteger MantissaGet0;
			CInteger MantissaGet1;
			f_GetNormalized(Exponent0, MantissaGet0);
			_Value.f_GetNormalized(Exponent1, MantissaGet1);
			CDoubleInteger Mantissa0 = MantissaGet0;
			CDoubleInteger Mantissa1 = MantissaGet1;
			CInteger Exponent = Exponent0 + Exponent1;
			CDoubleInteger NewMantissa = Mantissa0 * Mantissa1;
			if (NewMantissa == 0)
				Exponent = 0;
			f_SetAllRound(Sign, Exponent, NewMantissa, EMantissaBits);
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator ++ () -> TCFloat &
		{
			*this = *this + fs_1();
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator -- () -> TCFloat &
		{
			*this = *this - fs_1();
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Postfix operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator ++ (int) -> TCFloat
		{
			TCFloat Ret = *this;
			++(*this);
			return Ret;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator -- (int) -> TCFloat
		{
			TCFloat Ret = *this;
			--(*this);
			return Ret;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Trigomethric
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Sin() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Cos() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Tan() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_SinH() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_CosH() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_TanH() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ArcSin() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ArcCos() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ArcTan() const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ArcTan(const TCFloat &_Source) const -> TCFloat
		{
			DMibPDebugBreak; // Not implemented
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Logarithm and exponent
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_ExpN() const -> TCFloat
		{
			CInternalFloat Temp = *this;
			Temp.f_ExpN();
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Ret;
		}            
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_LogN() const -> TCFloat
		{
			CInternalFloat Temp = *this;
			Temp.f_LogN();
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Ret;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Exp10() const -> TCFloat
		{
			CInternalFloat Temp = *this;
			Temp.f_Exp10();
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Ret;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Log10() const -> TCFloat
		{
			CInternalFloat Temp = *this;
			Temp.f_Log10();
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Ret;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Exp2() const -> TCFloat
		{
			CInternalFloat Temp = *this;
			Temp.f_Exp2();
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Ret;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Log2() const -> TCFloat
		{
			CInternalFloat Temp = *this;
			Temp.f_Log2();
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Ret;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Exp(const TCFloat & _Base) const -> TCFloat
		{
			CInternalFloat Temp = *this;
			CInternalFloat TempLog = _Base;
			TempLog.f_Log2();
			Temp.Mul(TempLog);
			Temp.f_Exp2();
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return *this;
		}
		
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Log(const TCFloat & _Base) const -> TCFloat
		{
			CInternalFloat Temp = *this;
			CInternalFloat TempLog = _Base;
			TempLog.f_Log2();
			Temp.f_Exp2();
			Temp.Mul(TempLog);
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return *this;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Power
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Sqrt() const -> TCFloat
		{
			if (f_GetSignBits() != 0)
			{
				return fs_NegQNan();
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
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Ret;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Sqr() const -> TCFloat
		{
			return (*this) * (*this);
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Pow(const TCFloat &_Power) const -> TCFloat  
		{
			CInternalFloat Temp = *this;
			Temp.f_Log2();
			Temp.Mul(_Power);
			Temp.f_Exp2();
			TCFloat Ret;
			Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			return Ret;
		}

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Integer functions
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Floor() const -> TCFloat
		{
			TCFloat Temp = *this;
			CInteger Exponent = f_GetExponent();
			if (Exponent > CInteger(EMantissaBits + 1))
			{
				// No decimals exists
				return Temp;
			}

			if (Temp < fs_0())
			{
				if (f_GetExponent() < 0)
				{
					// Less than 0
					return -fs_1();
				}

				TCFloat TempMax;
				TempMax.f_SetMantissa((fg_Convert<CInteger>(1) << EMantissaBits) - fg_Convert<CInteger>(1));
				TempMax.f_SetSign(0);
				TempMax.f_SetExponent(-1);

				CInteger TempInt = (Temp - TempMax).f_ToInt();
				return fs_FromInt(TempInt);
			}
			else
			{
				if (f_GetExponent() < 0)
				{
					// Less than 0
					return fs_0();
				}
				CInteger TempInt = Temp.f_ToInt();
				return fs_FromInt(TempInt);
			}
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Fraction() const -> TCFloat
		{
			return *this - f_Floor();
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Ceil() const -> TCFloat
		{
			TCFloat Temp = *this;
			CInteger Exponent = f_GetExponent();
			if (Exponent > CInteger(EMantissaBits + 1))
			{
				// No decimals exists
				return Temp;
			}

			if (Temp < fs_0())
			{
				if (f_GetExponent() < 0)
				{
					// Less than 0
					return fs_0();
				}
				CInteger TempInt = Temp.f_ToInt();
				return fs_FromInt(TempInt);
			}
			else
			{
				if (f_GetExponent() < 0)
				{
					// Less than 0
					return fs_1();
				}
				TCFloat TempMax;
				TempMax.f_SetMantissa((fg_Convert<CInteger>(1) << EMantissaBits) - fg_Convert<CInteger>(1));
				TempMax.f_SetSign(0);
				TempMax.f_SetExponent(-1);

				CInteger TempInt = (Temp + TempMax).f_ToInt();
				return fs_FromInt(TempInt);
			}
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Abs() const -> TCFloat
		{
			TCFloat Temp;
			Temp.f_SetSignBits(0); // Remove sign
			return Temp;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Mod(const TCFloat &_Modulu) const -> TCFloat
		{
			DMibFastCheck(0); // Not implemented
			return *this;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		bool TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator == (const TCFloat &_Value) const
		{
			if (f_IsNaN() || _Value.f_IsNaN())
				return false;
			return m_Data == _Value.m_Data;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		bool TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator < (const TCFloat &_Value) const
		{
			if (f_IsNaN() || _Value.f_IsNaN())
				return false;
			if (f_GetSign() < _Value.f_GetSign())
				return true;
			else if (f_GetSign() > _Value.f_GetSign())
				return false;
			
			if (f_GetSign() > CInteger(0))
			{
				if (f_GetExponent() < _Value.f_GetExponent())
					return true;
				else if (f_GetExponent() > _Value.f_GetExponent())
					return false;
					
				if (f_GetMantissa() < _Value.f_GetMantissa())
					return true;
			}
			else
			{
				if (f_GetExponent() > _Value.f_GetExponent())
					return true;
				else if (f_GetExponent() < _Value.f_GetExponent())
					return false;
				if (f_GetMantissa() > _Value.f_GetMantissa())
					return true;
			}
			return false;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator bool() const
		{
			return !(*this == fs_0());
		}
	}
}
