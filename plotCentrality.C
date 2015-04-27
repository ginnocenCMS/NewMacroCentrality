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
#include <TF1.h>
#include <TProfile.h>


#include <vector>
//#include <TMap.h>
#include <map>

using namespace std;

const int NBINSCentrality=6;
const int limit[5]={10,20,60,100,140};


void plotCentrality(TString l1_input, bool isdata=false)
{

	TFile *lFile = TFile::Open(Form("%s_CentralityCalibration.root",l1_input.Data()));
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

	TH1D *hOffline[NBINSCentrality];

	for(int i = 0; i < NBINSCentrality; ++i){
		hOffline[i]=(TH1D*)lFile->Get(Form("hOffline_Bin%d",i)); 
	}  

	TF1 *f1 = new TF1("f1","pol9",0,6500);
	TF1 *f2 = new TF1("f2","pol9",0,200.);
	TF1 *f3 = new TF1("f3","pol1",0,200.);
	f3->SetLineColor(2);
	f1->SetLineColor(1);
	f2->SetLineColor(1);


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

	hcorrl1EtsumPlusVscorrl1EtsumMinus->Draw();

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


	TCanvas *canvasofflineCentralityVsl1Etsum=new TCanvas("canvasofflineCentralityVsl1Etsum","canvas",600,500);
	canvasofflineCentralityVsl1Etsum->cd();
	profileofflineCentralityVsl1Etsum->GetXaxis()->SetRangeUser(0,6500.);
	profileofflineCentralityVsl1Etsum->GetYaxis()->SetRangeUser(0,250.);
	profileofflineCentralityVsl1Etsum->GetYaxis()->SetTitle("Offline Centrality (bins of 0.5%)");
	profileofflineCentralityVsl1Etsum->GetXaxis()->SetTitle("Emulator HF E_{T} sum");
	profileofflineCentralityVsl1Etsum->SetMarkerStyle(21);
	profileofflineCentralityVsl1Etsum->SetMarkerSize(0.6);
	profileofflineCentralityVsl1Etsum->GetXaxis()->SetTitleOffset(1.2);
	profileofflineCentralityVsl1Etsum->GetYaxis()->SetTitleOffset(1.2);
	profileofflineCentralityVsl1Etsum->Draw();
	profileofflineCentralityVsl1Etsum->Fit("f1");


	TCanvas *canvasl1EtsumVsofflineCentrality=new TCanvas("canvasl1EtsumVsofflineCentrality","canvas",600,500);
	canvasl1EtsumVsofflineCentrality->cd();
	profilel1EtsumVsofflineCentrality->GetYaxis()->SetRangeUser(0,6500.);
	profilel1EtsumVsofflineCentrality->GetXaxis()->SetRangeUser(0,250.);
	profilel1EtsumVsofflineCentrality->GetXaxis()->SetTitle("Offline Centrality (bins of 0.5%)");
	profilel1EtsumVsofflineCentrality->GetYaxis()->SetTitle("Emulator HF E_{T} sum");
	profilel1EtsumVsofflineCentrality->SetMarkerStyle(21);
	profilel1EtsumVsofflineCentrality->SetMarkerSize(0.6);
	profilel1EtsumVsofflineCentrality->GetXaxis()->SetTitleOffset(1.2);
	profilel1EtsumVsofflineCentrality->GetYaxis()->SetTitleOffset(1.2);
	profilel1EtsumVsofflineCentrality->Draw();
	profilel1EtsumVsofflineCentrality->Fit("f2");

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

	const Int_t COLORS[NBINSCentrality] = {kViolet+1,kRed+1,kBlue+1,kGreen+1,1,30};

	TCanvas *canvasranges=new TCanvas("canvasranges","canvasranges",600,500);
	canvasranges->cd();

	hOffline[0]->SetMaximum(300);
	hOffline[0]->GetXaxis()->SetRangeUser(-10,210.);
	hOffline[0]->GetYaxis()->SetTitleOffset(1.5);

	for(int j=0;j<NBINSCentrality;j++){

		hOffline[j]->Sumw2();
		hOffline[j]->SetMarkerStyle(0);
		hOffline[j]->SetLineColor(COLORS[j]);
		hOffline[j]->SetFillStyle(3325);
		hOffline[j]->SetFillColor(COLORS[j]);
	}
	for(int j=0;j<NBINSCentrality;j++){
		hOffline[j]->Draw("same hist e");

	}

	TLegend *leg = new TLegend(0.340604,0.5940803,0.8741611,0.8816068,"L1 centrality threshold");
	leg->SetFillColor(0);
	leg->SetTextFont(42);
	leg->SetTextSizePixels(20);


	leg->AddEntry(hOffline[0],Form("0  < L1cen < %d",limit[0]),"lp");
	leg->AddEntry(hOffline[1],Form("%d < L1cen < %d",limit[0],limit[1]),"lp");
	leg->AddEntry(hOffline[2],Form("%d < L1cen < %d",limit[1],limit[2]),"lp");
	leg->AddEntry(hOffline[3],Form("%d < L1cen < %d",limit[2],limit[3]),"lp");
	leg->AddEntry(hOffline[4],Form("%d< L1cen < %d", limit[3],limit[4]),"lp");
	leg->AddEntry(hOffline[5],Form("%d< L1cen < 200",limit[4]),"lp");
	leg->Draw();  

	double Etsum[NBINSCentrality];

	for (int m=0;m<NBINSCentrality-1;m++){

		Etsum[m]=fprofileofflinel1EtsumVsCentrality_Calibration->Eval(limit[m]);
	}

	cout<<"***************************"<<endl;
	cout<<"LUT for centrality ranges"<<endl;
	cout<<"Centrality 0-5% = E_{T} sum > "<<Etsum[0]<<endl;
	cout<<"Centrality 5-10% ="<<Etsum[1]<<"<E_{T} sum <"<<Etsum[0]<<endl;
	cout<<"Centrality 10-30% ="<<Etsum[2]<<"<E_{T} sum <"<<Etsum[1]<<endl;
	cout<<"Centrality 30-50% ="<<Etsum[3]<<"<E_{T} sum <"<<Etsum[2]<<endl;
	cout<<"Centrality 50-90% ="<<Etsum[4]<<"<E_{T} sum <"<<Etsum[3]<<endl;
	cout<<"Centrality "<<(int)(limit[4]/2)<<"-100% =  E_{T} sum <"<<Etsum[4]<<endl;


	if(!isdata){

		TH1D *hNcoll[NBINSCentrality];

		for(int i = 0; i < NBINSCentrality; ++i){
			hNcoll[i]=(TH1D*)lFile->Get(Form("hNcoll_Bin%d",i)); 
			hNcoll[i]->Rebin(5);
		}  

		TCanvas *canvasrangesNcoll=new TCanvas("canvasrangesNcoll","canvasrangesNcoll",600,500);
		canvasrangesNcoll->cd();

		hNcoll[0]->SetMaximum(300);
		hNcoll[0]->GetXaxis()->SetRangeUser(-0.5,1999.5);
		hNcoll[0]->GetYaxis()->SetTitleOffset(1.5);

		for(int j=0;j<NBINSCentrality;j++){

			hNcoll[j]->Sumw2();
			hNcoll[j]->SetMarkerStyle(0);
			hNcoll[j]->SetLineColor(COLORS[j]);
			hNcoll[j]->SetFillStyle(3325);
			hNcoll[j]->SetFillColor(COLORS[j]);
		}
		for(int j=0;j<NBINSCentrality;j++){
			hNcoll[j]->Draw("same hist e");

		}

		TLegend *leg = new TLegend(0.340604,0.5940803,0.8741611,0.8816068,"L1 centrality threshold");
		leg->SetFillColor(0);
		leg->SetTextFont(42);
		leg->SetTextSizePixels(20);

		leg->AddEntry(hNcoll[0],Form("0  < L1cen < %d",limit[0]),"lp");
		leg->AddEntry(hNcoll[1],Form("%d < L1cen < %d",limit[0],limit[1]),"lp");
		leg->AddEntry(hNcoll[2],Form("%d < L1cen < %d",limit[1],limit[2]),"lp");
		leg->AddEntry(hNcoll[3],Form("%d < L1cen < %d",limit[2],limit[3]),"lp");
		leg->AddEntry(hNcoll[4],Form("%d< L1cen < %d", limit[3],limit[4]),"lp");
		leg->AddEntry(hNcoll[5],Form("%d< L1cen < 200",limit[4]),"lp");
		leg->Draw();

		canvasranges->SaveAs(Form("Plots/canvasranges_%s.eps",l1_input.Data()));
		canvasl1CentralityVsofflineCentrality->SaveAs(Form("Plots/canvasl1CentralityVsofflineCentrality_%s.pdf",l1_input.Data()));
		canvasL1CentralityVsfflineCentrality->SaveAs(Form("Plots/canvasL1CentralityVsfflineCentrality_%s.pdf",l1_input.Data()));
		canvasl1EtsumVsofflineCentrality->SaveAs(Form("Plots/canvasl1EtsumVsofflineCentrality_%s.pdf",l1_input.Data()));
		canvasofflineCentralityVsl1Etsum->SaveAs(Form("Plots/canvasofflineCentralityVsl1Etsum_%s.pdf",l1_input.Data()));
		canvasL1Etsum->SaveAs(Form("Plots/canvasL1Etsum_%s.pdf",l1_input.Data()));
		canvasOfflineEtsumVsL1Etsum->SaveAs(Form("Plots/canvasOfflineEtsumVsL1Etsum_%s.pdf",l1_input.Data()));
		canvasOfflineCentrality->SaveAs(Form("Plots/canvasOfflineCentrality_%s.pdf",l1_input.Data()));
		canvascorrl1EtsumPlusVscorrl1EtsumMinus->SaveAs(Form("Plots/canvascorrl1EtsumPlusVscorrl1EtsumMinus_%s.pdf",l1_input.Data()));
		canvascorrl1EtsumPlusVscorrl1EtsumMinus->SaveAs(Form("Plots/canvascorrl1EtsumPlusVscorrl1EtsumMinusNo_%s.pdf",l1_input.Data()));
		canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel->SaveAs(Form("Plots/canvascorrl1EtsumPlusVscorrl1EtsumMinusNoEvSel_%s.pdf",l1_input.Data()));
		canvasrangesNcoll->SaveAs(Form("Plots/canvasrangesNcoll_%s.pdf",l1_input.Data()));

	}
}


int main(int argc, char **argv)
{
	if(argc == 2)
	{
		plotCentrality(argv[1], argv[2]);
		return 0;
	}
	else
	{
		std::cout << "Usage: \nmakeTurnOn_fromSameFile.exe <input_HiForest_file> <output_file>" << std::endl;
		return 1;
	}
}
