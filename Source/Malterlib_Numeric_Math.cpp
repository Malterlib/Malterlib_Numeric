// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "Malterlib_Numeric_Math.h"

namespace NMib::NNumeric
{
	// CQuat_fp32

	// _Axis must be normalized.
	CQuat_fp32 CQuat_fp32::fs_FromAxisAngle(CVec3_fp32 const &_Axis, pfp32 _Radians)
	{
		pfp32 HalfAngle = _Radians * 0.5f;

		return CQuat_fp32(CVec4_fp32(_Axis * __builtin_sinf(HalfAngle), __builtin_cosf(HalfAngle)).m_Value);
	}

	// Interpolates along the shorter arc.
	CQuat_fp32 CQuat_fp32::fs_NormalizedLerp(CQuat_fp32 const &_From, CQuat_fp32 const &_To, pfp32 _Fraction)
	{
		CSimd4_fp32 To = _To.m_Value;
		if ((_From.m_Value * To).f_Sum() < 0.0f)
			To = -To;

		return CQuat_fp32(_From.m_Value + (To - _From.m_Value) * CSimd4_fp32(_Fraction)).f_Normalized();
	}

	// The quaternion must be normalized.
	CVec3_fp32 CQuat_fp32::f_Rotate(CVec3_fp32 const &_Vector) const
	{
		CVec3_fp32 Axis = CVec4_fp32(m_Value).f_GetXYZ();
		CVec3_fp32 Cross = Axis.f_Cross(_Vector);

		return _Vector + Cross * (2.0f * f_GetW()) + Axis.f_Cross(Cross) * 2.0f;
	}

	// The result applies _Right first, then this.
	CQuat_fp32 CQuat_fp32::operator * (CQuat_fp32 const &_Right) const
	{
		CVec3_fp32 LeftAxis = CVec4_fp32(m_Value).f_GetXYZ();
		CVec3_fp32 RightAxis = CVec4_fp32(_Right.m_Value).f_GetXYZ();
		pfp32 LeftW = f_GetW();
		pfp32 RightW = _Right.f_GetW();

		return CQuat_fp32(CVec4_fp32(RightAxis * LeftW + LeftAxis * RightW + LeftAxis.f_Cross(RightAxis), LeftW * RightW - LeftAxis.f_Dot(RightAxis)).m_Value);
	}

	// CMat4x4_fp32

	CMat4x4_fp32 CMat4x4_fp32::fs_Identity()
	{
		return CMat4x4_fp32
			(
				CVec4_fp32(1.0f, 0.0f, 0.0f, 0.0f)
				, CVec4_fp32(0.0f, 1.0f, 0.0f, 0.0f)
				, CVec4_fp32(0.0f, 0.0f, 1.0f, 0.0f)
				, CVec4_fp32(0.0f, 0.0f, 0.0f, 1.0f)
			)
		;
	}

	// Reads 16 values in column-major order.
	CMat4x4_fp32 CMat4x4_fp32::fs_Load(pfp32 const *_pSource)
	{
		return CMat4x4_fp32(CVec4_fp32::fs_Load(_pSource), CVec4_fp32::fs_Load(_pSource + 4), CVec4_fp32::fs_Load(_pSource + 8), CVec4_fp32::fs_Load(_pSource + 12));
	}

	CMat4x4_fp32 CMat4x4_fp32::fs_Translation(CVec3_fp32 const &_Translation)
	{
		CMat4x4_fp32 Result = fs_Identity();
		Result.m_Columns[3] = CVec4_fp32(_Translation, 1.0f);

		return Result;
	}

	CMat4x4_fp32 CMat4x4_fp32::fs_Scale(CVec3_fp32 const &_Scale)
	{
		return CMat4x4_fp32
			(
				CVec4_fp32(_Scale.f_GetX(), 0.0f, 0.0f, 0.0f)
				, CVec4_fp32(0.0f, _Scale.f_GetY(), 0.0f, 0.0f)
				, CVec4_fp32(0.0f, 0.0f, _Scale.f_GetZ(), 0.0f)
				, CVec4_fp32(0.0f, 0.0f, 0.0f, 1.0f)
			)
		;
	}

	// _Rotation must be normalized.
	CMat4x4_fp32 CMat4x4_fp32::fs_FromQuat(CQuat_fp32 const &_Rotation)
	{
		pfp32 X = _Rotation.f_GetX();
		pfp32 Y = _Rotation.f_GetY();
		pfp32 Z = _Rotation.f_GetZ();
		pfp32 W = _Rotation.f_GetW();

		return CMat4x4_fp32
			(
				CVec4_fp32(1.0f - 2.0f * (Y * Y + Z * Z), 2.0f * (X * Y + Z * W), 2.0f * (X * Z - Y * W), 0.0f)
				, CVec4_fp32(2.0f * (X * Y - Z * W), 1.0f - 2.0f * (X * X + Z * Z), 2.0f * (Y * Z + X * W), 0.0f)
				, CVec4_fp32(2.0f * (X * Z + Y * W), 2.0f * (Y * Z - X * W), 1.0f - 2.0f * (X * X + Y * Y), 0.0f)
				, CVec4_fp32(0.0f, 0.0f, 0.0f, 1.0f)
			)
		;
	}

	// Scales first, then rotates, then translates.
	CMat4x4_fp32 CMat4x4_fp32::fs_FromTransform(CVec3_fp32 const &_Translation, CQuat_fp32 const &_Rotation, CVec3_fp32 const &_Scale)
	{
		CMat4x4_fp32 Result = fs_FromQuat(_Rotation);
		Result.m_Columns[0] = Result.m_Columns[0] * _Scale.f_GetX();
		Result.m_Columns[1] = Result.m_Columns[1] * _Scale.f_GetY();
		Result.m_Columns[2] = Result.m_Columns[2] * _Scale.f_GetZ();
		Result.m_Columns[3] = CVec4_fp32(_Translation, 1.0f);

		return Result;
	}

	// _Up must not be parallel to the view direction.
	CMat4x4_fp32 CMat4x4_fp32::fs_LookAt(CVec3_fp32 const &_Eye, CVec3_fp32 const &_Target, CVec3_fp32 const &_Up)
	{
		CVec3_fp32 Forward = (_Target - _Eye).f_Normalized();
		CVec3_fp32 Side = Forward.f_Cross(_Up).f_Normalized();
		CVec3_fp32 Up = Side.f_Cross(Forward);

		return CMat4x4_fp32
			(
				CVec4_fp32(Side.f_GetX(), Up.f_GetX(), -Forward.f_GetX(), 0.0f)
				, CVec4_fp32(Side.f_GetY(), Up.f_GetY(), -Forward.f_GetY(), 0.0f)
				, CVec4_fp32(Side.f_GetZ(), Up.f_GetZ(), -Forward.f_GetZ(), 0.0f)
				, CVec4_fp32(-Side.f_Dot(_Eye), -Up.f_Dot(_Eye), Forward.f_Dot(_Eye), 1.0f)
			)
		;
	}

	// _FieldOfViewY is in radians. Depth is 0 at _Near and 1 at _Far.
	CMat4x4_fp32 CMat4x4_fp32::fs_Perspective(pfp32 _FieldOfViewY, pfp32 _AspectRatio, pfp32 _Near, pfp32 _Far)
	{
		pfp32 Focal = 1.0f / __builtin_tanf(_FieldOfViewY * 0.5f);

		return CMat4x4_fp32
			(
				CVec4_fp32(Focal / _AspectRatio, 0.0f, 0.0f, 0.0f)
				, CVec4_fp32(0.0f, Focal, 0.0f, 0.0f)
				, CVec4_fp32(0.0f, 0.0f, _Far / (_Near - _Far), -1.0f)
				, CVec4_fp32(0.0f, 0.0f, _Near * _Far / (_Near - _Far), 0.0f)
			)
		;
	}

	// _FieldOfViewY is in radians. Depth is 1 at _Near and approaches 0 at infinity.
	CMat4x4_fp32 CMat4x4_fp32::fs_PerspectiveReverseInfinite(pfp32 _FieldOfViewY, pfp32 _AspectRatio, pfp32 _Near)
	{
		pfp32 Focal = 1.0f / __builtin_tanf(_FieldOfViewY * 0.5f);

		return CMat4x4_fp32
			(
				CVec4_fp32(Focal / _AspectRatio, 0.0f, 0.0f, 0.0f)
				, CVec4_fp32(0.0f, Focal, 0.0f, 0.0f)
				, CVec4_fp32(0.0f, 0.0f, 0.0f, -1.0f)
				, CVec4_fp32(0.0f, 0.0f, _Near, 0.0f)
			)
		;
	}

	// Depth is 0 at _Near and 1 at _Far.
	CMat4x4_fp32 CMat4x4_fp32::fs_Orthographic(pfp32 _Left, pfp32 _Right, pfp32 _Bottom, pfp32 _Top, pfp32 _Near, pfp32 _Far)
	{
		return CMat4x4_fp32
			(
				CVec4_fp32(2.0f / (_Right - _Left), 0.0f, 0.0f, 0.0f)
				, CVec4_fp32(0.0f, 2.0f / (_Top - _Bottom), 0.0f, 0.0f)
				, CVec4_fp32(0.0f, 0.0f, 1.0f / (_Near - _Far), 0.0f)
				, CVec4_fp32(-(_Right + _Left) / (_Right - _Left), -(_Top + _Bottom) / (_Top - _Bottom), _Near / (_Near - _Far), 1.0f)
			)
		;
	}

	// Writes 16 values in column-major order.
	void CMat4x4_fp32::f_Store(pfp32 *o_pDestination) const
	{
		for (umint iColumn = 0; iColumn < 4; ++iColumn)
			m_Columns[iColumn].f_Store(o_pDestination + iColumn * 4);
	}

	pfp32 CMat4x4_fp32::f_Get(umint _iRow, umint _iColumn) const
	{
		return m_Columns[_iColumn].m_Value.f_GetLane(_iRow);
	}

	CVec4_fp32 CMat4x4_fp32::f_GetRow(umint _iRow) const
	{
		return CVec4_fp32(f_Get(_iRow, 0), f_Get(_iRow, 1), f_Get(_iRow, 2), f_Get(_iRow, 3));
	}

	// The matrix must be affine.
	CVec3_fp32 CMat4x4_fp32::f_TransformPoint(CVec3_fp32 const &_Point) const
	{
		return (*this * CVec4_fp32(_Point, 1.0f)).f_GetXYZ();
	}

	CVec3_fp32 CMat4x4_fp32::f_TransformDirection(CVec3_fp32 const &_Direction) const
	{
		return (*this * CVec4_fp32(_Direction, 0.0f)).f_GetXYZ();
	}

	CMat4x4_fp32 CMat4x4_fp32::f_Transposed() const
	{
		return CMat4x4_fp32(f_GetRow(0), f_GetRow(1), f_GetRow(2), f_GetRow(3));
	}

	// The matrix must be invertible.
	CMat4x4_fp32 CMat4x4_fp32::f_Inverse() const
	{
		pfp32 Source[16];
		f_Store(Source);

		pfp32 Inverse[16];

		Inverse[0] = Source[5] * Source[10] * Source[15] - Source[5] * Source[11] * Source[14] - Source[9] * Source[6] * Source[15]
			+ Source[9] * Source[7] * Source[14] + Source[13] * Source[6] * Source[11] - Source[13] * Source[7] * Source[10]
		;
		Inverse[4] = -Source[4] * Source[10] * Source[15] + Source[4] * Source[11] * Source[14] + Source[8] * Source[6] * Source[15]
			- Source[8] * Source[7] * Source[14] - Source[12] * Source[6] * Source[11] + Source[12] * Source[7] * Source[10]
		;
		Inverse[8] = Source[4] * Source[9] * Source[15] - Source[4] * Source[11] * Source[13] - Source[8] * Source[5] * Source[15]
			+ Source[8] * Source[7] * Source[13] + Source[12] * Source[5] * Source[11] - Source[12] * Source[7] * Source[9]
		;
		Inverse[12] = -Source[4] * Source[9] * Source[14] + Source[4] * Source[10] * Source[13] + Source[8] * Source[5] * Source[14]
			- Source[8] * Source[6] * Source[13] - Source[12] * Source[5] * Source[10] + Source[12] * Source[6] * Source[9]
		;
		Inverse[1] = -Source[1] * Source[10] * Source[15] + Source[1] * Source[11] * Source[14] + Source[9] * Source[2] * Source[15]
			- Source[9] * Source[3] * Source[14] - Source[13] * Source[2] * Source[11] + Source[13] * Source[3] * Source[10]
		;
		Inverse[5] = Source[0] * Source[10] * Source[15] - Source[0] * Source[11] * Source[14] - Source[8] * Source[2] * Source[15]
			+ Source[8] * Source[3] * Source[14] + Source[12] * Source[2] * Source[11] - Source[12] * Source[3] * Source[10]
		;
		Inverse[9] = -Source[0] * Source[9] * Source[15] + Source[0] * Source[11] * Source[13] + Source[8] * Source[1] * Source[15]
			- Source[8] * Source[3] * Source[13] - Source[12] * Source[1] * Source[11] + Source[12] * Source[3] * Source[9]
		;
		Inverse[13] = Source[0] * Source[9] * Source[14] - Source[0] * Source[10] * Source[13] - Source[8] * Source[1] * Source[14]
			+ Source[8] * Source[2] * Source[13] + Source[12] * Source[1] * Source[10] - Source[12] * Source[2] * Source[9]
		;
		Inverse[2] = Source[1] * Source[6] * Source[15] - Source[1] * Source[7] * Source[14] - Source[5] * Source[2] * Source[15]
			+ Source[5] * Source[3] * Source[14] + Source[13] * Source[2] * Source[7] - Source[13] * Source[3] * Source[6]
		;
		Inverse[6] = -Source[0] * Source[6] * Source[15] + Source[0] * Source[7] * Source[14] + Source[4] * Source[2] * Source[15]
			- Source[4] * Source[3] * Source[14] - Source[12] * Source[2] * Source[7] + Source[12] * Source[3] * Source[6]
		;
		Inverse[10] = Source[0] * Source[5] * Source[15] - Source[0] * Source[7] * Source[13] - Source[4] * Source[1] * Source[15]
			+ Source[4] * Source[3] * Source[13] + Source[12] * Source[1] * Source[7] - Source[12] * Source[3] * Source[5]
		;
		Inverse[14] = -Source[0] * Source[5] * Source[14] + Source[0] * Source[6] * Source[13] + Source[4] * Source[1] * Source[14]
			- Source[4] * Source[2] * Source[13] - Source[12] * Source[1] * Source[6] + Source[12] * Source[2] * Source[5]
		;
		Inverse[3] = -Source[1] * Source[6] * Source[11] + Source[1] * Source[7] * Source[10] + Source[5] * Source[2] * Source[11]
			- Source[5] * Source[3] * Source[10] - Source[9] * Source[2] * Source[7] + Source[9] * Source[3] * Source[6]
		;
		Inverse[7] = Source[0] * Source[6] * Source[11] - Source[0] * Source[7] * Source[10] - Source[4] * Source[2] * Source[11]
			+ Source[4] * Source[3] * Source[10] + Source[8] * Source[2] * Source[7] - Source[8] * Source[3] * Source[6]
		;
		Inverse[11] = -Source[0] * Source[5] * Source[11] + Source[0] * Source[7] * Source[9] + Source[4] * Source[1] * Source[11]
			- Source[4] * Source[3] * Source[9] - Source[8] * Source[1] * Source[7] + Source[8] * Source[3] * Source[5]
		;
		Inverse[15] = Source[0] * Source[5] * Source[10] - Source[0] * Source[6] * Source[9] - Source[4] * Source[1] * Source[10]
			+ Source[4] * Source[2] * Source[9] + Source[8] * Source[1] * Source[6] - Source[8] * Source[2] * Source[5]
		;

		pfp32 Determinant = Source[0] * Inverse[0] + Source[1] * Inverse[4] + Source[2] * Inverse[8] + Source[3] * Inverse[12];
		pfp32 InverseDeterminant = 1.0f / Determinant;

		for (pfp32 &Value : Inverse)
			Value *= InverseDeterminant;

		return fs_Load(Inverse);
	}

	// The matrix must be affine and invertible. Scale and shear are handled.
	CMat4x4_fp32 CMat4x4_fp32::f_InverseAffine() const
	{
		CVec3_fp32 Column0 = m_Columns[0].f_GetXYZ();
		CVec3_fp32 Column1 = m_Columns[1].f_GetXYZ();
		CVec3_fp32 Column2 = m_Columns[2].f_GetXYZ();
		CVec3_fp32 Translation = m_Columns[3].f_GetXYZ();

		CVec3_fp32 Row0 = Column1.f_Cross(Column2);
		CVec3_fp32 Row1 = Column2.f_Cross(Column0);
		CVec3_fp32 Row2 = Column0.f_Cross(Column1);

		pfp32 InverseDeterminant = 1.0f / Column0.f_Dot(Row0);
		Row0 *= InverseDeterminant;
		Row1 *= InverseDeterminant;
		Row2 *= InverseDeterminant;

		return CMat4x4_fp32
			(
				CVec4_fp32(Row0.f_GetX(), Row1.f_GetX(), Row2.f_GetX(), 0.0f)
				, CVec4_fp32(Row0.f_GetY(), Row1.f_GetY(), Row2.f_GetY(), 0.0f)
				, CVec4_fp32(Row0.f_GetZ(), Row1.f_GetZ(), Row2.f_GetZ(), 0.0f)
				, CVec4_fp32(-Row0.f_Dot(Translation), -Row1.f_Dot(Translation), -Row2.f_Dot(Translation), 1.0f)
			)
		;
	}

	// CMat3x4_fp32

	// _Affine must be affine, its last row is dropped.
	TCMat3x4<pfp32>::TCMat3x4(CMat4x4_fp32 const &_Affine)
		: m_Rows{_Affine.f_GetRow(0), _Affine.f_GetRow(1), _Affine.f_GetRow(2)}
	{
	}

	CMat4x4_fp32 CMat3x4_fp32::f_ToMat4() const
	{
		return CMat4x4_fp32(m_Rows[0], m_Rows[1], m_Rows[2], CVec4_fp32(0.0f, 0.0f, 0.0f, 1.0f)).f_Transposed();
	}

	// CBox_fp32

	// _Affine must be affine. The result bounds the transformed box and is usually larger than it.
	CBox_fp32 CBox_fp32::f_Transformed(CMat4x4_fp32 const &_Affine) const
	{
		CVec3_fp32 Center = _Affine.f_TransformPoint(f_GetCenter());
		CVec3_fp32 Extent = f_GetExtent();

		CVec3_fp32 NewExtent = _Affine.m_Columns[0].f_GetXYZ().f_Abs() * Extent.f_GetX()
			+ _Affine.m_Columns[1].f_GetXYZ().f_Abs() * Extent.f_GetY()
			+ _Affine.m_Columns[2].f_GetXYZ().f_Abs() * Extent.f_GetZ()
		;

		return fs_FromCenterExtent(Center, NewExtent);
	}

	// CPlane_fp32

	// A plane without a normal is returned unchanged, which is what an infinite far plane produces.
	CPlane_fp32 CPlane_fp32::f_Normalized() const
	{
		pfp32 Length = CVec4_fp32(m_Value).f_GetXYZ().f_Length();
		if (Length == 0.0f)
			return *this;

		return CPlane_fp32(m_Value / CSimd4_fp32(Length));
	}

	// CFrustum_fp32

	TCFrustum<pfp32>::TCFrustum(CMat4x4_fp32 const &_ViewProjection)
	{
		CSimd4_fp32 Row0 = _ViewProjection.f_GetRow(0).m_Value;
		CSimd4_fp32 Row1 = _ViewProjection.f_GetRow(1).m_Value;
		CSimd4_fp32 Row2 = _ViewProjection.f_GetRow(2).m_Value;
		CSimd4_fp32 Row3 = _ViewProjection.f_GetRow(3).m_Value;

		m_Planes[umint(EFrustumPlane::mc_Left)] = CPlane_fp32(Row3 + Row0).f_Normalized();
		m_Planes[umint(EFrustumPlane::mc_Right)] = CPlane_fp32(Row3 - Row0).f_Normalized();
		m_Planes[umint(EFrustumPlane::mc_Bottom)] = CPlane_fp32(Row3 + Row1).f_Normalized();
		m_Planes[umint(EFrustumPlane::mc_Top)] = CPlane_fp32(Row3 - Row1).f_Normalized();
		m_Planes[umint(EFrustumPlane::mc_Near)] = CPlane_fp32(Row2).f_Normalized();
		m_Planes[umint(EFrustumPlane::mc_Far)] = CPlane_fp32(Row3 - Row2).f_Normalized();
	}

	// Conservative: a sphere outside the frustum near a corner can be reported as intersecting.
	bool CFrustum_fp32::f_Intersects(CSphere_fp32 const &_Sphere) const
	{
		CVec3_fp32 Center = _Sphere.f_GetCenter();
		pfp32 Radius = _Sphere.f_GetRadius();

		for (auto &Plane : m_Planes)
		{
			if (Plane.f_SignedDistance(Center) < -Radius)
				return false;
		}

		return true;
	}

	// Conservative: a box outside the frustum near a corner can be reported as intersecting.
	bool CFrustum_fp32::f_Intersects(CBox_fp32 const &_Box) const
	{
		CVec3_fp32 Center = _Box.f_GetCenter();
		CVec3_fp32 Extent = _Box.f_GetExtent();

		for (auto &Plane : m_Planes)
		{
			CVec3_fp32 AbsNormal = CVec4_fp32(Plane.m_Value).f_GetXYZ().f_Abs();
			if (Plane.f_SignedDistance(Center) + AbsNormal.f_Dot(Extent) < 0.0f)
				return false;
		}

		return true;
	}

	namespace
	{
		constexpr umint gc_nCullLanes = CSimd8_fp32::mc_nLanes;

		struct CWidePlanes
		{
			CWidePlanes(CFrustum_fp32 const &_Frustum)
			{
				for (umint iPlane = 0; iPlane < CFrustum_fp32::mc_nPlanes; ++iPlane)
				{
					pfp32 Plane[4];
					_Frustum.m_Planes[iPlane].m_Value.f_Store(Plane);

					m_NormalX[iPlane] = CSimd8_fp32(Plane[0]);
					m_NormalY[iPlane] = CSimd8_fp32(Plane[1]);
					m_NormalZ[iPlane] = CSimd8_fp32(Plane[2]);
					m_Distance[iPlane] = CSimd8_fp32(Plane[3]);
				}
			}

			CSimd8_fp32 m_NormalX[CFrustum_fp32::mc_nPlanes];
			CSimd8_fp32 m_NormalY[CFrustum_fp32::mc_nPlanes];
			CSimd8_fp32 m_NormalZ[CFrustum_fp32::mc_nPlanes];
			CSimd8_fp32 m_Distance[CFrustum_fp32::mc_nPlanes];
		};

		// Reads _nValues values, which is fewer than a full vector at the end of an array.
		CSimd8_fp32 fg_LoadPartial(pfp32 const *_pSource, umint _nValues)
		{
			if (_nValues >= gc_nCullLanes)
				return CSimd8_fp32::fs_Load(_pSource);

			pfp32 Values[gc_nCullLanes] = {};
			for (umint i = 0; i < _nValues; ++i)
				Values[i] = _pSource[i];

			return CSimd8_fp32::fs_Load(Values);
		}

		void fg_StoreVisible(CSimd8_bool const &_Visible, umint _nValues, uint8 *o_pVisible)
		{
			uint32 Bits = _Visible.f_GetBits();
			for (umint i = 0; i < _nValues; ++i)
				o_pVisible[i] = (Bits >> i) & 1;
		}
	}

	// Writes 1 to o_pVisible for every sphere that f_Intersects reports as intersecting, 0 for the others.
	void CFrustum_fp32::f_CullSpheres
		(
			pfp32 const *_pCenterX
			, pfp32 const *_pCenterY
			, pfp32 const *_pCenterZ
			, pfp32 const *_pRadius
			, umint _nSpheres
			, uint8 *o_pVisible
		) const
	{
		CWidePlanes Planes(*this);

		for (umint iSphere = 0; iSphere < _nSpheres; iSphere += gc_nCullLanes)
		{
			umint nValues = fg_Min(_nSpheres - iSphere, gc_nCullLanes);

			CSimd8_fp32 CenterX = fg_LoadPartial(_pCenterX + iSphere, nValues);
			CSimd8_fp32 CenterY = fg_LoadPartial(_pCenterY + iSphere, nValues);
			CSimd8_fp32 CenterZ = fg_LoadPartial(_pCenterZ + iSphere, nValues);
			CSimd8_fp32 NegativeRadius = -fg_LoadPartial(_pRadius + iSphere, nValues);

			CSimd8_bool Visible = CSimd8_bool::fs_True();
			for (umint iPlane = 0; iPlane < mc_nPlanes; ++iPlane)
			{
				CSimd8_fp32 Distance = (Planes.m_NormalX[iPlane] * CenterX + Planes.m_NormalY[iPlane] * CenterY)
					+ (Planes.m_NormalZ[iPlane] * CenterZ + Planes.m_Distance[iPlane])
				;

				Visible &= ~(Distance < NegativeRadius);
			}

			fg_StoreVisible(Visible, nValues, o_pVisible + iSphere);
		}
	}

	// Writes 1 to o_pVisible for every box that f_Intersects reports as intersecting, 0 for the others.
	void CFrustum_fp32::f_CullBoxes
		(
			pfp32 const *_pCenterX
			, pfp32 const *_pCenterY
			, pfp32 const *_pCenterZ
			, pfp32 const *_pExtentX
			, pfp32 const *_pExtentY
			, pfp32 const *_pExtentZ
			, umint _nBoxes
			, uint8 *o_pVisible
		) const
	{
		CWidePlanes Planes(*this);

		for (umint iBox = 0; iBox < _nBoxes; iBox += gc_nCullLanes)
		{
			umint nValues = fg_Min(_nBoxes - iBox, gc_nCullLanes);

			CSimd8_fp32 CenterX = fg_LoadPartial(_pCenterX + iBox, nValues);
			CSimd8_fp32 CenterY = fg_LoadPartial(_pCenterY + iBox, nValues);
			CSimd8_fp32 CenterZ = fg_LoadPartial(_pCenterZ + iBox, nValues);
			CSimd8_fp32 ExtentX = fg_LoadPartial(_pExtentX + iBox, nValues);
			CSimd8_fp32 ExtentY = fg_LoadPartial(_pExtentY + iBox, nValues);
			CSimd8_fp32 ExtentZ = fg_LoadPartial(_pExtentZ + iBox, nValues);

			CSimd8_bool Visible = CSimd8_bool::fs_True();
			for (umint iPlane = 0; iPlane < mc_nPlanes; ++iPlane)
			{
				CSimd8_fp32 Distance = (Planes.m_NormalX[iPlane] * CenterX + Planes.m_NormalY[iPlane] * CenterY)
					+ (Planes.m_NormalZ[iPlane] * CenterZ + Planes.m_Distance[iPlane])
				;
				CSimd8_fp32 Reach = (Planes.m_NormalX[iPlane].f_Abs() * ExtentX + Planes.m_NormalY[iPlane].f_Abs() * ExtentY)
					+ (Planes.m_NormalZ[iPlane].f_Abs() * ExtentZ + CSimd8_fp32::fs_Zero())
				;

				Visible &= ~(Distance + Reach < CSimd8_fp32::fs_Zero());
			}

			fg_StoreVisible(Visible, nValues, o_pVisible + iBox);
		}
	}
}
