// Copyright © 2026 Unbroken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NNumeric
{
	template <typename t_CType, mint t_nDim>
	template <typename ...tfp_CParmas>
		requires (sizeof...(tfp_CParmas) > 1) || ((!cIsTCVec<tfp_CParmas>) && ...)
	constexpr TCVec<t_CType, t_nDim>::TCVec(tfp_CParmas && ...p_Param) noexcept
		: m_Axis{static_cast<CType>(p_Param)...}
	{
	}

	template <typename t_CType, mint t_nDim>
	template <typename tf_CType, mint tf_nDim>
	constexpr TCVec<t_CType, t_nDim>::TCVec(TCVec<tf_CType, tf_nDim> const &_Src)
	{
		constexpr static mint c_nDimMin = fg_Min(t_nDim, tf_nDim);
		for (mint i = 0; i < c_nDimMin; ++i)
			(*this)[i] = fg_Convert<CType>(_Src[i]);

		for (mint i = tf_nDim; i < t_nDim; ++i)
			(*this)[i] = CType{};
	}

	template <typename t_CType, mint t_nDim>
	constexpr TCVec<t_CType, t_nDim>::TCVec(CType _Value[t_nDim]) noexcept
	{
		for (mint i = 0; i < t_nDim; ++i)
			(*this)[i] = _Value[i];
	}

	template <typename t_CType, mint t_nDim>
	constexpr inline_small auto TCVec<t_CType, t_nDim>::operator [] (mint _iOpr) const -> CType const &
	{
		return m_Axis[_iOpr];
	}

	template <typename t_CType, mint t_nDim>
	constexpr inline_small auto TCVec<t_CType, t_nDim>::operator [] (mint _iOpr) -> CType &
	{
		return m_Axis[_iOpr];
	}

	template <typename t_CType, mint t_nDim>
	template <typename tf_CType, mint tf_nDim>
	constexpr auto TCVec<t_CType, t_nDim>::operator = (TCVec<tf_CType, tf_nDim> const &_Src) -> TCVec &
	{
		constexpr static mint c_nDimMin = fg_Min(t_nDim, tf_nDim);
		for (mint i = 0; i < c_nDimMin; ++i)
			(*this)[i] = fg_Convert<CType>(_Src[i]);

		for (mint i = tf_nDim; i < t_nDim; ++i)
			(*this)[i] = CType{};

		return *this;
	}
}
