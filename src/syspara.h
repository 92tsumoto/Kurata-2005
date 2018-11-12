//#ifndef __SYSPARA_H_INCLUDE 
//#define __SYSPARA_H_INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "mkl.h"
#include "./include/xhplot.h"

#define NN 16
#define BUF 100
#define NUM 60

//#define R 8314.472		// J/kmol/K
//#define F 96485.33771638995	// C/mol
//#define T 310.0		// K
#define R 8314400000000000		// J/kmol/K
#define F 96485000000000000	// C/mol
#define T 310.15		// K

#define VNMAX 400*5+1
#define dvm 5

struct varstruct {

    int datas;
    int line_wid[NUM];
	
	int n;

	// An invariant constant
	double FRT,RTF;

	// parameter variation
	double r,dr,uni;

	// Cell tupe
	int celltype;

	// Cell Geometry
	double vcell;
	double vi,vup,vrel;
	double CapHV;

	// Ion Valences 
	double zna,zk,zca;

	// Reversal potential
	double Ena,Ek,Eks,Eca;
	double prnak;
			
	// Total Ion currents 
	double itotal;

	// Net Ion Fluxes
	double jcanet,jnanet,jknet;

	// Troponin Ca Buffering (in Myoplasm)	
	double concTc,rftn,kktc,kbtc;

	// Calmodulin Ca Buffering (in Myoplasm) --- Rapid Buffering Approximation	
	double conccm,kdcm,bcm;

	// Calsequestrin Ca Buffering (in SR) --- Rapid Buffering Approximation
	double conccq,kdcq,bcq;

	// Extracellular ion concentrations
	double nao,ko,cao;

	// Intracellular ion concentrations
	double ki;

	// net flux
	double jCanet,jCal,jNaca,jIbca,jIpca;
	double jNanet;

	// Base Currnt Stimulus
    double Istim,Istim_base;
	double omega,ndis;

	// test variable
	double dt;
	// Sttimulus parameters
	double BCL;  // Base cycle length = stimulus period
	int beat; // Number of stimulus

    MKL_INT m;
    MKL_INT l;

    double x0[NUM][NN];
    double tsign[NUM];
    double tend[NUM];

    int pflag;
    int write, graph;
    int write0;
    int half;
	int pswitch;

} var;

// Fast and Late sodium currnets
struct inastruct {

	double Gna,fast,pkna,Enaf;
	double am,bm,minf,taum,hinf,tauh;
	double *Tam,*Tbm,*Thinf,*Ttauh;
	double u1,u2,k3;
	double mc1,mc2,mc3,mc4,mc5;
	double hc1,hc2,hc3,hc4,hc5,hc6,hc7;

} ina;

// Transient Outward Current (Ito)
struct itostruct {

	double ik,Gto,Ek;
	double rinf,taur,qinf,tauq;
	double ar,br,aq1,bq1,aq2,bq2;
	double *Tar,*Tbr,*Taq1,*Tbq1,*Taq2,*Tbq2;
	double pnato,dVgq;
	double c1,c2,c3,c4,c5,c6,c7,c8,c9;
	double q1,q2,q3,q4,q5,q6,q7,q8,q9,q10;
	double k1;
	

} ito;

// L-type Calcium channel current (IcaL)
struct icalstruct {

	double dinf,taud,finf,tauf;
	double *Tdinf,*Ttaud,*Tfinf,*Ttauf;
	double kmmca,gfCa_inf;
	double gca,Eca;
	double ica,icana,icak;
	double tmp;
	double dc1,dc2,dc3,dc4,dc5,dc6,dc7,dc8,dc9;
	double kc1,kc2,kc3,kc4,kc5,kc6,kc7;

} ical;

// Rapid activating potassium current (Ikr)
struct ikrstruct {

	double ik,Gkr,rate;
	double pinf,ap,bp,taup,piinf;
	double *Tpinf,*Tap,*Tbp,*Tpiinf;
	double c1,c2,c3,c4,c5,c6,c7;
	double k1,k2;

} ikr;

// Slowlactivating potassium current (Iks)
struct iksstruct {

	double ik,Gks,Ek,rate;
	double ninf,taun;
	double *Tninf,*Ttaun;
	double c1,c2,c3,c4,c5,c6;
	double k1;
		
} iks;

// Inward rectifier potassium current (Ik1)
struct ik1struct {

	double ik,Gk1;
	double k1inf,ak1,bk1;
	double *Tak1,*Tbk1;
	double c1,c2,c3,c4,c5,c6,c7,c8;
	double k1;

} ik1;

struct ncxstruct {

	double kncx;
	double kmnaex,kmcaex,rncx,ksat;
	double jncx;
	double *Texp0,*Texp1;
	double exp0,exp1,c1,c2,c3;

} ncx;

// Sodium-Potassium Pump
struct inakstruct {

	double kmnap,kmkp,nna;
	double G,inak;
	double rhonak,*Trhonak;
	double *Texp0,exp0,*Texp1,exp1;
	double c1,c2,c3,c4,c5;

} inak;

// Sarcolemmal Ca Pump
struct ipcastruct {

	double G,km,ca;

} ipca;

// Na Background Current
struct inabstruct {

	double pnab,na;


} inab;

// K Background Current
struct ikbstruct {

	double G,k;
	double xkb,*Txkb;

} ikb;

// Ca Background Current
struct icabstruct {

	double pcab,gacai,gacao,ca;
	double exp,*Texp;

} icab;

// SR calcium release flux, via RyR (Jrel)
struct jrelstruct {

	double drss,taudr;
	double dfss,taudf;
	double prel,nrel;
	double ca;

} jrel;

// Calcium uptake via SERCA pump
struct jupstruct {

	double pup,kup;
	double ca;

} jup;

// diffusion flux
struct jleakstruct {

	double pleak,ca;

} jleak;

// Translocation of Ca Ions from NSR to JSR
struct jtrstruct {

	double tau,ca;

} jtr;

struct caistruct {

	double c1,c2,c3;

} cai;

struct naistruct {

	double c1;

} nai;

// Newton method
struct new {
	double *A,*I,*DF,*DF0,*DF1;
	double *h,*xn0,*xn1,*xn2,*Fxn;
} new;

void val_consts(FILE *);
void make_ExPTable();

//void eular(int n,double h,double x[],double t);
void runge(int n,double h,double x[],double t);
void function(double x[],double f[],double t);
void input_para(FILE *);
void initial_mem();
void closed_mem();

void data_out(FILE *,double t,double x[]);
void current(FILE *,FILE *,FILE *,FILE *,FILE *,FILE *,double t,double x[]);
void comp_reversal_potential(double x[]);
void comp_ina(double x[]);
void comp_ito(double x[]);
void comp_ical(FILE *, double t, double x[]);
void comp_ikr(FILE *, double t, double x[]);
void comp_iks(FILE *, double t, double x[]);
void comp_ik1(double x[]);
void comp_inaca(FILE *, double t,double x[]);
void comp_inak(FILE *, double t,double x[]);
void comp_ipca(double x[]);
void comp_ikb(double x[]);
void comp_icab(double x[]);
void comp_inab(double x[]);
void comp_cicr(FILE *, double t, double x[]);
void comp_jup(double x[]);
void comp_jleak(double x[]);
void comp_jtr (double x[]);
void comp_concentration (double x[]);

void jacobi(double x[]);

main(int argc,char **argv);
