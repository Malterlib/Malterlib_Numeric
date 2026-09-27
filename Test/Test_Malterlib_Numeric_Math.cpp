// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Numeric/Math>

using namespace NMib::NNumeric;
using namespace NMib::NStr;

namespace
{
	constexpr pfp32 gc_Pi = 3.14159265358979323846f;
	constexpr pfp32 gc_Tolerance = 1e-5f;

	bool fg_Near(pfp32 _Left, pfp32 _Right, pfp32 _Tolerance = gc_Tolerance)
	{
		return __builtin_fabsf(_Left - _Right) <= _Tolerance;
	}

	bool fg_Near(CVec3_fp32 const &_Left, CVec3_fp32 const &_Right, pfp32 _Tolerance = gc_Tolerance)
	{
		return fg_Near(_Left.f_GetX(), _Right.f_GetX(), _Tolerance)
			&& fg_Near(_Left.f_GetY(), _Right.f_GetY(), _Tolerance)
			&& fg_Near(_Left.f_GetZ(), _Right.f_GetZ(), _Tolerance)
			&& _Left.m_Value.f_GetLane(3) == 0.0f
			&& _Right.m_Value.f_GetLane(3) == 0.0f
		;
	}

	bool fg_Near(CVec4_fp32 const &_Left, CVec4_fp32 const &_Right, pfp32 _Tolerance = gc_Tolerance)
	{
		return fg_Near(_Left.f_GetX(), _Right.f_GetX(), _Tolerance)
			&& fg_Near(_Left.f_GetY(), _Right.f_GetY(), _Tolerance)
			&& fg_Near(_Left.f_GetZ(), _Right.f_GetZ(), _Tolerance)
			&& fg_Near(_Left.f_GetW(), _Right.f_GetW(), _Tolerance)
		;
	}

	bool fg_Near(CMat4x4_fp32 const &_Left, CMat4x4_fp32 const &_Right, pfp32 _Tolerance = gc_Tolerance)
	{
		for (umint iColumn = 0; iColumn < 4; ++iColumn)
		{
			if (!fg_Near(_Left.m_Columns[iColumn], _Right.m_Columns[iColumn], _Tolerance))
				return false;
		}

		return true;
	}

	struct CRandom
	{
		pfp32 f_Get(pfp32 _Min, pfp32 _Max)
		{
			m_State = m_State * 1664525u + 1013904223u;

			return _Min + (_Max - _Min) * (pfp32(m_State >> 8) / 16777216.0f);
		}

		uint32 m_State = 0x12345678;
	};

	struct CMath_Tests : public NMib::NTest::CTest
	{
		void f_DoTests()
		{
			DMibTestSuite("Vector")
			{
				CVec3_fp32 Left(1.0f, 2.0f, 3.0f);
				CVec3_fp32 Right(-4.0f, 5.0f, 0.5f);

				DMibExpect(Left.f_Dot(Right), ==, 7.5f);
				DMibExpectTrue(fg_Near(Left.f_Cross(Right), CVec3_fp32(-14.0f, -12.5f, 13.0f)));
				DMibExpectTrue(fg_Near(CVec3_fp32(1.0f, 0.0f, 0.0f).f_Cross(CVec3_fp32(0.0f, 1.0f, 0.0f)), CVec3_fp32(0.0f, 0.0f, 1.0f)));
				DMibExpectTrue(fg_Near(CVec3_fp32(3.0f, 4.0f, 0.0f).f_Length(), 5.0f));
				DMibExpectTrue(fg_Near(CVec3_fp32(0.0f, 0.0f, -7.0f).f_Normalized(), CVec3_fp32(0.0f, 0.0f, -1.0f)));
				DMibExpectTrue(fg_Near(Left + Right, CVec3_fp32(-3.0f, 7.0f, 3.5f)));
				DMibExpectTrue(fg_Near(Left - Right, CVec3_fp32(5.0f, -3.0f, 2.5f)));
				DMibExpectTrue(fg_Near(Left * 2.0f, CVec3_fp32(2.0f, 4.0f, 6.0f)));
				DMibExpectTrue(fg_Near(Left / 2.0f, CVec3_fp32(0.5f, 1.0f, 1.5f)));

				{
					DMibTestPath("Division");

					// Multiplying with the inverse rounds differently from dividing for these
					constexpr pfp32 c_Values[3] = {1.0f, 5.0f, 7.0f};
					constexpr pfp32 c_Divisors[4] = {3.0f, 49.0f, 10.0f, -0.7f};

					umint nMismatches = 0;

					for (pfp32 Divisor : c_Divisors)
					{
						CVec3_fp32 Divided = CVec3_fp32(c_Values[0], c_Values[1], c_Values[2]) / Divisor;
						CVec4_fp32 Divided4 = CVec4_fp32(c_Values[0], c_Values[1], c_Values[2], c_Values[1]) / Divisor;

						for (umint i = 0; i < 3; ++i)
						{
							nMismatches += Divided.m_Value.f_GetLane(i) != c_Values[i] / Divisor;
							nMismatches += Divided4.m_Value.f_GetLane(i) != c_Values[i] / Divisor;
						}

						nMismatches += Divided.m_Value.f_GetLane(3) != 0.0f;
						nMismatches += Divided4.m_Value.f_GetLane(3) != c_Values[1] / Divisor;
					}

					DMibExpect(nMismatches, ==, 0);

					// The lane that pads stays zero, which keeps the dot product and the length right
					CVec3_fp32 DividedByZero = CVec3_fp32(1.0f, 2.0f, 3.0f) / 0.0f;
					DMibExpect(DividedByZero.m_Value.f_GetLane(3), ==, 0.0f);
				}
				DMibExpectTrue(fg_Near(-Left, CVec3_fp32(-1.0f, -2.0f, -3.0f)));
				DMibExpectTrue(fg_Near(Left.f_Min(Right), CVec3_fp32(-4.0f, 2.0f, 0.5f)));
				DMibExpectTrue(fg_Near(Left.f_Max(Right), CVec3_fp32(1.0f, 5.0f, 3.0f)));
				DMibExpectTrue(fg_Near(CVec3_fp32::fs_Lerp(Left, Right, 0.5f), CVec3_fp32(-1.5f, 3.5f, 1.75f)));
				DMibExpectTrue(fg_Near(CVec3_fp32(2.0f), CVec3_fp32(2.0f, 2.0f, 2.0f)));

				pfp32 Stored[3] = {};
				Left.f_Store(Stored);
				DMibExpectTrue(fg_Near(CVec3_fp32::fs_Load(Stored), Left));

				CVec4_fp32 Left4(Left, 4.0f);
				DMibExpect(Left4.f_GetW(), ==, 4.0f);
				DMibExpect(Left4.f_Dot(CVec4_fp32(1.0f, 1.0f, 1.0f, 1.0f)), ==, 10.0f);
				DMibExpectTrue(fg_Near(Left4.f_GetXYZ(), Left));
				DMibExpectTrue(fg_Near(CVec4_fp32(0.0f, 0.0f, 3.0f, 4.0f).f_Normalized(), CVec4_fp32(0.0f, 0.0f, 0.6f, 0.8f)));
			};

			DMibTestSuite("Quaternion")
			{
				CQuat_fp32 QuarterTurnZ = CQuat_fp32::fs_FromAxisAngle(CVec3_fp32(0.0f, 0.0f, 1.0f), gc_Pi * 0.5f);
				CQuat_fp32 QuarterTurnX = CQuat_fp32::fs_FromAxisAngle(CVec3_fp32(1.0f, 0.0f, 0.0f), gc_Pi * 0.5f);

				DMibExpectTrue(fg_Near(QuarterTurnZ.f_Rotate(CVec3_fp32(1.0f, 0.0f, 0.0f)), CVec3_fp32(0.0f, 1.0f, 0.0f)));
				DMibExpectTrue(fg_Near(QuarterTurnX.f_Rotate(CVec3_fp32(0.0f, 1.0f, 0.0f)), CVec3_fp32(0.0f, 0.0f, 1.0f)));
				DMibExpectTrue(fg_Near(CQuat_fp32::fs_Identity().f_Rotate(CVec3_fp32(1.0f, 2.0f, 3.0f)), CVec3_fp32(1.0f, 2.0f, 3.0f)));

				{
					DMibTestPath("Composition");
					CVec3_fp32 Vector(1.0f, 2.0f, 3.0f);
					DMibExpectTrue(fg_Near((QuarterTurnX * QuarterTurnZ).f_Rotate(Vector), QuarterTurnX.f_Rotate(QuarterTurnZ.f_Rotate(Vector))));
				}

				{
					DMibTestPath("Conjugate");
					CVec3_fp32 Vector(1.0f, 2.0f, 3.0f);
					DMibExpectTrue(fg_Near(QuarterTurnZ.f_Conjugate().f_Rotate(QuarterTurnZ.f_Rotate(Vector)), Vector));
				}

				{
					DMibTestPath("MatchesMatrix");
					CQuat_fp32 Rotation = CQuat_fp32::fs_FromAxisAngle(CVec3_fp32(1.0f, 2.0f, -0.5f).f_Normalized(), 1.1f);
					CVec3_fp32 Vector(-2.0f, 0.25f, 4.0f);
					DMibExpectTrue(fg_Near(CMat4x4_fp32::fs_FromQuat(Rotation).f_TransformDirection(Vector), Rotation.f_Rotate(Vector)));
				}

				{
					DMibTestPath("NormalizedLerp");
					CQuat_fp32 Half = CQuat_fp32::fs_NormalizedLerp(CQuat_fp32::fs_Identity(), QuarterTurnZ, 0.5f);
					CQuat_fp32 Expected = CQuat_fp32::fs_FromAxisAngle(CVec3_fp32(0.0f, 0.0f, 1.0f), gc_Pi * 0.25f);
					DMibExpectTrue(fg_Near(CVec4_fp32(Half.m_Value), CVec4_fp32(Expected.m_Value)));

					CQuat_fp32 Negated(-QuarterTurnZ.m_Value);
					CQuat_fp32 HalfShortest = CQuat_fp32::fs_NormalizedLerp(CQuat_fp32::fs_Identity(), Negated, 0.5f);
					DMibExpectTrue(fg_Near(CVec4_fp32(HalfShortest.m_Value), CVec4_fp32(Expected.m_Value)));
				}
			};

			DMibTestSuite("Matrix")
			{
				CMat4x4_fp32 Transform = CMat4x4_fp32::fs_FromTransform
					(
						CVec3_fp32(1.0f, -2.0f, 3.0f)
						, CQuat_fp32::fs_FromAxisAngle(CVec3_fp32(0.0f, 1.0f, 0.0f), 0.7f)
						, CVec3_fp32(2.0f, 0.5f, 1.5f)
					)
				;

				{
					DMibTestPath("Identity");
					DMibExpectTrue(fg_Near(CMat4x4_fp32::fs_Identity() * Transform, Transform));
					DMibExpectTrue(fg_Near(Transform * CMat4x4_fp32::fs_Identity(), Transform));
				}

				{
					DMibTestPath("TransformOrder");
					CMat4x4_fp32 Composed = CMat4x4_fp32::fs_Translation(CVec3_fp32(1.0f, -2.0f, 3.0f))
						* CMat4x4_fp32::fs_FromQuat(CQuat_fp32::fs_FromAxisAngle(CVec3_fp32(0.0f, 1.0f, 0.0f), 0.7f))
						* CMat4x4_fp32::fs_Scale(CVec3_fp32(2.0f, 0.5f, 1.5f))
					;
					DMibExpectTrue(fg_Near(Composed, Transform));
					DMibExpectTrue(fg_Near(Transform.f_TransformPoint(CVec3_fp32::fs_Zero()), CVec3_fp32(1.0f, -2.0f, 3.0f)));
				}

				{
					DMibTestPath("StoreLoad");
					pfp32 Stored[16];
					Transform.f_Store(Stored);
					DMibExpect(Stored[12], ==, 1.0f);
					DMibExpect(Stored[13], ==, -2.0f);
					DMibExpect(Stored[14], ==, 3.0f);
					DMibExpect(Transform.f_Get(1, 3), ==, -2.0f);
					DMibExpectTrue(fg_Near(CMat4x4_fp32::fs_Load(Stored), Transform, 0.0f));
				}

				{
					DMibTestPath("Transposed");
					CMat4x4_fp32 Transposed = Transform.f_Transposed();
					DMibExpect(Transposed.f_Get(3, 1), ==, Transform.f_Get(1, 3));
					DMibExpectTrue(fg_Near(Transposed.f_Transposed(), Transform, 0.0f));
				}

				{
					DMibTestPath("Inverse");
					DMibExpectTrue(fg_Near(Transform.f_Inverse() * Transform, CMat4x4_fp32::fs_Identity()));
					DMibExpectTrue(fg_Near(Transform.f_InverseAffine() * Transform, CMat4x4_fp32::fs_Identity()));
					DMibExpectTrue(fg_Near(Transform.f_InverseAffine(), Transform.f_Inverse()));

					CMat4x4_fp32 Projection = CMat4x4_fp32::fs_Perspective(1.0f, 1.5f, 0.1f, 100.0f);
					DMibExpectTrue(fg_Near(Projection.f_Inverse() * Projection, CMat4x4_fp32::fs_Identity(), 1e-3f));
				}

				{
					DMibTestPath("Mat3x4");
					DMibExpectTrue(fg_Near(CMat3x4_fp32(Transform).f_ToMat4(), Transform, 0.0f));
				}

				{
					DMibTestPath("LookAt");
					CMat4x4_fp32 View = CMat4x4_fp32::fs_LookAt(CVec3_fp32(0.0f, 0.0f, 5.0f), CVec3_fp32::fs_Zero(), CVec3_fp32(0.0f, 1.0f, 0.0f));
					DMibExpectTrue(fg_Near(View.f_TransformPoint(CVec3_fp32::fs_Zero()), CVec3_fp32(0.0f, 0.0f, -5.0f)));
					DMibExpectTrue(fg_Near(View.f_TransformPoint(CVec3_fp32(1.0f, 2.0f, 0.0f)), CVec3_fp32(1.0f, 2.0f, -5.0f)));

					CMat4x4_fp32 SideView = CMat4x4_fp32::fs_LookAt(CVec3_fp32(5.0f, 0.0f, 0.0f), CVec3_fp32::fs_Zero(), CVec3_fp32(0.0f, 1.0f, 0.0f));
					DMibExpectTrue(fg_Near(SideView.f_TransformPoint(CVec3_fp32(0.0f, 0.0f, 1.0f)), CVec3_fp32(-1.0f, 0.0f, -5.0f)));
				}

				{
					DMibTestPath("Perspective");
					CMat4x4_fp32 Projection = CMat4x4_fp32::fs_Perspective(gc_Pi * 0.5f, 2.0f, 1.0f, 10.0f);

					CVec4_fp32 Near = Projection * CVec4_fp32(0.0f, 0.0f, -1.0f, 1.0f);
					DMibExpectTrue(fg_Near(Near.f_GetZ() / Near.f_GetW(), 0.0f));

					CVec4_fp32 Far = Projection * CVec4_fp32(0.0f, 0.0f, -10.0f, 1.0f);
					DMibExpectTrue(fg_Near(Far.f_GetZ() / Far.f_GetW(), 1.0f));

					CVec4_fp32 Corner = Projection * CVec4_fp32(2.0f, 1.0f, -1.0f, 1.0f);
					DMibExpectTrue(fg_Near(Corner.f_GetX() / Corner.f_GetW(), 1.0f));
					DMibExpectTrue(fg_Near(Corner.f_GetY() / Corner.f_GetW(), 1.0f));
				}

				{
					DMibTestPath("PerspectiveReverseInfinite");
					CMat4x4_fp32 Projection = CMat4x4_fp32::fs_PerspectiveReverseInfinite(gc_Pi * 0.5f, 2.0f, 1.0f);

					CVec4_fp32 Near = Projection * CVec4_fp32(0.0f, 0.0f, -1.0f, 1.0f);
					DMibExpectTrue(fg_Near(Near.f_GetZ() / Near.f_GetW(), 1.0f));

					CVec4_fp32 Distant = Projection * CVec4_fp32(0.0f, 0.0f, -1e6f, 1.0f);
					DMibExpectTrue(fg_Near(Distant.f_GetZ() / Distant.f_GetW(), 0.0f));
				}

				{
					DMibTestPath("Orthographic");
					CMat4x4_fp32 Projection = CMat4x4_fp32::fs_Orthographic(-2.0f, 4.0f, -1.0f, 3.0f, 1.0f, 11.0f);
					DMibExpectTrue(fg_Near(Projection * CVec4_fp32(-2.0f, -1.0f, -1.0f, 1.0f), CVec4_fp32(-1.0f, -1.0f, 0.0f, 1.0f)));
					DMibExpectTrue(fg_Near(Projection * CVec4_fp32(4.0f, 3.0f, -11.0f, 1.0f), CVec4_fp32(1.0f, 1.0f, 1.0f, 1.0f)));
				}
			};

			DMibTestSuite("Bounds")
			{
				CBox_fp32 Box(CVec3_fp32(-1.0f, -2.0f, -3.0f), CVec3_fp32(3.0f, 2.0f, 1.0f));

				DMibExpectTrue(fg_Near(Box.f_GetCenter(), CVec3_fp32(1.0f, 0.0f, -1.0f)));
				DMibExpectTrue(fg_Near(Box.f_GetExtent(), CVec3_fp32(2.0f, 2.0f, 2.0f)));

				CBox_fp32 Union = Box.f_Union(CBox_fp32(CVec3_fp32(0.0f, -5.0f, 0.0f), CVec3_fp32(1.0f, 0.0f, 4.0f)));
				DMibExpectTrue(fg_Near(Union.m_Min, CVec3_fp32(-1.0f, -5.0f, -3.0f)));
				DMibExpectTrue(fg_Near(Union.m_Max, CVec3_fp32(3.0f, 2.0f, 4.0f)));

				CMat4x4_fp32 QuarterTurn = CMat4x4_fp32::fs_Translation(CVec3_fp32(10.0f, 0.0f, 0.0f))
					* CMat4x4_fp32::fs_FromQuat(CQuat_fp32::fs_FromAxisAngle(CVec3_fp32(0.0f, 0.0f, 1.0f), gc_Pi * 0.5f))
				;
				CBox_fp32 Transformed = Box.f_Transformed(QuarterTurn);
				DMibExpectTrue(fg_Near(Transformed.m_Min, CVec3_fp32(8.0f, -1.0f, -3.0f)));
				DMibExpectTrue(fg_Near(Transformed.m_Max, CVec3_fp32(12.0f, 3.0f, 1.0f)));

				CSphere_fp32 Sphere(CVec3_fp32(1.0f, 2.0f, 3.0f), 4.0f);
				DMibExpectTrue(fg_Near(Sphere.f_GetCenter(), CVec3_fp32(1.0f, 2.0f, 3.0f)));
				DMibExpect(Sphere.f_GetRadius(), ==, 4.0f);

				CPlane_fp32 Plane = CPlane_fp32(CVec3_fp32(0.0f, 2.0f, 0.0f), -4.0f).f_Normalized();
				DMibExpectTrue(fg_Near(Plane.f_SignedDistance(CVec3_fp32(5.0f, 5.0f, 5.0f)), 3.0f));
				DMibExpectTrue(fg_Near(Plane.f_SignedDistance(CVec3_fp32(5.0f, 0.0f, 5.0f)), -2.0f));
			};

			DMibTestSuite("Frustum")
			{
				auto fCheckFrustum = [](CStr const &_Name, CMat4x4_fp32 const &_Projection)
					{
						DMibTestPath(_Name);

						CMat4x4_fp32 View = CMat4x4_fp32::fs_LookAt(CVec3_fp32(0.0f, 0.0f, 0.0f), CVec3_fp32(0.0f, 0.0f, -1.0f), CVec3_fp32(0.0f, 1.0f, 0.0f));
						CFrustum_fp32 Frustum(_Projection * View);

						DMibExpectTrue(Frustum.f_Intersects(CSphere_fp32(CVec3_fp32(0.0f, 0.0f, -10.0f), 1.0f)));
						DMibExpectFalse(Frustum.f_Intersects(CSphere_fp32(CVec3_fp32(0.0f, 0.0f, 10.0f), 1.0f)));
						DMibExpectFalse(Frustum.f_Intersects(CSphere_fp32(CVec3_fp32(50.0f, 0.0f, -10.0f), 1.0f)));
						DMibExpectFalse(Frustum.f_Intersects(CSphere_fp32(CVec3_fp32(0.0f, -50.0f, -10.0f), 1.0f)));
						DMibExpectTrue(Frustum.f_Intersects(CSphere_fp32(CVec3_fp32(10.5f, 0.0f, -10.0f), 1.0f)));
						DMibExpectTrue(Frustum.f_Intersects(CSphere_fp32(CVec3_fp32(0.0f, 0.0f, 0.5f), 2.0f)));

						DMibExpectTrue(Frustum.f_Intersects(CBox_fp32::fs_FromCenterExtent(CVec3_fp32(0.0f, 0.0f, -10.0f), CVec3_fp32(1.0f))));
						DMibExpectFalse(Frustum.f_Intersects(CBox_fp32::fs_FromCenterExtent(CVec3_fp32(0.0f, 0.0f, 10.0f), CVec3_fp32(1.0f))));
						DMibExpectFalse(Frustum.f_Intersects(CBox_fp32::fs_FromCenterExtent(CVec3_fp32(-50.0f, 0.0f, -10.0f), CVec3_fp32(1.0f))));
						DMibExpectTrue(Frustum.f_Intersects(CBox_fp32::fs_FromCenterExtent(CVec3_fp32(-10.5f, 0.0f, -10.0f), CVec3_fp32(1.0f))));
					}
				;

				fCheckFrustum("Perspective", CMat4x4_fp32::fs_Perspective(gc_Pi * 0.5f, 1.0f, 1.0f, 100.0f));
				fCheckFrustum("PerspectiveReverseInfinite", CMat4x4_fp32::fs_PerspectiveReverseInfinite(gc_Pi * 0.5f, 1.0f, 1.0f));

				{
					DMibTestPath("FarPlane");
					CFrustum_fp32 Frustum(CMat4x4_fp32::fs_Perspective(gc_Pi * 0.5f, 1.0f, 1.0f, 100.0f));
					DMibExpectFalse(Frustum.f_Intersects(CSphere_fp32(CVec3_fp32(0.0f, 0.0f, -200.0f), 1.0f)));

					CFrustum_fp32 Infinite(CMat4x4_fp32::fs_PerspectiveReverseInfinite(gc_Pi * 0.5f, 1.0f, 1.0f));
					DMibExpectTrue(Infinite.f_Intersects(CSphere_fp32(CVec3_fp32(0.0f, 0.0f, -200.0f), 1.0f)));
				}
			};

			DMibTestSuite("WideCulling")
			{
				CMat4x4_fp32 View = CMat4x4_fp32::fs_LookAt(CVec3_fp32(3.0f, 4.0f, 5.0f), CVec3_fp32(-1.0f, 0.0f, -20.0f), CVec3_fp32(0.0f, 1.0f, 0.0f));
				CFrustum_fp32 Frustum(CMat4x4_fp32::fs_Perspective(1.0f, 1.6f, 0.5f, 60.0f) * View);

				constexpr umint c_nObjects = 1003;

				pfp32 CenterX[c_nObjects];
				pfp32 CenterY[c_nObjects];
				pfp32 CenterZ[c_nObjects];
				pfp32 Radius[c_nObjects];
				pfp32 ExtentX[c_nObjects];
				pfp32 ExtentY[c_nObjects];
				pfp32 ExtentZ[c_nObjects];

				CRandom Random;
				for (umint i = 0; i < c_nObjects; ++i)
				{
					CenterX[i] = Random.f_Get(-60.0f, 60.0f);
					CenterY[i] = Random.f_Get(-60.0f, 60.0f);
					CenterZ[i] = Random.f_Get(-80.0f, 30.0f);
					Radius[i] = Random.f_Get(0.0f, 6.0f);
					ExtentX[i] = Random.f_Get(0.0f, 6.0f);
					ExtentY[i] = Random.f_Get(0.0f, 6.0f);
					ExtentZ[i] = Random.f_Get(0.0f, 6.0f);
				}

				auto fCheckCounts = [&](CStr const &_Name, umint _nObjects)
					{
						DMibTestPath(_Name);

						uint8 VisibleSpheres[c_nObjects + 1];
						uint8 VisibleBoxes[c_nObjects + 1];
						for (umint i = 0; i <= c_nObjects; ++i)
						{
							VisibleSpheres[i] = 0xcc;
							VisibleBoxes[i] = 0xcc;
						}

						Frustum.f_CullSpheres(CenterX, CenterY, CenterZ, Radius, _nObjects, VisibleSpheres);
						Frustum.f_CullBoxes(CenterX, CenterY, CenterZ, ExtentX, ExtentY, ExtentZ, _nObjects, VisibleBoxes);

						umint nSphereMismatches = 0;
						umint nBoxMismatches = 0;
						umint nVisibleSpheres = 0;
						umint nVisibleBoxes = 0;

						for (umint i = 0; i < _nObjects; ++i)
						{
							CVec3_fp32 Center(CenterX[i], CenterY[i], CenterZ[i]);
							bool bSphere = Frustum.f_Intersects(CSphere_fp32(Center, Radius[i]));
							bool bBox = Frustum.f_Intersects(CBox_fp32::fs_FromCenterExtent(Center, CVec3_fp32(ExtentX[i], ExtentY[i], ExtentZ[i])));

							nSphereMismatches += VisibleSpheres[i] != uint8(bSphere);
							nBoxMismatches += VisibleBoxes[i] != uint8(bBox);
							nVisibleSpheres += bSphere;
							nVisibleBoxes += bBox;
						}

						DMibExpect(nSphereMismatches, ==, 0);
						DMibExpect(nBoxMismatches, ==, 0);
						DMibExpect(VisibleSpheres[_nObjects], ==, 0xcc);
						DMibExpect(VisibleBoxes[_nObjects], ==, 0xcc);

						if (_nObjects == c_nObjects)
						{
							DMibExpect(nVisibleSpheres, >, 20);
							DMibExpect(nVisibleSpheres, <, c_nObjects - 20);
							DMibExpect(nVisibleBoxes, >, 20);
							DMibExpect(nVisibleBoxes, <, c_nObjects - 20);
						}
					}
				;

				fCheckCounts("All", c_nObjects);
				fCheckCounts("Empty", 0);
				fCheckCounts("One", 1);
				fCheckCounts("Seven", 7);
				fCheckCounts("Eight", 8);
				fCheckCounts("Nine", 9);
			};
		}
	};

	DMibTestRegister(CMath_Tests, Malterlib::Numeric::Math);
}
