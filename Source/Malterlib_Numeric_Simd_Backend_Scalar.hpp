// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric::NPrivate
{
	// Defines the semantics every other backend must reproduce bit for bit.
	template <umint t_nLanes>
	struct TCSimdBackend_Scalar
	{
		static_assert(t_nLanes >= 1 && t_nLanes <= 32, "The bits of a mask have one bit for each lane in 32 bits");

		static constexpr umint mc_nLanes = t_nLanes;

		struct CFloat
		{
			pfp32 m_Lanes[t_nLanes];
		};

		struct CInt
		{
			int32 m_Lanes[t_nLanes];
		};

		struct CMask
		{
			uint32 m_Lanes[t_nLanes]; // All bits set or all bits clear
		};

		static constexpr uint32 mc_SignBit = 0x80000000u;

		// Float

		static inline_always CFloat fs_FloatZero()
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = 0.0f;

			return Result;
		}

		static inline_always CFloat fs_FloatSplat(pfp32 _Value)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Value;

			return Result;
		}

		static inline_always CFloat fs_FloatLoad(pfp32 const *_pSource)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _pSource[i];

			return Result;
		}

		static inline_always CFloat fs_FloatLoadAligned(pfp32 const *_pSource)
		{
			return fs_FloatLoad(_pSource);
		}

		static inline_always void fs_FloatStore(pfp32 *o_pDestination, CFloat const &_Value)
		{
			for (umint i = 0; i < t_nLanes; ++i)
				o_pDestination[i] = _Value.m_Lanes[i];
		}

		static inline_always void fs_FloatStoreAligned(pfp32 *o_pDestination, CFloat const &_Value)
		{
			fs_FloatStore(o_pDestination, _Value);
		}

		static inline_always pfp32 fs_FloatGetLane(CFloat const &_Value, umint _iLane)
		{
			return _Value.m_Lanes[_iLane];
		}

		static inline_always CFloat fs_FloatSetLane(CFloat const &_Value, umint _iLane, pfp32 _LaneValue)
		{
			CFloat Result = _Value;
			Result.m_Lanes[_iLane] = _LaneValue;

			return Result;
		}

		static inline_always CFloat fs_FloatAdd(CFloat const &_Left, CFloat const &_Right)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] + _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CFloat fs_FloatSub(CFloat const &_Left, CFloat const &_Right)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] - _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CFloat fs_FloatMul(CFloat const &_Left, CFloat const &_Right)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] * _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CFloat fs_FloatDiv(CFloat const &_Left, CFloat const &_Right)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] / _Right.m_Lanes[i];

			return Result;
		}

		// The right operand is returned when either operand is NaN
		static inline_always CFloat fs_FloatMin(CFloat const &_Left, CFloat const &_Right)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] < _Right.m_Lanes[i] ? _Left.m_Lanes[i] : _Right.m_Lanes[i];

			return Result;
		}

		// The right operand is returned when either operand is NaN
		static inline_always CFloat fs_FloatMax(CFloat const &_Left, CFloat const &_Right)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] > _Right.m_Lanes[i] ? _Left.m_Lanes[i] : _Right.m_Lanes[i];

			return Result;
		}

		static inline_always uint32 fs_ToBits(pfp32 _Value)
		{
			return __builtin_bit_cast(uint32, _Value);
		}

		static inline_always pfp32 fs_FromBits(uint32 _Value)
		{
			return __builtin_bit_cast(pfp32, _Value);
		}

		static inline_always CFloat fs_FloatNeg(CFloat const &_Value)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = fs_FromBits(fs_ToBits(_Value.m_Lanes[i]) ^ mc_SignBit);

			return Result;
		}

		static inline_always CFloat fs_FloatAbs(CFloat const &_Value)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = fs_FromBits(fs_ToBits(_Value.m_Lanes[i]) & ~mc_SignBit);

			return Result;
		}

		static inline_always CFloat fs_FloatSqrt(CFloat const &_Value)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = __builtin_sqrtf(_Value.m_Lanes[i]);

			return Result;
		}

		static inline_always CFloat fs_FloatFloor(CFloat const &_Value)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = __builtin_floorf(_Value.m_Lanes[i]);

			return Result;
		}

		static inline_always CFloat fs_FloatCeil(CFloat const &_Value)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = __builtin_ceilf(_Value.m_Lanes[i]);

			return Result;
		}

		static inline_always CMask fs_FloatEqual(CFloat const &_Left, CFloat const &_Right)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] == _Right.m_Lanes[i] ? ~uint32(0) : uint32(0);

			return Result;
		}

		static inline_always CMask fs_FloatLess(CFloat const &_Left, CFloat const &_Right)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] < _Right.m_Lanes[i] ? ~uint32(0) : uint32(0);

			return Result;
		}

		static inline_always CMask fs_FloatLessEqual(CFloat const &_Left, CFloat const &_Right)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] <= _Right.m_Lanes[i] ? ~uint32(0) : uint32(0);

			return Result;
		}

		static inline_always CFloat fs_FloatSelect(CMask const &_Mask, CFloat const &_True, CFloat const &_False)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Mask.m_Lanes[i] ? _True.m_Lanes[i] : _False.m_Lanes[i];

			return Result;
		}

		// Adds adjacent pairs first, then pairs of pairs
		static inline_always pfp32 fs_FloatSum(CFloat const &_Value)
		{
			pfp32 Sums[t_nLanes];
			for (umint i = 0; i < t_nLanes; ++i)
				Sums[i] = _Value.m_Lanes[i];

			for (umint nLanes = t_nLanes; nLanes > 1; nLanes = (nLanes + 1) / 2)
			{
				for (umint i = 0; i < nLanes / 2; ++i)
					Sums[i] = Sums[i * 2] + Sums[i * 2 + 1];

				if (nLanes & 1)
					Sums[nLanes / 2] = Sums[nLanes - 1];
			}

			return Sums[0];
		}

		// Truncates. The result is unspecified for NaN and for values outside the range of int32
		static inline_always CInt fs_FloatToInt(CFloat const &_Value)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(_Value.m_Lanes[i]);

			return Result;
		}

		static inline_always CFloat fs_FloatFromInt(CInt const &_Value)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = pfp32(_Value.m_Lanes[i]);

			return Result;
		}

		static inline_always CInt fs_FloatBitsToInt(CFloat const &_Value)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(fs_ToBits(_Value.m_Lanes[i]));

			return Result;
		}

		static inline_always CFloat fs_FloatBitsFromInt(CInt const &_Value)
		{
			CFloat Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = fs_FromBits(uint32(_Value.m_Lanes[i]));

			return Result;
		}

		template <umint ...tfp_iLanes>
		static inline_always CFloat fs_FloatShuffle(CFloat const &_Value)
		{
			return CFloat{{_Value.m_Lanes[tfp_iLanes]...}};
		}

		// Int

		static inline_always CInt fs_IntZero()
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = 0;

			return Result;
		}

		static inline_always CInt fs_IntSplat(int32 _Value)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Value;

			return Result;
		}

		static inline_always CInt fs_IntLoad(int32 const *_pSource)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _pSource[i];

			return Result;
		}

		static inline_always CInt fs_IntLoadAligned(int32 const *_pSource)
		{
			return fs_IntLoad(_pSource);
		}

		static inline_always void fs_IntStore(int32 *o_pDestination, CInt const &_Value)
		{
			for (umint i = 0; i < t_nLanes; ++i)
				o_pDestination[i] = _Value.m_Lanes[i];
		}

		static inline_always void fs_IntStoreAligned(int32 *o_pDestination, CInt const &_Value)
		{
			fs_IntStore(o_pDestination, _Value);
		}

		static inline_always int32 fs_IntGetLane(CInt const &_Value, umint _iLane)
		{
			return _Value.m_Lanes[_iLane];
		}

		static inline_always CInt fs_IntSetLane(CInt const &_Value, umint _iLane, int32 _LaneValue)
		{
			CInt Result = _Value;
			Result.m_Lanes[_iLane] = _LaneValue;

			return Result;
		}

		static inline_always CInt fs_IntAdd(CInt const &_Left, CInt const &_Right)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(uint32(_Left.m_Lanes[i]) + uint32(_Right.m_Lanes[i]));

			return Result;
		}

		static inline_always CInt fs_IntSub(CInt const &_Left, CInt const &_Right)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(uint32(_Left.m_Lanes[i]) - uint32(_Right.m_Lanes[i]));

			return Result;
		}

		static inline_always CInt fs_IntMul(CInt const &_Left, CInt const &_Right)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(uint32(_Left.m_Lanes[i]) * uint32(_Right.m_Lanes[i]));

			return Result;
		}

		static inline_always CInt fs_IntMin(CInt const &_Left, CInt const &_Right)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] < _Right.m_Lanes[i] ? _Left.m_Lanes[i] : _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CInt fs_IntMax(CInt const &_Left, CInt const &_Right)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] > _Right.m_Lanes[i] ? _Left.m_Lanes[i] : _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CInt fs_IntNeg(CInt const &_Value)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(uint32(0) - uint32(_Value.m_Lanes[i]));

			return Result;
		}

		// The most negative value is returned unchanged
		static inline_always CInt fs_IntAbs(CInt const &_Value)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Value.m_Lanes[i] < 0 ? int32(uint32(0) - uint32(_Value.m_Lanes[i])) : _Value.m_Lanes[i];

			return Result;
		}

		static inline_always CInt fs_IntAnd(CInt const &_Left, CInt const &_Right)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] & _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CInt fs_IntOr(CInt const &_Left, CInt const &_Right)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] | _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CInt fs_IntXor(CInt const &_Left, CInt const &_Right)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] ^ _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CInt fs_IntNot(CInt const &_Value)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = ~_Value.m_Lanes[i];

			return Result;
		}

		// Shift counts must be in the range 0 to 31
		static inline_always CInt fs_IntShiftLeft(CInt const &_Value, uint32 _nBits)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(uint32(_Value.m_Lanes[i]) << _nBits);

			return Result;
		}

		static inline_always CInt fs_IntShiftRight(CInt const &_Value, uint32 _nBits)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Value.m_Lanes[i] >> _nBits;

			return Result;
		}

		static inline_always CInt fs_IntShiftRightLogical(CInt const &_Value, uint32 _nBits)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(uint32(_Value.m_Lanes[i]) >> _nBits);

			return Result;
		}

		static inline_always CMask fs_IntEqual(CInt const &_Left, CInt const &_Right)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] == _Right.m_Lanes[i] ? ~uint32(0) : uint32(0);

			return Result;
		}

		static inline_always CMask fs_IntLess(CInt const &_Left, CInt const &_Right)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] < _Right.m_Lanes[i] ? ~uint32(0) : uint32(0);

			return Result;
		}

		static inline_always CInt fs_IntSelect(CMask const &_Mask, CInt const &_True, CInt const &_False)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Mask.m_Lanes[i] ? _True.m_Lanes[i] : _False.m_Lanes[i];

			return Result;
		}

		template <umint ...tfp_iLanes>
		static inline_always CInt fs_IntShuffle(CInt const &_Value)
		{
			return CInt{{_Value.m_Lanes[tfp_iLanes]...}};
		}

		// Mask

		static inline_always CMask fs_MaskFalse()
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = 0;

			return Result;
		}

		static inline_always CMask fs_MaskTrue()
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = ~uint32(0);

			return Result;
		}

		static inline_always CMask fs_MaskAnd(CMask const &_Left, CMask const &_Right)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] & _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CMask fs_MaskOr(CMask const &_Left, CMask const &_Right)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] | _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CMask fs_MaskXor(CMask const &_Left, CMask const &_Right)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = _Left.m_Lanes[i] ^ _Right.m_Lanes[i];

			return Result;
		}

		static inline_always CMask fs_MaskNot(CMask const &_Value)
		{
			CMask Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = ~_Value.m_Lanes[i];

			return Result;
		}

		// Lane 0 is the least significant bit
		static inline_always uint32 fs_MaskBits(CMask const &_Value)
		{
			uint32 Result = 0;
			for (umint i = 0; i < t_nLanes; ++i)
				Result |= (_Value.m_Lanes[i] >> 31) << i;

			return Result;
		}

		static inline_always CInt fs_MaskToInt(CMask const &_Value)
		{
			CInt Result;
			for (umint i = 0; i < t_nLanes; ++i)
				Result.m_Lanes[i] = int32(_Value.m_Lanes[i]);

			return Result;
		}
	};
}
