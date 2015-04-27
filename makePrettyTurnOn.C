#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>

const int NThresholds=12;
const Double_t L1_THRESHOLD[NThresholds] = {0.,10.,20.,30.,40.,50.,100.,140.,160.,170.,180.,190.};
const Int_t COLORS[NThresholds] = {1, 1, kBlue,kRed,kOrange,kRed+2,1,6,kBlue,kRed,kOrange,kRed+2 };

void makePrettyTurnOn(){

	gROOT->SetStyle("Plain");	
	gStyle->SetOptStat(0);
	gStyle->SetOptStat(0000);
	gStyle->SetPalette(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetOptTitle(0);

	TFile *inFile = TFile::Open("Hydjet502MC_CentralityCalibration.root");
	TGraphAsymmErrors *asymm[NThresholds];//[2];
	TLine*line[NThresholds];
	for(int i = 1; i < NThresholds; i++)
	{
		asymm[i] = (TGraphAsymmErrors*)inFile->Get(Form("asymm_cen_%d_cen",(int)L1_THRESHOLD[i]));
		asymm[i]->SetMarkerColor(COLORS[i]);
		asymm[i]->SetLineColor(COLORS[i]);
		line[i]=new TLine(L1_THRESHOLD[i],0.,L1_THRESHOLD[i],1.);
		line[i]->SetLineWidth(2);
		line[i]->SetLineStyle(2);
		line[i]->SetLineColor(COLORS[i]);
	}

	const int nBins = 100;
	const double maxPt = 200;

	TH1D *hEmpty = new TH1D("hEmpty",";Offline centrality; Efficiency",nBins,0.,maxPt);

	TCanvas *c1 = new TCanvas();
	hEmpty->SetMinimum(0);
	hEmpty->SetMaximum(1.2);
	hEmpty->Draw();


	for(int i = 1; i < NThresholds; i++){
		asymm[i]->Draw("p");
	}

	TLegend *leg = new TLegend(0.3689777,0.205074,0.6427732,0.6257928,"L1 centrality threshold");
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->SetTextSizePixels(20);

	for(int i = 1; i < NThresholds; i++){
		leg->AddEntry(asymm[i],Form("L1 cen >%d",(int)L1_THRESHOLD[i]),"lp");
		line[i]->Draw();
	}

	leg->Draw();

	c1->SaveAs("Plots/TurnOnCurveCentrality.pdf");

}

int main()
{
	makePrettyTurnOn();
	return 0;
}
