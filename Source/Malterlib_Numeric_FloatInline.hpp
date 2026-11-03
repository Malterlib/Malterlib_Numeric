// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric
{
	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	inline_always auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fsp_IntegerDataToStorage
		(
			CUnsignedInteger _Data
		)
		-> CDataStorage
	{
		if constexpr (mc_bIsBuiltIn)
		{
			CDataStorage Return;
			memcpy(&Return, &_Data, sizeof(Return));
			return Return;
		}
		else
			return _Data;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	inline_always void TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_SetIntegerData(CUnsignedInteger _Data)
	{
		if constexpr (mc_bIsBuiltIn)
			memcpy(&mp_DataStorage, &_Data, sizeof(mp_DataStorage));
		else
			mp_DataStorage = _Data;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	inline_always auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_GetIntegerData() const
		-> CUnsignedInteger
	{
		if constexpr (mc_bIsBuiltIn)
		{
			CUnsignedInteger Return;
			memcpy(&Return, &mp_DataStorage, sizeof(Return));
			return Return;
		}
		else
			return mp_DataStorage;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	inline_always auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::fp_GetMaskedIntegerData() const
		-> CUnsignedInteger
	{
		if constexpr (mc_bIsBuiltIn)
		{
			CUnsignedInteger Return;
			memcpy(&Return, &mp_DataStorage, sizeof(Return));

			if constexpr (mc_PaddingBits != 0)
				return Return & ((CUnsignedInteger(1) << mc_PaddingBitPos) - CUnsignedInteger(1));
			else
				return Return;
		}
		else if constexpr (mc_PaddingBits != 0)
			return mp_DataStorage & ((CUnsignedInteger(1) << mc_PaddingBitPos) - CUnsignedInteger(1));
		else
			return mp_DataStorage;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	constexpr DMibFloatInlineS t_CImplicitFloat &TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::f_Get() noexcept
		requires (mc_bIsBuiltIn)
	{
		return mp_DataStorage;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	constexpr DMibFloatInlineS t_CImplicitFloat const &TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>
		::f_Get() const noexcept
		requires (mc_bIsBuiltIn)
	{
		return mp_DataStorage;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	constexpr DMibFloatInlineS TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>::TCFloat
		(
			t_CImplicitFloat const &_Value
		)
		noexcept
		requires (mc_bIsBuiltIn)
		: mp_DataStorage(_Value)
	{
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	constexpr DMibFloatInlineS auto TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>
		::operator = (t_CImplicitFloat const &_Value) noexcept
		-> TCFloat &
		requires (mc_bIsBuiltIn)
	{
		mp_DataStorage = _Value;
		return *this;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	inline DMibFloatConstexpr bool TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>
		::operator == (CImplicitFloat const &_Right) const noexcept
		requires (mc_bIsBuiltIn)
	{
		return f_Get() == _Right;
	}

	template <aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	inline DMibFloatConstexpr COrdering_Partial TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>
		::operator <=> (CImplicitFloat const &_Right) const noexcept
		requires (mc_bIsBuiltIn)
	{
		return f_Get() <=> _Right;
	}
}

namespace NMib
{
	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename tf_CType>
	DMibFloatInlineS t_CType0 TCConvert
		<
			t_CType0
			, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>
			, NTraits::TCCompileTimeConstant<int, (NTraits::cIsFloat<t_CType0>)>
		>
		::fs_Convert(tf_CType const &_From)
	{
		using CRetType = typename NNumeric::TCFloatFromNative<t_CType0>::CType;
		CRetType Ret = _From;
		return (t_CType0 const &)Ret;
	}

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename tf_CType>
	DMibFloatInlineS t_CType0 TCConvert
		<
			t_CType0
			, NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>
			, NTraits::TCCompileTimeConstant<int, (!NTraits::cIsFloat<t_CType0>)>
		>
		::fs_Convert(tf_CType const &_From)
	{
		return fg_Convert<t_CType0>(_From.f_ToInt());
	}

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename tf_CType>
	DMibFloatInlineS auto TCConvert<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, t_CType0>
		::fs_Convert(tf_CType const &_From)
		-> TCDisableIf<NTraits::cIsFloat<tf_CType>, CFloatType>
	{
		return CFloatType::fs_FromInt(_From);
	}

	template <typename t_CType0, aint t_SignBits, aint t_ExponentBits, aint t_MantissaBits, aint t_PaddingBits, typename t_CImplicitFloat, bool t_bDummyOptimize, typename t_CIntegerStorage>
	template <typename tf_CType>
	DMibFloatInlineS auto TCConvert<NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>, t_CType0>
		::fs_Convert(tf_CType const &_From)
		-> TCEnableIf<NTraits::cIsFloat<tf_CType>, CFloatType>
	{
		return CFloatType(((typename NNumeric::TCFloatFromNative<tf_CType>::CType const &)_From));
	}

	template
	<
		typename t_CUpper
		, typename t_CLower
		, aint t_SignBits
		, aint t_ExponentBits
		, aint t_MantissaBits
		, aint t_PaddingBits
		, typename t_CImplicitFloat
		, bool t_bDummyOptimize
		, typename t_CIntegerStorage
	>
	DMibFloatInlineS auto TCConvert
		<
			NMib::NNumeric::TCFloat<t_SignBits, t_ExponentBits, t_MantissaBits, t_PaddingBits, t_CImplicitFloat, t_bDummyOptimize, t_CIntegerStorage>
			, NNumeric::TCInt<t_CUpper, t_CLower>
		>
		::fs_Convert(NNumeric::TCInt<t_CUpper, t_CLower> const &_From)
		-> CFloatType
	{
		return CFloatType::fs_FromInt(_From);
	}
}
