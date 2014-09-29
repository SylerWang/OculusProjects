// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include <xmmintrin.h>
#include <emmintrin.h>
#include <cmath>
#include <cstdint>

namespace gte
{
// Support for Intel's Streaming SIMD Extensions (SSE) using 128-bit registers
// that store four 32-bit floating-point numbers.
class GTE_IMPEXP SIMD
{
public:
    // The representation of the SIMD 4-tuple.
    class GTE_IMPEXP Vector
    {
    public:
        // Information about vectors.
        enum { NUM_ELEMENTS = 4 };
        typedef float ElementType;

        // Construction.
        Vector ();
        Vector (Vector const& vec);
        Vector (__m128 const vec);
        Vector (__m128i const vec);
        Vector (float number);
        Vector (float n0, float n1, float n2, float n3);
        Vector (uint32_t encoding);
        Vector (uint32_t e0, uint32_t e1, uint32_t e2, uint32_t e3);

        // Assignment.
        Vector& operator= (Vector const& vec);
        Vector& operator= (__m128 const vec);
        Vector& operator= (__m128i const vec);

        // Implicit conversions.
        operator __m128 ();
        operator __m128 () const;
        operator __m128i ();
        operator __m128i () const;

    protected:
        __m128 mTuple;
    };

    // The representation of the SIMD 4x4-table.
    class GTE_IMPEXP Matrix
    {
    public:
        // Information about matrices.
        enum
        {
            NUM_ROWS = 4,
            NUM_COLS = 4,
            NUM_ELEMENTS = 16,
#if defined(GTE_USE_ROW_MAJOR)
            STORAGE_ROW_MAJOR = 1,
#else
            STORAGE_ROW_MAJOR = 0,
#endif
        };
        typedef float ElementType;

        // Construction.
        Matrix ();
        Matrix (Matrix const& mat);
        Matrix (__m128 const* mat);
        Matrix (
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);

        // Assignment.
        Matrix& operator= (Matrix const& mat);
        Matrix& operator= (__m128 const* mat);

        // Implicit conversions.
        operator __m128* ();
        operator __m128 const* () const;

        // Access to the slices (rows or columns) of the matrix.
        __m128 const& operator[] (int i) const;
        __m128& operator[] (int i);

    protected:
        // mTable[i] is row i for row-major storage but is column i for
        // column-major order.
        __m128 mTable[4];
    };

public:
    // Logical operations.
    inline static __m128 Not (__m128 const v);                          // ~v
    inline static __m128 And (__m128 const v0, __m128 const v1);        // v0 & v1
    inline static __m128 AndNot (__m128 const v0, __m128 const v1);     // ~v0 & v1
    inline static __m128 Or (__m128 const v0, __m128 const v1);         // v0 | v1
    inline static __m128 Xor (__m128 const v0, __m128 const v1);        // v0 ^ v1
    inline static __m128 Select (__m128 const c, __m128 const v0, __m128 const v1); // (c & v0) | (~c & v1)

    // Comparisons.
    inline static __m128 Equal (__m128 const v0, __m128 const v1);          // v0 == v1
    inline static __m128 NotEqual (__m128 const v0, __m128 const v1);       // v0 != v1
    inline static __m128 Less (__m128 const v0, __m128 const v1);           // v0 < v1
    inline static __m128 LessEqual (__m128 const v0, __m128 const v1);      // v0 <= v1
    inline static __m128 Greater (__m128 const v0, __m128 const v1);        // v0 > v1
    inline static __m128 GreaterEqual (__m128 const v0, __m128 const v1);   // v0 >= v1

    // Vector arithmetic operations.
    inline static __m128 Negate (__m128 const v);                       // -v
    inline static __m128 Add (__m128 const v0, __m128 const v1);        // v0 + v1
    inline static __m128 Subtract (__m128 const v0, __m128 const v1);   // v0 - v1
    inline static __m128 Multiply (__m128 const v0, __m128 const v1);   // v0 * v1
    inline static __m128 Divide (__m128 const v0, __m128 const v1);     // v0 / v1
    inline static __m128 Round (__m128 const v);
    inline static __m128 MaximumAbsoluteComponent (__m128 const v);

    // Vector algebraic operations.
    inline static __m128 Dot (__m128 const v0, __m128 const v1);
    inline static __m128 Length (__m128 const v);
    inline static __m128 LengthRobust (__m128 const v);
    inline static __m128 Normalize (__m128 const v);
    inline static __m128 NormalizeGetLength (__m128 const v, __m128& length);
    inline static __m128 NormalizeRobust (__m128 const v);
    inline static __m128 NormalizeRobustGetLength (__m128 const v, __m128& length);
    inline static __m128 Cross (__m128 const v0, __m128 const v1);

    // Matrix arithmetic operations.
    inline static void Negate (__m128 const* M, __m128* result);
    inline static void Add (__m128 const* A, __m128 const*B, __m128* result);
    inline static void Subtract (__m128 const* A, __m128 const* B, __m128* result);
    inline static void Multiply (__m128 const* M, __m128 const c, __m128* result);
    inline static void Divide (__m128 const* M, __m128 const c, __m128* result);

    // Matrix geometric operations.
    inline static void Transpose (__m128 const* mat, __m128* trn);
    inline static void Inverse (__m128 const* mat, __m128* inv);
    inline static void Adjoint (__m128 const* mat, __m128* adj);
    inline static __m128 Determinant (__m128 const* mat);
    inline static __m128 L1Norm (__m128 const* mat);
    inline static __m128 L2Norm (__m128 const* mat);
    inline static __m128 LInfinityNorm (__m128 const* mat);

    // Matrix-matrix products.
    inline static void MultiplyAB (__m128 const* A, __m128 const* B, __m128* AB);
    inline static void MultiplyATB (__m128 const* A, __m128 const* B, __m128* ATB);
    inline static void MultiplyABT (__m128 const* A, __m128 const* B, __m128* ABT);
    inline static void MultiplyATBT (__m128 const* A, __m128 const* B, __m128* ATBT);
    inline static void MultiplyDM (__m128 const D, __m128 const* M, __m128* DM);
    inline static void MultiplyMD (__m128 const* M, __m128 const D, __m128* MD);

    // Matrix-vector products.
    inline static __m128 MultiplyMV (__m128 const* M, __m128 const V);
    inline static __m128 MultiplyVM (__m128 const V, __m128 const* M);

    // Quaternion support.  In QSlerp, the 't' component must be the splat of
    // a floating-point scalar in [0,1], and q0 and q1 must be unit-length
    // quaternions.
    inline static __m128 QMultiply (__m128 const q0, __m128 const q1);
    inline static __m128 QConjugate (__m128 const q);
    inline static __m128 QInverse (__m128 const q);
    inline static __m128 QSlerp (__m128 const t, __m128 const q0, __m128 const q1);

    // Function evaluations (generally slow, CPU function call per component).
    inline static __m128 Sin (__m128 const v);
    inline static __m128 Cos (__m128 const v);
    inline static __m128 Tan (__m128 const v);
    inline static __m128 ASin (__m128 const v);
    inline static __m128 ACos (__m128 const v);
    inline static __m128 ATan (__m128 const v);

    // Fast function approximations.

    // The SinAppr* functions require |x| <= pi/2.  When x is in this domain,
    // just call SinAppr*(x).  When x is not in the domain, call
    // ReduceAnglesSin(x,y) to obtain y in the domain with sin(x) = sin(y),
    // and then call SinAppr*(y).
    inline static void ReduceAnglesSin (__m128 const x, __m128& y);
    inline static __m128 SinApprDeg11 (__m128 const x);
    inline static __m128 SinApprDeg7 (__m128 const x);

    // The CosAppr* functions require |x| <= pi/2.  When x is in this domain,
    // just call CosAppr*(x, Float4SEE::PPP).  When x is not in the domain,
    // call ReduceAnglesCos(x,y,sign) to obtain y in the domain with cos(x) =
    // sign*cos(y), and then call CosAppr*(y,sign).
    inline static void ReduceAnglesCos (__m128 const x, __m128& y, __m128& sign);
    inline static __m128 CosApprDeg10 (__m128 const x, __m128 const sign);
    inline static __m128 CosApprDeg6 (__m128 const x, __m128 const sign);

    // Integer masks.
    static Vector const ZZZZ;  // (0x00000000, 0x00000000, 0x00000000, 0x00000000)
    static Vector const ZZZF;  // (0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF)
    static Vector const ZZFZ;  // (0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000)
    static Vector const ZZFF;  // (0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF)
    static Vector const ZFZZ;  // (0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000)
    static Vector const ZFZF;  // (0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF)
    static Vector const ZFFZ;  // (0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000)
    static Vector const ZFFF;  // (0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF)
    static Vector const FZZZ;  // (0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000)
    static Vector const FZZF;  // (0xFFFFFFFF, 0x00000000, 0x00000000, 0xFFFFFFFF)
    static Vector const FZFZ;  // (0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000)
    static Vector const FZFF;  // (0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF)
    static Vector const FFZZ;  // (0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000)
    static Vector const FFZF;  // (0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF)
    static Vector const FFFZ;  // (0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000)
    static Vector const FFFF;  // (0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF)
    static Vector const SIGN;  // (0x80000000, 0x80000000, 0x80000000, 0x80000000)
    static Vector const NSIGN; // (0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF)
    static Vector const NOFRC; // (0x00800000, 0x00800000, 0x00800000, 0x00800000)

    // Numeric constants.
    static Vector const PZZZ;  // (+1.0f,  0.0f,  0.0f,  0.0f)
    static Vector const ZPZZ;  // ( 0.0f, +1.0f,  0.0f,  0.0f)
    static Vector const ZZPZ;  // ( 0.0f,  0.0f, +1.0f,  0.0f)
    static Vector const ZZZP;  // ( 0.0f,  0.0f,  0.0f, +1.0f)
    static Vector const MZZZ;  // (-1.0f,  0.0f,  0.0f,  0.0f)
    static Vector const ZMZZ;  // ( 0.0f, -1.0f,  0.0f,  0.0f)
    static Vector const ZZMZ;  // ( 0.0f,  0.0f, -1.0f,  0.0f)
    static Vector const ZZZM;  // ( 0.0f,  0.0f,  0.0f, -1.0f)
    static Vector const MMMM;  // (-1.0f, -1.0f, -1.0f, -1.0f)
    static Vector const MMMP;  // (-1.0f, -1.0f, -1.0f, +1.0f)
    static Vector const MMPM;  // (-1.0f, -1.0f, +1.0f, -1.0f)
    static Vector const MMPP;  // (-1.0f, -1.0f, +1.0f, +1.0f)
    static Vector const MPMM;  // (-1.0f, +1.0f, -1.0f, -1.0f)
    static Vector const MPMP;  // (-1.0f, +1.0f, -1.0f, +1.0f)
    static Vector const MPPM;  // (-1.0f, +1.0f, +1.0f, -1.0f)
    static Vector const MPPP;  // (-1.0f, +1.0f, +1.0f, +1.0f)
    static Vector const PMMM;  // (+1.0f, -1.0f, -1.0f, -1.0f)
    static Vector const PMMP;  // (+1.0f, -1.0f, -1.0f, +1.0f)
    static Vector const PMPM;  // (+1.0f, -1.0f, +1.0f, -1.0f)
    static Vector const PMPP;  // (+1.0f, -1.0f, +1.0f, +1.0f)
    static Vector const PPMM;  // (+1.0f, +1.0f, -1.0f, -1.0f)
    static Vector const PPMP;  // (+1.0f, +1.0f, -1.0f, +1.0f)
    static Vector const PPPM;  // (+1.0f, +1.0f, +1.0f, -1.0f)
    static Vector const PPPP;  // (+1.0f, +1.0f, +1.0f, +1.0f)
    static Vector const UNIT[4];  // = {PZZZ, ZPZZ, ZZPZ, ZZZP};

    // Constants involving pi.
    static Vector const PI;
    static Vector const HALF_PI;
    static Vector const TWO_PI;
    static Vector const INV_PI;
    static Vector const INV_TWO_PI;

private:
    // Support for computing the adjoint, determinanat, and inverse.
    inline static void GetAdjDet (__m128 const* mat, __m128* adj, __m128* det);

    // Constants to support approximations of sin(x).
    static Vector const C_SIN_APPR_DEG11_0;
    static Vector const C_SIN_APPR_DEG11_1;
    static Vector const C_SIN_APPR_DEG11_2;
    static Vector const C_SIN_APPR_DEG11_3;
    static Vector const C_SIN_APPR_DEG11_4;
    static Vector const C_SIN_APPR_DEG11_5;
    static Vector const C_SIN_APPR_DEG7_0;
    static Vector const C_SIN_APPR_DEG7_1;
    static Vector const C_SIN_APPR_DEG7_2;
    static Vector const C_SIN_APPR_DEG7_3;

    // Constants to support approximations of cos(x).
    static Vector const C_COS_APPR_DEG10_0;
    static Vector const C_COS_APPR_DEG10_1;
    static Vector const C_COS_APPR_DEG10_2;
    static Vector const C_COS_APPR_DEG10_3;
    static Vector const C_COS_APPR_DEG10_4;
    static Vector const C_COS_APPR_DEG10_5;
    static Vector const C_COS_APPR_DEG6_0;
    static Vector const C_COS_APPR_DEG6_1;
    static Vector const C_COS_APPR_DEG6_2;
    static Vector const C_COS_APPR_DEG6_3;
};

#include "GteIntelSSE.inl"

}
