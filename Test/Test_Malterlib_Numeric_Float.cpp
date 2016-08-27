// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Numeric/CustomFloat>

#if 1
#include <cmath>
#include <limits>

#include "Test_Malterlib_Numeric_Float.h"
using namespace NMib::NMath;
namespace
{
	class CFloat_Tests : public NMib::NTest::CTest
	{
	public:

		template <template <typename t_CFloat00> class t_CTestTemplate>
		static void fs_TestAll(bool _bSuite = true)
		{
			NMib::NTest::ETestCategoryFlag Flags = _bSuite ? NMib::NTest::ETestCategoryFlag_Tests : NMib::NTest::ETestCategoryFlag_None;
			DMibTestCategoryFlags("fp8", Flags)
			{
				t_CTestTemplate<fp8>()();
			};
			DMibTestCategoryFlags("fp16", Flags)
			{
				t_CTestTemplate<fp16>()();
			};
			DMibTestCategoryFlags("fp32", Flags)
			{
				t_CTestTemplate<fp32>()();
			};
			DMibTestCategoryFlags("fp32Emu", Flags)
			{
				t_CTestTemplate<CIEEEFloat32Emu>()();
			};
			DMibTestCategoryFlags("fp64", Flags)
			{
				t_CTestTemplate<fp64>()();
			};
			DMibTestCategoryFlags("fp64Emu", Flags)
			{
				t_CTestTemplate<CIEEEFloat64Emu>()();
			};
			DMibTestCategoryFlags("fp80", Flags)
			{
				t_CTestTemplate<fp80>()();
			};
			DMibTestCategoryFlags("fp80Emu", Flags)
			{
				t_CTestTemplate<CIEEEFloat80Emu>()();
			};
			DMibTestCategoryFlags("fp128", Flags)
			{
				t_CTestTemplate<fp128>()();
			};
			DMibTestCategoryFlags("fp256", Flags)
			{
				t_CTestTemplate<fp256>()();
			};
			DMibTestCategoryFlags("fp512", Flags)
			{
				t_CTestTemplate<fp512>()();
			};
#ifndef DMibDebug
			DMibTestCategoryFlags("fp1024", Flags)
			{
				t_CTestTemplate<fp1024>()();
			};
/*			DMibTestCategoryFlags("fp2048", Flags)
			{
				t_CTestTemplate<fp2048>()();
			};*/
/*			DMibTestCategoryFlags("fp4096", Flags)
			{
				t_CTestTemplate<fp4096>()();
			};*/
#endif
		}
		
		template <typename t_CFloat>
		class CConstants
		{
		public:
			typedef typename NMib::NTraits::TCSmallestType<t_CFloat, fp64>::CType CSmallestType;
			template <typename t_CFrom>
			CSmallestType f_Cnv(const t_CFrom &_From)
			{
				return NMib::fg_Convert<CSmallestType>(_From);
			}
			void operator() ()
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
						if (sizeof(t_CFloatLeft) >= sizeof(t_CFloatRight))\
							DMibExpect(Converted##d_Name, d_ExpectBiggerOperator, d_Name);\
						else\
							DMibExpect(Converted##d_Name, d_ExpectSmallerOperator, d_ExpectSmaller);\
					}\
					{\
						DMibTestPath("Assign");\
						auto d_Name = d_Value;\
						t_CFloatLeft Converted##d_Name;\
						Converted##d_Name = d_Name;\
						if (sizeof(t_CFloatLeft) >= sizeof(t_CFloatRight))\
							DMibExpect(Converted##d_Name, d_ExpectBiggerOperator, d_Name);\
						else\
							DMibExpect(Converted##d_Name, d_ExpectSmallerOperator, d_ExpectSmaller);\
					}
					
					DTestConversion(SmallestDenormal, t_CFloatRight::fs_SmallestDenormal(), ==, SmallestDenormal, ==, t_CFloatLeft::fs_0());
					DTestConversion(NegSmallestDenormal, t_CFloatRight::fs_NegSmallestDenormal(), ==, NegSmallestDenormal, ==, -t_CFloatLeft::fs_0());
					if (sizeof(t_CFloatLeft) != sizeof(t_CFloatRight) && t_CFloatLeft::EExponentBits == t_CFloatRight::EExponentBits)
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
			typedef typename NMib::NTraits::TCSmallestType<t_CFloat, fp64>::CType CSmallestType;
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

		void f_DoTests()
		{
			fp16 Test = fp16::fs_0();
			fp8 Test2 = Test;
			
			bool boo = Test == Test2;
			(void)boo;
			
			DMibTestCategory("Invalid")
			{
				fs_TestAll<CInvalid>();
			};
			
			DMibTestCategory("Conversion")
			{
				fs_TestAll<CConversion>(false);
			};

			DMibTestCategory("Constants")
			{
				fs_TestAll<CConstants>();
			};
#if 0
			{
				ufp8 Temp = fp64(1.0);
				ufp8 Test2 = Temp * ufp8(fp64(0.33333333333333333333));
				DMibTrace("\nufp8: {} {} {}\n", Test2 << fp32(Test2) << fp64(Test2));
			}
			
			{
				fp8 Temp = fp64(1.0);
				fp8 Test2 = Temp * fp8(fp64(0.33333333333333333333));
				DMibTrace("\nfp8: {} {} {}\n", Test2 << fp32(Test2) << fp64(Test2));
			}

			{
				NMib::NMath::TCFloat <0, 4, 10> Temp = fp64(1.0);
				NMib::NMath::TCFloat <0, 4, 10> Test2 = Temp * NMib::NMath::TCFloat <0, 4, 10>(fp64(0.33333333333333333333));
				DMibTrace("\nufp14: {} {} {}\n", Test2 << fp32(Test2) << fp64(Test2));
			}

			{
				ufp16 Temp = fp64(1.0);
				ufp16 Test2 = Temp * ufp16(fp64(0.33333333333333333333));
				DMibTrace("\nufp16: {} {} {}\n", Test2 << fp32(Test2) << fp64(Test2));
			}

			{
				fp16 Temp = fp64(1.0);
				fp16 Test2 = Temp * fp16(fp64(0.33333333333333333333));
				DMibTrace("\nfp16: {} {} {}\n", Test2 << fp32(Test2) << fp64(Test2));
			}

			{
				ufp32 Temp = fp64(1.0);
				ufp32 Test2 = Temp * ufp32(fp64(0.33333333333333333333));
				DMibTrace("\nufp32: {} {} {}\n", Test2 << fp32(Test2) << fp64(Test2));
			}

			{
				fp32 Temp = fp64(1.0);
				fp32 Test2 = Temp * fp32(fp64(0.33333333333333333333));
				DMibTrace("\nfp32: {} {} {}\n", Test2 << fp32(Test2) << fp64(Test2));
			}

			{
				fp32 Test = 0.0f;

				fp32 Test2 = fg_FSetSignBits(Test, 1);

				fp64 Test3 = fg_FSetSignBits(fp64(0), 1);

				auto Test4 = fg_FArcTan(fp64(2.0), fp32(2.0));
			}

			{
				pfp32 Test = 0.0f;

				pfp32 Test2 = fg_FSetSignBits(Test, 1);

				pfp64 Test3 = fg_FSetSignBits(pfp64(0), 1);

				auto Test4 = fg_FArcTan(pfp64(2.0), pfp32(2.0));
			}
			{
				pfp32 Test = fg_F0<pfp32>();
			}
#endif

		}
			
	};

	DMibTestRegister(CFloat_Tests, Malterlib::Numeric);
}


#else
#define NumTest 8
#define NumIter 65536


using namespace NMib::NMath;

template <typename t_CTo, typename t_CFrom>
t_CTo ConvertType (const t_CFrom &_Input)
{
	return ((t_CTo &)_Input);
}

class CTestFloat : public CMalterlibTest
{
public:

	class CVectorClass
	{
	public:

	};

	aint Rand (void)
	{
		static aint holdrand = 548;
		return(((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
	}

	bool f_AutomaticTest() 
	{
		return true;
	}


	NMib::NStr::CStr Certify(CTestInterface &_Interface)
	{

		{
			CIEEEFloat32Emu Temp;
			Temp = 2.8f;
			Temp = Temp.f_Floor();
			Temp = 2.8f;
			Temp = Temp.f_Ceil();
			Temp = -2.8f;
			Temp = Temp.f_Floor();
			Temp = -2.8f;
			Temp = Temp.f_Ceil();

			Temp = 1.999999f;
			Temp = Temp.f_Floor();
			Temp = 1.999999f;
			Temp = Temp.f_Ceil();
			Temp = -1.999999f;
			Temp = Temp.f_Floor();
			Temp = -1.999999f;
			Temp = Temp.f_Ceil();

			Temp = 0.9999f;
			Temp = Temp.f_Floor();
			Temp = 0.9999f;
			Temp = Temp.f_Ceil();
			Temp = -0.9999f;
			Temp = Temp.f_Floor();
			Temp = -0.9999f;
			Temp = Temp.f_Ceil();
			Temp = 777777777777777777777.0f;
			Temp = Temp.f_Floor();
			Temp = 777777777777777777777.0f;
			Temp = Temp.f_Ceil();
			Temp = -777777777777777777777.0f;
			Temp = Temp.f_Floor();
			Temp = -777777777777777777777.0f;
			Temp = Temp.f_Ceil();
		}

		{
			CIEEEFloat32Emu Temp = 7.0f;
			CIEEEFloat32Emu Temp2 = Temp.f_Exp10();
			CIEEEFloat32Emu Temp3 =  CIEEEFloat32Emu(10.0f).f_Pow(Temp);
			fp32 Temp4 = 7.0f;
			fp32 Temp5 = Temp4.f_Exp10();
			fp32 Temp6 = fp32(10.0f).f_Pow(Temp4);
			fp32 Temp7 = fp32(10.0f).f_Pow(Temp4);
		}

		{
			CIEEEFloat64Emu Temp = 16.0;
			CIEEEFloat64Emu Temp2 = Temp.f_Exp10();
			CIEEEFloat64Emu Temp3 =  CIEEEFloat64Emu(10.0).f_Pow(Temp);
			fp64 Temp4 = 16.0;
			fp64 Temp5 = Temp4.f_Exp10();
			fp64 Temp6 = fp64(10.0).f_Pow(Temp4);
			fp64 Temp7 = fp64(10.0).f_Pow(Temp4);
		}

		DMibTrace("FloatFromat: {fd0,fm6} \n", fp32(5.5555555555f));
		DMibTrace("FloatFromat: {} \n", fp32(5.5555555555f));

		DMibTrace("FloatFromat: {fe0,fn3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fe1,fn3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fe2,fn3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fe3,fn3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fe4,fn3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fe5,fn3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fe6,fn3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fe7,fn3} \n\n", fp32(11.111111111f));

		DMibTrace("FloatFromat: {fe0,fn3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fe1,fn3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fe2,fn3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fe3,fn3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fe4,fn3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fe5,fn3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fe6,fn3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fe7,fn3} \n\n", fp32(11.0f));

		DMibTrace("FloatFromat: {fe0,fn3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fe1,fn3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fe2,fn3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fe3,fn3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fe4,fn3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fe5,fn3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fe6,fn3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fe7,fn3} \n\n", fp32(0.01111f));

		DMibTrace("FloatFromat: {fe0,fn3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fe1,fn3} \n", fp32(0.00001f));
		DMibTrace("FloatFromat: {fe2,fn3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fe3,fn3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fe4,fn3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fe5,fn3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fe6,fn3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fe7,fn3} \n\n", fp32(0.00011f));

		DMibTrace("FloatFromat: {fe0,fn3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fe1,fn3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fe2,fn3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fe3,fn3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fe4,fn3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fe5,fn3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fe6,fn3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fe7,fn3} \n\n", fp32(111111.0f));

		DMibTrace("FloatFromat: {fd0,fm3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fd1,fm3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fd2,fm3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fd3,fm3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fd4,fm3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fd5,fm3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fd6,fm3} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {fd7,fm3} \n\n", fp32(11.111111111f));

		DMibTrace("FloatFromat: {fd0,fm3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fd1,fm3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fd2,fm3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fd3,fm3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fd4,fm3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fd5,fm3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fd6,fm3} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {fd7,fm3} \n\n", fp32(11.0f));

		DMibTrace("FloatFromat: {fd0,fm3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fd1,fm3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fd2,fm3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fd3,fm3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fd4,fm3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fd5,fm3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fd6,fm3} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {fd7,fm3} \n\n", fp32(0.01111f));

		DMibTrace("FloatFromat: {fd0,fm3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fd1,fm3} \n", fp32(0.00001f));
		DMibTrace("FloatFromat: {fd2,fm3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fd3,fm3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fd4,fm3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fd5,fm3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fd6,fm3} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {fd7,fm3} \n\n", fp32(0.00011f));

		DMibTrace("FloatFromat: {fd0,fm3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fd1,fm3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fd2,fm3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fd3,fm3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fd4,fm3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fd5,fm3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fd6,fm3} \n", fp32(111111.0f));
		DMibTrace("FloatFromat: {fd7,fm3} \n\n", fp32(111111.0f));

		DMibTrace("FloatFromat: {} \n", fp32(11.111111111f));
		DMibTrace("FloatFromat: {} \n", fp32(11.0f));
		DMibTrace("FloatFromat: {} \n", fp32(0.01111f));
		DMibTrace("FloatFromat: {} \n", fp32(0.00011f));
		DMibTrace("FloatFromat: {} \n\n", fp32(111111.0f));

//		DMibTrace("FloatFromat: {fe0,fn2} \n", fp32(4.555f));
//		DMibTrace("FloatFromat: {fe0,fn2} \n", fp64(4.555f));
//		DMibTrace("FloatFromat: {fe0,fn2} \n", fp64(4.555));
		DMibTrace("FloatFromat: {fdb,fa0} \n", fp32(4.555f));
		DMibTrace("FloatFromat: {fdb,fa0} \n", fp64(4.555f));
//		DMibTrace("FloatFromat: {fdb,fa0} \n", fp64(4.555));
//		DMibTrace("FloatFromat: {fdb,fa0} \n", fp128(fp64(4.555)));
//		DMibTrace("FloatFromat: {fdb,fa0} \n", fp256(fp64(4.555)));

		{
			fp64 Test = NMib::NStr::fg_StrToFloat("999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", fp64::fs_0());
			fp32 Test2 = Test;
			fp32 Test3 = Test2;
			Test3.f_SetMantissa(Test3.f_GetMantissa() + 1);

			CIEEEFloat32Emu Test4;
			Test4.f_AssignRoundUp(Test);
			
			fp64 Diff0 = Test - Test2;
			fp64 Diff1 = Test - Test3;
			DMibTrace("FloatFromat: {fdb,fa0} \n", Test4);
		}

		{
			fp64 Test = NMib::NStr::fg_StrToFloat("0.0000000000000000000000000000000000000000111111111111111111111111111111111111111", fp64::fs_0());
			fp32 Test2 = Test;
			fp32 Test3 = Test2;
			Test3.f_SetMantissa(Test3.f_GetMantissa() + 1);

			CIEEEFloat32Emu Test4;
			Test4.f_AssignRoundUp(Test);
			
			fp64 Diff0 = Test - Test2;
			fp64 Diff1 = Test - Test3;
			DMibTrace("FloatFromat: {ffe,fdb,fa0,fsd} \n", Test2);
		}

		{
			fp64 Test = NMib::NStr::fg_StrToFloat("25.1111155", fp64::fs_0());
			fp32 Test2 = Test;
			fp32 Test3 = Test2;
			Test3.f_SetMantissa(Test3.f_GetMantissa() + 1);

			CIEEEFloat32Emu Test4;
			Test4.f_AssignRoundUp(Test);
			
			fp64 Diff0 = Test - Test2;
			fp64 Diff1 = Test - Test3;
			DMibTrace("FloatFromat: {fdb,fa0} \n", Test4);
		}
		{
			fp64 Test = NMib::NStr::fg_StrToFloat("4.555", fp64::fs_0());
			fp32 Test2 = Test;
			fp32 Test3 = Test2;
			Test3.f_SetMantissa(Test3.f_GetMantissa() + 1);

			fp32 Test4 = Test;
			
			fp64 Diff0 = Test - Test2;
			fp64 Diff1 = Test - Test3;
			fp64 Temp = Test4;
			DMibTrace("FloatFromat: {fdb,fa0} \n", fp64(Temp));
			DMibTrace("FloatFromat: {fe0,fn2} \n", Test4);
		}
		{
			fp64 Test = NMib::NStr::fg_StrToFloat("4.555", fp64::fs_0());
			fp32 Test2 = Test;
			fp32 Test3 = Test2;
			Test3.f_SetMantissa(Test3.f_GetMantissa() + 1);

			CIEEEFloat32Emu Test4;
			Test4.f_AssignRoundUp(Test);
			
			fp64 Diff0 = Test - Test2;
			fp64 Diff1 = Test - Test3;
			DMibTrace("FloatFromat: {fdb,fa0} \n", fp64(Test4));
			DMibTrace("FloatFromat: {fe0,fn2} \n", Test4);
		}
		{
			fp64 Test = NMib::NStr::fg_StrToFloat("4.554999", fp64::fs_0());
			fp32 Test2 = Test;
			fp32 Test3 = Test2;
			Test3.f_SetMantissa(Test3.f_GetMantissa() + 1);

			CIEEEFloat32Emu Test4;
			Test4.f_AssignRoundUp(Test);
			
			fp64 Diff0 = Test - Test2;
			fp64 Diff1 = Test - Test3;
			DMibTrace("FloatFromat: {fdb,fa0} \n", fp64(Test4));
			DMibTrace("FloatFromat: {fe0,fn2} \n", Test4);
			DMibTrace("FloatFromat: {} \n", Test4);
		}

		{
			fp64 Test = NMib::NStr::fg_StrToFloat("4.0", fp64::fs_0());
			Test.f_SetMantissaBits(0xffffffffffffffffi64);
			fp32 Test2 = Test;
			fp32 Test3 = Test2;
			Test3.f_SetMantissa(Test3.f_GetMantissa() + 1);

			CIEEEFloat32Emu Test4;
			Test4.f_AssignRoundUp(Test);
			
			fp64 Diff0 = Test - Test2;
			fp64 Diff1 = Test - Test3;
			DMibTrace("FloatFromat: {fdb,fa0} \n", fp64(Test4));
		}

		{
			fp64 Test = NMib::NStr::fg_StrToFloat("4.0", fp64::fs_0());
			Test.f_SetMantissaBits(0xffffffffffffffffi64);
			Test.f_SetExponent(NMib::fg_PowerOfTwoMinusOne<fp32::CInteger>(fp32::EExponentBits) - 1);
			fp32 Test2 = Test;
			fp32 Test3 = Test2;
			Test3.f_SetMantissa(Test3.f_GetMantissa() + 1);

			CIEEEFloat32Emu Test4;
			Test4.f_AssignRoundUp(Test);
			
			fp64 Diff0 = Test - Test2;
			fp64 Diff1 = Test - Test3;
			DMibTrace("FloatFromat: {fdb,fa0} \n", fp64(Test4));
		}


		DMibTrace("FloatFromat: {fdb,fa0} \n", fp64(NMib::NStr::fg_StrToFloat("4.555", fp32::fs_0())) );
		DMibTrace("FloatFromat: {fdb,fa0} \n", fp128(NMib::NStr::fg_StrToFloat("4.555", fp64::fs_0())) );
		DMibTrace("FloatFromat: {fdb,fa0} \n", fp256(NMib::NStr::fg_StrToFloat("4.555", fp128::fs_0())) );
		DMibTrace("FloatFromat: {fdb,fa0} \n", fp512(NMib::NStr::fg_StrToFloat("4.555", fp256::fs_0())) );
		DMibTrace("FloatFromat: {fdb,fa0} \n", fp1024(NMib::NStr::fg_StrToFloat("4.555", fp512::fs_0())) );
//		DMibTrace("FloatFromat: {fdb,fa0} \n", (NMib::NStr::fg_StrToFloat("4.555", fp1024::fs_0())) );
//		DMibTrace("FloatFromat: {fdb,fa0} \n", fp2048(NMib::NStr::fg_StrToFloat("4.555", fp1024::fs_0())) );
//		DMibTrace("FloatFromat: {fdb,fa0} \n", fp4096(NMib::NStr::fg_StrToFloat("4.555", fp2048::fs_0())) );
//		DMibTrace("FloatFromat: {fdb,fa0} \n", (NMib::NStr::fg_StrToFloat("4.555", fp4096::fs_0())) );

		DMibTrace("FloatFromat: {fr1,fe11} \n", fp64(24.5524564567864523456456));

#if 1
		DMibTrace("{fe3}\n", fp32(0.00000000020f));
		DMibTrace("{fe2}\n", fp32(0.00000000020f));
		DMibTrace("{fe3}\n", fp32(0.0000000020f));
		DMibTrace("{fe2}\n", fp32(0.0000000020f));
		DMibTrace("{fe3}\n", fp32(0.000000020f));
		DMibTrace("{fe2}\n", fp32(0.000000020f));
		DMibTrace("{fe3}\n", fp32(0.00000020f));
		DMibTrace("{fe2}\n", fp32(0.00000020f));
		DMibTrace("{fe3}\n", fp32(0.0000020f));
		DMibTrace("{fe2}\n", fp32(0.0000020f));
		DMibTrace("{fe3}\n", fp32(0.000020f));
		DMibTrace("{fe2}\n", fp32(0.000020f));
		DMibTrace("{fe3}\n", fp32(0.00020f));
		DMibTrace("{fe2}\n", fp32(0.00020f));
		DMibTrace("{fe3}\n", fp32(0.0020f));
		DMibTrace("{fe2}\n", fp32(0.0020f));
		DMibTrace("{fe3}\n", fp32(0.020f));
		DMibTrace("{fe2}\n", fp32(0.020f));
		DMibTrace("{fe3}\n", fp32(0.20f));
		DMibTrace("{fe2}\n", fp32(0.20f));
		DMibTrace("{fe3}\n", fp32(2.0f));
		DMibTrace("{fe2}\n", fp32(2.0f));
		DMibTrace("{fe3}\n", fp32(20.0f));
		DMibTrace("{fe2}\n", fp32(20.0f));
		DMibTrace("{fe3}\n", fp32(200.0f));
		DMibTrace("{fe2}\n", fp32(200.0f));
		DMibTrace("{fe3}\n", fp32(2000.0f));
		DMibTrace("{fe2}\n", fp32(2000.0f));
		DMibTrace("{fe3}\n", fp32(20000.0f));
		DMibTrace("{fe2}\n", fp32(20000.0f));
		DMibTrace("{fe3}\n", fp32(200000.0f));
		DMibTrace("{fe2}\n", fp32(200000.0f));
		DMibTrace("{fe3}\n", fp32(2000000.0f));
		DMibTrace("{fe2}\n", fp32(2000000.0f));
		DMibTrace("{fe3}\n", fp32(20000000.0f));
		DMibTrace("{fe2}\n", fp32(20000000.0f));
		DMibTrace("{fe3}\n", fp32(200000000.0f));
		DMibTrace("{fe2}\n", fp32(200000000.0f));
		DMibTrace("{fe3}\n", fp32(2000000000.0f));
		DMibTrace("{fe2}\n", fp32(2000000000.0f));


		DMibTrace("{fe3,ffe}\n", fp32(0.00000000020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.00000000020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.0000000020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.0000000020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.000000020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.000000020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.00000020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.00000020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.0000020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.0000020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.000020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.000020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.00020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.00020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.0020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.0020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.020f));
		DMibTrace("{fe2,ffe}\n", fp32(0.020f));
		DMibTrace("{fe3,ffe}\n", fp32(0.20f));
		DMibTrace("{fe2,ffe}\n", fp32(0.20f));
		DMibTrace("{fe3,ffe}\n", fp32(2.0f));
		DMibTrace("{fe2,ffe}\n", fp32(2.0f));
		DMibTrace("{fe3,ffe}\n", fp32(20.0f));
		DMibTrace("{fe2,ffe}\n", fp32(20.0f));
		DMibTrace("{fe3,ffe}\n", fp32(200.0f));
		DMibTrace("{fe2,ffe}\n", fp32(200.0f));
		DMibTrace("{fe3,ffe}\n", fp32(2000.0f));
		DMibTrace("{fe2,ffe}\n", fp32(2000.0f));
		DMibTrace("{fe3,ffe}\n", fp32(20000.0f));
		DMibTrace("{fe2,ffe}\n", fp32(20000.0f));
		DMibTrace("{fe3,ffe}\n", fp32(200000.0f));
		DMibTrace("{fe2,ffe}\n", fp32(200000.0f));
		DMibTrace("{fe3,ffe}\n", fp32(2000000.0f));
		DMibTrace("{fe2,ffe}\n", fp32(2000000.0f));
		DMibTrace("{fe3,ffe}\n", fp32(20000000.0f));
		DMibTrace("{fe2,ffe}\n", fp32(20000000.0f));
		DMibTrace("{fe3,ffe}\n", fp32(200000000.0f));
		DMibTrace("{fe2,ffe}\n", fp32(200000000.0f));
		DMibTrace("{fe3,ffe}\n", fp32(2000000000.0f));
		DMibTrace("{fe2,ffe}\n", fp32(2000000000.0f));


		DMibTrace("{fe100}\n", fp32(2000000000.0f));

		typedef NMib::NMath::TCFloat <1, 8, 23, pfp32, 0> CIEEEFloat32Emulate;
		typedef NMib::NMath::TCFloat <1, 11, 52, pfp64, 0> CIEEEFloat64Emulate;

		fp128 Temp1 = fp64(11.0);

		Temp1 /= fp64(32.0);

		
		DMibTrace("{}\n", Temp1);

		(NMib::NStr::CStr::CParse("{}") >> Temp1).f_Parse("1123400.45535");

		DMibTrace("{}\n", Temp1);

		DMibTrace("fp64 {}\n", NMib::fg_Convert<fp64>(1) / (NMib::fg_Convert<fp64>(3)));
		DMibTrace("fp128 {}\n", NMib::fg_Convert<fp128>(1) / (NMib::fg_Convert<fp128>(3)));
//		DMibTrace("fp256 {}\n", NMib::fg_Convert<fp256>(1) / (NMib::Convert<fp256>(3)));
//		DMibTrace("fp512 {}\n", NMib::fg_Convert<fp512>(1) / (NMib::Convert<fp512>(3)));


		DMibTrace("{}\n", NMib::fg_Convert<CIEEEFloat32Emulate>(11));
		DMibTrace("{}\n", NMib::fg_Convert<CIEEEFloat64Emulate>(11));
		DMibTrace("{}\n", NMib::fg_Convert<fp64>(11));
		DMibTrace("{}\n", NMib::fg_Convert<fp32>(11));
		DMibTrace("{}\n", NMib::fg_Convert<CIEEEFloat32Emulate>(99));
		DMibTrace("{}\n", NMib::fg_Convert<CIEEEFloat64Emulate>(99));
		DMibTrace("{}\n", NMib::fg_Convert<fp64>(99));
		DMibTrace("{}\n", NMib::fg_Convert<fp32>(99));

		DMibTrace("{}\n", fp32(1.4564564f));

		DMibTrace("{}\n", fp32(0));
		DMibTrace("{FD3}\n", fp32(14564564.0f));
		DMibTrace("{FD3}\n", fp32(0.00000000014564564f));
		DMibTrace("{}\n", fp32(1456.4564f));
		DMibTrace("{}\n", fp32(94564564.0f));
		DMibTrace("{}\n", fp32(0.00000000094564564f));
		DMibTrace("{FE2}\n", fp32(9456.4564f));
		DMibTrace("{FE0}\n", fp32(9456.4564f));
		DMibTrace("{}\n", fp32(94564564446456456456456456456456456456.0f));

		DMibTrace("{}\n", fp32(999999.0f));
		DMibTrace("{}\n", fp32(100001.0f));
		DMibTrace("{}\n", fp32(99.0f));
		DMibTrace("{}\n", fp32(11.0f));
		DMibTrace("{}\n\n\n", fp32(999999.0f));

		DMibTrace("{FFs}\n", fp32(1.4564564f));

		DMibTrace("{FFs}\n", fp32(0));
		DMibTrace("{FFs,FD3}\n", fp32(14564564.0f));
		DMibTrace("{FFs,FD3}\n", fp32(0.00000000014564564f));
		DMibTrace("{FFs}\n", fp32(1456.4564f));
		DMibTrace("{FFs}\n", fp32(94564564.0f));
		DMibTrace("{FFs}\n", fp32(0.00000000094564564f));
		DMibTrace("{FFs,FE2}\n", fp32(9456.4564f));
		DMibTrace("{FFs,FE0}\n", fp32(9456.4564f));
		DMibTrace("{FFs}\n", fp32(94564564446456456456456456456456456456.0f));

		DMibTrace("{FFs}\n", fp32(999999.0f));
		DMibTrace("{FFs}\n", fp32(100001.0f));
		DMibTrace("{FFs}\n", fp32(99.0f));
		DMibTrace("{FFs}\n", fp32(11.0f));
		DMibTrace("{FFs}\n\n\n", fp32(999999.0f));


		DMibTrace("{FFe}\n", fp32(1.4564564f));

		DMibTrace("{FFe}\n", fp32(0));
		DMibTrace("{FFe,FD3}\n", fp32(14564564.0f));
		DMibTrace("{FFe,FD3}\n", fp32(0.00000000014564564f));
		DMibTrace("{FFe}\n", fp32(1456.4564f));
		DMibTrace("{FFe}\n", fp32(94564564.0f));
		DMibTrace("{FFe}\n", fp32(0.00000000094564564f));
		DMibTrace("{FFe,FE2}\n", fp32(9456.4564f));
		DMibTrace("{FFe,FE0}\n", fp32(9456.4564f));
		DMibTrace("{FFe}\n", fp32(94564564446456456456456456456456456456.0f));

		DMibTrace("{FFe}\n", fp32(999999.0f));
		DMibTrace("{FFe}\n", fp32(100001.0f));	
		DMibTrace("{FFe}\n", fp32(99.0f));
		DMibTrace("{FFe}\n", fp32(11.0f));
		DMibTrace("{FFe}\n\n\n", fp32(999999.0f));


		DMibTrace("{}\n", fp64(0));
		DMibTrace("{FD3}\n", fp64(14564564));
		DMibTrace("{FD3}\n", fp64(0.00000000014564564));
		DMibTrace("{}\n", fp64(1456.4564f));
		DMibTrace("{}\n", fp64(94564564));
		DMibTrace("{}\n", fp64(0.00000000094564564));
		DMibTrace("{FE2}\n", fp64(9456.4564));
		DMibTrace("{FE0}\n", fp64(9456.4564));
		DMibTrace("{}\n", fp64(94564564446456456456456456456456456456456456.0));

		DMibTrace("{}\n", fp64(999999.0));
		DMibTrace("{}\n", fp64(100001.0));
		DMibTrace("{}\n", fp64(99));
		DMibTrace("{}\n", fp64(11.0));

		DMibTrace("f_Log2(1.5): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate(1.5).f_Log2())<< ConvertType<fp32>(CIEEEFloat32Emulate(1.5).f_Log2()) << ConvertType<uint32>(fp32(1.5).f_Log2()) << fp32(1.5f).f_Log2());

		DMibTrace("f_Log2(333333333.0): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate(333333333.0f).f_Log2())<< ConvertType<fp32>(CIEEEFloat32Emulate(333333333.0f).f_Log2()) << ConvertType<uint32>(fp32(333333333.0f).f_Log2()) << fp32(333333333.0f).f_Log2());
		DMibTrace("f_Log2(333333333.0): 0x{nfh,sj16,sf0} {ffe,fdb} 0x{nfh,sj16,sf0} {ffe,fdb}\n", (CIEEEFloat64Emulate(333333333.0).f_Log2().f_GetMantissa() << 7) << ConvertType<fp64>(CIEEEFloat64Emulate(333333333.0).f_Log2()) << (fp64(333333333.0).f_Log2().f_GetMantissa() << 7) << fp64(333333333.0).f_Log2());

		DMibTrace("Loge(2): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_LogE_2())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_LogE_2()) << ConvertType<uint32>(fp32::fs_LogE_2()) << fp32::fs_LogE_2());
		DMibTrace("f_LogN(Pi): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Pi().f_LogN())<< ConvertType<fp32>(CIEEEFloat32Emulate::fs_Pi().f_LogN()) << ConvertType<uint32>(fp32::fs_Pi().f_LogN()) << fp32::fs_Pi().f_LogN());
		DMibTrace("f_ExpN(Pi): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Pi().f_ExpN())<< ConvertType<fp32>(CIEEEFloat32Emulate::fs_Pi().f_ExpN()) << ConvertType<uint32>(fp32::fs_Pi().f_ExpN()) << fp32::fs_Pi().f_ExpN());

		DMibTrace("f_ExpN(22.0): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate(22.0f).f_ExpN())<< ConvertType<fp32>(CIEEEFloat32Emulate(22.0f).f_ExpN()) << ConvertType<uint32>(fp32(22.0f).f_ExpN()) << fp32(22.0f).f_ExpN());
		DMibTrace("f_ExpN(22.0): 0x{nfh,sj16,sf0} {ffe,fdb} 0x{nfh,sj16,sf0} {ffe,fdb}\n", (CIEEEFloat64Emulate(22.0f).f_ExpN().f_GetMantissa()) << ConvertType<fp64>(CIEEEFloat64Emulate(22.0f).f_ExpN()) << fp64(22.0f).f_ExpN().f_GetMantissa() << fp64(22.0f).f_ExpN());
		DMibTrace("f_ExpN(22.22222): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate(22.222222f).f_ExpN())<< ConvertType<fp32>(CIEEEFloat32Emulate(22.222222f).f_ExpN()) << ConvertType<uint32>(fp32(22.222222f).f_ExpN()) << fp32(22.222222f).f_ExpN());
		DMibTrace("f_ExpN(-22.22222): 0x{nfh,sj8,sf0} {ffe,fdb} 0x{nfh,sj8,sf0} {ffe,fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate(-22.222222f).f_ExpN())<< ConvertType<fp32>(CIEEEFloat32Emulate(-22.222222f).f_ExpN()) << ConvertType<uint32>(fp32(fp64(-22.222222f).f_ExpN())) << fp32(fp64(-22.222222f).f_ExpN()));
//		DMibTrace("f_ExpN(-22.22222): 0x{nfh,sj16,sf0} {ffe,fdb} 0x{nfh,sj16,sf0} {ffe,fdb}\n", ConvertType<uint64>(CIEEEFloat64Emulate(-22.222222).f_ExpN())<< ConvertType<fp64>(CIEEEFloat64Emulate(-22.222222).f_ExpN()) << ConvertType<uint64>(fp64(-22.222222).f_ExpN()) << fp64(-22.222222).f_ExpN());
		DMibTrace("f_ExpN(-22.22222): 0x{nfh,sj16,sf0} {ffe,fdb} 0x{nfh,sj16,sf0} {ffe,fdb}\n", CIEEEFloat32Emulate(-22.222222f).f_ExpN().f_GetMantissa() << ConvertType<fp32>(CIEEEFloat32Emulate(-22.222222f).f_ExpN()) << fp32(fp64(-22.222222f).f_ExpN()).f_GetMantissa() << fp32(fp64(-22.222222f).f_ExpN()));
		DMibTrace("f_ExpN(-22.22222): 0x{nfh,sj16,sf0} {ffe,fdb} 0x{nfh,sj16,sf0} {ffe,fdb}\n", (CIEEEFloat64Emulate(-22.222222).f_ExpN().f_GetMantissa() << 7) << ConvertType<fp64>(CIEEEFloat64Emulate(-22.222222).f_ExpN()) << fp64(-22.222222).f_ExpN().f_GetMantissa() << fp64(-22.222222).f_ExpN());
		DMibTrace("f_Exp2(-22.22222): 0x{nfh,sj16,sf0} {ffe,fdb} 0x{nfh,sj16,sf0} {ffe,fdb}\n", CIEEEFloat32Emulate(-22.222222f).f_Exp2().f_GetMantissa() << ConvertType<fp32>(CIEEEFloat32Emulate(-22.222222f).f_Exp2()) << fp32(fp64(-22.222222f).f_Exp2()).f_GetMantissa() << fp32(fp64(-22.222222).f_Exp2()));
		DMibTrace("f_Exp2(-22.22222): 0x{nfh,sj16,sf0} {ffe,fdb} 0x{nfh,sj16,sf0} {ffe,fdb}\n", (CIEEEFloat64Emulate(-22.222222).f_Exp2().f_GetMantissa() << 7) << ConvertType<fp64>(CIEEEFloat64Emulate(-22.222222).f_Exp2()) << fp64(-22.222222).f_Exp2().f_GetMantissa() << fp64(-22.222222).f_Exp2());
//		DMibTrace("f_ExpN(-22.22222): 0x{nfh,sj16,sf0} {ffe,fdb}\n", ConvertType<uint80>(fp80(-22.222222).f_ExpN()) << fp80(-22.222222).f_ExpN());

		DMibTrace("0: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_0())<< ConvertType<fp32>(CIEEEFloat32Emulate::fs_0()) << ConvertType<uint32>(fp32::fs_0()) << fp32::fs_0());
		DMibTrace("0.5: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_0_5())<< ConvertType<fp32>(CIEEEFloat32Emulate::fs_0_5()) << ConvertType<uint32>(fp32::fs_0_5()) << fp32::fs_0_5());
		DMibTrace("1.0: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_1())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_1()) << ConvertType<uint32>(fp32::fs_1()) << fp32::fs_1());
		DMibTrace("2.0: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_2())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_2()) << ConvertType<uint32>(fp32::fs_2()) << fp32::fs_2());
		DMibTrace("e: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_E())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_E()) << ConvertType<uint32>(fp32::fs_E()) << fp32::fs_E());
		DMibTrace("Pi: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Pi())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_Pi()) << ConvertType<uint32>(fp32::fs_Pi()) << fp32::fs_Pi());
		DMibTrace("Euler: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Euler())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_Euler()) << ConvertType<uint32>(fp32::fs_Euler()) << fp32::fs_Euler());
		DMibTrace("Euler: 0x{nfh,sj16,sf0} {ffe,fdb} 0x{nfh,sj16,sf0} {ffe,fdb}\n", (CIEEEFloat64Emulate::fs_Euler().f_GetMantissa()) << ConvertType<fp64>(CIEEEFloat64Emulate::fs_Euler()) << fp64::fs_Euler().f_GetMantissa() << fp64::fs_Euler());
		DMibTrace("GoldenRatio: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_GoldenRatio())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_GoldenRatio()) << ConvertType<uint32>(fp32::fs_GoldenRatio()) << fp32::fs_GoldenRatio());
		DMibTrace("Inf: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Inf())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_Inf()) << ConvertType<uint32>(fp32::fs_Inf()) << fp32::fs_Inf());
		DMibTrace("f_Log10(2): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Log10_2())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_Log10_2()) << ConvertType<uint32>(fp32::fs_Log10_2()) << fp32::fs_Log10_2());
		DMibTrace("f_Log2(10): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Log2_10())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_Log2_10()) << ConvertType<uint32>(fp32::fs_Log2_10()) << fp32::fs_Log2_10());
		DMibTrace("f_Log2(e): 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Log2_E())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_Log2_E()) << ConvertType<uint32>(fp32::fs_Log2_E()) << fp32::fs_Log2_E());
		DMibTrace("NegInf: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_NegInf())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_NegInf()) << ConvertType<uint32>(fp32::fs_NegInf()) << fp32::fs_NegInf());
		DMibTrace("NegQNan: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_NegQNan())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_NegQNan()) << ConvertType<uint32>(fp32::fs_NegQNan()) << fp32::fs_NegQNan());
		DMibTrace("NegSNan: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_NegSNan())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_NegSNan()) << ConvertType<uint32>(fp32::fs_NegSNan()) << fp32::fs_NegSNan());
		DMibTrace("QNan: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_QNan())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_QNan()) << ConvertType<uint32>(fp32::fs_QNan()) << fp32::fs_QNan());
		DMibTrace("SNan: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_SNan())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_SNan()) << ConvertType<uint32>(fp32::fs_SNan()) << fp32::fs_SNan());
		DMibTrace("Sqrt2: 0x{nfh,sj8,sf0} {fdb} 0x{nfh,sj8,sf0} {fdb}\n", ConvertType<uint32>(CIEEEFloat32Emulate::fs_Sqrt2())<<ConvertType<fp32>(CIEEEFloat32Emulate::fs_Sqrt2()) << ConvertType<uint32>(fp32::fs_Sqrt2()) << fp32::fs_Sqrt2());


		CIEEEFloat32Emulate Emulate(2.52f);
		CIEEEFloat32 Real(2.52f);
		Emulate *= -2.2222f;
		Real *= -2.2222f;
		DMibTrace("Mul Emulated: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);
		Emulate /= -3.353555f;
		Real /= -3.353555f;
		DMibTrace("Div Emulated: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);
		Emulate += 2.2222f;
		Real += 2.2222f;
		DMibTrace("Add Emulated: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);
		Emulate -= 3.353555f;
		Real -= 3.353555f;
		DMibTrace("Sub Emulated: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);

		Emulate = Emulate.f_Sqrt();
		Real = Real.f_Sqrt();
		DMibTrace("f_Sqrt Emulated: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);

		Emulate = -1.0;
		Real = -1.0;
		Emulate = Emulate.f_Sqrt();
		Real = Real.f_Sqrt();
		DMibTrace("f_Sqrt Emulated: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);

		for (int i = 0; i < 200; ++i)
		{
			CIEEEFloat32Emulate Number = CIEEEFloat32Emulate(Rand()) / CIEEEFloat32Emulate(1000.0);
			fp64 Temp = fp64(Number).f_Sqrt();
			Emulate = Number.f_Sqrt();
			Real = ((fp32&)Number).f_Sqrt();
			if ((fp32&)Emulate != Real)
				DMibTrace("f_Sqrt random Emulated error: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);
		}

		for (int i = 0; i < 200; ++i)
		{
			Emulate /= 3.353555f;
			Real /= 3.353555f;
			if ((fp32&)Emulate != Real)
				DMibTrace("Div cascade Emulated error: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);
		}

		Emulate = 3.353555f;
		Real = 3.353555f;
		for (int i = 0; i < 200; ++i)
		{
			Emulate *= 3.353555f;
			Real *= 3.353555f;
			if ((fp32&)Emulate != Real)
				DMibTrace("Mul cascade Emulated error: 0x{nfh,sj8,sf0} 0x{nfh,sj8,sf0} {fdb,ffe} {fdb,ffe}\n", (uint32&)Emulate << (uint32&)Real << (fp32&)Emulate << Real);
		}

		fp32 Value = 1.2554f;
		NMib::NTime::CTimerMin Timer;
		for (aint j = 0; j < NumTest; ++j)
		{
			{

				DMibScopeTimerMin(Timer);
				
				for (aint i = 0; i < NumIter*32; ++i)
				{
					Value = fp32(Rand()).f_ArcTan();
				}				
			}
		}
		DMibTrace("{}\n", Value);
		
		DMibTrace("Performance for f_ArcTan = {fe2} per second\n", fp64(NumIter*32) / Timer.f_GetTime());
#endif

		return "";

	}
		
};

DMibRuntimeClass(CMalterlibTest, CTestFloat);
#endif

