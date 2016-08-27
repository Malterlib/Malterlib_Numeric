// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp64)
#include "math.h"

namespace NMib::NSys::NMath
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
		/*
		// Gives bad accurency
		pfp64 log_10 = 2.3025850929940456840179914546844;
		return exp(log_10 * _Val);
		*/
		return pow(10.0, _Val);
	}
	pfp64 fg_Log10(pfp64 _Val)
	{
		return log10(_Val);
	}
	pfp64 fg_Exp2(pfp64 _Val)
	{
		// e^(log(2) * x)
		/*
		// Gives bad accurency
		pfp64 log_2 = 0.69314718055994530941723212145818;
		return exp(log_2 * _Val);
		*/
		return pow(2.0, _Val);
	}
	pfp64 fg_Log2(pfp64 _Val)
	{
		// log(x) / log(2)
		// log(x) * log2(e)
		pfp64 log2_e = 1.4426950408889634073599246810019;
		return log(_Val) * log2_e;
	}
	pfp64 fg_Exp(pfp64 _Val, pfp64 _Base)
	{
		// e^(log(_Base) * x)
		pfp64 log_Base = log(_Base);
		return exp(log_Base * _Val);
	}
	pfp64 fg_Log(pfp64 _Val, pfp64 _Base)
	{
		// log(x) / log(_Base)
		pfp64 log_Base = log((_Base));
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
