////////////////////////////////////////////////////////////////////////
/// \file    SRTrueInteraction.h
/// \brief   True neutrino/cosmic (or other top-level particle) interaction
/// \author  J. Wolcott <jwolcott@fnal.gov>  [but mostly copied from NOvA/SBN sources]

#ifndef DUNEANAOBJ_SRTRUEINTERACTION_H
#define DUNEANAOBJ_SRTRUEINTERACTION_H

#include <limits>

#include "duneanaobj/StandardRecord/SRTrueParticle.h"
#include "duneanaobj/StandardRecord/SRVector3D.h"

namespace caf
{
   /// Known generators of neutrino interactions (extend as other generators are used)
   enum class Generator
   {
     kUnknownGenerator = 0,
     kGENIE            = 1,
     kGIBUU            = 2,
     kNEUT             = 3
   };

  /// \brief Neutrino interaction categories.
  /// These values are taken from nusimdata/SimulationBase/MCNeutrino.h (where
  /// they are probably copied from some genie header). Duplicating that
  /// information here is sub-optimal, but less sub-optimal than adding a
  /// dependency on larsoft to interpret the CAFss.
  enum class ScatteringMode
   {
     kUnknownMode               = -1,
     kQE                        = 0,
     kRes                       = 1,
     kDIS                       = 2,
     kCoh                       = 3,
     kCohElastic                = 4,
     kElectronScattering        = 5,
     kIMDAnnihilation           = 6,
     kInverseBetaDecay          = 7,
     kGlashowResonance          = 8,
     kAMNuGamma                 = 9,
     kMEC                       = 10,
     kDiffractive               = 11,
     kEM                        = 12,
     kWeakMix                   = 13
   };

   /// \brief True interaction of probe particle with detector.  Usually neutrinos, but occasionally cosmics etc.
   class SRTrueInteraction
   {
     private:
       // just to keep the typing under control below
       static constexpr float NaN = std::numeric_limits<float>::signaling_NaN();

     public:
       bool  isvtxcont = false;   ///< Is true vertex is within detector?  If not, might be a rock particle or cosmic

       int   pdg     = 0;         ///< PDG code of probe particle
       int   pdgorig = 0;         ///< Initial (unoscillated) PDG code of probe neutrino (may be different than `pdg` if this file is a 'swap' file)

       bool           iscc      = false;                          ///< CC (true) or NC/interference (false)
       ScatteringMode mode      = ScatteringMode::kUnknownMode;   ///< Interaction mode
       int            targetPDG = 0;                              ///< PDG code of struck target

       /// PDG code of struck nucleon (or, in the case of MEC, struck nucleon-nucleon pair).
       /// For MEC, the codes are: 2000000200 --> nn,  2000000201 --> np,  2000000202 --> pp
       int   hitnuc = 0;

       float       E         = NaN; ///< True energy [GeV]
       SRVector3D  vtx;             ///< Interaction vertex position in detector coord. [cm]
       SRVector3D  momentum;        ///< Neutrino three-momentum
       SRVector3D  position;        ///< Neutrino interaction position

       float time         = NaN;    ///< True interaction time
       float bjorkenX     = NaN;    ///< Bjorken x = (k-k')^2/(2*p.q) [Dimensionless]
       float inelasticity = NaN;    ///< Inelasticity y = (p.q) / (k.p) = q0 / Enu
       float Q2           = NaN;    ///< Invariant four-momentum transfer from lepton to nuclear system
       float q0           = NaN;    ///< Energy transferred from lepton to nuclear system (in lab frame)
       float modq         = NaN;    ///< Magnitude of three-momentum transferred from lepton to nuclear system, |q| (in lab frame)
       float W            = NaN;    ///< Hadronic invariant mass W [GeV^2]
       float t            = NaN;    ///< Kinematic t
       float baseline     = NaN;    ///< Distance from decay to interaction [m]

       unsigned int npiplus  = 0;   ///< Number of \f$\pi^+\f$'s after neutrino reaction, before FSI
       unsigned int npiminus = 0;   ///< Number of \f$\pi^1\f$'s after neutrino reaction, before FSI
       unsigned int npizero  = 0;   ///< Number of \f$\pi^0\f$'s after neutrino reaction, before FSI
       unsigned int nproton  = 0;   ///< Number of protons after neutrino reaction, before FSI
       unsigned int nneutron = 0;   ///< Number of neutrons after neutrino reaction, before FSI

       // GTruth stuff
       bool  ischarm    = false;    ///< Is a charmed quark in interaction
       bool  isseaquark = false;    ///< Did neutrino scatter off a sea quark
       int   resnum     = 0;        ///< Resonance number, straight from GENIE
       float xsec       = NaN;      ///< xsec for thrown interaction, in 1/GeV^2, straight from GENIE

       float genweight = NaN;       ///< Weight, if any, assigned by the generator

       SRVector3D prod_vtx;              ///< Neutrino production vertex [cm; beam coordinates]
       SRVector3D parent_dcy_mom;        ///< Neutrino parent momentum at decay [GeV; beam coordinates]
       int        parent_dcy_mode = -1;  ///< Parent hadron/muon decay mode
       int        parent_pdg      = 0;   ///< PDG Code of parent particle ID
       float      parent_dcy_E    = NaN; ///< Neutrino parent energy at decay [GeV]
       float      imp_weight      = NaN; ///< Importance weight from flux file


       Generator                   generator = Generator::kUnknownGenerator;  ///< The generator that created this neutrino interaction
       std::vector<unsigned int>   genVersion;                                ///< Version of the generator that created this neutrino interaction
       std::string                 genConfigString;                           ///< String associated with generator configuration. (For GENIE 3+, this is the "Comprehensive Model Configuration".)

       int                         nprim = 0;       ///< Number of primary daughters
       std::vector<SRTrueParticle> prim;            ///< Primary daughters.  The lepton always comes first in this vector.
   };

} // caf

#endif //DUNEANAOBJ_SRTRUEINTERACTION_H
