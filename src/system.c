#include "syspara.h"

inline void function(double x[],double f[],double t)
{

double BCM,DFTC,Jleak,Jup,Jrel,JCanet,jcal,jnaca,JNanet;

BCM = (var.kdcm + x[12])*(var.kdcm + x[12])/(var.conccm*var.kdcm + (var.kdcm + x[12])*(var.kdcm + x[12]));
Jleak=jleak.pleak*(x[14] - x[12])*var.vup/var.vi;
Jup=(jup.pup*x[12]*x[12])/(jup.kup*jup.kup + x[12]*x[12])*var.vup/var.vi;

JCanet=(var.CapHV/(F*var.zca)/var.vi)*(icab.pcab*(x[0] - (var.RTF*log(var.cao/x[12]))/var.zca))
	+ (var.CapHV/(F*var.zca)/var.vi)*(ipca.G*x[12])/(ipca.km + x[12])
	+ (var.CapHV/(F*var.zca)/var.vi)*(2.0*ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(1.0 + ncx.ksat*exp(var.FRT*ncx.c3*x[0]))
	+ (var.CapHV/(F*var.zca)/var.vi)*(ical.gca*ical.kmmca*x[3]*x[4]*(x[0]-ical.Eca))/(ical.kmmca + x[12]);

jcal= (var.CapHV/(F*var.zca)/var.vi)*(ical.gca*ical.kmmca*x[3]*x[4]*(x[0]-ical.Eca))/(ical.kmmca + x[12]);
jnaca= (var.CapHV/(F*var.zca)/var.vi)*(2.0*ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(1.0 + ncx.ksat*exp(var.FRT*ncx.c3*x[0]));
Jrel=(jrel.prel*var.vrel*x[9]*x[9]*x[9]*x[10]*x[10]*x[10]*(x[13] - x[12]))/(1.0 + exp((cai.c2 +
	icab.pcab*(x[0] - (var.RTF*log(var.cao/x[12]))/var.zca) +
	(ipca.G*x[12])/(ipca.km + x[12])+
	(2.0*ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(1.0 + ncx.ksat*exp(var.FRT*ncx.c3*x[0])) +
	(ical.gca*ical.kmmca*x[3]*x[4]*(x[0]-ical.Eca))/(ical.kmmca + x[12])
	)/cai.c3))/var.vi;

DFTC= var.kktc*x[12]*(1.0 - x[11])-var.kbtc*x[11];
var.jCanet=-BCM*JCanet;
var.jCal=-BCM*jcal;
var.jNaca=-BCM*jnaca;

JNanet=(var.CapHV*(
inab.pnab*(x[0] - var.RTF*log(var.nao/x[15]))
+ ina.Gna*x[1]*x[1]*x[1]*x[2]*x[2]*(x[0] - var.RTF*log(ina.u1/(ina.u2 + x[15])))
+ (3.0*ncx.c1*(var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0]) - ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0])))/(1.0 + ncx.ksat*exp(var.FRT*ncx.c3*x[0])) 
+ (3.0*inak.G*inak.c1)/((1.0 + (10.0/x[15])*sqrt(10.0/x[15]))*(1.0 + inak.c3*exp(-var.FRT*x[0]) + 0.1245*exp(-var.FRT*0.1*x[0])))
))/(F*var.vi);
var.jNanet=JNanet;


var.itotal=-(icab.pcab*(x[0] - (var.RTF*log(var.cao/x[12]))/var.zca) + inab.pnab*(x[0] - var.RTF*log(var.nao/x[15])) + iks.rate*iks.Gks*x[8]*x[8]*(x[0] - var.RTF*log(iks.k1/(var.ki + var.prnak*x[15]))) - (ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(var.uni + ncx.ksat*exp(var.FRT*ncx.c3*x[0])) + (ipca.G*x[12])/(ipca.km + x[12]) + ina.Gna*x[1]*x[1]*x[1]*x[2]*x[2]*(x[0] - var.RTF*log(ina.u1/(ina.u2 + x[15]))) + ito.Gto*x[5]*x[6]*(x[0] - var.RTF*log(ito.k1/(var.ki + ito.pnato*x[15]))) + (inak.G*inak.c1)/((var.uni + (inak.c4*sqrt(inak.c4/x[15]))/x[15])*(var.uni + inak.c3*exp(-var.FRT*x[0]) + inak.c2*exp(-var.FRT*inak.c5*x[0]))) - (ik1.Gk1*ik1.c5*(var.Ek - x[0])*(var.uni + exp(ik1.c6*(var.Ek - x[0]))))/((var.uni + exp(-ik1.c1*(var.Ek + ik1.c2 - x[0])))*(exp(-ik1.c5*(var.Ek + ik1.c7 - x[0])) + ik1.c8*exp(ik1.c3*(ik1.c4 - var.Ek + x[0]))) + ik1.c5*(var.uni + exp(ik1.c6*(var.Ek - x[0])))) - (ikr.Gkr*ikr.rate*x[7]*(var.Ek - x[0]))/(var.uni + exp((ikr.k1 + x[0])/ikr.k2)) - (ical.gca*ical.kmmca*x[3]*x[4]*(ical.Eca - x[0]))/(ical.kmmca + x[12]));

f[0]=-(icab.pcab*(x[0] - (var.RTF*log(var.cao/x[12]))/var.zca) - var.Istim + inab.pnab*(x[0] - var.RTF*log(var.nao/x[15])) + iks.rate*iks.Gks*x[8]*x[8]*(x[0] - var.RTF*log(iks.k1/(var.ki + var.prnak*x[15]))) - (ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(var.uni + ncx.ksat*exp(var.FRT*ncx.c3*x[0])) + (ipca.G*x[12])/(ipca.km + x[12]) + ina.Gna*x[1]*x[1]*x[1]*x[2]*x[2]*(x[0] - var.RTF*log(ina.u1/(ina.u2 + x[15]))) + ito.Gto*x[5]*x[6]*(x[0] - var.RTF*log(ito.k1/(var.ki + ito.pnato*x[15]))) + (inak.G*inak.c1)/((var.uni + (inak.c4*sqrt(inak.c4/x[15]))/x[15])*(var.uni + inak.c3*exp(-var.FRT*x[0]) + inak.c2*exp(-var.FRT*inak.c5*x[0]))) - (ik1.Gk1*ik1.c5*(var.Ek - x[0])*(var.uni + exp(ik1.c6*(var.Ek - x[0]))))/((var.uni + exp(-ik1.c1*(var.Ek + ik1.c2 - x[0])))*(exp(-ik1.c5*(var.Ek + ik1.c7 - x[0])) + ik1.c8*exp(ik1.c3*(ik1.c4 - var.Ek + x[0]))) + ik1.c5*(var.uni + exp(ik1.c6*(var.Ek - x[0])))) - (ikr.Gkr*ikr.rate*x[7]*(var.Ek - x[0]))/(var.uni + exp((ikr.k1 + x[0])/ikr.k2)) - (ical.gca*ical.kmmca*x[3]*x[4]*(ical.Eca - x[0]))/(ical.kmmca + x[12]))/var.omega;
f[1]=-(ina.mc3*x[1]*exp(-x[0]/ina.mc4) - (ina.mc1*(ina.mc2 + x[0])*(var.uni - x[1]))/(var.uni - exp(-(ina.mc2 + x[0])/ina.mc5)))/var.omega;
f[2]=-(x[2] - ina.hc7*(var.uni - tanh(ina.hc1 + ina.hc2*x[0])))/(var.omega*(ina.hc3 + (ina.hc4*(var.uni - tanh(ina.hc1 + ina.hc2*x[0])))/(var.uni - tanh(ina.hc5*(ina.hc6 + x[0])))));
f[3]=-(x[3] - var.uni/(var.uni + exp(-(ical.dc1 + x[0])/ical.dc2)))/(var.omega*(var.uni/(var.uni + exp((ical.dc6 - x[0])/ical.dc7)) + (ical.dc8*(ical.dc3 + ical.dc8/(var.uni + exp(-(ical.dc4 + x[0])/ical.dc5))))/(var.uni + exp((ical.dc9 + x[0])/ical.dc9))));
f[4]=-((ical.kc6 + ical.kc3*exp(-ical.kc4*ical.kc4*(ical.kc7 - x[0])*(ical.kc7 - x[0])))*(x[4] - var.uni/(var.uni + exp((ical.kc1 + x[0])/ical.kc2))))/(ical.kc5*var.omega);
f[5]=-((x[5]*(ito.c8*x[0] + ito.c5*exp(ito.c6*(ito.c7 - x[0]))))/(var.uni + exp(ito.c9*(ito.c8 - x[0]))) - (ito.c1*exp(ito.c2*(ito.c3 - x[0]))*(var.uni - x[5]))/(var.uni + exp(ito.c4*(ito.c3 - x[0]))))/var.omega;
f[6]=-((x[6] - (ito.q1*exp(-ito.q2*(ito.q3 - ito.dVgq + x[0])) - ito.q4*(ito.dVgq - x[0]))/((var.uni + exp(-ito.q5*(ito.q3 - ito.dVgq + x[0])))*((ito.q1*exp(-ito.q2*(ito.q3 - ito.dVgq + x[0])) - ito.q4*(ito.dVgq - x[0]))/(var.uni + exp(-ito.q5*(ito.q3 - ito.dVgq + x[0]))) + (ito.q6*exp(-ito.q7*(ito.q8 - ito.dVgq + x[0])) - ito.q9*(ito.dVgq - x[0]))/(var.uni + exp(-ito.q10*(ito.q8 - ito.dVgq + x[0]))))))*((ito.q4*x[0] + ito.q1*exp(-ito.q2*(ito.q3 + x[0])))/(var.uni + exp(-ito.q5*(ito.q3 + x[0]))) + (ito.q9*x[0] + ito.q6*exp(-ito.q7*(ito.q8 + x[0])))/(var.uni + exp(-ito.q10*(ito.q8 + x[0])))))/var.omega;
f[7]=-(((ikr.c2*(ikr.c3 - x[0]))/(var.uni - exp(-(ikr.c3 - x[0])/ikr.c4)) + (ikr.c1*(ikr.c5 + x[0]))/(var.uni - exp(-(ikr.c5 + x[0])/ikr.c7)))*(x[7] - var.uni/(var.uni + exp(-(ikr.c5 + x[0])/ikr.c6))))/var.omega;
f[8]=-(x[8] - var.uni/sqrt(var.uni + exp((iks.c3 - x[0])/iks.c4)))/(var.omega*(iks.c1 + iks.c2/(var.uni + exp(-(iks.c5 + x[0])/iks.c6))));
f[9]=-(x[9] - var.uni/(var.uni + exp(-(ical.dc1 + x[0])/ical.dc2)))/(jrel.taudr*var.omega);
f[10]=-(x[10] - var.uni/(var.uni + exp((ical.kc1 + x[0])/ical.kc2)))/(jrel.taudf*var.omega);
f[11]=-(var.kbtc*x[11] - var.kktc*x[12]*(var.uni - x[11]))/var.omega;
f[12]=-(((jleak.pleak*var.vup*(x[12] - x[14]) + (jup.pup*var.vup*x[12]*x[12])/(jup.kup*jup.kup + x[12]*x[12]) + (var.CapHV*(icab.pcab*(x[0] - (var.RTF*log(var.cao/x[12]))/var.zca) + (ipca.G*x[12])/(ipca.km + x[12]) + (cai.c1*ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(var.uni + ncx.ksat*exp(var.FRT*ncx.c3*x[0])) - (ical.gca*ical.kmmca*x[3]*x[4]*(ical.Eca - x[0]))/(ical.kmmca + x[12])))/(F*var.zca) + (jrel.prel*var.vrel*x[9]*x[9]*x[9]*x[10]*x[10]*x[10]*(x[12] - x[13]))/(var.uni + exp((cai.c2 + icab.pcab*(x[0] - (var.RTF*log(var.cao/x[12]))/var.zca) + (ipca.G*x[12])/(ipca.km + x[12]) + (cai.c1*ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(var.uni + ncx.ksat*exp(var.FRT*ncx.c3*x[0])) - (ical.gca*ical.kmmca*x[3]*x[4]*(ical.Eca - x[0]))/(ical.kmmca + x[12]))/cai.c3)))/var.vi - var.concTc*(var.kbtc*x[11] - var.kktc*x[12]*(var.uni - x[11])))*(var.kdcm + x[12])*(var.kdcm + x[12]))/(var.omega*(var.conccm*var.kdcm + (var.kdcm + x[12])*(var.kdcm + x[12])));
f[13]=-((var.kdcq + x[13])*(var.kdcq + x[13])*((x[13] - x[14])/jtr.tau - (jrel.prel*x[9]*x[9]*x[9]*x[10]*x[10]*x[10]*(x[12] - x[13]))/(var.uni + exp((cai.c2 + icab.pcab*(x[0] - (var.RTF*log(var.cao/x[12]))/var.zca) + (ipca.G*x[12])/(ipca.km + x[12]) + (cai.c1*ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(var.uni + ncx.ksat*exp(var.FRT*ncx.c3*x[0])) - (ical.gca*ical.kmmca*x[3]*x[4]*(ical.Eca - x[0]))/(ical.kmmca + x[12]))/cai.c3))))/(var.omega*(var.conccq*var.kdcq + (var.kdcq + x[13])*(var.kdcq + x[13])));
f[14]=(jleak.pleak*(x[12] - x[14]) + (jup.pup*x[12]*x[12])/(jup.kup*jup.kup + x[12]*x[12]) + (var.vrel*(x[13] - x[14]))/(jtr.tau*var.vup))/var.omega;
f[15]=-(var.CapHV*(inab.pnab*(x[0] - var.RTF*log(var.nao/x[15])) + ina.Gna*x[1]*x[1]*x[1]*x[2]*x[2]*(x[0] - var.RTF*log(ina.u1/(ina.u2 + x[15]))) - (nai.c1*ncx.c1*(ncx.c2*x[12]*exp(var.FRT*ncx.c3*x[0]) - var.cao*x[15]*x[15]*x[15]*exp(var.FRT*ncx.rncx*x[0])))/(var.uni + ncx.ksat*exp(var.FRT*ncx.c3*x[0])) + (inak.G*inak.c1*nai.c1)/((var.uni + (inak.c4*sqrt(inak.c4/x[15]))/x[15])*(var.uni + inak.c3*exp(-var.FRT*x[0]) + inak.c2*exp(-var.FRT*inak.c5*x[0])))))/(F*var.vi*var.zna*var.omega);

}
