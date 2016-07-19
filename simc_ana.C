#include "TFile.h"
#include "TTree.h"

int electron = 0;	int hadron = 1;		int both  = 2;
int ytar     = 0;	int delta  = 1;		int yptar = 2;
int xptar    = 3;	int moment = 4;		int pmiss = 5;
int emiss    = 6;
int entries;

float Pe_cent     = 3470.15; //MeV/c
float Pp_cent     = 1606.68; //MeV/c
float Thetae_cent = 20.862 ; //deg
float Thetap_cent = 48.6763; //deg

float normfact;
float counts  ;
float coefficient; int exponent;
// ===========================================================================================
void simc_ana(){

	cout << "Introduce number of counts: ";
	cin >> counts;
	cout << "Introduce normfact: coefficient = "; cin >> coefficient;
	cout << "Introduce normfact: exponent = "; cin >> exponent;
	normfact = coefficient*pow(10, exponent);
	// ************************************************************
	// CREATE AND INITIALIZE HISTOGRAMS
	TH1F* h1_Pm     = new TH1F("Pmiss"      ,"Pmiss"    , 50,     0,  0.5);	

	// ************************************************************



	// ****************************************************************************************
	// OPEN TREE, ACCESS BRANCHES, AND LOAD VARIABLES
        int flag = 2;
	if(flag == 1){ TFile *f = new TFile( "rey_he3_fastk_sf_1days.root" );}
	if(flag == 2){ TFile *f = new TFile( "rey_he3_slowk_sf_8days.root" );}

	TTree *T = (TTree*)f->Get("h666");		entries = T -> GetEntries();
	Float_t Weight;		T->SetBranchAddress("Weight"  ,&Weight);
	Float_t Em;	        T->SetBranchAddress("Em"      ,&Em    );
	Float_t Pm;		T->SetBranchAddress("Pm"      ,&Pm    );
	Float_t Pmpar;		T->SetBranchAddress("Pmpar"   ,&Pmpar );
	
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
	        
		// Cut to reduce FSI
		if(-acos(Pmpar / Pm) < 0.698){
			h1_Pm -> Fill(Pm, Weight*normfact/counts);
		}
	}
	// **********************************************************************************
	double integral;
	integral = h1_Pm->Integral();
	cout << integral <<endl;
	// ***************************************************
	// FORMAT AND EDIT HISTOGRAMS
	
	Pretty1D( h1_Pm  , 1 , both , pmiss);

	// **********************************************************************************
	// PLOT HISTOGRAMS
	TCanvas *c6 = new TCanvas("c6","Missing Momentum",900,700);
        gStyle->SetOptStat(0);
	h1_Pm -> Draw();

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
void Pretty2D(TH2F *gP, int xvar, int yvar, int xpart, int ypart){
	AddLabels2D(gP, xvar, yvar, xpart , ypart);
	AddTitle2D (gP, xvar, yvar, xpart , ypart);
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
	if(var == pmiss ){gP->GetXaxis()->SetTitle("|P_{miss}| [GeV/c]");}
}

// ===========================================================================================
// FUNCTION TO ADD LABELS TO 2D HISTOGRAMS
void AddLabels2D(TH2F *gP, int xvar, int yvar, int xpart, int ypart){
	if(xvar == ytar  ){gP->GetXaxis()->SetTitle("y (target) [cm]"          );}
	if(xvar == delta ){gP->GetXaxis()->SetTitle("delta [%]"                );}
	if(xvar == yptar ){gP->GetXaxis()->SetTitle("in-plane angle [deg]"    );}
	if(xvar == xptar ){gP->GetXaxis()->SetTitle("out-of-plane angle [deg]");}
	if(xvar == moment){gP->GetXaxis()->SetTitle("Momentum [MeV/c]"         );}
	if(xvar == pmiss ){gP->GetXaxis()->SetTitle("Missing Momentum [GeV/c]" );}
	if(xvar == emiss ){gP->GetXaxis()->SetTitle("Missing Energy [GeV]"     );}

	if(yvar == ytar  ){gP->GetYaxis()->SetTitle("y (target) [cm]");}
	if(yvar == delta ){gP->GetYaxis()->SetTitle("delta [%]");}
	if(yvar == yptar ){gP->GetYaxis()->SetTitle("in-plane angle [deg]");}
	if(yvar == xptar ){gP->GetYaxis()->SetTitle("out-of-plane angle [deg]");}
	if(yvar == moment){gP->GetYaxis()->SetTitle("Momentum [MeV/c]"         );}
	if(yvar == pmiss ){gP->GetYaxis()->SetTitle("Missing Momentum [GeV/c]" );}
        if(yvar == emiss ){gP->GetYaxis()->SetTitle("Missing Energy [GeV]"     );}
}

// ===========================================================================================
// FUNCTION TO ADD TITLE TO 2D HISTOGRAMS
void AddTitle2D(TH2F *gP, int xvar, int yvar, int xpart, int ypart){
	if((xpart==electron) && (ypart==electron)){gP->SetTitle("electron arm"       );}
	if((xpart==hadron  ) && (ypart==hadron  )){gP->SetTitle("hadron arm"         );}
	if((xpart==hadron  ) && (ypart==electron)){gP->SetTitle("electron vs. hadron");}
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

















