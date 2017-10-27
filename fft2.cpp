#include <fstream>
#include <iostream>
#include <complex>
#include <cmath>
#include <cstdlib>
#define PI 3.1415926535897932384626433832795028841971
using namespace std;

void fft(complex<double> x[],complex<double> y[], int p)
{
	cout<<"start fft:"<<p<<endl;
	if(p==0)
	{
		y[0]=x[0];
		return;
	}
	int n = 1<<p;
	complex<double> wn(cos(2.0/n*PI),sin(2.0/n*PI));
	complex<double> *xo = new complex<double>[n/2];
	complex<double> *xe = new complex<double>[n/2];
	complex<double> *yo = new complex<double>[n/2];
	complex<double> *ye = new complex<double>[n/2];
	
	int i;
	for(i=0;i<n/2;i++)
	{
		xe[i]=x[i*2];
		xo[i]=x[i*2+1];
	}
	fft(xo,yo,p-1);
	fft(xe,ye,p-1);
	complex<double> t;
	complex<double> w(1,0);
	for(i=0;i<n/2;i++)
	{
		t=w*yo[i];
		cout<<t.real()<<endl;
		y[i]=ye[i]+t;
		y[i+n/2]=ye[i]-t;
		w=w*wn;
	}
	delete[] yo;
	delete[] ye;
	delete[] xo;
	delete[] xe;
	return;
}

void get_rev(int bit,int *rev)
{
	for(int i=0;i<(1<<bit);i++)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	}

}

void fft_iterate(complex<double> x[], complex<double> y[], int p)
{
	int rev[1<<p]={};
	get_rev(p,rev);
	int i;
	int N = 1<<p;
	complex<double> wn;
	complex<double> w(1,0);
	complex<double> yo,ye;
	complex<double> temp;
	int j,k;
	int n;
	for(i=0;i<N;i++)
	{
		y[i]=x[rev[i]];
	}
	for(i=1;i<=p;i++)
	{
	
		n=1<<i;
		//****
		//n==length
		//****
		wn=complex<double>(cos(2.0*PI/n),sin(2.0*PI/n));

		for(j=0;j<N;j+=n)
		{
			w=1;
			for(k=j;k<j+(n>>1);k++)
			{
				
				ye=y[k];
				yo=y[k+(n>>1)];
				temp=yo*w;
				y[k]=ye+temp;
				y[k+(n>>1)]=ye-temp;
				w*=wn;
				//foreach t in [1..n/2];
				//Y[t] = Yo[t] + W(n,k) * Ye[t];
				//Y[t+n/2] = Yo[t] -  W(n,k)Ye[t];
			}

		}
	}
}

int retp(int n)
{
	int t=1,p=0;
	while(t<n) {
		t=t<<1;
		p++;
	}
	return p;
}

ifstream fin("test.in");
ofstream fout("test.out");
int main()
{
	int n,i,p;
	int N;
	//cin>>n;
	fin>>n;
	p=retp(n);
	N=1<<p;
	double t;
	complex<double> *x = new complex<double>[N];
	complex<double> *y = new complex<double>[N];
	for(i=0;i<n;i++){
		x[i]=0;
		y[i]=0;
	}
	for(i=0;i<n;i++)
	{
		//cin>>t;
		fin>>t;
		x[i]=t;
	}
	fft_iterate(x,y,p);
	for(i=0;i<N;i++)
	{
		//cout<<y[i].real<<"+j"<<y[i].imag<<endl;
		fout<<y[i].real()<<"+j"<<y[i].imag()<<endl;
	}

	return 0;
}

