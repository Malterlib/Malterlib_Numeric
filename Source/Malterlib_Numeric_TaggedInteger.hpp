// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NNumeric
{
	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::TCTaggedInteger()
	{
		mp_Data = t_DefaultInit;
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr auto TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::operator ++ () -> TCTaggedInteger &
	{
		++mp_Data;

		return *this;
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr inline_small bool TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::operator == (const TCTaggedInteger &_Data) const
	{
		return this->mp_Data == _Data.mp_Data;
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr inline_small bool TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::operator < (const TCTaggedInteger &_Data) const
	{
		return this->mp_Data < _Data.mp_Data;
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr inline_small t_CType TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::f_Get() const
	{
		return mp_Data;
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr inline_small void TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::f_Set(const t_CType &_Source)
	{
		mp_Data = _Source;
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr inline_small auto TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::fs_Default() -> TCTaggedInteger
	{
		return TCTaggedInteger{};
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr inline_small bool TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::f_IsValid() const
	{
		return mp_Data != t_DefaultInit;
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	constexpr auto TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::fs_Create(const t_CType &_Data) -> TCTaggedInteger
	{
		TCTaggedInteger Ret;
		Ret.mp_Data = _Data;
		return Ret;
	}

	template <typename t_CType, typename t_CTag, t_CType t_DefaultInit>
	template <typename tf_CFormatter>
	auto TCTaggedInteger<t_CType, t_CTag, t_DefaultInit>::f_CreateStringFormatter(tf_CFormatter &_Formatter) const -> decltype(fg_CreateStringFormatter(_Formatter, fg_GetType<t_CType>()))
	{
		return fg_CreateStringFormatter(_Formatter, mp_Data);
	}
}

namespace NMib::NStream
{
	template <typename t_CStream, typename t_CType, typename t_CIdent, t_CType t_DefaultValue>
	class TCBinaryStreamTypeReference<t_CStream, NNumeric::TCTaggedInteger<t_CType, t_CIdent, t_DefaultValue> >
	{
	public:
		static void fs_Feed(t_CStream &_Stream, NNumeric::TCTaggedInteger<t_CType, t_CIdent, t_DefaultValue> const &_Data)
		{
			_Stream << _Data.mp_Data;
		}

		static void fs_Consume(t_CStream &_Stream, NNumeric::TCTaggedInteger<t_CType, t_CIdent, t_DefaultValue> &_Data)
		{
			_Stream >> _Data.mp_Data;
		}
	};
}
