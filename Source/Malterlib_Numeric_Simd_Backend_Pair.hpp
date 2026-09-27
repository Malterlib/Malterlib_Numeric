// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

namespace NMib::NNumeric::NPrivate
{
	// Doubles the lane count of a backend by operating on two of its vectors.
	template <typename t_CHalf>
	struct TCSimdBackend_Pair
	{
		static constexpr umint mc_nHalfLanes = t_CHalf::mc_nLanes;
		static constexpr umint mc_nLanes = mc_nHalfLanes * 2;

		struct CFloat
		{
			typename t_CHalf::CFloat m_Low;
			typename t_CHalf::CFloat m_High;
		};

		struct CInt
		{
			typename t_CHalf::CInt m_Low;
			typename t_CHalf::CInt m_High;
		};

		struct CMask
		{
			typename t_CHalf::CMask m_Low;
			typename t_CHalf::CMask m_High;
		};

		// Float

		static inline_always CFloat fs_FloatZero()
		{
			return {t_CHalf::fs_FloatZero(), t_CHalf::fs_FloatZero()};
		}

		static inline_always CFloat fs_FloatSplat(pfp32 _Value)
		{
			return {t_CHalf::fs_FloatSplat(_Value), t_CHalf::fs_FloatSplat(_Value)};
		}

		static inline_always CFloat fs_FloatLoad(pfp32 const *_pSource)
		{
			return {t_CHalf::fs_FloatLoad(_pSource), t_CHalf::fs_FloatLoad(_pSource + mc_nHalfLanes)};
		}

		static inline_always CFloat fs_FloatLoadAligned(pfp32 const *_pSource)
		{
			return {t_CHalf::fs_FloatLoadAligned(_pSource), t_CHalf::fs_FloatLoadAligned(_pSource + mc_nHalfLanes)};
		}

		static inline_always void fs_FloatStore(pfp32 *o_pDestination, CFloat const &_Value)
		{
			t_CHalf::fs_FloatStore(o_pDestination, _Value.m_Low);
			t_CHalf::fs_FloatStore(o_pDestination + mc_nHalfLanes, _Value.m_High);
		}

		static inline_always void fs_FloatStoreAligned(pfp32 *o_pDestination, CFloat const &_Value)
		{
			t_CHalf::fs_FloatStoreAligned(o_pDestination, _Value.m_Low);
			t_CHalf::fs_FloatStoreAligned(o_pDestination + mc_nHalfLanes, _Value.m_High);
		}

		static inline_always pfp32 fs_FloatGetLane(CFloat const &_Value, umint _iLane)
		{
			if (_iLane < mc_nHalfLanes)
				return t_CHalf::fs_FloatGetLane(_Value.m_Low, _iLane);

			return t_CHalf::fs_FloatGetLane(_Value.m_High, _iLane - mc_nHalfLanes);
		}

		static inline_always CFloat fs_FloatSetLane(CFloat const &_Value, umint _iLane, pfp32 _LaneValue)
		{
			if (_iLane < mc_nHalfLanes)
				return {t_CHalf::fs_FloatSetLane(_Value.m_Low, _iLane, _LaneValue), _Value.m_High};

			return {_Value.m_Low, t_CHalf::fs_FloatSetLane(_Value.m_High, _iLane - mc_nHalfLanes, _LaneValue)};
		}

		static inline_always CFloat fs_FloatAdd(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatAdd(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatAdd(_Left.m_High, _Right.m_High)};
		}

		static inline_always CFloat fs_FloatSub(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatSub(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatSub(_Left.m_High, _Right.m_High)};
		}

		static inline_always CFloat fs_FloatMul(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatMul(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatMul(_Left.m_High, _Right.m_High)};
		}

		static inline_always CFloat fs_FloatDiv(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatDiv(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatDiv(_Left.m_High, _Right.m_High)};
		}

		static inline_always CFloat fs_FloatMin(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatMin(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatMin(_Left.m_High, _Right.m_High)};
		}

		static inline_always CFloat fs_FloatMax(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatMax(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatMax(_Left.m_High, _Right.m_High)};
		}

		static inline_always CFloat fs_FloatNeg(CFloat const &_Value)
		{
			return {t_CHalf::fs_FloatNeg(_Value.m_Low), t_CHalf::fs_FloatNeg(_Value.m_High)};
		}

		static inline_always CFloat fs_FloatAbs(CFloat const &_Value)
		{
			return {t_CHalf::fs_FloatAbs(_Value.m_Low), t_CHalf::fs_FloatAbs(_Value.m_High)};
		}

		static inline_always CFloat fs_FloatSqrt(CFloat const &_Value)
		{
			return {t_CHalf::fs_FloatSqrt(_Value.m_Low), t_CHalf::fs_FloatSqrt(_Value.m_High)};
		}

		static inline_always CFloat fs_FloatFloor(CFloat const &_Value)
		{
			return {t_CHalf::fs_FloatFloor(_Value.m_Low), t_CHalf::fs_FloatFloor(_Value.m_High)};
		}

		static inline_always CFloat fs_FloatCeil(CFloat const &_Value)
		{
			return {t_CHalf::fs_FloatCeil(_Value.m_Low), t_CHalf::fs_FloatCeil(_Value.m_High)};
		}

		static inline_always CMask fs_FloatEqual(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatEqual(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatEqual(_Left.m_High, _Right.m_High)};
		}

		static inline_always CMask fs_FloatLess(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatLess(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatLess(_Left.m_High, _Right.m_High)};
		}

		static inline_always CMask fs_FloatLessEqual(CFloat const &_Left, CFloat const &_Right)
		{
			return {t_CHalf::fs_FloatLessEqual(_Left.m_Low, _Right.m_Low), t_CHalf::fs_FloatLessEqual(_Left.m_High, _Right.m_High)};
		}

		static inline_always CFloat fs_FloatSelect(CMask const &_Mask, CFloat const &_True, CFloat const &_False)
		{
			return {t_CHalf::fs_FloatSelect(_Mask.m_Low, _True.m_Low, _False.m_Low), t_CHalf::fs_FloatSelect(_Mask.m_High, _True.m_High, _False.m_High)};
		}

		static inline_always pfp32 fs_FloatSum(CFloat const &_Value)
		{
			return t_CHalf::fs_FloatSum(_Value.m_Low) + t_CHalf::fs_FloatSum(_Value.m_High);
		}

		static inline_always CInt fs_FloatToInt(CFloat const &_Value)
		{
			return {t_CHalf::fs_FloatToInt(_Value.m_Low), t_CHalf::fs_FloatToInt(_Value.m_High)};
		}

		static inline_always CFloat fs_FloatFromInt(CInt const &_Value)
		{
			return {t_CHalf::fs_FloatFromInt(_Value.m_Low), t_CHalf::fs_FloatFromInt(_Value.m_High)};
		}

		static inline_always CInt fs_FloatBitsToInt(CFloat const &_Value)
		{
			return {t_CHalf::fs_FloatBitsToInt(_Value.m_Low), t_CHalf::fs_FloatBitsToInt(_Value.m_High)};
		}

		static inline_always CFloat fs_FloatBitsFromInt(CInt const &_Value)
		{
			return {t_CHalf::fs_FloatBitsFromInt(_Value.m_Low), t_CHalf::fs_FloatBitsFromInt(_Value.m_High)};
		}

		// Int

		static inline_always CInt fs_IntZero()
		{
			return {t_CHalf::fs_IntZero(), t_CHalf::fs_IntZero()};
		}

		static inline_always CInt fs_IntSplat(int32 _Value)
		{
			return {t_CHalf::fs_IntSplat(_Value), t_CHalf::fs_IntSplat(_Value)};
		}

		static inline_always CInt fs_IntLoad(int32 const *_pSource)
		{
			return {t_CHalf::fs_IntLoad(_pSource), t_CHalf::fs_IntLoad(_pSource + mc_nHalfLanes)};
		}

		static inline_always CInt fs_IntLoadAligned(int32 const *_pSource)
		{
			return {t_CHalf::fs_IntLoadAligned(_pSource), t_CHalf::fs_IntLoadAligned(_pSource + mc_nHalfLanes)};
		}

		static inline_always void fs_IntStore(int32 *o_pDestination, CInt const &_Value)
		{
			t_CHalf::fs_IntStore(o_pDestination, _Value.m_Low);
			t_CHalf::fs_IntStore(o_pDestination + mc_nHalfLanes, _Value.m_High);
		}

		static inline_always void fs_IntStoreAligned(int32 *o_pDestination, CInt const &_Value)
		{
			t_CHalf::fs_IntStoreAligned(o_pDestination, _Value.m_Low);
			t_CHalf::fs_IntStoreAligned(o_pDestination + mc_nHalfLanes, _Value.m_High);
		}

		static inline_always int32 fs_IntGetLane(CInt const &_Value, umint _iLane)
		{
			if (_iLane < mc_nHalfLanes)
				return t_CHalf::fs_IntGetLane(_Value.m_Low, _iLane);

			return t_CHalf::fs_IntGetLane(_Value.m_High, _iLane - mc_nHalfLanes);
		}

		static inline_always CInt fs_IntSetLane(CInt const &_Value, umint _iLane, int32 _LaneValue)
		{
			if (_iLane < mc_nHalfLanes)
				return {t_CHalf::fs_IntSetLane(_Value.m_Low, _iLane, _LaneValue), _Value.m_High};

			return {_Value.m_Low, t_CHalf::fs_IntSetLane(_Value.m_High, _iLane - mc_nHalfLanes, _LaneValue)};
		}

		static inline_always CInt fs_IntAdd(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntAdd(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntAdd(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntSub(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntSub(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntSub(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntMul(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntMul(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntMul(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntMin(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntMin(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntMin(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntMax(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntMax(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntMax(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntNeg(CInt const &_Value)
		{
			return {t_CHalf::fs_IntNeg(_Value.m_Low), t_CHalf::fs_IntNeg(_Value.m_High)};
		}

		static inline_always CInt fs_IntAbs(CInt const &_Value)
		{
			return {t_CHalf::fs_IntAbs(_Value.m_Low), t_CHalf::fs_IntAbs(_Value.m_High)};
		}

		static inline_always CInt fs_IntAnd(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntAnd(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntAnd(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntOr(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntOr(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntOr(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntXor(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntXor(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntXor(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntNot(CInt const &_Value)
		{
			return {t_CHalf::fs_IntNot(_Value.m_Low), t_CHalf::fs_IntNot(_Value.m_High)};
		}

		static inline_always CInt fs_IntShiftLeft(CInt const &_Value, uint32 _nBits)
		{
			return {t_CHalf::fs_IntShiftLeft(_Value.m_Low, _nBits), t_CHalf::fs_IntShiftLeft(_Value.m_High, _nBits)};
		}

		static inline_always CInt fs_IntShiftRight(CInt const &_Value, uint32 _nBits)
		{
			return {t_CHalf::fs_IntShiftRight(_Value.m_Low, _nBits), t_CHalf::fs_IntShiftRight(_Value.m_High, _nBits)};
		}

		static inline_always CInt fs_IntShiftRightLogical(CInt const &_Value, uint32 _nBits)
		{
			return {t_CHalf::fs_IntShiftRightLogical(_Value.m_Low, _nBits), t_CHalf::fs_IntShiftRightLogical(_Value.m_High, _nBits)};
		}

		static inline_always CMask fs_IntEqual(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntEqual(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntEqual(_Left.m_High, _Right.m_High)};
		}

		static inline_always CMask fs_IntLess(CInt const &_Left, CInt const &_Right)
		{
			return {t_CHalf::fs_IntLess(_Left.m_Low, _Right.m_Low), t_CHalf::fs_IntLess(_Left.m_High, _Right.m_High)};
		}

		static inline_always CInt fs_IntSelect(CMask const &_Mask, CInt const &_True, CInt const &_False)
		{
			return {t_CHalf::fs_IntSelect(_Mask.m_Low, _True.m_Low, _False.m_Low), t_CHalf::fs_IntSelect(_Mask.m_High, _True.m_High, _False.m_High)};
		}

		// Mask

		static inline_always CMask fs_MaskFalse()
		{
			return {t_CHalf::fs_MaskFalse(), t_CHalf::fs_MaskFalse()};
		}

		static inline_always CMask fs_MaskTrue()
		{
			return {t_CHalf::fs_MaskTrue(), t_CHalf::fs_MaskTrue()};
		}

		static inline_always CMask fs_MaskAnd(CMask const &_Left, CMask const &_Right)
		{
			return {t_CHalf::fs_MaskAnd(_Left.m_Low, _Right.m_Low), t_CHalf::fs_MaskAnd(_Left.m_High, _Right.m_High)};
		}

		static inline_always CMask fs_MaskOr(CMask const &_Left, CMask const &_Right)
		{
			return {t_CHalf::fs_MaskOr(_Left.m_Low, _Right.m_Low), t_CHalf::fs_MaskOr(_Left.m_High, _Right.m_High)};
		}

		static inline_always CMask fs_MaskXor(CMask const &_Left, CMask const &_Right)
		{
			return {t_CHalf::fs_MaskXor(_Left.m_Low, _Right.m_Low), t_CHalf::fs_MaskXor(_Left.m_High, _Right.m_High)};
		}

		static inline_always CMask fs_MaskNot(CMask const &_Value)
		{
			return {t_CHalf::fs_MaskNot(_Value.m_Low), t_CHalf::fs_MaskNot(_Value.m_High)};
		}

		static inline_always uint32 fs_MaskBits(CMask const &_Value)
		{
			return t_CHalf::fs_MaskBits(_Value.m_Low) | (t_CHalf::fs_MaskBits(_Value.m_High) << mc_nHalfLanes);
		}

		static inline_always CInt fs_MaskToInt(CMask const &_Value)
		{
			return {t_CHalf::fs_MaskToInt(_Value.m_Low), t_CHalf::fs_MaskToInt(_Value.m_High)};
		}
	};
}
