// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include "Malterlib_Numeric_Simd.h"

// Conventions: column vectors, column-major matrices, right-handed view space looking down negative Z,
// clip space depth in the range 0 to 1.

namespace NMib::NNumeric
{
	// The math types are templates of the type of their elements, and only pfp32 is implemented. Other types are added
	// when something uses them
	template <typename t_CType>
	struct TCVec3;

	template <typename t_CType>
	struct TCVec4;

	template <typename t_CType>
	struct TCQuat;

	template <typename t_CType>
	struct TCMat4x4;

	template <typename t_CType>
	struct TCMat3x4;

	template <typename t_CType>
	struct TCSphere;

	template <typename t_CType>
	struct TCBox;

	template <typename t_CType>
	struct TCPlane;

	template <typename t_CType>
	struct TCFrustum;

	using CVec3_fp32 = TCVec3<pfp32>;
	using CVec4_fp32 = TCVec4<pfp32>;
	using CQuat_fp32 = TCQuat<pfp32>;
	using CMat4x4_fp32 = TCMat4x4<pfp32>;
	using CMat3x4_fp32 = TCMat3x4<pfp32>;
	using CSphere_fp32 = TCSphere<pfp32>;
	using CBox_fp32 = TCBox<pfp32>;
	using CPlane_fp32 = TCPlane<pfp32>;
	using CFrustum_fp32 = TCFrustum<pfp32>;

	template <>
	struct TCVec3<pfp32>
	{
		TCVec3() = default;
		TCVec3(pfp32 _X, pfp32 _Y, pfp32 _Z);
		explicit TCVec3(pfp32 _Value);
		explicit TCVec3(CSimd4_fp32 const &_Value);

		static CVec3_fp32 fs_Zero();
		static CVec3_fp32 fs_Load(pfp32 const *_pSource);
		static CVec3_fp32 fs_Lerp(CVec3_fp32 const &_From, CVec3_fp32 const &_To, pfp32 _Fraction);

		void f_Store(pfp32 *o_pDestination) const;
		pfp32 f_GetX() const;
		pfp32 f_GetY() const;
		pfp32 f_GetZ() const;

		pfp32 f_Dot(CVec3_fp32 const &_Other) const;
		CVec3_fp32 f_Cross(CVec3_fp32 const &_Other) const;
		pfp32 f_LengthSquared() const;
		pfp32 f_Length() const;
		CVec3_fp32 f_Normalized() const;
		CVec3_fp32 f_Min(CVec3_fp32 const &_Other) const;
		CVec3_fp32 f_Max(CVec3_fp32 const &_Other) const;
		CVec3_fp32 f_Abs() const;

		CVec3_fp32 operator + (CVec3_fp32 const &_Right) const;
		CVec3_fp32 operator - (CVec3_fp32 const &_Right) const;
		CVec3_fp32 operator * (CVec3_fp32 const &_Right) const;
		CVec3_fp32 operator * (pfp32 _Right) const;
		CVec3_fp32 operator / (pfp32 _Right) const;
		CVec3_fp32 operator - () const;

		CVec3_fp32 &operator += (CVec3_fp32 const &_Right);
		CVec3_fp32 &operator -= (CVec3_fp32 const &_Right);
		CVec3_fp32 &operator *= (pfp32 _Right);

		CSimd4_fp32 m_Value; // Lane 3 is always zero
	};

	template <>
	struct TCVec4<pfp32>
	{
		TCVec4() = default;
		TCVec4(pfp32 _X, pfp32 _Y, pfp32 _Z, pfp32 _W);
		TCVec4(CVec3_fp32 const &_XYZ, pfp32 _W);
		explicit TCVec4(pfp32 _Value);
		explicit TCVec4(CSimd4_fp32 const &_Value);

		static CVec4_fp32 fs_Zero();
		static CVec4_fp32 fs_Load(pfp32 const *_pSource);
		static CVec4_fp32 fs_Lerp(CVec4_fp32 const &_From, CVec4_fp32 const &_To, pfp32 _Fraction);

		void f_Store(pfp32 *o_pDestination) const;
		pfp32 f_GetX() const;
		pfp32 f_GetY() const;
		pfp32 f_GetZ() const;
		pfp32 f_GetW() const;
		CVec3_fp32 f_GetXYZ() const;

		pfp32 f_Dot(CVec4_fp32 const &_Other) const;
		pfp32 f_LengthSquared() const;
		pfp32 f_Length() const;
		CVec4_fp32 f_Normalized() const;
		CVec4_fp32 f_Min(CVec4_fp32 const &_Other) const;
		CVec4_fp32 f_Max(CVec4_fp32 const &_Other) const;

		CVec4_fp32 operator + (CVec4_fp32 const &_Right) const;
		CVec4_fp32 operator - (CVec4_fp32 const &_Right) const;
		CVec4_fp32 operator * (CVec4_fp32 const &_Right) const;
		CVec4_fp32 operator * (pfp32 _Right) const;
		CVec4_fp32 operator / (pfp32 _Right) const;
		CVec4_fp32 operator - () const;

		CSimd4_fp32 m_Value;
	};

	template <>
	struct TCQuat<pfp32>
	{
		TCQuat() = default;
		TCQuat(pfp32 _X, pfp32 _Y, pfp32 _Z, pfp32 _W);
		explicit TCQuat(CSimd4_fp32 const &_Value);

		static CQuat_fp32 fs_Identity();
		static CQuat_fp32 fs_FromAxisAngle(CVec3_fp32 const &_Axis, pfp32 _Radians);
		static CQuat_fp32 fs_NormalizedLerp(CQuat_fp32 const &_From, CQuat_fp32 const &_To, pfp32 _Fraction);

		pfp32 f_GetX() const;
		pfp32 f_GetY() const;
		pfp32 f_GetZ() const;
		pfp32 f_GetW() const;

		CQuat_fp32 f_Conjugate() const;
		CQuat_fp32 f_Normalized() const;
		CVec3_fp32 f_Rotate(CVec3_fp32 const &_Vector) const;

		CQuat_fp32 operator * (CQuat_fp32 const &_Right) const;

		CSimd4_fp32 m_Value; // X, Y, Z, W
	};

	template <>
	struct TCMat4x4<pfp32>
	{
		TCMat4x4() = default;
		TCMat4x4(CVec4_fp32 const &_Column0, CVec4_fp32 const &_Column1, CVec4_fp32 const &_Column2, CVec4_fp32 const &_Column3);

		static CMat4x4_fp32 fs_Identity();
		static CMat4x4_fp32 fs_Load(pfp32 const *_pSource);
		static CMat4x4_fp32 fs_Translation(CVec3_fp32 const &_Translation);
		static CMat4x4_fp32 fs_Scale(CVec3_fp32 const &_Scale);
		static CMat4x4_fp32 fs_FromQuat(CQuat_fp32 const &_Rotation);
		static CMat4x4_fp32 fs_FromTransform(CVec3_fp32 const &_Translation, CQuat_fp32 const &_Rotation, CVec3_fp32 const &_Scale);
		static CMat4x4_fp32 fs_LookAt(CVec3_fp32 const &_Eye, CVec3_fp32 const &_Target, CVec3_fp32 const &_Up);
		static CMat4x4_fp32 fs_Perspective(pfp32 _FieldOfViewY, pfp32 _AspectRatio, pfp32 _Near, pfp32 _Far);
		static CMat4x4_fp32 fs_PerspectiveReverseInfinite(pfp32 _FieldOfViewY, pfp32 _AspectRatio, pfp32 _Near);
		static CMat4x4_fp32 fs_Orthographic(pfp32 _Left, pfp32 _Right, pfp32 _Bottom, pfp32 _Top, pfp32 _Near, pfp32 _Far);

		void f_Store(pfp32 *o_pDestination) const;
		pfp32 f_Get(umint _iRow, umint _iColumn) const;
		CVec4_fp32 f_GetRow(umint _iRow) const;

		CVec3_fp32 f_TransformPoint(CVec3_fp32 const &_Point) const;
		CVec3_fp32 f_TransformDirection(CVec3_fp32 const &_Direction) const;
		CMat4x4_fp32 f_Transposed() const;
		CMat4x4_fp32 f_Inverse() const;
		CMat4x4_fp32 f_InverseAffine() const;

		CMat4x4_fp32 operator * (CMat4x4_fp32 const &_Right) const;
		CVec4_fp32 operator * (CVec4_fp32 const &_Right) const;

		CVec4_fp32 m_Columns[4];
	};

	// The upper three rows of an affine transform, the layout used for instance data on the GPU.
	template <>
	struct TCMat3x4<pfp32>
	{
		TCMat3x4() = default;
		explicit TCMat3x4(CMat4x4_fp32 const &_Affine);

		CMat4x4_fp32 f_ToMat4() const;

		CVec4_fp32 m_Rows[3];
	};

	template <>
	struct TCSphere<pfp32>
	{
		TCSphere() = default;
		TCSphere(CVec3_fp32 const &_Center, pfp32 _Radius);

		CVec3_fp32 f_GetCenter() const;
		pfp32 f_GetRadius() const;

		CSimd4_fp32 m_Value; // Center in X, Y, Z and radius in W
	};

	template <>
	struct TCBox<pfp32>
	{
		TCBox() = default;
		TCBox(CVec3_fp32 const &_Min, CVec3_fp32 const &_Max);

		static CBox_fp32 fs_FromCenterExtent(CVec3_fp32 const &_Center, CVec3_fp32 const &_Extent);

		CVec3_fp32 f_GetCenter() const;
		CVec3_fp32 f_GetExtent() const;
		CBox_fp32 f_Union(CBox_fp32 const &_Other) const;
		CBox_fp32 f_Transformed(CMat4x4_fp32 const &_Affine) const;

		CVec3_fp32 m_Min;
		CVec3_fp32 m_Max;
	};

	template <>
	struct TCPlane<pfp32>
	{
		TCPlane() = default;
		TCPlane(CVec3_fp32 const &_Normal, pfp32 _Distance);
		explicit TCPlane(CSimd4_fp32 const &_Value);

		CPlane_fp32 f_Normalized() const;
		pfp32 f_SignedDistance(CVec3_fp32 const &_Point) const;

		CSimd4_fp32 m_Value; // Normal in X, Y, Z and distance in W. Points with a positive signed distance are inside
	};

	enum class EFrustumPlane : uint8
	{
		mc_Left
		, mc_Right
		, mc_Bottom
		, mc_Top
		, mc_Near
		, mc_Far
		, mc_Count
	};

	template <>
	struct TCFrustum<pfp32>
	{
		static constexpr umint mc_nPlanes = umint(EFrustumPlane::mc_Count);

		TCFrustum() = default;
		explicit TCFrustum(CMat4x4_fp32 const &_ViewProjection);

		bool f_Intersects(CSphere_fp32 const &_Sphere) const;
		bool f_Intersects(CBox_fp32 const &_Box) const;

		void f_CullSpheres
			(
				pfp32 const *_pCenterX
				, pfp32 const *_pCenterY
				, pfp32 const *_pCenterZ
				, pfp32 const *_pRadius
				, umint _nSpheres
				, uint8 *o_pVisible
			) const
		;

		void f_CullBoxes
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
		;

		CPlane_fp32 m_Planes[mc_nPlanes];
	};
}

#include "Malterlib_Numeric_Math.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NNumeric;
#endif
