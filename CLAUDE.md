# CLAUDE.md - Numeric Module

This file provides guidance to Claude Code (claude.ai/code) when working with the Numeric module in the Malterlib framework.

## Module Overview

The Numeric module provides comprehensive numeric computation capabilities including:
- **Custom floating-point types** with configurable precision (fp8 through fp4096)
- **Extended-precision integers** (int8 through int4096, including unsigned variants)
- **Tagged integer types** for type-safe integer handling
- **Vector mathematics** with templated n-dimensional vectors
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
- **TCVecAggregate** - Core vector storage template
- **TCVec** - Full-featured vector class with mathematical operations
- Support for any dimension and underlying numeric type
- SIMD optimizations for common configurations (when available)

## File Organization

```
Numeric/
├── Include/Mib/Numeric/          # Public headers
│   ├── Float                     # Generic float header
│   ├── FloatImp                  # Float implementation details
│   ├── CustomFloat               # Custom float configurations
│   ├── Integer                   # Extended integer types
│   ├── TaggedInteger             # Type-safe integers
│   ├── Vector                    # Vector mathematics
│   ├── Limits                    # Numeric limits
│   └── fp*/ufp*                  # Specific precision headers
├── Source/                       # Implementation files
│   ├── Malterlib_Numeric_Float*  # Float implementation
│   ├── Malterlib_Numeric_Integer.h
│   ├── Malterlib_Numeric_TaggedInteger.*
│   └── Malterlib_Numeric_Vector.h
└── Test/                         # Unit tests
    ├── Test_Malterlib_Numeric_Float.*
    ├── Test_Malterlib_Numeric_Integer.cpp
    └── Test_Malterlib_Numeric_Vector.cpp
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

// 3D vector operations
TCVec<fp32, 3> Position(1.0f, 2.0f, 3.0f);
TCVec<fp32, 3> Velocity(0.5f, -1.0f, 0.0f);

TCVec<fp32, 3> NewPosition = Position + Velocity;
fp32 Distance = Position.f_Length();
TCVec<fp32, 3> Normalized = Position.f_Normalized();

// N-dimensional vectors
TCVec<fp64, 10> HighDimVector;
HighDimVector[5] = 3.14;
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
- Vector operations may use SIMD when available
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
- SIMD instructions for vector operations (when available)
