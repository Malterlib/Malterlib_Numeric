# CLAUDE.md - Numeric Module

This file provides guidance to Claude Code (claude.ai/code) when working with the Numeric module in the Malterlib framework.

## Module Overview

The Numeric module provides comprehensive numeric computation capabilities including:
- **Custom floating-point types** with configurable precision (fp8 through fp4096)
- **Extended-precision integers** (int8 through int4096, including unsigned variants)
- **Tagged integer types** for type-safe integer handling
- **Vector mathematics** with templated n-dimensional vectors
- **SIMD** lane vectors, and the vector, matrix, quaternion and bounds types of 3D math built on them
- **Mathematical constants** and utility functions

## Architecture

### Floating-Point System

The module implements a flexible floating-point template system:
- **TCFloat** - Core template class for floating-point numbers with configurable sign, exponent, mantissa, and padding bits
- **Multiple precisions**: fp8, fp16, fp32, fp64, fp80, fp128, fp256, fp512, fp1024, fp2048, fp4096
- **Unsigned variants**: ufp8, ufp16, ufp32, ufp64, ufp80, ufp128, ufp256, ufp512, ufp1024, ufp2048, ufp4096
- **Emulated types**: CIEEEFloat32Emu, CIEEEFloat64Emu, CIEEEFloat80Emu for testing and cross-platform consistency
- **Built-in vs emulated**: System automatically uses hardware types when available (fp32, fp64, fp80 on some platforms)

### Extended Integer System

The module provides arbitrary-precision integer arithmetic:
- **TCInt** - Core template class for extended-precision integers
- **Signed types**: int8, int16, int32, int64, int80, int96, int128, int160, int192, int256, int320, int384, int512, int1024, int2048, int4096
- **Unsigned types**: uint8, uint16, uint32, uint64, uint80, uint96, uint128, uint160, uint192, uint256, uint320, uint384, uint512, uint1024, uint2048, uint4096
- Supports arithmetic operations across different precisions

### Tagged Integer System

Type-safe integer wrappers:
- **TCTaggedInteger** - Template class for creating distinct integer types
- Prevents accidental mixing of different semantic integer types
- Configurable default initialization value
- Full arithmetic and comparison operator support

### Vector Mathematics

N-dimensional vector operations:
- **TCVec** - Storage for any dimension and underlying numeric type, with construction, conversion and indexing
- `TCVec` has no arithmetic and no SIMD. Use the math types below for computation

### SIMD

`Mib/Numeric/Simd` provides fixed-width vectors of `pfp32` and `int32`:
- **TCSimd<t_CType, t_nLanes>** selects `TCSimdFloat`, `TCSimdInt` or `TCSimdMask` (`bool`) on the native backend
- **CSimd4_fp32**, **CSimd4_int32**, **CSimd4_bool** and the `8` variants are the common aliases
- **TCSimdReference<t_CType, t_nLanes>** is the same interface on the scalar backend

The backend is chosen at compile time from `DArchitectureExtension_NEON`, `DArchitectureExtension_SSE`,
`DArchitectureExtension_SSE41` and `DArchitectureExtension_AVX2`. There is no runtime dispatch.
8 lanes are one AVX2 vector or a pair of 4 lane vectors, 16 lanes a pair of 8 lane vectors, and other
lane counts use the scalar backend. A vector has 1 to 32 lanes, which is what the bits of a mask hold.

Every backend must produce the same bits as the scalar backend, which is what
`Test_Malterlib_Numeric_Simd.cpp` checks. When adding an operation, add it to every backend in
`Source/Malterlib_Numeric_Simd_Backend_*.hpp` and to that test. Semantics that differ between
instruction sets are pinned as follows:
- `f_Min` and `f_Max` return the argument when either operand is NaN
- `f_Sum` adds adjacent lanes first, then the pairs
- Comparisons return a mask. `!=` is true for NaN, all others are false
- `f_ToInt` truncates and is unspecified for NaN and values outside `int32`
- Shift counts must be 0 to 31

### Math

`Mib/Numeric/Math` builds on `CSimd4_fp32`: `CVec3_fp32`, `CVec4_fp32`, `CQuat_fp32`, `CMat4x4_fp32`,
`CMat3x4_fp32`, `CSphere_fp32`, `CBox_fp32`, `CPlane_fp32` and `CFrustum_fp32`.

Each is a template of the type of its elements, as `TCVec3<t_CType>`, and the name ends with the type after an
underscore. Only `pfp32` is implemented, and the other templates are declared without a definition. Element types
are added when something uses them, which is also how the lane types of `TCSimd` are named: `CSimd4_fp32`,
`CSimd8_int32`.

Conventions: column vectors, column-major matrices, right-handed view space looking down negative Z,
clip space depth 0 to 1. `CVec3_fp32` keeps lane 3 at zero.

Range: the math types are for the values of scenes. Operations calculate in `pfp32` with the fastest
way that is right for values whose squares and products of up to three are well within what `pfp32`
has, and for matrices that are far from one without an inverse. Other values give infinities, zeros
or values that are not numbers, as `pfp32` does. Do not make often used operations slower to handle
values that only data that is broken has.

`CFrustum_fp32::f_CullSpheres` and `f_CullBoxes` take structure-of-arrays input, process 8 objects at
a time and give the same answers as `f_Intersects`.

## File Organization

```
Numeric/
├── Include/Mib/Numeric/          # Public headers
│   ├── Float                     # Generic float header
│   ├── FloatImp                  # Float implementation details
│   ├── CustomFloat               # Custom float configurations
│   ├── Integer                   # Extended integer types
│   ├── TaggedInteger             # Type-safe integers
│   ├── Vector                    # Vector storage
│   ├── Simd                      # SIMD vectors
│   ├── Math                      # Vector, matrix, quaternion and bounds types
│   ├── Limits                    # Numeric limits
│   └── fp*/ufp*                  # Specific precision headers
├── Source/                       # Implementation files
│   ├── Malterlib_Numeric_Float*  # Float implementation
│   ├── Malterlib_Numeric_Integer.h
│   ├── Malterlib_Numeric_TaggedInteger.*
│   ├── Malterlib_Numeric_Vector.h
│   ├── Malterlib_Numeric_Simd*   # SIMD wrapper and backends
│   └── Malterlib_Numeric_Math*   # SIMD math types
└── Test/                         # Unit tests
    ├── Test_Malterlib_Numeric_Float.*
    ├── Test_Malterlib_Numeric_Integer.cpp
    ├── Test_Malterlib_Numeric_Vector.cpp
    ├── Test_Malterlib_Numeric_Simd.cpp
    └── Test_Malterlib_Numeric_Math.cpp
```

## Usage Examples

### Floating-Point Numbers

```cpp
#include <Mib/Numeric/fp32>
#include <Mib/Numeric/fp64>
#include <Mib/Numeric/fp128>

// Basic usage
fp32 Value32 = fp32(3.14f);
fp64 Value64 = fp64(2.71828);
fp128 Value128 = fp128(Value64);  // Conversion between precisions

// Mathematical operations
fp64 Result = Value64 * fp64::fs_2() + fp64::fs_Pi();

// Constants
fp64 Pi = fg_FPi<fp64>();
fp64 E = fg_FE<fp64>();
fp64 Sqrt2 = fg_FSqrt2<fp64>();

// Special values
fp64 Infinity = fp64::fs_Inf();
fp64 NaN = fp64::fs_QNan();
```

### Extended Integers

```cpp
#include <Mib/Numeric/Integer>

// Extended precision arithmetic
int128 BigNum1(int64(0x7FFFFFFFFFFFFFFF));
int128 BigNum2(int64(0x1000000000000000));
int128 Result = BigNum1 + BigNum2;

// Mixed precision operations
int256 LargerResult = int256(BigNum1) * int256(BigNum2);

// Bit operations
uint128 Shifted = uint128(1) << 100;
```

### Tagged Integers

```cpp
#include <Mib/Numeric/TaggedInteger>

// Define distinct ID types
struct CUserIDTag {};
struct CProductIDTag {};

using CUserID = TCTaggedInteger<int32, CUserIDTag>;
using CProductID = TCTaggedInteger<int32, CProductIDTag>;

// Type-safe usage
CUserID UserID = CUserID::fs_Create(12345);
CProductID ProductID = CProductID::fs_Create(67890);

// This would cause a compile error:
// UserID = ProductID;  // Error: incompatible types

// Explicit access when needed
int32 RawUserID = UserID.f_Get();
```

### Vector Operations

```cpp
#include <Mib/Numeric/Vector>

TCVec<fp32, 3> Position(1.0f, 2.0f, 3.0f);
TCVec<int32, 3> Cell(Position); // Converts each axis

// N-dimensional vectors
TCVec<fp64, 10> HighDimVector;
HighDimVector[5] = 3.14;
```

### SIMD Operations

```cpp
#include <Mib/Numeric/Math>

CSimd4_fp32 Values(1.0f, -2.0f, 3.0f, -4.0f);
CSimd4_fp32 Clamped = CSimd4_fp32::fs_Select(Values < 0.0f, CSimd4_fp32::fs_Zero(), Values);

CMat4x4_fp32 View = CMat4x4_fp32::fs_LookAt(CVec3_fp32(0.0f, 2.0f, 5.0f), CVec3_fp32::fs_Zero(), CVec3_fp32(0.0f, 1.0f, 0.0f));
CMat4x4_fp32 Projection = CMat4x4_fp32::fs_PerspectiveReverseInfinite(1.0f, 16.0f / 9.0f, 0.1f);
CFrustum_fp32 Frustum(Projection * View);

bool bVisible = Frustum.f_Intersects(CSphere_fp32(CVec3_fp32(0.0f, 0.0f, -3.0f), 1.0f));
```

## Mathematical Constants

The module provides templated constants for any floating-point type:

```cpp
template <typename t_CFloat>
constexpr t_CFloat fg_F0();          // Zero
constexpr t_CFloat fg_F0_5();        // 0.5
constexpr t_CFloat fg_F1();          // One
constexpr t_CFloat fg_F2();          // Two
constexpr t_CFloat fg_FPi();         // Pi
constexpr t_CFloat fg_FSqrt2();      // Square root of 2
constexpr t_CFloat fg_FE();          // Euler's number (e)
constexpr t_CFloat fg_FGoldenRatio(); // Golden ratio
constexpr t_CFloat fg_FLog10_2();    // Log base 10 of 2
constexpr t_CFloat fg_FLog2_10();    // Log base 2 of 10
constexpr t_CFloat fg_FInf();        // Positive infinity
constexpr t_CFloat fg_FNegInf();     // Negative infinity
constexpr t_CFloat fg_FQNan();       // Quiet NaN
constexpr t_CFloat fg_FSNan();       // Signaling NaN
```

## Implementation Notes

### Floating-Point Implementation

- Uses `TCFloat` template with configurable bit widths for sign, exponent, and mantissa
- Automatically selects hardware implementation when available (fp32, fp64, fp80)
- Falls back to software emulation for other precisions
- Supports IEEE-754 compliant operations
- Provides both constexpr and runtime implementations

### Integer Implementation

- Uses `TCInt` template combining upper and lower halves
- Supports arbitrary precision through recursive composition
- Implements full arithmetic, bitwise, and comparison operations
- Handles sign extension and overflow correctly
- Optimized for common sizes (matches hardware types when possible)

### Performance Considerations

- Hardware types (fp32, fp64, int32, int64) use native operations
- Extended precision types use software emulation
- `TCSimd` and the math types use NEON, SSE or AVX2 selected at compile time
- Consider precision requirements vs performance trade-offs
- Use emulated types (e.g., CIEEEFloat32Emu) for cross-platform consistency in tests

## Code Standards

When working with the Numeric module:

### Include Patterns
```cpp
// Include specific precision headers
#include <Mib/Numeric/fp64>
#include <Mib/Numeric/int128>

// Include base functionality
#include <Mib/Numeric/Float>
#include <Mib/Numeric/Integer>
#include <Mib/Numeric/Vector>
```

### Naming Conventions
- Float types: `fp[bits]` for signed, `ufp[bits]` for unsigned
- Integer types: `int[bits]` for signed, `uint[bits]` for unsigned
- Constants: `fg_F[Name]<Type>()` for templated constants
- Static constructors: `fs_[Name]()` for special values

### Function Patterns
```cpp
// Static factory methods
fp64 Value = fp64::fs_Pi();
fp64 Two = fp64::fs_2();

// Conversion functions
fp32 Converted = fg_Convert<fp32>(DoubleValue);

// Member functions
bool bIsNaN = Value.f_IsNaN();
bool bIsInf = Value.f_IsInf();
fp64 Raw = Value.f_Get();
```

## Testing

The module includes comprehensive test coverage:

```bash
# Run all numeric tests
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/Numeric*"]'

# Run specific test suites
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/Numeric/Float*"]'
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/Numeric/Integer*"]'
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/Numeric/Vector*"]'
/opt/Deploy/Tests/RunAllTests --paths '["Malterlib/Numeric/Simd*", "Malterlib/Numeric/Math*"]'
```

Test files use templated test functions to verify behavior across all supported types.

## Dependencies

The Numeric module depends on:
- **Core** - Basic types and utilities
- **Bit** - Bit manipulation operations
- **Type** - Type traits and metaprogramming
- **Storage** - Memory management utilities
- **String** - String formatting support

## Common Pitfalls

1. **Precision Loss**: Converting from higher to lower precision loses information
2. **Performance**: Extended precision types are much slower than hardware types
3. **NaN Propagation**: NaN values propagate through operations
4. **Integer Overflow**: Extended integers have limits, check for overflow
6. **Template Instantiation**: Large precision types increase compile time and binary size

## Advanced Features

### Custom Float Configuration
```cpp
// Define custom floating-point format
using CCustomFloat = TCFloat<1, 8, 23, 0>;  // Sign, exponent, mantissa, padding
```

### Compile-Time Computation
```cpp
// Many operations support constexpr evaluation
constexpr fp64 Result = fg_FPi<fp64>() * fp64::fs_2();
static_assert(Result > fp64(6.0));
```

### Platform-Specific Optimizations
The module automatically detects and uses:
- Hardware FPU for fp32, fp64
- Extended precision FPU for fp80 (x86)
- NEON, SSE or AVX2 for `TCSimd`, selected at compile time
