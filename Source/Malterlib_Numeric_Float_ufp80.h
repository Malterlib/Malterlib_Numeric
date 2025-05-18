// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

using ufp80 = NMib::NNumeric::TCFloat<0, 15, 64>;
using zufp80 = NMib::TCAutoClear<ufp80>;
