#ifndef MATRIX_H
#define MATRIX_H

#include <time.h>
#include <vector>
#include "vector_m.h"

//note that the sizeof a matrix is 80.004kb = 10000 x 8 as the complex is 8b and the vector_m is 0.804kb
//the stack can handle max of 7 matrixes during runtime (either from the main or from inside any other function) that's about 0.6mb

#define Size_r 100 //rows max. size
#define Size_c 100 //columns max. size
#define Rand 4000
#define Rand_D 29 //Dimentions Rand 1-->(Rand_D+1)

//hidden features (rand,qrand,prand,skip,ans,exit) q:square , p:proper

class matrix //for every error we encounter the function will print the error then return 1 & for success it'll return 0 so that in the main if a function returned 1 we'll repeat the input
{            //to print the errors for the first user use the non-operator functions //we could have used vector<vector<complex>> with push_back() to avoid static Size 
private:
	complex** mat = new complex*[Size_r]; //new array of pointers to complex //mat[0]{1,2-i,0,...} --> mat[n] is a pointer to an array of complex
	                                                                         //mat[1]{0,0,0,.....}
																			 //mat[2]{...........}
	                                                                         //.
	                                                                         //.
	int rows, columns;
public: //we'll not define these functions returning matrix because it'll elemenate the error checking or we'll have to find an alternative way to check errors
	matrix();
	
	matrix(int row_count, int column_count);
	
	void set_dimentions(int row, int column);
	
	void set_element(int row, int column, complex value);
	
	void set_a_row(int position, matrix row);
	
	void set_a_column(int position, matrix column);
	
	void set_a_row(int position, vector_m row);
	
	void set_a_column(int position, vector_m column);
	
	void get_a_row(int position, matrix full);
	
	void get_a_column(int position, matrix full);
	
	vector_m get_a_row(int position)const;
	
	vector_m get_a_column(int position)const;
	
	void swap_rows(int from, int to);
	
	void swap_columns(int from, int to);
	
	void set_rows(int row);
	
	void set_columns(int column);
	
	int get_rows(void)const;
	
	int get_columns(void)const;
	
	complex get_element(int row, int column)const;
	
	void print(void)const;
	
	void intialize(void);
	
	void operator=(matrix var);
	
	void operator+=(matrix var);
	
	void operator-=(matrix var);
	
	void operator*=(matrix var);
	
	void operator/=(matrix var);
	
	bool operator==(matrix var)const;
	
	bool operator!=(matrix var)const;
	
	matrix operator+(matrix var)const;
	
	matrix operator-(matrix var)const;
	
	matrix operator*(matrix var)const;
	
	matrix operator/(matrix var)const;
	
	matrix operator^(unsigned int power)const;

	/*to avoid memory leaks*/
	void deletem(void);
	
	matrix m_inverse()const;
	
	matrix m_transpose()const;
	
	matrix m_eliminate()const;
	
	int add(matrix first, matrix second);
	
	int subtract(matrix first, matrix second);
	
	int multiply(matrix first, matrix second);
	
	int transpose(matrix var);
	
	int power(matrix var, string pow1);
	
	/*this function changes (*this) so just use it in the direct determinant calculation*/
	complex determinant(bool &state)const;
	
	complex determinant()const;
	
	vector_m cramer(matrix ans_column, bool &state);
	
	vector_m cramer(matrix ans_column);
	
	int eliminate(matrix var);
	
	int eliminate_d(matrix var);
	
	int rank(void);
	
	int rank_d(void);
	
	int inverse(matrix var);
	
	int inverse_d(matrix var);
	
	int Old_inverse(matrix var);
	
	int divide(matrix first, matrix second);
	
	int fill(string input);
	
	void randomize(void);
	
	void square_randomize(void);
	
	void proper_randomize(int rows0, int columns0);
	
	void selective_randomize(int rows0, int columns0);
	
	bool has_NaN(void);
private:
	complex determinant_R(bool &state);
	
	complex matrix_of_coFactors(int d, int c)const;
	
	complex multiply_diagonal_elements(void)const;
	
	int no_of_zero_vectors(void)const;
	
	void create_NaN(void);
};

//all the int functions are kept to give the detailed reason of error if needed but they can be suspended and use the operators instead (with no cout)
//there are two version for every function ... one having cout << error and one that returns NaN's

#endif