#ifndef VECTOR_M_H
#define VECTOR_M_H

#include "complex.h"

#define Size 100 //should equal the largest of (Size_r & Size_c)

class vector_m
{
private:
	complex* vector = new complex[Size];
	
	int count;
public:
	vector_m();
	
	vector_m(int elements);
	
	void set_element(int pos, complex value);
	
	complex get_element(int pos)const;
	
	void set_count(int no);
	
	int get_count(void)const;
	
	void operator=(vector_m var);
	
	vector_m operator*(complex factor)const;
	
	vector_m operator/(complex factor)const;
	
	vector_m operator+(vector_m second)const;
	
	vector_m operator-(vector_m second)const;
	
	bool is_zero_vec()const;
	
	bool is_zero_vec_inverseSpecial(int count)const;
	
	void print_C(void)const;
	
	bool has_NaN(void)const;
};

#endif