// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#if defined(DMibPFloat_StdLib) && defined(DMibPCanDo_fp32)
#include "math.h"

namespace NMib
{
	namespace NSys
	{
		namespace NMath
		{
			pfp32 fg_Sin(pfp32 _Val)
			{
				return sin(_Val);
			}
			pfp32 fg_Cos(pfp32 _Val)
			{
				return cos(_Val);
			}
			pfp32 fg_Tan(pfp32 _Val)
			{
				return tan(_Val);
			}
			pfp32 fg_SinH(pfp32 _Val)
			{
				return sinh(_Val);
			}
			pfp32 fg_CosH(pfp32 _Val)
			{
				return cosh(_Val);
			}
			pfp32 fg_TanH(pfp32 _Val)
			{
				return tanh(_Val);
			}
			pfp32 fg_ArcSin(pfp32 _Val)
			{
				return asin(_Val);
			}
			pfp32 fg_ArcCos(pfp32 _Val)
			{
				return acos(_Val);
			}
			pfp32 fg_ArcTan(pfp32 _Val)
			{
				return atan(_Val);
			}
			pfp32 fg_ArcTan(pfp32 _Val, pfp32 _Source)
			{
				return atan2(_Val, _Source);
			}

			/************************************************************************************************\
			||¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯||
			|| Logarithm and exponent
			||______________________________________________________________________________________________||
			\************************************************************************************************/


			pfp32 fg_ExpN(pfp32 _Val)
			{
				return exp(_Val);
			}
			pfp32 fg_LogN(pfp32 _Val)
			{
				return log(_Val);
			}
			pfp32 fg_Exp10(pfp32 _Val)
			{
				// e^(log(10) * x)
				pfp64 log_10 = 2.3025850929940456840179914546844;
				return exp(log_10 * pfp64(_Val));
			}
			pfp32 fg_Log10(pfp32 _Val)
			{
				return log10(_Val);
			}
			pfp32 fg_Exp2(pfp32 _Val)
			{
				// e^(log(2) * x)
				pfp64 log_2 = 0.69314718055994530941723212145818;
				return exp(log_2 * pfp64(_Val));
			}
			pfp32 fg_Log2(pfp32 _Val)
			{
				// log(x) / log(2)
				// log(x) * log2(e)
				pfp64 log2_e = 1.4426950408889634073599246810019;
				return log(pfp64(_Val)) * log2_e;
			}
			pfp32 fg_Exp(pfp32 _Val, pfp32 _Base)
			{
				// e^(log(_Base) * x)
				pfp32 log_Base = log(_Base);
				return exp(log_Base * _Val);
			}
			pfp32 fg_Log(pfp32 _Val, pfp32 _Base)
			{
				// log(x) / log(_Base)
				pfp32 log_Base = log((_Base));
				return log(_Val) / log_Base;
			}
			pfp32 fg_Sqrt(pfp32 _Val)
			{
				return sqrt(_Val);
			}
			pfp32 fg_Pow(pfp32 _Val, pfp32 _Power)
			{
				return pow(_Val, _Power);
			}
			pfp32 fg_Floor(pfp32 _Val)
			{
				return floor(_Val);
			}
			pfp32 fg_Ceil(pfp32 _Val)
			{
				return ceil(_Val);
			}
			pfp32 fg_Abs(pfp32 _Val)
			{
				return fabs(_Val);
			}
			pfp32 fg_Mod(pfp32 _Val, pfp32 _Modulu)
			{
				return fmod(_Val, _Modulu);
			}
		}
	}
}
#endif
