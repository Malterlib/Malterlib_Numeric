// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>
#include <Mib/String/String>

namespace NMib::NNumeric
{
	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit = -1>
	struct TCTaggedInteger
	{
		using CType = t_CType;

		constexpr TCTaggedInteger();

		constexpr TCTaggedInteger(TCTaggedInteger const &_Source) = default;
		constexpr TCTaggedInteger(TCTaggedInteger &&_Source) = default;

		constexpr TCTaggedInteger &operator = (TCTaggedInteger const &_Source) = default;
		constexpr TCTaggedInteger &operator = (TCTaggedInteger &&_Source) = default;

		constexpr TCTaggedInteger &operator ++ ();

		constexpr inline_small bool operator == (const TCTaggedInteger &_Data) const noexcept;
		constexpr inline_small auto operator <=> (const TCTaggedInteger &_Data) const noexcept;

		constexpr inline_small t_CType f_Get() const;
		constexpr inline_small void f_Set(const t_CType &_Source);
		constexpr inline_small bool f_IsValid() const;

		constexpr inline_small static TCTaggedInteger fs_Default();
		constexpr static TCTaggedInteger fs_Create(const t_CType &_Data);

		template <typename tf_CFormatter>
		auto f_GetStringFormatType(tf_CFormatter &_Formatter) -> decltype(fg_GetStringFormatType(_Formatter, fg_GetType<t_CType>()));

		template <typename tf_CFormatter>
		auto f_CreateStringFormatter(tf_CFormatter &_Formatter) const -> decltype(fg_CreateStringFormatter(_Formatter, fg_GetType<t_CType>()));

	private:

		template <typename t_CStream, typename t_CType2>
		friend class NStream::TCBinaryStreamTypeReference;

		t_CType mp_Data;
	};
}

#include "Malterlib_Numeric_TaggedInteger.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NNumeric;
#endif
