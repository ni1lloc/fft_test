#include <iostream>
#include <complex>
#include <cmath>
#include <cstdlib>
#define PI 3.1415926535897932384626433832795028841971
using namespace std;

void fft(complex<double> x[], complex<double> y[], int p)
{
	if(p==0)
	{
		y[0]=x[0];
		return;
	}
	int n = 1<<p;
	complex<double> wn(cos(2/n*PI),sin(2/n*PI));
	complex<double> *xo = new complex<double>[n/2];
	complex<double> *xe = new complex<double>[n/2];
	complex<double> *yo = new complex<double>[n/2];
	complex<double> *ye = new complex<double>[n/2];
	
	int i;
	for(i=0;i<n/2;i++)
	{
		xo[i]=x[i*2];
		xe[i]=x[i*2+1];
	}
	fft(xo,yo,p-1);
	fft(xe,ye,p-1);
	complex<double> t;
	complex<double> w(1,0);
	for(i=0;i<n/2;i++)
	{
		t=w*ye(i);
		y[i]=yo[i]+t;
		y[i+n/2]=yo-t;
		w=w*wn;
	}
	delete[] yo;
	delete[] ye;
	delete[] xo;
	delete[] xe;
	return;
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

int main()
{
	int n,i;
	int N;
	cin>>n;
	N=1<<retp(n);
	double t;
	complex<double> *x = new complex<double>[N];
	complex<double> *y = new complex<double>[N];
	for(i=0;i<n;i++)
	{
		cin>>t;
		x[i]=t;
	}
	fft(x,y,p);
	for(i=0;i<N;i++)
	{
		cout<<y[i].real<<"+j"<<y[i].imag<<endl;
	}

	return 0;
}

