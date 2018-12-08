// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp32)
#include "math.h"

namespace NMib::NSys::NNumeric
{
	pfp32 fg_Sin(pfp32 _Val)
	{
		return sinf(_Val);
	}
	pfp32 fg_Cos(pfp32 _Val)
	{
		return cosf(_Val);
	}
	pfp32 fg_Tan(pfp32 _Val)
	{
		return tanf(_Val);
	}
	pfp32 fg_SinH(pfp32 _Val)
	{
		return sinhf(_Val);
	}
	pfp32 fg_CosH(pfp32 _Val)
	{
		return coshf(_Val);
	}
	pfp32 fg_TanH(pfp32 _Val)
	{
		return tanhf(_Val);
	}
	pfp32 fg_ArcSin(pfp32 _Val)
	{
		return asinf(_Val);
	}
	pfp32 fg_ArcCos(pfp32 _Val)
	{
		return acosf(_Val);
	}
	pfp32 fg_ArcTan(pfp32 _Val)
	{
		return atanf(_Val);
	}
	pfp32 fg_ArcTan(pfp32 _Val, pfp32 _Source)
	{
		return atan2f(_Val, _Source);
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	pfp32 fg_ExpN(pfp32 _Val)
	{
		return expf(_Val);
	}
	pfp32 fg_LogN(pfp32 _Val)
	{
		return logf(_Val);
	}
	pfp32 fg_Exp10(pfp32 _Val)
	{
		// e^(log(10) * x)
		return powf(10.0f, _Val);
	}
	pfp32 fg_Log10(pfp32 _Val)
	{
		return log10f(_Val);
	}
	pfp32 fg_Exp2(pfp32 _Val)
	{
		// e^(log(2) * x)
		return exp2f(_Val);
	}
	pfp32 fg_Log2(pfp32 _Val)
	{
		// log(x) / log(2)
		// log(x) * log2(e)
		return log2f(_Val);
	}
	pfp32 fg_Exp(pfp32 _Val, pfp32 _Base)
	{
		// e^(log(_Base) * x)
		return powf(_Base, _Val);
	}
	pfp32 fg_Log(pfp32 _Val, pfp32 _Base)
	{
		// log(x) / log(_Base)
		pfp32 log_Base = logf(_Base);
		return logf(_Val) / log_Base;
	}
	pfp32 fg_Sqrt(pfp32 _Val)
	{
		return sqrtf(_Val);
	}
	pfp32 fg_Pow(pfp32 _Val, pfp32 _Power)
	{
		return powf(_Val, _Power);
	}
	pfp32 fg_Floor(pfp32 _Val)
	{
		return floorf(_Val);
	}
	pfp32 fg_Ceil(pfp32 _Val)
	{
		return ceilf(_Val);
	}
	pfp32 fg_Abs(pfp32 _Val)
	{
		return fabsf(_Val);
	}
	pfp32 fg_Mod(pfp32 _Val, pfp32 _Modulu)
	{
		return fmodf(_Val, _Modulu);
	}
}
#endif
