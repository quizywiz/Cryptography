#include <iostream>
#include<cstring>
#define rep(i,a,b)for(i=a;i<b;++i)
using namespace std;
int RCON[11][8]={
				1,0,0,0,1,1,0,1,
				0,0,0,0,0,0,0,1,
				0,0,0,0,0,0,1,0,
				0,0,0,0,0,1,0,0,
				0,0,0,0,1,0,0,0,
				0,0,0,1,0,0,0,0,
				0,0,1,0,0,0,0,0,
				0,1,0,0,0,0,0,0,
				1,0,0,0,0,0,0,0,
				0,0,0,1,1,0,1,1,
				0,0,1,1,0,1,1,0};
void rotward(int b[32])
{
	int i;
	int j=8;
	for(i=0;i<32;++i)
	{
		b[i]=b[j];
		++j;
		if(j>=32)
			j-=32;
	}
}
void fieldmult(int a[8], int b[8], int c[8])
{
//	for(int l=0;l<8;++l)printf("%d",a[l]);
//	printf("\n");
//	for(int l=0;l<8;++l)printf("%d",b[l]);
//	printf("\n");
	//printf("%d")
	for(int i=0;i<8;++i)c[i]=0;
	for(int i=0;i<8;++i)
	{
		if(a[7-i]==0)continue;
		for(int j=0;j<8;++j)
		{
			if(b[7-j]==0)continue;
			int k=i+j;
		//	printf("%d%d%d\n",i,j,k);
			//int temp[8]={0};
			if(k>=8)
			{
				
				k-=8;
				int m[8]={0,0,0,1,1,0,1,1};
				int n[8]={0,0,0,0,0,0,0,0};
				n[7-k]=1;
				int t[8];
				fieldmult(m,n,t);
				for(int l=0;l<8;++l)c[l] = (c[l]+t[l])&1;
				
			}
			else c[7-k] = (c[7-k] + 1)&1;
		}
	}
}
void fieldinv(int a[8], int ans[8])
{
	int i1,i2,i3,i4,i5,i6,i7,i8;
	int temp[8];
	rep(i1,0,2)rep(i2,0,2)rep(i3,0,2)rep(i4,0,2)rep(i5,0,2)rep(i6,0,2)rep(i7,0,2)rep(i8,0,2)
	{
		ans[0]=i1;
		ans[1]=i2;
		ans[2]=i3;
		ans[3]=i4;
		ans[4]=i5;
		ans[5]=i6;
		ans[6]=i7;
		ans[7]=i8;
		
		fieldmult(ans,a,temp);
		int k;
		bool isone=true;
		if(temp[7]==0)continue;
		rep(k,0,7)
		{
			if(temp[k]==1)
			isone=false;
		}
		if(isone)
		{
			
			return;
		}
	}
	;
}
void subbyte(int a[8], int b[8])
{
	bool zero = true;
	for(int i=0;i<8;++i)
		if(a[i]!=0)zero=false;
	if(zero)return;
	int z[8],c[8]={0,1,1,0,0,0,1,1};
	fieldinv(a,z);
	int k;
//	rep(k,0,8)printf("%d",z[k]);
//	printf("\n");
	for(int i=0;i<8;++i)
	{
		b[7-i] = (z[7-i] + z[(7-(i+4))&7] + z[(7-(i+5))&7] + z[(7-(i+6))&7] + z[(7-(i+7))&7] + c[7-i])&1;
	}
//	rep(k,0,8)printf("%d",b[k]);
//	printf("\n\n");
}
void printinhex(int a[32])
{
	int k;
	for(k=0;k<32;k+=4)
	{
		int c = 8*a[k]+4*a[k+1]+2*a[k+2]+a[k+3];
		if(c<=9){printf("%d",c);continue;}
		else
		{
			printf("%c",c-10+'A');
		}
	}
}
void subword(int a[32], int b[32])
{
	subbyte(a,b);
	subbyte(a+8,b+8);
	subbyte(a+16,b+16);
	subbyte(a+24,b+24);
}
int main() {
	// your code goes here
	char key[129];
	int i;
	scanf("%s",key);
	int keyint[128]={0};
	int len = strlen(key);
	for(i=0;i<len;++i)
	{
		keyint[i]=(int)(key[i]-'0');
	
	}
//	rotward(keyint);
//	for(i=0;i<len;++i)	printf("%d",keyint[i]);
	printf("\n");
//	fieldmult(keyint,keyint+8,keyint+16);
//	fieldinv(keyint,keyint+24);
	int w[44][32];
	for(i=0;i<=3;++i)
	{
		int k;
		rep(k,0,32)
		{
			w[i][k]=keyint[i*32+k];
			printf("%d",w[i][k]);
		}
		printf("--%d\n",1+i/4);
	}
	for(i=4;i<=43;++i)
	{
		int k,temp[32];
		rep(k,0,32)temp[k]=w[i-1][k];
		
	//	rep(k,0,32)printf("%d",w[i][k]);
		if((i&3)==0)
		{
			int temp2[32];
			
			rotward(temp);
			
			subword(temp,temp2);
	//		rep(k,0,32)printf("%d",temp2[k]);
	//		printf("%d\n",i);
			rep(k,0,8)
			temp[k] = (temp2[k]+RCON[i/4][k])&1;
			rep(k,8,32)
			temp[k]=temp2[k];
	//		rep(k,0,32)printf("%d",temp[k]);
	//		printf("%d\n",1+i/4);	
		}
		rep(k,0,32)w[i][k]=(w[i-4][k]+temp[k])&1;
		rep(k,0,32)printf("%d",w[i][k]);
		printf("--%d\n",1+i/4);
	}
	for(i=0;i<44;i+=4)
	{
		printinhex(w[i]);
		printinhex(w[i+1]);
		printinhex(w[i+2]);
		printinhex(w[i+3]);
		printf("\n");
	}
	
	//for(i=0;i<128;++i)printf("%d",keyint[i]);
	return 0;
}