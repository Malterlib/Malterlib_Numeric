// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <immintrin.h>

namespace NMib::NNumeric::NPrivate
{
	struct CSimdBackend_AVX8
	{
		static constexpr umint mc_nLanes = 8;

		using CFloat = __m256;
		using CInt = __m256i;
		using CMask = __m256i;

		static inline_always CFloat fs_SignBits()
		{
			return _mm256_castsi256_ps(_mm256_set1_epi32(int32(0x80000000u)));
		}

		// Float

		static inline_always CFloat fs_FloatZero()
		{
			return _mm256_setzero_ps();
		}

		static inline_always CFloat fs_FloatSplat(pfp32 _Value)
		{
			return _mm256_set1_ps(_Value);
		}

		static inline_always CFloat fs_FloatLoad(pfp32 const *_pSource)
		{
			return _mm256_loadu_ps(_pSource);
		}

		static inline_always CFloat fs_FloatLoadAligned(pfp32 const *_pSource)
		{
			return _mm256_load_ps(_pSource);
		}

		static inline_always void fs_FloatStore(pfp32 *o_pDestination, CFloat _Value)
		{
			_mm256_storeu_ps(o_pDestination, _Value);
		}

		static inline_always void fs_FloatStoreAligned(pfp32 *o_pDestination, CFloat _Value)
		{
			_mm256_store_ps(o_pDestination, _Value);
		}

		static inline_always pfp32 fs_FloatGetLane(CFloat _Value, umint _iLane)
		{
			pfp32 Lanes[8];
			_mm256_storeu_ps(Lanes, _Value);

			return Lanes[_iLane];
		}

		static inline_always CFloat fs_FloatSetLane(CFloat _Value, umint _iLane, pfp32 _LaneValue)
		{
			pfp32 Lanes[8];
			_mm256_storeu_ps(Lanes, _Value);
			Lanes[_iLane] = _LaneValue;

			return _mm256_loadu_ps(Lanes);
		}

		static inline_always CFloat fs_FloatAdd(CFloat _Left, CFloat _Right)
		{
			return _mm256_add_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatSub(CFloat _Left, CFloat _Right)
		{
			return _mm256_sub_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatMul(CFloat _Left, CFloat _Right)
		{
			return _mm256_mul_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatDiv(CFloat _Left, CFloat _Right)
		{
			return _mm256_div_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatMin(CFloat _Left, CFloat _Right)
		{
			return _mm256_min_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatMax(CFloat _Left, CFloat _Right)
		{
			return _mm256_max_ps(_Left, _Right);
		}

		static inline_always CFloat fs_FloatNeg(CFloat _Value)
		{
			return _mm256_xor_ps(_Value, fs_SignBits());
		}

		static inline_always CFloat fs_FloatAbs(CFloat _Value)
		{
			return _mm256_andnot_ps(fs_SignBits(), _Value);
		}

		static inline_always CFloat fs_FloatSqrt(CFloat _Value)
		{
			return _mm256_sqrt_ps(_Value);
		}

		static inline_always CFloat fs_FloatFloor(CFloat _Value)
		{
			return _mm256_floor_ps(_Value);
		}

		static inline_always CFloat fs_FloatCeil(CFloat _Value)
		{
			return _mm256_ceil_ps(_Value);
		}

		static inline_always CMask fs_FloatEqual(CFloat _Left, CFloat _Right)
		{
			return _mm256_castps_si256(_mm256_cmp_ps(_Left, _Right, _CMP_EQ_OQ));
		}

		static inline_always CMask fs_FloatLess(CFloat _Left, CFloat _Right)
		{
			return _mm256_castps_si256(_mm256_cmp_ps(_Left, _Right, _CMP_LT_OQ));
		}

		static inline_always CMask fs_FloatLessEqual(CFloat _Left, CFloat _Right)
		{
			return _mm256_castps_si256(_mm256_cmp_ps(_Left, _Right, _CMP_LE_OQ));
		}

		static inline_always CFloat fs_FloatSelect(CMask _Mask, CFloat _True, CFloat _False)
		{
			return _mm256_blendv_ps(_False, _True, _mm256_castsi256_ps(_Mask));
		}

		static inline_always pfp32 fs_FloatSum(CFloat _Value)
		{
			return CSimdBackend_SSE4::fs_FloatSum(_mm256_castps256_ps128(_Value)) + CSimdBackend_SSE4::fs_FloatSum(_mm256_extractf128_ps(_Value, 1));
		}

		static inline_always CInt fs_FloatToInt(CFloat _Value)
		{
			return _mm256_cvttps_epi32(_Value);
		}

		static inline_always CFloat fs_FloatFromInt(CInt _Value)
		{
			return _mm256_cvtepi32_ps(_Value);
		}

		static inline_always CInt fs_FloatBitsToInt(CFloat _Value)
		{
			return _mm256_castps_si256(_Value);
		}

		static inline_always CFloat fs_FloatBitsFromInt(CInt _Value)
		{
			return _mm256_castsi256_ps(_Value);
		}

		// Int

		static inline_always CInt fs_IntZero()
		{
			return _mm256_setzero_si256();
		}

		static inline_always CInt fs_IntSplat(int32 _Value)
		{
			return _mm256_set1_epi32(_Value);
		}

		static inline_always CInt fs_IntLoad(int32 const *_pSource)
		{
			return _mm256_loadu_si256((__m256i const *)_pSource);
		}

		static inline_always CInt fs_IntLoadAligned(int32 const *_pSource)
		{
			return _mm256_load_si256((__m256i const *)_pSource);
		}

		static inline_always void fs_IntStore(int32 *o_pDestination, CInt _Value)
		{
			_mm256_storeu_si256((__m256i *)o_pDestination, _Value);
		}

		static inline_always void fs_IntStoreAligned(int32 *o_pDestination, CInt _Value)
		{
			_mm256_store_si256((__m256i *)o_pDestination, _Value);
		}

		static inline_always int32 fs_IntGetLane(CInt _Value, umint _iLane)
		{
			int32 Lanes[8];
			fs_IntStore(Lanes, _Value);

			return Lanes[_iLane];
		}

		static inline_always CInt fs_IntSetLane(CInt _Value, umint _iLane, int32 _LaneValue)
		{
			int32 Lanes[8];
			fs_IntStore(Lanes, _Value);
			Lanes[_iLane] = _LaneValue;

			return fs_IntLoad(Lanes);
		}

		static inline_always CInt fs_IntAdd(CInt _Left, CInt _Right)
		{
			return _mm256_add_epi32(_Left, _Right);
		}

		static inline_always CInt fs_IntSub(CInt _Left, CInt _Right)
		{
			return _mm256_sub_epi32(_Left, _Right);
		}

		static inline_always CInt fs_IntMul(CInt _Left, CInt _Right)
		{
			return _mm256_mullo_epi32(_Left, _Right);
		}

		static inline_always CInt fs_IntMin(CInt _Left, CInt _Right)
		{
			return _mm256_min_epi32(_Left, _Right);
		}

		static inline_always CInt fs_IntMax(CInt _Left, CInt _Right)
		{
			return _mm256_max_epi32(_Left, _Right);
		}

		static inline_always CInt fs_IntNeg(CInt _Value)
		{
			return _mm256_sub_epi32(_mm256_setzero_si256(), _Value);
		}

		static inline_always CInt fs_IntAbs(CInt _Value)
		{
			return _mm256_abs_epi32(_Value);
		}

		static inline_always CInt fs_IntAnd(CInt _Left, CInt _Right)
		{
			return _mm256_and_si256(_Left, _Right);
		}

		static inline_always CInt fs_IntOr(CInt _Left, CInt _Right)
		{
			return _mm256_or_si256(_Left, _Right);
		}

		static inline_always CInt fs_IntXor(CInt _Left, CInt _Right)
		{
			return _mm256_xor_si256(_Left, _Right);
		}

		static inline_always CInt fs_IntNot(CInt _Value)
		{
			return _mm256_xor_si256(_Value, _mm256_set1_epi32(-1));
		}

		static inline_always CInt fs_IntShiftLeft(CInt _Value, uint32 _nBits)
		{
			return _mm256_sll_epi32(_Value, _mm_cvtsi32_si128(int32(_nBits)));
		}

		static inline_always CInt fs_IntShiftRight(CInt _Value, uint32 _nBits)
		{
			return _mm256_sra_epi32(_Value, _mm_cvtsi32_si128(int32(_nBits)));
		}

		static inline_always CInt fs_IntShiftRightLogical(CInt _Value, uint32 _nBits)
		{
			return _mm256_srl_epi32(_Value, _mm_cvtsi32_si128(int32(_nBits)));
		}

		static inline_always CMask fs_IntEqual(CInt _Left, CInt _Right)
		{
			return _mm256_cmpeq_epi32(_Left, _Right);
		}

		static inline_always CMask fs_IntLess(CInt _Left, CInt _Right)
		{
			return _mm256_cmpgt_epi32(_Right, _Left);
		}

		static inline_always CInt fs_IntSelect(CMask _Mask, CInt _True, CInt _False)
		{
			return _mm256_blendv_epi8(_False, _True, _Mask);
		}

		// Mask

		static inline_always CMask fs_MaskFalse()
		{
			return _mm256_setzero_si256();
		}

		static inline_always CMask fs_MaskTrue()
		{
			return _mm256_set1_epi32(-1);
		}

		static inline_always CMask fs_MaskAnd(CMask _Left, CMask _Right)
		{
			return _mm256_and_si256(_Left, _Right);
		}

		static inline_always CMask fs_MaskOr(CMask _Left, CMask _Right)
		{
			return _mm256_or_si256(_Left, _Right);
		}

		static inline_always CMask fs_MaskXor(CMask _Left, CMask _Right)
		{
			return _mm256_xor_si256(_Left, _Right);
		}

		static inline_always CMask fs_MaskNot(CMask _Value)
		{
			return _mm256_xor_si256(_Value, _mm256_set1_epi32(-1));
		}

		static inline_always uint32 fs_MaskBits(CMask _Value)
		{
			return uint32(_mm256_movemask_ps(_mm256_castsi256_ps(_Value)));
		}

		static inline_always CInt fs_MaskToInt(CMask _Value)
		{
			return _Value;
		}
	};
}
