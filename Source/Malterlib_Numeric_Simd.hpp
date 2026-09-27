// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{
	// TCSimdMask

	template <typename t_CBackend>
	inline_always TCSimdMask<t_CBackend>::TCSimdMask(CStorage const &_Storage)
		: m_Value(_Storage)
	{
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::fs_False() -> TCSimdMask
	{
		return TCSimdMask(t_CBackend::fs_MaskFalse());
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::fs_True() -> TCSimdMask
	{
		return TCSimdMask(t_CBackend::fs_MaskTrue());
	}

	template <typename t_CBackend>
	inline_always bool TCSimdMask<t_CBackend>::f_Any() const
	{
		return t_CBackend::fs_MaskBits(m_Value) != 0;
	}

	template <typename t_CBackend>
	inline_always bool TCSimdMask<t_CBackend>::f_All() const
	{
		return t_CBackend::fs_MaskBits(m_Value) == mc_AllBits;
	}

	template <typename t_CBackend>
	inline_always bool TCSimdMask<t_CBackend>::f_None() const
	{
		return t_CBackend::fs_MaskBits(m_Value) == 0;
	}

	template <typename t_CBackend>
	inline_always bool TCSimdMask<t_CBackend>::f_GetLane(umint _iLane) const
	{
		return (t_CBackend::fs_MaskBits(m_Value) >> _iLane) & 1;
	}

	template <typename t_CBackend>
	inline_always uint32 TCSimdMask<t_CBackend>::f_GetBits() const
	{
		return t_CBackend::fs_MaskBits(m_Value);
	}

	template <typename t_CBackend>
	inline_always TCSimdInt<t_CBackend> TCSimdMask<t_CBackend>::f_ToInt() const
	{
		return TCSimdInt<t_CBackend>(t_CBackend::fs_MaskToInt(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::operator & (TCSimdMask const &_Right) const -> TCSimdMask
	{
		return TCSimdMask(t_CBackend::fs_MaskAnd(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::operator | (TCSimdMask const &_Right) const -> TCSimdMask
	{
		return TCSimdMask(t_CBackend::fs_MaskOr(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::operator ^ (TCSimdMask const &_Right) const -> TCSimdMask
	{
		return TCSimdMask(t_CBackend::fs_MaskXor(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::operator ~ () const -> TCSimdMask
	{
		return TCSimdMask(t_CBackend::fs_MaskNot(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::operator &= (TCSimdMask const &_Right) -> TCSimdMask &
	{
		m_Value = t_CBackend::fs_MaskAnd(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::operator |= (TCSimdMask const &_Right) -> TCSimdMask &
	{
		m_Value = t_CBackend::fs_MaskOr(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdMask<t_CBackend>::operator ^= (TCSimdMask const &_Right) -> TCSimdMask &
	{
		m_Value = t_CBackend::fs_MaskXor(m_Value, _Right.m_Value);
		return *this;
	}

	// TCSimdInt

	template <typename t_CBackend>
	inline_always TCSimdInt<t_CBackend>::TCSimdInt(int32 _Value)
		: m_Value(t_CBackend::fs_IntSplat(_Value))
	{
	}

	template <typename t_CBackend>
	inline_always TCSimdInt<t_CBackend>::TCSimdInt(CStorage const &_Storage)
		: m_Value(_Storage)
	{
	}

	template <typename t_CBackend>
	template <typename ...tfp_CLanes>
		requires (sizeof...(tfp_CLanes) == t_CBackend::mc_nLanes && sizeof...(tfp_CLanes) > 1)
	inline_always TCSimdInt<t_CBackend>::TCSimdInt(tfp_CLanes ...p_Lanes)
	{
		int32 const Lanes[mc_nLanes] = {int32(p_Lanes)...};
		m_Value = t_CBackend::fs_IntLoad(Lanes);
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::fs_Zero() -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntZero());
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::fs_Load(int32 const *_pSource) -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntLoad(_pSource));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::fs_LoadAligned(int32 const *_pSource) -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntLoadAligned(_pSource));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::fs_Select(CMask const &_Mask, TCSimdInt const &_True, TCSimdInt const &_False) -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntSelect(_Mask.m_Value, _True.m_Value, _False.m_Value));
	}

	template <typename t_CBackend>
	inline_always void TCSimdInt<t_CBackend>::f_Store(int32 *o_pDestination) const
	{
		t_CBackend::fs_IntStore(o_pDestination, m_Value);
	}

	template <typename t_CBackend>
	inline_always void TCSimdInt<t_CBackend>::f_StoreAligned(int32 *o_pDestination) const
	{
		t_CBackend::fs_IntStoreAligned(o_pDestination, m_Value);
	}

	template <typename t_CBackend>
	inline_always int32 TCSimdInt<t_CBackend>::f_GetLane(umint _iLane) const
	{
		return t_CBackend::fs_IntGetLane(m_Value, _iLane);
	}

	template <typename t_CBackend>
	inline_always void TCSimdInt<t_CBackend>::f_SetLane(umint _iLane, int32 _Value)
	{
		m_Value = t_CBackend::fs_IntSetLane(m_Value, _iLane, _Value);
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::f_Min(TCSimdInt const &_Other) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntMin(m_Value, _Other.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::f_Max(TCSimdInt const &_Other) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntMax(m_Value, _Other.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::f_Clamp(TCSimdInt const &_Min, TCSimdInt const &_Max) const -> TCSimdInt
	{
		return f_Max(_Min).f_Min(_Max);
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::f_Abs() const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntAbs(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::f_ShiftRightLogical(uint32 _nBits) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntShiftRightLogical(m_Value, _nBits));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::f_ToFloat() const -> CFloat
	{
		return CFloat(t_CBackend::fs_FloatFromInt(m_Value));
	}

	template <typename t_CBackend>
	template <umint ...tfp_iLanes>
		requires (sizeof...(tfp_iLanes) == t_CBackend::mc_nLanes && t_CBackend::mc_nLanes == 4)
	inline_always auto TCSimdInt<t_CBackend>::f_Shuffle() const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::template fs_IntShuffle<tfp_iLanes...>(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator + (TCSimdInt const &_Right) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntAdd(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator - (TCSimdInt const &_Right) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntSub(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator * (TCSimdInt const &_Right) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntMul(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator - () const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntNeg(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator & (TCSimdInt const &_Right) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntAnd(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator | (TCSimdInt const &_Right) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntOr(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator ^ (TCSimdInt const &_Right) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntXor(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator ~ () const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntNot(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator << (uint32 _nBits) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntShiftLeft(m_Value, _nBits));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator >> (uint32 _nBits) const -> TCSimdInt
	{
		return TCSimdInt(t_CBackend::fs_IntShiftRight(m_Value, _nBits));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator += (TCSimdInt const &_Right) -> TCSimdInt &
	{
		m_Value = t_CBackend::fs_IntAdd(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator -= (TCSimdInt const &_Right) -> TCSimdInt &
	{
		m_Value = t_CBackend::fs_IntSub(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator *= (TCSimdInt const &_Right) -> TCSimdInt &
	{
		m_Value = t_CBackend::fs_IntMul(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator &= (TCSimdInt const &_Right) -> TCSimdInt &
	{
		m_Value = t_CBackend::fs_IntAnd(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator |= (TCSimdInt const &_Right) -> TCSimdInt &
	{
		m_Value = t_CBackend::fs_IntOr(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator ^= (TCSimdInt const &_Right) -> TCSimdInt &
	{
		m_Value = t_CBackend::fs_IntXor(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator <<= (uint32 _nBits) -> TCSimdInt &
	{
		m_Value = t_CBackend::fs_IntShiftLeft(m_Value, _nBits);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator >>= (uint32 _nBits) -> TCSimdInt &
	{
		m_Value = t_CBackend::fs_IntShiftRight(m_Value, _nBits);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator == (TCSimdInt const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_IntEqual(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator != (TCSimdInt const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_MaskNot(t_CBackend::fs_IntEqual(m_Value, _Right.m_Value)));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator < (TCSimdInt const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_IntLess(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator > (TCSimdInt const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_IntLess(_Right.m_Value, m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator <= (TCSimdInt const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_MaskNot(t_CBackend::fs_IntLess(_Right.m_Value, m_Value)));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdInt<t_CBackend>::operator >= (TCSimdInt const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_MaskNot(t_CBackend::fs_IntLess(m_Value, _Right.m_Value)));
	}

	// TCSimdFloat

	template <typename t_CBackend>
	inline_always TCSimdFloat<t_CBackend>::TCSimdFloat(pfp32 _Value)
		: m_Value(t_CBackend::fs_FloatSplat(_Value))
	{
	}

	template <typename t_CBackend>
	inline_always TCSimdFloat<t_CBackend>::TCSimdFloat(CStorage const &_Storage)
		: m_Value(_Storage)
	{
	}

	template <typename t_CBackend>
	template <typename ...tfp_CLanes>
		requires (sizeof...(tfp_CLanes) == t_CBackend::mc_nLanes && sizeof...(tfp_CLanes) > 1)
	inline_always TCSimdFloat<t_CBackend>::TCSimdFloat(tfp_CLanes ...p_Lanes)
	{
		pfp32 const Lanes[mc_nLanes] = {pfp32(p_Lanes)...};
		m_Value = t_CBackend::fs_FloatLoad(Lanes);
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::fs_Zero() -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatZero());
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::fs_Load(pfp32 const *_pSource) -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatLoad(_pSource));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::fs_LoadAligned(pfp32 const *_pSource) -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatLoadAligned(_pSource));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::fs_Select(CMask const &_Mask, TCSimdFloat const &_True, TCSimdFloat const &_False) -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatSelect(_Mask.m_Value, _True.m_Value, _False.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::fs_FromBits(CInt const &_Bits) -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatBitsFromInt(_Bits.m_Value));
	}

	template <typename t_CBackend>
	inline_always void TCSimdFloat<t_CBackend>::f_Store(pfp32 *o_pDestination) const
	{
		t_CBackend::fs_FloatStore(o_pDestination, m_Value);
	}

	template <typename t_CBackend>
	inline_always void TCSimdFloat<t_CBackend>::f_StoreAligned(pfp32 *o_pDestination) const
	{
		t_CBackend::fs_FloatStoreAligned(o_pDestination, m_Value);
	}

	template <typename t_CBackend>
	inline_always pfp32 TCSimdFloat<t_CBackend>::f_GetLane(umint _iLane) const
	{
		return t_CBackend::fs_FloatGetLane(m_Value, _iLane);
	}

	template <typename t_CBackend>
	inline_always void TCSimdFloat<t_CBackend>::f_SetLane(umint _iLane, pfp32 _Value)
	{
		m_Value = t_CBackend::fs_FloatSetLane(m_Value, _iLane, _Value);
	}

	// Returns _Other in lanes where either operand is NaN.
	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_Min(TCSimdFloat const &_Other) const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatMin(m_Value, _Other.m_Value));
	}

	// Returns _Other in lanes where either operand is NaN.
	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_Max(TCSimdFloat const &_Other) const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatMax(m_Value, _Other.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_Clamp(TCSimdFloat const &_Min, TCSimdFloat const &_Max) const -> TCSimdFloat
	{
		return f_Max(_Min).f_Min(_Max);
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_Abs() const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatAbs(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_Sqrt() const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatSqrt(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_Floor() const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatFloor(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_Ceil() const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatCeil(m_Value));
	}

	// Adds adjacent lanes first, then the pairs, so the result is the same on every backend.
	template <typename t_CBackend>
	inline_always pfp32 TCSimdFloat<t_CBackend>::f_Sum() const
	{
		return t_CBackend::fs_FloatSum(m_Value);
	}

	// Truncates. The result is unspecified for NaN and for values outside the range of int32.
	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_ToInt() const -> CInt
	{
		return CInt(t_CBackend::fs_FloatToInt(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::f_ToBits() const -> CInt
	{
		return CInt(t_CBackend::fs_FloatBitsToInt(m_Value));
	}

	template <typename t_CBackend>
	template <umint ...tfp_iLanes>
		requires (sizeof...(tfp_iLanes) == t_CBackend::mc_nLanes && t_CBackend::mc_nLanes == 4)
	inline_always auto TCSimdFloat<t_CBackend>::f_Shuffle() const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::template fs_FloatShuffle<tfp_iLanes...>(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator + (TCSimdFloat const &_Right) const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatAdd(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator - (TCSimdFloat const &_Right) const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatSub(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator * (TCSimdFloat const &_Right) const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatMul(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator / (TCSimdFloat const &_Right) const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatDiv(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator - () const -> TCSimdFloat
	{
		return TCSimdFloat(t_CBackend::fs_FloatNeg(m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator += (TCSimdFloat const &_Right) -> TCSimdFloat &
	{
		m_Value = t_CBackend::fs_FloatAdd(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator -= (TCSimdFloat const &_Right) -> TCSimdFloat &
	{
		m_Value = t_CBackend::fs_FloatSub(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator *= (TCSimdFloat const &_Right) -> TCSimdFloat &
	{
		m_Value = t_CBackend::fs_FloatMul(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator /= (TCSimdFloat const &_Right) -> TCSimdFloat &
	{
		m_Value = t_CBackend::fs_FloatDiv(m_Value, _Right.m_Value);
		return *this;
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator == (TCSimdFloat const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_FloatEqual(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator != (TCSimdFloat const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_MaskNot(t_CBackend::fs_FloatEqual(m_Value, _Right.m_Value)));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator < (TCSimdFloat const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_FloatLess(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator > (TCSimdFloat const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_FloatLess(_Right.m_Value, m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator <= (TCSimdFloat const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_FloatLessEqual(m_Value, _Right.m_Value));
	}

	template <typename t_CBackend>
	inline_always auto TCSimdFloat<t_CBackend>::operator >= (TCSimdFloat const &_Right) const -> CMask
	{
		return CMask(t_CBackend::fs_FloatLessEqual(_Right.m_Value, m_Value));
	}

	template <typename t_CBackend>
	inline_always TCSimdFloat<t_CBackend> operator + (pfp32 _Left, TCSimdFloat<t_CBackend> const &_Right)
	{
		return TCSimdFloat<t_CBackend>(_Left) + _Right;
	}

	template <typename t_CBackend>
	inline_always TCSimdFloat<t_CBackend> operator - (pfp32 _Left, TCSimdFloat<t_CBackend> const &_Right)
	{
		return TCSimdFloat<t_CBackend>(_Left) - _Right;
	}

	template <typename t_CBackend>
	inline_always TCSimdFloat<t_CBackend> operator * (pfp32 _Left, TCSimdFloat<t_CBackend> const &_Right)
	{
		return TCSimdFloat<t_CBackend>(_Left) * _Right;
	}

	template <typename t_CBackend>
	inline_always TCSimdFloat<t_CBackend> operator / (pfp32 _Left, TCSimdFloat<t_CBackend> const &_Right)
	{
		return TCSimdFloat<t_CBackend>(_Left) / _Right;
	}
}
