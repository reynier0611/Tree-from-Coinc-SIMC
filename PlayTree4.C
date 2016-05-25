#include "TFile.h"
#include "TTree.h"

int electron = 0;	int hadron = 1;
int ytar = 0;	int delta = 1;	int yptar = 2;	int xptar = 3;
int entries;
// ===========================================================================================
void PlayTree4(){


	// ************************************************************
	// CREATE AND INITIALIZE HISTOGRAMS
	TH1F** h_electron  	= new TH1F*[4];
	TH1F** h_hadron	   	= new TH1F*[4];
	TH1F** h_electron_res 	= new TH1F*[4];
	TH1F** h_hadron_res   	= new TH1F*[4];

	for(int i = 0 ; i < 2; i++){
		h_electron[i]  = new TH1F("","",100,-6,   6   );	h_hadron[i]  = new TH1F("","",100,-6,   6   );
		h_electron[i+2]= new TH1F("","",100,-0.07,0.07);	h_hadron[i+2]= new TH1F("","",100,-0.07,0.07);

		h_electron_res[i]    = new TH1F("","",100,  -0.4,     	0.4  );
		h_hadron_res  [i]    = new TH1F("","",100,  -0.4,     	0.4  );
		h_electron_res[i+2]  = new TH1F("","",100,  -0.006,	0.006);
		h_hadron_res  [i+2]  = new TH1F("","",100,  -0.006,  	0.006);
	}

	TH2F* h2_e_d_y    = new TH2F("e_d_y"     ,"e_d_y"     , 80,    -6,    6, 80,    -6,    6);
	TH2F* h2_h_d_y    = new TH2F("h_d_y"     ,"h_d_y"     , 80,    -6,    6, 80,    -6,    6);
	TH2F* h2_e_ip_op  = new TH2F("e_ip_op"   ,"e_ip_op"   , 80, -0.07, 0.07, 80, -0.07, 0.07);
        TH2F* h2_h_ip_op  = new TH2F("h_ip_op"   ,"h_ip_op"   , 80, -0.07, 0.07, 80, -0.07, 0.07);
	// ************************************************************



	// ****************************************************************************************
	// OPEN TREE, ACCESS BRANCHES, AND LOAD VARIABLES
	TFile *f = new TFile("fastkinematics.root");
	TTree *T = (TTree*)f->Get("h666");		entries = T -> GetEntries();

	//Load Electron Variables
	Float_t hsytar;         Float_t hsdelta;	Float_t hsyptar;        Float_t hsxptar;
	Float_t hsytari;        Float_t hsdeltai;       Float_t hsyptari;       Float_t hsxptari;
	T->SetBranchAddress("hsytar"    ,&hsytar);	T->SetBranchAddress("hsdelta"   ,&hsdelta);
	T->SetBranchAddress("hsyptar"   ,&hsyptar);	T->SetBranchAddress("hsxptar"   ,&hsxptar);
	T->SetBranchAddress("hsytari"   ,&hsytari);     T->SetBranchAddress("hsdeltai"  ,&hsdeltai);
	T->SetBranchAddress("hsyptari"  ,&hsyptari);    T->SetBranchAddress("hsxptari"  ,&hsxptari);

	//Load Hadron Variables
	Float_t ssytar;         Float_t ssdelta;	Float_t ssyptar;        Float_t ssxptar;
	Float_t ssytari;        Float_t ssdeltai;       Float_t ssyptari;       Float_t ssxptari;
	T->SetBranchAddress("ssytar"    ,&ssytar);	T->SetBranchAddress("ssdelta"   ,&ssdelta);
	T->SetBranchAddress("ssyptar"   ,&ssyptar);	T->SetBranchAddress("ssxptar"   ,&ssxptar);
	T->SetBranchAddress("ssytari"   ,&ssytari);     T->SetBranchAddress("ssdeltai"  ,&ssdeltai);
	T->SetBranchAddress("ssyptari"  ,&ssyptari);    T->SetBranchAddress("ssxptari"  ,&ssxptari);
	// ****************************************************************************************



	// **********************************************************************************
	// FILL HISTOGRAMS	
	for (int i = 0 ; i < entries ; i++){
		T->GetEntry(i);	
		h_electron[ytar ] -> Fill(hsytar );	h_electron[delta] -> Fill(hsdelta);
		h_electron[yptar] -> Fill(hsyptar);	h_electron[xptar] -> Fill(hsxptar);
		h_hadron  [ytar ] -> Fill(ssytar );     h_hadron  [delta] -> Fill(ssdelta);
		h_hadron  [yptar] -> Fill(ssyptar);     h_hadron  [xptar] -> Fill(ssxptar);

		h_electron_res [ytar ] 	-> Fill(hsytar  - hsytari );
		h_electron_res [delta] 	-> Fill(hsdelta - hsdeltai);
		h_electron_res [yptar] 	-> Fill(hsyptar - hsyptari);
		h_electron_res [xptar] 	-> Fill(hsxptar - hsxptari);
		h_hadron_res   [ytar ] 	-> Fill(ssytar  - ssytari );
		h_hadron_res   [delta] 	-> Fill(ssdelta - ssdeltai);
		h_hadron_res   [yptar] 	-> Fill(ssyptar - ssyptari);
		h_hadron_res   [xptar] 	-> Fill(ssxptar - ssxptari);
		h2_e_d_y		-> Fill(hsytar , hsdelta);
		h2_h_d_y                -> Fill(ssytar , ssdelta);
		h2_e_ip_op              -> Fill(hsxptar, hsyptar);
		h2_h_ip_op              -> Fill(ssxptar, ssyptar);
	}
	// **********************************************************************************



	// ***************************************************
	// FORMAT AND EDIT HISTOGRAMS
	for(int i = 0 ; i < 4 ; i++){
		Pretty1D( h_electron    [i]  , 1 , electron , i );
		Pretty1D( h_hadron      [i]  , 2 , hadron   , i );
		Pretty1D( h_electron_res[i]  , 1 , electron , i );
		Pretty1D( h_hadron_res  [i]  , 2 , hadron   , i );
	}
	Pretty2D(h2_e_d_y   , 	ytar  , delta , electron);
	Pretty2D(h2_h_d_y   , 	ytar  , delta , hadron  );
	Pretty2D(h2_e_ip_op , 	xptar , yptar , electron);
	Pretty2D(h2_h_ip_op , 	xptar , yptar , hadron  );
	// ***************************************************



	// ******************************************************
	// Drawing the histograms
	leg = new TLegend(0.6,0.6,0.89,0.89);
	leg->SetTextSize(0.05);
	leg->AddEntry( h_electron[0]	,"electron arm");
	leg->AddEntry( h_hadron  [0]	,"hadron arm");
	int ci = 925;		color = new TColor(ci, 0, 0, 0, " ", 0);
	leg->SetLineColor(ci);	leg->SetLineStyle(1);	leg->SetLineWidth(1);

	// **********************************************************************************
	// PLOT HISTOGRAMS
	TCanvas *c1 = new TCanvas("c1","Variables",900,700);
	gStyle->SetOptStat(0);
	c1->Divide(2,2);

	for(int i = 0 ; i < 4 ; i++){
		h_electron[i]->SetMaximum(100 + FindHistMax(h_hadron[i] , h_electron[i]));
		h_hadron  [i]->SetMaximum(100 + FindHistMax(h_hadron[i] , h_electron[i]));
		c1->cd(i+1);	h_hadron[i] -> Draw();	h_electron[i] -> Draw("same");
		if(i==0){leg->Draw("same");} 
	}

	TCanvas *c2 = new TCanvas("c2","Resolution",900,700);
	c2->Divide(2,2);

	for(int i = 0 ; i < 4 ; i++){
		h_electron_res[i]->SetMaximum(100 + FindHistMax(h_hadron_res[i] , h_electron_res[i]));
                h_hadron_res  [i]->SetMaximum(100 + FindHistMax(h_hadron_res[i] , h_electron_res[i]));
		c2->cd(i+1);    h_hadron_res[i] -> Draw();	h_electron_res[i] -> Draw("same");
		if(i==1){leg->Draw("same");}
	}

	TCanvas *c3 = new TCanvas("c3","2D histos",1000,700);
        c3->Divide(2,2);
        c3->cd(1);		h2_e_d_y   -> Draw("COLZ");      
	c3->cd(2);		h2_h_d_y   -> Draw("COLZ");
	c3->cd(3);              h2_e_ip_op -> Draw("COLZ");
	c3->cd(4);              h2_h_ip_op -> Draw("COLZ");
	// **********************************************************************************

} //END MAIN FUNCTION

// ===========================================================================================
// FUNCTION TO EDIT 1D HISTOGRAMS
void Pretty1D(TH1F *gP, int k, int part, int var){
	int color; int style; int linestyle;
	if( k == 0){ color = 1; style = 3004;}
	if( k == 1){ color = 2; style = 3005;}
	if( k == 2){ color = 4; style = 3004;}
	if( k == 3){ color = 3; style = 3007;}
	if( k == 4){ color = 7; style = 3006;}
	if( k == 5){ color = 6; style = 3005;}

	AddLabels1D(gP, part, var);

	gP -> SetLineColor(color);
	gP -> SetFillColor(color);
	gP -> SetFillStyle(style);
	gP -> SetMarkerColor(color);
	gP -> GetXaxis()->SetTitleSize(0.05);
	//gP -> GetXaxis()->SetRangeUser(0,5);
	gP -> GetYaxis()->SetLabelSize (0.05);
	gP -> GetXaxis()->SetLabelSize (0.05);
	//gP -> GetXaxis()->SetNdivisions(505);
}

// ===========================================================================================
// FUNCTION TO EDIT 2D HISTOGRAMS
void Pretty2D(TH2F *gP, int xvar, int yvar, int part){
        AddLabels2D(gP, xvar, yvar, part);
        AddTitle2D (gP, xvar, yvar, part);
	gP -> GetYaxis()->SetTitleSize(0.05);
 	gP -> GetXaxis()->SetTitleSize(0.05);     
        gP -> GetYaxis()->SetLabelSize(0.05);
        gP -> GetXaxis()->SetLabelSize(0.05); 
}


// ===========================================================================================
// FUNCTION TO ADD LABELS TO 1D HISTOGRAMS
void AddLabels1D(TH1F *gP, int part, int var){
	if(var == ytar	){gP->GetXaxis()->SetTitle("y (target) [cm]");}
	if(var == delta	){gP->GetXaxis()->SetTitle("delta [%]");}
	if(var == yptar	){gP->GetXaxis()->SetTitle("in-plane angle [mrad]");}
	if(var == xptar	){gP->GetXaxis()->SetTitle("out-of-plane angle [mrad]");}
}

// ===========================================================================================
// FUNCTION TO ADD LABELS TO 2D HISTOGRAMS
void AddLabels2D(TH2F *gP, int xvar, int yvar, int part){
        if(xvar == ytar  ){gP->GetXaxis()->SetTitle("y (target) [cm]");}
        if(xvar == delta ){gP->GetXaxis()->SetTitle("delta [%]");}
        if(xvar == yptar ){gP->GetXaxis()->SetTitle("in-plane angle [mrad]");}
        if(xvar == xptar ){gP->GetXaxis()->SetTitle("out-of-plane angle [mrad]");}
	
	if(yvar == ytar  ){gP->GetYaxis()->SetTitle("y (target) [cm]");}
        if(yvar == delta ){gP->GetYaxis()->SetTitle("delta [%]");}
        if(yvar == yptar ){gP->GetYaxis()->SetTitle("in-plane angle [mrad]");}
        if(yvar == xptar ){gP->GetYaxis()->SetTitle("out-of-plane angle [mrad]");}
}

// ===========================================================================================
// FUNCTION TO ADD TITLE TO 2D HISTOGRAMS
void AddTitle2D(TH2F *gP, int xvar, int yvar, int part){
        if(part == electron){gP->SetTitle("electron arm");}
	if(part == hadron  ){gP->SetTitle("hadron arm"  );}
	gStyle->SetTitleSize(0.09,"t");
}

// ===========================================================================================
// GET MAXIMUM OF TWO HISTOGRAMS
float FindHistMax(TH1F *h1,TH1F *h2){
float max1 = h1->GetMaximum();
float max2 = h2->GetMaximum();

if(max1  > max2){return max1;}
if(max1  < max2){return max2;}
if(max1 == max2){return max2;}
}
