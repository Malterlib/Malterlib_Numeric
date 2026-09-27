// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{
	// CVec3_fp32

	inline_always TCVec3<pfp32>::TCVec3(pfp32 _X, pfp32 _Y, pfp32 _Z)
		: m_Value(_X, _Y, _Z, 0.0f)
	{
	}

	inline_always TCVec3<pfp32>::TCVec3(pfp32 _Value)
		: m_Value(_Value, _Value, _Value, 0.0f)
	{
	}

	// Lane 3 of _Value must be zero.
	inline_always TCVec3<pfp32>::TCVec3(CSimd4_fp32 const &_Value)
		: m_Value(_Value)
	{
	}

	inline_always CVec3_fp32 CVec3_fp32::fs_Zero()
	{
		return CVec3_fp32(CSimd4_fp32::fs_Zero());
	}

	// Reads three values.
	inline_always CVec3_fp32 CVec3_fp32::fs_Load(pfp32 const *_pSource)
	{
		return CVec3_fp32(_pSource[0], _pSource[1], _pSource[2]);
	}

	inline_always CVec3_fp32 CVec3_fp32::fs_Lerp(CVec3_fp32 const &_From, CVec3_fp32 const &_To, pfp32 _Fraction)
	{
		return CVec3_fp32(_From.m_Value + (_To.m_Value - _From.m_Value) * CSimd4_fp32(_Fraction));
	}

	// Writes three values.
	inline_always void CVec3_fp32::f_Store(pfp32 *o_pDestination) const
	{
		pfp32 Lanes[4];
		m_Value.f_Store(Lanes);

		o_pDestination[0] = Lanes[0];
		o_pDestination[1] = Lanes[1];
		o_pDestination[2] = Lanes[2];
	}

	inline_always pfp32 CVec3_fp32::f_GetX() const
	{
		return m_Value.f_GetLane(0);
	}

	inline_always pfp32 CVec3_fp32::f_GetY() const
	{
		return m_Value.f_GetLane(1);
	}

	inline_always pfp32 CVec3_fp32::f_GetZ() const
	{
		return m_Value.f_GetLane(2);
	}

	inline_always pfp32 CVec3_fp32::f_Dot(CVec3_fp32 const &_Other) const
	{
		return (m_Value * _Other.m_Value).f_Sum();
	}

	inline_always CVec3_fp32 CVec3_fp32::f_Cross(CVec3_fp32 const &_Other) const
	{
		return CVec3_fp32
			(
				m_Value.f_Shuffle<1, 2, 0, 3>() * _Other.m_Value.f_Shuffle<2, 0, 1, 3>()
				- m_Value.f_Shuffle<2, 0, 1, 3>() * _Other.m_Value.f_Shuffle<1, 2, 0, 3>()
			)
		;
	}

	inline_always pfp32 CVec3_fp32::f_LengthSquared() const
	{
		return f_Dot(*this);
	}

	inline_always pfp32 CVec3_fp32::f_Length() const
	{
		return __builtin_sqrtf(f_LengthSquared());
	}

	// The length must not be zero.
	inline_always CVec3_fp32 CVec3_fp32::f_Normalized() const
	{
		return CVec3_fp32(m_Value / CSimd4_fp32(f_Length()));
	}

	inline_always CVec3_fp32 CVec3_fp32::f_Min(CVec3_fp32 const &_Other) const
	{
		return CVec3_fp32(m_Value.f_Min(_Other.m_Value));
	}

	inline_always CVec3_fp32 CVec3_fp32::f_Max(CVec3_fp32 const &_Other) const
	{
		return CVec3_fp32(m_Value.f_Max(_Other.m_Value));
	}

	inline_always CVec3_fp32 CVec3_fp32::f_Abs() const
	{
		return CVec3_fp32(m_Value.f_Abs());
	}

	inline_always CVec3_fp32 CVec3_fp32::operator + (CVec3_fp32 const &_Right) const
	{
		return CVec3_fp32(m_Value + _Right.m_Value);
	}

	inline_always CVec3_fp32 CVec3_fp32::operator - (CVec3_fp32 const &_Right) const
	{
		return CVec3_fp32(m_Value - _Right.m_Value);
	}

	inline_always CVec3_fp32 CVec3_fp32::operator * (CVec3_fp32 const &_Right) const
	{
		return CVec3_fp32(m_Value * _Right.m_Value);
	}

	inline_always CVec3_fp32 CVec3_fp32::operator * (pfp32 _Right) const
	{
		return CVec3_fp32(m_Value * CSimd4_fp32(_Right));
	}

	inline_always CVec3_fp32 CVec3_fp32::operator / (pfp32 _Right) const
	{
		// The lane that pads is divided by one, which keeps it zero for any divisor
		return CVec3_fp32(m_Value / CSimd4_fp32(_Right, _Right, _Right, 1.0f));
	}

	inline_always CVec3_fp32 CVec3_fp32::operator - () const
	{
		return CVec3_fp32(CSimd4_fp32::fs_Zero() - m_Value);
	}

	inline_always CVec3_fp32 &CVec3_fp32::operator += (CVec3_fp32 const &_Right)
	{
		m_Value += _Right.m_Value;
		return *this;
	}

	inline_always CVec3_fp32 &CVec3_fp32::operator -= (CVec3_fp32 const &_Right)
	{
		m_Value -= _Right.m_Value;
		return *this;
	}

	inline_always CVec3_fp32 &CVec3_fp32::operator *= (pfp32 _Right)
	{
		m_Value *= CSimd4_fp32(_Right);
		return *this;
	}

	// CVec4_fp32

	inline_always TCVec4<pfp32>::TCVec4(pfp32 _X, pfp32 _Y, pfp32 _Z, pfp32 _W)
		: m_Value(_X, _Y, _Z, _W)
	{
	}

	inline_always TCVec4<pfp32>::TCVec4(CVec3_fp32 const &_XYZ, pfp32 _W)
		: m_Value(_XYZ.m_Value + CSimd4_fp32(0.0f, 0.0f, 0.0f, _W))
	{
	}

	inline_always TCVec4<pfp32>::TCVec4(pfp32 _Value)
		: m_Value(_Value)
	{
	}

	inline_always TCVec4<pfp32>::TCVec4(CSimd4_fp32 const &_Value)
		: m_Value(_Value)
	{
	}

	inline_always CVec4_fp32 CVec4_fp32::fs_Zero()
	{
		return CVec4_fp32(CSimd4_fp32::fs_Zero());
	}

	inline_always CVec4_fp32 CVec4_fp32::fs_Load(pfp32 const *_pSource)
	{
		return CVec4_fp32(CSimd4_fp32::fs_Load(_pSource));
	}

	inline_always CVec4_fp32 CVec4_fp32::fs_Lerp(CVec4_fp32 const &_From, CVec4_fp32 const &_To, pfp32 _Fraction)
	{
		return CVec4_fp32(_From.m_Value + (_To.m_Value - _From.m_Value) * CSimd4_fp32(_Fraction));
	}

	inline_always void CVec4_fp32::f_Store(pfp32 *o_pDestination) const
	{
		m_Value.f_Store(o_pDestination);
	}

	inline_always pfp32 CVec4_fp32::f_GetX() const
	{
		return m_Value.f_GetLane(0);
	}

	inline_always pfp32 CVec4_fp32::f_GetY() const
	{
		return m_Value.f_GetLane(1);
	}

	inline_always pfp32 CVec4_fp32::f_GetZ() const
	{
		return m_Value.f_GetLane(2);
	}

	inline_always pfp32 CVec4_fp32::f_GetW() const
	{
		return m_Value.f_GetLane(3);
	}

	inline_always CVec3_fp32 CVec4_fp32::f_GetXYZ() const
	{
		CSimd4_fp32 Value = m_Value;
		Value.f_SetLane(3, 0.0f);

		return CVec3_fp32(Value);
	}

	inline_always pfp32 CVec4_fp32::f_Dot(CVec4_fp32 const &_Other) const
	{
		return (m_Value * _Other.m_Value).f_Sum();
	}

	inline_always pfp32 CVec4_fp32::f_LengthSquared() const
	{
		return f_Dot(*this);
	}

	inline_always pfp32 CVec4_fp32::f_Length() const
	{
		return __builtin_sqrtf(f_LengthSquared());
	}

	// The length must not be zero.
	inline_always CVec4_fp32 CVec4_fp32::f_Normalized() const
	{
		return CVec4_fp32(m_Value / CSimd4_fp32(f_Length()));
	}

	inline_always CVec4_fp32 CVec4_fp32::f_Min(CVec4_fp32 const &_Other) const
	{
		return CVec4_fp32(m_Value.f_Min(_Other.m_Value));
	}

	inline_always CVec4_fp32 CVec4_fp32::f_Max(CVec4_fp32 const &_Other) const
	{
		return CVec4_fp32(m_Value.f_Max(_Other.m_Value));
	}

	inline_always CVec4_fp32 CVec4_fp32::operator + (CVec4_fp32 const &_Right) const
	{
		return CVec4_fp32(m_Value + _Right.m_Value);
	}

	inline_always CVec4_fp32 CVec4_fp32::operator - (CVec4_fp32 const &_Right) const
	{
		return CVec4_fp32(m_Value - _Right.m_Value);
	}

	inline_always CVec4_fp32 CVec4_fp32::operator * (CVec4_fp32 const &_Right) const
	{
		return CVec4_fp32(m_Value * _Right.m_Value);
	}

	inline_always CVec4_fp32 CVec4_fp32::operator * (pfp32 _Right) const
	{
		return CVec4_fp32(m_Value * CSimd4_fp32(_Right));
	}

	inline_always CVec4_fp32 CVec4_fp32::operator / (pfp32 _Right) const
	{
		return CVec4_fp32(m_Value / CSimd4_fp32(_Right));
	}

	inline_always CVec4_fp32 CVec4_fp32::operator - () const
	{
		return CVec4_fp32(-m_Value);
	}

	// CQuat_fp32

	inline_always TCQuat<pfp32>::TCQuat(pfp32 _X, pfp32 _Y, pfp32 _Z, pfp32 _W)
		: m_Value(_X, _Y, _Z, _W)
	{
	}

	inline_always TCQuat<pfp32>::TCQuat(CSimd4_fp32 const &_Value)
		: m_Value(_Value)
	{
	}

	inline_always CQuat_fp32 CQuat_fp32::fs_Identity()
	{
		return CQuat_fp32(0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline_always pfp32 CQuat_fp32::f_GetX() const
	{
		return m_Value.f_GetLane(0);
	}

	inline_always pfp32 CQuat_fp32::f_GetY() const
	{
		return m_Value.f_GetLane(1);
	}

	inline_always pfp32 CQuat_fp32::f_GetZ() const
	{
		return m_Value.f_GetLane(2);
	}

	inline_always pfp32 CQuat_fp32::f_GetW() const
	{
		return m_Value.f_GetLane(3);
	}

	inline_always CQuat_fp32 CQuat_fp32::f_Conjugate() const
	{
		return CQuat_fp32(m_Value * CSimd4_fp32(-1.0f, -1.0f, -1.0f, 1.0f));
	}

	// The length must not be zero.
	inline_always CQuat_fp32 CQuat_fp32::f_Normalized() const
	{
		return CQuat_fp32(m_Value / CSimd4_fp32(__builtin_sqrtf((m_Value * m_Value).f_Sum())));
	}

	// CMat4x4_fp32

	inline_always TCMat4x4<pfp32>::TCMat4x4(CVec4_fp32 const &_Column0, CVec4_fp32 const &_Column1, CVec4_fp32 const &_Column2, CVec4_fp32 const &_Column3)
		: m_Columns{_Column0, _Column1, _Column2, _Column3}
	{
	}

	inline_always CVec4_fp32 CMat4x4_fp32::operator * (CVec4_fp32 const &_Right) const
	{
		return CVec4_fp32
			(
				m_Columns[0].m_Value * _Right.m_Value.f_Shuffle<0, 0, 0, 0>()
				+ m_Columns[1].m_Value * _Right.m_Value.f_Shuffle<1, 1, 1, 1>()
				+ m_Columns[2].m_Value * _Right.m_Value.f_Shuffle<2, 2, 2, 2>()
				+ m_Columns[3].m_Value * _Right.m_Value.f_Shuffle<3, 3, 3, 3>()
			)
		;
	}

	inline_always CMat4x4_fp32 CMat4x4_fp32::operator * (CMat4x4_fp32 const &_Right) const
	{
		return CMat4x4_fp32(*this * _Right.m_Columns[0], *this * _Right.m_Columns[1], *this * _Right.m_Columns[2], *this * _Right.m_Columns[3]);
	}

	// CSphere_fp32

	inline_always TCSphere<pfp32>::TCSphere(CVec3_fp32 const &_Center, pfp32 _Radius)
		: m_Value(CVec4_fp32(_Center, _Radius).m_Value)
	{
	}

	inline_always CVec3_fp32 CSphere_fp32::f_GetCenter() const
	{
		return CVec4_fp32(m_Value).f_GetXYZ();
	}

	inline_always pfp32 CSphere_fp32::f_GetRadius() const
	{
		return m_Value.f_GetLane(3);
	}

	// CBox_fp32

	inline_always TCBox<pfp32>::TCBox(CVec3_fp32 const &_Min, CVec3_fp32 const &_Max)
		: m_Min(_Min)
		, m_Max(_Max)
	{
	}

	inline_always CBox_fp32 CBox_fp32::fs_FromCenterExtent(CVec3_fp32 const &_Center, CVec3_fp32 const &_Extent)
	{
		return CBox_fp32(_Center - _Extent, _Center + _Extent);
	}

	inline_always CVec3_fp32 CBox_fp32::f_GetCenter() const
	{
		return (m_Min + m_Max) * 0.5f;
	}

	inline_always CVec3_fp32 CBox_fp32::f_GetExtent() const
	{
		return (m_Max - m_Min) * 0.5f;
	}

	inline_always CBox_fp32 CBox_fp32::f_Union(CBox_fp32 const &_Other) const
	{
		return CBox_fp32(m_Min.f_Min(_Other.m_Min), m_Max.f_Max(_Other.m_Max));
	}

	// CPlane_fp32

	inline_always TCPlane<pfp32>::TCPlane(CVec3_fp32 const &_Normal, pfp32 _Distance)
		: m_Value(CVec4_fp32(_Normal, _Distance).m_Value)
	{
	}

	inline_always TCPlane<pfp32>::TCPlane(CSimd4_fp32 const &_Value)
		: m_Value(_Value)
	{
	}

	inline_always pfp32 CPlane_fp32::f_SignedDistance(CVec3_fp32 const &_Point) const
	{
		return (m_Value * CVec4_fp32(_Point, 1.0f).m_Value).f_Sum();
	}
}
