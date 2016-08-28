// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib
#pragma once

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
			CNoImplicit() = delete;
			~CNoImplicit() = delete;
		};

		template <typename t_CFloat>
		class TCFloatFromNative;

		template <typename t_CFloat>
		class TCFloatConstants;

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat = CNoImplicit, bool t_bDummyOptimize = true, typename t_CIntegerStorage = typename NTraits::TCIntFromSizeLarger<(t_SignBits + t_ExponentBits + t_MantissaBits + 7)/8>::CType>
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
				EStorageBits = sizeof(CInteger) * 8				
				, ESignBits = t_SignBits
				, EExponentBits = t_ExponentBits
				, EMantissaBits = t_MantissaBits
				, EUnusedBits = EStorageBits - (ESignBits + EExponentBits + EMantissaBits)
				, ESignBitPos = EStorageBits - (ESignBits)
				, EExponentBitPos = EStorageBits - (ESignBits + EExponentBits)
				, EUnusedBitPos = EStorageBits - (ESignBits + EExponentBits + EUnusedBits)
				, EMantissaBitPos = 0
#ifdef DMibPFloat_StdLib
				, mc_bIsBuiltIn = !NTraits::TCIsSame<t_CImplicitFloat, CNoImplicit>::mc_Value
#else
				, mc_bIsBuiltIn = false
#endif
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
					
					return NMib::NMath::TCFloat<1, 11, 52, pfp64>(*pThis).f_Get();
				}
			};
			static CHelper *ms_pHelper;
#endif
			void fp_Set_0();
			void fp_Set_0_5();
			void fp_Set_1();
			void fp_Set_2();
			void fp_Set_E();
			void fp_Set_Pi();
			void fp_Set_Euler();
			void fp_Set_Sqrt2();
			void fp_Set_GoldenRatio();
			void fp_Set_Log2_10();
			void fp_Set_Log10_2();
			void fp_Set_LogE_10();
			void fp_Set_Log10_E();
			void fp_Set_Log2_E();
			void fp_Set_LogE_2();
			void fp_Set_Inf();
			void fp_Set_NegInf();
			void fp_Set_QNan();
			void fp_Set_SNan();
			void fp_Set_NegQNan();
			void fp_Set_NegSNan();
		public:
			
			static DMibFloatInline TCFloat fs_SmallestDenormal();
			static DMibFloatInline TCFloat fs_NegSmallestDenormal();
			static DMibFloatInline TCFloat fs_Smallest();
			static DMibFloatInline TCFloat fs_NegSmallest();
			static DMibFloatInline TCFloat fs_LimitMin();
			static DMibFloatInline TCFloat fs_LimitMax();
			static DMibFloatInline TCFloat fs_Epsilon();
			static DMibFloatInline TCFloat fs_0();
			static DMibFloatInline TCFloat fs_0_5();
			static DMibFloatInline TCFloat fs_1();
			static DMibFloatInline TCFloat fs_2();
			static DMibFloatInline TCFloat fs_E();
			static DMibFloatInline TCFloat fs_Pi();
			static DMibFloatInline TCFloat fs_Sqrt2();
			static DMibFloatInline TCFloat fs_Euler();
			static DMibFloatInline TCFloat fs_GoldenRatio();
			static DMibFloatInline TCFloat fs_Log10_2();
			static DMibFloatInline TCFloat fs_Log2_10();
			static DMibFloatInline TCFloat fs_Log10_E();
			static DMibFloatInline TCFloat fs_LogE_10();
			static DMibFloatInline TCFloat fs_Log2_E();
			static DMibFloatInline TCFloat fs_LogE_2();
			DMibFloatInlineS CInteger f_GetSignBits() const;
			DMibFloatInlineS CInteger f_GetExponentBits() const;
			DMibFloatInlineS CInteger f_GetMantissaBits() const;
			DMibFloatInlineS CInteger f_GetSign() const;
			DMibFloatInlineS CInteger f_GetExponent() const;
			DMibFloatInlineS CInteger f_GetMantissa() const;
			DMibFloatInlineS CInteger f_GetDenormalizedMantissa() const;
			DMibFloatInlineS void f_GetNormalized(CInteger &o_Exponent, CInteger &o_Mantissa) const;
			DMibFloatInlineS void f_SetSignBits(const CUnsignedInteger &_Value);
			DMibFloatInlineS void f_SetExponentBits(const CUnsignedInteger &_Value);
			DMibFloatInlineS void f_SetMantissaBits(const CUnsignedInteger &_Value);
			DMibFloatInlineS void f_SetSign(const CInteger &_Value);
			DMibFloatInlineS void f_SetExponent(const CInteger &_Value);
			DMibFloatInlineS void f_SetMantissa(const CInteger &_Value);
			void f_SetAllRound(const CInteger &_Sign, const CInteger &_Exponent, const CDoubleUnsignedInteger &_Mantissa, aint _AtleastExtraBits);
			DMibFloatInlineS bool f_IsNan() const;
			DMibFloatInlineS bool f_IsQNan() const;
			DMibFloatInlineS bool f_IsSNan() const;
			DMibFloatInlineS bool f_IsInfinity() const;
			DMibFloatInlineS bool f_IsInvalid() const;
			DMibFloatInlineS bool f_IsDenormalized() const;
			static DMibFloatInline TCFloat fs_Inf();
			static DMibFloatInline TCFloat fs_NegInf();
			static DMibFloatInline TCFloat fs_QNan();
			static DMibFloatInline TCFloat fs_SNan();
			static DMibFloatInline TCFloat fs_NegQNan();
			static DMibFloatInline TCFloat fs_NegSNan();
			DMibFloatInlineS void * f_GetData();
			DMibFloatInlineS const void * f_GetData() const;
			CUnsignedInteger &f_GetStorage();
			CUnsignedInteger const &f_GetStorage() const;
			// Do nothing in default constructor
			DMibFloatInlineS TCFloat();

			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			DMibFloatInlineS void f_AssignRoundUp(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue);
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			DMibFloatInlineS void f_Assign(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue);
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			DMibFloatInlineS TCFloat & operator = (const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue);
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			DMibFloatInlineS TCFloat(const TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> &_SetValue);
			DMibFloatInlineS CInteger f_ToInt() const;
			DMibFloatInlineS CUnsignedInteger f_ToUnsignedInt() const;
			DMibFloatInlineS CInteger f_ToIntRound() const;
			DMibFloatInlineS CUnsignedInteger f_ToUnsignedIntRound() const;
			DMibFloatInlineS CInteger f_ToIntRoundTowardZero() const;
			DMibFloatInlineS CUnsignedInteger f_ToUnsignedIntRoundTowardZero() const;

			template <typename t_CInteger>
			static TCFloat fs_FromInt(const t_CInteger &_Int);
			
			template <typename t_CInteger>
			void f_FromInt(const t_CInteger &_Int);
			
            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Implicit Float
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			DMibFloatInlineS t_CImplicitFloat &f_Get();
			DMibFloatInlineS t_CImplicitFloat const &f_Get() const;
			DMibFloatInlineS TCFloat(const t_CImplicitFloat &_Value);
			DMibFloatInlineS TCFloat &operator = (const t_CImplicitFloat &_Value);
			template <typename tf_CType>
			DMibFloatInlineS TCFloat(tf_CType _Value, typename TCEnableIf<NTraits::TCIsSame<tf_CType, bool>::mc_Value>::CType *_pDummy = nullptr);
			template <typename tf_CType>
			DMibFloatInlineS typename TCEnableIf<NTraits::TCIsSame<tf_CType, bool>::mc_Value, TCFloat &>::CType operator = (tf_CType _Value);

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Return by value operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat operator + (const TCFloat &_Value) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator + (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

			TCFloat operator - (const TCFloat &_Value) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator - (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

			TCFloat operator * (const TCFloat &_Value) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator * (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

			TCFloat operator / (const TCFloat &_Value) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator / (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;
			
			TCFloat operator - () const;
			TCFloat operator + () const;

			// Internal float working with 8 extra bits of precission
			class CInternalFloat
			{
			public:
				typedef CDoubleUnsignedInteger CMantissa;
				typedef CDoubleInteger CSignedMantissa;
				typedef CDoubleInteger CExponent;

				typedef typename NTraits::TCLargerType<CMantissa>::CType CRawQuadMantissa;

				typedef typename NTraits::TCUnsigned<CRawQuadMantissa>::CType CQuadMantissa;
				typedef typename NTraits::TCSigned<CRawQuadMantissa>::CType CSignedQuadMantissa;
				
				CMantissa m_Mantissa;
				CExponent m_Exponent;
				CInteger m_Sign;
				mint m_MantissaBits = 0;

				CInternalFloat();

				enum
				{
					EInternalMaxMantissaBits = sizeof(CMantissa)*8 - 3,
					EInternalHalfMantissaBits = EInternalMaxMantissaBits / 2,
					EInternalMaxQuadMantissaBits = sizeof(CQuadMantissa)*8 - 2,
					EInternalHalfQuadMantissaBits = EInternalMaxQuadMantissaBits / 2,
					EInternalExponentBits = sizeof(CExponent)*8 - 2
				};

				static CInternalFloat fs_LogE_2();
				static CInternalFloat fs_Log2_E();
				static CInternalFloat fs_LogE_10();
				static CInternalFloat fs_Log10_E();
				static CInternalFloat fs_Log2_10();
				static CInternalFloat fs_Log10_2();
				static CInternalFloat fs_E();
				static CInternalFloat fs_Euler();
				static CInternalFloat fs_GoldenRatio();
				static CInternalFloat fs_Pi();
				static CInternalFloat fs_Sqrt2();
				
				CInternalFloat(const TCFloat &_Source);
				CInternalFloat &operator = (const TCFloat &_Source);
				CMantissa f_GetSharedMantissa(CInternalFloat const &_Other, CMantissa &o_OtherMantissa, mint &o_nMantissaBits);
				bool f_AlmostEqual(const CInternalFloat &_Value, int _nBits);
				void f_SetAllRound(const CInteger &_Sign, const CExponent &_Exponent, const CMantissa &_Mantissa, aint _nMantissaBits);
				void f_Mul(const CInternalFloat &_Value);
				void f_Div(const CInternalFloat &_Value);
				void f_Add(const CInternalFloat &_Value);
				void f_Sub(const CInternalFloat &_Value);
				void f_ATan();
				void f_Remainder();
				
				CSignedMantissa f_ToInt(bool &o_bOverflow);
				void f_FromInt(const CSignedMantissa &_Int);
				static CInternalFloat fs_FromInt(const CSignedMantissa &_Other);
				void f_ExpN();
				void f_Exp10();
				TCFloat f_GetFloat();
				template <typename tf_CFloat>
				tf_CFloat f_GetFloat();
				void f_LogNFull();
				void f_LogN();
				void f_Log10();
				void f_Log2();
				void f_Exp2();
				void f_Sqrt();
			};

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Return by reference operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat &operator += (const TCFloat &_Value);
			TCFloat &operator -= (const TCFloat &_Value);
			TCFloat &operator /= (const TCFloat &_Value);
			TCFloat &operator *= (const TCFloat &_Value);
			TCFloat &operator ++ ();
			TCFloat &operator -- ();
			
			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Postfix operators
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat operator ++ (int);
			TCFloat operator -- (int);

            /************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Trigomethric
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat f_Sin() const;
			TCFloat f_Cos() const;
			TCFloat f_Tan() const;
			TCFloat f_SinH() const;
			TCFloat f_CosH() const;
			TCFloat f_TanH() const;
			TCFloat f_ArcSin() const;
			TCFloat f_ArcCos() const;
			TCFloat f_ArcTan() const;
			TCFloat f_ArcTan(const TCFloat &_Source) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_ArcTan(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Source) const;

			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Logarithm and exponent
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat f_ExpN() const;
			TCFloat f_LogN() const;
			TCFloat f_Exp10() const;
			TCFloat f_Log10() const;
			TCFloat f_Exp2() const;
			TCFloat f_Log2() const;
			TCFloat f_Exp(const TCFloat & _Base) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Exp(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const;
			TCFloat f_Log(const TCFloat & _Base) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Log(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const;

			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Power
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat f_Sqrt() const;
			TCFloat f_Sqr() const;
			TCFloat f_Pow(const TCFloat &_Power) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Pow(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Power) const;

			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Integer functions
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			TCFloat f_Floor() const;
			TCFloat f_Fraction() const;
			TCFloat f_Ceil() const; 
			TCFloat f_Abs() const;
			TCFloat f_Mod(const TCFloat &_Modulu) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			typename NTraits::TCLargestType<TCFloat, NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Mod(NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Modulu) const;
			
			
			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Integer functions
			||______________________________________________________________________________________________||
			\************************************************************************************************/

			bool f_AlmostEqual(TCFloat const &_Other, mint _nMantissaBits = 1) const;
			
			bool operator == (const TCFloat &_Value) const;
			bool operator < (const TCFloat &_Value) const;
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			bool operator < (TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right);
			template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
			bool operator == (NMib::NMath::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right);
			explicit operator bool() const;
		};

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		bool operator < (NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Left, typename NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Right);
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		bool operator < (typename NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Left, NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Right);
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		bool operator == (NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Left, typename NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Right);
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		bool operator == (typename NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Left, NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Right);
	}

	namespace NTraits
	{
		namespace NImplementation
		{
			template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
			class TCIsSigned<NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> >
			{
			public:
				enum
				{
					EValue = (t_SignBits > 0)
				};
			};

			template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
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

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
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

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< t_CType0, NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NTraits::TCCompileTimeConstant<int, (!NTraits::TCIsFloat<t_CType0>::mc_Value)>>
	{
	public:

		template <typename t_CType>
		static DMibFloatInlineS t_CType0 fs_Convert( t_CType const &_From)
		{
			return fg_Convert<t_CType0>(_From.f_ToInt());
		}

	};

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
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

	template <typename t_CUpper, typename t_CLower, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
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
typedef NMib::NMath::TCFloat<1, 3, 4, pfp8> CIEEEFloat8;
typedef NMib::NMath::TCFloat<1, 2, 5, pfp8, 0> CIEEEFloat8Emu;
#else
typedef NMib::NMath::TCFloat<1, 3, 4> CIEEEFloat8;
typedef NMib::NMath::TCFloat<1, 2, 5, NMib::NMath::CNoImplicit, 0> CIEEEFloat8Emu;
#endif
typedef NMib::NMath::TCFloat<0, 3, 5> ufp8;
typedef CIEEEFloat8 fp8;
typedef NMib::TCAutoClear<fp8> zfp8;
typedef NMib::TCAutoClear<ufp8> zufp8;

#ifdef DMibPCanDo_fp16
typedef NMib::NMath::TCFloat<1, 5, 10, pfp16> CIEEEFloat16;
typedef NMib::NMath::TCFloat<1, 4, 11, pfp16, 0> CIEEEFloat16Emu;
#else
typedef NMib::NMath::TCFloat<1, 5, 10> CIEEEFloat16;
typedef NMib::NMath::TCFloat<1, 4, 11, NMib::NMath::CNoImplicit, 0> CIEEEFloat16Emu;
#endif
typedef NMib::NMath::TCFloat<0, 5, 11> ufp16;
typedef CIEEEFloat16 fp16;
typedef NMib::TCAutoClear<fp16> zfp16;
typedef NMib::TCAutoClear<ufp16> zufp16;

#ifdef DMibPCanDo_fp32
typedef NMib::NMath::TCFloat<1, 8, 23, pfp32> CIEEEFloat32;
typedef NMib::NMath::TCFloat<1, 8, 23, pfp32, 0> CIEEEFloat32Emu;
#else
typedef NMib::NMath::TCFloat<1, 8, 23> CIEEEFloat32;
typedef NMib::NMath::TCFloat<1, 8, 23, NMib::NMath::CNoImplicit, 0> CIEEEFloat32Emu;
#endif
typedef NMib::NMath::TCFloat<0, 8, 24> ufp32;
typedef CIEEEFloat32 fp32;
typedef NMib::TCAutoClear<fp32> zfp32;
typedef NMib::TCAutoClear<ufp32> zufp32;

#ifdef DMibPCanDo_fp64
typedef NMib::NMath::TCFloat<1, 11, 52, pfp64, 0> CIEEEFloat64Emu;
typedef NMib::NMath::TCFloat<1, 11, 52, pfp64> CIEEEFloat64;
#else
typedef NMib::NMath::TCFloat<1, 11, 52> CIEEEFloat64;
typedef NMib::NMath::TCFloat<1, 11, 52, NMib::NMath::CNoImplicit, 0> CIEEEFloat64Emu;
#endif
typedef CIEEEFloat64 fp64;
typedef NMib::TCAutoClear<fp64> zfp64;
//typedef NMib::TCAutoClear<ufp64> zufp64;

#ifdef DMibPCanDo_fp80
typedef NMib::NMath::TCFloat<1, 15, 63, pfp80> CIEEEFloat80;
typedef NMib::NMath::TCFloat<1, 15, 63, pfp80, 0> CIEEEFloat80Emu;
#else
typedef NMib::NMath::TCFloat<1, 15, 63> CIEEEFloat80;
typedef NMib::NMath::TCFloat<1, 15, 63, NMib::NMath::CNoImplicit, 0> CIEEEFloat80Emu;
#endif
typedef CIEEEFloat80 fp80;
typedef NMib::TCAutoClear<fp80> zfp80;
//typedef NMib::TCAutoClear<ufp80> zufp80;

#ifdef DMibPCanDo_fp128
typedef NMib::NMath::TCFloat<1, 15, 112, pfp128> CIEEEFloat128;
typedef NMib::NMath::TCFloat<1, 15, 112, pfp128, 0> CIEEEFloat128Emu;
#else
typedef NMib::NMath::TCFloat<1, 15, 112> CIEEEFloat128;
typedef NMib::NMath::TCFloat<1, 15, 112, NMib::NMath::CNoImplicit, 0> CIEEEFloat128Emu;
#endif
typedef CIEEEFloat128 fp128;
typedef NMib::TCAutoClear<fp128> zfp128;
//typedef NMib::TCAutoClear<ufp128> zufp128;

typedef NMib::NMath::TCFloat<1, 19, 236> CIEEEFloat256;
typedef NMib::NMath::TCFloat<1, 19, 236, NMib::NMath::CNoImplicit, 0> CIEEEFloat256Emu;
typedef CIEEEFloat256 fp256;
typedef NMib::TCAutoClear<fp256> zfp256;
//typedef NMib::TCAutoClear<ufp256> zufp256;

typedef NMib::NMath::TCFloat<1, 63, 512-64> CIEEEFloat512;
typedef NMib::NMath::TCFloat<1, 63, 512-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat512Emu;
typedef CIEEEFloat512 fp512;
typedef NMib::TCAutoClear<fp512> zfp512;
//typedef NMib::TCAutoClear<ufp512> zufp512;

typedef NMib::NMath::TCFloat<1, 63, 1024-64> CIEEEFloat1024;
typedef NMib::NMath::TCFloat<1, 63, 1024-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat1024Emu;
typedef CIEEEFloat1024 fp1024;
typedef NMib::TCAutoClear<fp1024> zfp1024;
//typedef NMib::TCAutoClear<ufp1024> zufp1024;

typedef NMib::NMath::TCFloat<1, 63, 2048-64> CIEEEFloat2048;
typedef NMib::NMath::TCFloat<1, 63, 2048-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat2048Emu;
typedef CIEEEFloat2048 fp2048;
typedef NMib::TCAutoClear<fp2048> zfp2048;
//typedef NMib::TCAutoClear<ufp2048> zufp2048;

typedef NMib::NMath::TCFloat<1, 63, 4096-64> CIEEEFloat4096;
typedef NMib::NMath::TCFloat<1, 63, 4096-64, NMib::NMath::CNoImplicit, 0> CIEEEFloat4096Emu;
typedef CIEEEFloat4096 fp4096;
typedef NMib::TCAutoClear<fp4096> zfp4096;
//typedef NMib::TCAutoClear<ufp4096> zufp4096;


// Default supprot
#if defined(DMibPCanDo_fp32)
#	include "Malterlib_Numeric_Float_fp32.h"
#endif
#if defined(DMibPCanDo_fp64)
#	include "Malterlib_Numeric_Float_fp64.h"
#endif
#if defined(DMibPCanDo_fp80)
#	include "Malterlib_Numeric_Float_fp80.h"
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
