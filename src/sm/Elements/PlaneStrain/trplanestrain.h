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

#ifndef trplanstrain_h
#define trplanstrain_h

#include "Elements/structural2delement.h"
#include "ErrorEstimators/directerrorindicatorrc.h"
#include "ErrorEstimators/zzerrorestimator.h"
#include "ErrorEstimators/huertaerrorestimator.h"
#include "zznodalrecoverymodel.h"
#include "nodalaveragingrecoverymodel.h"
#include "sprnodalrecoverymodel.h"
#include "spatiallocalizer.h"
#include "eleminterpmapperinterface.h"
#include "mmashapefunctprojection.h"

#define _IFT_TrPlaneStrain_Name "trplanestrain"

namespace oofem {
class FEI2dTrLin;

/**
 * This class implements an triangular three-node  plane-
 * strain elasticity finite element. Each node has 2 degrees of freedom.
 */
class TrPlaneStrain : public PlaneStrainElement, public ZZNodalRecoveryModelInterface,
public NodalAveragingRecoveryModelInterface, public SPRNodalRecoveryModelInterface,
public SpatialLocalizerInterface,
public EIPrimaryUnknownMapperInterface,
public ZZErrorEstimatorInterface,
public HuertaErrorEstimatorInterface
{
protected:
    static FEI2dTrLin interp;
    double area;

public:
    TrPlaneStrain(int n, Domain * d);
    virtual ~TrPlaneStrain() { }

    virtual FEInterpolation *giveInterpolation() const;
    virtual Interface *giveInterface(InterfaceType it);

    virtual void NodalAveragingRecoveryMI_computeNodalValue(FloatArray &answer, int node,
                                                            InternalStateType type, TimeStep *tStep);

    virtual void SPRNodalRecoveryMI_giveSPRAssemblyPoints(IntArray &pap);
    virtual void SPRNodalRecoveryMI_giveDofMansDeterminedByPatch(IntArray &answer, int pap);
    virtual int SPRNodalRecoveryMI_giveNumberOfIP();
    virtual SPRPatchType SPRNodalRecoveryMI_givePatchType();

    virtual void EIPrimaryUnknownMI_computePrimaryUnknownVectorAtLocal(ValueModeType mode,
                                                                       TimeStep *tStep, const FloatArray &lcoords,
                                                                       FloatArray &answer);

    // HuertaErrorEstimatorInterface
    virtual void HuertaErrorEstimatorI_setupRefinedElementProblem(RefinedElement *refinedElement, int level, int nodeId,
                                                                  IntArray &localNodeIdArray, IntArray &globalNodeIdArray,
                                                                  HuertaErrorEstimatorInterface :: SetupMode sMode, TimeStep *tStep,
                                                                  int &localNodeId, int &localElemId, int &localBcId,
                                                                  IntArray &controlNode, IntArray &controlDof,
                                                                  HuertaErrorEstimator :: AnalysisMode aMode);
    virtual void HuertaErrorEstimatorI_computeNmatrixAt(GaussPoint *gp, FloatMatrix &answer);

#ifdef __OOFEG
    virtual void drawRawGeometry(oofegGraphicContext &gc, TimeStep *tStep);
    virtual void drawDeformedGeometry(oofegGraphicContext &gc, TimeStep *tStep, UnknownType);
    virtual void drawScalar(oofegGraphicContext &gc, TimeStep *tStep);
#endif

    // definition & identification
    virtual const char *giveInputRecordName() const { return _IFT_TrPlaneStrain_Name; }
    virtual const char *giveClassName() const { return "TrPlaneStrain"; }
    virtual IRResultType initializeFrom(InputRecord *ir);

protected:
    virtual int giveNumberOfIPForMassMtrxIntegration() { return 1; }
};
} // end namespace oofem
#endif // trplanstrain_h
