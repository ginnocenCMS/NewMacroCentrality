#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TProfile.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TString.h>
#include <TLegendEntry.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>

#include <vector>
#include <iostream>

const int MAXL1JETS = 8;
const int MAXRCTREGIONS= 396;
const int MAXJETS = 500;
const Int_t THRESHOLDS = 30;

int limit0=10;
int limit1=20;
int limit2=60;
int limit3=100;
int limit4=140; 


void centralityCalibration(TString inHiForestFileName, TString outFileName, bool montecarlo = false)
{
  TFile *outFile = new TFile(outFileName,"RECREATE");
  TFile *inFile = TFile::Open(inHiForestFileName);
  TTree *f1Tree = (TTree*)inFile->Get("akPu3CaloJetAnalyzer/t");
  TTree *fEvtTree = (TTree*)inFile->Get("hiEvtAnalyzer/HiTree");
  TTree *fSkimTree = (TTree*)inFile->Get("skimanalysis/HltTree");
  TTree *l1Tree = (TTree*)inFile->Get("L1UpgradeAnalyzer/L1UpgradeTree");
  TTree *fEvtGen = (TTree*)inFile->Get("HiGenParticleAna/hi");

  Int_t l1_event, l1_run, l1_lumi;  
  Int_t l1_region_hwPt[MAXRCTREGIONS];
  Int_t l1_region_hwEta[MAXRCTREGIONS];

  l1Tree->SetBranchAddress("event",&l1_event);
  l1Tree->SetBranchAddress("run",&l1_run);
  l1Tree->SetBranchAddress("lumi",&l1_lumi);
  l1Tree->SetBranchAddress("region_hwPt",l1_region_hwPt);
  l1Tree->SetBranchAddress("region_hwEta",l1_region_hwEta);

  Int_t f_evt, f_run, f_lumi;
  Float_t vz;
  Int_t hiBin;
  float hiHF,ncoll;

  fEvtTree->SetBranchAddress("evt",&f_evt);
  fEvtTree->SetBranchAddress("run",&f_run);
  fEvtTree->SetBranchAddress("lumi",&f_lumi);
  fEvtTree->SetBranchAddress("vz",&vz);
  fEvtTree->SetBranchAddress("hiBin",&hiBin);
  fEvtTree->SetBranchAddress("hiHF",&hiHF);
  fEvtGen->SetBranchAddress("ncoll",&ncoll);


  Int_t pcollisionEventSelection, pHBHENoiseFilter;
  fSkimTree->SetBranchAddress("pcollisionEventSelection",&pcollisionEventSelection);
  fSkimTree->SetBranchAddress("pHBHENoiseFilter",&pHBHENoiseFilter);

  
  TH2D *hcorrl1EtsumPlusVscorrl1EtsumMinus = new TH2D("hcorrl1EtsumPlusVscorrl1EtsumMinus","L1 EtsumPlus vs L1 EtsumMinus; L1 EtsumMinus ; L1 EtsumPlus",100,0,6000,100,0,6000); 
  TH2D *hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel = new TH2D("hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel","L1 EtsumPlus vs L1 EtsumMinus; L1 EtsumMinus ; L1 EtsumPlus",100,0,6000,100,0,6000);
  TH2D *hcorrl1EtsumVsofflineCentrality = new TH2D("hcorrl1EtsumVsofflineCentrality","L1 Etsum vs offline centrality; offline centrality ; L1 Etsum",100,0,200,100,0,6000);
  TH2D *hcorrofflineCentralityVsl1Etsum = new TH2D("hcorrofflineCentralityVsl1Etsum","Offline centrality vs L1 Etsum; L1 Etsum ; offline centrality",100,0,6000,100,0,200);  
  TH2D *hcorrL1CentralityVsfflineCentrality = new TH2D("hcorrL1CentralityVsfflineCentrality","Online centrality vs offline centrality; L1 Etsum ; offline centrality",200,0,200,200,0,200);  
  TH1D *hofflineCentrality = new TH1D("hofflineCentrality","Offline cent; Offline centrality; Entries",40,0.,200.);
  TH1D *hl1Etsum = new TH1D("hl1Etsum","L1 Etsum ; L1 Etsum; Entries ",40,0.,6000.);
  TH1D *hofflineEtsum = new TH1D("hofflineEtsum","Offline Etsum ; Offline Etsum; Entries ",40,0.,6000.);
  TH2D *hcorrOfflineEtsumVsL1Etsum = new TH2D("hcorrOfflineEtsumVsL1Etsum","Offline Etsum vs L1 Etsum; Offline Etsum; L1 Etsum",100,0.,6000.,100,0.,6000.);
  
  TProfile *profilel1EtsumVsofflineCentrality = new TProfile("profilel1EtsumVsofflineCentrality","L1 Etsum vs offline centrality; offline centrality ; L1 Etsum",100,0,200,0,6000);
  TProfile *profileofflineCentralityVsl1Etsum = new TProfile("profileofflineCentralityVsl1Etsum","Offline centrality vs L1 Etsum; L1 Etsum ; offline centrality",400,0,6000,0,200);
  TProfile *profileofflineCentralityVsl1Etsum_Calibration = new TProfile("profileofflineCentralityVsl1Etsum_Calibration","Offline centrality vs L1 Etsum; L1 Etsum ; offline centrality",200,0,6000,0,200);
  TProfile *profilel1EtsumVsofflineCentrality_Calibration = new TProfile("profilel1EtsumVsofflineCentrality_Calibration","Offline centrality vs L1 Etsum; L1 Etsum ; offline centrality",50,0,200,0,6000);
  TProfile *profilel1CentralityVsofflineCentrality = new TProfile("profilel1CentralityVsofflineCentrality","L1 centrality vs Offline Centrality; Offline Centrality ; L1 centrality",100,0,200,0,200);
  
  TH1D *hOffline_Bin0 = new TH1D("hOffline_Bin0","hOffline_Bin0 ; Offline Centrality; Entries ",260,-30.,230.);
  TH1D *hOffline_Bin1 = new TH1D("hOffline_Bin1","hOffline_Bin1 ; Offline Centrality; Entries ",260,-30.,230.);
  TH1D *hOffline_Bin2 = new TH1D("hOffline_Bin2","hOffline_Bin2 ; Offline Centrality; Entries ",260,-30.,230.);
  TH1D *hOffline_Bin3 = new TH1D("hOffline_Bin3","hOffline_Bin3 ; Offline Centrality; Entries ",260,-30.,230.);
  TH1D *hOffline_Bin4 = new TH1D("hOffline_Bin4","hOffline_Bin4 ; Offline Centrality; Entries ",260,-30.,230.);
  TH1D *hOffline_Bin5 = new TH1D("hOffline_Bin5","hOffline_Bin5 ; Offline Centrality; Entries ",260,-30.,230.);
  
  TH1D *hNcollAll = new TH1D("hNcollAll","hNcollAll ; N_{coll}; Entries ",2000,-0.5,1999.5);
  TH1D *hNcoll_Bin0 = new TH1D("hNcoll_Bin0","hNcoll_Bin0 ; N_{coll}; Entries ",2000,-0.5,1999.5);
  TH1D *hNcoll_Bin1 = new TH1D("hNcoll_Bin1","hNcoll_Bin1 ; N_{coll}; Entries ",2000,-0.5,1999.5);
  TH1D *hNcoll_Bin2 = new TH1D("hNcoll_Bin2","hNcoll_Bin2 ; N_{coll}; Entries ",2000,-0.5,1999.5);
  TH1D *hNcoll_Bin3 = new TH1D("hNcoll_Bin3","hNcoll_Bin3 ; N_{coll}; Entries ",2000,-0.5,1999.5);
  TH1D *hNcoll_Bin4 = new TH1D("hNcoll_Bin4","hNcoll_Bin4 ; N_{coll}; Entries ",2000,-0.5,1999.5);
  TH1D *hNcoll_Bin5 = new TH1D("hNcoll_Bin5","hNcoll_Bin5 ; N_{coll}; Entries ",2000,-0.5,1999.5);

  
  const int nBins = 100; 
  const double maxCen = 200.;
  const Double_t L1_THRESHOLD[12] = {0.,10.,20.,30.,40.,50.,100.,140.,160.,170.,180.,190.};
  
  TH1D *accepted[12][1];
  accepted[0][0] = new TH1D("accepted_cen_0","",nBins,0,maxCen);
  accepted[1][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_10");
  accepted[2][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_20");
  accepted[3][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_30");
  accepted[4][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_40");
  accepted[5][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_50");
  accepted[6][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_100");
  accepted[7][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_140");
  accepted[8][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_160");
  accepted[9][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_170");
  accepted[10][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_180");
  accepted[11][0] = (TH1D*)accepted[0][0]->Clone("accepted_cen_190");
  
  TH1D *fCenOffline[1]; 
  fCenOffline[0] = new TH1D("fCenOffline",";Offline Centrality",nBins,0,maxCen);

  int countCalib = 0;

  Long64_t entries = f1Tree->GetEntries();
  for(Long64_t j = 0; j < entries; ++j)
  {
    if(j % 10000 == 0)
      printf("%lld / %lld\n",j,entries);

    // Only use good collision events ********
    fEvtTree->GetEntry(j);
    fSkimTree->GetEntry(j);
    l1Tree->GetEntry(j);
    f1Tree->GetEntry(j);

    bool goodEvent = false;
    if((pcollisionEventSelection == 1) && (montecarlo || (pHBHENoiseFilter == 1)) && (TMath::Abs(vz) < 15))
    {
      goodEvent = true;
    }
    if(!goodEvent) continue;
    
    int etsum=0;
    int l1_etsumPlus=0;
    int l1_etsumMinus=0;
    
    for (int i=0;i<396;i++){
      if (l1_region_hwEta[i]<=3) l1_etsumPlus=l1_etsumPlus+l1_region_hwPt[i];   
      if (l1_region_hwEta[i]>=18) l1_etsumMinus=l1_etsumMinus+l1_region_hwPt[i];   
    }
      etsum=l1_etsumPlus+l1_etsumMinus;
      //std::cout<<"etsum="<<etsum<<std::endl;
      //std::cout<<"l1_etsumPlus="<<l1_etsumPlus<<std::endl;
      //std::cout<<"l1_etsumMinus="<<l1_etsumMinus<<std::endl;
      profileofflineCentralityVsl1Etsum_Calibration->Fill(etsum,hiBin); 
      profilel1EtsumVsofflineCentrality_Calibration->Fill(hiBin,etsum); 
      countCalib++;
  }
  //************** second loop ************** 
  
  printf("Matching entries: %d\n",countCalib);

  TF1 *fprofileofflineCentralityVsl1Etsum_Calibration = new TF1("fprofileofflineCentralityVsl1Etsum_Calibration","pol9",0,2500);
  profileofflineCentralityVsl1Etsum_Calibration->Fit("fprofileofflineCentralityVsl1Etsum_Calibration");
  TF1 *fprofileofflinel1EtsumVsCentrality_Calibration = new TF1("fprofileofflinel1EtsumVsCentrality_Calibration","pol9",0,200);
  profilel1EtsumVsofflineCentrality_Calibration->Fit("fprofileofflinel1EtsumVsCentrality_Calibration");

  double L1centrality=0.;

  
  for(Long64_t j = 0; j < entries; ++j)
  {
    if(j % 10000 == 0)
      printf("%lld / %lld\n",j,entries);

    // Only use good collision events ********
    fEvtTree->GetEntry(j);
    fSkimTree->GetEntry(j);
    l1Tree->GetEntry(j);
    f1Tree->GetEntry(j);
    fEvtGen->GetEntry(j);

    bool goodEvent = false;
    if((pcollisionEventSelection == 1) && (montecarlo || (pHBHENoiseFilter == 1)) && (TMath::Abs(vz) < 15))
    {
      goodEvent = true;
    }
    if(!goodEvent) continue;
    
    int etsum=0;
    int l1_etsumPlus=0;
    int l1_etsumMinus=0;
    
    for (int i=0;i<396;i++){
      if (l1_region_hwEta[i]<=3) l1_etsumPlus=l1_etsumPlus+l1_region_hwPt[i];   
      if (l1_region_hwEta[i]>=18) l1_etsumMinus=l1_etsumMinus+l1_region_hwPt[i];   
    }
      etsum=l1_etsumPlus+l1_etsumMinus;
      //printf("et value %d\n",etsum);
      //printf("hiBin %d\n",hiBin);
      //printf("hiHF %f\n",hiHF);

	  hcorrl1EtsumPlusVscorrl1EtsumMinus->Fill(l1_etsumMinus,l1_etsumPlus);
	  hcorrl1EtsumVsofflineCentrality->Fill(hiBin,etsum);
	  hcorrofflineCentralityVsl1Etsum->Fill(etsum,hiBin);
	  hofflineCentrality->Fill(hiBin);
	  hl1Etsum->Fill(etsum);
	  hofflineEtsum->Fill(hiHF);
	  hcorrOfflineEtsumVsL1Etsum->Fill(hiHF,etsum); 
	  profileofflineCentralityVsl1Etsum->Fill(etsum,hiBin);  
	  profilel1EtsumVsofflineCentrality->Fill(hiBin,etsum);  	  
	  //L1centrality=fprofileofflineCentralityVsl1Etsum_Calibration->Eval(etsum);
	  L1centrality=fprofileofflinel1EtsumVsCentrality_Calibration->GetX(etsum);
	  printf("L1centrality %f\n",L1centrality);
	  hcorrL1CentralityVsfflineCentrality->Fill(hiBin,L1centrality);
	  profilel1CentralityVsofflineCentrality->Fill(hiBin,L1centrality);
	  
	  double Etsum_Bin0=fprofileofflinel1EtsumVsCentrality_Calibration->Eval((double)(limit0));
      double Etsum_Bin1=fprofileofflinel1EtsumVsCentrality_Calibration->Eval((double)(limit1));
      double Etsum_Bin2=fprofileofflinel1EtsumVsCentrality_Calibration->Eval((double)(limit2));
      double Etsum_Bin3=fprofileofflinel1EtsumVsCentrality_Calibration->Eval((double)(limit3));
      double Etsum_Bin4=fprofileofflinel1EtsumVsCentrality_Calibration->Eval((double)(limit4));
      
      if(etsum>Etsum_Bin0) {hOffline_Bin0->Fill(hiBin); hNcoll_Bin0->Fill(ncoll);}
      if(etsum>Etsum_Bin1 && etsum<Etsum_Bin0) {hOffline_Bin1->Fill(hiBin); hNcoll_Bin1->Fill(ncoll);}
      if(etsum>Etsum_Bin2 && etsum<Etsum_Bin1) {hOffline_Bin2->Fill(hiBin); hNcoll_Bin2->Fill(ncoll);}
      if(etsum>Etsum_Bin3 && etsum<Etsum_Bin2) {hOffline_Bin3->Fill(hiBin); hNcoll_Bin3->Fill(ncoll);}
      if(etsum>Etsum_Bin4 && etsum<Etsum_Bin3) {hOffline_Bin4->Fill(hiBin); hNcoll_Bin4->Fill(ncoll);}
      if(etsum<Etsum_Bin4) {hOffline_Bin5->Fill(hiBin); hNcoll_Bin5->Fill(ncoll);}
      hNcollAll->Fill(ncoll);
	  fCenOffline[0]->Fill(hiBin);

	  
	  for(int k = 0; k < 12; ++k){
	    if(L1centrality>L1_THRESHOLD[k]){
	      accepted[k][0]->Fill(hiBin);
	    }
	  }
    }  

  outFile->cd();
  hcorrl1EtsumPlusVscorrl1EtsumMinus->Write();
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->Write();
  hcorrl1EtsumVsofflineCentrality->Write();
  hcorrofflineCentralityVsl1Etsum->Write();
  hofflineCentrality->Write();
  hl1Etsum->Write();
  hofflineEtsum->Write();
  hcorrOfflineEtsumVsL1Etsum->Write();
  profilel1EtsumVsofflineCentrality->Write();
  profileofflineCentralityVsl1Etsum->Write();
  profileofflineCentralityVsl1Etsum_Calibration->Write();
  fprofileofflineCentralityVsl1Etsum_Calibration->SetName("fprofileofflineCentralityVsl1Etsum_Calibration");
  fprofileofflineCentralityVsl1Etsum_Calibration->Write();
  fprofileofflinel1EtsumVsCentrality_Calibration->SetName("fprofileofflinel1EtsumVsCentrality_Calibration");
  fprofileofflinel1EtsumVsCentrality_Calibration->Write();
  hcorrL1CentralityVsfflineCentrality->Write();
  profilel1CentralityVsofflineCentrality->Write();
  hOffline_Bin0->Write();
  hOffline_Bin1->Write();
  hOffline_Bin2->Write();
  hOffline_Bin3->Write();
  hOffline_Bin4->Write();
  hOffline_Bin5->Write();
  
  hNcoll_Bin0->Write();
  hNcoll_Bin1->Write();
  hNcoll_Bin2->Write();
  hNcoll_Bin3->Write();
  hNcoll_Bin4->Write();
  hNcoll_Bin5->Write();
  hNcollAll->Write();

  

  TGraphAsymmErrors *a[12][1];
  for(int k = 0; k < 12; ++k){
    for(int l = 0; l < 1; ++l)
    {
      a[k][l] = new TGraphAsymmErrors();
      a[k][l]->BayesDivide(accepted[k][l],fCenOffline[l]);
    }
  }
  a[0][0]->SetName("asymm_cen_0_cen");
  a[1][0]->SetName("asymm_cen_10_cen");
  a[2][0]->SetName("asymm_cen_20_cen");
  a[3][0]->SetName("asymm_cen_30_cen");
  a[4][0]->SetName("asymm_cen_40_cen");
  a[5][0]->SetName("asymm_cen_50_cen");
  a[6][0]->SetName("asymm_cen_100_cen");
  a[7][0]->SetName("asymm_cen_140_cen");
  a[8][0]->SetName("asymm_cen_160_cen");
  a[9][0]->SetName("asymm_cen_170_cen");
  a[10][0]->SetName("asymm_cen_180_cen");
  a[11][0]->SetName("asymm_cen_190_cen");
  
  fCenOffline[0]->Write();
   
  for(int k = 0; k < 12; ++k){
    for(int l = 0; l < 1; ++l)
    {
      accepted[k][l]->Write();
      a[k][l]->Write();
    }
  }
  outFile->Close();
} 



int main(int argc, char **argv)
{
  if(argc == 3)
  {
    centralityCalibration(argv[1], argv[2], argv[3]);
    return 0;
  }
  else
  {
    std::cout << "Usage: \nmakeTurnOn_fromSameFile.exe <input_HiForest_file> <output_file>" << std::endl;
    return 1;
  }
}
