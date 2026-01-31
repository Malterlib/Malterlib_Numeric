// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib::NNumeric
{
	template <typename t_CType, mint t_nDim>
	class TCVecAggregate
	{
	public:
		using CType = t_CType;

		enum
		{
			ENumDim = t_nDim
		};
		CType m_Axis[ENumDim];
		inline_small const CType &operator [] (mint _iOpr) const
		{
			return m_Axis[_iOpr];
		}

		inline_small CType &operator [] (mint _iOpr)
		{
			return m_Axis[_iOpr];
		}

		template <typename t_CType1, mint t_nDim1>
		TCVecAggregate &operator = (const TCVecAggregate<t_CType1, t_nDim1> &_Src) const
		{
			mint nDimMin = fg_Min(ENumDim, _Src.ENumDim);
			for (mint i = 0; i < nDimMin; ++i)
			{
				(*this)[i] = _Src[i];
			}
			for (mint i = ENumDim; i < _Src.ENumDim; ++i)
			{
				(*this)[i] = 0;
			}

			return *this;
		}

	};

	template <typename t_CType, mint t_nDim>
	class TCVec : public TCVecAggregate<t_CType, t_nDim>
	{
	public:
		using CSuper = TCVecAggregate<t_CType, t_nDim>;
		using CType = typename CSuper::CType;

		TCVec()
		{
		}
		TCVec(CType _Value[t_nDim])
		{
			for (mint i = 0; i < t_nDim; ++i)
			{
				(*this)[i] = _Value[i];
			}
		}
		template <typename t_CType1, mint t_nDim1>
		TCVec(const TCVecAggregate<t_CType1, t_nDim1> &_Src)
		{
			mint nDimMin = fg_Min(CSuper::ENumDim, _Src.ENumDim);
			for (mint i = 0; i < nDimMin; ++i)
			{
				(*this)[i] = _Src[i];
			}
			for (mint i = CSuper::ENumDim; i <TCVecAggregate<t_CType1, t_nDim1>::ENumDim; ++i)
			{
				(*this)[i] = 0;
			}
		}

		TCVec(const TCVecAggregate<t_CType, t_nDim> &_Src)
		{
			*((TCVecAggregate<t_CType, t_nDim> *) this) = _Src;
		}
	};

	template <typename t_CType>
	class TCVec<t_CType, 2> : public TCVecAggregate<t_CType, 2>
	{
	public:
		using CSuper = TCVecAggregate<t_CType, 2>;
		using CType = typename CSuper::CType;

		enum
		{
			ENumDim = CSuper::ENumDim
		};

		TCVec()
		{
		}
		TCVec(CType _Value[ENumDim])
		{
			(*this)[0] = _Value[0];
			(*this)[1] = _Value[1];
		}
		TCVec(CType _Value0)
		{
			(*this)[0] = _Value0;
			(*this)[1] = _Value0;
		}
		TCVec(CType _Value0, CType _Value1)
		{
			(*this)[0] = _Value0;
			(*this)[1] = _Value1;
		}
		template <typename t_CType1, mint t_nDim1>
		TCVec(const TCVecAggregate<t_CType1, t_nDim1> &_Src)
		{
			mint nDimMin = fg_Min(ENumDim, _Src.ENumDim);
			for (mint i = 0; i < nDimMin; ++i)
			{
				(*this)[i] = _Src[i];
			}
			for (mint i = ENumDim; i < _Src.ENumDim; ++i)
			{
				(*this)[i] = 0;
			}
		}

		TCVec(const TCVecAggregate<t_CType, ENumDim> &_Src)
		{
			*((TCVecAggregate<t_CType, ENumDim> *) this) = _Src;
		}
	};

	template <typename t_CType>
	class TCVec<t_CType, 3> : public TCVecAggregate<t_CType, 3>
	{
	public:
		using CSuper = TCVecAggregate<t_CType, 3>;
		using CType = typename CSuper::CType;

		enum
		{
			ENumDim = CSuper::ENumDim
		};

		TCVec()
		{
		}
		TCVec(CType _Value[ENumDim])
		{
			(*this)[0] = _Value[0];
			(*this)[1] = _Value[1];
			(*this)[2] = _Value[2];
		}
		TCVec(CType _Value0)
		{
			(*this)[0] = _Value0;
			(*this)[1] = _Value0;
			(*this)[2] = _Value0;
		}
		TCVec(CType _Value0, CType _Value1, CType _Value2)
		{
			(*this)[0] = _Value0;
			(*this)[1] = _Value1;
			(*this)[2] = _Value2;
		}
		template <typename t_CType1, mint t_nDim1>
		TCVec(const TCVecAggregate<t_CType1, t_nDim1> &_Src)
		{
			mint nDimMin = fg_Min(ENumDim, _Src.ENumDim);
			for (mint i = 0; i < nDimMin; ++i)
			{
				(*this)[i] = _Src[i];
			}
			for (mint i = ENumDim; i < _Src.ENumDim; ++i)
			{
				(*this)[i] = 0;
			}
		}
		TCVec(const TCVecAggregate<t_CType, ENumDim> &_Src)
		{
			*((TCVecAggregate<t_CType, ENumDim> *) this) = _Src;
		}
	};

	template <typename t_CType>
	class TCVec<t_CType, 4> : public TCVecAggregate<t_CType, 4>
	{
	public:
		using CSuper = TCVecAggregate<t_CType, 4>;
		using CType = typename CSuper::CType;

		enum
		{
			ENumDim = CSuper::ENumDim
		};

		TCVec()
		{
		}
		TCVec(CType _Value[ENumDim])
		{
			(*this)[0] = _Value[0];
			(*this)[1] = _Value[1];
			(*this)[2] = _Value[2];
			(*this)[3] = _Value[3];
		}
		TCVec(CType _Value0)
		{
			(*this)[0] = _Value0;
			(*this)[1] = _Value0;
			(*this)[2] = _Value0;
			(*this)[4] = _Value0;
		}
		TCVec(CType _Value0, CType _Value1, CType _Value2, CType _Value3)
		{
			(*this) = TCVecAggregate<t_CType, 4>::fs_Init(_Value0, _Value1, _Value2, _Value3);
		}
		template <typename t_CType1, mint t_nDim1>
		TCVec(const TCVecAggregate<t_CType1, t_nDim1> &_Src)
		{
			mint nDimMin = fg_Min(ENumDim, _Src.ENumDim);
			for (mint i = 0; i < nDimMin; ++i)
			{
				(*this)[i] = _Src[i];
			}
			for (mint i = ENumDim; i < _Src.ENumDim; ++i)
			{
				(*this)[i] = 0;
			}
		}
		TCVec(const TCVecAggregate<t_CType, ENumDim> &_Src)
		{
			(*this)[0] = _Src[0];
			(*this)[1] = _Src[1];
			(*this)[2] = _Src[2];
			(*this)[3] = _Src[3];
		}
		TCVec(const TCVec &_Src)
		{
			(*this)[0] = _Src[0];
			(*this)[1] = _Src[1];
			(*this)[2] = _Src[2];
			(*this)[3] = _Src[3];
		}
	};

	using CVec2Dint32 = TCVec<int32, 2>;
	using CVec3Dint32 = TCVec<int32, 3>;
	using CVec4Dint32 = TCVec<int32, 4>;

	using CVec2Duint32 = TCVec<int32, 2>;
	using CVec3Duint32 = TCVec<int32, 3>;
	using CVec4Duint32 = TCVec<int32, 4>;

	using CVec2Dfp32 = TCVec<fp32, 2>;
	using CVec3Dfp32 = TCVec<fp32, 3>;
	using CVec4Dfp32 = TCVec<fp32, 4>;

	using CVecAggr2Dint32 = TCVecAggregate<int32, 2>;
	using CVecAggr3Dint32 = TCVecAggregate<int32, 3>;
	using CVecAggr4Dint32 = TCVecAggregate<int32, 4>;

	using CVecAggr2Duint32 = TCVecAggregate<int32, 2>;
	using CVecAggr3Duint32 = TCVecAggregate<int32, 3>;
	using CVecAggr4Duint32 = TCVecAggregate<int32, 4>;

	using CVecAggr2Dfp32 = TCVecAggregate<fp32, 2>;
	using CVecAggr3Dfp32 = TCVecAggregate<fp32, 3>;
	using CVecAggr4Dfp32 = TCVecAggregate<fp32, 4>;

	template <typename t_CType, mint t_nDimX>
	class TCMatrixAggregate
	{
	public:
		using CVec = t_CType;

		enum
		{
			ENumDimY = t_CType::ENumDim,
			ENumDimX = t_nDimX
		};
		CVec m_Columns[ENumDimX];

		inline_small const CVec &operator [] (mint _iOpr) const
		{
			return m_Columns[_iOpr];
		}

		inline_small CVec &operator [] (mint _iOpr)
		{
			return m_Columns[_iOpr];
		}


		template <typename t_CType0, mint t_nDimX0, typename t_CType1, mint t_nDimX1>
		static void fs_Multiply(TCMatrixAggregate<t_CType, t_nDimX> &_Dest, const TCMatrixAggregate<t_CType0, t_nDimX0> &_Src0, const TCMatrixAggregate<t_CType1, t_nDimX1> &_Src1)
		{
			enum
			{
				EDimX0 = TCMatrixAggregate<t_CType0, t_nDimX0>::ENumDimX,
				EDimY0 = TCMatrixAggregate<t_CType0, t_nDimX0>::ENumDimY,
				EDimX1 = TCMatrixAggregate<t_CType1, t_nDimX1>::ENumDimX,
				EDimY1 = TCMatrixAggregate<t_CType1, t_nDimX1>::ENumDimY,
				EMaxX = EDimX0 > EDimX1 ? (EDimX0 > ENumDimX ? EDimX0 : ENumDimX) : (EDimX1 > ENumDimX ? EDimX1 : ENumDimX),
				EMaxY = EDimY0 > EDimY1 ? (EDimY0 > ENumDimY ? EDimY0 : ENumDimY) : (EDimY1 > ENumDimY ? EDimY1 : ENumDimY),
				EMinX = EDimX0 < EDimX1 ? (EDimX0 < ENumDimX ? EDimX0 : ENumDimX) : (EDimX1 < ENumDimX ? EDimX1 : ENumDimX),
				EMinY = EDimY0 < EDimY1 ? (EDimY0 < ENumDimY ? EDimY0 : ENumDimY) : (EDimY1 < ENumDimY ? EDimY1 : ENumDimY),
				EMax = EMaxX > EMaxY ? EMaxX : EMaxY,
				EMin = EMinX < EMinY ? EMinX : EMinY,
			};
			for (mint x = 0; x < ENumDimX; ++x)
			{
				for (mint y = 0; y < ENumDimY; ++y)
				{
					typename CVec::CType Add = 0;
					for (mint i = 0; i < EMin; ++i)
					{
						Add += _Src0.m_Columns[x][i] * _Src1.m_Columns[i][y];
					}
					for (mint i = EMin; i < EDimX1; ++i)
					{
						Add += _Src1.m_Columns[i][y];
					}
					for (mint i = EMin; i < EDimY0; ++i)
					{
						Add += _Src0.m_Columns[x][i];
					}
					_Dest.m_Columns[x][y] = Add;
				}
			}
		}

		template <typename t_CType0, mint t_nDimX0>
		inline_small TCMatrixAggregate operator *(const TCMatrixAggregate<t_CType0, t_nDimX0> &_Src) const
		{
			TCMatrixAggregate Ret;
			fs_Multiply(Ret, *this, _Src);
			return Ret;
		}
	};

	template <>
	class TCMatrixAggregate<CVecAggr4Dfp32, 4>
	{
	public:
		using CVec = CVecAggr4Dfp32;
		enum
		{
			ENumDimY = CVecAggr4Dfp32::ENumDim,
			ENumDimX = 4
		};
		CVec m_Columns[ENumDimX];

		inline_small const CVec &operator [] (mint _iOpr) const
		{
			return m_Columns[_iOpr];
		}

		inline_small CVec &operator [] (mint _iOpr)
		{
			return m_Columns[_iOpr];
		}

		template <typename t_CType0, mint t_nDimX0, typename t_CType1, mint t_nDimX1>
		static void fs_Multiply(TCMatrixAggregate<CVec, ENumDimX> &_Dest, const TCMatrixAggregate<t_CType0, t_nDimX0> &_Src0, const TCMatrixAggregate<t_CType1, t_nDimX1> &_Src1)
		{
			enum
			{
				EDimX0 = TCMatrixAggregate<t_CType0, t_nDimX0>::ENumDimX,
				EDimY0 = TCMatrixAggregate<t_CType0, t_nDimX0>::ENumDimY,
				EDimX1 = TCMatrixAggregate<t_CType1, t_nDimX1>::ENumDimX,
				EDimY1 = TCMatrixAggregate<t_CType1, t_nDimX1>::ENumDimY,
				EMaxX = EDimX0 > EDimX1 ? (EDimX0 > ENumDimX ? EDimX0 : ENumDimX) : (EDimX1 > ENumDimX ? EDimX1 : ENumDimX),
				EMaxY = EDimY0 > EDimY1 ? (EDimY0 > ENumDimY ? EDimY0 : ENumDimY) : (EDimY1 > ENumDimY ? EDimY1 : ENumDimY),
				EMinX = EDimX0 < EDimX1 ? (EDimX0 < ENumDimX ? EDimX0 : ENumDimX) : (EDimX1 < ENumDimX ? EDimX1 : ENumDimX),
				EMinY = EDimY0 < EDimY1 ? (EDimY0 < ENumDimY ? EDimY0 : ENumDimY) : (EDimY1 < ENumDimY ? EDimY1 : ENumDimY),
				EMax = EMaxX > EMaxY ? EMaxX : EMaxY,
				EMin = EMinX < EMinY ? EMinX : EMinY,
			};
			for (mint x = 0; x < ENumDimX; ++x)
			{
				for (mint y = 0; y < ENumDimY; ++y)
				{
					CVec::CType Add = 0;
					for (mint i = 0; i < EMin; ++i)
					{
						Add += _Src0.m_Columns[x][i] * _Src1.m_Columns[i][y];
					}
					for (mint i = EMin; i < EDimX1; ++i)
					{
						Add += _Src1.m_Columns[i][y];
					}
					for (mint i = EMin; i < EDimY0; ++i)
					{
						Add += _Src0.m_Columns[x][i];
					}
					_Dest.m_Columns[x][y] = Add;
				}
			}
		}

		template <typename t_CType0, mint t_nDimX0>
		inline_small TCMatrixAggregate operator *(const TCMatrixAggregate<t_CType0, t_nDimX0> &_Src) const
		{
			TCMatrixAggregate Ret;
			fs_Multiply(Ret, *this, _Src);
			return Ret;
		}
	};

	using CVecAggr4x4fp32 = TCMatrixAggregate<CVecAggr4Dfp32, 4>;
	using CVecAggr3x4fp32 = TCMatrixAggregate<CVecAggr4Dfp32, 3>;
}

#ifndef DMibPNoShortCuts
	using namespace NMib::NNumeric;
#endif
