#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.14159265358979323846
class Perenos
{
private:
	double **arr;
public:
	int jt, kt;
	double sttau,sth,kurt;
	Perenos()
	{
		printf("VVEDITE KOLLICHESTVO VREMENNYH SLOEV ");
		scanf("%d", &jt);
		printf("VVEDITE KOLLICHESTVO DELENIY STERZHNYA ");
		scanf("%d", &kt);
		printf("\n");
		sttau = 1.0 / jt;
		sth = 1.0 / kt;
		kurt = sttau / (2.0*sth);
		arr = (double**)calloc(sizeof(double*), jt + 1);
		for (int i = 0; i < jt + 1; i++)
			arr[i] = (double*)calloc(sizeof(double), kt + 1);
		for (int i = 0; i <= kt; i++)
		{
			arr[0][i] = Phi(i*sth);
		}
		for (int i = 1; i < jt + 1; i++) {
			arr[i][kt] = 2.5*M_PI;
		}
	}
	void write()
	{
		for (int i = 0; i < jt + 1; i++) {
			printf("\n");
			for (int j = 0; j < kt + 1; j++)
				printf("%lf ", arr[i][j]);
		}
		printf("\n");
	}
	double C(double x, double t)
	{
		return((sin(2.0*M_PI*x)*sin(M_PI*t)) / (2.0*cos(2.0*M_PI*x)*cos(M_PI*t) + 2.5));
	}
	double Phi(double x)
	{
		return(sin(2.0*M_PI*x) + 2.5*M_PI*x);
	}
	double U(double x, double t)
	{
		return(sin(2.0*M_PI*x)*cos(M_PI*t) + 2.5*M_PI*x);
	}
	void vychsloy(int n)
	{
		for (int i = 1; i < kt; i++)
		{
			arr[n][i] = 0.5*(arr[n - 1][i + 1] + arr[n - 1][i - 1]) - kurt*C(i*sth, (n-1)*sttau)*(arr[n - 1][i + 1] - arr[n - 1][i - 1]);
		}
	}
	void toFile()
	{
		FILE * f = fopen("output.txt", "w");
		for (int i = 0; i < jt + 1; i++) {
			for (int j = 0; j < kt + 1; j++)
				fprintf(f, "%lf %lf %lf\n", i*sttau, j*sth, arr[i][j]);
			fprintf(f, "\n");
		}
		FILE *g = fopen("output1.txt", "w");
		for (int i = 0; i < jt + 1; i++) {
			for (int j = 0; j < kt + 1; j++)
				fprintf(g, "%lf %lf %lf\n", i*sttau, j*sth, U(j*sth, i*sttau));
			fprintf(g, "\n");
		}
		fclose(f);
		fclose(g);
	}
	void pogresh()
	{
		double max = 0;
		for (int i = 1; i < jt; i++)
			for (int j = 1; j < kt; j++)
				if (fabs(U(j*sth, i*sttau) - arr[i][j])>max)
					max = fabs(U(j*sth, i*sttau) - arr[i][j]);
		printf("%lf\n", max);
	}
};
void main()
{
	Perenos * per = new Perenos();
	//per->write();
	for (int i = 1; i < per->jt + 1; i++)
		per->vychsloy(i);
	//per->write();
	//for (int i = 0; i < per->jt + 1; i++)
	//{
	//	printf("\n");
	//	for (int j = 0; j < per->kt + 1; j++)
	//		printf(" %lf", per->U(j*per->sth, i*per->sttau));
	//}
	printf("\n");
	per->toFile();
	per->pogresh();
}
