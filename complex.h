#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>
#include <math.h>

#define PI 3.14159265359
#define Range 0.0005 //Made up precision range it'll convert any no. in a period of (2*Range) around any integer to intger --> -1.00045=-1

using namespace std;

class complex //we always deal with real and imaginary out side the class for simplicity
{
private:
	float real, img; //we don't need magnitude & phase for every member (memory)
public: //only (void) print will work so to choose bet. precision, range, auto choose your print
	complex();

	complex(float R, float I);
	
	void operator= (complex scnd);
	
	void operator+=(complex scnd);
	
	void operator-=(complex scnd);
	
	void operator*=(complex scnd);
	
	void operator/=(complex scnd);
	
	bool operator==(complex scnd)const;
	
	bool operator!=(complex scnd)const;
	
	complex operator+(complex scnd)const;
	
	complex operator-(complex scnd)const;
	
	complex operator*(complex scnd)const;
	
	complex operator/(complex scnd)const;
	
	complex operator^(float powr)const;
	
	void set_real(float realIn);
	
	void set_img(float imgIn);
	
	float get_real(void)const;
	
	float get_imaginary(void)const;
	
	float get_phase(char format)const;
	
	float get_magnitude(void)const;
	
	void print(void)const;
	
	void print(int null)const;
	
	void conjugate(complex var);
	
	int divide(complex first, complex second);
	
	complex p_r(float magnitude, float phase)const;
	
	complex cconjugate(void)const;
	
	bool has_NaN(void)const;
private: //not used
	complex r_p();

	complex p_r();
};

#endif