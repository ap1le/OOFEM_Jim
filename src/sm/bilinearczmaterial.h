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
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef bilinearczmaterial_h
#define bilinearczmaterial_h

#include "structuralmaterial.h"
#include "structuralms.h"

///@name Input fields for BilinearCZMaterial
//@{
#define _IFT_BilinearCZMaterial_kn "kn"
#define _IFT_BilinearCZMaterial_ks "ks"
#define _IFT_BilinearCZMaterial_knc "knc"
#define _IFT_BilinearCZMaterial_g1c "g1c"
#define _IFT_BilinearCZMaterial_sigfn "sigfn"
#define _IFT_BilinearCZMaterial_sigfs "sigfs"
//#define _IFT_IsoInterfaceDamageMaterial_gf "gf"
//#define _IFT_IsoInterfaceDamageMaterial_maxOmega "maxomega"
//#define _IFT_IsoInterfaceDamageMaterial_talpha "talpha"
//@}

namespace oofem {
//class IntegrationPoint;

/**
 * This class implements associated Material Status to IsoInterfaceDamageMaterial.
 */
class BilinearCZMaterialStatus : public StructuralMaterialStatus
{
protected:
    /// Scalar measure of the largest equivalent displacement ever reached in material.
    //double kappa;

public:
    /// Constructor
    BilinearCZMaterialStatus(int n, Domain *d, GaussPoint *g);
    /// Destructor
    virtual ~BilinearCZMaterialStatus();

    virtual void printOutputAt(FILE *file, TimeStep *tStep);

    /// Returns the last equilibrated scalar measure of the largest strain level.
    //double giveKappa() { return kappa; }
    
    //void setTempDamage(double newDamage) { tempDamage = newDamage; }

    // definition
    virtual const char *giveClassName() const { return "BilinearCZMaterialStatus"; }
    virtual classType giveClassID() const { return MaterialStatusClass; }

    virtual void initTempStatus();
    virtual void updateYourself(TimeStep *tStep);

    //virtual contextIOResultType saveContext(DataStream *stream, ContextMode mode, void *obj = NULL);
    //virtual contextIOResultType restoreContext(DataStream *stream, ContextMode mode, void *obj = NULL);
};


/**
 * Simple isotropic damage based model for 2d interface elements.
 * In 2d, the interface elements are used to model contact layer between
 * element edges. The generalized strain vector contains two relative displacements
 * (in normal and shear direction). The generalized stress vector contains corresponding
 * tractions in normal and tangent direction.
 *
 * The behaviour of the model is elastic, described by normal and shear stiffness components.
 * Isotropic damage is initiated  when the stress reaches the tensile strength. Damage evolution
 * is governed by normal component of generalized strain vector (normal relative displacement)
 * by an exponential softening law.
 */
class BilinearCZMaterial : public StructuralMaterial
{
protected:
    /// Material parameters
    double kn0;
    double ks0;
    double knc;   // stiffness in compression  
    double GIc;
    double sigfn;
    double sigfs;

    double gn0;   // normal jump at damage initiation
    double gs0;   // shear jump at damage initiations
    double gnmax; // max normal jump

    double kn1;   // slope during softening part

    virtual int checkConsistency();
    void give3dInterfaceMaterialStiffnessMatrix(FloatMatrix &answer, MatResponseForm form, MatResponseMode rMode,
                                                                     GaussPoint *gp, TimeStep *atTime);
public:
    /// Constructor
    BilinearCZMaterial(int n, Domain *d);
    /// Destructor
    virtual ~BilinearCZMaterial();

    virtual int hasNonLinearBehaviour()   { return 1; }

    virtual int hasMaterialModeCapability(MaterialMode mode);
    virtual const char *giveClassName() const { return "BilinearCZMaterial"; }
    virtual classType giveClassID() const { return BilinearCZMaterialClass; }

    

    virtual void giveRealStressVector(FloatArray &answer, MatResponseForm form, GaussPoint *gp,
                              const FloatArray &reducedStrain, TimeStep *tStep);

    virtual void giveCharacteristicMatrix(FloatMatrix &answer,
                                          MatResponseForm form,
                                          MatResponseMode mode,
                                          GaussPoint *gp,
                                          TimeStep *tStep);
    
    virtual int giveIPValue(FloatArray &answer, GaussPoint *gp, InternalStateType type, TimeStep *tStep);
    virtual int giveIntVarCompFullIndx(IntArray &answer, InternalStateType type, MaterialMode mmode);
    virtual InternalStateValueType giveIPValueType(InternalStateType type);
    virtual int giveIPValueSize(InternalStateType type, GaussPoint *gp);
    //virtual void giveThermalDilatationVector(FloatArray &answer, GaussPoint *gp, TimeStep *tStep);


    virtual IRResultType initializeFrom(InputRecord *ir);
    
    virtual MaterialStatus *CreateStatus(GaussPoint *gp) const { return new BilinearCZMaterialStatus(1, domain, gp); }

protected:
   
};
} // end namespace oofem
#endif // isointerfacedamage01_h