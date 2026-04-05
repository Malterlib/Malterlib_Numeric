// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	constexpr DMibFloatInlineS t_CImplicitFloat &TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Get() noexcept
		requires (mc_bIsBuiltIn)
	{
		return m_DataStorage;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	constexpr DMibFloatInlineS t_CImplicitFloat const &TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Get() const noexcept
		requires (mc_bIsBuiltIn)
	{
		return m_DataStorage;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	constexpr DMibFloatInlineS TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::TCFloat(const t_CImplicitFloat &_Value) noexcept
		requires (mc_bIsBuiltIn)
		: m_DataStorage(_Value)
	{
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	constexpr DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::operator = (const t_CImplicitFloat &_Value) noexcept -> TCFloat &
		requires (mc_bIsBuiltIn)
	{
		m_DataStorage = _Value;
		return *this;
	}
}
