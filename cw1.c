#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#define numboflines 50
	int  fld[numboflines+1][numboflines+1]; 
	int TopL[numboflines][(numboflines/2)+(numboflines%2)];
	int	LeftL[numboflines][(numboflines/2)+(numboflines%2)];
	
void startpos(int Line,int Xnumboflines)
{	
	int numb=0;
	int i=0,j=0,x=0;	
	for (i=0;i<Xnumboflines;i++)
		fld[Line][i]=0;
	while ((LeftL[Line][numb]!=0) && (numb<((Xnumboflines/2)+(Xnumboflines%2))))
		numb++;	
	for (i=0;i<numb;i++){
		for (j=1;j<=LeftL[Line][i];j++){
			fld[Line][x]=1;
			x++;
		}			
	x++;
	}		
}
int chngelm(int Line,int elem,int Xnumboflines)
{	
	int i;
	int x=-1,take=1,take1=0;
	for (i=0;i<elem-1;i++)
		take=take+LeftL[Line][i];	
	for (i=0;i<Xnumboflines;i++){
		x++;
		take1=take1+fld[Line][i];
		if (take1==take)
			i=Xnumboflines;	
	}	
	if ((fld[Line][x+LeftL[Line][elem-1]+1]!=0) || (x+LeftL[Line][elem-1]-1==Xnumboflines-1)){
		return 1;
	}
	else{
		fld[Line][x]=0;
		fld[Line][x+LeftL[Line][elem-1]]=1;
		return 0;
	}	
}
int returnelm(int Line,int elem,int Xnumboflines)
{
	int x1=-1,x2=-1,btake=1,btake1=0,atake=1,atake1=0;
	int i;
	for (i=0;i<elem-1;i++)
			btake=btake+LeftL[Line][i];	
	for (i=0;i<Xnumboflines;i++){
		x2++;
		btake1=btake1+fld[Line][i];
		if (btake1==btake)
			i=Xnumboflines;	
	}
	for (i=0;i<elem-2;i++)
		atake=atake+LeftL[Line][i];	
	for (i=0;i<Xnumboflines;i++){
		x1++;
		atake1=atake1+fld[Line][i];
		if (atake1==atake)
			i=Xnumboflines;	
	}		
	if (x2==x1+LeftL[Line][elem-2]+1)
		return 1;
	else{
		for (i=x2;i<x2+LeftL[Line][elem-1];i++)
			fld[Line][i]=0;
		for (i=x1+LeftL[Line][elem-2]+1;i<=x1+LeftL[Line][elem-2]+LeftL[Line][elem-1];i++)
			fld[Line][i]=1;					
		return 0;
	}
}
int returnchnge(int Line,int elem,int numb,int Xnumboflines)
{	
	int n=0,r;
	int i;
	n=chngelm(Line,elem,Xnumboflines);
	if (n==1)
		return 2;
	else{
		r=returnelm(Line,elem+1,Xnumboflines);		
		if (r==1)
			return 1;
		else{
			for (i=elem+2;i<=numb;i++)
				returnelm(Line,i,Xnumboflines);
			return 0;
		}	
	}
}

int chngpos(int Line,int Xnumboflines)
{	
	int numb=0,all=0,elem;
	int i,n=0,k=3;
	while ((LeftL[Line][numb]!=0) && (numb<((Xnumboflines/2)+(Xnumboflines%2))))
		numb++;
	elem=numb;
	for (i=0;i<numb;i++)
		all=all+LeftL[Line][i];
	all=all+numb-1;
	if (all==Xnumboflines || all==-1)
		return 1;
	else{
		n=chngelm(Line,numb,Xnumboflines);
		if (n==1 && numb!=1){
			while (k!=0 && k!=1 && elem>1){
				elem--;
				k=returnchnge(Line,elem,numb,Xnumboflines);
			}
		}
		if ((k==2 && elem==1) || (n==1 && numb==1))
			return 2;
		else
			return 0;
	}
}
int filt1(int Clmn,int Nmb,int Ynumboflines)
{	
	int i,n=0;
	for (i=0;i<=Nmb;i++){ 
		if (fld[i][Clmn]!=fld[Ynumboflines][i]){
			i=Nmb+1;
			n=1;
		}
	} 
	return n;
}
int filt(int Line,int Xnumboflines,int Ynumboflines)
{
	int k=0,p=1,t;
	int i,j,Column;
	for (Column=0;Column<Xnumboflines;Column++){
		i=0;
		while (TopL[Column][i]!=0){
			LeftL[Ynumboflines][i]=TopL[Column][i];
			i++;
		}
		startpos(Ynumboflines,Ynumboflines);
		p=filt1(Column,Line,Ynumboflines);
		while(k!=2 && k!=1 && p!=0){
			k=chngpos(Ynumboflines,Ynumboflines);
			p=filt1(Column,Line,Ynumboflines);
		}
		for (j=0;j<=i;j++)
			LeftL[Ynumboflines][j]=0;
		if (p==0)
			t=0;
		else {
			t=1;
			Column=Xnumboflines;
		}
	}
	return	t;
}

int push(int Xnumboflines,int Ynumboflines)
{
	int k=0,p=0,t=2;
	int i;
	for (i=0;i<Ynumboflines;i++)
		startpos(i,Xnumboflines);
			
	for (i=0;i<Ynumboflines;i++){ 
		p=filt(i,Xnumboflines,Ynumboflines);	
		while (k!=2 && k!=1 && p!=0){
			k=chngpos(i,Xnumboflines);
			p=filt(i,Xnumboflines,Ynumboflines);
		}
		if (p==0){
			t=0;
			k=0;
		}
		else{
			k=1;
			while((k==1 || k==2) && i>0){
				startpos(i,Xnumboflines);
				k=chngpos(i-1,Xnumboflines);
				i--;
			}
			i--;
			if (i<0 && k==1){
				exit(1);
			}
		}
	}
	return t;	
}

int main()
{	
	int i,j,c,k;
	int Xnumboflines=0;
	int Ynumboflines=0;
	for (i=0;i<numboflines;i++)
		for (j=0;j<numboflines;j++)
			fld[i][j]=0;
	for (i=0;i<numboflines;i++)
		for (j=0;j<=(numboflines/2)+(numboflines%2)-1;j++){
			LeftL[i][j]=0;
			TopL[i][j]=0;
		}
	printf("\nEnter size (x and y)\n");
	while ((c=getchar())!=(int)'\n')
		Xnumboflines=Xnumboflines*10+c-(int)'0';
	while ((c=getchar())!=(int)'\n')
		Ynumboflines=Ynumboflines*10+c-(int)'0';
	printf("Enter Top Line(%d elements):",(Ynumboflines/2)+(Ynumboflines%2));
	__fpurge(stdin);				
	for (i=0;i<Xnumboflines;i++){
		printf("\nColumn %d:  ",i+1);
		for (j=0;j<=(Ynumboflines/2)+(Ynumboflines%2);j++){
			(void)scanf("%d",&TopL[i][j]);
			if (TopL[i][j]==0){printf("%d/%d",i,j);
				j=(Ynumboflines/2)+(Ynumboflines%2);
				__fpurge(stdin);
			}
			else
				(void)scanf(",");
		}
	}
		
	printf("\nEnter Left Column(%d elements):",(Xnumboflines/2)+(Xnumboflines%2));
		
	for (i=0;i<Ynumboflines;i++){
		printf("\nLine %d: ",i+1);	
		for (j=0;j<=(Xnumboflines/2)+(Xnumboflines%2);j++){
			scanf("%d,",&LeftL[i][j]);
			if (LeftL[i][j]==0){
				j=(Xnumboflines/2)+(Xnumboflines%2);
				__fpurge(stdin);
			}
			else 
				(void)scanf(",");
		}
	}
	
	printf("Top LIne:");
	
	for (i=0;i<(Ynumboflines/2)+(Ynumboflines%2);i++){
		printf("\n");
		for (j=0;j<Xnumboflines;j++)
			printf("%3d/",TopL[j][i]);
	}
	
	printf("\nLeft Line:");
	for (i=0;i<Ynumboflines;i++){
		printf("\n");
		for (j=0;j<(Xnumboflines/2)+(Xnumboflines%2);j++)
			printf("%3d/",LeftL[i][j]);
	}

	k=push(Xnumboflines,Ynumboflines);

	if (k==0)
		for (i=0;i<Ynumboflines;i++){
			printf("\n");
			for (j=0;j<Xnumboflines;j++)
				if (fld[i][j]==1)
					printf("██");
				else 
					printf("  ");
		}
	else
		printf("\nCan't do it!!!!!!!!!!!!!!!((((((\n");
		
	return 0;
}
