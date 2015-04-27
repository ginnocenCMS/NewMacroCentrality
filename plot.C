#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TString.h>
#include <stdio.h>
#include <TLegendEntry.h>
#include <TGraphAsymmErrors.h>

#include <vector>
//#include <TMap.h>
#include <map>

using namespace std;

int limit0=10;
int limit1=20;
int limit2=60;
int limit3=100;
int limit4=140;

TString option="CentLim_10_20_60_100_140";

void plot(bool isdata=false)
{

   gROOT->SetStyle("Plain");	
   gStyle->SetOptStat(0);
   gStyle->SetOptStat(0000);
   gStyle->SetPalette(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetFrameFillColor(0);
   gStyle->SetOptTitle(0);

  const TString l1_input = "Hydjet502MC_CentralityCalibration.root";
  //const TString l1_input = Form("../Input/Data/CalibrationEtsum_%s.root",option.Data());
  TFile *lFile = TFile::Open(l1_input);
  TH2D *hcorrOfflineEtsumVsL1Etsum = (TH2D*)lFile->Get("hcorrOfflineEtsumVsL1Etsum");
  TH1D *hl1Etsum = (TH1D*)lFile->Get("hl1Etsum");
  TProfile *profileofflineCentralityVsl1Etsum = (TProfile*)lFile->Get("profileofflineCentralityVsl1Etsum");
  TProfile *profilel1EtsumVsofflineCentrality = (TProfile*)lFile->Get("profilel1EtsumVsofflineCentrality");
  TProfile *profilel1CentralityVsofflineCentrality = (TProfile*)lFile->Get("profilel1CentralityVsofflineCentrality");
  TH2D *hcorrL1CentralityVsfflineCentrality= (TH2D*)lFile->Get("hcorrL1CentralityVsfflineCentrality");
  TF1* fprofileofflinel1EtsumVsCentrality_Calibration=(TF1*)lFile->Get("fprofileofflinel1EtsumVsCentrality_Calibration");
  fprofileofflinel1EtsumVsCentrality_Calibration->SetName("fprofileofflinel1EtsumVsCentrality_Calibration");
  TH1D *hofflineCentrality= (TH1D*)lFile->Get("hofflineCentrality");
  
  TH1D *hcorrl1EtsumPlusVscorrl1EtsumMinus= (TH1D*)lFile->Get("hcorrl1EtsumPlusVscorrl1EtsumMinus");
  TH1D *hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel= (TH1D*)lFile->Get("hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel");
  
  TH1D *hOffline_Bin0 = (TH1D*)lFile->Get("hOffline_Bin0");
  TH1D *hOffline_Bin1 = (TH1D*)lFile->Get("hOffline_Bin1");
  TH1D *hOffline_Bin2 = (TH1D*)lFile->Get("hOffline_Bin2");
  TH1D *hOffline_Bin3 = (TH1D*)lFile->Get("hOffline_Bin3");
  TH1D *hOffline_Bin4 = (TH1D*)lFile->Get("hOffline_Bin4");
  TH1D *hOffline_Bin5 = (TH1D*)lFile->Get("hOffline_Bin5");
  
  
  TF1 *f1 = new TF1("f1","pol9",0,5000);
  TF1 *f2 = new TF1("f2","pol9",0,200.);
  TF1 *f3 = new TF1("f3","pol1",0,200.);
  f3->SetLineColor(2);
  
  
  TCanvas *canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel=new TCanvas("canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel","canvas",600,600);
  canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->cd();
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->SetMinimum(0.);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetTitleOffset(1.3);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetLabelSize(0.03);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetXaxis()->SetTitle("L1 ETsum Plus");
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetTitle("L1 ETsum Minus");
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetXaxis()->SetTitleOffset(1.1);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetTitleOffset(1.1);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetXaxis()->SetTitleSize(0.04);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetTitleSize(0.04);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetXaxis()->SetRangeUser(0,2500.);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->GetYaxis()->SetRangeUser(0,2500.);
  hcorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->Draw();
  canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->SaveAs(Form("Plots/Plots_%s/canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel.eps",option.Data()));
  
  TCanvas *canvascorrl1EtsumPlusVscorrl1EtsumMinus=new TCanvas("canvascorrl1EtsumPlusVscorrl1EtsumMinus","canvas",600,600);
  canvascorrl1EtsumPlusVscorrl1EtsumMinus->cd();
  hcorrl1EtsumPlusVscorrl1EtsumMinus->SetMinimum(0.);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetTitleOffset(1.3);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetLabelSize(0.03);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetXaxis()->SetTitle("L1 ETsum Plus");
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetTitle("L1 ETsum Minus");
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetXaxis()->SetTitleOffset(1.1);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetTitleOffset(1.1);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetXaxis()->SetTitleSize(0.04);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetTitleSize(0.04);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetXaxis()->SetRangeUser(0,2500.);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->GetYaxis()->SetRangeUser(0,2500.);
  hcorrl1EtsumPlusVscorrl1EtsumMinus->Draw();
  canvascorrl1EtsumPlusVscorrl1EtsumMinus->SaveAs(Form("Plots/Plots_%s/canvascorrl1EtsumPlusVscorrl1EtsumMinusNo.eps",option.Data()));

  
  

  
  hcorrl1EtsumPlusVscorrl1EtsumMinus->Draw();
  canvascorrl1EtsumPlusVscorrl1EtsumMinus->SaveAs(Form("Plots/Plots_%s/canvascorrl1EtsumPlusVscorrl1EtsumMinus.eps",option.Data()));
  
  TCanvas *canvasOfflineCentrality=new TCanvas("canvasOfflineCentrality","canvas",1200,800);
  canvasOfflineCentrality->cd();
  hofflineCentrality->SetMinimum(0.);
  hofflineCentrality->GetYaxis()->SetTitleOffset(1.3);
  hofflineCentrality->GetYaxis()->SetLabelSize(0.03);
  hofflineCentrality->GetXaxis()->SetTitle("Offline Centrality");
  hofflineCentrality->GetYaxis()->SetTitle("Entries");
  hofflineCentrality->GetXaxis()->SetTitleOffset(1.1);
  hofflineCentrality->GetYaxis()->SetTitleOffset(1.1);
  hofflineCentrality->GetXaxis()->SetTitleSize(0.04);
  hofflineCentrality->GetYaxis()->SetTitleSize(0.04);
  hofflineCentrality->Draw();
  canvasOfflineCentrality->SaveAs(Form("Plots/Plots_%s/canvasOfflineCentrality.eps",option.Data()));


  
  TCanvas *canvasOfflineEtsumVsL1Etsum=new TCanvas("canvasOfflineEtsumVsL1Etsum","canvas",1200,800);
  canvasOfflineEtsumVsL1Etsum->cd();
  hcorrOfflineEtsumVsL1Etsum->SetMinimum(0.);
  hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetTitleOffset(1.3);
  hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetLabelSize(0.03);
  hcorrOfflineEtsumVsL1Etsum->GetXaxis()->SetTitle("Offline HF E_{T} sum");
  hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetTitle("Emulator HF E_{T} sum");
  hcorrOfflineEtsumVsL1Etsum->GetXaxis()->SetTitleOffset(1.1);
  hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetTitleOffset(1.1);
  hcorrOfflineEtsumVsL1Etsum->GetXaxis()->SetTitleSize(0.04);
  hcorrOfflineEtsumVsL1Etsum->GetYaxis()->SetTitleSize(0.04);
  hcorrOfflineEtsumVsL1Etsum->Draw();
  canvasOfflineEtsumVsL1Etsum->SaveAs(Form("Plots/Plots_%s/canvasOfflineEtsumVsL1Etsum.eps",option.Data()));
  

  TCanvas *canvasL1Etsum=new TCanvas("canvasL1Etsum","canvas",600,500);
  canvasL1Etsum->cd();
  hl1Etsum->SetMinimum(0.);
  hl1Etsum->GetYaxis()->SetTitleOffset(1.3);
  hl1Etsum->GetYaxis()->SetLabelSize(0.03);
  hl1Etsum->GetYaxis()->SetTitle("Entries");
  hl1Etsum->GetXaxis()->SetTitle("L1 E_{T} sum");
  hl1Etsum->GetXaxis()->SetTitleOffset(1.1);
  hl1Etsum->GetYaxis()->SetTitleOffset(1.1);
  hl1Etsum->GetXaxis()->SetTitleSize(0.04);
  hl1Etsum->GetYaxis()->SetTitleSize(0.04);
  hl1Etsum->Draw();
  canvasL1Etsum->SaveAs(Form("Plots/Plots_%s/canvasL1Etsum.eps",option.Data()));
  

  TCanvas *canvasofflineCentralityVsl1Etsum=new TCanvas("canvasofflineCentralityVsl1Etsum","canvas",600,500);
  canvasofflineCentralityVsl1Etsum->cd();
  profileofflineCentralityVsl1Etsum->GetXaxis()->SetRangeUser(0,2000.);
  profileofflineCentralityVsl1Etsum->GetYaxis()->SetRangeUser(0,250.);
  profileofflineCentralityVsl1Etsum->GetYaxis()->SetTitle("Offline Centrality (bins of 0.5%)");
  profileofflineCentralityVsl1Etsum->GetXaxis()->SetTitle("Emulator HF E_{T} sum");
  profileofflineCentralityVsl1Etsum->SetMarkerStyle(21);
  profileofflineCentralityVsl1Etsum->SetMarkerSize(0.6);
  profileofflineCentralityVsl1Etsum->GetXaxis()->SetTitleOffset(1.2);
  profileofflineCentralityVsl1Etsum->GetYaxis()->SetTitleOffset(1.2);
  profileofflineCentralityVsl1Etsum->Draw();
  profileofflineCentralityVsl1Etsum->Fit("f1");
  canvasofflineCentralityVsl1Etsum->SaveAs(Form("Plots/Plots_%s/canvasofflineCentralityVsl1Etsum.eps",option.Data()));

  
  TCanvas *canvasl1EtsumVsofflineCentrality=new TCanvas("canvasl1EtsumVsofflineCentrality","canvas",600,500);
  canvasl1EtsumVsofflineCentrality->cd();
  profilel1EtsumVsofflineCentrality->GetYaxis()->SetRangeUser(0,5000.);
  profilel1EtsumVsofflineCentrality->GetXaxis()->SetRangeUser(0,250.);
  profilel1EtsumVsofflineCentrality->GetXaxis()->SetTitle("Offline Centrality (bins of 0.5%)");
  profilel1EtsumVsofflineCentrality->GetYaxis()->SetTitle("Emulator HF E_{T} sum");
  profilel1EtsumVsofflineCentrality->SetMarkerStyle(21);
  profilel1EtsumVsofflineCentrality->SetMarkerSize(0.6);
  profilel1EtsumVsofflineCentrality->GetXaxis()->SetTitleOffset(1.2);
  profilel1EtsumVsofflineCentrality->GetYaxis()->SetTitleOffset(1.2);
  profilel1EtsumVsofflineCentrality->Draw();
  profilel1EtsumVsofflineCentrality->Fit("f2");
  canvasl1EtsumVsofflineCentrality->SaveAs(Form("Plots/Plots_%s/canvasl1EtsumVsofflineCentrality.eps",option.Data()));



 // Double_t linear(Double_t *x, Double_t *par){
 // Double_t *p1= &par[0];
 // return result = 


  TCanvas *canvasL1CentralityVsfflineCentrality=new TCanvas("canvasL1CentralityVsfflineCentrality","canvas",600,500);
  canvasL1CentralityVsfflineCentrality->cd();
  hcorrL1CentralityVsfflineCentrality->SetMinimum(0.);
  hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetTitleOffset(1.3);
  hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetLabelSize(0.03);
  hcorrL1CentralityVsfflineCentrality->GetXaxis()->SetTitle("Offline centrality");
  hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetTitle("L1 centrality");
  hcorrL1CentralityVsfflineCentrality->GetXaxis()->SetTitleOffset(1.1);
  hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetTitleOffset(1.1);
  hcorrL1CentralityVsfflineCentrality->GetXaxis()->SetTitleSize(0.04);
  hcorrL1CentralityVsfflineCentrality->GetYaxis()->SetTitleSize(0.04);
  hcorrL1CentralityVsfflineCentrality->Draw();
  canvasL1CentralityVsfflineCentrality->SaveAs(Form("Plots/Plots_%s/canvasL1CentralityVsfflineCentrality.eps",option.Data()));


  TCanvas *canvasl1CentralityVsofflineCentrality=new TCanvas("canvasl1CentralityVsofflineCentrality","canvas",600,500);
  canvasl1CentralityVsofflineCentrality->cd();
  profilel1CentralityVsofflineCentrality->GetYaxis()->SetRangeUser(0,250.);
  profilel1CentralityVsofflineCentrality->GetXaxis()->SetRangeUser(0,250.);
  profilel1CentralityVsofflineCentrality->GetXaxis()->SetTitle("Offline Centrality (bins of 0.5%)");
  profilel1CentralityVsofflineCentrality->GetYaxis()->SetTitle("L1 Centrality (bins of 0.5%)");
  profilel1CentralityVsofflineCentrality->SetMarkerStyle(21);
  profilel1CentralityVsofflineCentrality->SetMarkerSize(0.6);
  profilel1CentralityVsofflineCentrality->GetXaxis()->SetTitleOffset(1.2);
  profilel1CentralityVsofflineCentrality->GetYaxis()->SetTitleOffset(1.2);
  profilel1CentralityVsofflineCentrality->Draw();
  profilel1CentralityVsofflineCentrality->Fit("f3");
  canvasl1CentralityVsofflineCentrality->SaveAs(Form("Plots/Plots_%s/canvasl1CentralityVsofflineCentrality.eps",option.Data()));
  
  TCanvas *canvasranges=new TCanvas("canvasranges","canvasranges",600,500);
  canvasranges->cd();
  
  hOffline_Bin0->SetMaximum(15000);
  hOffline_Bin0->GetXaxis()->SetRangeUser(-10,210.);
  hOffline_Bin0->GetYaxis()->SetTitleOffset(1.5);
  
  hOffline_Bin0->Sumw2();
  hOffline_Bin0->SetMarkerStyle(0);
  hOffline_Bin0->SetLineColor(kViolet+1);
  hOffline_Bin0->SetFillStyle(3325);
  hOffline_Bin0->SetFillColor(kViolet+1);
  
  
  hOffline_Bin1->Sumw2();
  hOffline_Bin1->SetMarkerStyle(0);
  hOffline_Bin1->SetLineColor(kRed+1);
  hOffline_Bin1->SetFillStyle(3325);
  hOffline_Bin1->SetFillColor(kRed+1);
  
  hOffline_Bin2->Sumw2();
  hOffline_Bin2->SetMarkerStyle(0);
  hOffline_Bin2->SetLineColor(kBlue+1);
  hOffline_Bin2->SetFillStyle(3325);
  hOffline_Bin2->SetFillColor(kBlue+1);

  hOffline_Bin3->Sumw2();
  hOffline_Bin3->SetMarkerStyle(0);
  hOffline_Bin3->SetLineColor(kGreen+1);
  hOffline_Bin3->SetFillStyle(3325);
  hOffline_Bin3->SetFillColor(kGreen+1);

  hOffline_Bin4->Sumw2();
  hOffline_Bin4->SetMarkerStyle(0);
  hOffline_Bin4->SetLineColor(1);
  hOffline_Bin4->SetFillStyle(3325);
  hOffline_Bin4->SetFillColor(1);

  hOffline_Bin5->Sumw2();
  hOffline_Bin5->SetMarkerStyle(0);
  hOffline_Bin5->SetLineColor(30);
  hOffline_Bin5->SetFillStyle(3325);
  hOffline_Bin5->SetFillColor(30);

  hOffline_Bin0->Draw("same hist e");
  hOffline_Bin1->Draw("same hist e");
  hOffline_Bin2->Draw("same hist e");
  hOffline_Bin3->Draw("same hist e");
  hOffline_Bin4->Draw("same hist e");
  hOffline_Bin5->Draw("same hist e");
  
  TLegend *leg = new TLegend(0.340604,0.5940803,0.8741611,0.8816068,"L1 centrality threshold");
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSizePixels(20);
  
  
  leg->AddEntry(hOffline_Bin0,Form("0  < L1cen < %d",limit0),"lp");
  leg->AddEntry(hOffline_Bin1,Form("%d < L1cen < %d",limit0,limit1),"lp");
  leg->AddEntry(hOffline_Bin2,Form("%d < L1cen < %d",limit1,limit2),"lp");
  leg->AddEntry(hOffline_Bin3,Form("%d < L1cen < %d",limit2,limit3),"lp");
  leg->AddEntry(hOffline_Bin4,Form("%d< L1cen < %d", limit3,limit4),"lp");
  leg->AddEntry(hOffline_Bin5,Form("%d< L1cen < 200",limit4),"lp");
  leg->Draw();
  canvasranges->SaveAs(Form("Plots/Plots_%s/canvasranges.eps",option.Data()));
  
  
  
  double Etsum_Bin0=fprofileofflinel1EtsumVsCentrality_Calibration->Eval(limit0);
  double Etsum_Bin1=fprofileofflinel1EtsumVsCentrality_Calibration->Eval(limit1);
  double Etsum_Bin2=fprofileofflinel1EtsumVsCentrality_Calibration->Eval(limit2);
  double Etsum_Bin3=fprofileofflinel1EtsumVsCentrality_Calibration->Eval(limit3);
  double Etsum_Bin4=fprofileofflinel1EtsumVsCentrality_Calibration->Eval(limit4);
  
  cout<<"***************************"<<endl;
  cout<<"LUT for centrality ranges"<<endl;
  cout<<"Centrality 0-5% = E_{T} sum > "<<Etsum_Bin0<<endl;
  cout<<"Centrality 5-10% ="<<Etsum_Bin0<<"<E_{T} sum <"<<Etsum_Bin1<<endl;
  cout<<"Centrality 10-30% ="<<Etsum_Bin1<<"<E_{T} sum <"<<Etsum_Bin2<<endl;
  cout<<"Centrality 30-50% ="<<Etsum_Bin2<<"<E_{T} sum <"<<Etsum_Bin3<<endl;
  cout<<"Centrality 50-90% ="<<Etsum_Bin3<<"<E_{T} sum <"<<Etsum_Bin4<<endl;
  cout<<"Centrality "<<(int)(limit4/2)<<"-100% =  E_{T} sum <"<<Etsum_Bin4<<endl;
  
  
  if(!isdata){
  
    TH1D *hNcoll_Bin0 = (TH1D*)lFile->Get("hNcoll_Bin0");
    TH1D *hNcoll_Bin1 = (TH1D*)lFile->Get("hNcoll_Bin1");
    TH1D *hNcoll_Bin2 = (TH1D*)lFile->Get("hNcoll_Bin2");
    TH1D *hNcoll_Bin3 = (TH1D*)lFile->Get("hNcoll_Bin3");
    TH1D *hNcoll_Bin4 = (TH1D*)lFile->Get("hNcoll_Bin4");
    TH1D *hNcoll_Bin5 = (TH1D*)lFile->Get("hNcoll_Bin5");
    
    TCanvas *canvasrangesNcoll=new TCanvas("canvasrangesNcoll","canvasrangesNcoll",600,500);
    canvasrangesNcoll->cd();
    
    hNcoll_Bin0->Rebin(5);
    hNcoll_Bin1->Rebin(5);
    hNcoll_Bin2->Rebin(5);
    hNcoll_Bin3->Rebin(5);
    hNcoll_Bin4->Rebin(5);
    hNcoll_Bin5->Rebin(5);
    
  
  hNcoll_Bin0->SetMaximum(50000);
  hNcoll_Bin0->GetXaxis()->SetRangeUser(-0.5,1999.5);
  hNcoll_Bin0->GetYaxis()->SetTitleOffset(1.5);
  
  hNcoll_Bin0->Sumw2();
  hNcoll_Bin0->SetMarkerStyle(0);
  hNcoll_Bin0->SetLineColor(kViolet+1);
  hNcoll_Bin0->SetFillStyle(3325);
  hNcoll_Bin0->SetFillColor(kViolet+1);
  
  
  hNcoll_Bin1->Sumw2();
  hNcoll_Bin1->SetMarkerStyle(0);
  hNcoll_Bin1->SetLineColor(kRed+1);
  hNcoll_Bin1->SetFillStyle(3325);
  hNcoll_Bin1->SetFillColor(kRed+1);
  
  hNcoll_Bin2->Sumw2();
  hNcoll_Bin2->SetMarkerStyle(0);
  hNcoll_Bin2->SetLineColor(kBlue+1);
  hNcoll_Bin2->SetFillStyle(3325);
  hNcoll_Bin2->SetFillColor(kBlue+1);

  hNcoll_Bin3->Sumw2();
  hNcoll_Bin3->SetMarkerStyle(0);
  hNcoll_Bin3->SetLineColor(kGreen+1);
  hNcoll_Bin3->SetFillStyle(3325);
  hNcoll_Bin3->SetFillColor(kGreen+1);

  hNcoll_Bin4->Sumw2();
  hNcoll_Bin4->SetMarkerStyle(0);
  hNcoll_Bin4->SetLineColor(1);
  hNcoll_Bin4->SetFillStyle(3325);
  hNcoll_Bin4->SetFillColor(1);

  hNcoll_Bin5->Sumw2();
  hNcoll_Bin5->SetMarkerStyle(0);
  hNcoll_Bin5->SetLineColor(kRed+1);
  hNcoll_Bin5->SetFillStyle(1);
  hNcoll_Bin5->SetFillColor(kRed+1);

  hNcoll_Bin0->Draw("same hist e");
  hNcoll_Bin1->Draw("same hist e");
  hNcoll_Bin2->Draw("same hist e");
  hNcoll_Bin3->Draw("same hist e");
  hNcoll_Bin4->Draw("same hist e");
  hNcoll_Bin5->Draw("same hist e");
  
  TLegend *leg = new TLegend(0.340604,0.5940803,0.8741611,0.8816068,"L1 centrality threshold");
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSizePixels(20);

  leg->AddEntry(hNcoll_Bin0,Form("0  < L1cen < %d",limit0),"lp");
  leg->AddEntry(hNcoll_Bin1,Form("%d < L1cen < %d",limit0,limit1),"lp");
  leg->AddEntry(hNcoll_Bin2,Form("%d < L1cen < %d",limit1,limit2),"lp");
  leg->AddEntry(hNcoll_Bin3,Form("%d < L1cen < %d",limit2,limit3),"lp");
  leg->AddEntry(hNcoll_Bin4,Form("%d< L1cen < %d", limit3,limit4),"lp");
  leg->AddEntry(hNcoll_Bin5,Form("%d< L1cen < 200",limit4),"lp");
  leg->Draw();
  canvasrangesNcoll->SaveAs(Form("Plots/Plots_%s/canvasrangesNcoll.eps",option.Data()));
  
  
  
  }
}