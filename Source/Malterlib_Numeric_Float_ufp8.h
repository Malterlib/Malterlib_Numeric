// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

#include <Mib/Core/Core>

#include "Malterlib_Numeric_Float.h"

using ufp8 = NMib::NNumeric::TCFloat<0, 3, 5, 0>;
using zufp8 = NMib::TCAutoClear<ufp8>;
