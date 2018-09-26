#include<omp.h>
#include<iostream>
#include <cstdlib>

using namespace std;

double step;
int main(int argc,char *argv[])
{
	int i;
	double pi;
	if (argc != 3) {
		cerr << "usage: pi num_steps number_of_threads" << endl;
		exit(-1);
	}
	
	// num_steps is number of rectangles to use
	long int num_steps = atol (argv[1]);
	long int num_threads=atol(argv[2]);
	// step is width of each rectangle
	double step = 1.0/(double) num_steps;
	
	// x is midpoint of each rectangle
	// sum accumulates rectangle heights (i.e. values of f(x))
	double x, sum = 0.0;
	double delta;
	
	omp_set_num_threads(num_threads);
	cout<<"step is"<<step<<endl;
	double start =omp_get_wtime();
	#pragma omp parallel private(x,i)
	{
		
	#pragma omp for reduction(+:sum) 
	for(i=0;i<num_steps;i++)
		{
			x = (i - 0.5) * step;
			sum = sum + 4.0 / (1.0 + x*x);
			
		}
		
	}
	pi=step*sum;
	delta=omp_get_wtime()-start;
	
	cout<<"Pi is"<<pi<<endl;
	cout<<"Time taken is "<<delta<<endl;
	
	
	return 0;
}