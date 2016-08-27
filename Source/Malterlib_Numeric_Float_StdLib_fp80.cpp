// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp80) 
#include "math.h"

namespace NMib::NSys::NMath
{
	pfp80 fg_Sin(pfp80 _Val)
	{
		return sin(_Val);
	}
	pfp80 fg_Cos(pfp80 _Val)
	{
		return cos(_Val);
	}
	pfp80 fg_Tan(pfp80 _Val)
	{
		return tan(_Val);
	}
	pfp80 fg_SinH(pfp80 _Val)
	{
		return sinh(_Val);
	}
	pfp80 fg_CosH(pfp80 _Val)
	{
		return cosh(_Val);
	}
	pfp80 fg_TanH(pfp80 _Val)
	{
		return tanh(_Val);
	}
	pfp80 fg_ArcSin(pfp80 _Val)
	{
		return asin(_Val);
	}
	pfp80 fg_ArcCos(pfp80 _Val)
	{
		return acos(_Val);
	}
	pfp80 fg_ArcTan(pfp80 _Val)
	{
		return atan(_Val);
	}
	pfp80 fg_ArcTan(pfp80 _Val, pfp80 _Source)
	{
		return atan2(_Val, _Source);
	}

	/************************************************************************************************\
	||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
	|| Logarithm and exponent
	||______________________________________________________________________________________________||
	\************************************************************************************************/


	pfp80 fg_ExpN(pfp80 _Val)
	{
		return exp(_Val);
	}
	pfp80 fg_LogN(pfp80 _Val)
	{
		return log(_Val);
	}
	pfp80 fg_Exp10(pfp80 _Val)
	{
		// e^(log(10) * x)
		/*
		// Gives bad accurency
		pfp80 log_10 = 2.3025850929940456840179914546844;
		return exp(log_10 * _Val);
		*/
		return pow(10.0l, _Val);
	}
	pfp80 fg_Log10(pfp80 _Val)
	{
		return log10(_Val);
	}
	pfp80 fg_Exp2(pfp80 _Val)
	{
		// e^(log(2) * x)
		/*
		// Gives bad accurency
		pfp80 log_2 = 0.69314718055994530941723212145818;
		return exp(log_2 * _Val);
		*/
		return pow(2.0l, _Val);
	}
	pfp80 fg_Log2(pfp80 _Val)
	{
		// log(x) / log(2)
		// log(x) * log2(e)
		pfp80 log2_e = 1.4426950408889634073599246810018921374266459541529l;
		return log(_Val) * log2_e;
	}
	pfp80 fg_Exp(pfp80 _Val, pfp80 _Base)
	{
		// e^(log(_Base) * x)
		pfp80 log_Base = log(_Base);
		return exp(log_Base * _Val);
	}
	pfp80 fg_Log(pfp80 _Val, pfp80 _Base)
	{
		// log(x) / log(_Base)
		pfp80 log_Base = log((_Base));
		return log(_Val) / log_Base;
	}
	pfp80 fg_Sqrt(pfp80 _Val)
	{
		return sqrt(_Val);
	}
	pfp80 fg_Pow(pfp80 _Val, pfp80 _Power)
	{
		return pow(_Val, _Power);
	}
	pfp80 fg_Floor(pfp80 _Val)
	{
		return floor(_Val);
	}
	pfp80 fg_Ceil(pfp80 _Val)
	{
		return ceil(_Val);
	}
	pfp80 fg_Abs(pfp80 _Val)
	{
		return fabs(_Val);
	}
	pfp80 fg_Mod(pfp80 _Val, pfp80 _Modulu)
	{
		return fmod(_Val, _Modulu);
	}
}
#endif
