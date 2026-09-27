// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <emmintrin.h>
#ifdef DArchitectureExtension_SSE41
#	include <smmintrin.h>
#endif

namespace NMib::NNumeric::NPrivate
{
	struct CSimdBackend_SSE4
	{
		static constexpr umint mc_nLanes = 4;

		using CFloat = __m128;
		using CInt = __m128i;
		using CMask = __m128i;

		static inline_always CFloat fs_SignBits()
		{
			return _mm_castsi128_ps(_mm_set1_epi32(int32(0x80000000u)));
		}

		// Float

		static inline_always CFloat fs_FloatZero()
		{
			return _mm_setzero_ps();
		}

		static inline_always CFloat fs_FloatSplat(pfp32 _Value)
		{
			return _mm_set1_ps(_Value);
		}

		static inline_always CFloat fs_FloatLoad(pfp32 const *_pSource)
		{
			return _mm_loadu_ps(_pSource);
		}

		static inline_always CFloat fs_FloatLoadAligned(pfp32 const *_pSource)
		{
			return _mm_load_ps(_pSource);
		}

		static inline_always void fs_FloatStore(pfp32 *o_pDestination, CFloat _Value)
		{
			_mm_storeu_ps(o_pDestination, _Value);
		}

		static inline_always void fs_FloatStoreAligned(pfp32 *o_pDestination, CFloat _Value)
		{
			_mm_store_ps(o_pDestination, _Value);
		}

		static inline_always pfp32 fs_FloatGetLane(CFloat _Value, umint _iLane)
		{
			pfp32 Lanes[4];
			_mm_storeu_ps(Lanes, _Value);

			return Lanes[_iLane];
		}

		static inline_always CFloat fs_FloatSetLane(CFloat _Value, umint _iLane, pfp32 _LaneValue)
		{
			pfp32 Lanes[4];
			_mm_storeu_ps(Lanes, _Value);
			Lanes[_iLane] = _LaneValue;

			return _mm_loadu_ps(Lanes);
		}

		static inline_always CFloat fs_FloatAdd(CFloat _Left, CFloat _Right)
		{
			return _mm_add_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatSub(CFloat _Left, CFloat _Right)
		{
			return _mm_sub_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatMul(CFloat _Left, CFloat _Right)
		{
			return _mm_mul_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatDiv(CFloat _Left, CFloat _Right)
		{
			return _mm_div_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatMin(CFloat _Left, CFloat _Right)
		{
			return _mm_min_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatMax(CFloat _Left, CFloat _Right)
		{
			return _mm_max_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatNeg(CFloat _Value)
		{
			return _mm_xor_ps(_Value, fs_SignBits());
		}

		static inline_always CFloat fs_FloatAbs(CFloat _Value)
		{
			return _mm_andnot_ps(fs_SignBits(), _Value);
		}

		static inline_always CFloat fs_FloatSqrt(CFloat _Value)
		{
			return _mm_sqrt_ps(_Value);
		}

#ifndef DArchitectureExtension_SSE41
		// _Adjust is subtracted where the truncated value is on the wrong side of the input
		static inline_always CFloat fs_FloatRoundFromTruncated(CFloat _Value, CFloat _Truncated, CFloat _NeedsAdjust, pfp32 _Adjust)
		{
			CFloat Adjusted = _mm_sub_ps(_Truncated, _mm_and_ps(_NeedsAdjust, _mm_set1_ps(_Adjust)));
			CFloat Signed = _mm_or_ps(_mm_andnot_ps(fs_SignBits(), Adjusted), _mm_and_ps(fs_SignBits(), _Value));

			// Values this large are already integral, and NaN must pass through
			CFloat IsSmall = _mm_cmplt_ps(fs_FloatAbs(_Value), _mm_set1_ps(8388608.0f));

			return _mm_or_ps(_mm_and_ps(IsSmall, Signed), _mm_andnot_ps(IsSmall, _Value));
		}
#endif

		static inline_always CFloat fs_FloatFloor(CFloat _Value)
		{
#ifdef DArchitectureExtension_SSE41
			return _mm_floor_ps(_Value);
#else
			CFloat Truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(_Value));

			return fs_FloatRoundFromTruncated(_Value, Truncated, _mm_cmpgt_ps(Truncated, _Value), 1.0f);
#endif
		}

		static inline_always CFloat fs_FloatCeil(CFloat _Value)
		{
#ifdef DArchitectureExtension_SSE41
			return _mm_ceil_ps(_Value);
#else
			CFloat Truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(_Value));

			return fs_FloatRoundFromTruncated(_Value, Truncated, _mm_cmplt_ps(Truncated, _Value), -1.0f);
#endif
		}

		static inline_always CMask fs_FloatEqual(CFloat _Left, CFloat _Right)
		{
			return _mm_castps_si128(_mm_cmpeq_ps(_Left, _Right));
		}

		static inline_always CMask fs_FloatLess(CFloat _Left, CFloat _Right)
		{
			return _mm_castps_si128(_mm_cmplt_ps(_Left, _Right));
		}

		static inline_always CMask fs_FloatLessEqual(CFloat _Left, CFloat _Right)
		{
			return _mm_castps_si128(_mm_cmple_ps(_Left, _Right));
		}

		static inline_always CFloat fs_FloatSelect(CMask _Mask, CFloat _True, CFloat _False)
		{
			CFloat Mask = _mm_castsi128_ps(_Mask);
#ifdef DArchitectureExtension_SSE41
			return _mm_blendv_ps(_False, _True, Mask);
#else
			return _mm_or_ps(_mm_and_ps(Mask, _True), _mm_andnot_ps(Mask, _False));
#endif
		}

		static inline_always pfp32 fs_FloatSum(CFloat _Value)
		{
			CFloat Pairs = _mm_add_ps(_Value, _mm_shuffle_ps(_Value, _Value, _MM_SHUFFLE(2, 3, 0, 1)));

			return _mm_cvtss_f32(_mm_add_ss(Pairs, _mm_movehl_ps(Pairs, Pairs)));
		}

		static inline_always CInt fs_FloatToInt(CFloat _Value)
		{
			return _mm_cvttps_epi32(_Value);
		}

		static inline_always CFloat fs_FloatFromInt(CInt _Value)
		{
			return _mm_cvtepi32_ps(_Value);
		}

		static inline_always CInt fs_FloatBitsToInt(CFloat _Value)
		{
			return _mm_castps_si128(_Value);
		}

		static inline_always CFloat fs_FloatBitsFromInt(CInt _Value)
		{
			return _mm_castsi128_ps(_Value);
		}

		template <umint t_iLane0, umint t_iLane1, umint t_iLane2, umint t_iLane3>
		static inline_always CFloat fs_FloatShuffle(CFloat _Value)
		{
			return _mm_shuffle_ps(_Value, _Value, _MM_SHUFFLE(int(t_iLane3), int(t_iLane2), int(t_iLane1), int(t_iLane0)));
		}

		// Int

		static inline_always CInt fs_IntZero()
		{
			return _mm_setzero_si128();
		}

		static inline_always CInt fs_IntSplat(int32 _Value)
		{
			return _mm_set1_epi32(_Value);
		}

		static inline_always CInt fs_IntLoad(int32 const *_pSource)
		{
			return _mm_loadu_si128((__m128i const *)_pSource);
		}

		static inline_always CInt fs_IntLoadAligned(int32 const *_pSource)
		{
			return _mm_load_si128((__m128i const *)_pSource);
		}

		static inline_always void fs_IntStore(int32 *o_pDestination, CInt _Value)
		{
			_mm_storeu_si128((__m128i *)o_pDestination, _Value);
		}

		static inline_always void fs_IntStoreAligned(int32 *o_pDestination, CInt _Value)
		{
			_mm_store_si128((__m128i *)o_pDestination, _Value);
		}

		static inline_always int32 fs_IntGetLane(CInt _Value, umint _iLane)
		{
			int32 Lanes[4];
			fs_IntStore(Lanes, _Value);

			return Lanes[_iLane];
		}

		static inline_always CInt fs_IntSetLane(CInt _Value, umint _iLane, int32 _LaneValue)
		{
			int32 Lanes[4];
			fs_IntStore(Lanes, _Value);
			Lanes[_iLane] = _LaneValue;

			return fs_IntLoad(Lanes);
		}

		static inline_always CInt fs_IntAdd(CInt _Left, CInt _Right)
		{
			return _mm_add_epi32(_Left, _Right);
		}

		static inline_always CInt fs_IntSub(CInt _Left, CInt _Right)
		{
			return _mm_sub_epi32(_Left, _Right);
		}

		static inline_always CInt fs_IntMul(CInt _Left, CInt _Right)
		{
#ifdef DArchitectureExtension_SSE41
			return _mm_mullo_epi32(_Left, _Right);
#else
			CInt Even = _mm_mul_epu32(_Left, _Right);
			CInt Odd = _mm_mul_epu32(_mm_srli_si128(_Left, 4), _mm_srli_si128(_Right, 4));

			return _mm_unpacklo_epi32(_mm_shuffle_epi32(Even, _MM_SHUFFLE(0, 0, 2, 0)), _mm_shuffle_epi32(Odd, _MM_SHUFFLE(0, 0, 2, 0)));
#endif
		}

		static inline_always CInt fs_IntSelect(CMask _Mask, CInt _True, CInt _False)
		{
			return _mm_or_si128(_mm_and_si128(_Mask, _True), _mm_andnot_si128(_Mask, _False));
		}

		static inline_always CInt fs_IntMin(CInt _Left, CInt _Right)
		{
#ifdef DArchitectureExtension_SSE41
			return _mm_min_epi32(_Left, _Right);
#else
			return fs_IntSelect(_mm_cmplt_epi32(_Left, _Right), _Left, _Right);
#endif
		}

		static inline_always CInt fs_IntMax(CInt _Left, CInt _Right)
		{
#ifdef DArchitectureExtension_SSE41
			return _mm_max_epi32(_Left, _Right);
#else
			return fs_IntSelect(_mm_cmpgt_epi32(_Left, _Right), _Left, _Right);
#endif
		}

		static inline_always CInt fs_IntNeg(CInt _Value)
		{
			return _mm_sub_epi32(_mm_setzero_si128(), _Value);
		}

		static inline_always CInt fs_IntAbs(CInt _Value)
		{
			CInt Sign = _mm_srai_epi32(_Value, 31);

			return _mm_sub_epi32(_mm_xor_si128(_Value, Sign), Sign);
		}

		static inline_always CInt fs_IntAnd(CInt _Left, CInt _Right)
		{
			return _mm_and_si128(_Left, _Right);
		}

		static inline_always CInt fs_IntOr(CInt _Left, CInt _Right)
		{
			return _mm_or_si128(_Left, _Right);
		}

		static inline_always CInt fs_IntXor(CInt _Left, CInt _Right)
		{
			return _mm_xor_si128(_Left, _Right);
		}

		static inline_always CInt fs_IntNot(CInt _Value)
		{
			return _mm_xor_si128(_Value, _mm_set1_epi32(-1));
		}

		static inline_always CInt fs_IntShiftLeft(CInt _Value, uint32 _nBits)
		{
			return _mm_sll_epi32(_Value, _mm_cvtsi32_si128(int32(_nBits)));
		}

		static inline_always CInt fs_IntShiftRight(CInt _Value, uint32 _nBits)
		{
			return _mm_sra_epi32(_Value, _mm_cvtsi32_si128(int32(_nBits)));
		}

		static inline_always CInt fs_IntShiftRightLogical(CInt _Value, uint32 _nBits)
		{
			return _mm_srl_epi32(_Value, _mm_cvtsi32_si128(int32(_nBits)));
		}

		static inline_always CMask fs_IntEqual(CInt _Left, CInt _Right)
		{
			return _mm_cmpeq_epi32(_Left, _Right);
		}

		static inline_always CMask fs_IntLess(CInt _Left, CInt _Right)
		{
			return _mm_cmplt_epi32(_Left, _Right);
		}

		template <umint t_iLane0, umint t_iLane1, umint t_iLane2, umint t_iLane3>
		static inline_always CInt fs_IntShuffle(CInt _Value)
		{
			return _mm_shuffle_epi32(_Value, _MM_SHUFFLE(int(t_iLane3), int(t_iLane2), int(t_iLane1), int(t_iLane0)));
		}

		// Mask

		static inline_always CMask fs_MaskFalse()
		{
			return _mm_setzero_si128();
		}

		static inline_always CMask fs_MaskTrue()
		{
			return _mm_set1_epi32(-1);
		}

		static inline_always CMask fs_MaskAnd(CMask _Left, CMask _Right)
		{
			return _mm_and_si128(_Left, _Right);
		}

		static inline_always CMask fs_MaskOr(CMask _Left, CMask _Right)
		{
			return _mm_or_si128(_Left, _Right);
		}

		static inline_always CMask fs_MaskXor(CMask _Left, CMask _Right)
		{
			return _mm_xor_si128(_Left, _Right);
		}

		static inline_always CMask fs_MaskNot(CMask _Value)
		{
			return _mm_xor_si128(_Value, _mm_set1_epi32(-1));
		}

		static inline_always uint32 fs_MaskBits(CMask _Value)
		{
			return uint32(_mm_movemask_ps(_mm_castsi128_ps(_Value)));
		}

		static inline_always CInt fs_MaskToInt(CMask _Value)
		{
			return _Value;
		}
	};
}
