#include <stdio.h>
#define nomboflines 20
	int Xnomboflines=0;
	int Ynomboflines=0;
	int  fld[nomboflines+1][nomboflines+1]; 
	int TopL[nomboflines][(nomboflines/2)+(nomboflines%2)];
	int	LeftL[nomboflines][(nomboflines/2)+(nomboflines%2)];	
void startpos(int Line)
{
	int nomb=0;
	int k1=0,k2=0,x=0;	
	for (k1=0;k1<Xnomboflines;k1++)
		fld[Line][k1]=0;
	while ((LeftL[Line][nomb]!=0) && (nomb<((Xnomboflines/2)+(Xnomboflines%2))))
		nomb++;	
	for (k1=0;k1<nomb;k1++){
		for (k2=1;k2<=LeftL[Line][k1];k2++){
			fld[Line][x]=1;
			x++;
		}			
	x++;
	}		
}
int chngelm(int Line,int elem)
{
	int k1;
	int x=-1,take=1,take1=0;
	for (k1=0;k1<elem-1;k1++)
		take=take+LeftL[Line][k1];	
	for (k1=0;k1<Xnomboflines;k1++){
		x++;
		take1=take1+fld[Line][k1];
		if (take1==take)
			k1=Xnomboflines;	
	}
	
	if ((fld[Line][x+LeftL[Line][elem-1]+1]!=0) || (x+LeftL[Line][elem-1]-1==Xnomboflines-1)){
		return 1;
	}
	else{
		fld[Line][x]=0;
		fld[Line][x+LeftL[Line][elem-1]]=1;
		return 0;
	}	
}
int returnelm(int Line,int elem)
{
	int x1=-1,x2=-1,btake=1,btake1=0,atake=1,atake1=0;
	int k1;
	for (k1=0;k1<elem-1;k1++)
			btake=btake+LeftL[Line][k1];	
		for (k1=0;k1<Xnomboflines;k1++){
			x2++;
			btake1=btake1+fld[Line][k1];
			if (btake1==btake)
				k1=Xnomboflines;	
		}
		for (k1=0;k1<elem-2;k1++)
			atake=atake+LeftL[Line][k1];	
		for (k1=0;k1<Xnomboflines;k1++){
			x1++;
			atake1=atake1+fld[Line][k1];
			if (atake1==atake)
				k1=Xnomboflines;	
		}		
		if (x2==x1+LeftL[Line][elem-2]+1)
			return 1;
		else{
			for (k1=x2;k1<x2+LeftL[Line][elem-1];k1++)
				fld[Line][k1]=0;
			for (k1=x1+LeftL[Line][elem-2]+1;k1<=x1+LeftL[Line][elem-2]+LeftL[Line][elem-1];k1++)
				fld[Line][k1]=1;					
			return 0;
		}
}
int returnchnge(int Line,int elem)
{
	int n=0,x1=-1,x2=-1,btake=1,btake1=0,atake=1,atake1=0,nomb=0;
	int k1;
	while ((LeftL[Line][nomb]!=0) && (nomb<((Xnomboflines/2)+(Xnomboflines%2))))
		nomb++;
	n=chngelm(Line,elem);
	if (n==1)
		return 1;
	else{
		for (k1=0;k1<elem;k1++)
			btake=btake+LeftL[Line][k1];	
		for (k1=0;k1<Xnomboflines;k1++){
			x2++;
			btake1=btake1+fld[Line][k1];
			if (btake1==btake)
				k1=Xnomboflines;	
		}
		for (k1=0;k1<elem-1;k1++)
			atake=atake+LeftL[Line][k1];	
		for (k1=0;k1<Xnomboflines;k1++){
			x1++;
			atake1=atake1+fld[Line][k1];
			if (atake1==atake)
				k1=Xnomboflines;	
		}		
		if (x2==x1+LeftL[Line][elem-1]+1)
			if (elem==1)
				return 3;
			else
				return 2;
		
		else{
			for (k1=x2;k1<x2+LeftL[Line][elem];k1++)
				fld[Line][k1]=0;
			for (k1=x1+LeftL[Line][elem-1]+1;k1<=x1+LeftL[Line][elem-1]+LeftL[Line][elem];k1++)
				fld[Line][k1]=1;
			for (k1=elem+2;k1<=nomb;k1++)
				returnelm(Line,k1);
			return 0;
		}	
	}
}

int chngpos(int Line)
{
	int nomb=0,all=0,elem;
	int k1,k2,n=0,k=1;
	while ((LeftL[Line][nomb]!=0) && (nomb<((Xnomboflines/2)+(Xnomboflines%2))))
		nomb++;
	elem=nomb;
	for (k1=0;k1<nomb;k1++)
		all=all+LeftL[Line][k1];
	all=all+nomb-1;
	if (all==Xnomboflines)
		return 1;
	else{
		n=chngelm(Line,elem);
		if (n==1){
			k=n;
			k2=0;
			while (k!=0 && k!=3){
				k2++;
				k=returnchnge(Line,elem-k2);
			}
		}
		if (k==3)
			return 2;
		else
			return 0;
	}	
}
int filt1(int Clmn,int Nmb)
{
	int k1,n=0;
	for (k1=0;k1<=Nmb;k1++)
		if (fld[k1][Clmn]!=fld[Ynomboflines][k1]){
			k1=Ynomboflines;
			n=1;
		}
	return n;
}
int filt(int Line)
{
	int k=0,p=1,t;
	int k1,Column;
	for (Column=0;Column<Xnomboflines;Column++){
		k1=0;
		while (TopL[Column][k1]!=0){//заполняет левую колонку
			LeftL[Ynomboflines][k1]=TopL[Column][k1];
			k1++;
		}
		startpos(Ynomboflines);
		p=filt1(Column,Line);
		while(k!=2 && k!=1 && p!=0){
			k=chngpos(Ynomboflines);
			p=filt1(Column,Line);
		}
		if (p==0)
			t=0;
		else {
			t=1;
			Column=Xnomboflines;
		}
	}
	return	t;
}
/*
int push(){
	int k=0,p=0;
	int k1;
	for (k1=0;k1<Ynomboflines;k1++)
		startpos(k1);
	for (k1=0;k1<Ynomboflines;k1++){
		p=filt(k1);
		while (k!=2 && k!=1 && p!=0){
			k=chngpos(k1);
			p=filt(k1);
		}
		if (p==0){
			t=0;
			k=0;
		}
		else{
			if (k1==0)
				k1=Ynomboflines;
				t=1;
			else{
				
				k=1;
				while(k==1){
					k1--;
					k=changepos(k1)
				
				}
				
			}
		}
	}	
}
*/
int main()
{	
	int nombofelements=(nomboflines/2)+(nomboflines%2);
	int k1,k2,c,k;
	int Xnombofelements=0,Ynombofelements=0;
	for (k1=0;k1<nomboflines;k1++)
		for (k2=0;k2<nomboflines;k2++)
			fld[k1][k2]=0;
	for (k1=0;k1<nomboflines;k1++)
		for (k2=0;k2<=nombofelements-1;k2++){
			LeftL[k1][k2]=0;
			TopL[k1][k2]=0;
		}
	printf("\nEnter size (x and y)\n");
	while ((c=getchar())!=(int)'\n')
		Xnomboflines=Xnomboflines*10+c-(int)'0';
	while ((c=getchar())!=(int)'\n')
		Ynomboflines=Ynomboflines*10+c-(int)'0';
	Xnombofelements=(Xnomboflines/2)+(Xnomboflines%2);
	Ynombofelements=(Ynomboflines/2)+(Ynomboflines%2);		
	printf("//%d//%d//",Xnombofelements,Ynombofelements);
	printf("Enter Top Line:");				
	for (k1=0;k1<Xnomboflines;k1++){
		printf("\nColumn %d:  ",k1+1);
		for (k2=0;k2<Ynombofelements;k2++){
			printf("\nNmb %d:  ",k2+1);
			while ((c=getchar())!=(int)'\n'){
					TopL[k1][k2]=TopL[k1][k2]*10+c-(int)'0';
			}
			if (TopL[k1][k2]==0)
				k2=Ynombofelements;
			printf("\n");
		}
	}	
	printf("\nEnter Left Column:");	
	for (k1=0;k1<Ynomboflines;k1++){
		printf("\nLine %d: ",k1+1);	
		for (k2=0;k2<Xnombofelements;k2++){
			printf("\nNmb %d:  ",k2+1);
			while ((c=getchar())!=(int)'\n'){
					LeftL[k1][k2]=LeftL[k1][k2]*10+c-(int)'0';
				}
			if (LeftL[k1][k2]==0)
				k2=Xnombofelements;
		}
	}
	printf("Top LIne:");
	for (k1=0;k1<Ynombofelements;k1++){
		printf("\n");
		for (k2=0;k2<Xnomboflines;k2++)
			printf("%d/",TopL[k2][k1]);
	}
	printf("\nLeft Line:");
	for (k1=0;k1<Ynomboflines;k1++){
		printf("\n");
		for (k2=0;k2<Xnombofelements;k2++)
			printf("%d/",LeftL[k1][k2]);
	}			
	/*/------------------------------------------------------------------///Start//*/
	startpos(0);
	startpos(1);
	startpos(2);
	startpos(3);
	startpos(4);
	while (k!=2 && k!=1) {
		k=chngpos(0);
		for (k1=0;k1<Ynomboflines;k1++){
			printf("\n");
			for (k2=0;k2<Xnomboflines;k2++)
				printf("%d/",fld[k1][k2]);
		}
		printf("\n");
	}
	k=filt(4);
	printf("filt: /%d/\n",k);
	
	
	/*/------------------------------------------------------------------///End//*/
	for (k1=0;k1<Ynomboflines;k1++){
		printf("\n");
		for (k2=0;k2<Xnomboflines;k2++)
			printf("%d/",fld[k1][k2]);
	}
	return 0;
}
