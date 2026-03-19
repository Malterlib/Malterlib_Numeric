// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NNumeric
{
	template <typename t_CType, umint t_nDim>
	struct TCVec;

	namespace NPrivate
	{
		template <typename t_CType>
		struct TCIsTCVec
		{
			constexpr static bool mc_Value = false;
		};

		template <typename t_CType, umint t_nDim>
		struct TCIsTCVec<TCVec<t_CType, t_nDim>>
		{
			constexpr static bool mc_Value = true;
		};
	}

	template <typename t_CType>
	concept cIsTCVec = NPrivate::TCIsTCVec<NTraits::TCRemoveReferenceAndQualifiers<t_CType>>::mc_Value;

	template <typename t_CType, umint t_nDim>
	struct TCVec
	{
		using CType = t_CType;

		constexpr TCVec() noexcept = default;
		constexpr TCVec(TCVec const &_Src) noexcept = default;
		constexpr TCVec(TCVec &&_Src) noexcept = default;
		constexpr TCVec &operator = (TCVec const &_Src) noexcept = default;
		constexpr TCVec &operator = (TCVec &&_Src) noexcept = default;

		template <typename tf_CType, umint tf_nDim>
		constexpr TCVec(TCVec<tf_CType, tf_nDim> const &_Src);

		template <typename ...tfp_CParmas>
			requires (sizeof...(tfp_CParmas) > 1) || ((!cIsTCVec<tfp_CParmas>) && ...)
		constexpr TCVec(tfp_CParmas && ...p_Param) noexcept;

		constexpr TCVec(CType _Value[t_nDim]) noexcept;

		constexpr inline_small CType const &operator [] (umint _iOpr) const;
		constexpr inline_small CType &operator [] (umint _iOpr);

		template <typename tf_CType, umint tf_nDim>
		constexpr TCVec &operator = (TCVec<tf_CType, tf_nDim> const &_Src);

		constexpr static umint mc_NumDim = t_nDim;
		CType m_Axis[t_nDim];
	};

	using CVec2Dint32 = TCVec<int32, 2>;
	using CVec3Dint32 = TCVec<int32, 3>;
	using CVec4Dint32 = TCVec<int32, 4>;

	using CVec2Duint32 = TCVec<int32, 2>;
	using CVec3Duint32 = TCVec<int32, 3>;
	using CVec4Duint32 = TCVec<int32, 4>;

	using CVec2Dfp32 = TCVec<fp32, 2>;
	using CVec3Dfp32 = TCVec<fp32, 3>;
	using CVec4Dfp32 = TCVec<fp32, 4>;
}

#include "Malterlib_Numeric_Vector.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NNumeric;
#endif
