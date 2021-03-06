/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2013   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef fei3dtriquad_h
#define fei3dtriquad_h

#include "feinterpol3d.h"

namespace oofem {
/**
 * Second order triangular interpolation in 3D space (6 nodes).
 * @todo This class is entirely unchecked.
 * @author Jim Brouzoulis
 * @author Mikael Öhman
 */
class OOFEM_EXPORT FEI3dTrQuad : public FEInterpolation3d
{
public:
    FEI3dTrQuad() : FEInterpolation3d(2) { }

    virtual integrationDomain giveIntegrationDomain() const { return _Triangle; }
    virtual Element_Geometry_Type giveGeometryType() const { return EGT_triangle_2; }

    // Bulk
    virtual void evalN(FloatArray &answer, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual double evaldNdx(FloatMatrix &answer, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual void local2global(FloatArray &answer, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual int  global2local(FloatArray &answer, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual double giveTransformationJacobian(const FloatArray &lcoords, const FEICellGeometry &cellgeo);

    // new methods
    void giveDerivativeXi(FloatArray &n, const FloatArray &lcoords);
    void giveDerivativeEta(FloatArray &n, const FloatArray &lcoords);
    virtual void giveLocalNodeCoords(FloatMatrix &answer);
    virtual void evaldNdxi(FloatMatrix &answer, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    void surfaceEvaldNdxi(FloatMatrix &answer, const FloatArray &lcoords);

    // Edge
    virtual void edgeEvalN(FloatArray &answer, int iedge, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    void edgeEvaldNdxi(FloatArray &answer, int iedge, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual void edgeEvaldNdx(FloatMatrix &answer, int iedge,
                              const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual void edgeLocal2global(FloatArray &answer, int iedge,
                                  const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual double edgeGiveTransformationJacobian(int iedge, const FloatArray &lcoords,
                                                  const FEICellGeometry &cellgeo);
    virtual void computeLocalEdgeMapping(IntArray &edgeNodes, int iedge);

    virtual int giveNumberOfEdges() const { return 3; };

    // Surface
    virtual void surfaceEvalN(FloatArray &answer, int isurf, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual void surfaceEvaldNdx(FloatMatrix &answer, int isurf,
                                 const FloatArray &lcoords, const FEICellGeometry &cellgeo);

    virtual double surfaceEvalNormal(FloatArray &answer, int isurf, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual void surfaceLocal2global(FloatArray &answer, int isurf,
                                     const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual double surfaceGiveTransformationJacobian(int isurf, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual void computeLocalSurfaceMapping(IntArray &edgeNodes, int iedge);
    void surfaceEvalBaseVectorsAt(FloatArray &G1, FloatArray &G2, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
    virtual void surfaceGiveJacobianMatrixAt(FloatMatrix &jacobianMatrix, const FloatArray &lcoords, const FEICellGeometry &cellgeo);

    virtual IntegrationRule *giveIntegrationRule(int order);
    virtual IntegrationRule *giveBoundaryIntegrationRule(int order, int boundary);
    double giveArea(const FEICellGeometry &cellgeo) const;

protected:
    double edgeComputeLength(IntArray &edgeNodes, const FEICellGeometry &cellgeo);

    double computeVolume(const FEICellGeometry &cellgeo);

    virtual void giveJacobianMatrixAt(FloatMatrix &jacobianMatrix, const FloatArray &lcoords, const FEICellGeometry &cellgeo);
};
} // end namespace oofem
#endif // fei3dtetquad_h
