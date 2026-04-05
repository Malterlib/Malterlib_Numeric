// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Core/Core>

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp64)
#include "math.h"

namespace NMib::NSys::NNumeric
{
	pfp64 fg_Sin(pfp64 _Val)
	{
		return sin(_Val);
	}
	pfp64 fg_Cos(pfp64 _Val)
	{
		return cos(_Val);
	}
	pfp64 fg_Tan(pfp64 _Val)
	{
		return tan(_Val);
	}
	pfp64 fg_SinH(pfp64 _Val)
	{
		return sinh(_Val);
	}
	pfp64 fg_CosH(pfp64 _Val)
	{
		return cosh(_Val);
	}
	pfp64 fg_TanH(pfp64 _Val)
	{
		return tanh(_Val);
	}
	pfp64 fg_ArcSin(pfp64 _Val)
	{
		return asin(_Val);
	}
	pfp64 fg_ArcCos(pfp64 _Val)
	{
		return acos(_Val);
	}
	pfp64 fg_ArcTan(pfp64 _Val)
	{
		return atan(_Val);
	}
	pfp64 fg_ArcTan(pfp64 _Val, pfp64 _Source)
	{
		return atan2(_Val, _Source);
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	pfp64 fg_ExpN(pfp64 _Val)
	{
		return exp(_Val);
	}
	pfp64 fg_LogN(pfp64 _Val)
	{
		return log(_Val);
	}
	pfp64 fg_Exp10(pfp64 _Val)
	{
		// e^(log(10) * x)
		return pow(10.0, _Val);
	}
	pfp64 fg_Log10(pfp64 _Val)
	{
		return log10(_Val);
	}
	pfp64 fg_Exp2(pfp64 _Val)
	{
		// e^(log(2) * x)
		return exp2(_Val);
	}
	pfp64 fg_Log2(pfp64 _Val)
	{
		// log(x) / log(2)
		// log(x) * log2(e)
		return log2(_Val);
	}
	pfp64 fg_Exp(pfp64 _Val, pfp64 _Base)
	{
		// e^(log(_Base) * x)
		return pow(_Base, _Val);
	}
	pfp64 fg_Log(pfp64 _Val, pfp64 _Base)
	{
		// log(x) / log(_Base)
		pfp64 log_Base = log(_Base);
		return log(_Val) / log_Base;
	}
	pfp64 fg_Sqrt(pfp64 _Val)
	{
		return sqrt(_Val);
	}
	pfp64 fg_Pow(pfp64 _Val, pfp64 _Power)
	{
		return pow(_Val, _Power);
	}
	pfp64 fg_Floor(pfp64 _Val)
	{
		return floor(_Val);
	}
	pfp64 fg_Ceil(pfp64 _Val)
	{
		return ceil(_Val);
	}
	pfp64 fg_Abs(pfp64 _Val)
	{
		return fabs(_Val);
	}
	pfp64 fg_Mod(pfp64 _Val, pfp64 _Modulu)
	{
		return fmod(_Val, _Modulu);
	}
}
#endif
