// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Numeric/fp8>
#include <Mib/Numeric/fp16>
#include <Mib/Numeric/fp32>
#include <Mib/Numeric/fp64>
#include <Mib/Numeric/fp80>
#include <Mib/Numeric/fp128>
#include <Mib/Numeric/fp256>
#include <Mib/Numeric/fp512>
#include <Mib/Numeric/fp1024>
#include <Mib/Numeric/fp2048>
#include <Mib/Numeric/fp4096>

#include <cmath>
#include <limits>
#include <float.h>

#include "Test_Malterlib_Numeric_Float.h"

#ifdef DCompiler_MSVC
#pragma float_control(precise, on)
#pragma fp_contract(off)
#pragma fenv_access(on)
#endif

using namespace NMib::NNumeric;
using namespace NMib::NTraits;
namespace
{
	class CFloat_Tests : public NMib::NTest::CTest
	{
	public:

		template <template <typename t_CFloat00> class t_CTestTemplate>
		static void fs_TestAll()
		{
			{
				DMibTestPath("fp8");
				t_CTestTemplate<fp8>()();
			}
			{
				DMibTestPath("fp16");
				t_CTestTemplate<fp16>()();
			}
			{
				DMibTestPath("fp32");
				t_CTestTemplate<fp32>()();
			}
			{
				DMibTestPath("fp32Emu");
				t_CTestTemplate<CIEEEFloat32Emu>()();
			}
			{
				DMibTestPath("fp64");
				t_CTestTemplate<fp64>()();
			}
			{
				DMibTestPath("fp64Emu");
				t_CTestTemplate<CIEEEFloat64Emu>()();
			}
			{
				DMibTestPath("fp80");
				t_CTestTemplate<fp80>()();
			}
			{
				DMibTestPath("fp80Emu");
				t_CTestTemplate<CIEEEFloat80Emu>()();
			}
			{
				DMibTestPath("fp128");
				t_CTestTemplate<fp128>()();
			}
			{
				DMibTestPath("fp256");
				t_CTestTemplate<fp256>()();
			}
/*			{
				DMibTestPath("fp512");
				t_CTestTemplate<fp512>()();
			}
			{
				DMibTestPath("fp1024");
				t_CTestTemplate<fp1024>()();
			}
			{
				DMibTestPath("fp2048");
				t_CTestTemplate<fp2048>()();
			}
			{
				DMibTestPath("fp4096");
				t_CTestTemplate<fp4096>()();
			}*/
		}

		template <typename t_CFloat>
		class CConstants
		{
		public:
			using CSmallestType = TCSmallestType<t_CFloat, fp64>;

			template <typename t_CFrom>
			CSmallestType f_Cnv(const t_CFrom &_From)
			{
				return NMib::fg_Convert<CSmallestType>(_From);
			}

			void operator() ()
			{
				DMibTestSuite("Constants")
				{
					DMibExpect(f_Cnv(fg_F0<t_CFloat>()), ==, f_Cnv(0.0));
					DMibExpect(f_Cnv(fg_F0_5<t_CFloat>()), ==, f_Cnv(0.5));
					DMibExpect(f_Cnv(fg_F1<t_CFloat>()), ==, f_Cnv(1.0));
					DMibExpect(f_Cnv(fg_F2<t_CFloat>()), ==, f_Cnv(2.0));
					DMibExpect(f_Cnv(fg_FPi<t_CFloat>()), ==, f_Cnv(3.1415926535897932384626433832795028841971693));
					DMibExpect(f_Cnv(fg_FSqrt2<t_CFloat>()), ==, f_Cnv(1.4142135623730950488016887242096980785696718));
					DMibExpect(f_Cnv(fg_FE<t_CFloat>()), ==, f_Cnv(2.7182818284590452353602874713526624977572470936999));
					// Euler too slow currently
					//DMibExpect(f_Cnv(fg_FEuler<t_CFloat>()), ==, DMibExpr(f_Cnv(0.57721566490153286060651209008240243104215933593992));
					DMibExpect(f_Cnv(fg_FGoldenRatio<t_CFloat>()), ==, f_Cnv(1.61803398874989484820458683436563811772030));
					DMibExpect(f_Cnv(fg_FLog10_2<t_CFloat>()), ==, f_Cnv(0.3010299956639811952137388947244930267681898814));
					DMibExpect(f_Cnv(fg_FLog2_10<t_CFloat>()), ==, f_Cnv(3.3219280948873623478703194294893901758648313930));
					DMibExpect(f_Cnv(fg_FLog10_E<t_CFloat>()), ==, f_Cnv(0.43429448190325182765112891891660508229439700580366));
					DMibExpect(f_Cnv(fg_FLogE_10<t_CFloat>()), ==, f_Cnv(2.3025850929940456840179914546843642076011014886287));
					DMibExpect(f_Cnv(fg_FLog2_E<t_CFloat>()), ==, f_Cnv(1.4426950408889634073599246810018921374266459541529));
					DMibExpect(f_Cnv(fg_FLogE_2<t_CFloat>()), ==, f_Cnv(0.69314718055994530941723212145817656807550013436025));
					DMibExpect(f_Cnv(fg_FInf<t_CFloat>()), ==, f_Cnv(fp64::fs_Inf()));
					DMibExpect(f_Cnv(fg_FNegInf<t_CFloat>()), ==, f_Cnv(fp64::fs_NegInf()));
					DMibExpect(f_Cnv(fg_FQNan<t_CFloat>()), !=, f_Cnv(fp64::fs_QNan()));
					DMibExpect(f_Cnv(fg_FSNan<t_CFloat>()), !=, f_Cnv(fp64::fs_SNan()));
					DMibExpect(f_Cnv(fg_FNegQNan<t_CFloat>()), !=, f_Cnv(fp64::fs_NegQNan()));
					DMibExpect(f_Cnv(fg_FNegSNan<t_CFloat>()), !=, f_Cnv(fp64::fs_NegSNan()));
				};
			}
		};

		template <typename t_CFloat>
		class CMultiply
		{
		public:
			void operator() ()
			{
				DMibExpect(t_CFloat::fs_2() * t_CFloat::fs_2(), ==, t_CFloat(fp64(4.0)));

				umint ExpectedBits = 1;
				if (umint(t_CFloat::mc_MantissaBits) > umint(fp64::mc_MantissaBits))
					ExpectedBits = (t_CFloat::mc_MantissaBits - fp64::mc_MantissaBits) - 1;

				auto fCheckValue = [&](NMib::NStr::CStr const &_Desc, double _Left, double _Right)
					{
						DMibTestPath(_Desc);
						volatile double Left = _Left;
						volatile double Right = _Right;
						t_CFloat Actual = (t_CFloat(fp64(double(Left))) * t_CFloat(fp64(double(Right))));
						t_CFloat Expected = t_CFloat(fp64(double(Left * Right)));
						DMibExpectTrue(Actual.f_AlmostEqual(Expected, ExpectedBits));
					}
				;
				fCheckValue("1/3*1/3", 1.0/3.0, 1.0/3.0);
				fCheckValue("2/3*2/3", 2.0/3.0, 2.0/3.0);
				fCheckValue("10*10", 10.0, 10.0);
			}
		};

		template <typename t_CFloat>
		class CDivide
		{
		public:
			void operator() ()
			{
				DMibExpect(t_CFloat::fs_2() / t_CFloat::fs_2(), ==, t_CFloat(fp64(1.0)));

				umint ExpectedBits = 1;
				if (umint(t_CFloat::mc_MantissaBits) > umint(fp64::mc_MantissaBits))
					ExpectedBits = (t_CFloat::mc_MantissaBits - fp64::mc_MantissaBits) - 1;

				auto fCheckValue = [&](NMib::NStr::CStr const &_Desc, double _Left, double _Right)
					{
						DMibTestPath(_Desc);
						volatile double Left = _Left;
						volatile double Right = _Right;
						t_CFloat Actual = (t_CFloat(fp64(double(Left))) / t_CFloat(fp64(double(Right))));
						t_CFloat Expected = t_CFloat(fp64(double(Left / Right)));
						DMibExpectTrue(Actual.f_AlmostEqual(Expected, ExpectedBits));
					}
				;

				fCheckValue("1/3", 2.0, 10);
				fCheckValue("1/10", 1.0, 10.0);
				fCheckValue("10/10", 10.0, 10.0);
				fCheckValue("1/0", 1.0, 0.0);
				fCheckValue("1/-0", 1.0, -0.0);
				fCheckValue("-1/0", -1.0, 0.0);
				fCheckValue("-1/-0", -1.0, -0.0);
			}
		};

		template <typename t_CFloat>
		class CInvalid
		{
		public:
			void operator() ()
			{
				DMibTest(DMibExpr(t_CFloat::fs_LimitMax()) * DMibExpr(t_CFloat::fs_2()) == DMibExpr(t_CFloat::fs_Inf()))(ETestFlag_NoValues);
				DMibTest(DMibExpr(t_CFloat::fs_LimitMin()) * DMibExpr(t_CFloat::fs_2()) == DMibExpr(t_CFloat::fs_NegInf()))(ETestFlag_NoValues);
			}
		};

		template <typename t_CFloatLeft>
		class TCConversion
		{
		public:
			template <typename t_CFloatRight>
			class CInner
			{
			public:
				void operator() ()
				{
#define DTestConversion(d_Name, d_Value, d_ExpectBiggerOperator, d_ExpectBigger, d_ExpectSmallerOperator, d_ExpectSmaller) \
					{\
						DMibTestPath("Construct");\
						auto d_Name = d_Value;\
						t_CFloatLeft Converted##d_Name{d_Name}; \
						if constexpr (t_CFloatLeft::mc_MantissaBits >= t_CFloatRight::mc_MantissaBits)\
							DMibExpect(Converted##d_Name, d_ExpectBiggerOperator, d_Name);\
						else\
							DMibExpect(Converted##d_Name, d_ExpectSmallerOperator, d_ExpectSmaller);\
					}\
					{\
						DMibTestPath("Assign");\
						auto d_Name = d_Value;\
						t_CFloatLeft Converted##d_Name;\
						Converted##d_Name = d_Name;\
						if constexpr (t_CFloatLeft::mc_MantissaBits >= t_CFloatRight::mc_MantissaBits)\
							DMibExpect(Converted##d_Name, d_ExpectBiggerOperator, d_Name);\
						else\
							DMibExpect(Converted##d_Name, d_ExpectSmallerOperator, d_ExpectSmaller);\
					}

					DTestConversion(SmallestDenormal, t_CFloatRight::fs_SmallestDenormal(), ==, SmallestDenormal, ==, t_CFloatLeft::fs_0());
					DTestConversion(NegSmallestDenormal, t_CFloatRight::fs_NegSmallestDenormal(), ==, NegSmallestDenormal, ==, -t_CFloatLeft::fs_0());
					if (t_CFloatLeft::mc_MantissaBits != t_CFloatRight::mc_MantissaBits && umint(t_CFloatLeft::mc_ExponentBits) == umint(t_CFloatRight::mc_ExponentBits))
					{
						DTestConversion(Smallest, t_CFloatRight::fs_Smallest(), ==, Smallest, ==, Smallest);
						DTestConversion(NegSmallest, t_CFloatRight::fs_NegSmallest(), ==, NegSmallest, ==, NegSmallest);
					}
					else
					{
						DTestConversion(Smallest, t_CFloatRight::fs_Smallest(), ==, Smallest, ==, t_CFloatLeft::fs_0());
						DTestConversion(NegSmallest, t_CFloatRight::fs_NegSmallest(), ==, NegSmallest, ==, -t_CFloatLeft::fs_0());
					}
					DTestConversion(LimitMin, t_CFloatRight::fs_LimitMin(), ==, LimitMin, ==, t_CFloatLeft::fs_NegInf());
					DTestConversion(LimitMax, t_CFloatRight::fs_LimitMax(), ==, LimitMax, ==, t_CFloatLeft::fs_Inf());

					DTestConversion(Float_0, t_CFloatRight::fs_0(), ==, Float_0, ==, t_CFloatLeft::fs_0());
					DTestConversion(Float_0_5, t_CFloatRight::fs_0_5(), ==, Float_0_5, ==, t_CFloatLeft::fs_0_5());
					DTestConversion(Float_1, t_CFloatRight::fs_1(), ==, Float_1, ==, t_CFloatLeft::fs_1());
					DTestConversion(Float_2, t_CFloatRight::fs_2(), ==, Float_2, ==, t_CFloatLeft::fs_2());
					DTestConversion(Float_E, t_CFloatRight::fs_E(), ==, Float_E, ==, t_CFloatLeft::fs_E());
					DTestConversion(Float_Pi, t_CFloatRight::fs_Pi(), ==, Float_Pi, ==, t_CFloatLeft::fs_Pi());
					DTestConversion(Float_Sqrt2, t_CFloatRight::fs_Sqrt2(), ==, Float_Sqrt2, ==, t_CFloatLeft::fs_Sqrt2());
					//DTestConversion(Float_Euler, t_CFloatRight::fs_Euler(), ==, Float_Euler, ==, t_CFloatLeft::fs_Euler()); // Slow
					DTestConversion(Float_GoldenRatio, t_CFloatRight::fs_GoldenRatio(), ==, Float_GoldenRatio, ==, t_CFloatLeft::fs_GoldenRatio());
					DTestConversion(Float_Log10_2, t_CFloatRight::fs_Log10_2(), ==, Float_Log10_2, ==, t_CFloatLeft::fs_Log10_2());
					DTestConversion(Float_Log2_10, t_CFloatRight::fs_Log2_10(), ==, Float_Log2_10, ==, t_CFloatLeft::fs_Log2_10());
					DTestConversion(Float_Log10_E, t_CFloatRight::fs_Log10_E(), ==, Float_Log10_E, ==, t_CFloatLeft::fs_Log10_E());
					DTestConversion(Float_LogE_10, t_CFloatRight::fs_LogE_10(), ==, Float_LogE_10, ==, t_CFloatLeft::fs_LogE_10());
					DTestConversion(Float_Log2_E, t_CFloatRight::fs_Log2_E(), ==, Float_Log2_E, ==, t_CFloatLeft::fs_Log2_E());
					DTestConversion(Float_LogE_2, t_CFloatRight::fs_LogE_2(), ==, Float_LogE_2, ==, t_CFloatLeft::fs_LogE_2());
				}
			};
		};

		template <typename t_CFloat>
		class CConversion
		{
		public:
			using CSmallestType = TCSmallestType<t_CFloat, fp64>;

			template <typename t_CFrom>
			CSmallestType f_Cnv(const t_CFrom &_From)
			{
				return NMib::fg_Convert<CSmallestType>(_From);
			}
			void operator() ()
			{
				fs_TestAll<TCConversion<t_CFloat>::template CInner>();
			}
		};

		template <typename tf_CType>
		static bool fs_IsNan(tf_CType const &_Type)
		{
			return _Type.f_IsNan();
		}

		static bool fs_IsNan(bool const &_Type)
		{
			return false;
		}

		template <typename tf_CType>
		static auto fs_GetName(tf_CType const &_Type)
		{
			if (_Type.f_IsNan())
				return NMib::NStr::CStr::fs_ToStr(_Type.f_Abs());

			return NMib::NStr::CStr::fs_ToStr(_Type);
		}

		static bool fs_GetName(bool const &_Type)
		{
			return NMib::NStr::CStr::fs_ToStr(_Type);
		}

		template <typename tf_CFloat>
		static auto fs_ConvertValue(tf_CFloat const &_Float)
		{
			if ((cIsSame<tf_CFloat, fp80> || cIsSame<tf_CFloat, CIEEEFloat80Emu>) && _Float.f_IsQNan())
				return _Float.f_Abs();
			return _Float;
		}

		static auto fs_ConvertValue(bool _bValue)
		{
			return _bValue;
		}

		template <typename tf_CFloat, typename tf_CFloat2>
		static bool fs_AlmostEqual(tf_CFloat const &_Float, tf_CFloat2 const &_Float2, umint _nBits)
		{
			return _Float.f_AlmostEqual(_Float2, _nBits);
		}

		static bool fs_AlmostEqual(bool _Float, bool _Float2, umint _nBits)
		{
			return _Float == _Float2;
		}

		template <typename tf_CFloat, typename tf_CEmulateFloat>
		void f_CompareEmulate()
		{
			struct CValue
			{
				ch8 const *m_pDesc;
				tf_CFloat m_Value;
			};

			CValue Values[] =
				{
					{"Max", tf_CFloat::fs_LimitMax()}
					, {"Min", tf_CFloat::fs_LimitMin()}
					, {"SmallestDenormal", tf_CFloat::fs_SmallestDenormal()}
					, {"-SmallestDenormal", tf_CFloat::fs_NegSmallestDenormal()}
					, {"Smallest", tf_CFloat::fs_Smallest()}
					, {"-Smallest", tf_CFloat::fs_NegSmallest()}
					, {"Inf", tf_CFloat::fs_Inf()}
					, {"-Inf", tf_CFloat::fs_NegInf()}
					, {"QNan", tf_CFloat::fs_QNan()}
					, {"-QNan", tf_CFloat::fs_NegQNan()}
					, {"SNan", tf_CFloat::fs_SNan()}
					, {"-SNan", tf_CFloat::fs_NegSNan()}
					, {"Epsilon", tf_CFloat::fs_Epsilon()}
					, {"-Epsilon", -tf_CFloat::fs_Epsilon()}
					, {"(1.0+Epsilon)", tf_CFloat(1.0l) + tf_CFloat::fs_Epsilon()}
					, {"(1.0-Epsilon)", tf_CFloat(1.0l) - tf_CFloat::fs_Epsilon()}
					, {"E", tf_CFloat::fs_E()}
					, {"-E", -tf_CFloat::fs_E()}
					, {"Pi", tf_CFloat::fs_Pi()}
					, {"-Pi", -tf_CFloat::fs_Pi()}
					, {"2*Pi", tf_CFloat(2.0l)*tf_CFloat::fs_Pi()}
					, {"-2*Pi", tf_CFloat(-2.0l)*tf_CFloat::fs_Pi()}
					, {"Sqrt2", tf_CFloat::fs_Sqrt2()}
					, {"-Sqrt2", -tf_CFloat::fs_Sqrt2()}
					, {"0.0", 0.0l}
					, {"-0.0", -0.0l}
					, {"0.25", 0.25l}
					, {"-0.25", -0.25l}
					, {"0.5", 0.5l}
					, {"-0.5", -0.5l}
					, {"0.75", 0.75l}
					, {"-0.75", -0.75l}
					, {"1.0", 1.0l}
					, {"-1.0", -1.0l}
					, {"1.25", 1.25l}
					, {"-1.25", -1.25l}
					, {"1.5", 1.5l}
					, {"-1.5", -1.5l}
					, {"1.75", 1.75l}
					, {"-1.75", -1.75l}
					, {"2.0", 2.0l}
					, {"-2.0", -2.0l}
					, {"2.25", 2.25l}
					, {"-2.25", -2.25l}
					, {"2.75", 2.75l}
					, {"-2.75", -2.75l}
					, {"3.0", 3.0l}
					, {"-3.0", -3.0l}
					, {"4.0", 4.0l}
					, {"-4.0", -4.0l}
					, {"5.0", 5.0l}
					, {"-5.0", -5.0l}
				}
			;

			auto fCheckBinary = [](NMib::NStr::CStr const &_Desc, tf_CFloat _Value0, tf_CFloat _Value1, auto _fFunctor)
				{
					DMibTestPath(_Desc);
					auto Result = fs_ConvertValue(_fFunctor(tf_CFloat(_Value0), tf_CFloat(_Value1)));
					auto ResultEmu = fs_ConvertValue(_fFunctor(tf_CEmulateFloat(_Value0), tf_CEmulateFloat(_Value1)));
					bool bCheckName = true;

					if (cIsSame<tf_CFloat, fp80>)
					{
						if (!fs_IsNan(Result))
							bCheckName = false;
					}
					else if (cIsSame<tf_CFloat, fp64>)
					{
						if (_Desc.f_Find(".f_Pow(") >= 0 || _Desc.f_Find(".f_Exp(") >= 0)
							bCheckName = false;
					}

					if (_Desc.f_Find(".f_Log(") >= 0)
						bCheckName = false;


					if (bCheckName)
						DMibExpect(fs_GetName(ResultEmu), ==, fs_GetName(Result));

					if (!fs_IsNan(Result))
					{
						umint AlmontEqualBits = 0;
						if (_Desc.f_Find(".f_Log(") >= 0)
							AlmontEqualBits = 2;
						else if (cIsSame<tf_CFloat, fp80>)
						{
							if (_Desc.f_Find(".f_Pow(") >= 0 || _Desc.f_Find(".f_Exp(") >= 0)
								AlmontEqualBits = 4;
						}
						else if (cIsSame<tf_CFloat, fp64>)
						{
							if (_Desc.f_Find(".f_Pow(") >= 0 || _Desc.f_Find(".f_Exp(") >= 0)
								AlmontEqualBits = 1;
						}
						else if (cIsSame<tf_CFloat, fp32>)
						{
							if (_Desc.f_Find(".f_Pow(") >= 0 || _Desc.f_Find(".f_Exp(") >= 0)
								AlmontEqualBits = 1;
						}

						if (AlmontEqualBits)
							DMibTest(DMibExpr(fs_AlmostEqual(ResultEmu, Result, AlmontEqualBits)) || DMibExpr(ResultEmu) == DMibExpr(Result));
						else
							DMibExpect(ResultEmu, ==, Result);
					}
				}
			;
			auto fCheckBinaryFunctions = [&](NMib::NStr::CStr const &_LeftDesc, NMib::NStr::CStr const &_RightDesc, tf_CFloat _Value0, tf_CFloat _Value1)
				{
					fCheckBinary(_LeftDesc + "*" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left * _Right; });
					fCheckBinary(_LeftDesc + "/" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left / _Right; });
					fCheckBinary(_LeftDesc + "+" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left + _Right; });
					fCheckBinary(_LeftDesc + "-" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left - _Right; });
					fCheckBinary(_LeftDesc + "==" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left == _Right; });
					fCheckBinary(_LeftDesc + "<" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left < _Right; });
					fCheckBinary(_LeftDesc + "<=" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left <= _Right; });
					fCheckBinary(_LeftDesc + ">" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left > _Right; });
					fCheckBinary(_LeftDesc + ">=" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left >= _Right; });
					fCheckBinary(_LeftDesc + "!=" + _RightDesc, _Value0, _Value1, [](auto _Left, auto _Right){ return _Left != _Right; });
					fCheckBinary("(" + _LeftDesc + ").f_Pow(" + _RightDesc + ")", _Value0, _Value1, [](auto _Left, auto _Right){ return _Left.f_Pow(_Right); });
					fCheckBinary("(" + _LeftDesc + ").f_Exp(" + _RightDesc + ")", _Value0, _Value1, [](auto _Left, auto _Right){ return _Left.f_Exp(_Right); });
					fCheckBinary("(" + _LeftDesc + ").f_Log(" + _RightDesc + ")", _Value0, _Value1, [](auto _Left, auto _Right){ return _Left.f_Log(_Right); });
#if 0
					fCheckBinary("(" + _LeftDesc + ").f_Mod(" + _RightDesc + ")", _Value0, _Value1, [](auto _Left, auto _Right){ return _Left.f_Mod(_Right); });
					fCheckBinary("(" + _LeftDesc + ").f_ArcTan(" + _RightDesc + ")", _Value0, _Value1, [](auto _Left, auto _Right){ return _Left.f_ArcTan(_Right); });
#endif
				}
			;

			for (auto &Left : Values)
			{
				for (auto &Right : Values)
					fCheckBinaryFunctions(Left.m_pDesc, Right.m_pDesc, Left.m_Value, Right.m_Value);
			}

			auto fCheckUnary = [](NMib::NStr::CStr const &_Desc, tf_CFloat _Value0, auto _fFunctor)
				{
					DMibTestPath(_Desc);
					auto Result = _fFunctor(tf_CFloat(_Value0));
					auto ResultEmu = _fFunctor(tf_CEmulateFloat(_Value0));
					if (fs_IsNan(Result))
						DMibExpect(fs_IsNan(ResultEmu), ==, fs_IsNan(Result));
					else if (!cIsSame<tf_CFloat, fp80>)
						DMibExpect(fs_GetName(ResultEmu), ==, fs_GetName(Result));
					if (!fs_IsNan(Result))
					{
						if
							(
								(
									cIsSame<tf_CFloat, fp80>
#if defined(DArchitecture_arm64) || defined(DArchitecture_arm64e)
									|| true
#endif
								)
								&&
								(
									_Desc.f_Find(".f_LogN()") >= 0
									|| _Desc.f_Find(".f_Log2()") >= 0
									|| _Desc.f_Find(".f_Log10()") >= 0
									|| _Desc.f_Find(".f_ExpN()") >= 0
									|| _Desc.f_Find(".f_Exp2()") >= 0
									|| _Desc.f_Find(".f_Exp10()") >= 0
								)
							)
						{
							umint nBitsEqual = 2;
							DMibExpectTrue(ResultEmu.f_AlmostEqual(Result, nBitsEqual));
						}
						else
							DMibExpect(ResultEmu, ==, Result);
					}
				}
			;
			auto fCheckUnaryFunctions = [&](NMib::NStr::CStr const &_LeftDesc, tf_CFloat _Value0)
				{
#if 0
					fCheckUnary("(" + _LeftDesc + ").f_Sin()", _Value0, [](auto _Left){ return _Left.f_Sin(); });
					fCheckUnary("(" + _LeftDesc + ").f_Cos()", _Value0, [](auto _Left){ return _Left.f_Cos(); });
					fCheckUnary("(" + _LeftDesc + ").f_Tan()", _Value0, [](auto _Left){ return _Left.f_Tan(); });
					fCheckUnary("(" + _LeftDesc + ").f_SinH()", _Value0, [](auto _Left){ return _Left.f_SinH(); });
					fCheckUnary("(" + _LeftDesc + ").f_CosH()", _Value0, [](auto _Left){ return _Left.f_CosH(); });
					fCheckUnary("(" + _LeftDesc + ").f_TanH()", _Value0, [](auto _Left){ return _Left.f_TanH(); });
					fCheckUnary("(" + _LeftDesc + ").f_ArcSin()", _Value0, [](auto _Left){ return _Left.f_ArcSin(); });
					fCheckUnary("(" + _LeftDesc + ").f_ArcCos()", _Value0, [](auto _Left){ return _Left.f_ArcCos(); });
					fCheckUnary("(" + _LeftDesc + ").f_ArcTan()", _Value0, [](auto _Left){ return _Left.f_ArcTan(); });
#endif
					fCheckUnary("(" + _LeftDesc + ").f_ExpN()", _Value0, [](auto _Left){ return _Left.f_ExpN(); });
					fCheckUnary("(" + _LeftDesc + ").f_LogN()", _Value0, [](auto _Left){ return _Left.f_LogN(); });
					fCheckUnary("(" + _LeftDesc + ").f_Exp10()", _Value0, [](auto _Left){ return _Left.f_Exp10(); });
					fCheckUnary("(" + _LeftDesc + ").f_Log10()", _Value0, [](auto _Left){ return _Left.f_Log10(); });
					fCheckUnary("(" + _LeftDesc + ").f_Exp2()", _Value0, [](auto _Left){ return _Left.f_Exp2(); });
					fCheckUnary("(" + _LeftDesc + ").f_Log2()", _Value0, [](auto _Left){ return _Left.f_Log2(); });
					fCheckUnary("(" + _LeftDesc + ").f_Sqrt()", _Value0, [](auto _Left){ return _Left.f_Sqrt(); });
					fCheckUnary("(" + _LeftDesc + ").f_Sqr()", _Value0, [](auto _Left){ return _Left.f_Sqr(); });
					fCheckUnary("(" + _LeftDesc + ").f_Floor()", _Value0, [](auto _Left){ return _Left.f_Floor(); });
					fCheckUnary("(" + _LeftDesc + ").f_Fraction()", _Value0, [](auto _Left){ return _Left.f_Fraction(); });
					fCheckUnary("(" + _LeftDesc + ").f_Ceil()", _Value0, [](auto _Left){ return _Left.f_Ceil(); });
					fCheckUnary("(" + _LeftDesc + ").f_Abs()", _Value0, [](auto _Left){ return _Left.f_Abs(); });
				}
			;
			for (auto &Left: Values)
				fCheckUnaryFunctions(Left.m_pDesc, Left.m_Value);
		}

		void f_DoTests()
		{
			DMibTestSuite("Invalid")
			{
				fs_TestAll<CInvalid>();
			};
#ifdef DMibDebug
			DMibTestSuite("Conversion")
			{
				fs_TestAll<CConversion>();
			};
#endif
			DMibTestCategory("Constants")
			{
				fs_TestAll<CConstants>();
			};
			DMibTestSuite("Multiply")
			{
				fs_TestAll<CMultiply>();
			};
			DMibTestSuite("Divide")
			{
				fs_TestAll<CDivide>();
			};
#if !defined(DCompiler_MSVC_Workaround) && !defined(DCompiler_clang_cl) && !defined(DPlatformFamily_Linux)
			DMibTestCategory("Compare Emulate")
			{
#if defined(DMibPCanDo_fp32)
				DMibTestSuite("fp32")
				{
					f_CompareEmulate<fp32, CIEEEFloat32Emu>();
				};
#endif
#if defined(DMibPCanDo_fp64)
				DMibTestSuite("fp64")
				{
					f_CompareEmulate<fp64, CIEEEFloat64Emu>();
				};
#endif
#if defined(DMibPCanDo_fp80)
				DMibTestSuite("fp80")
				{
					f_CompareEmulate<fp80, CIEEEFloat80Emu>();
				};
#endif
			};
#endif
		}
	};

	DMibTestRegister(CFloat_Tests, Malterlib::Numeric);
}
