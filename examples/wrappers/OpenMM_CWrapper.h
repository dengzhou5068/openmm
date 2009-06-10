// -----------------------------------------------------------------------------
//        OpenMM(tm) example C wrapper function declarations (June 2009)
// -----------------------------------------------------------------------------
// This header should be included by a C main program that would like to
// access the OpenMM API through the C wrappers. Please note that this is not
// an official part of OpenMM; it is just an example of how the C++ API can be
// wrapped for access from C.
// -----------------------------------------------------------------------------

#ifndef OPENMM_CWRAPPER_H
#define OPENMM_CWRAPPER_H

#if defined(__cplusplus)
    #include <cmath>
#else
    #include <math.h>
#endif

/*
 * This header file is intended to be included in a C compilation unit so must
 * not use any C++ features that are not also present in ANSI C.
 */

/* These incomplete types are declared so we can have unique pointer types. */
typedef struct OpenMM_System_s      OpenMM_System;
typedef struct OpenMM_Context_s     OpenMM_Context;
typedef double                      OpenMM_Vec3[3];
typedef struct OpenMM_Vec3Array_s   OpenMM_Vec3Array;
typedef struct OpenMM_String_s      OpenMM_String;

/*
 * OpenMM_Integrator is the generic type for all integrators. Cast your
 * specific pointer type to the generic one for communication with functions
 * that take type OpenMM_Integrator.
 */
typedef struct OpenMM_Integrator_s         OpenMM_Integrator;
typedef struct OpenMM_VerletIntegrator_s        OpenMM_VerletIntegrator;
typedef struct OpenMM_LangevinIntegrator_s      OpenMM_LangevinIntegrator;

/*
 * OpenMM_Force is the generic type for all Force objects. Create the
 * concrete Force object and then cast it to the generic type.
 */
typedef struct OpenMM_Force_s               OpenMM_Force;
typedef struct OpenMM_NonbondedForce_s          OpenMM_NonbondedForce;
typedef struct OpenMM_GBSAOBCForce_s            OpenMM_GBSAOBCForce;

typedef enum {
    OpenMM_NonbondedForce_NoCutoff            = 0,
    OpenMM_NonbondedForce_CutoffNonPeriodic   = 1,
    OpenMM_NonbondedForce_CutoffPeriodic      = 2,
    OpenMM_NonbondedForce_Ewald               = 3
} OpenMM_NonbondedForce_NonbondedMethod;


typedef struct OpenMM_State_s               OpenMM_State;
typedef enum {
    OpenMM_State_Positions   = 1, 
    OpenMM_State_Velocities  = 2,
    OpenMM_State_Forces      = 4,
    OpenMM_State_Energy      = 8,
    OpenMM_State_Parameters  = 16
} OpenMM_State_DataType;

/* Conversion constants from openmm/Units.h */

/*
 * The number of nanometers in an Angstrom.
 */
static const double OpenMM_NmPerAngstrom = 0.1;
/*
 * The number of Angstroms in a nanometer.
 */
static const double OpenMM_AngstromsPerNm = 10.0;
/*
 * The number of picoseconds in a femtosecond.
 */
static const double OpenMM_PsPerFs = 0.001;
/*
 * The number of femtoseconds in a picosecond.
 */
static const double OpenMM_FsPerPs = 1000.0;
/*
 * The number of kJ in a kcal.
 */
static const double OpenMM_KJPerKcal = 4.184;
/*
 * The number of kcal in a kJ.
 */
static const double OpenMM_KcalPerKJ = 1.0/4.184;
/*
 * The number of radians in a degree.
 */
static const double OpenMM_RadiansPerDegree = 3.1415926535897932385/180.0;
/*
 * The number of degrees in a radian.
 */
static const double OpenMM_DegreesPerRadian = 180.0/3.1415926535897932385;
/*
 * This is the conversion factor that takes you from a van der Waals radius
 * (defined as 1/2 the minimum energy separation) to the related Lennard Jones 
 * "sigma" parameter (defined as the zero crossing separation). The value
 * is 2*pow(2, -1/6).
 */
static const double OpenMM_SigmaPerVdwRadius = 1.78179743628068;


#if defined(__cplusplus)
extern "C" {
#endif

/* OpenMM_Vec3Array */
extern OpenMM_Vec3Array*    OpenMM_Vec3Array_create(int n);
extern int                  OpenMM_Vec3Array_size(const OpenMM_Vec3Array*);
extern void                 OpenMM_Vec3Array_resize(OpenMM_Vec3Array*, int n);
extern void                 OpenMM_Vec3Array_destroy(OpenMM_Vec3Array*);
extern void                 OpenMM_Vec3Array_append(OpenMM_Vec3Array*, const double[3]);
extern void                 OpenMM_Vec3Array_get(const OpenMM_Vec3Array*, int i, double[3]);

/* OpenMM_String */
extern OpenMM_String*       OpenMM_String_create(const char* init);
extern void                 OpenMM_String_destroy(OpenMM_String*);
extern int                  OpenMM_String_length(const OpenMM_String*);
extern const char*          OpenMM_String_getAsC(const OpenMM_String*);
extern void                 OpenMM_String_get(const OpenMM_String*, char* buf, int buflen);
extern void                 OpenMM_String_set(OpenMM_String*, const char* buf);

/* OpenMM::Platform */
extern void OpenMM_Platform_loadPluginsFromDirectory(const char*);
extern const char* OpenMM_Platform_getDefaultPluginsDirectory();

/* OpenMM::System */

extern OpenMM_System* OpenMM_System_create();
extern void OpenMM_System_destroy (OpenMM_System*);
extern void OpenMM_System_addForce(OpenMM_System*, OpenMM_Force*);
extern void OpenMM_System_addParticle(OpenMM_System*, double mass);


/* OpenMM::NonbondedForce */
extern OpenMM_NonbondedForce* OpenMM_NonbondedForce_create();
extern void OpenMM_NonbondedForce_destroy              (OpenMM_NonbondedForce*);
extern void OpenMM_NonbondedForce_setNonbondedMethod   (OpenMM_NonbondedForce*, 
                                                        OpenMM_NonbondedForce_NonbondedMethod);
extern void OpenMM_NonbondedForce_setCutoffDistance    (OpenMM_NonbondedForce*, double);
extern void OpenMM_NonbondedForce_setPeriodicBoxVectors(OpenMM_NonbondedForce*, 
                                                        const OpenMM_Vec3,const OpenMM_Vec3,const OpenMM_Vec3);
extern void OpenMM_NonbondedForce_addParticle(OpenMM_NonbondedForce*,
                                              double charge,
                                              double sigmaInNm,
                                              double vdwEnergyInKJ);

/* OpenMM::GBSAOBCForce */
extern OpenMM_GBSAOBCForce* OpenMM_GBSAOBCForce_create();
extern void OpenMM_GBSAOBCForce_destroy             (OpenMM_GBSAOBCForce*);
extern void OpenMM_GBSAOBCForce_setSolventDielectric(OpenMM_GBSAOBCForce*, double);
extern void OpenMM_GBSAOBCForce_setSoluteDielectric (OpenMM_GBSAOBCForce*, double);
extern void OpenMM_GBSAOBCForce_addParticle(OpenMM_GBSAOBCForce*,
                                            double charge,
                                            double radiusInNm,
                                            double scalingFactor);

/* OpenMM::Integrator */
extern void OpenMM_Integrator_step(OpenMM_Integrator*, int numSteps);
extern void OpenMM_Integrator_destroy(OpenMM_Integrator*);
/* OpenMM::VerletIntegrator */
extern OpenMM_VerletIntegrator* OpenMM_VerletIntegrator_create(double stepSzInPs);
extern void                     OpenMM_VerletIntegrator_destroy(OpenMM_VerletIntegrator*);
extern void                     OpenMM_VerletIntegrator_step(OpenMM_VerletIntegrator*, int numSteps);
/* OpenMM::LangevinIntegrator */
extern OpenMM_LangevinIntegrator* OpenMM_LangevinIntegrator_create(double temperature, double frictionInPs, double stepSzInPs);
extern void                       OpenMM_VLangevinIntegrator_destroy(OpenMM_LangevinIntegrator*);
extern void                       OpenMM_LangevinIntegrator_step(OpenMM_LangevinIntegrator*, int numSteps);

/* OpenMM::Context */
extern OpenMM_Context*  OpenMM_Context_create(OpenMM_System*, OpenMM_Integrator*);
extern void             OpenMM_Context_destroy(OpenMM_Context*);
extern void             OpenMM_Context_setPositions(OpenMM_Context*, const OpenMM_Vec3Array*);
extern void             OpenMM_Context_setVelocities(OpenMM_Context*, const OpenMM_Vec3Array*);
extern OpenMM_State*    OpenMM_Context_createState(const OpenMM_Context*, int types);
extern const char*      OpenMM_Context_getPlatformName(const OpenMM_Context*);
extern double           OpenMM_Context_getTime(OpenMM_Context*);

/* OpenMM::State */
extern void     OpenMM_State_destroy(OpenMM_State*);
extern double   OpenMM_State_getTime(const OpenMM_State*);
extern double   OpenMM_State_getPotentialEnergy(const OpenMM_State*);
extern double   OpenMM_State_getKineticEnergy(const OpenMM_State*);
extern const OpenMM_Vec3Array* OpenMM_State_getPositions(const OpenMM_State*);
extern const OpenMM_Vec3Array* OpenMM_State_getVelocities(const OpenMM_State*);


#if defined(__cplusplus)
}
#endif


static void OpenMM_Vec3_scale(const OpenMM_Vec3 in, double s, OpenMM_Vec3 out) {
    out[0] = in[0]*s; out[1] = in[1]*s; out[2] = in[2]*s;
}

static void OpenMM_Vec3_set(double x, double y, double z, OpenMM_Vec3 out) {
    out[0] = x; out[1] = y; out[2] = z;
}


#endif /*OPENMM_CWRAPPER_H*/




