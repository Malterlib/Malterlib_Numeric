// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#include <arm_neon.h>

namespace NMib::NNumeric::NPrivate
{
	struct CSimdBackend_NEON4
	{
		static constexpr umint mc_nLanes = 4;

		using CFloat = float32x4_t;
		using CInt = int32x4_t;
		using CMask = uint32x4_t;

		// Float

		static inline_always CFloat fs_FloatZero()
		{
			return vdupq_n_f32(0.0f);
		}

		static inline_always CFloat fs_FloatSplat(pfp32 _Value)
		{
			return vdupq_n_f32(_Value);
		}

		static inline_always CFloat fs_FloatLoad(pfp32 const *_pSource)
		{
			return vld1q_f32(_pSource);
		}

		static inline_always CFloat fs_FloatLoadAligned(pfp32 const *_pSource)
		{
			return vld1q_f32(_pSource);
		}

		static inline_always void fs_FloatStore(pfp32 *o_pDestination, CFloat _Value)
		{
			vst1q_f32(o_pDestination, _Value);
		}

		static inline_always void fs_FloatStoreAligned(pfp32 *o_pDestination, CFloat _Value)
		{
			vst1q_f32(o_pDestination, _Value);
		}

		static inline_always pfp32 fs_FloatGetLane(CFloat _Value, umint _iLane)
		{
			pfp32 Lanes[4];
			vst1q_f32(Lanes, _Value);

			return Lanes[_iLane];
		}

		static inline_always CFloat fs_FloatSetLane(CFloat _Value, umint _iLane, pfp32 _LaneValue)
		{
			pfp32 Lanes[4];
			vst1q_f32(Lanes, _Value);
			Lanes[_iLane] = _LaneValue;

			return vld1q_f32(Lanes);
		}

		static inline_always CFloat fs_FloatAdd(CFloat _Left, CFloat _Right)
		{
			return vaddq_f32(_Left, _Right);
		}

		static inline_always CFloat fs_FloatSub(CFloat _Left, CFloat _Right)
		{
			return vsubq_f32(_Left, _Right);
		}

		static inline_always CFloat fs_FloatMul(CFloat _Left, CFloat _Right)
		{
			return vmulq_f32(_Left, _Right);
		}

		static inline_always CFloat fs_FloatDiv(CFloat _Left, CFloat _Right)
		{
			return vdivq_f32(_Left, _Right);
		}

		// vminq_f32 and vmaxq_f32 propagate NaN from either operand
		static inline_always CFloat fs_FloatMin(CFloat _Left, CFloat _Right)
		{
			return vbslq_f32(vcltq_f32(_Left, _Right), _Left, _Right);
		}

		static inline_always CFloat fs_FloatMax(CFloat _Left, CFloat _Right)
		{
			return vbslq_f32(vcgtq_f32(_Left, _Right), _Left, _Right);
		}

		static inline_always CFloat fs_FloatNeg(CFloat _Value)
		{
			return vnegq_f32(_Value);
		}

		static inline_always CFloat fs_FloatAbs(CFloat _Value)
		{
			return vabsq_f32(_Value);
		}

		static inline_always CFloat fs_FloatSqrt(CFloat _Value)
		{
			return vsqrtq_f32(_Value);
		}

		static inline_always CFloat fs_FloatFloor(CFloat _Value)
		{
			return vrndmq_f32(_Value);
		}

		static inline_always CFloat fs_FloatCeil(CFloat _Value)
		{
			return vrndpq_f32(_Value);
		}

		static inline_always CMask fs_FloatEqual(CFloat _Left, CFloat _Right)
		{
			return vceqq_f32(_Left, _Right);
		}

		static inline_always CMask fs_FloatLess(CFloat _Left, CFloat _Right)
		{
			return vcltq_f32(_Left, _Right);
		}

		static inline_always CMask fs_FloatLessEqual(CFloat _Left, CFloat _Right)
		{
			return vcleq_f32(_Left, _Right);
		}

		static inline_always CFloat fs_FloatSelect(CMask _Mask, CFloat _True, CFloat _False)
		{
			return vbslq_f32(_Mask, _True, _False);
		}

		static inline_always pfp32 fs_FloatSum(CFloat _Value)
		{
			return vpadds_f32(vget_low_f32(vpaddq_f32(_Value, _Value)));
		}

		static inline_always CInt fs_FloatToInt(CFloat _Value)
		{
			return vcvtq_s32_f32(_Value);
		}

		static inline_always CFloat fs_FloatFromInt(CInt _Value)
		{
			return vcvtq_f32_s32(_Value);
		}

		static inline_always CInt fs_FloatBitsToInt(CFloat _Value)
		{
			return vreinterpretq_s32_f32(_Value);
		}

		static inline_always CFloat fs_FloatBitsFromInt(CInt _Value)
		{
			return vreinterpretq_f32_s32(_Value);
		}

		template <umint t_iLane0, umint t_iLane1, umint t_iLane2, umint t_iLane3>
		static inline_always CFloat fs_FloatShuffle(CFloat _Value)
		{
			return __builtin_shufflevector(_Value, _Value, int(t_iLane0), int(t_iLane1), int(t_iLane2), int(t_iLane3));
		}

		// Int

		static inline_always CInt fs_IntZero()
		{
			return vdupq_n_s32(0);
		}

		static inline_always CInt fs_IntSplat(int32 _Value)
		{
			return vdupq_n_s32(_Value);
		}

		// int32 is not the type of the lanes on all platforms, so the lanes are loaded and stored as bytes
		static inline_always CInt fs_IntLoad(int32 const *_pSource)
		{
			return vreinterpretq_s32_u8(vld1q_u8(reinterpret_cast<uint8_t const *>(_pSource)));
		}

		static inline_always CInt fs_IntLoadAligned(int32 const *_pSource)
		{
			return vreinterpretq_s32_u8(vld1q_u8(reinterpret_cast<uint8_t const *>(_pSource)));
		}

		static inline_always void fs_IntStore(int32 *o_pDestination, CInt _Value)
		{
			vst1q_u8(reinterpret_cast<uint8_t *>(o_pDestination), vreinterpretq_u8_s32(_Value));
		}

		static inline_always void fs_IntStoreAligned(int32 *o_pDestination, CInt _Value)
		{
			vst1q_u8(reinterpret_cast<uint8_t *>(o_pDestination), vreinterpretq_u8_s32(_Value));
		}

		static inline_always int32 fs_IntGetLane(CInt _Value, umint _iLane)
		{
			int32_t Lanes[4];
			vst1q_s32(Lanes, _Value);

			return Lanes[_iLane];
		}

		static inline_always CInt fs_IntSetLane(CInt _Value, umint _iLane, int32 _LaneValue)
		{
			int32_t Lanes[4];
			vst1q_s32(Lanes, _Value);
			Lanes[_iLane] = _LaneValue;

			return vld1q_s32(Lanes);
		}

		static inline_always CInt fs_IntAdd(CInt _Left, CInt _Right)
		{
			return vaddq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntSub(CInt _Left, CInt _Right)
		{
			return vsubq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntMul(CInt _Left, CInt _Right)
		{
			return vmulq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntMin(CInt _Left, CInt _Right)
		{
			return vminq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntMax(CInt _Left, CInt _Right)
		{
			return vmaxq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntNeg(CInt _Value)
		{
			return vnegq_s32(_Value);
		}

		static inline_always CInt fs_IntAbs(CInt _Value)
		{
			return vabsq_s32(_Value);
		}

		static inline_always CInt fs_IntAnd(CInt _Left, CInt _Right)
		{
			return vandq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntOr(CInt _Left, CInt _Right)
		{
			return vorrq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntXor(CInt _Left, CInt _Right)
		{
			return veorq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntNot(CInt _Value)
		{
			return vmvnq_s32(_Value);
		}

		static inline_always CInt fs_IntShiftLeft(CInt _Value, uint32 _nBits)
		{
			return vshlq_s32(_Value, vdupq_n_s32(int32(_nBits)));
		}

		static inline_always CInt fs_IntShiftRight(CInt _Value, uint32 _nBits)
		{
			return vshlq_s32(_Value, vdupq_n_s32(-int32(_nBits)));
		}

		static inline_always CInt fs_IntShiftRightLogical(CInt _Value, uint32 _nBits)
		{
			return vreinterpretq_s32_u32(vshlq_u32(vreinterpretq_u32_s32(_Value), vdupq_n_s32(-int32(_nBits))));
		}

		static inline_always CMask fs_IntEqual(CInt _Left, CInt _Right)
		{
			return vceqq_s32(_Left, _Right);
		}

		static inline_always CMask fs_IntLess(CInt _Left, CInt _Right)
		{
			return vcltq_s32(_Left, _Right);
		}

		static inline_always CInt fs_IntSelect(CMask _Mask, CInt _True, CInt _False)
		{
			return vbslq_s32(_Mask, _True, _False);
		}

		template <umint t_iLane0, umint t_iLane1, umint t_iLane2, umint t_iLane3>
		static inline_always CInt fs_IntShuffle(CInt _Value)
		{
			return __builtin_shufflevector(_Value, _Value, int(t_iLane0), int(t_iLane1), int(t_iLane2), int(t_iLane3));
		}

		// Mask

		static inline_always CMask fs_MaskFalse()
		{
			return vdupq_n_u32(0);
		}

		static inline_always CMask fs_MaskTrue()
		{
			return vdupq_n_u32(~uint32(0));
		}

		static inline_always CMask fs_MaskAnd(CMask _Left, CMask _Right)
		{
			return vandq_u32(_Left, _Right);
		}

		static inline_always CMask fs_MaskOr(CMask _Left, CMask _Right)
		{
			return vorrq_u32(_Left, _Right);
		}

		static inline_always CMask fs_MaskXor(CMask _Left, CMask _Right)
		{
			return veorq_u32(_Left, _Right);
		}

		static inline_always CMask fs_MaskNot(CMask _Value)
		{
			return vmvnq_u32(_Value);
		}

		static inline_always uint32 fs_MaskBits(CMask _Value)
		{
			static constexpr int32_t c_Shifts[4] = {0, 1, 2, 3};

			return vaddvq_u32(vshlq_u32(vshrq_n_u32(_Value, 31), vld1q_s32(c_Shifts)));
		}

		static inline_always CInt fs_MaskToInt(CMask _Value)
		{
			return vreinterpretq_s32_u32(_Value);
		}
	};
}
