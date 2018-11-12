#include <string.h>
#include "syspara.h"

void eventloop(FILE *fp1,int *mode, int *P,double m[])
{
	int i;
		
	xhplot(KEYIN,0,0,WHITE);
	if (xddpret.key != -1){
		switch (xddpret.key){
			case 'e':
				if(*mode==1){
					xhplot(CLS, m[0],m[1],BLACK);
					xhplot(FRAME, m[0],m[1],WHITE);
				}
				if(*mode==2){
					xhplot(CLS, m[0],m[2],BLACK);
					xhplot(FRAME, m[0],m[2],WHITE);
				}
				if(!*mode){
					xhplot(CLS, m[0],m[1],BLACK);
					xhplot(FRAME, m[0],m[1],WHITE);
				}
				break;
			case 'f':
				if(var.pflag == 1){
					var.pflag = 1 - var.pflag;
				}else if(var.pflag == 0){
					var.pflag = 1;
				}
				break;
			case 'g':
				switch(*P){
				case 2 : 
					*P = 8;
					fprintf(stderr,"fixed point is doted\n");
					printf("P=%d\n",*P);
					break;
				case 8 : 
					*P = 2;
					fprintf(stderr,"fixed point is not doted\n");
					printf("P=%d\n",*P);
					break;
				}
				break;
			case 'q':
				printf("quit\n");
				exit(0);
				break;
			case 's':
				printf("\nStatus\n");
				//printf("k2 = %lf --> v\n",var.k2);
				printf("%lf %lf %f %f %f\n", m[0],m[1],m[2],m[3],m[4]);
				printf("%lf %lf %f %f %f\n", m[5],m[6],m[7],m[8],m[9]);
				printf("%lf %lf %f %f %f %f\n", m[10],m[11],m[12],m[13],m[14],m[15]);
				fflush(stdout);
				break;
			case 'a':
				ikr.rate -= var.dr;
				printf("r = %lf\n",ikr.rate);
				fflush(stdout);
				break;
			case 'A':
				ikr.rate += var.dr;
				printf("r = %lf\n",ikr.rate);
				fflush(stdout);
				break;
			case 'p':
				if(var.pswitch==0){
					var.pswitch++;
					printf("data out start\n");
				} else {
					var.pswitch=0;
					printf("data out stop\n");
				}
				break;
			case ' ':
				//mode = 1 - mode;
				printf("\n");
				*mode+=1;
				if(*mode==1)
					printf("### Now plane is Vm, m ###\n");
				if(*mode==2)
					printf("### Now plane is Vm, h ###\n");
				if(*mode>2){
					*mode=1; 
					printf("### Now plane is Vm, m ###\n");
					printf("\n");
					printf(" a:   Istim\n");
					printf(" e:   clear\n");
					printf(" f:   change\n");
					printf(" g:   small <-> big\n");
					printf(" s:   state\n");
					printf("space: Vm,m <-> Vm,h \n");
					printf("\n");
					break;
				}
		}
	}
}
