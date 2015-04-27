#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>

void makePrettyTurnOn()
{

  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile *inFile = TFile::Open("Hydjet502MC_CentralityCalibration.root");
  TGraphAsymmErrors *asymm_cen_0_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_0_cen");
  TGraphAsymmErrors *asymm_cen_10_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_10_cen");
  TGraphAsymmErrors *asymm_cen_20_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_20_cen");
  TGraphAsymmErrors *asymm_cen_30_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_30_cen");
  TGraphAsymmErrors *asymm_cen_40_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_40_cen");
  TGraphAsymmErrors *asymm_cen_50_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_50_cen");
  TGraphAsymmErrors *asymm_cen_100_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_100_cen");
  TGraphAsymmErrors *asymm_cen_140_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_140_cen");
  TGraphAsymmErrors *asymm_cen_160_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_160_cen");
  TGraphAsymmErrors *asymm_cen_170_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_170_cen");
  TGraphAsymmErrors *asymm_cen_180_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_180_cen");
  TGraphAsymmErrors *asymm_cen_190_cen = (TGraphAsymmErrors*)inFile->Get("asymm_cen_190_cen");


  asymm_cen_10_cen->SetMarkerColor(1);
  asymm_cen_10_cen->SetLineColor(1);
  asymm_cen_20_cen->SetMarkerColor(kBlue);
  asymm_cen_20_cen->SetLineColor(kBlue);
  asymm_cen_30_cen->SetMarkerColor(kRed);
  asymm_cen_30_cen->SetLineColor(kRed);
  asymm_cen_40_cen->SetMarkerColor(kOrange);
  asymm_cen_40_cen->SetLineColor(kOrange);
  asymm_cen_50_cen->SetMarkerColor(kRed+2);
  asymm_cen_50_cen->SetLineColor(kRed+2);
  asymm_cen_100_cen->SetMarkerColor(1);
  asymm_cen_100_cen->SetLineColor(1);
  asymm_cen_140_cen->SetMarkerColor(6);
  asymm_cen_140_cen->SetLineColor(6);
  asymm_cen_160_cen->SetMarkerColor(kBlue);
  asymm_cen_160_cen->SetLineColor(kBlue);
  asymm_cen_170_cen->SetMarkerColor(kRed);
  asymm_cen_170_cen->SetLineColor(kRed);
  asymm_cen_180_cen->SetMarkerColor(kOrange);
  asymm_cen_180_cen->SetLineColor(kOrange);
  asymm_cen_190_cen->SetMarkerColor(kRed+2);
  asymm_cen_190_cen->SetLineColor(kRed+2);

  
  TLine*line_cen10=new TLine(10,0.,10,1.);
  line_cen10->SetLineWidth(2);
  line_cen10->SetLineColor(1);
  line_cen10->SetLineStyle(2);
  
  TLine*line_cen20=new TLine(20,0.,20,1.);
  line_cen20->SetLineWidth(2);
  line_cen20->SetLineColor(kBlue);
  line_cen20->SetLineStyle(2);

  TLine*line_cen30=new TLine(30,0.,30,1.);
  line_cen30->SetLineWidth(2);
  line_cen30->SetLineColor(kRed);
  line_cen30->SetLineStyle(2);

  TLine*line_cen40=new TLine(40,0.,40,1.);
  line_cen40->SetLineWidth(2);
  line_cen40->SetLineColor(kOrange);
  line_cen40->SetLineStyle(2);

  TLine*line_cen50=new TLine(50,0.,50,1.);
  line_cen50->SetLineWidth(2);
  line_cen50->SetLineColor(kRed+2);
  line_cen50->SetLineStyle(2);
  
  TLine*line_cen100=new TLine(100,0.,100,1.);
  line_cen100->SetLineWidth(2);
  line_cen100->SetLineColor(1);
  line_cen100->SetLineStyle(2);
  
  TLine*line_cen140=new TLine(140,0.,140,1.);
  line_cen140->SetLineWidth(2);
  line_cen140->SetLineColor(6);
  line_cen140->SetLineStyle(2);
  
  TLine*line_cen160=new TLine(160,0.,160,1.);
  line_cen160->SetLineWidth(2);
  line_cen160->SetLineColor(kBlue);
  line_cen160->SetLineStyle(2);
  
  TLine*line_cen170=new TLine(170,0.,170,1.);
  line_cen170->SetLineWidth(2);
  line_cen170->SetLineColor(kRed);
  line_cen170->SetLineStyle(2);
  
  TLine*line_cen180=new TLine(180,0.,180,1.);
  line_cen180->SetLineWidth(2);
  line_cen180->SetLineColor(kOrange);
  line_cen180->SetLineStyle(2);
  
  TLine*line_cen190=new TLine(190,0.,190,1.);
  line_cen190->SetLineWidth(2);
  line_cen190->SetLineColor(kRed+2);
  line_cen190->SetLineStyle(2);

  
  const int nBins = 100;
  const double maxPt = 200;

  TH1D *hEmpty = new TH1D("hEmpty",";Offline centrality; Efficiency",nBins,0.,maxPt);

  TCanvas *c1 = new TCanvas();
  hEmpty->SetMinimum(0);
  hEmpty->SetMaximum(1.2);
  hEmpty->Draw();
  //c1->SetLogy();

  //asymm_cen_0_cen->Draw("p");
  asymm_cen_10_cen->Draw("p");
  asymm_cen_20_cen->Draw("p");
  asymm_cen_30_cen->Draw("p");
  asymm_cen_40_cen->Draw("p");
  asymm_cen_50_cen->Draw("p");
  asymm_cen_100_cen->Draw("p");
  asymm_cen_140_cen->Draw("p");
  asymm_cen_160_cen->Draw("p");
  asymm_cen_170_cen->Draw("p");
  asymm_cen_180_cen->Draw("p");
  asymm_cen_190_cen->Draw("p");

  TLegend *leg = new TLegend(0.3689777,0.205074,0.6427732,0.6257928,"L1 centrality threshold");
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSizePixels(20);

  leg->AddEntry(asymm_cen_10_cen,"L1 cen >10","lp");
  leg->AddEntry(asymm_cen_20_cen,"L1 cen >20","lp");
  leg->AddEntry(asymm_cen_30_cen,"L1 cen >30","lp");
  leg->AddEntry(asymm_cen_40_cen,"L1 cen >40","lp");
  leg->AddEntry(asymm_cen_50_cen,"L1 cen >50","lp");
  leg->AddEntry(asymm_cen_100_cen,"L1 cen >100","lp");
  leg->AddEntry(asymm_cen_140_cen,"L1 cen >140","lp");
  leg->AddEntry(asymm_cen_160_cen,"L1 cen >160","lp");
  leg->AddEntry(asymm_cen_170_cen,"L1 cen >170","lp");
  leg->AddEntry(asymm_cen_180_cen,"L1 cen >180","lp");
  leg->AddEntry(asymm_cen_190_cen,"L1 cen >190","lp");

  leg->Draw();
  line_cen10->Draw();
  line_cen20->Draw();
  line_cen30->Draw();
  line_cen40->Draw();
  line_cen50->Draw();
  line_cen100->Draw();
  line_cen140->Draw();
  line_cen160->Draw();
  line_cen170->Draw();
  line_cen180->Draw();
  line_cen190->Draw();

  c1->SaveAs("Plots/TurnOnCurveCentrality.pdf");

}

int main()
{
  makePrettyTurnOn();
  return 0;
}
