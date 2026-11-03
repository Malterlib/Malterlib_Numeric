// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

namespace NMib
{
	namespace NNumeric
	{
#define DMibMathImplementNativeFloat(d_Native, d_TCFloat) \
	template <>\
	struct TCFloatFromNative<d_Native>\
	{\
		using CType = d_TCFloat;\
	};

		DMibMathImplementNativeFloat(pfp32, CIEEEFloat32);
		DMibMathImplementNativeFloat(pfp64, CIEEEFloat64);

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		struct TCFloatFromNative<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
		{
			using CType = NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>;
		};

		template <typename t_CFloat>
		struct TCFloatTraits : public TCFloatTraits<typename TCFloatFromNative<t_CFloat>::CType>
		{
		};

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
		struct TCFloatTraits<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
		{
		private:
			// Declared before the public section, which uses it.
			using CFloat = NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>;

		public:
			using CStorageInteger = typename CFloat::CInteger;
			using CStorageInteger_X2 = typename CFloat::CDoubleInteger;
			using CStorageUnsignedInteger = typename CFloat::CUnsignedInteger;
			using CStorageUnsignedInteger_X2 = typename CFloat::CDoubleUnsignedInteger;
			using CFundamentalFloat = typename CFloat::CImplicitFloat;

			bool const static ms_bHasFundamentalFloat = !NTraits::cIsSame<CFundamentalFloat, NMib::NNumeric::CNoImplicit>;
		};

		template <typename t_CFloat>
		struct TCNativeFromFloat
		{
			using CType = TCConditional<TCFloatTraits<t_CFloat>::ms_bHasFundamentalFloat, typename TCFloatTraits<t_CFloat>::CFundamentalFloat, t_CFloat>;
		};

		template <typename t_CFloat0, typename t_CFloat1>
		struct TCFloatCombinedType
		{
			using CType = NTraits::TCLargestType<t_CFloat0, t_CFloat1>;
		};

		template <typename t_CFloat, void (&t_fInit)(t_CFloat &_Float)>
		struct TCFloatConstant
		{
			constexpr TCFloatConstant(EAggregateInitialization _Init);
			operator t_CFloat const & ();

		private:
			bool mp_bInit;
			NStorage::TCAggregateSimple<t_CFloat> mp_Float;
		};

		template <typename t_CFloat>
		struct TCFloatConstants
		{
		private:
			static void fsp_Init_0(t_CFloat &_Float);
			static void fsp_Init_0_5(t_CFloat &_Float);
			static void fsp_Init_1(t_CFloat &_Float);
			static void fsp_Init_2(t_CFloat &_Float);
			static void fsp_Init_E(t_CFloat &_Float);
			static void fsp_Init_Pi(t_CFloat &_Float);
			static void fsp_Init_Sqrt2(t_CFloat &_Float);
			static void fsp_Init_Euler(t_CFloat &_Float);
			static void fsp_Init_GoldenRatio(t_CFloat &_Float);
			static void fsp_Init_Log10_2(t_CFloat &_Float);
			static void fsp_Init_Log2_10(t_CFloat &_Float);
			static void fsp_Init_Log10_E(t_CFloat &_Float);
			static void fsp_Init_LogE_10(t_CFloat &_Float);
			static void fsp_Init_Log2_E(t_CFloat &_Float);
			static void fsp_Init_LogE_2(t_CFloat &_Float);
			static void fsp_Init_Inf(t_CFloat &_Float);
			static void fsp_Init_NegInf(t_CFloat &_Float);
			static void fsp_Init_QNan(t_CFloat &_Float);
			static void fsp_Init_SNan(t_CFloat &_Float);
			static void fsp_Init_NegQNan(t_CFloat &_Float);
			static void fsp_Init_NegSNan(t_CFloat &_Float);

		public:
			static TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_0> ms_Zero;
			static TCFloatConstant<t_CFloat, fsp_Init_0_5> ms_Half;
			static TCFloatConstant<t_CFloat, fsp_Init_1> ms_One;
			static TCFloatConstant<t_CFloat, fsp_Init_2> ms_Two;
			static TCFloatConstant<t_CFloat, fsp_Init_E> ms_EulersNumber;
			static TCFloatConstant<t_CFloat, fsp_Init_Pi> ms_Pi;
			static TCFloatConstant<t_CFloat, fsp_Init_Sqrt2> ms_Sqrt2;
			static TCFloatConstant<t_CFloat, fsp_Init_Euler> ms_Euler;
			static TCFloatConstant<t_CFloat, fsp_Init_GoldenRatio> ms_GoldenRatio;
			static TCFloatConstant<t_CFloat, fsp_Init_Log10_2> ms_Log10_2;
			static TCFloatConstant<t_CFloat, fsp_Init_Log2_10> ms_Log2_10;
			static TCFloatConstant<t_CFloat, fsp_Init_Log10_E> ms_Log10_E;
			static TCFloatConstant<t_CFloat, fsp_Init_LogE_10> ms_LogE_10;
			static TCFloatConstant<t_CFloat, fsp_Init_Log2_E> ms_Log2_E;
			static TCFloatConstant<t_CFloat, fsp_Init_LogE_2> ms_LogE_2;
			static TCFloatConstant<t_CFloat, fsp_Init_Inf> ms_Inf;
			static TCFloatConstant<t_CFloat, fsp_Init_NegInf> ms_NegInf;
			static TCFloatConstant<t_CFloat, fsp_Init_QNan> ms_QNan;
			static TCFloatConstant<t_CFloat, fsp_Init_SNan> ms_SNan;
			static TCFloatConstant<t_CFloat, fsp_Init_NegQNan> ms_NegQNan;
			static TCFloatConstant<t_CFloat, fsp_Init_NegSNan> ms_NegSNan;
		};

		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_0> TCFloatConstants<t_CFloat>::ms_Zero = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_0_5> TCFloatConstants<t_CFloat>::ms_Half = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_1> TCFloatConstants<t_CFloat>::ms_One = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_2> TCFloatConstants<t_CFloat>::ms_Two = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_E> TCFloatConstants<t_CFloat>::ms_EulersNumber = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_Pi> TCFloatConstants<t_CFloat>::ms_Pi = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_Sqrt2> TCFloatConstants<t_CFloat>::ms_Sqrt2 = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_Euler> TCFloatConstants<t_CFloat>::ms_Euler = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_GoldenRatio> TCFloatConstants<t_CFloat>::ms_GoldenRatio = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_Log10_2> TCFloatConstants<t_CFloat>::ms_Log10_2 = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_Log2_10> TCFloatConstants<t_CFloat>::ms_Log2_10 = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_Log10_E> TCFloatConstants<t_CFloat>::ms_Log10_E = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_LogE_10> TCFloatConstants<t_CFloat>::ms_LogE_10 = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_Log2_E> TCFloatConstants<t_CFloat>::ms_Log2_E = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_LogE_2> TCFloatConstants<t_CFloat>::ms_LogE_2 = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_Inf> TCFloatConstants<t_CFloat>::ms_Inf = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_NegInf> TCFloatConstants<t_CFloat>::ms_NegInf = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_QNan> TCFloatConstants<t_CFloat>::ms_QNan = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_SNan> TCFloatConstants<t_CFloat>::ms_SNan = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_NegQNan> TCFloatConstants<t_CFloat>::ms_NegQNan = {DAggregateInit};
		template <typename t_CFloat>
		constinit TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fsp_Init_NegSNan> TCFloatConstants<t_CFloat>::ms_NegSNan = {DAggregateInit};

		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlace0(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlace0_5(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlace1(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlace2(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceE(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlacePi(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceSqrt2(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceEuler(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceGoldenRatio(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceLog10_2(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceLog2_10(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceLog10_E(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceLogE_10(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceLog2_E(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceLogE_2(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceInf(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceNegInf(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceQNan(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceSNan(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceNegQNan(tf_CFloat &_Float);
		template <typename tf_CFloat>
		static tf_CFloat &fg_FInPlaceNegSNan(tf_CFloat &_Float);
		template <typename tf_CFloat, typename tf_CInteger>
		static tf_CFloat &fg_FInPlaceFromInt(tf_CFloat &_Float, tf_CInteger const &_Int);
		template <typename tf_CFloat, typename tf_CIntegerSign, typename tf_CIntegerExponent, typename tf_CMantissoExponent>
		auto fg_FInPlaceFromAllRound(tf_CFloat &_Float, tf_CIntegerSign const &_Sign, tf_CIntegerExponent const &_Exponent, tf_CMantissoExponent const &_Mantissa, aint _AtleastExtraBits)
			-> tf_CFloat &
		;

		template <typename tf_CFloat>
		tf_CFloat fg_F0();
		template <typename tf_CFloat>
		tf_CFloat fg_F0_5();
		template <typename tf_CFloat>
		tf_CFloat fg_F1();
		template <typename tf_CFloat>
		tf_CFloat fg_F2();
		template <typename tf_CFloat>
		tf_CFloat fg_FE();
		template <typename tf_CFloat>
		tf_CFloat fg_FPi();
		template <typename tf_CFloat>
		tf_CFloat fg_FSqrt2();
		template <typename tf_CFloat>
		tf_CFloat fg_FEuler();
		template <typename tf_CFloat>
		tf_CFloat fg_FGoldenRatio();
		template <typename tf_CFloat>
		tf_CFloat fg_FLog10_2();
		template <typename tf_CFloat>
		tf_CFloat fg_FLog2_10();
		template <typename tf_CFloat>
		tf_CFloat fg_FLog10_E();
		template <typename tf_CFloat>
		tf_CFloat fg_FLogE_10();
		template <typename tf_CFloat>
		tf_CFloat fg_FLog2_E();
		template <typename tf_CFloat>
		tf_CFloat fg_FLogE_2();
		template <typename tf_CFloat>
		tf_CFloat fg_FInf();
		template <typename tf_CFloat>
		tf_CFloat fg_FNegInf();
		template <typename tf_CFloat>
		tf_CFloat fg_FQNan();
		template <typename tf_CFloat>
		tf_CFloat fg_FSNan();
		template <typename tf_CFloat>
		tf_CFloat fg_FNegQNan();
		template <typename tf_CFloat>
		tf_CFloat fg_FNegSNan();

		template <typename tf_CFloat, typename tf_CInteger>
		static tf_CFloat fg_FFromInt(tf_CInteger const &_Int);
		template <typename tf_CFloat, typename tf_CIntegerSign, typename tf_CIntegerExponent, typename tf_CMantissoExponent>
		tf_CFloat fg_FFromAllRound(tf_CIntegerSign const &_Sign, tf_CIntegerExponent const &_Exponent, tf_CMantissoExponent const &_Mantissa, aint _AtleastExtraBits);

		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FSignBits(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FExponentBits(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FMantissaBits(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FSign(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FExponent(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FMantissa(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FDenormalizedMantissa(tf_CFloat const &_Float);

		template <typename tf_CFloat>
		bool fg_FIsNaN(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		bool fg_FIsQNaN(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		bool fg_FIsSNaN(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		bool fg_FIsInfinity(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		bool fg_FIsInvalid(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		bool fg_FIsDenormalized(tf_CFloat const &_Float);

		template <typename tf_CInteger, typename tf_CFloat>
		tf_CInteger fg_FToInt(tf_CFloat const &_Float);
		template <typename tf_CInteger, typename tf_CFloat>
		tf_CInteger fg_FToIntRound(tf_CFloat const &_Float);
		template <typename tf_CInteger, typename tf_CFloat>
		tf_CInteger fg_FToIntRoundTowardZero(tf_CFloat const &_Float);

		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FToInt(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageUnsignedInteger fg_FToUnsignedInt(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FToIntRound(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageUnsignedInteger fg_FToUnsignedIntRound(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageInteger fg_FToIntRoundTowardZero(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		typename TCFloatTraits<tf_CFloat>::CStorageUnsignedInteger fg_FToUnsignedIntRoundTowardZero(tf_CFloat const &_Float);

		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat &fg_FInPlaceSetSignBits(tf_CFloat &_Float, tf_CInteger const &_Value);

		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat &fg_FInPlaceSetExponentBits(tf_CFloat &_Float, tf_CInteger const &_Value);

		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat &fg_FInPlaceSetMantissaBits(tf_CFloat &_Float, tf_CInteger const &_Value);

		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat &fg_FInPlaceSetSign(tf_CFloat &_Float, tf_CInteger const &_Value);

		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat &fg_FInPlaceSetExponent(tf_CFloat &_Float, tf_CInteger const &_Value);

		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat &fg_FInPlaceSetMantissa(tf_CFloat &_Float, tf_CInteger const &_Value);

		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 &fg_FInPlaceConvertRoundUp(tf_CFloat0 &_Float, tf_CFloat1 const &_ConvertFrom);

		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 &fg_FInPlaceConvert(tf_CFloat0 &_Float, tf_CFloat1 const &_ConvertFrom);

		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceSin(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceCos(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceTan(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceSinH(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceCosH(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceTanH(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceArcSin(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceArcCos(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceArcTan(tf_CFloat &_Float);
		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 &fg_FInPlaceArcTan(tf_CFloat0 &_Float, tf_CFloat1 const &_Source);

		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceArcTan(tf_CFloat &_Float, tf_CFloat const &_Source);

		template <typename tf_CFloat>
		tf_CFloat &fg_FExpN(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceLogN(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceExp10(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceLog10(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceExp2(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceLog2(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceSqrt(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceSqr(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceFloor(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceFraction(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceCeil(tf_CFloat &_Float);
		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceAbs(tf_CFloat &_Float);

		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceExp(tf_CFloat &_Float, tf_CFloat const &_Base);
		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 &fg_FInPlaceExp(tf_CFloat0 &_Float, tf_CFloat1 const &_Base);

		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceLog(tf_CFloat &_Float, tf_CFloat const &_Base);
		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 &fg_FInPlaceLog(tf_CFloat0 &_Float, tf_CFloat1 const &_Base);

		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlacePow(tf_CFloat &_Float, tf_CFloat const &_Power);
		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 &fg_FInPlacePow(tf_CFloat0 &_Float, tf_CFloat1 const &_Power);

		template <typename tf_CFloat>
		tf_CFloat &fg_FInPlaceMod(tf_CFloat &_Float, tf_CFloat const &_Modulu);
		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 &fg_FInPlaceMod(tf_CFloat0 &_Float, tf_CFloat1 const &_Modulu);

		// Non-inplace

		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat fg_FSetSignBits(tf_CFloat const &_Float, tf_CInteger _Value);
		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat fg_FSetExponentBits(tf_CFloat const &_Float, tf_CInteger _Value);
		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat fg_FSetMantissaBits(tf_CFloat const &_Float, tf_CInteger _Value);
		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat fg_FSetSign(tf_CFloat const &_Float, tf_CInteger _Value);
		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat fg_FSetExponent(tf_CFloat const &_Float, tf_CInteger _Value);
		template <typename tf_CFloat, typename tf_CInteger>
		tf_CFloat fg_FSetMantissa(tf_CFloat const &_Float, tf_CInteger _Value);
		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 fg_FConvertRoundUp(tf_CFloat1 const &_ConvertFrom);
		template <typename tf_CFloat0, typename tf_CFloat1>
		tf_CFloat0 fg_FConvert(tf_CFloat1 const &_ConvertFrom);

		template <typename tf_CFloat>
		tf_CFloat fg_FSin(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FCos(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FTan(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FSinH(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FCosH(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FTanH(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FArcSin(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FArcCos(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FArcTan(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FArcTan(tf_CFloat const &_Float, tf_CFloat const &_Source);
		template <typename tf_CFloat0, typename tf_CFloat1>
		typename TCFloatCombinedType<tf_CFloat0, tf_CFloat1>::CType fg_FArcTan(tf_CFloat0 const &_Float, tf_CFloat1 const &_Source);

		template <typename tf_CFloat>
		tf_CFloat fg_FExpN(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FLogN(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FExp10(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FLog10(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FExp2(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FLog2(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FSqrt(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FSqr(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FFloor(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FFraction(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FCeil(tf_CFloat const &_Float);
		template <typename tf_CFloat>
		tf_CFloat fg_FAbs(tf_CFloat const &_Float);

		template <typename tf_CFloat>
		tf_CFloat fg_FExp(tf_CFloat const &_Float, tf_CFloat const &_Base);
		template <typename tf_CFloat>
		tf_CFloat fg_FLog(tf_CFloat const &_Float, tf_CFloat const &_Base);
		template <typename tf_CFloat>
		tf_CFloat fg_FPow(tf_CFloat const &_Float, tf_CFloat const &_Power);
		template <typename tf_CFloat>
		tf_CFloat fg_FMod(tf_CFloat const &_Float, tf_CFloat const &_Modulu);
	}
}

#include "Test_Malterlib_Numeric_Float.hpp"
