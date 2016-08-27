// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

namespace NMib
{
	namespace NMath
	{


#define DMibMathImplementNativeFloat(_Native, _TCFloat) \
		template <>\
		class TCFloatFromNative<_Native>\
		{\
		public:\
			typedef _TCFloat CType;\
		};

		DMibMathImplementNativeFloat(pfp32, CIEEEFloat32);
		DMibMathImplementNativeFloat(pfp64, CIEEEFloat64);

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		class TCFloatFromNative<NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
		{
		public:
			typedef NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CType;
		};

		template <typename t_CFloat>
		class TCFloatTraits : public TCFloatTraits<typename TCFloatFromNative<t_CFloat>::CType>
		{
		public:
		};

		template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, typename t_CImplicitFloat, bint t_bDummyOptimize, typename t_CIntegerStorage>
		class TCFloatTraits<NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>>
		{
			typedef NMib::NMath::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage> CFloat;
		public:
			typedef typename CFloat::CInteger CStorageInteger;
			typedef typename CFloat::CDoubleInteger CStorageInteger_x2;

			typedef typename CFloat::CUnsignedInteger CStorageUnsignedInteger;
			typedef typename CFloat::CDoubleUnsignedInteger CStorageUnsignedInteger_x2;

			typedef typename CFloat::CImplicitFloat CFundamentalFloat;

			bint const static ms_bHasFundamentalFloat = !NTraits::TCIsSame<CFundamentalFloat, NMib::NMath::CNoImplicit>::mc_Value;
		};

		template <typename t_CFloat>
		class TCNativeFromFloat
		{
		public:

			typename TCChooseType<TCFloatTraits<t_CFloat>::ms_bHasFundamentalFloat, typename TCFloatTraits<t_CFloat>::CFundamentalFloat, t_CFloat>::CFloat CType;
			
		};


		template <typename t_CFloat0, typename t_CFloat1>
		class TCFloatCombinedType
		{
		public:
			typedef typename NTraits::TCLargestType<t_CFloat0, t_CFloat1>::CType CType;
		};

		template <typename t_CFloat, void (&f_Init)(t_CFloat &_Float)>
		class TCFloatConstant
		{
		public:
#ifndef DMibNoAggregateConstexpr
			constexpr TCFloatConstant(EAggregateInitialization _Init)
				: mp_bInit{}
				, mp_Float{_Init}
			{
			}
#endif
			bint mp_bInit;
			NAggregate::TCAggregateSimple<t_CFloat> mp_Float;
			operator const t_CFloat & ()
			{
				if (!mp_bInit)
				{
					mp_Float.f_Construct();
					f_Init(*mp_Float);
					mp_bInit = true;
				}
				return *mp_Float;
			}
		};

		template <typename t_CFloat>
		class TCFloatConstants
		{
			static void fg_Init_0(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_0();
			}
			static void fg_Init_0_5(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_0_5();
			}
			static void fg_Init_1(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_1();
			}
			static void fg_Init_2(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_2();
			}
			static void fg_Init_E(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_E();
			}
			static void fg_Init_Pi(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_Pi();
			}
			static void fg_Init_Sqrt2(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_Sqrt2();
			}
			static void fg_Init_Euler(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_Euler();
			}
			static void fg_Init_GoldenRatio(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_GoldenRatio();
			}
			static void fg_Init_Log10_2(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_Log10_2();
			}
			static void fg_Init_Log2_10(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_Log2_10();
			}
			static void fg_Init_Log10_E(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_Log10_E();
			}
			static void fg_Init_LogE_10(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_LogE_10();
			}
			static void fg_Init_Log2_E(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_Log2_E();
			}
			static void fg_Init_LogE_2(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_LogE_2();
			}
			static void fg_Init_Inf(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_Inf();
			}
			static void fg_Init_NegInf(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_NegInf();
			}
			static void fg_Init_QNan(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_QNan();
			}
			static void fg_Init_SNan(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_SNan();
			}
			static void fg_Init_NegQNan(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_NegQNan();
			}
			static void fg_Init_NegSNan(t_CFloat &_Float)
			{
				typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
				((CFloat &)_Float).fp_Set_NegSNan();
			}
		public:
			static TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_0> ms_0;
			static TCFloatConstant<t_CFloat, fg_Init_0_5> ms_0_5;
			static TCFloatConstant<t_CFloat, fg_Init_1> ms_1;
			static TCFloatConstant<t_CFloat, fg_Init_2> ms_2;
			static TCFloatConstant<t_CFloat, fg_Init_E> ms_E;
			static TCFloatConstant<t_CFloat, fg_Init_Pi> ms_Pi;
			static TCFloatConstant<t_CFloat, fg_Init_Sqrt2> ms_Sqrt2;
			static TCFloatConstant<t_CFloat, fg_Init_Euler> ms_Euler;
			static TCFloatConstant<t_CFloat, fg_Init_GoldenRatio> ms_GoldenRatio;
			static TCFloatConstant<t_CFloat, fg_Init_Log10_2> ms_Log10_2;
			static TCFloatConstant<t_CFloat, fg_Init_Log2_10> ms_Log2_10;
			static TCFloatConstant<t_CFloat, fg_Init_Log10_E> ms_Log10_E;
			static TCFloatConstant<t_CFloat, fg_Init_LogE_10> ms_LogE_10;
			static TCFloatConstant<t_CFloat, fg_Init_Log2_E> ms_Log2_E;
			static TCFloatConstant<t_CFloat, fg_Init_LogE_2> ms_LogE_2;
			static TCFloatConstant<t_CFloat, fg_Init_Inf> ms_Inf;
			static TCFloatConstant<t_CFloat, fg_Init_NegInf> ms_NegInf;
			static TCFloatConstant<t_CFloat, fg_Init_QNan> ms_QNan;
			static TCFloatConstant<t_CFloat, fg_Init_SNan> ms_SNan;
			static TCFloatConstant<t_CFloat, fg_Init_NegQNan> ms_NegQNan;
			static TCFloatConstant<t_CFloat, fg_Init_NegSNan> ms_NegSNan;

		};

		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_0> TCFloatConstants<t_CFloat>::ms_0 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_0_5> TCFloatConstants<t_CFloat>::ms_0_5 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_1> TCFloatConstants<t_CFloat>::ms_1 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_2> TCFloatConstants<t_CFloat>::ms_2 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_E> TCFloatConstants<t_CFloat>::ms_E = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_Pi> TCFloatConstants<t_CFloat>::ms_Pi = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_Sqrt2> TCFloatConstants<t_CFloat>::ms_Sqrt2 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_Euler> TCFloatConstants<t_CFloat>::ms_Euler = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_GoldenRatio> TCFloatConstants<t_CFloat>::ms_GoldenRatio = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_Log10_2> TCFloatConstants<t_CFloat>::ms_Log10_2 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_Log2_10> TCFloatConstants<t_CFloat>::ms_Log2_10 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_Log10_E> TCFloatConstants<t_CFloat>::ms_Log10_E = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_LogE_10> TCFloatConstants<t_CFloat>::ms_LogE_10 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_Log2_E> TCFloatConstants<t_CFloat>::ms_Log2_E = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_LogE_2> TCFloatConstants<t_CFloat>::ms_LogE_2 = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_Inf> TCFloatConstants<t_CFloat>::ms_Inf = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_NegInf> TCFloatConstants<t_CFloat>::ms_NegInf = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_QNan> TCFloatConstants<t_CFloat>::ms_QNan = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_SNan> TCFloatConstants<t_CFloat>::ms_SNan = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_NegQNan> TCFloatConstants<t_CFloat>::ms_NegQNan = {DAggregateInit};
		template <typename t_CFloat>
		TCFloatConstant<t_CFloat, TCFloatConstants<t_CFloat>::fg_Init_NegSNan> TCFloatConstants<t_CFloat>::ms_NegSNan = {DAggregateInit};
		
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlace0(t_CFloat &_Float)
		{
			_Float = TCFloatConstants<t_CFloat>::ms_0;
		}
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlace0_5(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlace1(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlace2(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceE(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlacePi(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceSqrt2(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceEuler(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceGoldenRatio(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceLog10_2(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceLog2_10(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceLog10_E(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceLogE_10(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceLog2_E(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceLogE_2(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceInf(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceNegInf(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceQNan(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceSNan(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceNegQNan(t_CFloat &_Float);
		template <typename t_CFloat>
		static t_CFloat &fg_FInPlaceNegSNan(t_CFloat &_Float);
		template <typename t_CFloat, typename t_CInteger>
		static t_CFloat &fg_FInPlaceFromInt(t_CFloat &_Float, const t_CInteger &_Int);
		template <typename t_CFloat, typename t_CIntegerSign, typename t_CIntegerExponent, typename t_CMantissoExponent>
		t_CFloat &fg_FInPlaceFromAllRound(t_CFloat &_Float, const t_CIntegerSign &_Sign, const t_CIntegerExponent &_Exponent, const t_CMantissoExponent &_Mantissa, aint _AtleastExtraBits);

		template <typename t_CFloat>
		t_CFloat fg_F0()
		{
			return TCFloatConstants<t_CFloat>::ms_0;
		}
		template <typename t_CFloat>
		t_CFloat fg_F0_5()
		{
			return TCFloatConstants<t_CFloat>::ms_0_5;
		}
		template <typename t_CFloat>
		t_CFloat fg_F1()
		{
			return TCFloatConstants<t_CFloat>::ms_1;
		}
		template <typename t_CFloat>
		t_CFloat fg_F2()
		{
			return TCFloatConstants<t_CFloat>::ms_2;
		}
		template <typename t_CFloat>
		t_CFloat fg_FE()
		{
			return TCFloatConstants<t_CFloat>::ms_E;
		}
		template <typename t_CFloat>
		t_CFloat fg_FPi()
		{
			return TCFloatConstants<t_CFloat>::ms_Pi;
		}
		template <typename t_CFloat>
		t_CFloat fg_FSqrt2()
		{
			return TCFloatConstants<t_CFloat>::ms_Sqrt2;
		}
		template <typename t_CFloat>
		t_CFloat fg_FEuler()
		{
			return TCFloatConstants<t_CFloat>::ms_Euler;
		}
		template <typename t_CFloat>
		t_CFloat fg_FGoldenRatio()
		{
			return TCFloatConstants<t_CFloat>::ms_GoldenRatio;
		}
		template <typename t_CFloat>
		t_CFloat fg_FLog10_2()
		{
			return TCFloatConstants<t_CFloat>::ms_Log10_2;
		}
		template <typename t_CFloat>
		t_CFloat fg_FLog2_10()
		{
			return TCFloatConstants<t_CFloat>::ms_Log2_10;
		}
		template <typename t_CFloat>
		t_CFloat fg_FLog10_E()
		{
			return TCFloatConstants<t_CFloat>::ms_Log10_E;
		}
		template <typename t_CFloat>
		t_CFloat fg_FLogE_10()
		{
			return TCFloatConstants<t_CFloat>::ms_LogE_10;
		}
		template <typename t_CFloat>
		t_CFloat fg_FLog2_E()
		{
			return TCFloatConstants<t_CFloat>::ms_Log2_E;
		}
		template <typename t_CFloat>
		t_CFloat fg_FLogE_2()
		{
			return TCFloatConstants<t_CFloat>::ms_LogE_2;
		}
		template <typename t_CFloat>
		t_CFloat fg_FInf()
		{
			return TCFloatConstants<t_CFloat>::ms_Inf;
		}
		template <typename t_CFloat>
		t_CFloat fg_FNegInf()
		{
			return TCFloatConstants<t_CFloat>::ms_NegInf;
		}
		template <typename t_CFloat>
		t_CFloat fg_FQNan()
		{
			return TCFloatConstants<t_CFloat>::ms_QNan;
		}
		template <typename t_CFloat>
		t_CFloat fg_FSNan()
		{
			return TCFloatConstants<t_CFloat>::ms_SNan;
		}
		template <typename t_CFloat>
		t_CFloat fg_FNegQNan()
		{
			return TCFloatConstants<t_CFloat>::ms_NegQNan;
		}
		template <typename t_CFloat>
		t_CFloat fg_FNegSNan()
		{
			return TCFloatConstants<t_CFloat>::ms_NegSNan;
		}
		
		
		template <typename t_CFloat, typename t_CInteger>
		static t_CFloat fg_FFromInt(const t_CInteger &_Int);
		template <typename t_CFloat, typename t_CIntegerSign, typename t_CIntegerExponent, typename t_CMantissoExponent>
		t_CFloat fg_FFromAllRound(t_CIntegerSign const &_Sign, t_CIntegerExponent const &_Exponent, t_CMantissoExponent const &_Mantissa, aint _AtleastExtraBits);

		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FSignBits(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FExponentBits(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FMantissaBits(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FSign(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FExponent(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FMantissa(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FDenormalizedMantissa(t_CFloat const &_Float);

		template <typename t_CFloat>
		bint fg_FIsNaN(t_CFloat const &_Float);
		template <typename t_CFloat>
		bint fg_FIsQNaN(t_CFloat const &_Float);
		template <typename t_CFloat>
		bint fg_FIsSNaN(t_CFloat const &_Float);
		template <typename t_CFloat>
		bint fg_FIsInfinity(t_CFloat const &_Float);
		template <typename t_CFloat>
		bint fg_FIsInvalid(t_CFloat const &_Float);
		template <typename t_CFloat>
		bint fg_FIsDenormalized(t_CFloat const &_Float);

		template <typename t_CInteger, typename t_CFloat>
		t_CInteger fg_FToInt(t_CFloat const &_Float);
		template <typename t_CInteger, typename t_CFloat>
		t_CInteger fg_FToIntRound(t_CFloat const &_Float);
		template <typename t_CInteger, typename t_CFloat>
		t_CInteger fg_FToIntRoundTowardZero(t_CFloat const &_Float);

		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FToInt(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageUnsignedInteger fg_FToUnsignedInt(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FToIntRound(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageUnsignedInteger fg_FToUnsignedIntRound(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageInteger fg_FToIntRoundTowardZero(t_CFloat const &_Float);
		template <typename t_CFloat>
		typename TCFloatTraits<t_CFloat>::CStorageUnsignedInteger fg_FToUnsignedIntRoundTowardZero(t_CFloat const &_Float);

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat &fg_FInPlaceSetSignBits(t_CFloat &_Float, const t_CInteger &_Value)
		{
			typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
			CFloat &Float = (CFloat &)_Float;
			Float.f_SetSignBits(_Value);
			return _Float;
		}

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat &fg_FInPlaceSetExponentBits(t_CFloat &_Float, const t_CInteger &_Value);

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat &fg_FInPlaceSetMantissaBits(t_CFloat &_Float, const t_CInteger &_Value);

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat &fg_FInPlaceSetSign(t_CFloat &_Float, const t_CInteger &_Value);

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat &fg_FInPlaceSetExponent(t_CFloat &_Float, const t_CInteger &_Value);

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat &fg_FInPlaceSetMantissa(t_CFloat &_Float, const t_CInteger &_Value);


		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 &fg_FInPlaceConvertRoundUp(t_CFloat0 &_Float, const t_CFloat1 &_ConvertFrom);

		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 &fg_FInPlaceConvert(t_CFloat0 &_Float, const t_CFloat1 &_ConvertFrom);

		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceSin(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceCos(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceTan(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceSinH(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceCosH(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceTanH(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceArcSin(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceArcCos(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceArcTan(t_CFloat &_Float);
		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 &fg_FInPlaceArcTan(t_CFloat0 &_Float, const t_CFloat1 &_Source)
		{
			return fg_FInPlaceArcTan(_Float, (t_CFloat0)_Source);
		}
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceArcTan(t_CFloat &_Float, const t_CFloat &_Source);

		template <typename t_CFloat>
		t_CFloat &fg_FExpN(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceLogN(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceExp10(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceLog10(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceExp2(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceLog2(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceSqrt(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceSqr(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceFloor(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceFraction(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceCeil(t_CFloat &_Float);
		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceAbs(t_CFloat &_Float);

		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceExp(t_CFloat &_Float, const t_CFloat &_Base);
		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 &fg_FInPlaceExp(t_CFloat0 &_Float, const t_CFloat1 &_Base)
		{
			return fg_FInPlaceExp(_Float, (t_CFloat0)_Base);
		}

		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceLog(t_CFloat &_Float, const t_CFloat &_Base);
		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 &fg_FInPlaceLog(t_CFloat0 &_Float, const t_CFloat1 &_Base)
		{
			return fg_FInPlaceLog(_Float, (t_CFloat0)_Base);
		}

		template <typename t_CFloat>
		t_CFloat &fg_FInPlacePow(t_CFloat &_Float, const t_CFloat &_Power);
		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 &fg_FInPlacePow(t_CFloat0 &_Float, const t_CFloat1 &_Power)
		{
			return fg_FInPlacePow(_Float, (t_CFloat0)_Power);
		}

		template <typename t_CFloat>
		t_CFloat &fg_FInPlaceMod(t_CFloat &_Float, const t_CFloat &_Modulu);
		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 &fg_FInPlaceMod(t_CFloat0 &_Float, const t_CFloat1 &_Modulu)
		{
			return fg_FInPlaceMod(_Float, (t_CFloat0)_Modulu);
		}

		// Non-inplace

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat fg_FSetSignBits(const t_CFloat &_Float, t_CInteger _Value)
		{
			t_CFloat Ret = _Float;
			fg_FInPlaceSetSignBits(Ret, _Value);
			return Ret;
		}

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat fg_FSetExponentBits(t_CFloat const &_Float, t_CInteger _Value)
		{
			t_CFloat Ret = _Float;
			fg_FInPlaceSetExponentBits(Ret, _Value);
			return Ret;
		}

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat fg_FSetMantissaBits(t_CFloat const &_Float, t_CInteger _Value)
		{
			t_CFloat Ret = _Float;
			fg_FInPlaceSetMantissaBits(Ret, _Value);
			return Ret;
		}

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat  fg_FSetSign(t_CFloat const &_Float, t_CInteger _Value)
		{
			t_CFloat Ret = _Float;
			fg_FInPlaceSetSign(Ret, _Value);
			return Ret;
		}

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat fg_FSetExponent(t_CFloat const &_Float, t_CInteger _Value)
		{
			t_CFloat Ret = _Float;
			fg_FInPlaceSetExponent(Ret, _Value);
			return Ret;
		}

		template <typename t_CFloat, typename t_CInteger>
		t_CFloat  fg_FSetMantissa(t_CFloat const &_Float, t_CInteger _Value)
		{
			t_CFloat Ret = _Float;
			fg_FInPlaceSetMantissa(Ret, _Value);
			return Ret;
		}

		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 fg_FConvertRoundUp(const t_CFloat1 &_ConvertFrom)
		{
			t_CFloat0 Ret;
			fg_FInPlaceConvertRoundUp(Ret, _ConvertFrom);
			return Ret;
		}

		template <typename t_CFloat0, typename t_CFloat1>
		t_CFloat0 fg_FConvert(const t_CFloat1 &_ConvertFrom)
		{
			t_CFloat0 Ret;
			fg_FInPlaceConvert(Ret, _ConvertFrom);
			return Ret;
		}

		template <typename t_CFloat>
		t_CFloat fg_FSin(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FCos(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FTan(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FSinH(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FCosH(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FTanH(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FArcSin(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FArcCos(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FArcTan(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FArcTan(t_CFloat const &_Float, const t_CFloat &_Source)
		{
			typedef typename TCFloatFromNative<t_CFloat>::CType CFloat;
			const CFloat &Float = _Float;
			const CFloat &Source = _Source;
			return Float.f_ArcTan(Source).f_Get();
		}
		template <typename t_CFloat0, typename t_CFloat1>
		typename TCFloatCombinedType<t_CFloat0, t_CFloat1>::CType fg_FArcTan(t_CFloat0 const &_Float, const t_CFloat1 &_Source)
		{
			typedef typename TCFloatCombinedType<t_CFloat0, t_CFloat1>::CType CCombinedFloat;
			CCombinedFloat Float{_Float};
			CCombinedFloat Source{_Source};
			return fg_FArcTan(Float, Source);
		}

		template <typename t_CFloat>
		t_CFloat fg_FExpN(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FLogN(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FExp10(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FLog10(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FExp2(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FLog2(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FSqrt(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FSqr(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FFloor(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FFraction(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FCeil(t_CFloat const &_Float);
		template <typename t_CFloat>
		t_CFloat fg_FAbs(t_CFloat const &_Float);

		template <typename t_CFloat>
		t_CFloat fg_FExp(t_CFloat const &_Float, const t_CFloat &_Base);
		template <typename t_CFloat>
		t_CFloat fg_FLog(t_CFloat const &_Float, const t_CFloat &_Base);
		template <typename t_CFloat>
		t_CFloat fg_FPow(t_CFloat const &_Float, const t_CFloat &_Power);
		template <typename t_CFloat>
		t_CFloat fg_FMod(t_CFloat const &_Float, const t_CFloat &_Modulu);
	}
}
