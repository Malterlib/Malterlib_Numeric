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

#if 0
	template <>
	class TCVecAggregate<fp32, 4>
	{
	public:
		using CType = fp32;

		enum
		{
			ENumDim = 4
		};
		__m128 m_Axis;

		inline_small const fp32 &operator [] (mint _iOpr) const
		{
			const fp32 &Ret = m_Axis.m128_f32[_iOpr];
			return Ret;
		}

		inline_small CType &operator [] (mint _iOpr)
		{
			fp32 &Ret = (fp32 &)m_Axis.m128_f32[_iOpr];
			return Ret;
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

		static inline_small TCVecAggregate fs_Init(CType _Value0, CType _Value1, CType _Value2, CType _Value3)
		{
			TCVecAggregate Ret;
			Ret.m_Axis.m128_f32[0] = _Value0.f_Get();
			Ret.m_Axis.m128_f32[1] = _Value1.f_Get();
			Ret.m_Axis.m128_f32[2] = _Value2.f_Get();
			Ret.m_Axis.m128_f32[3] = _Value3.f_Get();
			//Ret.m_Axis; = _mm_set_ps(_Value0.f_Get(), _Value1.f_Get(), _Value2.f_Get(), _Value3.f_Get());
			return Ret;
		}

		template <uint64 _Number0, uint64 _Decimals0, int32 _Exponent0,
		uint64 _Number1, uint64 _Decimals1, int32 _Exponent1,
		uint64 _Number2, uint64 _Decimals2, int32 _Exponent2,
		uint64 _Number3, uint64 _Decimals3, int32 _Exponent3
		>
		class CStaticFixedPoint
		{
		public:
			static __m128 ms_Value;

			static __m128 fs_Get()
			{
				fp32 Value0 = pfp32(_Number0);
				Value0 = (Value0 + (fp32(pfp32(_Decimals0)) / fp32(10.0f).f_Pow(fp32(pfp32(_Decimals0)).f_Log10().f_Floor())) - fp32(1.0)) * fp32(10.0f).f_Pow(fp32(_Exponent0));
				fp32 Value1 = pfp32(_Number1);
				Value1 = (Value1 + (fp32(pfp32(_Decimals1)) / fp32(10.0f).f_Pow(fp32(pfp32(_Decimals1)).f_Log10().f_Floor())) - fp32(1.0)) * fp32(10.0f).f_Pow(fp32(_Exponent1));
				fp32 Value2 = pfp32(_Number2);
				Value2 = (Value2 + (fp32(pfp32(_Decimals2)) / fp32(10.0f).f_Pow(fp32(pfp32(_Decimals2)).f_Log10().f_Floor())) - fp32(1.0)) * fp32(10.0f).f_Pow(fp32(_Exponent2));
				fp32 Value3 = pfp32(_Number3);
				Value3 = (Value3 + (fp32(pfp32(_Decimals3)) / fp32(10.0f).f_Pow(fp32(pfp32(_Decimals3)).f_Log10().f_Floor())) - fp32(1.0)) * fp32(10.0f).f_Pow(fp32(_Exponent3));

				return _mm_set_ps(Value0.f_Get(), Value1.f_Get(), Value2.f_Get(), Value3.f_Get());
			}
		};
	};

	template <uint64 _Number0, uint64 _Decimals0, int32 _Exponent0,
	uint64 _Number1, uint64 _Decimals1, int32 _Exponent1,
	uint64 _Number2, uint64 _Decimals2, int32 _Exponent2,
	uint64 _Number3, uint64 _Decimals3, int32 _Exponent3
	>
	__m128 TCVecAggregate<fp32, 4>::CStaticFixedPoint<_Number0, _Decimals0, _Exponent0, _Number1, _Decimals1, _Exponent1, _Number2, _Decimals2, _Exponent2, _Number3, _Decimals3, _Exponent3>::ms_Value = TCVecAggregate<fp32, 4>::CStaticFixedPoint<_Number0, _Decimals0, _Exponent0, _Number1, _Decimals1, _Exponent1, _Number2, _Decimals2, _Exponent2, _Number3, _Decimals3, _Exponent3>::fs_Get();
#endif

#define DMibVec4Dfp32FixedPointConst(_Number0, _Decimals0, _Exponent0, _Number1, _Decimals1, _Exponent1, _Number2, _Decimals2, _Exponent2, _Number3, _Decimals3, _Exponent3) NMib::NNumeric::TCVecAggregate<fp32, 4>::CStaticFixedPoint<_Number0, 1##_Decimals0, _Exponent0, _Number1, 1##_Decimals1, _Exponent1, _Number2, 1##_Decimals2, _Exponent2, _Number3, 1##_Decimals3, _Exponent3>::ms_Value


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
//				using CVec0 = TCMatrixAggregate<t_CType0, t_nDimX0>::CType;
//				using CVec1 = TCMatrixAggregate<t_CType1, t_nDimX1>::CType;
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
#if 0
		static inline_small __m128 fs_SplatX(__m128 _Val)
		{
			return _mm_shuffle_ps(_Val, _Val, _MM_SHUFFLE(0,0,0,0));
		}
		static inline_small __m128 fs_SplatY(__m128 _Val)
		{
			return _mm_shuffle_ps(_Val, _Val, _MM_SHUFFLE(1,1,1,1));
		}
		static inline_small __m128 fs_SplatZ(__m128 _Val)
		{
			return _mm_shuffle_ps(_Val, _Val, _MM_SHUFFLE(2,2,2,2));
		}
		static inline_small __m128 fs_SplatW(__m128 _Val)
		{
			return _mm_shuffle_ps(_Val, _Val, _MM_SHUFFLE(3,3,3,3));
		}

		static void fs_Multiply(TCMatrixAggregate &_Dest, const TCMatrixAggregate &_Src0, const TCMatrixAggregate &_Src1)
		{
			__m128 Vec00 = _Src0.m_Columns[0].m_Axis;
			__m128 Vec01 = _Src0.m_Columns[1].m_Axis;
			__m128 Vec02 = _Src0.m_Columns[2].m_Axis;
			__m128 Vec03 = _Src0.m_Columns[3].m_Axis;
			__m128 Vec10 = _Src1.m_Columns[0].m_Axis;
			__m128 Vec11 = _Src1.m_Columns[1].m_Axis;
			__m128 Vec12 = _Src1.m_Columns[2].m_Axis;
			__m128 Vec13 = _Src1.m_Columns[3].m_Axis;

			_MM_TRANSPOSE4_PS(Vec00, Vec01, Vec02, Vec03);
			_MM_TRANSPOSE4_PS(Vec10, Vec11, Vec12, Vec13);

			__m128 VecT00 = fs_SplatX(Vec00);
			__m128 VecT01 = fs_SplatY(Vec00);
			__m128 VecT02 = fs_SplatZ(Vec00);
			__m128 VecT03 = fs_SplatW(Vec00);
			__m128 VecT10 = fs_SplatX(Vec01);
			__m128 VecT11 = fs_SplatY(Vec01);
			__m128 VecT12 = fs_SplatZ(Vec01);
			__m128 VecT13 = fs_SplatW(Vec01);
			__m128 VecT20 = fs_SplatX(Vec02);
			__m128 VecT21 = fs_SplatY(Vec02);
			__m128 VecT22 = fs_SplatZ(Vec02);
			__m128 VecT23 = fs_SplatW(Vec02);
			__m128 VecT30 = fs_SplatX(Vec03);
			__m128 VecT31 = fs_SplatY(Vec03);
			__m128 VecT32 = fs_SplatZ(Vec03);
			__m128 VecT33 = fs_SplatW(Vec03);

			__m128 Temp00 = _mm_mul_ps(VecT00, Vec10);
			__m128 Temp01 = _mm_mul_ps(VecT01, Vec11);
			__m128 Temp02 = _mm_mul_ps(VecT02, Vec12);
			__m128 Temp03 = _mm_mul_ps(VecT03, Vec13);

			__m128 Temp10 = _mm_mul_ps(VecT10, Vec10);
			__m128 Temp11 = _mm_mul_ps(VecT11, Vec11);
			__m128 Temp12 = _mm_mul_ps(VecT12, Vec12);
			__m128 Temp13 = _mm_mul_ps(VecT13, Vec13);

			__m128 Temp20 = _mm_mul_ps(VecT20, Vec10);
			__m128 Temp21 = _mm_mul_ps(VecT21, Vec11);
			__m128 Temp22 = _mm_mul_ps(VecT22, Vec12);
			__m128 Temp23 = _mm_mul_ps(VecT23, Vec13);

			__m128 Temp30 = _mm_mul_ps(VecT30, Vec10);
			__m128 Temp31 = _mm_mul_ps(VecT31, Vec11);
			__m128 Temp32 = _mm_mul_ps(VecT32, Vec12);
			__m128 Temp33 = _mm_mul_ps(VecT33, Vec13);

			Vec00 = _mm_add_ps(_mm_add_ps(_mm_add_ps(Temp00, Temp10), Temp20), Temp30);
			Vec01 = _mm_add_ps(_mm_add_ps(_mm_add_ps(Temp01, Temp11), Temp21), Temp31);
			Vec02 = _mm_add_ps(_mm_add_ps(_mm_add_ps(Temp02, Temp12), Temp22), Temp32);
			Vec03 = _mm_add_ps(_mm_add_ps(_mm_add_ps(Temp03, Temp13), Temp23), Temp33);
			_MM_TRANSPOSE4_PS(Vec00, Vec01, Vec02, Vec03);

			_Dest.m_Columns[0].m_Axis = Vec00;
			_Dest.m_Columns[1].m_Axis = Vec01;
			_Dest.m_Columns[2].m_Axis = Vec02;
			_Dest.m_Columns[3].m_Axis = Vec03;


		}
#endif

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
