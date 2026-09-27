// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float_fp32.h"
#include "Malterlib_Numeric_Simd_Backend_Scalar.hpp"
#include "Malterlib_Numeric_Simd_Backend_Pair.hpp"

#if defined(DArchitectureExtension_NEON)
#	include "Malterlib_Numeric_Simd_Backend_NEON.hpp"
#elif defined(DArchitectureExtension_SSE) && defined(__SSE2__)
#	include "Malterlib_Numeric_Simd_Backend_SSE.hpp"
#	ifdef DArchitectureExtension_AVX2
#		include "Malterlib_Numeric_Simd_Backend_AVX2.hpp"
#	endif
#endif

namespace NMib::NNumeric
{
	namespace NPrivate
	{
#if defined(DArchitectureExtension_NEON)
		using CSimdBackend_Native4 = CSimdBackend_NEON4;
#elif defined(DArchitectureExtension_SSE) && defined(__SSE2__)
		using CSimdBackend_Native4 = CSimdBackend_SSE4;
#else
		using CSimdBackend_Native4 = TCSimdBackend_Scalar<4>;
#endif

#if defined(DArchitectureExtension_AVX2) && !defined(DArchitectureExtension_NEON)
		using CSimdBackend_Native8 = CSimdBackend_AVX8;
#else
		using CSimdBackend_Native8 = TCSimdBackend_Pair<CSimdBackend_Native4>;
#endif

		template <umint t_nLanes>
		struct TCSimdNativeBackend
		{
			using CType = TCSimdBackend_Scalar<t_nLanes>;
		};

		template <>
		struct TCSimdNativeBackend<4>
		{
			using CType = CSimdBackend_Native4;
		};

		template <>
		struct TCSimdNativeBackend<8>
		{
			using CType = CSimdBackend_Native8;
		};

		template <>
		struct TCSimdNativeBackend<16>
		{
			using CType = TCSimdBackend_Pair<CSimdBackend_Native8>;
		};

		template <typename t_CType, typename t_CBackend>
		struct TCSimdFromElement;
	}

	template <typename t_CBackend>
	struct TCSimdFloat;

	template <typename t_CBackend>
	struct TCSimdInt;

	// One flag per lane, produced by comparisons and consumed by fs_Select.
	template <typename t_CBackend>
	struct TCSimdMask
	{
		using CBackend = t_CBackend;
		using CStorage = typename t_CBackend::CMask;

		static constexpr umint mc_nLanes = t_CBackend::mc_nLanes;
		static constexpr uint32 mc_AllBits = uint32((uint64(1) << t_CBackend::mc_nLanes) - 1);

		TCSimdMask() = default;
		explicit TCSimdMask(CStorage const &_Storage);

		static TCSimdMask fs_False();
		static TCSimdMask fs_True();

		bool f_Any() const;
		bool f_All() const;
		bool f_None() const;
		bool f_GetLane(umint _iLane) const;
		uint32 f_GetBits() const;
		TCSimdInt<t_CBackend> f_ToInt() const;

		TCSimdMask operator & (TCSimdMask const &_Right) const;
		TCSimdMask operator | (TCSimdMask const &_Right) const;
		TCSimdMask operator ^ (TCSimdMask const &_Right) const;
		TCSimdMask operator ~ () const;
		TCSimdMask &operator &= (TCSimdMask const &_Right);
		TCSimdMask &operator |= (TCSimdMask const &_Right);
		TCSimdMask &operator ^= (TCSimdMask const &_Right);

		CStorage m_Value;
	};

	template <typename t_CBackend>
	struct TCSimdInt
	{
		using CBackend = t_CBackend;
		using CStorage = typename t_CBackend::CInt;
		using CElement = int32;
		using CMask = TCSimdMask<t_CBackend>;
		using CFloat = TCSimdFloat<t_CBackend>;

		static constexpr umint mc_nLanes = t_CBackend::mc_nLanes;

		TCSimdInt() = default;
		TCSimdInt(int32 _Value);
		explicit TCSimdInt(CStorage const &_Storage);

		template <typename ...tfp_CLanes>
			requires (sizeof...(tfp_CLanes) == t_CBackend::mc_nLanes && sizeof...(tfp_CLanes) > 1)
		TCSimdInt(tfp_CLanes ...p_Lanes);

		static TCSimdInt fs_Zero();
		static TCSimdInt fs_Load(int32 const *_pSource);
		static TCSimdInt fs_LoadAligned(int32 const *_pSource);
		static TCSimdInt fs_Select(CMask const &_Mask, TCSimdInt const &_True, TCSimdInt const &_False);

		void f_Store(int32 *o_pDestination) const;
		void f_StoreAligned(int32 *o_pDestination) const;
		int32 f_GetLane(umint _iLane) const;
		void f_SetLane(umint _iLane, int32 _Value);

		TCSimdInt f_Min(TCSimdInt const &_Other) const;
		TCSimdInt f_Max(TCSimdInt const &_Other) const;
		TCSimdInt f_Clamp(TCSimdInt const &_Min, TCSimdInt const &_Max) const;
		TCSimdInt f_Abs() const;
		TCSimdInt f_ShiftRightLogical(uint32 _nBits) const;
		CFloat f_ToFloat() const;

		template <umint ...tfp_iLanes>
			requires (sizeof...(tfp_iLanes) == t_CBackend::mc_nLanes && t_CBackend::mc_nLanes == 4)
		TCSimdInt f_Shuffle() const;

		TCSimdInt operator + (TCSimdInt const &_Right) const;
		TCSimdInt operator - (TCSimdInt const &_Right) const;
		TCSimdInt operator * (TCSimdInt const &_Right) const;
		TCSimdInt operator - () const;
		TCSimdInt operator & (TCSimdInt const &_Right) const;
		TCSimdInt operator | (TCSimdInt const &_Right) const;
		TCSimdInt operator ^ (TCSimdInt const &_Right) const;
		TCSimdInt operator ~ () const;
		TCSimdInt operator << (uint32 _nBits) const;
		TCSimdInt operator >> (uint32 _nBits) const;

		TCSimdInt &operator += (TCSimdInt const &_Right);
		TCSimdInt &operator -= (TCSimdInt const &_Right);
		TCSimdInt &operator *= (TCSimdInt const &_Right);
		TCSimdInt &operator &= (TCSimdInt const &_Right);
		TCSimdInt &operator |= (TCSimdInt const &_Right);
		TCSimdInt &operator ^= (TCSimdInt const &_Right);
		TCSimdInt &operator <<= (uint32 _nBits);
		TCSimdInt &operator >>= (uint32 _nBits);

		CMask operator == (TCSimdInt const &_Right) const;
		CMask operator != (TCSimdInt const &_Right) const;
		CMask operator < (TCSimdInt const &_Right) const;
		CMask operator > (TCSimdInt const &_Right) const;
		CMask operator <= (TCSimdInt const &_Right) const;
		CMask operator >= (TCSimdInt const &_Right) const;

		CStorage m_Value;
	};

	template <typename t_CBackend>
	struct TCSimdFloat
	{
		using CBackend = t_CBackend;
		using CStorage = typename t_CBackend::CFloat;
		using CElement = pfp32;
		using CMask = TCSimdMask<t_CBackend>;
		using CInt = TCSimdInt<t_CBackend>;

		static constexpr umint mc_nLanes = t_CBackend::mc_nLanes;

		TCSimdFloat() = default;
		TCSimdFloat(pfp32 _Value);
		explicit TCSimdFloat(CStorage const &_Storage);

		template <typename ...tfp_CLanes>
			requires (sizeof...(tfp_CLanes) == t_CBackend::mc_nLanes && sizeof...(tfp_CLanes) > 1)
		TCSimdFloat(tfp_CLanes ...p_Lanes);

		static TCSimdFloat fs_Zero();
		static TCSimdFloat fs_Load(pfp32 const *_pSource);
		static TCSimdFloat fs_LoadAligned(pfp32 const *_pSource);
		static TCSimdFloat fs_Select(CMask const &_Mask, TCSimdFloat const &_True, TCSimdFloat const &_False);
		static TCSimdFloat fs_FromBits(CInt const &_Bits);

		void f_Store(pfp32 *o_pDestination) const;
		void f_StoreAligned(pfp32 *o_pDestination) const;
		pfp32 f_GetLane(umint _iLane) const;
		void f_SetLane(umint _iLane, pfp32 _Value);

		TCSimdFloat f_Min(TCSimdFloat const &_Other) const;
		TCSimdFloat f_Max(TCSimdFloat const &_Other) const;
		TCSimdFloat f_Clamp(TCSimdFloat const &_Min, TCSimdFloat const &_Max) const;
		TCSimdFloat f_Abs() const;
		TCSimdFloat f_Sqrt() const;
		TCSimdFloat f_Floor() const;
		TCSimdFloat f_Ceil() const;
		pfp32 f_Sum() const;
		CInt f_ToInt() const;
		CInt f_ToBits() const;

		template <umint ...tfp_iLanes>
			requires (sizeof...(tfp_iLanes) == t_CBackend::mc_nLanes && t_CBackend::mc_nLanes == 4)
		TCSimdFloat f_Shuffle() const;

		TCSimdFloat operator + (TCSimdFloat const &_Right) const;
		TCSimdFloat operator - (TCSimdFloat const &_Right) const;
		TCSimdFloat operator * (TCSimdFloat const &_Right) const;
		TCSimdFloat operator / (TCSimdFloat const &_Right) const;
		TCSimdFloat operator - () const;

		TCSimdFloat &operator += (TCSimdFloat const &_Right);
		TCSimdFloat &operator -= (TCSimdFloat const &_Right);
		TCSimdFloat &operator *= (TCSimdFloat const &_Right);
		TCSimdFloat &operator /= (TCSimdFloat const &_Right);

		CMask operator == (TCSimdFloat const &_Right) const;
		CMask operator != (TCSimdFloat const &_Right) const;
		CMask operator < (TCSimdFloat const &_Right) const;
		CMask operator > (TCSimdFloat const &_Right) const;
		CMask operator <= (TCSimdFloat const &_Right) const;
		CMask operator >= (TCSimdFloat const &_Right) const;

		CStorage m_Value;
	};

	template <typename t_CBackend>
	TCSimdFloat<t_CBackend> operator + (pfp32 _Left, TCSimdFloat<t_CBackend> const &_Right);

	template <typename t_CBackend>
	TCSimdFloat<t_CBackend> operator - (pfp32 _Left, TCSimdFloat<t_CBackend> const &_Right);

	template <typename t_CBackend>
	TCSimdFloat<t_CBackend> operator * (pfp32 _Left, TCSimdFloat<t_CBackend> const &_Right);

	template <typename t_CBackend>
	TCSimdFloat<t_CBackend> operator / (pfp32 _Left, TCSimdFloat<t_CBackend> const &_Right);

	namespace NPrivate
	{
		template <typename t_CBackend>
		struct TCSimdFromElement<pfp32, t_CBackend>
		{
			using CType = TCSimdFloat<t_CBackend>;
		};

		template <typename t_CBackend>
		struct TCSimdFromElement<fp32, t_CBackend>
		{
			using CType = TCSimdFloat<t_CBackend>;
		};

		template <typename t_CBackend>
		struct TCSimdFromElement<int32, t_CBackend>
		{
			using CType = TCSimdInt<t_CBackend>;
		};

		template <typename t_CBackend>
		struct TCSimdFromElement<bool, t_CBackend>
		{
			using CType = TCSimdMask<t_CBackend>;
		};
	}

	template <typename t_CType, umint t_nLanes>
	using TCSimd = typename NPrivate::TCSimdFromElement<t_CType, typename NPrivate::TCSimdNativeBackend<t_nLanes>::CType>::CType;

	// Same interface on the scalar backend, which defines the expected results.
	template <typename t_CType, umint t_nLanes>
	using TCSimdReference = typename NPrivate::TCSimdFromElement<t_CType, NPrivate::TCSimdBackend_Scalar<t_nLanes>>::CType;

	using CSimd4_fp32 = TCSimd<pfp32, 4>;
	using CSimd4_int32 = TCSimd<int32, 4>;
	using CSimd4_bool = TCSimd<bool, 4>;

	using CSimd8_fp32 = TCSimd<pfp32, 8>;
	using CSimd8_int32 = TCSimd<int32, 8>;
	using CSimd8_bool = TCSimd<bool, 8>;
}

#include "Malterlib_Numeric_Simd.hpp"

#ifndef DMibPNoShortCuts
	using namespace NMib::NNumeric;
#endif
