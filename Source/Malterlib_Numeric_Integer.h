// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>
#include <Mib/Bit/Bit>
#include <Mib/Type/Traits>

namespace NMib::NNumeric::NPrivate
{
	struct CDummy
	{
		static CDummy ms_Dummy;
	};
}

namespace NMib::NNumeric
{
	template <typename t_CUpper, typename t_CLower>
	struct TCInt
	{
		using CUpper = t_CUpper;
		using CLower = t_CLower;
		using CInt = TCInt;
		struct CConstants;

		// Do nothing in default constructor
		constexpr TCInt() noexcept = default;
		constexpr TCInt(TCInt const &_Value) noexcept = default;
		constexpr TCInt(TCInt &&_Value) noexcept = default;

		constexpr TCInt(t_CUpper _Upper, t_CLower _Lower);
		constexpr TCInt(t_CLower _Lower);

		template <typename tf_CType>
		constexpr TCInt(tf_CType const &_Convert, TCEnableIf<NTraits::cIsFundamental<tf_CType>, NPrivate::CDummy &> _Dummy = NPrivate::CDummy::ms_Dummy);
		template <typename tf_CUpper2, typename tf_CLower2>
		constexpr TCInt(TCInt<tf_CUpper2, tf_CLower2> const &_Other);

		constexpr TCInt &operator = (TCInt const &_Value) = default;
		constexpr TCInt &operator = (TCInt &&_Value) = default;

		template <typename tf_CUpper2, typename tf_CLower2>
		constexpr TCInt<tf_CUpper2, tf_CLower2> f_GetAsTCInt() const;
		template <typename tf_CInt>
		constexpr explicit operator tf_CInt () const;

		template <typename tf_CType>
		constexpr TCInt &operator = (tf_CType const &_Convert);

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Unary prefix operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr TCInt operator - () const;
		constexpr TCInt operator + () const;
		constexpr TCInt operator ~ () const;
		constexpr explicit operator bool () const;
		constexpr TCInt &operator ++ ();
		constexpr TCInt &operator -- ();

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Postfix operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr TCInt operator ++ (int);
		constexpr TCInt operator -- (int);

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Binary operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr TCInt operator + (TCInt const &_Value) const;
		constexpr TCInt operator - (TCInt const &_Value) const;
		constexpr TCInt operator * (TCInt const &_Value) const;
		constexpr TCInt operator / (TCInt const &_Value) const;
		constexpr TCInt operator >> (uaint _Value) const;
		constexpr TCInt operator << (uaint _Value) const;
		constexpr TCInt operator % (TCInt const &_Value) const;
		constexpr TCInt operator & (TCInt const &_Value) const;
		constexpr TCInt operator | (TCInt const &_Value) const;
		constexpr TCInt operator ^ (TCInt const &_Value) const;
		constexpr bool operator && (TCInt const &_Value) const;
		constexpr bool operator || (TCInt const &_Value) const;

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Binary assignment operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr TCInt &operator += (TCInt const &_Value);
		constexpr TCInt &operator -= (TCInt const &_Value);
		constexpr TCInt &operator *= (TCInt const &_Value);
		static constexpr bool fs_IsBitSet(uaint _Bit);
		constexpr TCInt &operator /= (TCInt const &_Value);
		constexpr TCInt &operator %= (TCInt const &_Value);

		constexpr TCInt &operator >>= (uaint _Value);
		constexpr TCInt &operator <<= (uaint _Value);
		constexpr TCInt &operator &= (TCInt const &_Value);
		constexpr TCInt &operator ^= (TCInt const &_Value);
		constexpr TCInt &operator |= (TCInt const &_Value);

		/************************************************************************************************\
		||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
		|| Binary comparative operators
		||______________________________________________________________________________________________||
		\************************************************************************************************/

		constexpr bool operator == (TCInt const &_Value) const noexcept;
		constexpr COrdering_Strong operator <=> (TCInt const &_Value) const noexcept;

		static constexpr aint mc_LowerBits = sizeof(t_CLower) * 8;
		static constexpr aint mc_LowerFirstBit = 0;
		static constexpr aint mc_LowerLastBit = mc_LowerBits - 1;
		static constexpr aint mc_UpperBits = sizeof(t_CUpper) * 8;
		static constexpr aint mc_UpperFirstBit = mc_LowerBits;
		static constexpr aint mc_UpperLastBit = mc_UpperBits + mc_LowerBits - 1;
		static constexpr aint mc_AllBits = mc_LowerBits + mc_UpperBits;
		static constexpr aint mc_HalfBits = mc_AllBits / 2;

		static_assert(mc_UpperBits >= mc_LowerBits, "If non symmetric sizes for constituent integers, the upper integer needs to be the larger one, otherwise sign extension wont work");

		static constexpr aint mc_Size = sizeof(t_CUpper) + sizeof(t_CLower);

		static constexpr bool mc_bIsSigned = NTraits::cIsSigned<t_CUpper>;

		static constexpr t_CUpper mc_UpperZero{0};
		static constexpr t_CUpper mc_UpperOne{1};
		static constexpr t_CLower mc_LowerZero{0};
		static constexpr t_CLower mc_LowerOne{1};

#ifdef DMibPLittleEndian
		t_CLower m_Lower{};
		t_CUpper m_Upper{};
#else
		t_CUpper m_Upper{};
		t_CLower m_Lower{};
#endif

	private:
		template <typename tf_CDummy>
		constexpr inline_small void fp_SignExtendUpper(TCEnableIf<NTraits::cIsSigned<tf_CDummy> && NTraits::cIsFundamental<tf_CDummy>, tf_CDummy> *_pDummy = nullptr);
		template <typename tf_CDummy>
		constexpr inline_small void fp_SignExtendUpper(TCEnableIf<!NTraits::cIsSigned<tf_CDummy>, tf_CDummy> *_pDummy = nullptr);
		template <typename tf_CDummy>
		constexpr inline_small void fp_SignExtendUpper(TCEnableIf<NTraits::cIsSigned<tf_CDummy> && !NTraits::cIsFundamental<tf_CDummy>, tf_CDummy> *_pDummy = nullptr);
	};

	template <typename t_CUpper, typename t_CLower>
	struct TCInt<t_CUpper, t_CLower>::CConstants
	{
		static constexpr TCInt<t_CUpper, t_CLower> mc_Zero{0};
		static constexpr TCInt<t_CUpper, t_CLower> mc_One{1};
	};
}

namespace NMib::NTraits::NPrivate
{
	template <typename t_CUpper, typename t_CLower>
	struct TCIsSigned<NMib::NNumeric::TCInt<t_CUpper, t_CLower>>
	{
		static constexpr bool mc_bValue = NMib::NTraits::cIsSigned<t_CUpper>;
	};

	template <typename t_CUpper, typename t_CLower>
	struct TCUnsigned<NMib::NNumeric::TCInt<t_CUpper, t_CLower>>
	{
		using CType = NMib::NNumeric::TCInt<NMib::NTraits::TCUnsigned<t_CUpper>, t_CLower>;
	};

	template <typename t_CUpper, typename t_CLower>
	struct TCSigned<NMib::NNumeric::TCInt<t_CUpper, t_CLower>>
	{
		using CType = NMib::NNumeric::TCInt<NMib::NTraits::TCSigned<t_CUpper>, t_CLower>;
	};

	template <typename t_CUpper, typename t_CLower>
	struct TCIsInteger<NMib::NNumeric::TCInt<t_CUpper, t_CLower>>
	{
		static constexpr bool mc_bValue = true;
	};
}

namespace NMib
{
	template <typename tf_CInt>
	constexpr NTraits::TCSmallerType<tf_CInt> fg_GetLower(tf_CInt const &_Integer) noexcept;
	template <typename tf_CInt>
	constexpr NTraits::TCSmallerType<tf_CInt> fg_GetUpper(tf_CInt const &_Integer) noexcept;

	template <typename tf_CUpper, typename tf_CLower>
	constexpr typename NNumeric::TCInt<tf_CUpper, tf_CLower>::CLower const &fg_GetLower(NNumeric::TCInt<tf_CUpper, tf_CLower> const &_Integer) noexcept;
	template <typename tf_CUpper, typename tf_CLower>
	constexpr typename NNumeric::TCInt<tf_CUpper, tf_CLower>::CUpper const &fg_GetUpper(NNumeric::TCInt<tf_CUpper, tf_CLower> const &_Integer) noexcept;

	template <typename tf_CInteger>
	NTraits::TCUnsigned<tf_CInteger> &fg_Unsigned(tf_CInteger &_Integer);
	template <typename tf_CInteger>
	NTraits::TCSigned<tf_CInteger> &fg_Signed(tf_CInteger &_Integer);
}

#ifndef DMibPCanDo_int16
using int16 = NMib::NNumeric::TCInt<int8, uint8>;
#endif

#ifndef DMibPCanDo_uint16
using uint16 = NMib::NNumeric::TCInt<uint8, uint8>;
#endif

#ifndef DMibPCanDo_int32
using int32 = NMib::NNumeric::TCInt<int16, uint16>;
#endif

#ifndef DMibPCanDo_uint32
using uint32 = NMib::NNumeric::TCInt<uint16, uint16>;
#endif

#ifndef DMibPCanDo_int64
using int64 = NMib::NNumeric::TCInt<int32, uint32>;
#endif

#ifndef DMibPCanDo_uint64
using uint64 = NMib::NNumeric::TCInt<uint32, uint32>;
#endif

#ifndef DMibPCanDo_int80
using int80 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<int16, uint16>, NMib::NNumeric::TCInt<uint16, uint16>>, uint16>;
#endif

#ifndef DMibPCanDo_uint80
using uint80 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<uint16, uint16>, NMib::NNumeric::TCInt<uint16, uint16>>, uint16>;
#endif

#ifndef DMibPCanDo_int96
using int96 = NMib::NNumeric::TCInt<NMib::TCConditional<alignof(int64) <= 4, int64, NMib::NNumeric::TCInt<int32, uint32>>, uint32>;
#endif

#ifndef DMibPCanDo_uint96
using uint96 = NMib::NNumeric::TCInt<NMib::TCConditional<alignof(uint64) <= 4, uint64, NMib::NNumeric::TCInt<uint32, uint32>>, uint32>;
#endif

#ifndef DMibPCanDo_int128
using int128 = NMib::NNumeric::TCInt<int64, uint64>;
#endif

#ifndef DMibPCanDo_uint128
using uint128 = NMib::NNumeric::TCInt<uint64, uint64>;
#endif

#ifndef DMibPCanDo_int160
using int160 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<int32, uint32>, NMib::NNumeric::TCInt<uint32, uint32>>, uint32>;
#endif

#ifndef DMibPCanDo_uint160
using uint160 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<uint32, uint32>, NMib::NNumeric::TCInt<uint32, uint32>>, uint32>;
#endif

#ifndef DMibPCanDo_int192
using int192 = NMib::NNumeric::TCInt<NMib::TCConditional<alignof(int128) <= 8, int128, NMib::NNumeric::TCInt<int64, uint64>>, uint64>;
#endif

#ifndef DMibPCanDo_uint192
using uint192 = NMib::NNumeric::TCInt<NMib::TCConditional<alignof(uint128) <= 8, uint128, NMib::NNumeric::TCInt<uint64, uint64>>, uint64>;
#endif

#ifndef DMibPCanDo_int256
using int256 = NMib::NNumeric::TCInt<int128, uint128>;
#endif

#ifndef DMibPCanDo_uint256
using uint256 = NMib::NNumeric::TCInt<uint128, uint128>;
#endif

#ifndef DMibPCanDo_int320
using int320 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<int64, uint64>, NMib::NNumeric::TCInt<uint64, uint64>>, uint64>;
#endif

#ifndef DMibPCanDo_uint320
using uint320 = NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<NMib::NNumeric::TCInt<uint64, uint64>, NMib::NNumeric::TCInt<uint64, uint64>>, uint64>;
#endif

#ifndef DMibPCanDo_int384
using int384 = NMib::NNumeric::TCInt<int256, uint128>;
#endif

#ifndef DMibPCanDo_uint384
using uint384 = NMib::NNumeric::TCInt<uint256, uint128>;
#endif

#ifndef DMibPCanDo_int512
using int512 = NMib::NNumeric::TCInt<int256, uint256>;
#endif

#ifndef DMibPCanDo_uint512
using uint512 = NMib::NNumeric::TCInt<uint256, uint256>;
#endif

#ifndef DMibPCanDo_int1024
using int1024 = NMib::NNumeric::TCInt<int512, uint512>;
#endif

#ifndef DMibPCanDo_uint1024
using uint1024 = NMib::NNumeric::TCInt<uint512, uint512>;
#endif

#ifndef DMibPCanDo_int2048
using int2048 = NMib::NNumeric::TCInt<int1024, uint1024>;
#endif

#ifndef DMibPCanDo_uint2048
using uint2048 = NMib::NNumeric::TCInt<uint1024, uint1024>;
#endif

#ifndef DMibPCanDo_int4096
using int4096 = NMib::NNumeric::TCInt<int2048, uint2048>;
#endif

#ifndef DMibPCanDo_uint4096
using uint4096 = NMib::NNumeric::TCInt<uint2048, uint2048>;
#endif

#ifndef DMibPCanDo_int8192
using int8192 = NMib::NNumeric::TCInt<int4096, uint4096>;
#endif

#ifndef DMibPCanDo_uint8192
using uint8192 = NMib::NNumeric::TCInt<uint4096, uint4096>;
#endif

#ifndef DMibPCanDo_int16384
using int16384 = NMib::NNumeric::TCInt<int8192, uint8192>;
#endif

#ifndef DMibPCanDo_uint16384
using uint16384 = NMib::NNumeric::TCInt<uint8192, uint8192>;
#endif

#if !(defined(DMibPCanDo_uint8) && defined(DMibPCanDo_uint16))
DMibTraitsImplementSizePair(uint8, uint16);
#endif
#if !(defined(DMibPCanDo_uint16) && defined(DMibPCanDo_uint32))
DMibTraitsImplementSizePair(uint16, uint32);
#endif
#if !(defined(DMibPCanDo_uint32) && defined(DMibPCanDo_uint64))
DMibTraitsImplementSizePair(uint32, uint64);
#endif
#if !(defined(DMibPCanDo_uint64) && defined(DMibPCanDo_uint128))
DMibTraitsImplementSizePair(uint64, uint128);
#endif
#if !(defined(DMibPCanDo_uint80) && defined(DMibPCanDo_uint160))
DMibTraitsImplementSizePair(uint80, uint160);
#endif
#if !(defined(DMibPCanDo_uint96) && defined(DMibPCanDo_uint192))
DMibTraitsImplementSizePair(uint96, uint192);
#endif
#if !(defined(DMibPCanDo_uint160) && defined(DMibPCanDo_uint320))
DMibTraitsImplementSizePair(uint160, uint320);
#endif
#if !(defined(DMibPCanDo_uint192) && defined(DMibPCanDo_uint384))
DMibTraitsImplementSizePair(uint192, uint384);
#endif
#if !(defined(DMibPCanDo_uint128) && defined(DMibPCanDo_uint256))
DMibTraitsImplementSizePair(uint128, uint256);
#endif
#if !(defined(DMibPCanDo_uint256) && defined(DMibPCanDo_uint512))
DMibTraitsImplementSizePair(uint256, uint512);
#endif
#if !(defined(DMibPCanDo_uint512) && defined(DMibPCanDo_uint1024))
DMibTraitsImplementSizePair(uint512, uint1024);
#endif
#if !(defined(DMibPCanDo_uint1024) && defined(DMibPCanDo_uint2048))
DMibTraitsImplementSizePair(uint1024, uint2048);
#endif
#if !(defined(DMibPCanDo_uint2048) && defined(DMibPCanDo_uint4096))
DMibTraitsImplementSizePair(uint2048, uint4096);
#endif
#if !(defined(DMibPCanDo_uint4096) && defined(DMibPCanDo_uint8192))
DMibTraitsImplementSizePair(uint4096, uint8192);
#endif
#if !(defined(DMibPCanDo_uint8192) && defined(DMibPCanDo_uint16384))
DMibTraitsImplementSizePair(uint8192, uint16384);
#endif

#if !(defined(DMibPCanDo_int8) && defined(DMibPCanDo_int16))
DMibTraitsImplementSizePair(int8, int16);
#endif
#if !(defined(DMibPCanDo_int16) && defined(DMibPCanDo_int32))
DMibTraitsImplementSizePair(int16, int32);
#endif
#if !(defined(DMibPCanDo_int32) && defined(DMibPCanDo_int64))
DMibTraitsImplementSizePair(int32, int64);
#endif
#if !(defined(DMibPCanDo_int64) && defined(DMibPCanDo_int128))
DMibTraitsImplementSizePair(int64, int128);
#endif
#if !(defined(DMibPCanDo_int80) && defined(DMibPCanDo_int160))
DMibTraitsImplementSizePair(int80, int160);
#endif
#if !(defined(DMibPCanDo_int96) && defined(DMibPCanDo_int192))
DMibTraitsImplementSizePair(int96, int192);
#endif
#if !(defined(DMibPCanDo_int128) && defined(DMibPCanDo_int256))
DMibTraitsImplementSizePair(int128, int256);
#endif
#if !(defined(DMibPCanDo_int160) && defined(DMibPCanDo_int320))
DMibTraitsImplementSizePair(int160, int320);
#endif
#if !(defined(DMibPCanDo_int192) && defined(DMibPCanDo_int384))
DMibTraitsImplementSizePair(int192, int384);
#endif
#if !(defined(DMibPCanDo_int256) && defined(DMibPCanDo_int512))
DMibTraitsImplementSizePair(int256, int512);
#endif
#if !(defined(DMibPCanDo_int512) && defined(DMibPCanDo_int1024))
DMibTraitsImplementSizePair(int512, int1024);
#endif
#if !(defined(DMibPCanDo_int1024) && defined(DMibPCanDo_int2048))
DMibTraitsImplementSizePair(int1024, int2048);
#endif
#if !(defined(DMibPCanDo_int2048) && defined(DMibPCanDo_int4096))
DMibTraitsImplementSizePair(int2048, int4096);
#endif
#if !(defined(DMibPCanDo_int4096) && defined(DMibPCanDo_int8192))
DMibTraitsImplementSizePair(int4096, int8192);
#endif
#if !(defined(DMibPCanDo_int8192) && defined(DMibPCanDo_int16384))
DMibTraitsImplementSizePair(int8192, int16384);
#endif

#if !defined(DMibPCanDo_int8)
DMibTraitsImplementIntegerFromSize(int8);
#endif
#if !defined(DMibPCanDo_int16)
DMibTraitsImplementIntegerFromSize(int16);
#endif
#if !defined(DMibPCanDo_int32)
DMibTraitsImplementIntegerFromSize(int32);
#endif
#if !defined(DMibPCanDo_int64)
DMibTraitsImplementIntegerFromSize(int64);
#endif
#if !defined(DMibPCanDo_int80)
DMibTraitsImplementIntegerFromSize(int80);
#endif
#if !defined(DMibPCanDo_int96)
DMibTraitsImplementIntegerFromSize(int96);
#endif
#if !defined(DMibPCanDo_int128)
DMibTraitsImplementIntegerFromSize(int128);
#endif
#if !defined(DMibPCanDo_int160)
DMibTraitsImplementIntegerFromSize(int160);
#endif
#if !defined(DMibPCanDo_int192)
DMibTraitsImplementIntegerFromSize(int192);
#endif
#if !defined(DMibPCanDo_int256)
DMibTraitsImplementIntegerFromSize(int256);
#endif
#if !defined(DMibPCanDo_int320)
DMibTraitsImplementIntegerFromSize(int320);
#endif
#if !defined(DMibPCanDo_int384)
DMibTraitsImplementIntegerFromSize(int384);
#endif
#if !defined(DMibPCanDo_int512)
DMibTraitsImplementIntegerFromSize(int512);
#endif
#if !defined(DMibPCanDo_int1024)
DMibTraitsImplementIntegerFromSize(int1024);
#endif
#if !defined(DMibPCanDo_int2048)
DMibTraitsImplementIntegerFromSize(int2048);
#endif
#if !defined(DMibPCanDo_int4096)
DMibTraitsImplementIntegerFromSize(int4096);
#endif
#if !defined(DMibPCanDo_int8192)
DMibTraitsImplementIntegerFromSize(int8192);
#endif
#if !defined(DMibPCanDo_int16384)
DMibTraitsImplementIntegerFromSize(int16384);
#endif

#ifndef DMibPNoShortCuts
using namespace NMib::NNumeric;
#endif

#include "Malterlib_Numeric_Integer.hpp"
