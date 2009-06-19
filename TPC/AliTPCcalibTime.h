#ifndef ALITPCCALIBTIME_H
#define ALITPCCALIBTIME_H

/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

#include "AliTPCcalibBase.h"
#include "TH2F.h"
#include "TF1.h"
#include "TArrayD.h"
#include "TObjArray.h"

class TH1F;
class TH3F;
class TH2F;
class THnSparse;
class TList;
class AliESDEvent;
class AliESDtrack;
class AliTPCcalibLaser;
class TGraphErrors;

#include "TTreeStream.h"
#include "TMap.h"
 
class AliTPCcalibTime:public AliTPCcalibBase {
public:
  AliTPCcalibTime(); 
  AliTPCcalibTime(const Text_t *name, const Text_t *title, UInt_t StartTime, UInt_t EndTime, Int_t deltaIntegrationTimeVdrift);
  virtual ~AliTPCcalibTime();
  
  virtual void           Process(AliESDEvent *event);
  virtual Long64_t       Merge(TCollection *li);
  virtual void           Analyze();
  //
  static Bool_t          IsLaser(AliESDEvent *event);
  void                   ProcessLaser (AliESDEvent *event);
  void                   ProcessCosmic(AliESDEvent *event);
  Bool_t                 IsPair(AliExternalTrackParam *tr0, AliExternalTrackParam *tr1);
  //
  THnSparse* GetHistVdriftLaserA(Int_t index=1){return fHistVdriftLaserA[index];};
  THnSparse* GetHistVdriftLaserC(Int_t index=1){return fHistVdriftLaserC[index];};
  THnSparse* GetHistoDrift(TObjString* name);
  THnSparse* GetHistoDrift(const char* name);
  TMap*      GetHistoDrift();
  TGraphErrors*    GetGraphDrift(TObjString* name);
  TGraphErrors*    GetGraphDrift(const char* name);
  TMap*      GetGraphDrift();
  TGraph*    GetFitDrift(TObjString* name);
  TGraph*    GetFitDrift(const char* name);
  TMap*      GetFitDrift();
  TH1F*      GetCosmiMatchingHisto(Int_t index=0){return fCosmiMatchingHisto[index];};
  
  void     Process(AliESDtrack *track, Int_t runNo=-1){AliTPCcalibBase::Process(track,runNo);};
  void     Process(AliTPCseed *track){return AliTPCcalibBase::Process(track);}
private:
  void ResetCurrent();                  // reset current values

  AliTPCcalibLaser * fLaser;            //! laser calibration
  //
  // current information
  //
  Float_t fDz;          //! current delta z
  
  // cuts
  //
  Float_t fCutMaxD;     // maximal distance in rfi ditection
  Float_t fCutMaxDz;    // maximal distance in z ditection
  Float_t fCutTheta;    // maximal distance in theta ditection
  Float_t fCutMinDir;   // direction vector products
  Int_t   fCutTracks;   // maximal number of tracks
 
  AliTPCcalibTime(const AliTPCcalibTime&); 
  AliTPCcalibTime& operator=(const AliTPCcalibTime&); 

  TH1F* fCosmiMatchingHisto[5];

  // laser histo
  THnSparse * fHistVdriftLaserA[3];	//Histograms for V drift from laser
  THnSparse * fHistVdriftLaserC[3];	//Histograms for V drift from laser
  // DELTA Z histo
  TMap      * fMapDz;			//Tmap of V drifts for different triggers

  Int_t    fTimeBins;			//Bins time
  Double_t fTimeStart;			//Start time
  Double_t fTimeEnd;			//End time
  Int_t    fPtBins;			//Bins pt
  Double_t fPtStart;			//Start pt
  Double_t fPtEnd;			//End pt
  Int_t    fVdriftBins;			//Bins vdrift
  Double_t fVdriftStart;		//Start vdrift
  Double_t fVdriftEnd;			//End vdrift
  Int_t    fRunBins;			//Bins run
  Double_t fRunStart;			//Start run
  Double_t fRunEnd;			//End run
  Int_t    fBinsVdrift[4];		//Bins for vdrift
  Double_t fXminVdrift[4];		//Xmax for vdrift
  Double_t fXmaxVdrift[4];		//Xmin for vdrift
  ClassDef(AliTPCcalibTime, 2); 
};

#endif


