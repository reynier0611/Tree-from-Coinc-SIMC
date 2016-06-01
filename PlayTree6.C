#include "TFile.h"
#include "TTree.h"

int electron = 0;	int hadron = 1;		int both = 2;
int ytar     = 0;	int delta  = 1;		int yptar = 2;
int xptar    = 3;	int moment = 4;
int entries;

float Pe_cent = 3334.21; //MeV/c
float Pp_cent = 2004.06; //MeV/c
// ===========================================================================================
void PlayTree6(){


	// ************************************************************
	// CREATE AND INITIALIZE HISTOGRAMS
	TH1F** h_electron  	= new TH1F*[4];
	TH1F** h_hadron	   	= new TH1F*[4];

	h_electron [ytar]  = new TH1F("","",100,   -3,   3);        h_hadron [ytar]  = new TH1F("","",100,   -3,   3);
	h_electron[delta]  = new TH1F("","",100,  -20,   5);        h_hadron[delta]  = new TH1F("","",100,  -20,   5);
	h_electron[yptar]  = new TH1F("","",100,-0.06,0.06);        h_hadron[yptar]  = new TH1F("","",100,-0.06,0.06);
	h_electron[xptar]  = new TH1F("","",100, -0.2, 0.2);        h_hadron[xptar]  = new TH1F("","",100, -0.2, 0.2);

	TH2F* h2_e_d_y     = new TH2F("e_d_y"     ,"e_d_y"     , 70,    -6,    1, 70,    -6,   -8);
	TH2F* h2_h_d_y     = new TH2F("h_d_y"     ,"h_d_y"     , 70,    -3,    3, 70,    -6,    6);
	TH2F* h2_e_ip_op   = new TH2F("e_ip_op"   ,"e_ip_op"   , 70, -0.15, 0.15, 70, -0.06, 0.06);
	TH2F* h2_h_ip_op   = new TH2F("h_ip_op"   ,"h_ip_op"   , 70, -0.08, 0.08, 70, -0.04, 0.04);

	TH2F* h2_y_evh     = new TH2F("y_evh"     ,"y_evh"     , 80,    -3,     3, 80,   -1,    1);
	TH2F* h2_delta_evh = new TH2F("delta_evh" ,"delta_evh" , 80,  -5.5,  -5.5, 80,   -6,   -2);
	TH2F* h2_ip_evh    = new TH2F("ip_evh"    ,"ip_evh"    , 80,  -0.1,  -0.1, 80, -0.1,  0.1);
	TH2F* h2_op_evh    = new TH2F("op_evh"    ,"ip_evh"    , 80, -0.08,  0.08, 80,-0.15, 0.15);

	TH2F* h2_e_pvip    = new TH2F("e_pvip"     ,"e_pvip"   , 80, -0.06,  0.06, 80,   2600,    3300);
	TH2F* h2_e_pvop    = new TH2F("e_pvop"     ,"e_pvop"   , 80,  -0.2,   0.2, 80,   2500,    3300);
	TH2F* h2_h_pvip    = new TH2F("h_pvip"     ,"h_pvip"   , 80, -0.04,  0.04, 80,   1850,    2100);
	TH2F* h2_h_pvop    = new TH2F("h_pvop"     ,"h_pvop"   , 80,  -0.1,   0.1, 80,   1850,    2100);

	// ************************************************************



	// ****************************************************************************************
	// OPEN TREE, ACCESS BRANCHES, AND LOAD VARIABLES
	TFile *f = new TFile("hydrogen.root");
	TTree *T = (TTree*)f->Get("h666");		entries = T -> GetEntries();
	Float_t Weight;		T->SetBranchAddress("Weight"    ,&Weight);
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

		// 1D histograms
		h_electron[ytar ] -> Fill(hsytar );     	h_electron[delta] -> Fill(hsdelta);
		h_electron[yptar] -> Fill(hsyptar);     	h_electron[xptar] -> Fill(hsxptar);
		h_hadron  [ytar ] -> Fill(ssytar );     	h_hadron  [delta] -> Fill(ssdelta);
		h_hadron  [yptar] -> Fill(ssyptar);     	h_hadron  [xptar] -> Fill(ssxptar);

		// 2D histograms
		h2_e_d_y		-> Fill(hsytar , hsdelta);
		h2_h_d_y                -> Fill(ssytar , ssdelta);
		h2_e_ip_op              -> Fill(hsxptar, hsyptar);
		h2_h_ip_op              -> Fill(ssxptar, ssyptar);

		h2_y_evh		-> Fill(ssytar , hsytar);
		h2_delta_evh		-> Fill(ssdelta,hsdelta);
		h2_ip_evh   		-> Fill(ssyptar,hsyptar);
		h2_op_evh   		-> Fill(ssxptar,hsxptar);

		h2_e_pvip		-> Fill(hsyptar, Pe_cent*(1+hsdelta/100));
		h2_e_pvop		-> Fill(hsxptar, Pe_cent*(1+hsdelta/100));
		h2_h_pvip		-> Fill(ssyptar, Pp_cent*(1+ssdelta/100));
		h2_h_pvop		-> Fill(ssxptar, Pp_cent*(1+ssdelta/100));
	}
	// **********************************************************************************



	// ***************************************************
	// FORMAT AND EDIT HISTOGRAMS
	for(int i = 0 ; i < 4 ; i++){
		Pretty1D( h_electron    [i]  , 1 , electron , i );
		Pretty1D( h_hadron      [i]  , 2 , hadron   , i );
	}
	Pretty2D(h2_e_d_y     ,   ytar  , delta , electron);
	Pretty2D(h2_h_d_y     ,   ytar  , delta , hadron  );
	Pretty2D(h2_e_ip_op   ,   xptar , yptar , electron);
	Pretty2D(h2_h_ip_op   ,   xptar , yptar , hadron  );

	Pretty2D(h2_y_evh     ,   ytar  , ytar  , both    );
	Pretty2D(h2_delta_evh ,   delta , delta , both    );
	Pretty2D(h2_ip_evh    ,   yptar , yptar , both    );
	Pretty2D(h2_op_evh    ,   xptar , xptar , both    );

	Pretty2D(h2_e_pvip    ,   yptar , moment, electron);
	Pretty2D(h2_e_pvop    ,   xptar , moment, electron);
	Pretty2D(h2_h_pvip    ,   yptar , moment, hadron  );
	Pretty2D(h2_h_pvop    ,   xptar , moment, hadron  );
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

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++
	TCanvas *c2 = new TCanvas("23","2D histos",1000,700);
	c2->Divide(2,2);
	c2->cd(1);		h2_e_d_y   -> Draw("COLZ");      
	c2->cd(2);		h2_h_d_y   -> Draw("COLZ");
	c2->cd(3);              h2_e_ip_op -> Draw("COLZ");
	c2->cd(4);              h2_h_ip_op -> Draw("COLZ");

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++
	TCanvas *c3 = new TCanvas("c3","Correlated",1000,700);
	c3->Divide(2,2);
	c3->cd(1);         	h2_y_evh     -> Draw("COLZ");    
	c3->cd(2);            	h2_delta_evh -> Draw("COLZ");
	c3->cd(3);           	h2_ip_evh    -> Draw("COLZ");
	c3->cd(4);          	h2_op_evh    -> Draw("COLZ");

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++
	TCanvas *c4 = new TCanvas("c4","Momentum vs angles",1000,700);
	c4->Divide(2,2);
	c4->cd(1);              h2_e_pvip    -> Draw("COLZ");   
	c4->cd(2);              h2_e_pvop    -> Draw("COLZ");
	c4->cd(3);              h2_h_pvip    -> Draw("COLZ");
	c4->cd(4);              h2_h_pvop    -> Draw("COLZ");

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
	if(xvar == ytar  ){gP->GetXaxis()->SetTitle("y (target) [cm]"          );}
	if(xvar == delta ){gP->GetXaxis()->SetTitle("delta [%]"                );}
	if(xvar == yptar ){gP->GetXaxis()->SetTitle("in-plane angle [mrad]"    );}
	if(xvar == xptar ){gP->GetXaxis()->SetTitle("out-of-plane angle [mrad]");}
	if(xvar == moment){gP->GetXaxis()->SetTitle("Momentum [MeV/c]"         );}

	if(yvar == ytar  ){gP->GetYaxis()->SetTitle("y (target) [cm]");}
	if(yvar == delta ){gP->GetYaxis()->SetTitle("delta [%]");}
	if(yvar == yptar ){gP->GetYaxis()->SetTitle("in-plane angle [mrad]");}
	if(yvar == xptar ){gP->GetYaxis()->SetTitle("out-of-plane angle [mrad]");}
	if(yvar == moment){gP->GetYaxis()->SetTitle("Momentum [MeV/c]"         );}
}

// ===========================================================================================
// FUNCTION TO ADD TITLE TO 2D HISTOGRAMS
void AddTitle2D(TH2F *gP, int xvar, int yvar, int part){
	if(part == electron){gP->SetTitle("electron arm"       );}
	if(part == hadron  ){gP->SetTitle("hadron arm"         );}
	if(part == both    ){gP->SetTitle("electron vs. hadron");}
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

/*

   delta = 100 [p - p(central)] / p(central)

   p = p(central)[1 + delta/100]

 */

/*

   TH1F** h_electron_res   = new TH1F*[4];
   TH1F** h_hadron_res     = new TH1F*[4];

   for(int i = 0 ; i < 2; i++){
   h_electron_res[i]    = new TH1F("","",100,  -0.4,       0.4  );
   h_hadron_res  [i]    = new TH1F("","",100,  -0.4,       0.4  );
   h_electron_res[i+2]  = new TH1F("","",100,  -0.006,     0.006);
   h_hadron_res  [i+2]  = new TH1F("","",100,  -0.006,     0.006);
   }

   h_electron_res [ytar ]  -> Fill(hsytar  - hsytari );
   h_electron_res [delta]  -> Fill(hsdelta - hsdeltai);
   h_electron_res [yptar]  -> Fill(hsyptar - hsyptari);
   h_electron_res [xptar]  -> Fill(hsxptar - hsxptari);
   h_hadron_res   [ytar ]  -> Fill(ssytar  - ssytari );
   h_hadron_res   [delta]  -> Fill(ssdelta - ssdeltai);
   h_hadron_res   [yptar]  -> Fill(ssyptar - ssyptari);
   h_hadron_res   [xptar]  -> Fill(ssxptar - ssxptari);

   for(int i = 0 ; i < 4 ; i++){
   Pretty1D( h_electron_res[i]  , 1 , electron , i );
   Pretty1D( h_hadron_res  [i]  , 2 , hadron   , i );
   }

   TCanvas *c2 = new TCanvas("c2","Resolution",900,700);
   c2->Divide(2,2);

   for(int i = 0 ; i < 4 ; i++){
   h_electron_res[i]->SetMaximum(100 + FindHistMax(h_hadron_res[i] , h_electron_res[i]));
   h_hadron_res  [i]->SetMaximum(100 + FindHistMax(h_hadron_res[i] , h_electron_res[i]));
   c2->cd(i+1);    h_hadron_res[i] -> Draw();      h_electron_res[i] -> Draw("same");
   if(i==1){leg->Draw("same");}
   }


 */

















