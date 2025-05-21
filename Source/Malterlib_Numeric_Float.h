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
		auto operator <=> (CNoImplicit const &_Right) const = default;
	};

	template <typename t_CFloat>
	class TCFloatFromNative;

	template <typename t_CFloat>
	class TCFloatConstants;

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat = CNoImplicit, bool t_bDummyOptimize = true, typename t_CIntegerStorage = NTraits::TCIntFromSizeLarger<(t_SignBits + t_ExponentBits + t_MantissaBits + 7)/8>>
	class
#ifdef DCompiler_clang
	alignas(fg_MaxConstexpr(alignof(t_CImplicitFloat), alignof(t_CIntegerStorage)))
#endif
	TCFloat
	{
		template <typename t_CFloat>
		friend class TCFloatConstants;
		using CDoubleIntegerRaw = NTraits::TCLargerType<t_CIntegerStorage>;
	public:
		using CInteger = t_CIntegerStorage;
		using CDoubleInteger = TCConditional<sizeof(CDoubleIntegerRaw) >= 8, CDoubleIntegerRaw, NTraits::TCIntFromSizeLarger<8>>;
		using CUnsignedInteger = NTraits::TCUnsigned<t_CIntegerStorage>;
		using CDoubleUnsignedInteger = NTraits::TCUnsigned<CDoubleInteger>;
		using CImplicitFloat = t_CImplicitFloat;

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
		static constexpr bool mc_bIsBuiltIn = !NTraits::cIsSame<t_CImplicitFloat, CNoImplicit>;
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
		DMibFloatInlineS ~TCFloat() = default;

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
		DMibFloatInlineS TCFloat(tf_CType _Value, TCEnableIf<NTraits::cIsSame<tf_CType, bool>> *_pDummy = nullptr);
		template <typename tf_CType>
		DMibFloatInlineS TCEnableIf<NTraits::cIsSame<tf_CType, bool>, TCFloat &> operator = (tf_CType _Value);

		DMibFloatInlineS TCFloat(TCFloat const &_Value);
		DMibFloatInlineS TCFloat(TCFloat &&_Value);
		DMibFloatInlineS TCFloat(CUnsignedInteger const &_Value, EConstexprInitialization);

		DMibFloatInlineS TCFloat &operator = (TCFloat const &_Value);
		DMibFloatInlineS TCFloat &operator = (TCFloat &&_Value);

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Return by value operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat operator + (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> operator + (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

		DMibFloatConstexpr TCFloat operator - (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> operator - (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

		DMibFloatConstexpr TCFloat operator * (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> operator * (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

		DMibFloatConstexpr TCFloat operator / (const TCFloat &_Value) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> operator / (NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Value) const;

		DMibFloatConstexpr TCFloat operator - () const;
		DMibFloatConstexpr TCFloat operator + () const;

		// Internal float working with 8 extra bits of precission
		class CInternalFloat
		{
		public:
			using CMantissa = CDoubleUnsignedInteger;
			using CSignedMantissa = CDoubleInteger;
			using CExponent = CDoubleInteger;

			using CRawQuadMantissa = NTraits::TCLargerType<CMantissa>;

			using CQuadMantissa = NTraits::TCUnsigned<CRawQuadMantissa>;
			using CSignedQuadMantissa = NTraits::TCSigned<CRawQuadMantissa>;

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
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> f_ArcTan(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Source) const;

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
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> f_Exp(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const;
		DMibFloatConstexpr TCFloat f_Log(const TCFloat & _Base) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> f_Log(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Base) const;

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Power
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr TCFloat f_Sqrt() const;
		DMibFloatConstexpr TCFloat f_Sqr() const;
		DMibFloatConstexpr TCFloat f_Pow(const TCFloat &_Power) const;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> f_Pow(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Power) const;

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
		DMibFloatConstexpr NTraits::TCLargestType<TCFloat, NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2>> f_Mod(NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Modulu) const;


		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Integer functions
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		DMibFloatConstexpr bool f_AlmostEqual(TCFloat const &_Other, mint _nMantissaBits = 1) const;

		DMibFloatConstexpr bool operator == (const TCFloat &_Value) const;
		DMibFloatConstexpr bool f_EqualIncludingNan(const TCFloat &_Value) const;
		DMibFloatConstexpr COrdering_Partial operator <=> (const TCFloat &_Value) const;
		DMibFloatConstexpr COrdering_Partial f_SpaceshipIncludingNan(const TCFloat &_Value) const;

		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr bool operator ==
			(
				NMib::NNumeric::TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right
			) const
		;
		template <aint t_SignBits2, aint t_ExponentBits2, aint t_MantissaBits2, typename t_CImplicitFloat2, bool t_bDummyOptimize2, typename t_CIntegerStorage2>
		DMibFloatConstexpr COrdering_Partial operator <=>
			(
				TCFloat<t_SignBits2, t_ExponentBits2, t_MantissaBits2, t_CImplicitFloat2, t_bDummyOptimize2, t_CIntegerStorage2> const &_Right
			) const
		;

		DMibFloatConstexpr bool operator == (CImplicitFloat const &_Right) const
		{
			return f_Get() == _Right;
		}

		DMibFloatConstexpr COrdering_Partial operator <=> (CImplicitFloat const &_Right) const
		{
			return f_Get() <=> _Right;
		}

		DMibFloatConstexpr explicit operator bool() const;
	};

	namespace NPrivate
	{
		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits>
		struct TCImplicitFloatFromParams
		{
			using CType = CNoImplicit;
		};
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits>
	using TCImplicitFloatFromParams = typename NPrivate::TCImplicitFloatFromParams<t_SignBits, t_ExponentBits, t_MantissaBits>::CType;

#	define DMibNumericImplementImplicitFloatFromParams(d_SignBits, d_ExponentBits, d_MantissaBits, d_Implicit) \
		template <>	\
		struct NMib::NNumeric::NPrivate::TCImplicitFloatFromParams<d_SignBits, d_ExponentBits, d_MantissaBits> \
		{ \
			using CType = d_Implicit; \
		};
}

namespace NMib::NTraits::NPrivate
{
	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	struct TCIsSigned<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
	{
		constexpr static bool mc_bValue = (t_SignBits > 0);
	};

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	struct TCUnsigned<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
	{
		using CType = NMib::NNumeric::TCFloat
			<
				0
				, t_ExponentBits
				, t_MantissaBits + t_SignBits
				, NMib::NNumeric::TCImplicitFloatFromParams<0, t_ExponentBits, t_MantissaBits + t_SignBits>
				, t_bDummyOptimize
				, t_CIntegerStorage
			>
		;
	};

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	struct TCSigned<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
	{
		using CType = NMib::NNumeric::TCFloat
			<
				1
				, t_ExponentBits
				, t_MantissaBits + t_SignBits - 1
				, NMib::NNumeric::TCImplicitFloatFromParams<1, t_ExponentBits, t_MantissaBits + t_SignBits - 1>
				, t_bDummyOptimize
				, t_CIntegerStorage
			>
		;
	};

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	struct TCIsFloat<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
	{
		constexpr static bool mc_bValue = true;
	};
}

namespace NMib
{
	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< t_CType0, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NTraits::TCCompileTimeConstant<int, (NTraits::cIsFloat<t_CType0>)>>
	{
	public:

		template <typename t_CType>
		static DMibFloatInlineS t_CType0 fs_Convert( t_CType const &_From)
		{
			using CRetType = typename NNumeric::TCFloatFromNative<t_CType0>::CType;
			CRetType Ret = _From;
			return (t_CType0 const &)Ret;
		}
	};

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< t_CType0, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NTraits::TCCompileTimeConstant<int, (!NTraits::cIsFloat<t_CType0>)>>
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
		using CFloatType = NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>;

		template <typename t_CType>
		static DMibFloatInlineS TCDisableIf<NTraits::cIsFloat<t_CType>, CFloatType> fs_Convert( t_CType const &_From)
		{
			return CFloatType::fs_FromInt(_From);
		}

		template <typename t_CType>
		static DMibFloatInlineS TCEnableIf<NTraits::cIsFloat<t_CType>, CFloatType> fs_Convert( t_CType const &_From)
		{
			return CFloatType(((typename NNumeric::TCFloatFromNative<t_CType>::CType const &)_From));
		}
	};

	template <typename t_CUpper, typename t_CLower, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	class TCConvert< NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, NNumeric::TCInt<t_CUpper, t_CLower> >
	{
	public:
		using CFloatType = NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> ;
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
