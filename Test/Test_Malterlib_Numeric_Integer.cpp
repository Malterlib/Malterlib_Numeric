// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#if 1

#include "Test_Malterlib_Numeric_Integer.h"

using namespace NMib::NNumeric;
namespace
{
	class CInt_Tests : public NMib::NTest::CTest
	{
	public:

		template <template <typename t_CFloat00> class t_CTestTemplate>
		void f_TestAll()
		{
			{
				DMibTestPath("int8");
				t_CTestTemplate<int8>()();
			}
			{
				DMibTestPath("int16");
				t_CTestTemplate<int16>()();
			}
			{
				DMibTestPath("int32");
				t_CTestTemplate<int32>()();
			}
			{
				DMibTestPath("int64");
				t_CTestTemplate<int64>()();
			}
			{
				DMibTestPath("int80");
				t_CTestTemplate<int80>()();
			}
			{
				DMibTestPath("int128");
				t_CTestTemplate<int128>()();
			}
			{
				DMibTestPath("int160");
				t_CTestTemplate<int160>()();
			}
			{
				DMibTestPath("int256");
				t_CTestTemplate<int256>()();
			}
			{
				DMibTestPath("int320");
				t_CTestTemplate<int320>()();
			}
			{
				DMibTestPath("int512");
				t_CTestTemplate<int512>()();
			}
			{
				DMibTestPath("int1024");
				t_CTestTemplate<int1024>()();
			}
#if 0
			{
				DMibTestPath("int2048");
				t_CTestTemplate<int2048>()();
			}
			{
				DMibTestPath("int4096");
				t_CTestTemplate<int4096>()();
			}
#endif
			{
				DMibTestPath("uint8");
				t_CTestTemplate<uint8>()();
			}
			{
				DMibTestPath("uint16");
				t_CTestTemplate<uint16>()();
			}
			{
				DMibTestPath("uint32");
				t_CTestTemplate<uint32>()();
			}
			{
				DMibTestPath("uint64");
				t_CTestTemplate<uint64>()();
			}
			{
				DMibTestPath("uint80");
				t_CTestTemplate<uint80>()();
			}
			{
				DMibTestPath("uint128");
				t_CTestTemplate<uint128>()();
			}
			{
				DMibTestPath("uint160");
				t_CTestTemplate<uint160>()();
			}
			{
				DMibTestPath("uint256");
				t_CTestTemplate<uint256>()();
			}
			{
				DMibTestPath("uint512");
				t_CTestTemplate<uint512>()();
			}
			{
				DMibTestPath("uint1024");
				t_CTestTemplate<uint1024>()();
			}
#if 0
			{
				DMibTestPath("uint2048");
				t_CTestTemplate<uint2048>()();
			}
			{
				DMibTestPath("uint4096");
				t_CTestTemplate<uint4096>()();
			}
#endif
		}

		template <typename t_CInt>
		class CAddition
		{
			void f_Test()
			{
				DMibTest(DMibExpr(t_CInt(0) + t_CInt(1)) == DMibExpr(t_CInt(1)));
			}
		public:
			void operator() ()
			{
				DMibTestPath("Addition");
				this->f_Test();
			}
		};

		template <typename t_CInt>
		class CSubtration
		{
			void f_Test()
			{
				DMibTest(DMibExpr(t_CInt(2) - t_CInt(1)) == DMibExpr(t_CInt(1)));
			}
		public:
			void operator() ()
			{
				DMibTestPath("Subtraction");
				this->f_Test();
			}
		};

		template <typename t_CInt>
		class CShiftLeft
		{
		public:
			void operator() ()
			{
				mint nBits = sizeof(t_CInt) * 8;
				t_CInt TestNumberBase = 0;
				auto fl_TestNumberBase
					= [&]() -> t_CInt
					{
						NMib::NStr::CStr StartNumber = "0x";
						aint Num = 9;
						for (mint i = 0; i < nBits; i += 4)
						{
							StartNumber += NMib::NStr::CStr::fs_ToStr("{nfh}", Num);
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						return NMib::NStr::fg_StrToInt(StartNumber.f_GetStr(), t_CInt(-1));
					}
				;
				for (mint i = 0; i < nBits; i += 4)
				{
					DMibTestPath(NMib::NStr::CStr::CFormat("{}") << i);
					{
						if (!TestNumberBase)
							TestNumberBase = fl_TestNumberBase();
						t_CInt Shifted = TestNumberBase << uaint(i);

						aint Num = 9;
						NMib::NStr::CStr ShouldBeNumber;
						for (mint j = 0; j < i; j += 4)
						{
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						for (mint j = i; j < nBits; j += 4)
						{
							ShouldBeNumber += NMib::NStr::CStr::fs_ToStr("{nfh}", Num);
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						for (mint j = 0; j < i; j += 4)
						{
							ShouldBeNumber += "0";
						}
						t_CInt CorrectShifted = NMib::NStr::fg_StrToInt(("0x" + ShouldBeNumber).f_GetStr(), t_CInt(-1));
						DMibTest(DMibExpr(Shifted) == DMibExpr(CorrectShifted));
					};
				}
			}
		};

		template <typename t_CInt>
		class CShiftRight
		{
		public:
			void operator() ()
			{
				mint nBits = sizeof(t_CInt) * 8;
				t_CInt TestNumberBase = 0;
				auto fl_TestNumberBase
					= [&]() -> t_CInt
					{
						NMib::NStr::CStr StartNumber = "0x";
						aint Num = 9;
						for (mint i = 0; i < nBits; i += 4)
						{
							StartNumber += NMib::NStr::CStr::fs_ToStr("{nfh}", Num);
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						return NMib::NStr::fg_StrToInt(StartNumber.f_GetStr(), t_CInt(-1));
					}
				;
				for (mint i = 0; i < nBits; i += 4)
				{
					DMibTestPath(NMib::NStr::CStr::CFormat("{}") << i);
					{
						if (!TestNumberBase)
							TestNumberBase = fl_TestNumberBase();

						t_CInt Shifted = TestNumberBase >> uaint(i);

						aint Num = 9;
						NMib::NStr::CStr ShouldBeNumber;
						for (mint j = 0; j < i; j += 4)
						{
							if (NMib::NTraits::TCIsSigned<t_CInt>::mc_Value)
								ShouldBeNumber += "F";
							else
								ShouldBeNumber += "0";
						}
						for (mint j = i; j < nBits; j += 4)
						{
							ShouldBeNumber += NMib::NStr::CStr::fs_ToStr("{nfh}", Num);
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						t_CInt CorrectShifted = NMib::NStr::fg_StrToInt(("0x" + ShouldBeNumber).f_GetStr(), t_CInt(-1));
						DMibTest(DMibExpr(Shifted) == DMibExpr(CorrectShifted));
					};
				}
			}
		};

		void f_DoTests()
		{

#if 0
			TCInt2<32> IntTest;
			IntTest;

			TCCombineInt<31> Inter;
			Inter;

			int Temee = sizeof(Inter);

			{
				

				int256 Test = NMib::NStr::fg_StrToInt("0x9abcdef123456789abcdef123456789abcdef123456789abcdef123456789abc", int256(-1));
				Test = Test << (64 + 8);
				Test = Test >> (64);
				Test = Test >> (64);
			}


			auto &Test0 = Inter.f_GetInt<0>();
			auto &Test1 = Inter.f_GetInt<1>();
			auto &Test2 = Inter.f_GetInt<2>();
			auto &Test3 = Inter.f_GetInt<3>();
			auto &Test4 = Inter.f_GetInt<4>();
			auto &Test5 = Inter.f_GetInt<5>();
//			auto &Test6 = Inter.f_GetInt<6>();
			Test0 = 0;
			Test1 = 1;
			Test2 = 2;
			Test3 = 3;
			Test4 = 4;
			Test5 = 5;
//			Test6 = 6;
#endif

			DMibTestCategoryFlags("Shift Left", ETestCategoryFlag_DisableValues | ETestCategoryFlag_Tests)
			{
				this->f_TestAll<CShiftLeft>();
			};
			DMibTestCategoryFlags("Shift Right", ETestCategoryFlag_DisableValues | ETestCategoryFlag_Tests)
			{
				this->f_TestAll<CShiftRight>();
			};
			{
				int32 Test = 0xffffffff;
				uint32 Testu = 0xffffffff;
				int32 Test2 = 0xffffffff;
				uint32 Testu2 = 0xffffffff;

				Test >>= 2;
				Testu >>= 2;
				Test2 <<= 2;
				Testu2 <<= 2;
				Testu2 += 0;
			}
			{
				TCInt<int16, uint16> Test = 0xffffffff;
				TCInt<uint16, uint16> Testu = 0xffffffff;
				TCInt<int16, uint16> Test2 = 0xffffffff;
				TCInt<uint16, uint16> Testu2 = 0xffffffff;

				Test >>= 2;
				Testu >>= 2;
				Test2 <<= 2;
				Testu2 <<= 2;
				Testu2 += 0;
			}

			{
				int80 Test = NMib::NStr::fg_StrToInt("0x923456789abcdefedcba", int80(-1));
				uint80 Testu = NMib::NStr::fg_StrToInt("0x923456789abcdefedcba", uint80(-1));
				int80 Test2 = NMib::NStr::fg_StrToInt("0x923456789abcdefedcba", int80(-1));
				uint80 Testu2 = NMib::NStr::fg_StrToInt("0x923456789abcdefedcba", uint80(-1));

				Test >>= 76;
				Testu >>= 76;
				Test2 <<= 76;
				Testu2 <<= 76;
				Testu2 += 0;
			}

			{
				int80 Test = NMib::NStr::fg_StrToInt("0x923456789abcdefedcba", int80(-1));
				uint80 Testu = NMib::NStr::fg_StrToInt("0x923456789abcdefedcba", uint80(-1));
				int80 Test2 = NMib::NStr::fg_StrToInt("0x923456789abcdefedcba", int80(-1));
				uint80 Testu2 = NMib::NStr::fg_StrToInt("0x923456789abcdefedcba", uint80(-1));

				Test >>= 76;
				Testu >>= 76;
				Test2 <<= 76;
				Testu2 <<= 76;
				Testu2 += 0;
			}

			{
				int80 Test = -1;
				uint80 Testu = -1;
				int80 Test2 = -1;
				uint80 Testu2 = -1;

				Test >>= 2;
				Testu >>= 2;
				Test2 <<= 2;
				Testu2 <<= 2;
				Testu2 += 0;
			}

			{
				int80 Test = -1;
				uint80 Testu = -1;
				int80 Test2 = -1;
				uint80 Testu2 = -1;

				Test >>= 2;
				Testu >>= 2;
				Test2 <<= 2;
				Testu2 <<= 2;
				Testu2 += 0;
			}

			DMibTestSuite("Addition")
			{
				this->f_TestAll<CAddition>();
			};

			DMibTestSuite("Subtration")
			{
				this->f_TestAll<CSubtration>();
			};

			DMibTestSuite("Limits")
			{
				DMibStaticCheck(NMib::TCLimitsInt<uint32>::mc_Min == 0);
				DMibStaticCheck(NMib::TCLimitsInt<uint32>::mc_Max == uint32(0xffffffff));
				DMibStaticCheck(NMib::TCLimitsInt<int32>::mc_Min == int32(0x80000000));
				DMibStaticCheck(NMib::TCLimitsInt<int32>::mc_Max == int32(0x7fffffff));

				DMibTest(DMibExpr(NMib::TCLimitsIntDyn<uint32>::mc_Min) == DMibExpr(0u));
				DMibTest(DMibExpr(NMib::TCLimitsIntDyn<uint32>::mc_Max) == DMibExpr(uint32(0xffffffff)));
				DMibTest(DMibExpr(NMib::TCLimitsIntDyn<int32>::mc_Min) == DMibExpr(int32(0x80000000)));
				DMibTest(DMibExpr(NMib::TCLimitsIntDyn<int32>::mc_Max) == DMibExpr(int32(0x7fffffff)));
			
			};
	

		}
	};

	DMibTestRegister(CInt_Tests, Malterlib::Numeric);
}

#else

#define NumTest 8
#define NumIter 65536


using namespace NMib::NNumeric;

typedef TCInt<int8, uint8> Simulate_int16;

DMibStrStringFormatterImplementInt(Simulate_int16);

class CTestInt : public CMalterlibTest
{
public:

	class CVectorClass
	{
	public:

		template <typename t_CConvert>
		operator t_CConvert () const
		{
			return t_CConvert ();
		}

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

	uint32 f_GetHighestPower2_shift(uint32 _Number)
	{
		uint32 v = _Number; // compute the next highest power of 2 of 32-bit v

		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;

		return v;
	}

	static inline_small int32 f_BitScanReverse_Test(unsigned long _Value)
	{
		return DMibPGetHighestBitSet32(_Value);
	}

	uint32 f_GetHighestPower2_BSR(uint32 _Number)
	{
		int32 v = f_BitScanReverse_Test(_Number - 1);
		
		return 1 << (v + 1);
	}

	static inline_small uint32 f_BitScanReverse_Test1(uint32 _Value)
	{
		return DMibPGetHighestBitSet32(_Value);
	}


	static inline_small uint32 f_GetHighestPower2_BSR1(uint32 _Number)
	{
		return 1 << DMibPGetHighestBitSet32((_Number << 1) - 1);
	}

	NMib::NStr::CStr Certify(CTestInterface &_Interface)
	{
		
		uint16 Swap16 = 0x0123;
		uint32 Swap32 = 0x01234567;
		uint64 Swap64 = 0x0123456789abcdefll;
		
		Swap16 = NMib::fg_ByteSwap(Swap16);
		Swap32 = NMib::fg_ByteSwap(Swap32);
		Swap64 = NMib::fg_ByteSwap(Swap64);

		aint Highest0 = NMib::fg_GetHighestBitSet(uint8(0x1));
		aint Highest1 = NMib::fg_GetHighestBitSet(uint8(0x3));
		aint Highest2 = NMib::fg_GetHighestBitSet(uint16(0x6554));
		aint Highest3 = NMib::fg_GetHighestBitSet(uint32(0x25540066));
		aint Highest4 = NMib::fg_GetHighestBitSet(uint64(0x1554006625540066));
		aint Highest5 = NMib::fg_GetHighestBitSet(uint64(0));
		aint Highest6 = NMib::fg_GetHighestBitSet(uint64(0x0000056625540066));

		DMibTrace("{} {} {} {} {} {} {}\n", Highest0 << Highest1 << Highest2 << Highest3 << Highest4 << Highest5 << Highest6);
		
		uint64 Temp = constant_uint64(40000000000);
		Temp += -3;
		TCInt<uint8, uint8> TestInt(0, 0);
		TestInt = TCInt<uint8, uint8>(255) + TCInt<uint8, uint8>(3);

		TCInt<int8, uint8> TestInt1(0, 0);
		TestInt1 = TCInt<int8, uint8>(255) + TCInt<int8, uint8>(-2,33);

		int16 Test1 = NMib::fg_Convert<int16>(TestInt1);

		TestInt1 = TCInt<int8, uint8>(255) - TCInt<int8, uint8>(555);
		Test1 = NMib::fg_Convert<int16>(TestInt1);

		TestInt1 = TCInt<int8, uint8>(50 + 256) - TCInt<int8, uint8>(80+256);
		Test1 = NMib::fg_Convert<int16>(TestInt1);

		
		TestInt1 = TCInt<int8, uint8>(-12152) << 4;
		Test1 = NMib::fg_Convert<int16>(TestInt1);
//		Test1 = (int16)(int16(-12152) << 4);
		TestInt1 = TCInt<int8, uint8>(-12152) << 8;
		Test1 = NMib::fg_Convert<int16>(TestInt1);
//		Test1 = (int16)(int16(-12152) << 8);
		TestInt1 = TCInt<int8, uint8>(-12152) << 12;
		Test1 = NMib::fg_Convert<int16>(TestInt1);
//		Test1 = (int16)(int16(-12152) << 12);
		TestInt1 = TCInt<int8, uint8>(-12152) << 16;
		Test1 = NMib::fg_Convert<int16>(TestInt1);
//		Test1 = (int16)(int16(-12152) << 16);

		TestInt1 = TCInt<int8, uint8>(5) * TCInt<int8, uint8>(5);
		Test1 = NMib::fg_Convert<int16>(TestInt1);
		Test1 = 5 * 5;

		TestInt1 = TCInt<int8, uint8>(25) * TCInt<int8, uint8>(25);
		Test1 = NMib::fg_Convert<int16>(TestInt1);
		Test1 = 25 * 25;

		TestInt1 = TCInt<int8, uint8>(25) * TCInt<int8, uint8>(25);
		Test1 = NMib::fg_Convert<int16>(TestInt1);
		Test1 = 25 * 25;


		DMibTrace("f_GetHighestPower2_BSR(0xFFFFFFFF) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR(0xFFFFFFFF));
		DMibTrace("f_GetHighestPower2_BSR(0x7FFFFFFF) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR(0x7FFFFFFF));
		DMibTrace("f_GetHighestPower2_BSR(0x80000000) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR(0x80000000));
		DMibTrace("f_GetHighestPower2_BSR(0x00000001) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR(1));
		DMibTrace("f_GetHighestPower2_BSR(0x00000000) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR(0));

		DMibTrace("f_GetHighestPower2_shift(0xFFFFFFFF) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_shift(0xFFFFFFFF));
		DMibTrace("f_GetHighestPower2_shift(0x7FFFFFFF) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_shift(0x7FFFFFFF));
		DMibTrace("f_GetHighestPower2_shift(0x80000000) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_shift(0x80000000));
		DMibTrace("f_GetHighestPower2_shift(0x00000001) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_shift(1));
		DMibTrace("f_GetHighestPower2_shift(0x00000000) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_shift(0));

		DMibTrace("f_GetHighestPower2_BSR1(0xFFFFFFFF) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR1(0xFFFFFFFF));
		DMibTrace("f_GetHighestPower2_BSR1(0x7FFFFFFF) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR1(0x7FFFFFFF));
		DMibTrace("f_GetHighestPower2_BSR1(0x80000000) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR1(0x80000000));
		DMibTrace("f_GetHighestPower2_BSR1(0x00000001) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR1(1));
		DMibTrace("f_GetHighestPower2_BSR1(0x00000000) = 0x{nfh,sf0,sj8}\n", f_GetHighestPower2_BSR1(0));

		{
			NMib::NTime::CTimerMin Timer;
			{
				uint32 Number = 0x1;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100000; ++i)
					{
						Number = f_GetHighestPower2_BSR(Number);
						Number = f_GetHighestPower2_BSR(Number);
						Number = f_GetHighestPower2_BSR(Number);
						Number = f_GetHighestPower2_BSR(Number);
						Number = f_GetHighestPower2_BSR(Number);
						Number = f_GetHighestPower2_BSR(Number);
						Number = f_GetHighestPower2_BSR(Number);
						Number = f_GetHighestPower2_BSR(Number);
					}
				}
				DMibTrace("Number 0 = {}\n", Number);
			}
			DMibTrace("Performance for 32 bit Power2 BSR Dependant = {} per second\n", ((fp64(800000) / Timer.f_GetTime())));
		}
		{
			NMib::NTime::CTimerMin Timer;
			{
				uint32 Number = 0x1;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100000; ++i)
					{
						Number = f_GetHighestPower2_BSR1(Number);
						Number = f_GetHighestPower2_BSR1(Number);
						Number = f_GetHighestPower2_BSR1(Number);
						Number = f_GetHighestPower2_BSR1(Number);
						Number = f_GetHighestPower2_BSR1(Number);
						Number = f_GetHighestPower2_BSR1(Number);
						Number = f_GetHighestPower2_BSR1(Number);
						Number = f_GetHighestPower2_BSR1(Number);
					}
				}
				DMibTrace("Number 0 = {}\n", Number);
			}
			DMibTrace("Performance for 32 bit Power2 BSR1 Dependant = {} per second\n", ((fp64(800000) / Timer.f_GetTime())));
		}
		{
			NMib::NTime::CTimerMin Timer;
			{
				uint32 Number = 0x1;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100000; ++i)
					{
						Number = f_GetHighestPower2_shift(Number);
						Number = f_GetHighestPower2_shift(Number);
						Number = f_GetHighestPower2_shift(Number);
						Number = f_GetHighestPower2_shift(Number);
						Number = f_GetHighestPower2_shift(Number);
						Number = f_GetHighestPower2_shift(Number);
						Number = f_GetHighestPower2_shift(Number);
						Number = f_GetHighestPower2_shift(Number);
					}
				}
				DMibTrace("Number 0 = {}\n", Number);
			}
			DMibTrace("Performance for 32 bit Power2 Shift Dependant = {} per second\n", ((fp64(800000) / Timer.f_GetTime())));
		}

		{
			NMib::NTime::CTimerMin Timer;
			{
				uint32 Number0 = 0xf;
				uint32 Number1 = 0x3;
				uint32 Number2 = 0x2;
				uint32 Number3 = 0x3;
				uint32 Number4 = 0x4;
				uint32 Number5 = 0x5;
				uint32 Number6 = 0x6;
				uint32 Number7 = 0x7;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100000; ++i)
					{
						Number0 = f_GetHighestPower2_BSR(Number0);
						Number1 = f_GetHighestPower2_BSR(Number1);
						Number2 = f_GetHighestPower2_BSR(Number2);
						Number3 = f_GetHighestPower2_BSR(Number3);
						Number4 = f_GetHighestPower2_BSR(Number4);
						Number5 = f_GetHighestPower2_BSR(Number5);
						Number6 = f_GetHighestPower2_BSR(Number6);
						Number7 = f_GetHighestPower2_BSR(Number7);
					}
				}
				DMibTrace("Number 0 = {}\n", Number0);
				DMibTrace("Number 1 = {}\n", Number1);
				DMibTrace("Number 2 = {}\n", Number2);
				DMibTrace("Number 3 = {}\n", Number3);
				DMibTrace("Number 4 = {}\n", Number4);
				DMibTrace("Number 5 = {}\n", Number5);
				DMibTrace("Number 6 = {}\n", Number6);
				DMibTrace("Number 7 = {}\n", Number7);
			}
			DMibTrace("Performance for 32 bit Power2 BSR = {} per second\n", ((fp64(800000) / Timer.f_GetTime())));
		}
		{
			NMib::NTime::CTimerMin Timer;
			{
				uint32 Number0 = 0xf;
				uint32 Number1 = 0x3;
				uint32 Number2 = 0x2;
				uint32 Number3 = 0x3;
				uint32 Number4 = 0x4;
				uint32 Number5 = 0x5;
				uint32 Number6 = 0x6;
				uint32 Number7 = 0x7;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100000; ++i)
					{
						Number0 = f_GetHighestPower2_BSR1(Number0);
						Number1 = f_GetHighestPower2_BSR1(Number1);
						Number2 = f_GetHighestPower2_BSR1(Number2);
						Number3 = f_GetHighestPower2_BSR1(Number3);
						Number4 = f_GetHighestPower2_BSR1(Number4);
						Number5 = f_GetHighestPower2_BSR1(Number5);
						Number6 = f_GetHighestPower2_BSR1(Number6);
						Number7 = f_GetHighestPower2_BSR1(Number7);
					}
				}
				DMibTrace("Number 0 = {}\n", Number0);
				DMibTrace("Number 1 = {}\n", Number1);
				DMibTrace("Number 2 = {}\n", Number2);
				DMibTrace("Number 3 = {}\n", Number3);
				DMibTrace("Number 4 = {}\n", Number4);
				DMibTrace("Number 5 = {}\n", Number5);
				DMibTrace("Number 6 = {}\n", Number6);
				DMibTrace("Number 7 = {}\n", Number7);
			}
			DMibTrace("Performance for 32 bit Power2 BSR1 = {} per second\n", ((fp64(800000) / Timer.f_GetTime())));
		}
		{
			NMib::NTime::CTimerMin Timer;
			{
				uint32 Number0 = 0xf;
				uint32 Number1 = 0x3;
				uint32 Number2 = 0x2;
				uint32 Number3 = 0x3;
				uint32 Number4 = 0x4;
				uint32 Number5 = 0x5;
				uint32 Number6 = 0x6;
				uint32 Number7 = 0x7;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100000; ++i)
					{
						Number0 = f_GetHighestPower2_shift(Number0);
						Number1 = f_GetHighestPower2_shift(Number1);
						Number2 = f_GetHighestPower2_shift(Number2);
						Number3 = f_GetHighestPower2_shift(Number3);
						Number4 = f_GetHighestPower2_shift(Number4);
						Number5 = f_GetHighestPower2_shift(Number5);
						Number6 = f_GetHighestPower2_shift(Number6);
						Number7 = f_GetHighestPower2_shift(Number7);
					}
				}
				DMibTrace("Number 0 = {}\n", Number0);
				DMibTrace("Number 1 = {}\n", Number0);
				DMibTrace("Number 2 = {}\n", Number0);
				DMibTrace("Number 3 = {}\n", Number0);
				DMibTrace("Number 4 = {}\n", Number0);
				DMibTrace("Number 5 = {}\n", Number0);
				DMibTrace("Number 6 = {}\n", Number0);
				DMibTrace("Number 7 = {}\n", Number0);
			}
			DMibTrace("Performance for 32 bit Power2 Shift = {} per second\n", ((fp64(800000) / Timer.f_GetTime())));
		}

		{
			int64 HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64(0));
			DMibTrace("HugeNumber: {}\n", HugeNumber);

			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber += Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64 bit add = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber -= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64 bit sub = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64 bit mul = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64 bit divide = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64 bit divide / mul = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
		}

		{
			typedef TCInt<int32, uint32> int64emu;

			int64emu HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64emu(0));
			DMibTrace("HugeNumber: {}\n", HugeNumber);

			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber += Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64emu bit add = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64emu(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber -= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64emu bit sub = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64emu(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64emu bit mul = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64emu(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64emu bit divide = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765", int64emu(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 64emu bit divide / mul = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
		}

		{
			int128 HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432", int128(0));
			DMibTrace("HugeNumber: {}\n", HugeNumber);

			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber += Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 128 bit add = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432", int128(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber -= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 128 bit sub = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432", int128(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 128 bit mul = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432", int128(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 128 bit divide = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432", int128(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 128 bit divide / mul = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
		}

		{
			int256 HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765432109876543210987654321098765432109876", int256(0));
			DMibTrace("HugeNumber: {}\n", HugeNumber);

			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber += Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 256 bit add = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765432109876543210987654321098765432109876", int256(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber -= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 256 bit sub = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765432109876543210987654321098765432109876", int256(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 256 bit mul = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765432109876543210987654321098765432109876", int256(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 256 bit divide = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-87654321098765432109876543210987654321098765432109876", int256(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 256 bit divide / mul = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
		}

		{
			int512 HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876", int512(0));
			DMibTrace("HugeNumber: {}\n", HugeNumber);

			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber += Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 512 bit add = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876", int512(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber -= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 512 bit sub = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876", int512(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 512 bit mul = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876", int512(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 512 bit divide = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876", int512(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 512 bit divide / mul = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
		}
		{
			int1024 HugeNumber = NMib::NStr::fg_StrToInt("-8765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098768765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098", int1024(0));

			DMibTrace("HugeNumber: {}\n", HugeNumber);

			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber += Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 1024 bit add = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-8765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098768765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098", int1024(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber -= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 1024 bit sub = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-8765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098768765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098", int1024(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 1000; ++i)
					{
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 1024 bit mul = {} per second\n", ((fp64(1000) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-8765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098768765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098", int1024(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 1024 bit divide = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
			HugeNumber = NMib::NStr::fg_StrToInt("-8765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098768765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098765432109876543210987654321098", int1024(0));
			{
				NMib::NTime::CTimerMin Timer;
				{
					DMibScopeTimerMin(Timer);
					for (int i = 0 ; i < 100; ++i)
					{
						HugeNumber /= Rand()+1;
						HugeNumber *= Rand()+1;
					}
				}
//				DMibTrace("HugeNumber result: {}\n", HugeNumber);
				DMibTrace("Performance for 1024 bit divide / mul = {} per second\n", ((fp64(100) / Timer.f_GetTime())));
			}
		}

		{
			uint64 Mega = constant_uint64(5555555555);
			Mega >>= 31;
			Mega >>= 1;
			TCInt<TCInt<int16, uint16>, TCInt<uint16, uint16> > TestInt1 = TCInt<TCInt<int16, uint16>, TCInt<uint16, uint16> >(constant_uint64(5555555555)) * TCInt<TCInt<int16, uint16>, TCInt<uint16, uint16> >(constant_uint64(5555555555));
			int64 Test2 = NMib::fg_Convert<int64>(TestInt1);
			int64 Mega0 = uint64(constant_uint64(5555555555));
			int64 Mega1 = uint64(constant_uint64(5555555555));
			Test2 = Mega0 * Mega1;
			Test2 = Mega0 * Mega1;
		}

		{
			int64 Mega0 = int64(constant_int64(5555555555));
			int64 Mega1 = int64(constant_int64(-555555));
			int64 Test2 = Mega0 / Mega1;
			TCInt<int32, uint32> TestInt1 = TCInt<int32, uint32>(constant_int64(5555555555)) / TCInt<int32, uint32>(-555555);
			Test2 = NMib::fg_Convert<int64>(TestInt1);
			Test2 = NMib::fg_Convert<int64>(TestInt1);
		}

		{
			int64 Mega0 = int64(constant_int64(-5555555555));
			int64 Mega1 = int64(555555);
			int64 Test2 = Mega0 % Mega1;
			TCInt<int32, uint32> TestInt1 = TCInt<int32, uint32>(constant_int64(-5555555555)) % TCInt<int32, uint32>(555555);
			Test2 = NMib::fg_Convert<int64>(TestInt1);
			Test2 = NMib::fg_Convert<int64>(TestInt1);
		}

		{
			int64 Mega0 = uint64(constant_int64(5555555555));
			int64 Mega1 = uint64(555555);
			int64 Test2 = Mega0 / Mega1;
			TCInt<TCInt<int16, uint16>, TCInt<uint16, uint16> > TestInt1 = TCInt<TCInt<int16, uint16>, TCInt<uint16, uint16> >(constant_int64(5555555555)) / TCInt<TCInt<int16, uint16>, TCInt<uint16, uint16> >(555555);
			Test2 = NMib::fg_Convert<int64>(TestInt1);
			Test2 = NMib::fg_Convert<int64>(TestInt1);
		}

		TestInt1 = TCInt<int8, uint8>(50 + 256) - TCInt<int8, uint8>(80+256);

		DMibTrace("{}\n", TestInt1);


		return "";

	}
		
};

DMibRuntimeClass(CMalterlibTest, CTestInt);
#endif
