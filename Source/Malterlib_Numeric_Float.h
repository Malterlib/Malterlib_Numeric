// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#ifndef DMibSafety_IncMalterlib_H
#	error "You have to include this file through <Mib/Core/Core>"
#endif

#include <Mib/Core/Core>

#include "../../Core/Source/Malterlib_Core_General.h"

#define DMibFloatInline 
#define DMibFloatInlineS

namespace NMib
{
	template <typename t_CType, aint _Power>
    class TCGetPowerTwoMinusOne
	{
	public:
		static const t_CType Number = (((t_CType)1) << (_Power - 1)) + ((((t_CType)1) << (_Power - 1)) - 1);
	};
	namespace NMath
	{
		class CNoImplicit
		{
		private:
			CNoImplicit()
			{
			}
			~CNoImplicit()
			{
			}
			
		};

		template <typename t_CFloat>
		class TCFloatFromNative
		{
		public:
//			typedef t_CFloat CType;
		};

		template <typename t_CFloat>
		class TCFloatConstants;

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat = CNoImplicit, bint t_bDummyOptimize = true, typename t_CIntegerStorage = typename NTraits::TCIntFromSizeLarger<(t_SignBits + t_ExponentBits + t_MantissaBits + 7)/8>::CType>
		class TCFloat
		{
			template <typename t_CFloat>
			friend class TCFloatConstants;
			typedef typename NTraits::TCLargerType<t_CIntegerStorage>::CType CDoubleIntegerRaw;
		public:
			typedef t_CIntegerStorage CInteger;
			typedef typename TCChooseType<sizeof(CDoubleIntegerRaw) >= 8, CDoubleIntegerRaw, typename NTraits::TCIntFromSizeLarger<8>::CType>::CType CDoubleInteger;
			typedef typename NTraits::TCUnsigned<t_CIntegerStorage>::CType CUnsignedInteger;
			typedef typename NTraits::TCUnsigned<CDoubleInteger>::CType CDoubleUnsignedInteger;
			typedef t_CImplicitFloat CImplicitFloat;
			
			enum 
			{
				EStorageBits = sizeof(CInteger) * 8,				
				ESignBits = t_SignBits,
				EExponentBits = t_ExponentBits,
				EMantissaBits = t_MantissaBits,
				EUnusedBits = EStorageBits - (ESignBits + EExponentBits + EMantissaBits),
				ESignBitPos = EStorageBits - (EUnusedBits + ESignBits),
				EExponentBitPos = EStorageBits - (EUnusedBits + ESignBits + EExponentBits),
				EMantissaBitPos = 0,
			};

			static_assert(constenum(EUnusedBits) >= 0, "");
			static_assert(sizeof(CDoubleInteger) > sizeof(CInteger), "");

		protected:
			// Data stored in granularity of t_CStorageClass
			CUnsignedInteger m_Data;
            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Constants
			||______________________________________________________________________________________________||
			\************************************************************************************************/

#ifdef DMibDebuggerHelpers
			struct CHelper
			{
				assure_used static pfp64 fs_GetAsDouble(void *_pData)
				{
					TCFloat *pThis = (TCFloat *)_pData;
					
					return NMib::NMath::TCFloat <1, 11, 52, pfp64>(*pThis).f_Get();
				}
			};
			static CHelper *ms_pHelper;
#endif
			void fp_Set_0()
			{
				m_Data = 0;
			}

			void fp_Set_0_5()
			{
				m_Data = 0;
				f_SetExponent(-1);
				f_SetMantissaBits(0);
			}

			void fp_Set_1()
			{
				m_Data = 0;
				f_SetExponent(0);
			}

			void fp_Set_2()
			{
				m_Data = 0;
				f_SetExponent(1);
				f_SetMantissaBits(0);
			}

			void fp_Set_E()
			{
				CInternalFloat Temp = CInternalFloat::fs_E();
				f_SetAllRound(Temp.m_Sign, Temp.m_Exponent - 1, CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}


			void fp_Set_Pi()
			{
				CInternalFloat Temp = CInternalFloat::fs_Pi();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_Euler()
			{
				CInternalFloat Temp = CInternalFloat::fs_Euler();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_Sqrt2()
			{
				CInternalFloat Temp = CInternalFloat::fs_Sqrt2();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_GoldenRatio()
			{
				CInternalFloat Temp = CInternalFloat::fs_GoldenRatio();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_Log2_10()
			{
				CInternalFloat Temp = CInternalFloat::fs_Log2_10();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_Log10_2()
			{
				CInternalFloat Temp = CInternalFloat::fs_Log10_2();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_LogE_10()
			{
				CInternalFloat Temp = CInternalFloat::fs_LogE_10();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_Log10_E()
			{
				CInternalFloat Temp = CInternalFloat::fs_Log10_E();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_Log2_E()
			{
				CInternalFloat Temp = CInternalFloat::fs_Log2_E();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_LogE_2()
			{
				CInternalFloat Temp = CInternalFloat::fs_LogE_2();
				f_SetAllRound(Temp.m_Sign, CInteger(Temp.m_Exponent - 1), CDoubleInteger(Temp.m_Mantissa), CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
			}

			void fp_Set_Inf()
			{
				f_SetSignBits(0);
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
				f_SetMantissaBits(0);
			}

			void fp_Set_NegInf()
			{
				f_SetSignBits(1);
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
				f_SetMantissaBits(0);
			}

			void fp_Set_QNan()
			{
				f_SetSignBits(0);
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
				f_SetMantissaBits((CUnsignedInteger(1) << (aint)(EMantissaBits - 1)) | 1);
			}

			void fp_Set_SNan()
			{
				f_SetSignBits(0);
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
				f_SetMantissaBits(1);
			}

			void fp_Set_NegQNan()
			{
				f_SetSignBits(1);
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
				f_SetMantissaBits((CUnsignedInteger(1) << (aint)(EMantissaBits - 1)) | 1);
			}

			void fp_Set_NegSNan()
			{
				f_SetSignBits(1);
				f_SetExponentBits(fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits));
				f_SetMantissaBits(1);
			}
		public:
			
			static DMibFloatInline TCFloat fs_LimitMin()
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
			}
			
			static DMibFloatInline TCFloat fs_LimitMax()
			{
				TCFloat Temp;
				Temp.f_SetMantissa((fg_Convert<CInteger>(1) << EMantissaBits) - fg_Convert<CInteger>(1));
				Temp.f_SetSign(0);
				Temp.f_SetExponent(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits-1));
				return Temp;
			}
			
			static DMibFloatInline TCFloat fs_0()
			{
				TCFloat Temp;
				Temp.fp_Set_0();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_0_5()
			{
				TCFloat Temp;
				Temp.fp_Set_0_5();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_1()
			{
				TCFloat Temp;
				Temp.fp_Set_1();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_2()
			{
				TCFloat Temp;
				Temp.fp_Set_2();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_E()
			{
				TCFloat Temp;
				Temp.fp_Set_E();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_Pi()
			{
				TCFloat Temp;
				Temp.fp_Set_Pi();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_Sqrt2()
			{
				TCFloat Temp;
				Temp.fp_Set_Sqrt2();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_Euler()
			{
				TCFloat Temp;
				Temp.fp_Set_Euler();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_GoldenRatio()
			{
				TCFloat Temp;
				Temp.fp_Set_GoldenRatio();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_Log10_2()
			{
				TCFloat Temp;
				Temp.fp_Set_Log10_2();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_Log2_10()
			{
				TCFloat Temp;
				Temp.fp_Set_Log2_10();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_Log10_E()
			{
				TCFloat Temp;
				Temp.fp_Set_Log10_E();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_LogE_10()
			{
				TCFloat Temp;
				Temp.fp_Set_LogE_10();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_Log2_E()
			{
				TCFloat Temp;
				Temp.fp_Set_Log2_E();
				return Temp;
			}

			static DMibFloatInline TCFloat fs_LogE_2()
			{
				TCFloat Temp;
				Temp.fp_Set_LogE_2();
				return Temp;
			}

			DMibFloatInlineS CInteger f_GetSignBits() const
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

			DMibFloatInlineS CInteger f_GetExponentBits() const
			{
				return (m_Data & (fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) << (aint)(EExponentBitPos))) >> (aint)(EExponentBitPos);
			}

			DMibFloatInlineS CInteger f_GetMantissaBits() const
			{
				return (m_Data & (fg_PowerOfTwoMinusOne<CInteger>(EMantissaBits) << (aint)(EMantissaBitPos))) >> (aint)(EMantissaBitPos);
			}

			DMibFloatInlineS CInteger f_GetSign() const
			{
				return CInteger(1) - (f_GetSignBits() << 1);
			}

			DMibFloatInlineS CInteger f_GetExponent() const
			{
				static CInteger ExponentBias = (CInteger(1) << (aint)(EExponentBits - 1)) - CInteger(1);
				CInteger ExponentBits = f_GetExponentBits();
				if (ExponentBits != 0)
					return ExponentBits - ExponentBias;	
				else
					return CInteger(1)-ExponentBias;
			}

			DMibFloatInlineS CInteger f_GetMantissa() const
			{
				if (f_GetExponentBits() == 0)
					return f_GetMantissaBits();
				else
					return (CInteger(1) << (aint)(EMantissaBits)) | f_GetMantissaBits();
			}

			DMibFloatInlineS CInteger f_GetDenormalizedMantissa() const
			{
				return f_GetMantissaBits();
			}

			DMibFloatInlineS void f_SetSignBits(const CUnsignedInteger &_Value)
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

			DMibFloatInlineS void f_SetExponentBits(const CUnsignedInteger &_Value)
			{
				const CUnsignedInteger And = fg_PowerOfTwoMinusOne<CUnsignedInteger>(EExponentBits);
				m_Data = (m_Data & ~(And << uaint(EExponentBitPos))) | ((_Value & And) << (aint)(EExponentBitPos));
			}

			DMibFloatInlineS void f_SetMantissaBits(const CUnsignedInteger &_Value)
			{
				const CUnsignedInteger And = fg_PowerOfTwoMinusOne<CUnsignedInteger>(EMantissaBits);
				m_Data = (m_Data & ~(And << uaint(EMantissaBitPos))) | ((_Value & And) << (aint)(EMantissaBitPos));

			}

			DMibFloatInlineS void f_SetSign(const CInteger &_Value)
			{
				f_SetSignBits((_Value + 1) >> 1);
			}

			DMibFloatInlineS void f_SetExponent(const CInteger &_Value)
			{
				static const CInteger ExponentBias = (CInteger(1) << (uaint(EExponentBits - 1))) - CInteger(1);
				f_SetExponentBits(_Value + ExponentBias);
			}

			DMibFloatInlineS void f_SetMantissa(const CInteger &_Value)
			{
				f_SetMantissaBits(_Value);
			}

			void f_SetAllRound(const CInteger &_Sign, const CInteger &_Exponent, const CDoubleInteger &_Mantissa, const CInteger &_AtleastExtraBits)
			{
				CInteger Exponent = _Exponent;
				aint ToShift = fg_Convert<aint>(_AtleastExtraBits);
				CDoubleInteger Mantissa = _Mantissa >> ToShift;
				while (Mantissa >= (CDoubleInteger(1) << ((aint)(EMantissaBits+1)) ))
				{
					++ToShift;
					++Exponent;
					Mantissa = _Mantissa >> ToShift;
				}
				const static CInteger ExponentBias = (CInteger(1) << (aint)(EExponentBits - 1)) - CInteger(1);
				const static CInteger MinExponent = CInteger(1)-ExponentBias;
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

				if ((ToShift > 0) && (_Mantissa & CDoubleInteger(1) << (ToShift-1)) != 0)
					++Mantissa;

				f_SetSignBits(_Sign);
				if (Mantissa == CInteger(0))
					f_SetExponentBits(0); // Set to 0.0
				else
					f_SetExponent(Exponent);
				f_SetMantissa(fg_Convert<CInteger>(Mantissa));
			}

			DMibFloatInlineS bint f_IsNaN() const
			{
				return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) && f_GetMantissaBits() != 0;
			}

			DMibFloatInlineS bint f_IsQNaN() const
			{
				return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) && f_GetMantissaBits() != 0 && (f_GetMantissaBits() & (CInteger(1) << (aint)(EMantissaBits - 1))) != 0;
			}

			DMibFloatInlineS bint f_IsSNaN() const
			{
				return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) && f_GetMantissaBits() != 0 && ((f_GetMantissaBits() & (CInteger(1) << (aint)(EMantissaBits - 1))) == 0);
			}

			DMibFloatInlineS bint f_IsInfinity() const
			{
				return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits) && f_GetMantissaBits() == 0;
			}

			DMibFloatInlineS bint f_IsInvalid() const
			{
				return f_GetExponentBits() == fg_PowerOfTwoMinusOne<CInteger>(EExponentBits);
			}

			DMibFloatInlineS bint f_IsDenormalized() const
			{
				return f_GetExponentBits() == 0 && f_GetMantissaBits() != 0;
			}

			static DMibFloatInline TCFloat fs_Inf()
			{
				TCFloat Temp;
				Temp.f_SetSignBits(0);
				Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
				Temp.f_SetMantissaBits(0);
				return Temp;
			}

			static DMibFloatInline TCFloat fs_NegInf()
			{
				TCFloat Temp;
				Temp.f_SetSignBits(1);
				Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
				Temp.f_SetMantissaBits(0);
				return Temp;
			}

			static DMibFloatInline TCFloat fs_QNan()
			{
				TCFloat Temp;
				Temp.f_SetSignBits(0);
				Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
				Temp.f_SetMantissaBits((CInteger(1) << (aint)(EMantissaBits - 1)) | 1);
				return Temp;
			}

			static DMibFloatInline TCFloat fs_SNan()
			{
				TCFloat Temp;
				Temp.f_SetSignBits(0);
				Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
				Temp.f_SetMantissaBits(1);
				return Temp;
			}

			static DMibFloatInline TCFloat fs_NegQNan()
			{
				TCFloat Temp;
				Temp.f_SetSignBits(1);
				Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
				Temp.f_SetMantissaBits((CInteger(1) << (aint)(EMantissaBits - 1)) | 1);
				return Temp;
			}

			static DMibFloatInline TCFloat fs_NegSNan()
			{
				TCFloat Temp;
				Temp.f_SetSignBits(1);
				Temp.f_SetExponentBits(fg_PowerOfTwoMinusOne<CInteger>(EExponentBits));
				Temp.f_SetMantissaBits(1);
				return Temp;
			}


			DMibFloatInlineS void * f_GetData()
			{
				return &m_Data;
			}

			DMibFloatInlineS const void * f_GetData() const
			{
				return &m_Data;
			}

			// Do nothing in default constructor
			DMibFloatInlineS TCFloat()
			{
#ifdef DMibDebuggerHelpers
				(void)&CHelper::fs_GetAsDouble;
				(void)&ms_pHelper;
#endif
			}

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			DMibFloatInlineS void f_AssignRoundUp(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue)
			{
				typedef TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> COtherFloat;
				COtherFloat Other = _SetValue;

				f_SetSignBits(fg_Convert<CInteger>(Other.f_GetSignBits()));

				static const CInteger ExponentMaxNeg = -((CInteger(1) << (aint)(EExponentBits - 1)) - CInteger(1));
				static const CInteger ExponentMax = fg_PowerOfTwoMinusOne<CInteger>(EExponentBits);

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

				if (uaint(COtherFloat::EMantissaBits) > uaint(EMantissaBits))
				{
					uaint nBits = (uaint(COtherFloat::EMantissaBits) - uaint(EMantissaBits));
					typename COtherFloat::CInteger Temp = Other.f_GetMantissaBits() + ((typename COtherFloat::CInteger(1) << nBits) - 1);
					typename COtherFloat::CInteger Largest = typename COtherFloat::CInteger(1) << uaint(COtherFloat::EMantissaBits);
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
					uaint nBits = (uaint(EMantissaBits) - uaint(COtherFloat::EMantissaBits));
					f_SetMantissaBits(fg_Convert<CInteger>(Other.f_GetMantissaBits()) << nBits);
				}

				*this *= EndMul;
			}

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			DMibFloatInlineS void f_Assign(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue)
			{
				typedef TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> COtherFloat;
				COtherFloat Other = _SetValue;

				f_SetSignBits(fg_Convert<CInteger>(Other.f_GetSignBits()));

				static const CInteger ExponentMaxNeg = -((CInteger(1) << (uaint(EExponentBits - 1))) - CInteger(1));
				static const CInteger ExponentMax = fg_PowerOfTwoMinusOne<CInteger>(EExponentBits);

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

				if (uaint(COtherFloat::EMantissaBits) > uaint(EMantissaBits))
				{
					uaint nBits = (uaint(COtherFloat::EMantissaBits) - uaint(EMantissaBits));
					typename COtherFloat::CInteger Temp = Other.f_GetMantissaBits() + ((typename COtherFloat::CInteger(1) << (nBits - 1)));
					typename COtherFloat::CInteger Largest = typename COtherFloat::CInteger(1) << uaint(COtherFloat::EMantissaBits);
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
					uaint nBits = (uaint(EMantissaBits) - uaint(COtherFloat::EMantissaBits));
					f_SetMantissaBits(fg_Convert<CInteger>(Other.f_GetMantissaBits()) << nBits);
				}

				*this *= EndMul;
			}

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			DMibFloatInlineS TCFloat & operator = (const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue)
			{
				f_Assign(_SetValue);
				return *this;
			}

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			DMibFloatInlineS TCFloat(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue)
			{		
				f_Assign(_SetValue);
#ifdef DMibDebuggerHelpers
				(void)&CHelper::fs_GetAsDouble;
				(void)&ms_pHelper;
#endif
			}

			DMibFloatInlineS CInteger f_ToInt() const
			{
				aint f_Exp = fg_Convert<aint>(f_GetExponent()) - EMantissaBits;
				
				CInteger Ret;
				if (f_Exp >= 0)
					Ret = f_GetMantissa() << f_Exp;
				else
					Ret = f_GetMantissa() >> (-f_Exp);

				if (f_GetSignBits() != 0)
					return -Ret;
				else
					return Ret;
			}
			
			DMibFloatInlineS CUnsignedInteger f_ToUnsignedInt() const
			{
				aint f_Exp = fg_Convert<aint>(f_GetExponent()) - EMantissaBits;
				
				if (f_Exp >= 0)
					return fg_Convert<CUnsignedInteger>(f_GetMantissa()) << f_Exp;
				else
					return fg_Convert<CUnsignedInteger>(f_GetMantissa()) >> (-f_Exp);
			}

			DMibFloatInlineS CInteger f_ToIntRound() const
			{
				if (*this < fs_0())
					return (*this - fs_0_5()).f_ToInt();
				else
					return (*this + fs_0_5()).f_ToInt();
			}

			DMibFloatInlineS CUnsignedInteger f_ToUnsignedIntRound() const
			{
				if (*this < fs_0())
					return (*this - fs_0_5()).f_ToUnsignedInt();
				else
					return (*this + fs_0_5()).f_ToUnsignedInt();
			}

			DMibFloatInlineS CInteger f_ToIntRoundTowardZero() const
			{
				return (*this + fs_0_5()).f_ToInt();
			}

			DMibFloatInlineS CUnsignedInteger f_ToUnsignedIntRoundTowardZero() const
			{
				return (*this + fs_0_5()).f_ToUnsignedInt();
			}


			template <typename t_CInteger>
			static TCFloat fs_FromInt(const t_CInteger &_Int)
			{
				TCFloat Ret;
				Ret.f_FromInt(_Int);
				return Ret;
			}
			
			template <typename t_CInteger>
			void f_FromInt(const t_CInteger &_Int)
			{
				aint IntegerBits = sizeof(_Int) * 8;
				CInteger Sign = 0;
				t_CInteger Int;
				if (_Int < 0)
				{
					Int = -_Int;
					Sign = 1;
				}
				else
				{
					Int = _Int;
				}

				if (IntegerBits > EMantissaBits && (Int > fg_Convert<t_CInteger>(CInteger(1) << (aint)(EMantissaBits))))
				{
					CInteger Exponent = fg_Convert<CInteger>(IntegerBits);
					CDoubleInteger Mantissa;
					Mantissa = fg_Convert<CDoubleInteger>((Int >> (IntegerBits - (aint)(EMantissaBits))));

					f_SetAllRound(Sign, Exponent, Mantissa, 0);
				}
				else if(Int == 0)
				{
					*this = fs_0();
				}
				else
				{
					CDoubleInteger Mantissa = fg_Convert<CDoubleInteger>(Int);

					CInteger Exponent = (aint)(EMantissaBits);
					while (Mantissa < (CDoubleInteger(1) << (aint)(EMantissaBits)))
					{
						Mantissa <<= 1;
						--Exponent;
					}

					f_SetAllRound(Sign, Exponent, Mantissa, 0);
				}
			}
			
            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Implicit Float
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			DMibFloatInlineS t_CImplicitFloat &f_Get()
			{
				return *((t_CImplicitFloat *)&m_Data);
			}

			DMibFloatInlineS t_CImplicitFloat const &f_Get() const
			{
				return *((t_CImplicitFloat const *)&m_Data);
			}

/*			DMibFloatInlineS operator t_CImplicitFloat &()
			{
				return (t_CImplicitFloat &)m_Data;
			}*/

			DMibFloatInlineS TCFloat(const t_CImplicitFloat &_Value)
			{
				((t_CImplicitFloat &)m_Data) = _Value;
#ifdef DMibDebuggerHelpers
				(void)&CHelper::fs_GetAsDouble;
				(void)&ms_pHelper;
#endif
			}

			DMibFloatInlineS TCFloat &operator = (const t_CImplicitFloat &_Value)
			{
				((t_CImplicitFloat &)m_Data) = _Value;
				return *this;
			}

			template <typename tf_CType>
			DMibFloatInlineS TCFloat(tf_CType _Value, typename TCEnableIf<NTraits::TCIsSame<tf_CType, bool>::mc_Value>::CType *_pDummy = nullptr)
			{
				*this = _Value ? fs_1() : fs_0();
#ifdef DMibDebuggerHelpers
				(void)&CHelper::fs_GetAsDouble;
				(void)&ms_pHelper;
#endif
			}

			template <typename tf_CType>
			DMibFloatInlineS typename TCEnableIf<NTraits::TCIsSame<tf_CType, bool>::mc_Value, TCFloat &>::CType operator = (tf_CType _Value)
			{
				*this = _Value ? fs_1() : fs_0();
				return *this;
			}

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Return by value operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat operator + (const TCFloat &_Value) const
			{
				TCFloat Temp = *this;
				Temp += _Value;
				return Temp;
			}
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator + (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).operator + (COperationType(_Value));
			}



			TCFloat operator - (const TCFloat &_Value) const
			{
				TCFloat Temp = *this;
				Temp -= _Value;
				return Temp;
			}
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator - (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).operator - (COperationType(_Value));
			}


			TCFloat operator * (const TCFloat &_Value) const
			{
				TCFloat Temp = *this;
				Temp *= _Value;
				return Temp;
			}
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator * (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).operator *(COperationType(_Value));
			}


			TCFloat operator / (const TCFloat &_Value) const
			{
				TCFloat Temp = *this;
				Temp /= _Value;
				return Temp;
			}
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator / (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).operator / (COperationType(_Value));
			}


			
			TCFloat operator - () const
			{
				TCFloat Temp = *this;
				Temp.f_SetSignBits(!Temp.f_GetSignBits());
				return Temp;
			}
			
			TCFloat operator + () const
			{
				return *this;
			}

			// Must do overloads to implicit float also
			/*
			DMibFloatInlineS TCFloat operator * (const t_CImplicitFloat &_Value) const
			{
				return operator *(TCFloat(_Value));
			}

			DMibFloatInlineS TCFloat operator + (const t_CImplicitFloat &_Value) const
			{
				return operator +(TCFloat(_Value));
			}

			DMibFloatInlineS TCFloat operator - (const t_CImplicitFloat &_Value) const
			{
				return operator -(TCFloat(_Value));
			}

			DMibFloatInlineS TCFloat operator / (const t_CImplicitFloat &_Value) const
			{
				return operator /(TCFloat(_Value));
			}*/

			// Internal float working with 8 extra bits of precission
			class CInternalFloat
			{
			public:
				typedef CDoubleUnsignedInteger CMantissa;
				typedef CDoubleInteger CSignedMantissa;
				typedef CDoubleInteger CExponent;
				CMantissa m_Mantissa;
				CExponent m_Exponent;
				CInteger m_Sign;

				CInternalFloat()
				{
					*this = fs_0();
				}

				enum
				{
					EInternalMantissaBits = sizeof(CMantissa)*4 - 1,
					EInternalExponentBits = sizeof(CExponent)*8 - 2
				};

				static CInternalFloat fs_LogE_2()
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

				static CInternalFloat fs_Log2_E()
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

				static CInternalFloat fs_LogE_10()
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

				static CInternalFloat fs_Log10_E()
				{
					static bint bInit = false;
					static CInternalFloat Temp = fs_1();
					{
						Temp.Div(fs_LogE_10());
						bInit = true;
					}
					return Temp;
				}

				static CInternalFloat fs_Log2_10()
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

				static CInternalFloat fs_Log10_2()
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

				static CInternalFloat fs_E()
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

				static CInternalFloat fs_Euler()
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
					CInternalFloat Temp5 = fs_0();
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

				static CInternalFloat fs_GoldenRatio()
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

				static CInternalFloat fs_Pi()
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

				static CInternalFloat fs_Sqrt2()
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

				CInternalFloat(const TCFloat &_Source)
				{
					m_Mantissa = _Source.f_GetMantissa();
					m_Mantissa <<= EInternalMantissaBits - EMantissaBits;
					m_Exponent = _Source.f_GetExponent();
					m_Sign = _Source.f_GetSignBits();
				}

				CInternalFloat &operator = (const TCFloat &_Source)
				{
					m_Mantissa = _Source.f_GetMantissa();
					m_Mantissa <<= EInternalMantissaBits - EMantissaBits;
					m_Exponent = _Source.f_GetExponent();
					m_Sign = _Source.f_GetSignBits();
					return *this;
				}

				bint f_AlmostEqual(const CInternalFloat &_Value, int _nBits)
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

				void f_SetAllRound(const CInteger &_Sign, const CExponent &_Exponent, const CMantissa &_Mantissa, const CInteger &_AtleastExtraBits)
				{
					CExponent Exponent = _Exponent;
					aint ToShift = fg_Convert<aint>(_AtleastExtraBits);
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

				void Mul(const CInternalFloat &_Value)
				{
					CInteger Sign = m_Sign ^ _Value.m_Sign;
					CExponent Exponent = m_Exponent + _Value.m_Exponent;
					CMantissa Mantissa0 = m_Mantissa;
					CMantissa Mantissa1 = _Value.m_Mantissa;
					CMantissa NewMantissa = Mantissa0 * Mantissa1;
					f_SetAllRound(Sign, Exponent, NewMantissa, (aint)(EInternalMantissaBits));
				}

				void Div(const CInternalFloat &_Value)
				{
					CInteger Sign = m_Sign ^ _Value.m_Sign;
					CExponent Exponent = m_Exponent - _Value.m_Exponent;

					CMantissa Mantissa0 = m_Mantissa;
					Mantissa0 <<= EInternalMantissaBits+1;
					CMantissa Mantissa1 = _Value.m_Mantissa;
					CMantissa NewMantissa = (Mantissa0 / Mantissa1);
					f_SetAllRound(Sign, Exponent-1, NewMantissa, 0);

				}

				void Add(const CInternalFloat &_Value)
				{
					CInteger Sign0 = m_Sign;
					CInteger Sign1 = _Value.m_Sign;
					CExponent Exponent0 = m_Exponent;
					CExponent Exponent1 = _Value.m_Exponent;
					CSignedMantissa Mantissa0 = m_Mantissa;
					CSignedMantissa Mantissa1 = _Value.m_Mantissa;

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

				void Sub(const CInternalFloat &_Value)
				{
					CInternalFloat Temp = _Value;
					Temp.m_Sign = !Temp.m_Sign;
					Add(Temp);
				}

				void ATan()
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
					while ((Term.m_Mantissa != 0 || Term.m_Exponent != MinExponent)
						&& !Result.f_AlmostEqual(LastResult, 0))
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

				void Remainder()
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

				CSignedMantissa f_ToInt()
				{
					aint f_Exp = fg_Convert<aint>(m_Exponent) - EInternalMantissaBits;
					CSignedMantissa Sign = CSignedMantissa(1) - (m_Sign << 1);
					
					if (f_Exp >= 0)
						return (m_Mantissa << f_Exp) * Sign;
					else
						return (m_Mantissa >> (-f_Exp) ) * Sign;
				}

				void f_FromInt(const CSignedMantissa &_Int)
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
				
				static CInternalFloat fs_FromInt(const CSignedMantissa &_Other)
				{
					CInternalFloat Ret;
					Ret.f_FromInt(_Other);
					return Ret;
				}
				
				void f_ExpN()
				{
					{
						CInternalFloat Temp = *this;
						Temp.Mul(fs_Log2_E());
						Temp.f_Exp2();
						*this = Temp;
					}
					return;
				}

				void f_Exp10()
				{
					{
						CInternalFloat Temp = *this;
						Temp.Mul(fs_Log2_10());
						Temp.f_Exp2();
						*this = Temp;
					}
					return;
				}

				TCFloat GetFloat()
				{
					TCFloat Temp;
					Temp.f_SetAllRound(m_Sign, m_Exponent - 1, m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
					return Temp;
				}

				void LogNFull()
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

				void f_LogN()
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

				void f_Log10()
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

				void f_Log2()
				{
					CExponent Exponent = m_Exponent;
					m_Exponent = 0;
					LogNFull();
					Mul(fs_Log2_E());
					CInternalFloat Temp;
					Temp.f_FromInt(Exponent);
					Add(Temp);
				}

				void f_Exp2()
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

				void f_Sqrt()
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

			};

			

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Return by reference operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat &operator += (const TCFloat &_Value)
			{
				/*CInternalFloat Temp = *this;

				Temp.Add(CInternalFloat(_Value));
				f_SetAllRound(Temp.m_Sign, Temp.m_Exponent - 1, Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return *this;*/

				
				CInteger Sign0 = f_GetSignBits();
				CInteger Sign1 = _Value.f_GetSignBits();
				CInteger Exponent0 = f_GetExponent();
				CInteger Exponent1 = _Value.f_GetExponent();
				CDoubleInteger Mantissa0 = f_GetMantissa() << 2;
				CDoubleInteger Mantissa1 = _Value.f_GetMantissa() << 2;

//				if (Sign0 != 0)
//					Mantissa0 = -Mantissa0;
//				if (Sign1 != 0)
//					Mantissa1 = -Mantissa1;

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

			TCFloat &operator -= (const TCFloat &_Value)
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

			TCFloat &operator /= (const TCFloat &_Value)
			{/*
				CInternalFloat Temp = *this;

				Temp.Div(CInternalFloat(_Value));
				f_SetAllRound(Temp.m_Sign, Temp.m_Exponent - 1, Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return *this*/

				
				CInteger Sign = f_GetSignBits() ^ _Value.f_GetSignBits();
				CInteger Exponent = f_GetExponent() - _Value.f_GetExponent();

				CDoubleInteger Mantissa0 = f_GetMantissa();
				Mantissa0 <<= (aint)(EStorageBits);
				CDoubleInteger Mantissa1 = _Value.f_GetMantissa();
				CDoubleInteger NewMantissa = (Mantissa0 / Mantissa1);
				f_SetAllRound(Sign, Exponent - 2, NewMantissa, (aint)(EStorageBits - EMantissaBits - 2));

				return *this;
			}
            
			TCFloat &operator *= (const TCFloat &_Value)
			{
				CInteger Sign = f_GetSignBits() ^ _Value.f_GetSignBits();
				CInteger Exponent = f_GetExponent() + _Value.f_GetExponent();
				CDoubleInteger Mantissa0 = f_GetMantissa();
				CDoubleInteger Mantissa1 = _Value.f_GetMantissa();
				CDoubleInteger NewMantissa = Mantissa0 * Mantissa1;
				f_SetAllRound(Sign, Exponent, NewMantissa, (aint)(EMantissaBits));
				return *this;
			}

			TCFloat &operator ++ ()
			{
				*this = *this + fs_1();
				return *this;
			}

			TCFloat &operator -- ()
			{
				*this = *this - fs_1();
				return *this;
			}

			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Postfix operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat operator ++ (int)
			{
				TCFloat Ret = *this;
				++(*this);
				return Ret;
			}

			TCFloat operator -- (int)
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

			TCFloat f_Sin() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}
			TCFloat f_Cos() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}
			TCFloat f_Tan() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}

			TCFloat f_SinH() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}
			TCFloat f_CosH() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}
			TCFloat f_TanH() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}

			TCFloat f_ArcSin() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}
			TCFloat f_ArcCos() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}
			TCFloat f_ArcTan() const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}
			TCFloat f_ArcTan(const TCFloat &_Source) const
			{
				DMibPDebugBreak; // Not implemented
				return *this;
			}
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_ArcTan(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Source) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).f_ArcTan(COperationType(_Source));
			}


			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Logarithm and exponent
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat f_ExpN() const
			{
				CInternalFloat Temp = *this;
				Temp.f_ExpN();
				TCFloat Ret;
				Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return Ret;
			}            
			TCFloat f_LogN() const
			{
				CInternalFloat Temp = *this;
				Temp.f_LogN();
				TCFloat Ret;
				Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return Ret;
			}

			TCFloat f_Exp10() const
			{
				CInternalFloat Temp = *this;
				Temp.f_Exp10();
				TCFloat Ret;
				Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return Ret;
			}            
			TCFloat f_Log10() const
			{
				CInternalFloat Temp = *this;
				Temp.f_Log10();
				TCFloat Ret;
				Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return Ret;
			}

			TCFloat f_Exp2() const
			{
				CInternalFloat Temp = *this;
				Temp.f_Exp2();
				TCFloat Ret;
				Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return Ret;
			}            
			TCFloat f_Log2() const
			{
				CInternalFloat Temp = *this;
				Temp.f_Log2();
				TCFloat Ret;
				Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return Ret;
			}

			TCFloat f_Exp(const TCFloat & _Base) const
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
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Exp(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).f_Exp(COperationType(_Base));
			}

			TCFloat f_Log(const TCFloat & _Base) const
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
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Log(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).f_Log(COperationType(_Base));
			}

			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Power
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat f_Sqrt() const
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

			TCFloat f_Sqr() const
			{
				return (*this) * (*this);
			}

			TCFloat f_Pow(const TCFloat &_Power) const
			{
				CInternalFloat Temp = *this;
				Temp.f_Log2();
				Temp.Mul(_Power);
				Temp.f_Exp2();
				TCFloat Ret;
				Ret.f_SetAllRound(Temp.m_Sign, fg_Convert<CInteger>(Temp.m_Exponent - 1), Temp.m_Mantissa, CInternalFloat::EInternalMantissaBits - EMantissaBits - 1);
				return Ret;
			}

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Pow(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Power) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).f_Pow(COperationType(_Power));
			}



			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Integer functions
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat f_Floor() const
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

			TCFloat f_Fraction() const
			{
				return *this - f_Floor();
			}

			TCFloat f_Ceil() const 
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

			TCFloat f_Abs() const
			{
				TCFloat Temp;
				Temp.f_SetSignBits(0); // Remove sign
				return Temp;
			}

			TCFloat f_Mod(const TCFloat &_Modulu) const
			{
				DMibFastCheck(0); // Not implemented
				return *this;
			}

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Mod(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Modulu) const
			{
				typedef typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType COperationType;

				return COperationType(*this).f_Mod(COperationType(_Modulu));
			}

			bool operator == (const TCFloat &_Value) const
			{
				return m_Data == _Value.m_Data;
			}

			bool operator < (const TCFloat &_Value) const
			{
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

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			bool operator < (TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right)
			{
				typedef TCFloat CLeftFloat;
				typedef TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> CRightFloat;

				if (f_GetSign() < _Right.f_GetSign())
					return true;
				else if (f_GetSign() > _Right.f_GetSign())
					return false;
				
				if (f_GetSign() > CLeftFloat::CInteger(0))
				{
					if (f_GetExponent() < _Right.f_GetExponent())
						return true;
					else if (f_GetExponent() > _Right.f_GetExponent())
						return false;
						
					if (uaint(CLeftFloat::EMantissaBits) > uaint(CRightFloat::EMantissaBits))
					{
						uaint nBits = (uaint(CLeftFloat::EMantissaBits) - uaint(CRightFloat::EMantissaBits));
						typename CLeftFloat::CInteger LeftMantissa = f_GetMantissa();
						typename CLeftFloat::CInteger RightMantissa = _Right.f_GetMantissa() << nBits;

						if (LeftMantissa < RightMantissa)
							return true;
					}
					else
					{
						uaint nBits = (uaint(CRightFloat::EMantissaBits) - uaint(CLeftFloat::EMantissaBits));
						typename CRightFloat::CInteger LeftMantissa = f_GetMantissa() << nBits;
						typename CRightFloat::CInteger RightMantissa = _Right.f_GetMantissa();

						if (LeftMantissa < RightMantissa)
							return true;
					}
				}
				else
				{
					if (f_GetExponent() > _Right.f_GetExponent())
						return true;
					else if (f_GetExponent() < _Right.f_GetExponent())
						return false;
					if (uaint(CLeftFloat::EMantissaBits) > uaint(CRightFloat::EMantissaBits))
					{
						uaint nBits = (uaint(CLeftFloat::EMantissaBits) - uaint(CRightFloat::EMantissaBits));
						typename CLeftFloat::CInteger LeftMantissa = f_GetMantissa();
						typename CLeftFloat::CInteger RightMantissa = _Right.f_GetMantissa() << nBits;

						if (LeftMantissa > RightMantissa)
							return true;
					}
					else
					{
						uaint nBits = (uaint(CRightFloat::EMantissaBits) - uaint(CLeftFloat::EMantissaBits));
						typename CRightFloat::CInteger LeftMantissa = f_GetMantissa() << nBits;
						typename CRightFloat::CInteger RightMantissa = _Right.f_GetMantissa();

						if (LeftMantissa > RightMantissa)
							return true;
					}
				}
				return false;
			}

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bint t_bDummyOptimize2, typename t_CIntegerStorage2>
			bool operator == (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right)
			{
				typedef TCFloat CLeftFloat;
				typedef NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> CRightFloat;

				if (!(f_GetSign() == _Right.f_GetSign()))
					return false;

				if (!(f_GetExponent() == _Right.f_GetExponent()))
					return false;
					
				if (uaint(CLeftFloat::EMantissaBits) > uaint(CRightFloat::EMantissaBits))
				{
					uaint nBits = (uaint(CLeftFloat::EMantissaBits) - uaint(CRightFloat::EMantissaBits));
					typename CLeftFloat::CInteger LeftMantissa = f_GetMantissa();
					typename CLeftFloat::CInteger RightMantissa = _Right.f_GetMantissa() << nBits;

					if (!(LeftMantissa == RightMantissa))
						return false;
				}
				else
				{
					uaint nBits = (uaint(CRightFloat::EMantissaBits) - uaint(CLeftFloat::EMantissaBits));
					typename CRightFloat::CInteger LeftMantissa = f_GetMantissa() << nBits;
					typename CRightFloat::CInteger RightMantissa = _Right.f_GetMantissa();

					if (!(LeftMantissa == RightMantissa))
						return false;
				}
				return true;
			}
			
			explicit operator bool() const
			{
				return !(*this == fs_0());
			}

		};

#ifdef DMibDebuggerHelpers
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		assure_used typename TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CHelper *
		TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::ms_pHelper = nullptr;
#endif
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		bool operator < (NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Left, typename NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Right)
		{
			return _Left.f_Get() < _Right;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		bool operator < (typename NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Left, NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Right)
		{
			return _Left < _Right.f_Get();
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		bool operator == (NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Left, typename NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Right)
		{
			return _Left.f_Get() == _Right;
		}

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		bool operator == (typename NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Left, NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Right)
		{
			return _Left == _Right.f_Get();
		}

	}

	namespace NTraits
	{
		namespace NImplementation
		{
			template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
			class TCIsSigned<NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> >
			{
			public:
				enum
				{
					EValue = (t_SignBits > 0)
				};
			};

			template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
			class TCIsFloat<NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> >
			{
			public:
				enum
				{
					EValue = true
				};
			};
		}
	}

	

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< t_CType0, NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NTraits::TCCompileTimeConstant<int, (NTraits::TCIsFloat<t_CType0>::mc_Value)>>
	{
	public:

		template <typename t_CType>
		static DMibFloatInlineS t_CType0 fs_Convert( t_CType const &_From)
		{
			typedef typename NMath::TCFloatFromNative<t_CType0>::CType CRetType;
			CRetType Ret = _From;
			return (t_CType0 const &)Ret;
		}
	};

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< t_CType0, NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NTraits::TCCompileTimeConstant<int, (!NTraits::TCIsFloat<t_CType0>::mc_Value)>>
	{
	public:

		template <typename t_CType>
		static DMibFloatInlineS t_CType0 fs_Convert( t_CType const &_From)
		{
			return fg_Convert<t_CType0>(_From.f_ToInt());
		}

	};

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, t_CType0>
	{
	public:
		typedef NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CFloatType;

		template <typename t_CType>
		static DMibFloatInlineS typename TCDisableIf<NTraits::TCIsFloat<t_CType>::mc_Value, CFloatType>::CType fs_Convert( t_CType const &_From)
		{
			return CFloatType::fs_FromInt(_From);
		}

		template <typename t_CType>
		static DMibFloatInlineS typename TCEnableIf<NTraits::TCIsFloat<t_CType>::mc_Value, CFloatType>::CType fs_Convert( t_CType const &_From)
		{
			return CFloatType(((typename NMath::TCFloatFromNative<t_CType>::CType const &)_From));
		}
	};

	template <typename t_CUpper, typename t_CLower, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NMath::TCInt<t_CUpper, t_CLower> >
	{
	public:
		typedef NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CFloatType;
		static DMibFloatInlineS CFloatType fs_Convert( NMath::TCInt<t_CUpper, t_CLower> const &_From)
		{
			return CFloatType::fs_FromInt(_From);
		}
	};

}


#ifdef DMibPCanDo_fp8
typedef NMib::NMath::TCFloat <1, 3, 4, pfp8> CIEEEFloat8;
#else
typedef NMib::NMath::TCFloat <1, 3, 4> CIEEEFloat8;
#endif

#ifdef DMibPCanDo_fp16
typedef NMib::NMath::TCFloat <1, 5, 10, pfp16> CIEEEFloat16;
#else
typedef NMib::NMath::TCFloat <1, 5, 10> CIEEEFloat16;
#endif

#ifdef DMibPCanDo_fp32
typedef NMib::NMath::TCFloat <1, 8, 23, pfp32> CIEEEFloat32;
#else
typedef NMib::NMath::TCFloat <1, 8, 23> CIEEEFloat32;
#endif
#ifdef DMibPCanDo_fp64
typedef NMib::NMath::TCFloat <1, 11, 52, pfp64> CIEEEFloat64;
#else
typedef NMib::NMath::TCFloat <1, 11, 52> CIEEEFloat64;
#endif
#ifdef DMibPCanDo_fp80
typedef NMib::NMath::TCFloat <1, 16, 63, pfp80> CIEEEFloat80;
#else
typedef NMib::NMath::TCFloat <1, 16, 63> CIEEEFloat80;
#endif
#ifdef DMibPCanDo_fp128
typedef NMib::NMath::TCFloat <1, 15, 112, pfp128> CIEEEFloat128;
#else
typedef NMib::NMath::TCFloat <1, 15, 112> CIEEEFloat128;
#endif
typedef NMib::NMath::TCFloat <1, 31, 256-32> CIEEEFloat256;
typedef NMib::NMath::TCFloat <1, 63, 512-64> CIEEEFloat512;
typedef NMib::NMath::TCFloat <1, 63, 1024-64> CIEEEFloat1024;
typedef NMib::NMath::TCFloat <1, 63, 2048-64> CIEEEFloat2048;
typedef NMib::NMath::TCFloat <1, 63, 4096-64> CIEEEFloat4096;

#ifdef DMibPCanDo_fp8
typedef NMib::NMath::TCFloat <1, 2, 5, pfp8, 0> CIEEEFloat8Emu;
#else
typedef NMib::NMath::TCFloat <1, 2, 5, NMib::NMath::CNoImplicit, 0> CIEEEFloat8Emu;
#endif

#ifdef DMibPCanDo_fp16
typedef NMib::NMath::TCFloat <1, 4, 11, pfp16, 0> CIEEEFloat16Emu;
#else
typedef NMib::NMath::TCFloat <1, 4, 11, NMib::NMath::CNoImplicit, 0> CIEEEFloat16Emu;
#endif

#ifdef DMibPCanDo_fp32
typedef NMib::NMath::TCFloat <1, 8, 23, pfp32, 0> CIEEEFloat32Emu;
#else
typedef NMib::NMath::TCFloat <1, 8, 23, NMib::NMath::CNoImplicit, 0> CIEEEFloat32Emu;
#endif
#ifdef DMibPCanDo_fp64
typedef NMib::NMath::TCFloat <1, 11, 52, pfp64, 0> CIEEEFloat64Emu;
#else
typedef NMib::NMath::TCFloat <1, 11, 52, NMib::NMath::CNoImplicit, 0> CIEEEFloat64Emu;
#endif
#ifdef DMibPCanDo_fp80
typedef NMib::NMath::TCFloat <1, 16, 63, pfp80, 0> CIEEEFloat80Emu;
#else
typedef NMib::NMath::TCFloat <1, 16, 63, NMib::NMath::CNoImplicit, 0> CIEEEFloat80Emu;
#endif
#ifdef DMibPCanDo_fp128
typedef NMib::NMath::TCFloat <1, 15, 112, pfp128, 0> CIEEEFloat128Emu;
#else
typedef NMib::NMath::TCFloat <1, 15, 112, NMib::NMath::CNoImplicit, 0> CIEEEFloat128Emu;
#endif
typedef NMib::NMath::TCFloat <1, 31, 256-32, NMib::NMath::CNoImplicit, 0> CIEEEFloat256Emu;
typedef NMib::NMath::TCFloat <1, 63, 512-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat512Emu;
typedef NMib::NMath::TCFloat <1, 63, 1024-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat1024Emu;
typedef NMib::NMath::TCFloat <1, 63, 2048-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat2048Emu;
typedef NMib::NMath::TCFloat <1, 63, 4096-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat4096Emu;

typedef CIEEEFloat8 fp8;
typedef CIEEEFloat16 fp16;
typedef CIEEEFloat32 fp32;
typedef CIEEEFloat64 fp64;
typedef CIEEEFloat80 fp80;
typedef CIEEEFloat128 fp128;
typedef CIEEEFloat256 fp256;
typedef CIEEEFloat512 fp512;
typedef CIEEEFloat1024 fp1024;
typedef CIEEEFloat2048 fp2048;
typedef CIEEEFloat4096 fp4096;

typedef NMib::TCAutoClear<fp8> zfp8;
typedef NMib::TCAutoClear<fp16> zfp16;
typedef NMib::TCAutoClear<fp32> zfp32;
typedef NMib::TCAutoClear<fp64> zfp64;
typedef NMib::TCAutoClear<fp80> zfp80;
typedef NMib::TCAutoClear<fp128> zfp128;
typedef NMib::TCAutoClear<fp256> zfp256;
typedef NMib::TCAutoClear<fp512> zfp512;
typedef NMib::TCAutoClear<fp1024> zfp1024;
typedef NMib::TCAutoClear<fp2048> zfp2048;
typedef NMib::TCAutoClear<fp4096> zfp4096;


typedef NMib::NMath::TCFloat <0, 8, 24> ufp32;
typedef NMib::NMath::TCFloat <0, 3, 5> ufp8;
typedef NMib::NMath::TCFloat <0, 5, 11> ufp16;

typedef NMib::TCAutoClear<ufp8> zufp8;
typedef NMib::TCAutoClear<ufp16> zufp16;
typedef NMib::TCAutoClear<ufp32> zufp32;
#if 0
typedef NMib::TCAutoClear<ufp64> zufp64;
typedef NMib::TCAutoClear<ufp80> zufp80;
typedef NMib::TCAutoClear<ufp128> zufp128;
typedef NMib::TCAutoClear<ufp256> zufp256;
typedef NMib::TCAutoClear<ufp512> zufp512;
typedef NMib::TCAutoClear<ufp1024> zufp1024;
typedef NMib::TCAutoClear<ufp2048> zufp2048;
typedef NMib::TCAutoClear<ufp4096> zufp4096;
#endif

#ifdef DMibPFloat_StdLib
#	include "Malterlib_Numeric_Float_StdLib.h"
#endif

namespace NMib
{
	namespace NTraits
	{
		DMibTraitsImplementFloatFromSize(fp8);
		DMibTraitsImplementFloatFromSize(fp16);
		DMibTraitsImplementFloatFromSize(fp32);
		DMibTraitsImplementFloatFromSize(fp64);
		DMibTraitsImplementFloatFromSize(fp80);
		DMibTraitsImplementFloatFromSize(fp128);
		DMibTraitsImplementFloatFromSize(fp256);
		DMibTraitsImplementFloatFromSize(fp512);
		DMibTraitsImplementFloatFromSize(fp1024);
		DMibTraitsImplementFloatFromSize(fp2048);
		DMibTraitsImplementFloatFromSize(fp4096);

		DMibTraitsImplementSizePair(fp8, fp16);
		DMibTraitsImplementSizePair(fp16, fp32);
		DMibTraitsImplementSizePair(fp32, fp64);
		DMibTraitsImplementSizePair(fp64, fp128);
		DMibTraitsImplementSizePair(fp128, fp256);
		DMibTraitsImplementSizePair(fp256, fp512);
		DMibTraitsImplementSizePair(fp512, fp1024);
		DMibTraitsImplementSizePair(fp1024, fp2048);
		DMibTraitsImplementSizePair(fp2048, fp4096);
	}
}

