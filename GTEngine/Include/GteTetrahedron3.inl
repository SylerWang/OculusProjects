// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Tetrahedron3<Real>::Tetrahedron3()
{
    v[0] = Vector3<Real>::Zero();
    v[1] = Vector3<Real>::Basis0();
    v[2] = Vector3<Real>::Basis1();
    v[3] = Vector3<Real>::Basis2();
}
//----------------------------------------------------------------------------
template <typename Real>
Tetrahedron3<Real>::Tetrahedron3(Vector3<Real> const& v0,
    Vector3<Real> const& v1, Vector3<Real> const& v2, Vector3<Real> const& v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}
//----------------------------------------------------------------------------
template <typename Real>
Tetrahedron3<Real>::Tetrahedron3(Vector3<Real> const inV[4])
{
    for (int i = 0; i < 4; ++i)
    {
        v[i] = inV[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void Tetrahedron3<Real>::GetFaceIndices(int face, int index[3])
    const
{
    if (face == 0)
    {
        index[0] = 0;
        index[1] = 2;
        index[2] = 1;
    }
    else if (face == 1)
    {
        index[0] = 0;
        index[1] = 1;
        index[2] = 3;
    }
    else if (face == 2)
    {
        index[0] = 0;
        index[1] = 3;
        index[2] = 2;
    }
    else  // face == 3 (no index validation is performed)
    {
        index[0] = 1;
        index[1] = 2;
        index[2] = 3;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void Tetrahedron3<Real>::GetPlanes(Plane3<Real> plane[4]) const
{
    Vector3<Real> edge10 = v[1] - v[0];
    Vector3<Real> edge20 = v[2] - v[0];
    Vector3<Real> edge30 = v[3] - v[0];
    Vector3<Real> edge21 = v[2] - v[1];
    Vector3<Real> edge31 = v[3] - v[1];

    plane[0].normal = UnitCross(edge20, edge10);  // <v0,v2,v1>
    plane[1].normal = UnitCross(edge10, edge30);  // <v0,v1,v3>
    plane[2].normal = UnitCross(edge30, edge20);  // <v0,v3,v2>
    plane[3].normal = UnitCross(edge21, edge31);  // <v1,v2,v3>

    Real det = Dot(edge10, plane[3].normal);
    if (det < (Real)0)
    {
        // The normals are inner pointing, reverse their directions.
        for (int i = 0; i < 4; ++i)
        {
            plane[i].normal = -plane[i].normal;
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        plane[i].constant = Dot(v[i], plane[i].normal);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
bool Tetrahedron3<Real>::IsEqualTo(Tetrahedron3 const& tetrahedron) const
{
    return v[0] == tetrahedron.v[0]
        && v[1] == tetrahedron.v[1]
        && v[2] == tetrahedron.v[2]
        && v[3] == tetrahedron.v[3];
}
//----------------------------------------------------------------------------
template <typename Real>
bool Tetrahedron3<Real>::IsLessThan(Tetrahedron3 const& tetrahedron) const
{
    for (int i = 0; i < 4; ++i)
    {
        if (v[i] < tetrahedron.v[i])
        {
            return true;
        }

        if (v[i] > tetrahedron.v[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
