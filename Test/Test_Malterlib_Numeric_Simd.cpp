// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Numeric/Simd>

using namespace NMib::NNumeric;
using namespace NMib::NStr;

namespace
{
	constexpr pfp32 gc_Infinity = __builtin_inff();
	constexpr pfp32 gc_NaN = __builtin_nanf("");

	constexpr pfp32 gc_FloatValues[] =
		{
			0.0f
			, -0.0f
			, 1.0f
			, -1.0f
			, 0.5f
			, -0.5f
			, 1.5f
			, -1.5f
			, 2.5f
			, -3.75f
			, 0.999999f
			, -0.000001f
			, 1e-40f
			, -1e-40f
			, 1.17549435e-38f
			, 3.40282347e+38f
			, -3.40282347e+38f
			, gc_Infinity
			, -gc_Infinity
			, gc_NaN
			, 8388607.5f
			, -8388607.5f
			, 8388608.0f
			, 16777216.0f
			, -16777217.0f
			, 123456.789f
			, 1e10f
			, -1e-10f
		}
	;

	constexpr pfp32 gc_FloatValuesInIntRange[] = {0.0f, -0.0f, 1.0f, -1.0f, 0.5f, -0.5f, 1.999f, -1.999f, 123456.789f, -2147483520.0f, 2147483520.0f, 1e-40f};

	constexpr int32 gc_IntValues[] =
		{
			0
			, 1
			, -1
			, 2
			, -2
			, 7
			, -13
			, 255
			, 65535
			, 65536
			, -65537
			, 0x7fffffff
			, int32(0x80000000u)
			, int32(0x80000001u)
			, 0x12345678
			, int32(0xdeadbeefu)
			, 46341
			, -46341
		}
	;

	constexpr umint gc_nIntValues = sizeof(gc_IntValues) / sizeof(gc_IntValues[0]);

	bool fg_SameFloat(pfp32 _Left, pfp32 _Right)
	{
		if (_Left != _Left && _Right != _Right)
			return true;

		return __builtin_bit_cast(uint32, _Left) == __builtin_bit_cast(uint32, _Right);
	}

	template <umint t_nLanes>
	struct TCSimdTester
	{
		using CFloat = TCSimd<pfp32, t_nLanes>;
		using CInt = TCSimd<int32, t_nLanes>;
		using CMask = TCSimd<bool, t_nLanes>;
		using CFloatReference = TCSimdReference<pfp32, t_nLanes>;
		using CIntReference = TCSimdReference<int32, t_nLanes>;
		using CMaskReference = TCSimdReference<bool, t_nLanes>;

		static bool fs_Same(CFloat const &_Value, CFloatReference const &_Reference)
		{
			pfp32 Value[t_nLanes];
			pfp32 Reference[t_nLanes];
			_Value.f_Store(Value);
			_Reference.f_Store(Reference);

			for (umint i = 0; i < t_nLanes; ++i)
			{
				if (!fg_SameFloat(Value[i], Reference[i]))
					return false;
			}

			return true;
		}

		static bool fs_Same(CInt const &_Value, CIntReference const &_Reference)
		{
			int32 Value[t_nLanes];
			int32 Reference[t_nLanes];
			_Value.f_Store(Value);
			_Reference.f_Store(Reference);

			for (umint i = 0; i < t_nLanes; ++i)
			{
				if (Value[i] != Reference[i])
					return false;
			}

			return true;
		}

		static bool fs_Same(CMask const &_Value, CMaskReference const &_Reference)
		{
			return _Value.f_GetBits() == _Reference.f_GetBits()
				&& _Value.f_Any() == _Reference.f_Any()
				&& _Value.f_All() == _Reference.f_All()
				&& _Value.f_None() == _Reference.f_None()
				&& fs_Same(_Value.f_ToInt(), _Reference.f_ToInt())
			;
		}

		static bool fs_Same(pfp32 _Value, pfp32 _Reference)
		{
			return fg_SameFloat(_Value, _Reference);
		}

		template <typename tf_CValue, umint tf_nValues>
		static void fs_Fill(tf_CValue *o_pLanes, tf_CValue const (&_Values)[tf_nValues], umint _iStart, umint _Step)
		{
			for (umint i = 0; i < t_nLanes; ++i)
				o_pLanes[i] = _Values[(_iStart + i * _Step) % tf_nValues];
		}

		// Returns the number of input combinations where the native and reference results differ.
		template <typename tf_FOperation, umint tf_nValues>
		static umint fs_CountFloatMismatches(pfp32 const (&_Values)[tf_nValues], tf_FOperation &&_fOperation)
		{
			umint nMismatches = 0;

			for (umint iLeft = 0; iLeft < tf_nValues; ++iLeft)
			{
				for (umint iRight = 0; iRight < tf_nValues; ++iRight)
				{
					pfp32 Left[t_nLanes];
					pfp32 Right[t_nLanes];
					fs_Fill(Left, _Values, iLeft, 1);
					fs_Fill(Right, _Values, iRight, 3);

					auto Native = _fOperation(CFloat::fs_Load(Left), CFloat::fs_Load(Right));
					auto Reference = _fOperation(CFloatReference::fs_Load(Left), CFloatReference::fs_Load(Right));

					if (!fs_Same(Native, Reference))
						++nMismatches;
				}
			}

			return nMismatches;
		}

		template <typename tf_FOperation>
		static umint fs_CountIntMismatches(tf_FOperation &&_fOperation)
		{
			umint nMismatches = 0;

			for (umint iLeft = 0; iLeft < gc_nIntValues; ++iLeft)
			{
				for (umint iRight = 0; iRight < gc_nIntValues; ++iRight)
				{
					int32 Left[t_nLanes];
					int32 Right[t_nLanes];
					fs_Fill(Left, gc_IntValues, iLeft, 1);
					fs_Fill(Right, gc_IntValues, iRight, 5);

					auto Native = _fOperation(CInt::fs_Load(Left), CInt::fs_Load(Right));
					auto Reference = _fOperation(CIntReference::fs_Load(Left), CIntReference::fs_Load(Right));

					if (!fs_Same(Native, Reference))
						++nMismatches;
				}
			}

			return nMismatches;
		}

		static void fs_TestFloat()
		{
#			define DCheckFloat(d_Name, d_Values, ...) \
				{ \
					DMibTestPath("{}/Float/" d_Name ""_f << t_nLanes); \
					DMibExpect(fs_CountFloatMismatches(d_Values, [](auto const &_Left, auto const &_Right) { return __VA_ARGS__; }), ==, 0); \
				}

			DCheckFloat("Add", gc_FloatValues, _Left + _Right);
			DCheckFloat("Sub", gc_FloatValues, _Left - _Right);
			DCheckFloat("Mul", gc_FloatValues, _Left * _Right);
			DCheckFloat("Div", gc_FloatValues, _Left / _Right);
			DCheckFloat("Neg", gc_FloatValues, -_Left);
			DCheckFloat("Min", gc_FloatValues, _Left.f_Min(_Right));
			DCheckFloat("Max", gc_FloatValues, _Left.f_Max(_Right));
			DCheckFloat("Clamp", gc_FloatValues, _Left.f_Clamp(_Right, _Right + 2.0f));
			DCheckFloat("Abs", gc_FloatValues, _Left.f_Abs());
			DCheckFloat("Sqrt", gc_FloatValues, _Left.f_Sqrt());
			DCheckFloat("Floor", gc_FloatValues, _Left.f_Floor());
			DCheckFloat("Ceil", gc_FloatValues, _Left.f_Ceil());
			DCheckFloat("Sum", gc_FloatValues, _Left.f_Sum());
			DCheckFloat("SumOfProducts", gc_FloatValues, (_Left * _Right).f_Sum());
			DCheckFloat("Equal", gc_FloatValues, _Left == _Right);
			DCheckFloat("NotEqual", gc_FloatValues, _Left != _Right);
			DCheckFloat("Less", gc_FloatValues, _Left < _Right);
			DCheckFloat("Greater", gc_FloatValues, _Left > _Right);
			DCheckFloat("LessEqual", gc_FloatValues, _Left <= _Right);
			DCheckFloat("GreaterEqual", gc_FloatValues, _Left >= _Right);
			DCheckFloat("MaskAnd", gc_FloatValues, (_Left < _Right) & (_Left > 0.0f));
			DCheckFloat("MaskOr", gc_FloatValues, (_Left < _Right) | (_Left > 0.0f));
			DCheckFloat("MaskXor", gc_FloatValues, (_Left < _Right) ^ (_Left > 0.0f));
			DCheckFloat("MaskNot", gc_FloatValues, ~(_Left < _Right));
			DCheckFloat("Select", gc_FloatValues, _Left.fs_Select(_Left < _Right, _Left, _Right));
			DCheckFloat("ToBits", gc_FloatValues, _Left.f_ToBits());
			DCheckFloat("FromBits", gc_FloatValues, _Left.fs_FromBits(_Left.f_ToBits() ^ _Right.f_ToBits()));
			DCheckFloat("ScalarLeft", gc_FloatValues, 2.0f * _Left - 1.0f / _Right);
			DCheckFloat("CompoundAssign", gc_FloatValues, [&] { auto Value = _Left; Value += _Right; Value *= _Left; Value -= _Right; Value /= _Left; return Value; }());
			DCheckFloat("ToInt", gc_FloatValuesInIntRange, _Left.f_ToInt());
			DCheckFloat("SetLane", gc_FloatValues, [&] { auto Value = _Left; Value.f_SetLane(t_nLanes - 1, _Right.f_GetLane(0)); return Value; }());
			DCheckFloat("Splat", gc_FloatValues, NMib::NTraits::TCRemoveReferenceAndQualifiers<decltype(_Left)>(_Right.f_GetLane(t_nLanes / 2)));

#			undef DCheckFloat
		}

		static void fs_TestInt()
		{
#			define DCheckInt(d_Name, ...) \
				{ \
					DMibTestPath("{}/Int/" d_Name ""_f << t_nLanes); \
					DMibExpect(fs_CountIntMismatches([](auto const &_Left, auto const &_Right) { return __VA_ARGS__; }), ==, 0); \
				}

			DCheckInt("Add", _Left + _Right);
			DCheckInt("Sub", _Left - _Right);
			DCheckInt("Mul", _Left * _Right);
			DCheckInt("Neg", -_Left);
			DCheckInt("Min", _Left.f_Min(_Right));
			DCheckInt("Max", _Left.f_Max(_Right));
			DCheckInt("Abs", _Left.f_Abs());
			DCheckInt("And", _Left & _Right);
			DCheckInt("Or", _Left | _Right);
			DCheckInt("Xor", _Left ^ _Right);
			DCheckInt("Not", ~_Left);
			DCheckInt("ShiftLeft0", _Left << 0);
			DCheckInt("ShiftLeft5", _Left << 5);
			DCheckInt("ShiftLeft31", _Left << 31);
			DCheckInt("ShiftRight0", _Left >> 0);
			DCheckInt("ShiftRight5", _Left >> 5);
			DCheckInt("ShiftRight31", _Left >> 31);
			DCheckInt("ShiftRightLogical0", _Left.f_ShiftRightLogical(0));
			DCheckInt("ShiftRightLogical5", _Left.f_ShiftRightLogical(5));
			DCheckInt("ShiftRightLogical31", _Left.f_ShiftRightLogical(31));
			DCheckInt("Equal", _Left == _Right);
			DCheckInt("NotEqual", _Left != _Right);
			DCheckInt("Less", _Left < _Right);
			DCheckInt("Greater", _Left > _Right);
			DCheckInt("LessEqual", _Left <= _Right);
			DCheckInt("GreaterEqual", _Left >= _Right);
			DCheckInt("Select", _Left.fs_Select(_Left < _Right, _Left, _Right));
			DCheckInt("ToFloat", _Left.f_ToFloat());
			DCheckInt("CompoundAssign", [&] { auto Value = _Left; Value += _Right; Value *= _Left; Value -= _Right; Value ^= _Left; Value <<= 3; Value >>= 1; return Value; }());
			DCheckInt("SetLane", [&] { auto Value = _Left; Value.f_SetLane(t_nLanes - 1, _Right.f_GetLane(0)); return Value; }());

#			undef DCheckInt
		}
	};

	struct CSimd_Tests : public NMib::NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("MatchesReference")
			{
				TCSimdTester<4>::fs_TestFloat();
				TCSimdTester<4>::fs_TestInt();
				TCSimdTester<8>::fs_TestFloat();
				TCSimdTester<8>::fs_TestInt();
				TCSimdTester<16>::fs_TestFloat();
				TCSimdTester<16>::fs_TestInt();
			};

			DMibTestSuite("General")
			{
				{
					DMibTestPath("LaneConstruction");
					CSimd4_fp32 Value(1.0f, 2.0f, 3.0f, 4.0f);
					DMibExpect(Value.f_GetLane(0), ==, 1.0f);
					DMibExpect(Value.f_GetLane(1), ==, 2.0f);
					DMibExpect(Value.f_GetLane(2), ==, 3.0f);
					DMibExpect(Value.f_GetLane(3), ==, 4.0f);
				}

				{
					DMibTestPath("Shuffle");
					CSimd4_fp32 Value = CSimd4_fp32(1.0f, 2.0f, 3.0f, 4.0f).f_Shuffle<3, 0, 2, 2>();
					DMibExpect(Value.f_GetLane(0), ==, 4.0f);
					DMibExpect(Value.f_GetLane(1), ==, 1.0f);
					DMibExpect(Value.f_GetLane(2), ==, 3.0f);
					DMibExpect(Value.f_GetLane(3), ==, 3.0f);

					CSimd4_int32 IntValue = CSimd4_int32(1, 2, 3, 4).f_Shuffle<1, 1, 0, 3>();
					DMibExpect(IntValue.f_GetLane(0), ==, 2);
					DMibExpect(IntValue.f_GetLane(1), ==, 2);
					DMibExpect(IntValue.f_GetLane(2), ==, 1);
					DMibExpect(IntValue.f_GetLane(3), ==, 4);
				}

				{
					DMibTestPath("MaskBits");
					CSimd8_fp32 Value(1.0f, -1.0f, 2.0f, -2.0f, -3.0f, 3.0f, -4.0f, -5.0f);
					DMibExpect((Value < 0.0f).f_GetBits(), ==, 0xdau);
					DMibExpectTrue((Value < 0.0f).f_GetLane(1));
					DMibExpectFalse((Value < 0.0f).f_GetLane(2));
					DMibExpectTrue(CSimd8_bool::fs_True().f_All());
					DMibExpectTrue(CSimd8_bool::fs_False().f_None());
				}

				{
					DMibTestPath("SumOrder");
					// Adding in lane order would lose both small values
					DMibExpect(CSimd4_fp32(1e20f, -1e20f, 1.0f, 2.0f).f_Sum(), ==, 3.0f);
				}

				{
					DMibTestPath("Aligned");
					alignas(32) pfp32 Source[8] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
					alignas(32) pfp32 Destination[8] = {};
					(CSimd8_fp32::fs_LoadAligned(Source) * 2.0f).f_StoreAligned(Destination);
					DMibExpect(Destination[0], ==, 2.0f);
					DMibExpect(Destination[7], ==, 16.0f);
				}
			};
		}
	};

	DMibTestRegister(CSimd_Tests, Malterlib::Numeric::Simd);
}
