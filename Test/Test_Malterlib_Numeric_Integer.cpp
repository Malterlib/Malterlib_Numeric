// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

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
				DMibTestPath("int96");
				t_CTestTemplate<int96>()();
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
				DMibTestPath("int192");
				t_CTestTemplate<int192>()();
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
				DMibTestPath("int384");
				t_CTestTemplate<int384>()();
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
				DMibTestPath("uint96");
				t_CTestTemplate<uint96>()();
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
				DMibTestPath("uint192");
				t_CTestTemplate<uint192>()();
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
				umint nBits = sizeof(t_CInt) * 8;
				t_CInt TestNumberBase = 0;
				auto fl_TestNumberBase
					= [&]() -> t_CInt
					{
						NMib::NStr::CStr StartNumber = "0x";
						aint Num = 9;
						for (umint i = 0; i < nBits; i += 4)
						{
							StartNumber += NMib::NStr::CStr::fs_ToStr("{nfh}", Num);
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						return NMib::NStr::fg_StrToInt(StartNumber.f_GetStr(), t_CInt(-1));
					}
				;
				for (umint i = 0; i < nBits; i += 4)
				{
					DMibTestPath(NMib::NStr::CStr::CFormat("{}") << i);
					{
						if (!TestNumberBase)
							TestNumberBase = fl_TestNumberBase();
						t_CInt Shifted = TestNumberBase << uaint(i);

						aint Num = 9;
						NMib::NStr::CStr ShouldBeNumber;
						for (umint j = 0; j < i; j += 4)
						{
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						for (umint j = i; j < nBits; j += 4)
						{
							ShouldBeNumber += NMib::NStr::CStr::fs_ToStr("{nfh}", Num);
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						for (umint j = 0; j < i; j += 4)
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
				umint nBits = sizeof(t_CInt) * 8;
				t_CInt TestNumberBase = 0;
				auto fl_TestNumberBase
					= [&]() -> t_CInt
					{
						NMib::NStr::CStr StartNumber = "0x";
						aint Num = 9;
						for (umint i = 0; i < nBits; i += 4)
						{
							StartNumber += NMib::NStr::CStr::fs_ToStr("{nfh}", Num);
							++Num;
							if (Num >= 16)
								Num = 1;
						}
						return NMib::NStr::fg_StrToInt(StartNumber.f_GetStr(), t_CInt(-1));
					}
				;
				for (umint i = 0; i < nBits; i += 4)
				{
					DMibTestPath(NMib::NStr::CStr::CFormat("{}") << i);
					{
						if (!TestNumberBase)
							TestNumberBase = fl_TestNumberBase();

						t_CInt Shifted = TestNumberBase >> uaint(i);

						aint Num = 9;
						NMib::NStr::CStr ShouldBeNumber;
						for (umint j = 0; j < i; j += 4)
						{
							if constexpr (NMib::NTraits::cIsSigned<t_CInt>)
								ShouldBeNumber += "F";
							else
								ShouldBeNumber += "0";
						}
						for (umint j = i; j < nBits; j += 4)
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
			DMibTestSuite("Literals")
			{
				DMibExpect(12_uint8, ==, uint8(12));
				DMibExpect(uint8(-12_uint8), ==, uint8(-12));
				DMibExpect(1234_uint16, ==, uint16(1234));
				DMibExpect(uint16(-1234_uint16), ==, uint16(-1234));
				DMibExpect(1234567890_uint32, ==, uint32(1234567890));
				DMibExpect(uint32(-1234567890_uint32), ==, uint32(-1234567890));
				DMibExpect(1234567890000_uint64, ==, uint64(constant_uint64(1234567890000)));
				DMibExpect(uint64(-1234567890000_uint64), ==, uint64(constant_uint64(-1234567890000)));

				DMibExpect(12_int8, ==, int8(12));
				DMibExpect(-12_int8, ==, int8(-12));
				DMibExpect(1234_int16, ==, int16(1234));
				DMibExpect(-1234_int16, ==, int16(-1234));
				DMibExpect(1234567890_int32, ==, int32(1234567890));
				DMibExpect(-1234567890_int32, ==, int32(-1234567890));
				DMibExpect(1234567890000_int64, ==, int64(constant_int64(1234567890000)));
				DMibExpect(-1234567890000_int64, ==, int64(constant_int64(-1234567890000)));

				DMibExpect(127_int8, ==, int8(127));
				DMibExpect(-127_int8, ==, int8(-127));
				DMibExpect(128_int8, ==, int8(128));
				DMibExpect(int8(-128_int8), ==, int8(-int8(128)));

				DMibExpect(32767_int16, ==, int16(32767));
				DMibExpect(-32767_int16, ==, int16(-32767));
				DMibExpect(32768_int16, ==, int16(32768));
				DMibExpect(int16(-32768_int16), ==, int16(-int16(32768)));

				DMibExpect(2147483647_int32, ==, int32(2147483647));
				DMibExpect(-2147483647_int32, ==, int32(-2147483647));
				DMibExpect(2147483648_int32, ==, int32(2147483648));
				[] DMibSuppressUndefinedSanitizer
					{
						DMibExpect(-2147483648_int32, ==, int32(-2147483648));
					}
					()
				;

				DMibExpect(0xff_uint8, ==, uint8(0xff));
				DMibExpect(0xffff_uint16, ==, uint16(0xffff));
				DMibExpect(0xffffffff_uint32, ==, uint32(0xffffffff));
				DMibExpect(0xffffffffffffffff_uint64, ==, uint64(constant_uint64(0xffffffffffffffff)));

			};
			DMibTestCategoryFlags("Shift Left", ETestCategoryFlag_DisableValues | ETestCategoryFlag_Tests)
			{
				this->f_TestAll<CShiftLeft>();
			};
			DMibTestCategoryFlags("Shift Right", ETestCategoryFlag_DisableValues | ETestCategoryFlag_Tests)
			{
				this->f_TestAll<CShiftRight>();
			};
			{
				[[maybe_unused]] int32 Test = 0xffffffff;
				[[maybe_unused]] uint32 Testu = 0xffffffff;
				[[maybe_unused]] int32 Test2 = 0xffffffff;
				[[maybe_unused]] uint32 Testu2 = 0xffffffff;

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
				static_assert(NMib::TCLimitsInt<uint32>::mc_Min == 0);
				static_assert(NMib::TCLimitsInt<uint32>::mc_Max == uint32(0xffffffff));
				static_assert(NMib::TCLimitsInt<int32>::mc_Min == int32(0x80000000));
				static_assert(NMib::TCLimitsInt<int32>::mc_Max == int32(0x7fffffff));
			};
		}
	};

	DMibTestRegister(CInt_Tests, Malterlib::Numeric);
}
