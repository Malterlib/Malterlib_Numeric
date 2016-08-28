// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp80) 
#include "math.h"

namespace NMib::NSys::NMath
{
	pfp80 fg_Sin(pfp80 _Val)
	{
		return sinl(_Val);
	}
	pfp80 fg_Cos(pfp80 _Val)
	{
		return cosl(_Val);
	}
	pfp80 fg_Tan(pfp80 _Val)
	{
		return tanl(_Val);
	}
	pfp80 fg_SinH(pfp80 _Val)
	{
		return sinhl(_Val);
	}
	pfp80 fg_CosH(pfp80 _Val)
	{
		return coshl(_Val);
	}
	pfp80 fg_TanH(pfp80 _Val)
	{
		return tanhl(_Val);
	}
	pfp80 fg_ArcSin(pfp80 _Val)
	{
		return asinl(_Val);
	}
	pfp80 fg_ArcCos(pfp80 _Val)
	{
		return acosl(_Val);
	}
	pfp80 fg_ArcTan(pfp80 _Val)
	{
		return atanl(_Val);
	}
	pfp80 fg_ArcTan(pfp80 _Val, pfp80 _Source)
	{
		return atan2l(_Val, _Source);
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	pfp80 fg_ExpN(pfp80 _Val)
	{
		return expl(_Val);
	}
	pfp80 fg_LogN(pfp80 _Val)
	{
		return logl(_Val);
	}
	pfp80 fg_Exp10(pfp80 _Val)
	{
		// e^(log(10) * x)
		return powl(10.0l, _Val);
	}
	pfp80 fg_Log10(pfp80 _Val)
	{
		return log10l(_Val);
	}
	pfp80 fg_Exp2(pfp80 _Val)
	{
		// e^(log(2) * x)
		return powl(2.0l, _Val);
	}
	pfp80 fg_Log2(pfp80 _Val)
	{
		// log(x) / log(2)
		// log(x) * log2(e)
		return log2l(_Val);
	}
	pfp80 fg_Exp(pfp80 _Val, pfp80 _Base)
	{
		// e^(log(_Base) * x)
		return powl(_Base, _Val);
	}
	pfp80 fg_Log(pfp80 _Val, pfp80 _Base)
	{
		// log(x) / log(_Base)
		pfp80 log_Base = logl(_Base);
		return logl(_Val) / log_Base;
	}
	pfp80 fg_Sqrt(pfp80 _Val)
	{
		return sqrtl(_Val);
	}
	pfp80 fg_Pow(pfp80 _Val, pfp80 _Power)
	{
		return powl(_Val, _Power);
	}
	pfp80 fg_Floor(pfp80 _Val)
	{
		return floorl(_Val);
	}
	pfp80 fg_Ceil(pfp80 _Val)
	{
		return ceill(_Val);
	}
	pfp80 fg_Abs(pfp80 _Val)
	{
		return fabsl(_Val);
	}
	pfp80 fg_Mod(pfp80 _Val, pfp80 _Modulu)
	{
		return fmodl(_Val, _Modulu);
	}
}
#endif
