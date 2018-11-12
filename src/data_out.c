#include "syspara.h"

void data_out(FILE *fp2, double t, double u[])
{

	fprintf(fp2,"%10.9e %lf %lf %10.9e %lf %lf %lf %lf %10.9e %10.9e %10.9e %10.9e\n",
		t,t/var.omega,u[0],u[12],u[13],u[14],u[15],var.itotal,var.jCanet,var.jCal,var.jNaca,var.jNanet);

}

void current(FILE *fp4, FILE *fp5, FILE *fp6, FILE *fp7, FILE *fp8, FILE *fp9, double t, double u[])
{

	comp_ikr(fp4,t,u);
	comp_iks(fp5,t,u);
	comp_ical(fp6,t,u);
	comp_inaca(fp7,t,u);
	comp_inak(fp8,t,u);
	comp_cicr(fp9,t,u);
	//printf("t=%lf\n",t);

}

void comp_ina(double p[])
{
	//ina.fast = ina.Gna*p[1]*p[1]*p[1]*p[2]*p[2]*(p[0] - var.RTF*log(ina.u1/(ina.u2 + p[15])));

}

// Ito Transient Outward Current
void comp_ito (double p[])
{

	//ito.ik = ito.Gto*p[5]*p[6]*(p[0] - var.RTF*log(ito.k1/(var.ki + ito.pnato*p[15])));

}


// L-type calcium current
void comp_ical(FILE *fp6, double time, double p[])
{
	double cdi;
	cdi = ical.kmmca/(ical.kmmca + p[12]);
	ical.ica = - ical.gca*p[3]*p[4]*cdi*(ical.Eca - p[0]);
	fprintf(fp6,"%10.9e %lf %e %e %e\n",time,ical.ica,p[3],p[4],cdi);

}

// Rapidly Activating Potassium Current 
void comp_ikr (FILE *fp4, double time, double p[])
{
	ikr.ik = -(ikr.Gkr*ikr.rate*p[7]*(var.Ek - p[0]))/(var.uni + exp((ikr.k1 + p[0])/ikr.k2));
	fprintf(fp4,"%10.9e %lf\n",time,ikr.ik);

}

// Slowly Activating Potassium Current 
void comp_iks (FILE *fp5, double time, double p[])
{
	
	iks.ik = iks.rate*iks.Gks*p[8]*p[8]*(p[0] - var.RTF*log(iks.k1/(var.ki + var.prnak*p[15])));
	fprintf(fp5,"%10.9e %lf\n",time,iks.ik);

}

// Inward rectifier potassium current (Ik1)
void comp_ik1 (double p[])
{

	ik1.ik = -(ik1.Gk1*ik1.c5*(var.Ek - p[0])*(var.uni + exp(ik1.c6*(var.Ek - p[0]))))/((var.uni + exp(-ik1.c1*(var.Ek + ik1.c2 - p[0])))*(exp(-ik1.c5*(var.Ek + ik1.c7 - p[0])) + ik1.c8*exp(ik1.c3*(ik1.c4 - var.Ek + p[0]))) + ik1.c5*(var.uni + exp(ik1.c6*(var.Ek - p[0]))));

}

// Sodium-Calcium Exchanger V-S

void comp_inaca (FILE *fp7, double time, double p[])
{
	ncx.jncx = -(ncx.c1*(ncx.c2*p[12]*exp(var.FRT*ncx.c3*p[0]) - var.cao*p[15]*p[15]*p[15]*exp(var.FRT*ncx.rncx*p[0])))/(var.uni + ncx.ksat*exp(var.FRT*ncx.c3*p[0]));
	fprintf(fp7,"%10.9e %lf\n",time,ncx.jncx);

}

// Sodium-Potassium Pump

void comp_inak (FILE *fp8, double time, double p[])
{
	inak.inak= (inak.G*inak.c1)/((var.uni + (inak.c4*sqrt(inak.c4/p[15]))/p[15])*(var.uni + inak.c3*exp(-var.FRT*p[0]) + inak.c2*exp(-var.FRT*inak.c5*p[0])));
	fprintf(fp8,"%10.9e %lf\n",time,inak.inak);

}

// Sarcolemmal Ca Pump 

void comp_ipca (double p[])
{

	ipca.ca = (ipca.G*p[12])/(ipca.km + p[12]);

}

// Ca Background Current 

void comp_icab (double p[])
{
	
	icab.ca = icab.pcab*(p[0] - (var.RTF*log(var.cao/p[12]))/var.zca);

}

// Na Background Current 

void comp_inab (double p[])
{

	inab.na = inab.pnab*(p[0] - var.RTF*log(var.nao/p[15]));

}

void comp_cicr (FILE *fp9, double time, double p[])
{
	double cdi;

	cdi = ical.kmmca/(ical.kmmca + p[12]);
	ical.ica=ical.gca*p[3]*p[4]*cdi*(ical.Eca - p[0]);
	icab.ca = icab.pcab*(p[0] - (var.RTF*log(var.cao/p[12]))/var.zca);
	ncx.jncx = -(ncx.c1*(ncx.c2*p[12]*exp(var.FRT*ncx.c3*p[0]) - var.cao*p[15]*p[15]*p[15]*exp(var.FRT*ncx.rncx*p[0])))/(var.uni + ncx.ksat*exp(var.FRT*ncx.c3*p[0]));
	ipca.ca = (ipca.G*p[12])/(ipca.km + p[12]);

	jrel.ca = jrel.prel/(1.0+exp((ical.ica + icab.ca - 2.0*ncx.jncx + ipca.ca + 5.0)/0.9))*p[9]*p[9]*p[9]*p[10]*p[10]*p[10]*(p[13]-p[12]);
	fprintf(fp9,"%10.9e %lf\n",time,jrel.ca);

}

void comp_jup (double p[])
{

}

void comp_jleak (double p[])
{

}
void comp_jtr (double p[])
{

}

void comp_concentration (double p[])
{

}


// Reversal potentials */

void comp_reversal_potential(double p[])
{

}

