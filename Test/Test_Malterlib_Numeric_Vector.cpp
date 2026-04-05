// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Numeric/Vector>

using namespace NMib::NNumeric;
using namespace NMib::NStr;

// Compile-time construction tests
constexpr static CVec2Dfp32 gc_TestAggregate2D{0.0f, 1.0f};
constexpr static CVec3Dfp32 gc_TestAggregate3D{0.0f, 1.0f, 2.0f};
constexpr static CVec4Dfp32 gc_TestAggregate4D{0.0f, 1.0f, 2.0f, 3.0f};

// Compile-time access tests
static_assert(gc_TestAggregate2D[0].f_Get() == 0.0f);
static_assert(gc_TestAggregate2D[1].f_Get() == 1.0f);
static_assert(gc_TestAggregate3D[2].f_Get() == 2.0f);
static_assert(gc_TestAggregate4D[3].f_Get() == 3.0f);

namespace
{
	struct CVec_Tests : public NMib::NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("Construction")
			{
				{
					DMibTestPath("Default");
					TCVec<int32, 3> Vec;
					// Default construction - values are uninitialized, just verify it compiles
					(void)Vec;
				}

				{
					DMibTestPath("Variadic");
					CVec3Dfp32 Vec(1.0f, 2.0f, 3.0f);
					DMibExpect(Vec[0], ==, 1.0f);
					DMibExpect(Vec[1], ==, 2.0f);
					DMibExpect(Vec[2], ==, 3.0f);
				}

				{
					DMibTestPath("Variadic/MixedTypes");
					// Construct with different numeric types
					TCVec<fp64, 3> Vec(1, 2.0f, 3.0);
					DMibExpect(Vec[0], ==, 1.0);
					DMibExpect(Vec[1], ==, 2.0);
					DMibExpect(Vec[2], ==, 3.0);
				}
			};

			DMibTestSuite("ConvertingConstruction")
			{
				{
					DMibTestPath("SameDim/TypeConversion");
					CVec3Dfp32 SrcFloat(1.5f, 2.5f, 3.5f);
					TCVec<int32, 3> DstInt(SrcFloat);
					DMibExpect(DstInt[0], ==, 1);
					DMibExpect(DstInt[1], ==, 2);
					DMibExpect(DstInt[2], ==, 3);
				}

				{
					DMibTestPath("SmallerToLarger");
					CVec2Dfp32 Src2D(1.0f, 2.0f);
					CVec4Dfp32 Dst4D(Src2D);
					DMibExpect(Dst4D[0], ==, 1.0f);
					DMibExpect(Dst4D[1], ==, 2.0f);
					DMibExpect(Dst4D[2], ==, 0.0f);
					DMibExpect(Dst4D[3], ==, 0.0f);
				}

				{
					DMibTestPath("LargerToSmaller");
					CVec4Dfp32 Src4D(1.0f, 2.0f, 3.0f, 4.0f);
					CVec2Dfp32 Dst2D(Src4D);
					DMibExpect(Dst2D[0], ==, 1.0f);
					DMibExpect(Dst2D[1], ==, 2.0f);
				}

				{
					DMibTestPath("TypeAndDimConversion");
					TCVec<fp64, 4> SrcDouble(1.5, 2.5, 3.5, 4.5);
					TCVec<int32, 2> DstInt(SrcDouble);
					DMibExpect(DstInt[0], ==, 1);
					DMibExpect(DstInt[1], ==, 2);
				}
			};

			DMibTestSuite("IndexAccess")
			{
				{
					DMibTestPath("Read");
					CVec3Dfp32 const Vec(1.0f, 2.0f, 3.0f);
					DMibExpect(Vec[0], ==, 1.0f);
					DMibExpect(Vec[1], ==, 2.0f);
					DMibExpect(Vec[2], ==, 3.0f);
				}

				{
					DMibTestPath("Write");
					CVec3Dfp32 Vec(0.0f, 0.0f, 0.0f);
					Vec[0] = 10.0f;
					Vec[1] = 20.0f;
					Vec[2] = 30.0f;
					DMibExpect(Vec[0], ==, 10.0f);
					DMibExpect(Vec[1], ==, 20.0f);
					DMibExpect(Vec[2], ==, 30.0f);
				}
			};

			DMibTestSuite("Assignment")
			{
				{
					DMibTestPath("SameDim/TypeConversion");
					CVec3Dfp32 SrcFloat(1.5f, 2.5f, 3.5f);
					TCVec<int32, 3> DstInt;
					DstInt = SrcFloat;
					DMibExpect(DstInt[0], ==, 1);
					DMibExpect(DstInt[1], ==, 2);
					DMibExpect(DstInt[2], ==, 3);
				}

				{
					DMibTestPath("SmallerToLarger");
					CVec2Dfp32 Src2D(5.0f, 6.0f);
					CVec4Dfp32 Dst4D(1.0f, 2.0f, 3.0f, 4.0f);
					Dst4D = Src2D;
					DMibExpect(Dst4D[0], ==, 5.0f);
					DMibExpect(Dst4D[1], ==, 6.0f);
					DMibExpect(Dst4D[2], ==, 0.0f);
					DMibExpect(Dst4D[3], ==, 0.0f);
				}

				{
					DMibTestPath("LargerToSmaller");
					CVec4Dfp32 Src4D(1.0f, 2.0f, 3.0f, 4.0f);
					CVec2Dfp32 Dst2D(0.0f, 0.0f);
					Dst2D = Src4D;
					DMibExpect(Dst2D[0], ==, 1.0f);
					DMibExpect(Dst2D[1], ==, 2.0f);
				}
			};

			DMibTestSuite("CopyAndMove")
			{
				{
					DMibTestPath("Copy");
					CVec3Dfp32 Src(1.0f, 2.0f, 3.0f);
					CVec3Dfp32 Dst(Src);
					DMibExpect(Dst[0], ==, 1.0f);
					DMibExpect(Dst[1], ==, 2.0f);
					DMibExpect(Dst[2], ==, 3.0f);
				}

				{
					DMibTestPath("Move");
					CVec3Dfp32 Src(1.0f, 2.0f, 3.0f);
					CVec3Dfp32 Dst(NMib::fg_Move(Src));
					DMibExpect(Dst[0], ==, 1.0f);
					DMibExpect(Dst[1], ==, 2.0f);
					DMibExpect(Dst[2], ==, 3.0f);
				}
			};
		}
	};

	DMibTestRegister(CVec_Tests, Malterlib::Numeric::Vector);
}
