// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include <Mib/Storage/LazyInit>

#include "../../Core/Source/Malterlib_Core_General.h"

#if 0
	#define DMibFloatConstexpr constexpr
	#define DMibFloatConstexprCache(d_Type) constexpr d_Type
	#define DMibFloattDoInline
	#define DMibFloatConstexprEnabled 1
#else
	#define DMibFloatConstexprEnabled 0
	#define DMibFloatConstexpr
	#define DMibFloatConstexprCache(d_Type) static constinit NStorage::TCLazyInit<d_Type>
#endif

#ifndef DMibDebug
#	define DMibFloattDoInline
#	ifdef DCompiler_MSVC
#		define DMibFloattDoInline_NoExternTemplate
#	endif
#	define DMibFloatInline inline DMibFloatConstexpr
#	define DMibFloatInlineS inline_small DMibFloatConstexpr
#else
#	define DMibFloatInline DMibFloatConstexpr
#	define DMibFloatInlineS DMibFloatConstexpr
#endif

namespace NMib
{
	template <typename t_CType, aint _Power>
    class TCGetPowerTwoMinusOne
	{
	public:
		static const t_CType Number = (((t_CType)1) << (_Power - 1)) + ((((t_CType)1) << (_Power - 1)) - 1);
	};
}

namespace NMib::NNumeric
{
	struct CNoImplicit
	{
	};

	template <typename t_CFloat>
	class TCFloatFromNative;

	template <typename t_CFloat>
	class TCFloatConstants;

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat = CNoImplicit, bool t_bDummyOptimize = true, typename t_CIntegerStorage = typename NTraits::TCIntFromSizeLarger<(t_SignBits + t_ExponentBits + t_MantissaBits + 7)/8>::CType>
	class
#ifdef DCompiler_clang
	alignas(fg_MaxConstexpr(NTraits::TCAlignmentOf<t_CImplicitFloat>::mc_Value, NTraits::TCAlignmentOf<t_CIntegerStorage>::mc_Value))
#endif
	TCFloat
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

		using CEmulatedFloat = TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, false, t_CIntegerStorage>;

		static constexpr aint mc_MantissaBits = t_MantissaBits;
		static constexpr aint mc_ExponentBits = t_ExponentBits;
		static constexpr aint mc_SignBits = t_SignBits;
		static constexpr mint mc_StorageBits = sizeof(CInteger) * 8;
		static constexpr aint mc_UnusedBits = mc_StorageBits - (mc_SignBits + mc_ExponentBits + mc_MantissaBits);
		static constexpr aint mc_SignBitPos = mc_StorageBits - (mc_SignBits);
		static constexpr aint mc_ExponentBitPos = mc_StorageBits - (mc_SignBits + mc_ExponentBits);
		static constexpr aint mc_UnusedBitPos = mc_StorageBits - (mc_SignBits + mc_ExponentBits + mc_UnusedBits);
		static constexpr aint mc_MantissaBitPos = 0;

#ifdef DMibPFloat_StdLib
		static constexpr bool mc_bIsBuiltIn = !NTraits::TCIsSame<t_CImplicitFloat, CNoImplicit>::mc_Value;
#else
		static constexpr bool mc_bIsBuiltIn = false;s
#endif

		static_assert(mint(mc_UnusedBits) >= 0);
		static_assert(sizeof(CDoubleInteger) > sizeof(CInteger));

	protected:
		// Data stored in granularity of t_CStorageClass
		union
		{
			CUnsignedInteger m_Data;
			CImplicitFloat m_DataImplicit;
		};
		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Constants
		||______________________________________________________________________________________________||
		\************************************************************************************************/

#ifdef DMibDebuggerHelpers
		pfp64 f_Debug_GetAsDouble()
		{
			return NMib::NNumeric::TCFloat<1, 11, 52, pfp64>(*this).f_Get();
		}
#endif
		DMibFloatConstexpr void fp_Set_0();
		DMibFloatConstexpr void fp_Set_0_5();
		DMibFloatConstexpr void fp_Set_1();
		DMibFloatConstexpr void fp_Set_2();
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
		DMibFloatConstexpr void fp_Set_Inf();
		DMibFloatConstexpr void fp_Set_NegInf();
		DMibFloatConstexpr void fp_Set_QNan();
		DMibFloatConstexpr void fp_Set_SNan();
		DMibFloatConstexpr void fp_Set_NegQNan();
		DMibFloatConstexpr void fp_Set_NegSNan();
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
		static DMibFloatInline TCFloat fs_MaxExponent();
		static TCFloat fs_E();
		static TCFloat fs_Pi();
		static TCFloat fs_Sqrt2();
		static TCFloat fs_Euler();
		static TCFloat fs_GoldenRatio();
		static TCFloat fs_Log10_2();
		static TCFloat fs_Log2_10();
		static TCFloat fs_Log10_E();
		static TCFloat fs_LogE_10();
		static TCFloat fs_Log2_E();
		static TCFloat fs_LogE_2();
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
		DMibFloatConstexpr void f_SetAllRound(const CInteger &_Sign, const CInteger &_Exponent, const CDoubleUnsignedInteger &_Mantissa, aint _AtleastExtraBits);
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
		DMibFloatInlineS CUnsignedInteger &f_GetStorage();
		DMibFloatInlineS CUnsignedInteger const &f_GetStorage() const;
		DMibFloatInlineS CImplicitFloat &f_GetImplicit();
		DMibFloatInlineS CImplicitFloat const &f_GetImplicit() const;
		// Do nothing in default constructor
		DMibFloatInlineS TCFloat();
		DMibFloatInlineS ~TCFloat();

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
		static DMibFloatConstexpr TCFloat fs_FromInt(const t_CInteger &_Int);

		template <typename t_CInteger>
		DMibFloatConstexpr void f_FromInt(const t_CInteger &_Int);

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

		DMibFloatInlineS TCFloat(TCFloat const &_Value);
		DMibFloatInlineS TCFloat(CUnsignedInteger const &_Value, EConstexprInitialization);

		DMibFloatInlineS TCFloat &operator = (TCFloat const &_Value);

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by value operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat operator + (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator + (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

		DMibFloatConstexpr TCFloat operator - (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator - (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

		DMibFloatConstexpr TCFloat operator * (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator * (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

		DMibFloatConstexpr TCFloat operator / (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType operator / (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

		DMibFloatConstexpr TCFloat operator - () const;
		DMibFloatConstexpr TCFloat operator + () const;

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

			DMibFloatConstexpr CInternalFloat();

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

			DMibFloatConstexpr CInternalFloat(const TCFloat &_Source);
			DMibFloatConstexpr CInternalFloat &operator = (const TCFloat &_Source);
			DMibFloatConstexpr CMantissa f_GetSharedMantissa(CInternalFloat const &_Other, CMantissa &o_OtherMantissa, mint &o_nMantissaBits);
			DMibFloatConstexpr bool f_AlmostEqual(const CInternalFloat &_Value, int _nBits);
			DMibFloatConstexpr void f_SetAllRound(const CInteger &_Sign, const CExponent &_Exponent, const CMantissa &_Mantissa, aint _nMantissaBits);
			DMibFloatConstexpr void f_Mul(const CInternalFloat &_Value);
			DMibFloatConstexpr void f_Div(const CInternalFloat &_Value);
			DMibFloatConstexpr void f_Add(const CInternalFloat &_Value);
			DMibFloatConstexpr void f_Sub(const CInternalFloat &_Value);
			DMibFloatConstexpr void f_ATan();
			DMibFloatConstexpr void f_Remainder();

			DMibFloatConstexpr CSignedMantissa f_ToInt(bool &o_bOverflow);
			DMibFloatConstexpr void f_FromInt(const CSignedMantissa &_Int);
			DMibFloatConstexpr static CInternalFloat fs_FromInt(const CSignedMantissa &_Other);
			DMibFloatConstexpr void f_ExpN();
			DMibFloatConstexpr void f_Exp10();
			DMibFloatConstexpr TCFloat f_GetFloat();
			template <typename tf_CFloat>
			DMibFloatConstexpr tf_CFloat f_GetFloat();
			DMibFloatConstexpr void f_LogNFull();
			DMibFloatConstexpr void f_LogN();
			DMibFloatConstexpr void f_Log10();
			DMibFloatConstexpr void f_Log2();
			DMibFloatConstexpr void f_Exp2();
			DMibFloatConstexpr void f_Sqrt();
		};

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by reference operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat &operator += (const TCFloat &_Value);
		DMibFloatConstexpr TCFloat &operator -= (const TCFloat &_Value);
		DMibFloatConstexpr TCFloat &operator /= (const TCFloat &_Value);
		DMibFloatConstexpr TCFloat &operator *= (const TCFloat &_Value);
		DMibFloatConstexpr TCFloat &operator ++ ();
		DMibFloatConstexpr TCFloat &operator -- ();

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Postfix operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat operator ++ (int);
		DMibFloatConstexpr TCFloat operator -- (int);

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Trigomethric
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat f_Sin() const;
		DMibFloatConstexpr TCFloat f_Cos() const;
		DMibFloatConstexpr TCFloat f_Tan() const;
		DMibFloatConstexpr TCFloat f_SinH() const;
		DMibFloatConstexpr TCFloat f_CosH() const;
		DMibFloatConstexpr TCFloat f_TanH() const;
		DMibFloatConstexpr TCFloat f_ArcSin() const;
		DMibFloatConstexpr TCFloat f_ArcCos() const;
		DMibFloatConstexpr TCFloat f_ArcTan() const;
		DMibFloatConstexpr TCFloat f_ArcTan(const TCFloat &_Source) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_ArcTan(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Source) const;

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Logarithm and exponent
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat f_ExpN() const;
		DMibFloatConstexpr TCFloat f_LogN() const;
		DMibFloatConstexpr TCFloat f_Exp10() const;
		DMibFloatConstexpr TCFloat f_Log10() const;
		DMibFloatConstexpr TCFloat f_Exp2() const;
		DMibFloatConstexpr TCFloat f_Log2() const;
		DMibFloatConstexpr TCFloat f_Exp(const TCFloat & _Base) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Exp(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const;
		DMibFloatConstexpr TCFloat f_Log(const TCFloat & _Base) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Log(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const;

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Power
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat f_Sqrt() const;
		DMibFloatConstexpr TCFloat f_Sqr() const;
		DMibFloatConstexpr TCFloat f_Pow(const TCFloat &_Power) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Pow(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Power) const;

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Integer functions
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat f_Floor() const;
		DMibFloatConstexpr TCFloat f_Fraction() const;
		DMibFloatConstexpr TCFloat f_Ceil() const;
		DMibFloatConstexpr TCFloat f_Abs() const;
		DMibFloatConstexpr TCFloat f_Mod(const TCFloat &_Modulu) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr typename NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>>::CType f_Mod(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Modulu) const;


		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Integer functions
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr bool f_AlmostEqual(TCFloat const &_Other, mint _nMantissaBits = 1) const;

		DMibFloatConstexpr bool operator == (const TCFloat &_Value) const;
		DMibFloatConstexpr bool operator < (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr bool operator < (TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr bool operator == (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right) const;
		DMibFloatConstexpr explicit operator bool() const;
	};

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	DMibFloatConstexpr bool operator < (NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Left, typename NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Right);
	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	DMibFloatConstexpr bool operator < (typename NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Left, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Right);
	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	DMibFloatConstexpr bool operator == (NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Left, typename NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Right);
	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	DMibFloatConstexpr bool operator == (typename NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::CImplicitFloat const &_Left, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> const &_Right);
}

namespace NMib::NTraits::NImplementation
{
	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCIsSigned<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> >
	{
	public:
		enum
		{
			EValue = (t_SignBits > 0)
		};
	};

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCIsFloat<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> >
	{
	public:
		enum
		{
			EValue = true
		};
	};
}

namespace NMib
{
	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< t_CType0, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NTraits::TCCompileTimeConstant<int, (NTraits::TCIsFloat<t_CType0>::mc_Value)>>
	{
	public:

		template <typename t_CType>
		static DMibFloatInlineS t_CType0 fs_Convert( t_CType const &_From)
		{
			typedef typename NNumeric::TCFloatFromNative<t_CType0>::CType CRetType;
			CRetType Ret = _From;
			return (t_CType0 const &)Ret;
		}
	};

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< t_CType0, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NTraits::TCCompileTimeConstant<int, (!NTraits::TCIsFloat<t_CType0>::mc_Value)>>
	{
	public:

		template <typename t_CType>
		static DMibFloatInlineS t_CType0 fs_Convert( t_CType const &_From)
		{
			return fg_Convert<t_CType0>(_From.f_ToInt());
		}

	};

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, t_CType0>
	{
	public:
		typedef NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CFloatType;

		template <typename t_CType>
		static DMibFloatInlineS typename TCDisableIf<NTraits::TCIsFloat<t_CType>::mc_Value, CFloatType>::CType fs_Convert( t_CType const &_From)
		{
			return CFloatType::fs_FromInt(_From);
		}

		template <typename t_CType>
		static DMibFloatInlineS typename TCEnableIf<NTraits::TCIsFloat<t_CType>::mc_Value, CFloatType>::CType fs_Convert( t_CType const &_From)
		{
			return CFloatType(((typename NNumeric::TCFloatFromNative<t_CType>::CType const &)_From));
		}
	};

	template <typename t_CUpper, typename t_CLower, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NNumeric::TCInt<t_CUpper, t_CLower> >
	{
	public:
		typedef NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CFloatType;
		static DMibFloatInlineS CFloatType fs_Convert( NNumeric::TCInt<t_CUpper, t_CLower> const &_From)
		{
			return CFloatType::fs_FromInt(_From);
		}
	};
}

#ifdef DMibFloattDoInline
#	include "Malterlib_Numeric_Float.hpp"
#endif

// Default support
#if defined(DMibPCanDo_fp32)
#	include "Malterlib_Numeric_Float_fp32.h"
#endif
#if defined(DMibPCanDo_fp64)
#	include "Malterlib_Numeric_Float_fp64.h"
#endif
#if defined(DMibPCanDo_fp80)
#	include "Malterlib_Numeric_Float_fp80.h"
#endif

#ifndef DMibPNoShortCuts
	using namespace NMib::NNumeric;
#endif
