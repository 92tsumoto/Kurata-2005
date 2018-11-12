/* produced by Tsumoto. K 2008.10.27 */

#include <string.h>
#include <stdlib.h>
#include "syspara.h"

FILE *fopen(), *fpin, *fp0, *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8, *fp9;
int mode = 1;
int P = 2;
int beats = 50;

typedef double Number;

main(argc,argv)
int argc;
char **argv;
{
	int i,w;
	int ii=0;
	double x[NN];
	double t = 0.0;
	double tt,ttt;
	double time=0.0;
	double ttime=0.0;
	double h;
	double v_old,dvdt,dvdt_new;
	double t_stok;
	char *tmpname;
	char cmd[BUFSIZ];
	double tend;

	tmpname = "temp";

	sprintf(cmd, "/usr/bin/cpp -P %s > %s", argv[1],tmpname);
	if(system(cmd) == -1){
		fprintf(stderr,"cannot open %s\n",argv[1]);
		exit(1);
	}
	if((fpin=fopen(tmpname,"r"))==NULL){
		fprintf(stderr,"cannot open %s\n",argv[1]);
		exit(1);
	}
	if ((fp1 = fopen("para.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp2 = fopen("data.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}
	if ((fp3 = fopen("nstate.out","w")) == NULL){
		printf("Can't open File\n");
		exit(1);
	}

// parameter inputs
	input_para(fpin);

	if (var.write){
		if ((fp0 = fopen(argv[2],"w"))==NULL){
			fprintf(stderr, "%s cannot open.\n",argv[2]);
			exit(-1);
		}
	}
	if (var.write0){
		if ((fp4 = fopen("ikr.out","w")) == NULL){
			printf("Can't open File\n");
			exit(1);
		}
		if ((fp5 = fopen("iks.out","w")) == NULL){
			printf("Can't open File\n");
			exit(1);
		}
		if ((fp6 = fopen("ical.out","w")) == NULL){
			printf("Can't open File\n");
			exit(1);
		}
		if ((fp7 = fopen("incx.out","w")) == NULL){
			printf("Can't open File\n");
			exit(1);
		}
		if ((fp8 = fopen("inak.out","w")) == NULL){
			printf("Can't open File\n");
			exit(1);
		}
		if ((fp9 = fopen("jrel.out","w")) == NULL){
			printf("Can't open File\n");
			exit(1);
		}
	}

	xhplot(WINDOW, 700.0, 700.0, WHITE);
	xhplot(DIRECT, 0.0, 0.0, WHITE);

	for (ii = 0; ii < var.datas; ii++){
		long j;
		time = 0.0;
		tend = var.tend[ii];
		for (i = 0; i < NN; i++){ 
			x[i] = var.x0[ii][i];
		}

		tt = var.ndis*(double)var.m;
		h = 2.0*M_PI / (double)var.m;
		h *= var.tsign[ii];

		xddp.line_wid = var.line_wid[ii];
		xhplot(LINEATT,0,0,WHITE);

		
		// parameter values input.
		val_consts(fp1);
		//var.pswitch=0;
		printf("exit consts\n");
	
		// initial values input.
		initial_mem();
		printf("exit memory initialization\n");

		printf("Istim=%lf\n",var.Istim_base);

		// Tablize exp functions.	
		printf("start tablization\n");
		make_ExpTable();
		printf("finished tablization\n");

		// Initialization time
		var.beat = 0;

		tt = var.ndis*(double)var.m;
		ttt = (1.0-var.ndis)*(double)var.m;
		while (1){
			eventloop(fp1,&mode,&P,x);
			time=var.beat*(var.BCL*var.omega);
			for (j = 0; j< (int)tt; j++){
				t = h*(double)j;
				v_old = x[0];
				var.Istim = var.Istim_base;
				runge(NN,h,x,t);
				dvdt = (x[0]-v_old)/(h/var.omega);
				if (var.pflag) orbit(&mode,x,dvdt);
				//if (var.beat >= (beats-20) && var.beat < beats){
				if (var.pswitch==1){
					//fprintf(fp2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
					//	time,time/var.omega,x[0],x[12],x[13],x[14],x[15],x[3],x[4],ical.kmmca/(ical.kmmca + x[12]),ical.gca*x[3]*x[4]*(ical.Eca - x[0])/(x[12]/ical.kmmca + 1.0),var.itotal);
						data_out(fp2,ttime,x);
					if(var.write0){
						current(fp4,fp5,fp6,fp7,fp8,fp9,ttime,x);
					}
				}
				time += h;
				ttime=time/var.omega;
			} // 1st-loop


			for (j = 0; j<(int)ttt; j++){
				t = h*(double)j;
				v_old = x[0];
				var.Istim = 0.0;
				runge(NN,h,x,t);
				dvdt = (x[0]-v_old)/(h/var.omega);
				if (var.pflag) orbit(&mode,x,dvdt);
				//if (var.beat >= (beats-20) && var.beat < beats){
				if (var.pswitch==1){
					//fprintf(fp2,"%lf %lf %lf %lf %lf %lf %lf\n",time,time/var.omega,x[0],x[12],x[13],x[14],x[15]);
					//fprintf(fp2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
					//	time,time/var.omega,x[0],x[12],x[13],x[14],x[15],x[3],x[4],ical.kmmca/(ical.kmmca + x[12]),ical.gca*x[3]*x[4]*(ical.Eca - x[0])/(x[12]/ical.kmmca + 1.0),var.itotal);
						data_out(fp2,ttime,x);
					if(var.write0){
						current(fp4,fp5,fp6,fp7,fp8,fp9,ttime,x);
					}
				}
				time += h;
				ttime=time/var.omega;
			} // 2nd-loop

			fprintf(fp3,"#beats=%d\n",var.beat);
			for(w=0;w<NN;w++){
				fprintf(fp3,"%16.15e\n",x[w]);
			}
			fflush(fp3);

			printf("%d %lf ",var.beat,time/var.omega);
			for(w=0;w<NN;w++){
				if(w!=NN-1){
					printf("%10.9lf ",x[w]);
				} else {
					printf("%10.9lf\n",x[w]);
				}
			} 
			draw_p(&mode,P,x,dvdt);
			mouse(&mode,x,dvdt);
			if (fabs(time) > tend &&  tend != 0.0) break;
			var.beat++;

		} // end for while loop

	} // end for ii-loop

	// closed file and open memories
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	if(var.write0){
		fclose(fp4);fclose(fp5);fclose(fp6);fclose(fp7);fclose(fp8);fclose(fp9);
	}
	closed_mem();
}

