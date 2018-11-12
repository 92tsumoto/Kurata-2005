
#include "syspara.h"

void val_consts(FILE *fp1)
{
	int i,w;
	double v_old,dvdt,dvdt_new;

	// unitiy
		var.uni = 1.0;

	// frequency
		var.omega = 2.0*M_PI/var.BCL;

	// Cell Geometry */
		var.CapHV = 153.4;  // Membrane Capacitance (pF)
		var.vcell = 38.0*0.000000000001; // Cell Volume:3.801e-5 (uL)
		var.vi = var.vcell*0.68;      // Myoplasm volume (uL) = 68% for Cell volume
		var.vup = var.vcell*0.0552;    // NSR volume (uL)
		var.vrel = var.vcell*0.0048;    // JSR volume (uL)
		printf("vi=%16.15e\n",var.vi);
		printf("vup=%16.15e\n",var.vup);
		printf("vrel=%16.15e\n",var.vrel);


	// Ion Valences
		var.zna = 1.0;  // Na valence
		var.zk = 1.0;   // K valence
		var.zca = 2.0;  // Ca valence

	// invariant constant
		var.FRT = F/(R*T);
		var.RTF = R*T/F;
		printf("FRT=%16.15e\n",var.FRT);
		printf("RTF=%16.15e\n",var.RTF);

	// Extracellular Concentrations
		var.nao = 140.0;    // (mM) 
		var.ko = 5.4;      // (mM)
		var.cao = 2.0;     // (mM)

	// Intracellular Concentrations
		//var.nai = 10.0;    // (mM) 
		var.ki = 140.0;      // (mM)
		//var.cai = 0.0001;     // [Ca] in myoplasm (mM)
		//var.carel = 1.0;     // [Ca] in SR Ca release site (junctional SR) (mM)
		//var.caup = 1.0;     // [Ca] in SR Ca uptake site (network SR) (mM)

		var.prnak = 0.01833;     // Na/K Permiability Ratio
		ina.pkna = 0.12;     // Na/K Permiability Ratio

	// Equilibrium Potentials (mV)
		var.Ek = (var.RTF/var.zk)*log(var.ko/var.ki);
		printf("Ek=%16.15e\n",var.Ek);

	// Fast sodium current
		ina.Gna = 7.8;	// (mS/uF).
		ina.mc1 = 0.32;	// (m gate).
		ina.mc2 = 47.13;	// (m gate).
		ina.mc3 = 0.08;	// (m gate).
		ina.mc4 = 11.0;	// (m gate).
		ina.mc5 = 10.0;	// (m gate).
		ina.hc1 = 7.74;	// (h gate).
		ina.hc2 = 0.12;	// (h gate).
		ina.hc3 = 0.25;	// (h gate).
		ina.hc4 = 2.24;	// (h gate).
		ina.hc5 = 0.07;	// (h gate).
		ina.hc6 = 92.4;	// (h gate).
		ina.hc7 = 0.5;	// (h gate).
		
		ina.u1=var.nao+ina.pkna*var.ko;
		ina.u2=ina.pkna*var.ki;
		printf("ina.u1=%16.15e\n",ina.u1);
		printf("ina.u2=%16.15e\n",ina.u2);
		
	// Transient outward current
		ito.pnato = 0.043;

		if(var.celltype==0){
			ito.dVgq= -12.0; //gating variables (q/r) % Endo (from Bernus 2002 model)
			ito.Gto = 0.13;	// Endo (from Bernus 2002 model).
		} else if(var.celltype==1){
			ito.dVgq= 0.0; //gating variables (q/r) % Epi (default for Kurata 2005 model)
			ito.Gto = 0.4;	// Epi (default for Kurata 2005 model).
		} else if(var.celltype==2){
			ito.dVgq= -4.0; //gating variables (q/r) % Mid (from Bernus 2002 model)
			ito.Gto = 0.35;	// Mid (from Bernus 2002 model).
		}

		ito.c1=0.5266;
		ito.c2=0.0166;
		ito.c3=42.2912;
		ito.c4=0.0943;
		ito.c5=0.5149;
		ito.c6=0.1344;
		ito.c7=5.0027;
		ito.c8=0.00005186;
		ito.c9=0.1348;
		
		ito.q1=0.0721;
		ito.q2=0.173;
		ito.q3=34.2531;
		ito.q4=0.00005612;
		ito.q5=0.1732;
		ito.q6=0.0767;
		ito.q7=0.00000000166;
		ito.q8=34.0235;
		ito.q9=0.0001215;
		ito.q10=0.1604;
		
		ito.k1=(ito.pnato*var.nao+var.ko);
		printf("ito.k1=%16.15e\n",ito.k1);

	// L-type calcium current
		ical.kmmca = 0.00035;
		ical.Eca = 52.8; // (mV)

		if(var.celltype == 0){ // Endo (based on O'Hara-Rudy 2011 model)
			ical.gca = 0.064*3.9*(1.0/1.2);
		} else if (var.celltype == 1){ // Epi (Default for Kurata 2005 model)
			ical.gca = 0.064*3.9;      	
		} else if (var.celltype == 2){ // Mid (based on O'Hara-Rudy 2011 model)
			ical.gca = 0.064*3.9*(2.5/1.2);
		}

		ical.dc1=7.64;	
		ical.dc2=6.32;	
		ical.dc3=0.25;	
		ical.dc4=35.0;	
		ical.dc5=13.0;	
		ical.dc6=50.0;	
		ical.dc7=20.0;	
		ical.dc8=1.4;	
		ical.dc9=5.0;	

		ical.kc1=24.6;
		ical.kc2=6.9;
		ical.kc3=0.1389;
		ical.kc4=0.0358;
		ical.kc5=23.9*0.75;
		ical.kc6=0.0519;
		ical.kc7=10.9;

	// Rapid delayed rectifier potassium current (Ikr)
		//ikr.rate = 0.55;
		//ikr.rate = 1.0;

		if(var.celltype == 0){
			ikr.Gkr = 0.012*(1.0/1.3);  //Endo (based on O'Hara-Rudy 2011 model)
		} else if(var.celltype == 1){
			ikr.Gkr = 0.012;  		// Epi (default for Kurata 2005 model)
		} else if(var.celltype == 2){
			ikr.Gkr = 0.012*(0.8/1.3);  // Mid (based on O'Hara-Rudy 2011 model)
		}

		ikr.c1=0.0003;
		ikr.c2=0.000073898;
		ikr.c3=3.4328;
		ikr.c4=5.1237;
		ikr.c5=14.0;
		ikr.c6=7.7;
		ikr.c7=5.0;

		ikr.k1=15.0;
		ikr.k2=22.4;

	// Slow delayed rectifier potassium current (Iks)

		//iks.rate = 0.5;

		if(var.celltype == 0){
			iks.Gks = 0.024*1.5*(1.0/1.4);	// Endo (based on O'Hara-Rudy 2011 model)
		} else if(var.celltype == 1){
			iks.Gks = 0.024*1.5;			// Epi (default for Kurata 2005 model)
		} else if(var.celltype == 2){
			//iks.Gks = 0.024*1.5*(1.0/1.4);		// Mid (based on O'Hara-Rudy 2011 model)
			iks.Gks = 0.024*1.5*(1.0/1.4);		// Mid (based on O'Hara-Rudy 2011 model)
		}
		
		iks.c1=129.0;
		iks.c2=555.0;
		iks.c3=9.4;
		iks.c4=11.8;
		iks.c5=22.0;
		iks.c6=11.3;

		iks.k1=(var.prnak*var.nao+var.ko);

		//iks.Ek = var.RTF*log((var.prnak*var.nao+var.ko)/(var.prnak*var.nai+var.ki));
	
	// Inward rectifier K current: Ik1
		if(var.celltype == 0){
			ik1.Gk1 = 3.9*(1.0/1.2);		// Endo (based on O'Hara-Rudy 2011 model)
		} else if(var.celltype == 1){
			ik1.Gk1 = 3.9;					// Epi (default for Kurata 2005 model)
		} else if(var.celltype == 2){
			ik1.Gk1 = 3.9*(1.3/1.2);		// Mid (based on O'Hara-Rudy 2011 model)
		}

		ik1.c1=0.06;
		ik1.c2=200.0;
		ik1.c3=0.0002;
		ik1.c4=100.0;
		ik1.c5=0.1;
		ik1.c6=0.5;
		ik1.c7=10.0;
		ik1.c8=3.0;

	// Sodium-Calcium Exchanger V-S
		ncx.kmnaex = 87.5;
		ncx.kmcaex = 1.38;
		ncx.rncx = 0.35;
		ncx.ksat = 0.1;

		if(var.celltype == 0){
			ncx.kncx = 1000.0*(1.0/1.1);	// Endo (based on O'Hara-Rudy 2011 model);
		} else {
			ncx.kncx = 1000.0;				// Epi (default for Kurata 2005 model) or Mid;
		}

		ncx.c1 = ncx.kncx/(pow(ncx.kmnaex,3)+pow(var.nao,3))/(ncx.kmcaex+var.cao);
		ncx.c2 = var.nao*var.nao*var.nao;
		ncx.c3 = ncx.rncx-1.0;
		//ncx.c1 = (pow(ncx.kmnaex,3)+pow(var.nao,3))/(ncx.kmcaex+var.cao);
		printf("ncx.c1=%16.15lf\n",ncx.c1);
		printf("ncx.c2=%16.15lf\n",ncx.c2);
		printf("ncx.c3=%16.15lf\n",ncx.c3);

	// Sodium-Potassium Pump
		inak.kmnap = 10.0;
		inak.kmkp = 1.5;
		inak.nna = 1.5;

		if(var.celltype == 0){
			inak.G = 1.3*0.68*(1.0/0.9);	// Endo (based on O'Hara-Rudy 2011 model)
		} else if(var.celltype == 1){
			inak.G = 1.3*0.68;				// Epi (default for Kurata 2005 model)
		} else if(var.celltype == 2){
			inak.G = 1.3*0.68;				// Mid (based on O'Hara-Rudy 2011 model)
		}

		inak.c1=(var.ko/(var.ko+inak.kmkp));
		inak.c2=0.1245;
		inak.c3=0.0365*(exp(var.nao/67.3)-1.0)/7.0;
		inak.c4=10.0;
		inak.c5=0.1;
		printf("inak.c1=%16.15e\n",inak.c1);
		printf("inak.c3=%16.15e\n",inak.c3);

	// Sarcolemmal Ca Pump
		ipca.G = 0.275*0.4;		// Max. Ca current through sarcolemmal Ca pump (mS/uF)
		ipca.km = 0.0005;		// Half-saturation concentration of sarcolemmal Ca pump (mM)

	// K Background Current 
		if(var.celltype != 1){
			//ikb.G = 0.003;		// Max. conductance of K background (mS/uF)
			ikb.G = 0.6*0.003;		// Max. conductance of K background (mS/uF)
		} else {
			ikb.G = 0.6*0.003;		// Max. conductance of K background (mS/uF)
		}

	// Ca Background Current 
		icab.pcab = 0.00085*0.6;	// (cm/s)

	// Na Background Current 
		inab.pnab = 0.001;

	// SR calcium release flux, via RyR (Jrel)
		jrel.nrel = 3.0;
		if(var.celltype!=2){
			jrel.prel = 50.0;	// Epi (default for Kurata 2005 model) or Endo
		} else {
			jrel.prel = 50.0*1.7;	// Mid (based on O'Hara-Rudy 2011 model)
		}
		jrel.taudr = 1.0*4.0;
		jrel.taudf = 4.0*4.0;

	// calcium uptake via SERCA pump (Jup)
		jup.kup = 0.00025;
		if(var.celltype != 1){
			jup.pup = 0.000425*5.2*(1.0/1.3);	// Mid or Endo (based on O'Hara-Rudy 2011 model)
		} else {
			jup.pup = 0.000425*5.2;				// Epi (default for Kurata 2005 model)
		}

	// Translocation of Ca Ions from NSR to JSR
		jtr.tau = 180.0;      // Time constant of Ca transfer from NSR to JSR (ms)

	// Ca leakage from SR to Cytoplasm
		jleak.pleak = 0.00026;

	//Troponin Ca Buffering (in Myoplasm)
		var.concTc = 0.07;
		var.rftn = 10.0;
		var.kktc = 40.0*var.rftn;
		var.kbtc = 0.02*var.rftn;
		
	//Calmodulin Ca Buffering (in Myoplasm) --- Rapid Buffering Approximation
		if(var.celltype != 1){
			var.conccm = 0.05*(1.0/1.3);  //% Mid or Endo (based on O'Hara-Rudy 2011 model)
		} else {
			var.conccm = 0.05;   //% Epi (default for Kurata 2005 model)
		}
		var.kdcm = 0.00238;	// % Kd for Ca-binding to Calmoduline 

	//Calsequestrin Ca Buffering (in SR) --- Rapid Buffering Approximation	
		var.conccq = 10.0;     // Max. [Ca] buffered in CSQN (mM)
		var.kdcq = 0.8;     // % Kd for Ca-binding to Calsequestrin

	// Cai
		cai.c1=2.0;
		cai.c2=5.0;
		cai.c3=0.9;

	// Nai
		nai.c1=3.0;



}

