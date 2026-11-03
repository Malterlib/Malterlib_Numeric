// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{
	template <typename t_CType, umint t_nDim>
	template <typename ...tfp_CParmas>
		requires (sizeof...(tfp_CParmas) > 1) || ((!cIsTCVec<tfp_CParmas>) && ...)
	constexpr TCVec<t_CType, t_nDim>::TCVec(tfp_CParmas && ...p_Param) noexcept
		: m_Axis{static_cast<CType>(p_Param)...}
	{
	}

	template <typename t_CType, umint t_nDim>
	template <typename tf_CType, umint tf_nDim>
	constexpr TCVec<t_CType, t_nDim>::TCVec(TCVec<tf_CType, tf_nDim> const &_Src)
	{
		static constexpr umint c_nDimMin = fg_Min(t_nDim, tf_nDim);
		for (umint iAxis = 0; iAxis < c_nDimMin; ++iAxis)
			(*this)[iAxis] = fg_Convert<CType>(_Src[iAxis]);

		for (umint iAxis = tf_nDim; iAxis < t_nDim; ++iAxis)
			(*this)[iAxis] = CType{};
	}

	template <typename t_CType, umint t_nDim>
	constexpr TCVec<t_CType, t_nDim>::TCVec(CType _Value[t_nDim]) noexcept
	{
		for (umint iAxis = 0; iAxis < t_nDim; ++iAxis)
			(*this)[iAxis] = _Value[iAxis];
	}

	template <typename t_CType, umint t_nDim>
	constexpr inline_small auto TCVec<t_CType, t_nDim>::operator [] (umint _iOpr) const -> CType const &
	{
		return m_Axis[_iOpr];
	}

	template <typename t_CType, umint t_nDim>
	constexpr inline_small auto TCVec<t_CType, t_nDim>::operator [] (umint _iOpr) -> CType &
	{
		return m_Axis[_iOpr];
	}

	template <typename t_CType, umint t_nDim>
	template <typename tf_CType, umint tf_nDim>
	constexpr auto TCVec<t_CType, t_nDim>::operator = (TCVec<tf_CType, tf_nDim> const &_Src) -> TCVec &
	{
		static constexpr umint c_nDimMin = fg_Min(t_nDim, tf_nDim);
		for (umint iAxis = 0; iAxis < c_nDimMin; ++iAxis)
			(*this)[iAxis] = fg_Convert<CType>(_Src[iAxis]);

		for (umint iAxis = tf_nDim; iAxis < t_nDim; ++iAxis)
			(*this)[iAxis] = CType{};

		return *this;
	}
}
