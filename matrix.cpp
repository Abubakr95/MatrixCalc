#include "matrix.h"

	matrix::matrix()
	{
		for (int i = 0; i < Size_r; i++)
			mat[i] = new complex[Size_c]; //each pointer points to an array of complexes
		//all complex values are intialized with zeros and there can not be an empty matrix
		rows = 1;
		columns = 1;
	}

	matrix::matrix(int row_count, int column_count) //we better not make (new complex[column_count]) cause if we try to equalize this matrix with a bigger one latter some values will be outside this one 
	{
		for (int i = 0; i < Size_r; i++)
			mat[i] = new complex[Size_c]; //each pointer points to an array of complexes
		//all complex values are intialized with zeros and there can not be an empty matrix
		rows = row_count;
		columns = column_count;
	}

	void matrix::set_dimentions(int row, int column)
	{
		rows = row;
		columns = column;
	}

	void matrix::set_element(int row, int column, complex value)
	{
		mat[row][column] = value;
	}

	void matrix::set_a_row(int position, matrix row) //position starts from 0
	{
		if (row.columns != 1)
			return;
		for (int n = 0; n < columns; n++) //if the row is shorter than the matrix it leaves the rest as it is
		{
			if (n >= row.columns)
				break;
			mat[position][n] = row.mat[0][n];
		}
	}

	void matrix::set_a_column(int position, matrix column) //position starts from 0
	{
		if (column.columns != 1)
			return;
		for (int n = 0; n < rows; n++)   //if the column is shorter than the matrix it leaves the rest as it is
		{
			if (n >= column.rows)
				break;
			mat[n][position] = column.mat[n][0];
		}
	}

	void matrix::set_a_row(int position, vector_m row) //position starts from 0
	{
		for (int n = 0; n < columns; n++) //if the row is shorter than the matrix it leaves the rest as it is
		{
			if (n >= row.get_count())
				break;
			mat[position][n] = row.get_element(n);
		}
	}

	void matrix::set_a_column(int position, vector_m column) //position starts from 0
	{
		for (int n = 0; n < rows; n++)   //if the column is shorter than the matrix it leaves the rest as it is
		{
			if (n >= column.get_count())
				break;
			mat[n][position] = column.get_element(n);
		}
	}

	void matrix::get_a_row(int position, matrix full) //position starts from 0
	{
		for (int n = 0; n < full.columns; n++)
			mat[0][n] = full.mat[position][n];
		columns = full.columns;
		rows = 1;
	}

	void matrix::get_a_column(int position, matrix full) //position starts from 0
	{
		for (int n = 0; n < full.rows; n++)
			mat[n][0] = full.mat[n][position];
		columns = 1;
		rows = full.rows;
	}

	vector_m matrix::get_a_row(int position)const //position starts from 0
	{
		vector_m row(columns);
		for (int n = 0; n < columns; n++)
			row.set_element(n, mat[position][n]);
		return row;
	}

	vector_m matrix::get_a_column(int position)const //position starts from 0
	{
		vector_m column(rows);
		for (int n = 0; n < rows; n++)
			column.set_element(n, mat[n][position]);
		return column;
	}

	void matrix::swap_rows(int from, int to)
	{
		vector_m first, second;
		first = (*this).get_a_row(from);
		second = (*this).get_a_row(to);
		(*this).set_a_row(to, first);
		(*this).set_a_row(from, second);
	}

	void matrix::swap_columns(int from, int to)
	{
		vector_m first, second;
		first = (*this).get_a_column(from);
		second = (*this).get_a_column(to);
		(*this).set_a_column(to, first);
		(*this).set_a_column(from, second);
	}

	void matrix::set_rows(int row)
	{
		rows = row;
	}

	void matrix::set_columns(int column)
	{
		columns = column;
	}

	int matrix::get_rows(void)const
	{
		return rows;
	}

	int matrix::get_columns(void)const
	{
		return columns;
	}

	complex matrix::get_element(int row, int column)const
	{
		return mat[row][column];
	}

	void matrix::print(void)const
	{
		cout << '[';
		for (int m = 0; m < rows; m++)
		{
			for (int n = 0; n < columns; n++)
			{
				mat[m][n].print();
				if (m != (rows - 1))
				{
					if (n == (columns - 1))
						cout << ";";
					else
						cout << " ";
				}
				else
				{
					if (n != (columns - 1))
						cout << " ";
				}
			}
		}
		cout << ']';
	}

	void matrix::intialize(void)
	{
		for (int row = 0; row < rows; row++) //first input rows
			for (int column = 0; column < columns; column++) //second input columns
				mat[row][column] = complex(0, 0);
	}

	void matrix::operator=(matrix var)
	{
		for (int m = 0; m < var.rows; m++)
		{
			for (int n = 0; n < var.columns; n++)
			{
				mat[m][n] = var.mat[m][n];
			}
		}
		rows = var.rows;
		columns = var.columns;
	}

	void matrix::operator+=(matrix var)
	{
		(*this) = (*this) + var;
	}

	void matrix::operator-=(matrix var)
	{
		(*this) = (*this) - var;
	}

	void matrix::operator*=(matrix var)
	{
		(*this) = (*this) * var;
	}

	void matrix::operator/=(matrix var)
	{
		(*this) = (*this) / var;
	}

	bool matrix::operator==(matrix var)const
	{
		bool state = true;
		for (int m = 0; m < var.rows; m++)
			for (int n = 0; n < var.columns; n++)
				if (mat[m][n] != var.mat[m][n])
					state = false;
		if (rows != var.rows || columns != var.columns)
			state = false;
		return state;
	}

	bool matrix::operator!=(matrix var)const
	{
		bool state = false;
		for (int m = 0; m < var.rows; m++)
			for (int n = 0; n < var.columns; n++)
				if (mat[m][n] != var.mat[m][n])
					state = true;
		if (rows != var.rows || columns != var.columns)
			state = true;
		return state;
	}

	matrix matrix::operator+(matrix var)const
	{
		if ((rows != var.rows) || (columns != var.columns))
		{
			var.set_element(0, 0, complex(nanf(0), nanf(0)));
			// the two matrixes don't have the same dimentions
			return var;
		}
		else
		{
			matrix temp(rows, columns);
			for (int row = 0; row < rows; row++)
				for (int column = 0; column < columns; column++)
					temp.mat[row][column] = mat[row][column] + var.mat[row][column];
			return temp;
		}
	}

	matrix matrix::operator-(matrix var)const
	{
		if ((rows != var.rows) || (columns != var.columns))
		{
			var.set_element(0, 0, complex(nanf(0), nanf(0)));
			// the two matrixes don't have the same dimentions
			return var;
		}
		else
		{
			matrix temp(rows, columns);
			for (int row = 0; row < rows; row++)
				for (int column = 0; column < columns; column++)
					temp.mat[row][column] = mat[row][column] - var.mat[row][column];
			return temp;
		}
	}

	matrix matrix::operator*(matrix var)const
	{
		if (get_rows() == 1 && get_columns() == 1) //if it's a scalar
		{
			for (int row = 0; row < var.rows; row++) //first input rows
				for (int column = 0; column < var.columns; column++) //second input columns
					var.mat[row][column] = mat[0][0] * var.mat[row][column];
			return var;
		}
		else if (var.get_rows() == 1 && var.get_columns() == 1) //if it's a scalar
		{
			complex factor = var.mat[0][0]; //this method to keep the function const
			for (int row = 0; row < rows; row++) //first input rows
				for (int column = 0; column < columns; column++) //second input columns
					var.mat[row][column] = mat[row][column] * factor;
			var.set_dimentions(rows, columns);
			return var;
		}
		else if (columns != var.rows) //m*n,k*j ---> n=k , out [m,j]
		{
			var.set_element(0, 0, complex(nanf(0), nanf(0)));
			// the two matrixes don't have the same dimentions
			return var;
		}
		else
		{   //no need for intialization with zeros
			matrix temp(rows, var.columns);
			for (short row = 0; row < rows; row++) //first input rows
				for (short column = 0; column < var.columns; column++) //second input columns
					for (short x = 0; x < columns; x++)
						temp.mat[row][column] += (mat[row][x] * var.mat[x][column]);
			return temp;
		}
	}

	matrix matrix::operator/(matrix var)const
	{
		if (var.get_rows() == 1 && var.get_columns() == 1) //if it's a scalar
		{
			complex factor = var.mat[0][0];
			for (int row = 0; row < rows; row++) //first input rows
				for (int column = 0; column < columns; column++) //second input columns
					var.mat[row][column] = mat[row][column] / factor;
			var.set_dimentions(rows, columns);
			return var;
		}
		//we'll give the imaginaries to this function just to use in the multiply function as matrixes full of zeros instead of defining and intializing 3 new matrixes
		else if (columns != var.rows || var.columns != var.rows) //m*n,k*j ---> n=k , out [m,j]
		{
			for (int m = 0; m < var.rows; m++)
				for (int n = 0; n < var.columns; n++)
					var.mat[m][n] = complex(nan(""), nan(""));
			return var;
		}
		else
			return (*this) * var.m_inverse();
	}

	matrix matrix::operator^(unsigned int power)const
	{
		if (columns != rows) //m*n,k*j ---> n=k , out [m,j]
		{
			matrix var(rows, columns);
			for (int m = 0; m < var.rows; m++)
				for (int n = 0; n < var.columns; n++)
					var.mat[m][n] = complex(nan(""), nan(""));
			return var;
		}
		else
		{
			matrix var(rows, columns);
			if (power == 0) //identity Matrix
			{
				for (int m = 0; m < var.rows; m++)
				{
					for (int n = 0; n < var.columns; n++)
					{
						var.mat[m][n] = complex(0, 0);
					}
					var.mat[m][m] = complex(1, 0);
				}
				return var;
			}
			else if (power == 1)
				return (*this);
			else
			{
				matrix var(rows, columns);
				//matrix TempCopy;
				var = (*this);
				for (int Power = 0; Power < (power - 1); Power++) //Power Loop
					var = (*this)* var; //using *= causes stack overflow
				return var;
			}
		}
	}

	void matrix::deletem(void)
	{
		for (int i = 0; i < Size_r; i++)
			delete[]mat[i];
		delete[]mat;
	}

	matrix matrix::m_inverse()const //shorened version (less variables for use with division) //equivalent for the operator of inverse
	{
		matrix bigMat(rows, columns * 2);
		if (rows != columns) //not square
		{
			bigMat.set_dimentions(rows, columns);
			for (int m = 0; m < rows; m++)
				for (int n = 0; n < columns; n++)
					bigMat.mat[m][n] = complex(nan(""), nan(""));
			return bigMat;
		}
		else
		{
			//first putting the matrix next to I
			for (int m = 0; m < rows; m++)
			{
				for (int n = 0; n < columns * 2; n++)
				{
					if (n >= columns)
					{
						bigMat.mat[m][n] = complex(0, 0);
					}
					else
						bigMat.mat[m][n] = mat[m][n];
				}
				bigMat.mat[m][m + columns] = complex(1, 0);
			}


			//getting zeros under the diagonal
			vector_m temp1;
			complex one(1, 0), minus_one(-1, 0), diag_element;
			for (int diag = 0; (diag < rows - 1) && (diag < columns); diag++) //chooses the element of the diagonal that we're eliminating under
			{
				for (int u_diag = diag + 1; u_diag < rows; u_diag++) //under each diagonal element we'll eliminate
				{
					if (bigMat.mat[u_diag][diag] == complex(0, 0))
						continue;
					temp1 = bigMat.get_a_row(u_diag);
					if (bigMat.mat[diag][diag] == one)
						bigMat.set_a_row(u_diag, temp1 + (bigMat.get_a_row(diag)*(bigMat.mat[u_diag][diag] * minus_one)));
					else if (bigMat.mat[diag][diag] == minus_one)
						bigMat.set_a_row(u_diag, temp1 + (bigMat.get_a_row(diag)*bigMat.mat[u_diag][diag]));
					else if (bigMat.mat[diag][diag] == complex(0, 0))
					{
						for (int trans = u_diag; trans < bigMat.rows; trans++)
						{
							if (bigMat.mat[trans][diag] != complex(0, 0))
							{
								bigMat.swap_rows(diag, trans);
								bigMat.set_a_row(trans, bigMat.get_a_row(trans)*minus_one);
								u_diag--;
								break;
							}
						}
					}
					else
						bigMat.set_a_row(u_diag, temp1 + (bigMat.get_a_row(diag)*(one / bigMat.mat[diag][diag])*(bigMat.mat[u_diag][diag] * minus_one)));
				}
			}


			//check for zero rows
			for (int m = 0; m < rows; m++) //not invertible
			{
				if (bigMat.get_a_row(m).is_zero_vec_inverseSpecial(columns))
				{
					bigMat.set_dimentions(rows, columns);
					for (int m = 0; m < rows; m++)
						for (int n = 0; n < columns; n++)
							bigMat.mat[m][n] = complex(nan(""), nan(""));
					return bigMat;
				}
			}


			//making the diagonal of our matrix = ones
			for (int m = 0; m < bigMat.rows; m++)
				bigMat.set_a_row(m, bigMat.get_a_row(m)*(one / bigMat.mat[m][m]));


			//eliminating above the diagoanl
			for (int diag = rows - 1; diag >= 0; diag--) //chooses the element of the diagonal that we're eliminating under
			{
				for (int u_diag = diag - 1; u_diag >= 0; u_diag--) //under each diagonal element we'll eliminate
				{
					if (bigMat.mat[u_diag][diag] == complex(0, 0))
						continue;
					temp1 = bigMat.get_a_row(u_diag);
					bigMat.set_a_row(u_diag, temp1 + (bigMat.get_a_row(diag)*(bigMat.mat[u_diag][diag] * minus_one)));
				}
			}


			//returing the inverse 
			for (int m = 0; m < rows; m++)
				for (int n = 0; n < columns; n++)
					bigMat.mat[m][n] = bigMat.mat[m][n + columns];
			bigMat.set_dimentions(rows, columns); //use bigMat again to be returned (to avoid declaring new matrix)
		}
		return bigMat;
	}

	matrix matrix::m_transpose()const
	{
		matrix temp(columns, rows);
		for (int m = 0; m < rows; m++)
			for (int n = 0; n < columns; n++)
				temp.mat[n][m] = mat[m][n];
		return temp;
	}

	matrix matrix::m_eliminate()const
	{
		vector_m temp1;
		complex one(1, 0), minus_one(-1, 0), diag_element;
		matrix var = (*this);
		for (int diag = 0; (diag < var.rows - 1) && (diag < var.columns); diag++) //chooses the element of the diagonal that we're eliminating under
		{
			for (int u_diag = diag + 1; u_diag < var.rows; u_diag++) //under each diagonal element we'll eliminate
			{
				if (var.mat[u_diag][diag] == complex(0, 0))
					continue;
				temp1 = var.get_a_row(u_diag);
				if (var.mat[diag][diag] == complex(1, 0))
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(var.mat[u_diag][diag] * minus_one)));
				else if (var.mat[diag][diag] == complex(-1, 0))
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*var.mat[u_diag][diag]));
				else if (var.mat[diag][diag] == complex(0, 0))
				{
					for (int trans = u_diag; trans < var.rows; trans++)
					{
						if (var.mat[trans][diag] != complex(0, 0))
						{
							var.swap_rows(diag, trans);
							var.set_a_row(trans, var.get_a_row(trans)*minus_one);
							u_diag--;
							break;
						}
					}
				}
				else
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(one / (var.mat[diag][diag])*(var.mat[u_diag][diag] * minus_one))));
			}
		}
		return var;
	}

	int matrix::add(matrix first, matrix second)
	{
		if ((first.rows != second.rows) || (first.columns != second.columns))
		{
			cout << "Error!\nImproper Dimentions";// the two matrixes don't have the same dimentions
			return 1;
		}
		else
		{
			for (int row = 0; row < first.rows; row++)
				for (int column = 0; column < first.columns; column++)
					mat[row][column] = first.mat[row][column] + second.mat[row][column];
		}
		rows = first.rows; //this
		columns = first.columns;
		return 0;
	}

	int matrix::subtract(matrix first, matrix second)
	{
		if ((first.rows != second.rows) || (first.columns != second.columns))
		{
			cout << "Error!\nImproper Dimentions";// the two matrixes don't have the same dimentions
			return 1;
		}
		else
			for (int row = 0; row < first.rows; row++)
				for (int column = 0; column < first.columns; column++)
					mat[row][column] = first.mat[row][column] - second.mat[row][column];
		rows = first.rows;
		columns = first.columns;
		return 0;
	}

	int matrix::multiply(matrix first, matrix second)
	{
		if (first.get_rows() == 1 && first.get_columns() == 1) //if it's a scalar
		{
			for (int row = 0; row < second.rows; row++) //first input rows
				for (int column = 0; column < second.columns; column++) //second input columns
					second.mat[row][column] = first.mat[0][0] * second.mat[row][column];
			(*this) = second;
			return 0;
		}
		else if (second.get_rows() == 1 && second.get_columns() == 1) //if it's a scalar
		{
			for (int row = 0; row < first.rows; row++) //first input rows
				for (int column = 0; column < first.columns; column++) //second input columns
					first.mat[row][column] = first.mat[row][column] * second.mat[0][0];
			(*this) = first;
			return 0;
		}
		else if (first.columns != second.rows) //m*n,k*j ---> n=k , out [m,j]
		{
			cout << "Error!\nImproper Dimentions";
			return 1;// the two matrixes don't have proper dimentions
		}
		else
		{   // intialization with zeros
			for (int row = 0; row < first.rows; row++) //first input rows
				for (int column = 0; column < second.columns; column++) //second input columns
					mat[row][column] = complex(0, 0);
			for (int row = 0; row < first.rows; row++) //first input rows
				for (int column = 0; column < second.columns; column++) //second input columns
					for (int x = 0; x < first.columns; x++)
						mat[row][column] += (first.mat[row][x] * second.mat[x][column]);
		}
		rows = first.rows;
		columns = second.columns;
		return 0;
	}

	int matrix::transpose(matrix var)
	{
		for (int m = 0; m < var.rows; m++)
			for (int n = 0; n < var.columns; n++)
				mat[n][m] = var.mat[m][n];
		rows = var.columns;
		columns = var.rows;
		return 0;
	}

	int matrix::power(matrix var, string pow1)
	{
		for (int i = 0; i < pow1.size(); i++)
		{
			switch (pow1[i])
			{
			case'0':
			case'1':
			case'2':
			case'3':
			case'4':
			case'5':
			case'6':
			case'7':
			case'8':
			case'9':
				break;
			default:
				cout << "Error!\nThe Power Is Not a Positive Intger"; //power is not an integer Or is not +ve
				return 1;
			}
		}
		float pow = atof(pow1.c_str());
		if (var.columns != var.rows) //m*n,k*j ---> n=k , out [m,j]
		{
			cout << "Error!\nImproper Dimentions";
			return 1;// not a square matrix
		}
		else
		{
			if (pow == 0) //identity Matrix
			{
				for (int m = 0; m < var.rows; m++)
				{
					for (int n = 0; n < var.columns; n++)
					{
						mat[m][n] = complex(0, 0);
					}
					mat[m][m] = complex(1, 0);
				}
				rows = var.rows;
				columns = var.columns;
			}
			else if (pow == 1)
				for (int m = 0; m < var.rows; m++)
					for (int n = 0; n < var.columns; n++)
						(*this) = var;
			else
			{
				//matrix TempCopy;
				(*this) = var;
				for (int Power = 0; Power < (pow - 1); Power++) //Power Loop
					(*this) = (*this)* var; //using *= causes stack overflow
			}
		}
		rows = var.rows;
		columns = var.columns;
		return 0;
	}

	complex matrix::determinant(bool &state)const //still there's a bug when trying to s swap 
	{
		state = 0; 
		if (columns != rows)
		{
			cout << "Error!\nNot a Square matrix!"; // Not a square matrix
			state = 1;
			return mat[0][0]; //null value won't be used
		}
		else
		{
			matrix temp = (*this);
			vector_m temp1;
			complex one(1, 0), minus_one(-1, 0), diag_element;
			for (int diag = 0; diag < temp.rows - 1; diag++) //chooses the element of the diagonal that we're eliminating under
			{
				for (int u_diag = diag + 1; u_diag < temp.rows; u_diag++) //under each diagonal element we'll eliminate
				{
					if (temp.mat[u_diag][diag] == complex(0, 0))
						continue;
					temp1 = temp.get_a_row(u_diag);
					if (temp.mat[diag][diag] == one)
						temp.set_a_row(u_diag, temp1 + (temp.get_a_row(diag)*(temp.mat[u_diag][diag] * minus_one)));
					else if (temp.mat[diag][diag] == minus_one)
						temp.set_a_row(u_diag, temp1 + (temp.get_a_row(diag)*temp.mat[u_diag][diag]));
					else if (temp.mat[diag][diag] == complex(0, 0))
					{
						for (int trans = u_diag; trans < temp.rows; trans++)
						{
							if (temp.mat[trans][diag] != complex(0, 0))
							{
								temp.swap_rows(diag, trans);
								temp.set_a_row(trans, temp.get_a_row(trans)*minus_one);
								u_diag--;
								break;
							}
							else
							{
								if (trans == temp.rows - 1)
								{
									diag_element = complex(0, 0);
									return diag_element;
								}
							}
						}
					}
					else
						temp.set_a_row(u_diag, temp1 + (temp.get_a_row(diag)*(one / temp.mat[diag][diag])*(temp.mat[u_diag][diag] * (minus_one))));
				}
			}
			return temp.multiply_diagonal_elements();
		}
	}

	complex matrix::determinant()const //still there's a bug when trying to s swap //no cout but returns nan (can't substitute the private one)
	{
		if (columns != rows)
			// Not a square matrix
			return complex(nanf(""), nanf("")); //null value won't be used
		else
		{
			matrix temp = (*this);
			vector_m temp1;
			complex one(1, 0), minus_one(-1, 0), diag_element;
			for (int diag = 0; diag < temp.rows - 1; diag++) //chooses the element of the diagonal that we're eliminating under
			{
				for (int u_diag = diag + 1; u_diag < temp.rows; u_diag++) //under each diagonal element we'll eliminate
				{
					if (temp.mat[u_diag][diag] == complex(0, 0))
						continue;
					temp1 = temp.get_a_row(u_diag);
					if (temp.mat[diag][diag] == one)
						temp.set_a_row(u_diag, temp1 + (temp.get_a_row(diag)*(temp.mat[u_diag][diag] * minus_one)));
					else if (temp.mat[diag][diag] == minus_one)
						temp.set_a_row(u_diag, temp1 + (temp.get_a_row(diag)*temp.mat[u_diag][diag]));
					else if (temp.mat[diag][diag] == complex(0, 0))
					{
						for (int trans = u_diag; trans < temp.rows; trans++)
						{
							if (temp.mat[trans][diag] != complex(0, 0))
							{
								temp.swap_rows(diag, trans);
								temp.set_a_row(trans, temp.get_a_row(trans)*minus_one);
								u_diag--;
								break;
							}
							else
							{
								if (trans == temp.rows - 1)
								{
									diag_element = complex(0, 0);
									return diag_element;
								}
							}
						}
					}
					else
						temp.set_a_row(u_diag, temp1 + (temp.get_a_row(diag)*(one / temp.mat[diag][diag])*(temp.mat[u_diag][diag] * (minus_one))));
				}
			}
			return temp.multiply_diagonal_elements();
		}
	}

	vector_m matrix::cramer(matrix ans_column, bool &state)
	{
		state = false;
		if (ans_column.rows != rows)
		{
			state = true;
			cout << "Error!\nAnswer-Column Does Not Meet no. Of Equations";
			return ans_column.get_a_column(0);
		}
		else if (rows < columns)
		{
			state = true;
			cout << "Error!\nNot Enough Equations";
			return ans_column.get_a_column(0);
		}
		else if (rows > columns)
		{
			state = true;
			cout << "Error!\nRemove " << rows - columns << " Of The Equations";
			return ans_column.get_a_column(0);
		}
		else
		{
			complex delta, delta_i;
			delta = determinant();
			if (delta == complex(0, 0))
			{
				state = true;
				cout << "Error!\nCoefficient Matrix Equals Zero";
				return ans_column.get_a_column(0);
			}
			vector_m unknowns(columns), temp_column;
			for (int i = 0; i < rows; i++)
			{
				temp_column = get_a_column(i);
				set_a_column(i, ans_column);
				delta_i = determinant();
				unknowns.set_element(i, delta_i / delta);
				set_a_column(i, temp_column);
			}
			return unknowns;
		}
	}

	vector_m matrix::cramer(matrix ans_column)
	{
		vector_m ans;
		ans = ans_column.get_a_column(0);
		if (ans_column.rows != rows || rows != columns)
		{
			ans.set_element(0, complex(nanf(""), nanf("")));
			return ans;
		}
		else
		{
			complex delta, delta_i;
			delta = determinant();
			if (delta == complex(0, 0))
			{
				ans.set_element(0, complex(nanf(""), nanf("")));
				return ans;
			}
			vector_m unknowns(rows), temp_column;
			for (int i = 0; i < rows; i++)
			{
				temp_column = get_a_column(i);
				set_a_column(i, ans_column);
				delta_i = determinant();
				unknowns.set_element(i, delta_i / delta);
				set_a_column(i, temp_column);
			}
			return unknowns;
		}
	}

	int matrix::eliminate(matrix var)
	{ //change elimination to be the method of inversing [1 0 0;0 1 0;0 0 1] 
		vector_m temp1;
		complex one(1, 0), minus_one(-1, 0), diag_element;
		for (int diag = 0; (diag < var.rows - 1) && (diag < var.columns); diag++) //chooses the element of the diagonal that we're eliminating under
		{
			for (int u_diag = diag + 1; u_diag < var.rows; u_diag++) //under each diagonal element we'll eliminate
			{
				if (var.mat[u_diag][diag] == complex(0, 0))
					continue;
				temp1 = var.get_a_row(u_diag);
				if (var.mat[diag][diag] == complex(1, 0))
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(var.mat[u_diag][diag] * minus_one)));
				else if (var.mat[diag][diag] == complex(-1, 0))
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*var.mat[u_diag][diag]));
				else if (var.mat[diag][diag] == complex(0, 0))
				{
					for (int trans = u_diag; trans < var.rows; trans++)
					{
						if (var.mat[trans][diag] != complex(0, 0))
						{
							var.swap_rows(diag, trans);
							var.set_a_row(trans, var.get_a_row(trans)*minus_one);
							u_diag--;
							break;
						}
					}
				}
				else
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(one / (var.mat[diag][diag])*(var.mat[u_diag][diag] * minus_one))));
			}
		}
		(*this) = var;
		return 0;
	}

	int matrix::eliminate_d(matrix var)
	{
		cout << endl;
		vector_m temp1;
		complex one(1, 0), minus_one(-1, 0), diag_element, factor0;
		for (int diag = 0, step = 1; (diag < var.rows - 1) && (diag < var.columns); diag++) //chooses the element of the diagonal that we're eliminating under
		{
			for (int u_diag = diag + 1; u_diag < var.rows; u_diag++, step++) //under each diagonal element we'll eliminate
			{
				if (var.mat[u_diag][diag] == complex(0, 0))
				{
					step--;
					continue;
				}

				cout << "Step " << step << ":" << endl;
				temp1 = var.get_a_row(u_diag);
				if (!(var.mat[diag][diag] == complex(0, 0)))
					factor0 = (one / var.mat[diag][diag])*(var.mat[u_diag][diag] * minus_one);

				if (var.mat[diag][diag] == one)
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(var.mat[u_diag][diag] * minus_one)));
				else if (var.mat[diag][diag] == minus_one)
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*var.mat[u_diag][diag]));
				else if (var.mat[diag][diag] == complex(0, 0))
				{
					for (int trans = u_diag; trans < var.rows; trans++)
					{
						if (var.mat[trans][diag] != complex(0, 0))
						{
							var.swap_rows(diag, trans);
							var.set_a_row(trans, var.get_a_row(trans)*minus_one);
							cout << "Swap Row " << diag + 1 << " With Row " << trans + 1 << " , Then Row " << trans + 1 << " * -1" << endl;
							var.print();
							cout << endl << endl;
							u_diag--;
							break;
						}
					}
					continue;
				}
				else
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(one / var.mat[diag][diag])*(var.mat[u_diag][diag] * minus_one)));
				cout << "Row " << diag + 1 << " * (";
				factor0.print();
				cout << ") + Row " << u_diag + 1 << endl;
				var.print();
				cout << endl << endl;
			}
		}
		((*this) = var);
		return 0;
	}

	int matrix::rank(void)
	{
		vector_m temp1;
		complex one(1, 0), minus_one(-1, 0), diag_element;
		int zeroVectors;
		for (int diag = 0; (diag < rows - 1) && (diag < columns); diag++) //chooses the element of the diagonal that we're eliminating under
		{
			for (int u_diag = diag + 1; u_diag < rows; u_diag++) //under each diagonal element we'll eliminate
			{
				if (mat[u_diag][diag] == complex(0, 0))
					continue;
				temp1 = get_a_row(u_diag);
				if (mat[diag][diag] == one)
					set_a_row(u_diag, temp1 + (get_a_row(diag)*mat[u_diag][diag] * minus_one));
				else if (mat[diag][diag] == minus_one)
					set_a_row(u_diag, temp1 + (get_a_row(diag)*mat[u_diag][diag]));
				else if (mat[diag][diag] == complex(0, 0))
				{
					for (int trans = u_diag; trans < rows; trans++)
					{
						if (mat[trans][diag] != complex(0, 0)) //swap with the first row that does not have zero in the same place
						{
							swap_rows(diag, trans);
							set_a_row(trans, get_a_row(trans)*minus_one);
							u_diag--;
							break;
						}
					}
				}
				else
					set_a_row(u_diag, temp1 + (get_a_row(diag)*(one / mat[diag][diag])*(mat[u_diag][diag] * minus_one)));
			}
		}
		return rows - (*this).no_of_zero_vectors();
	}

	int matrix::rank_d(void)
	{
		cout << endl;
		vector_m temp1;
		complex one(1, 0), minus_one(-1, 0), diag_element, factor0;
		for (int diag = 0, step = 1; (diag < rows - 1) && (diag < columns); diag++) //chooses the element of the diagonal that we're eliminating under
		{
			for (int u_diag = diag + 1; u_diag < rows; u_diag++, step++) //under each diagonal element we'll eliminate
			{
				if (mat[u_diag][diag] == complex(0, 0))
				{
					step--;
					continue;
				}

				cout << "Step " << step << ":" << endl;
				temp1 = get_a_row(u_diag);
				if (mat[diag][diag] != complex(0, 0))
					factor0 = (one / mat[diag][diag])*(mat[u_diag][diag] * minus_one);

				if (mat[diag][diag] == one)
					set_a_row(u_diag, temp1 + (get_a_row(diag)*(mat[u_diag][diag] * minus_one)));
				else if (mat[diag][diag] == minus_one)
					set_a_row(u_diag, temp1 + (get_a_row(diag)*mat[u_diag][diag]));
				else if (mat[diag][diag] == complex(0, 0))
				{
					for (int trans = u_diag; trans < rows; trans++)
					{
						if (mat[trans][diag] != complex(0, 0))
						{
							swap_rows(diag, trans);
							set_a_row(trans, get_a_row(trans)*minus_one);
							cout << "Swap Row " << diag + 1 << " With Row " << trans + 1 << " , Then Row " << trans + 1 << " * -1" << endl;
							print();
							cout << endl << endl;
							u_diag--;
							break;
						}
					}
					continue;
				}
				else
					set_a_row(u_diag, temp1 + (get_a_row(diag)*(one / mat[diag][diag])*(mat[u_diag][diag] * minus_one)));
				cout << "Row " << diag + 1 << " * (";
				factor0.print();
				cout << ") + Row " << u_diag + 1 << endl;
				print();
				cout << endl << endl;
			}
		}
		return rows - (*this).no_of_zero_vectors();
	}

	int matrix::inverse(matrix var) //better in the bigger matrixes but alittle bit worse (not always) in the small ones
	{
		if (var.rows != var.columns)
		{
			cout << "Error!\nNot a Square matrix";// Not a square matrix
			return 1;
		}
		else
		{

			//first putting the matrix next to I *(we'll use var instead of bigMat to avoid stack overflow)*
			for (int m = 0; m < var.rows; m++)
			{
				for (int n = 0; n < var.columns * 2; n++)
					if (n >= var.columns)
						var.mat[m][n] = complex(0, 0);
				var.mat[m][m + var.columns] = complex(1, 0);
			}

			rows = var.rows;
			columns = var.columns;
			var.columns = 2 * var.columns;

			//getting zeros under the diagonal
			vector_m temp1;
			complex one(1, 0), minus_one(-1, 0), diag_element;
			for (int diag = 0; (diag < rows - 1) && (diag < columns); diag++) //chooses the element of the diagonal that we're eliminating under
			{
				for (int u_diag = diag + 1; u_diag < rows; u_diag++) //under each diagonal element we'll eliminate
				{
					if (var.mat[u_diag][diag] == complex(0, 0))
						continue;
					temp1 = var.get_a_row(u_diag);
					if (var.mat[diag][diag] == one)
						var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(var.mat[u_diag][diag] * minus_one)));
					else if (var.mat[diag][diag] == minus_one)
						var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*var.mat[u_diag][diag]));
					else if (var.mat[diag][diag] == complex(0, 0))
					{
						for (int trans = u_diag; trans < rows; trans++)
						{
							if (var.mat[trans][diag] != complex(0, 0))
							{
								var.swap_rows(diag, trans);
								var.set_a_row(trans, var.get_a_row(trans)*minus_one);
								u_diag--;
								break;
							}
						}
					}
					else
						var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(one / var.mat[diag][diag])*(var.mat[u_diag][diag] * minus_one)));
				}
			}


			//check for zero rows
			for (int m = 0; m < rows; m++)
			{
				if (var.get_a_row(m).is_zero_vec_inverseSpecial(columns))
				{
					cout << "Error!\nMatrix is not invertible";
					return 1;
				}
			}


			//making the diagonal of our matrix = ones
			for (int m = 0; m < rows; m++)
				var.set_a_row(m, var.get_a_row(m)*(one / var.mat[m][m]));


			//eliminating above the diagoanl
			for (int diag = rows - 1; diag >= 0; diag--) //chooses the element of the diagonal that we're eliminating under
			{
				for (int u_diag = diag - 1; u_diag >= 0; u_diag--) //under each diagonal element we'll eliminate
				{
					if (var.mat[u_diag][diag] == complex(0, 0))
						continue;
					temp1 = var.get_a_row(u_diag);
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(var.mat[u_diag][diag] * minus_one)));
				}
			}


			//returing the inverse 
			for (int m = 0; m < rows; m++)
				for (int n = 0; n < columns; n++)
					mat[m][n] = var.mat[m][n + columns];
		}
		return 0;
	}

	int matrix::inverse_d(matrix var) //better in the bigger matrixes but alittle bit worse (not always) in the small ones
	{
		if (var.rows != var.columns)
		{
			cout << "Error!\nNot a Square matrix";// Not a square matrix
			return 1;
		}
		else
		{

			//first putting the matrix next to I *(we'll use var instead of bigMat to avoid stack overflow)*
			for (int m = 0; m < var.rows; m++)
			{
				for (int n = 0; n < var.columns * 2; n++)
					if (n >= var.columns)
						var.mat[m][n] = complex(0, 0);
				var.mat[m][m + var.columns] = complex(1, 0);
			}

			rows = var.rows;
			columns = var.columns;
			var.columns = 2 * var.columns;

			//getting zeros under the diagonal
			vector_m temp1;
			complex one(1, 0), minus_one(-1, 0), diag_element;
			for (int diag = 0; (diag < rows - 1) && (diag < columns); diag++) //chooses the element of the diagonal that we're eliminating under
			{
				for (int u_diag = diag + 1; u_diag < rows; u_diag++) //under each diagonal element we'll eliminate
				{
					if (var.mat[u_diag][diag] == complex(0, 0))
						continue;
					temp1 = var.get_a_row(u_diag);
					if (var.mat[diag][diag] == one)
						var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(var.mat[u_diag][diag] * minus_one)));
					else if (var.mat[diag][diag] == minus_one)
						var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*var.mat[u_diag][diag]));
					else if (var.mat[diag][diag] == complex(0, 0))
					{
						for (int trans = u_diag; trans < rows; trans++)
						{
							if (var.mat[trans][diag] != complex(0, 0))
							{
								var.swap_rows(diag, trans);
								var.set_a_row(trans, var.get_a_row(trans)*minus_one);
								u_diag--;
								break;
							}
						}
					}
					else
						var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(one / var.mat[diag][diag])*(var.mat[u_diag][diag] * minus_one)));
				}
			}


			//check for zero rows
			for (int m = 0; m < rows; m++)
			{
				if (var.get_a_row(m).is_zero_vec_inverseSpecial(columns))
				{
					cout << "Error!\nMatrix is not invertible";
					return 1;
				}
			}


			//making the diagonal of our matrix = ones
			for (int m = 0; m < rows; m++)
				var.set_a_row(m, var.get_a_row(m)*(one / var.mat[m][m]));


			//eliminating above the diagoanl
			for (int diag = rows - 1; diag >= 0; diag--) //chooses the element of the diagonal that we're eliminating under
			{
				for (int u_diag = diag - 1; u_diag >= 0; u_diag--) //under each diagonal element we'll eliminate
				{
					if (var.mat[u_diag][diag] == complex(0, 0))
						continue;
					temp1 = var.get_a_row(u_diag);
					var.set_a_row(u_diag, temp1 + (var.get_a_row(diag)*(var.mat[u_diag][diag] * minus_one)));
				}
			}


			//returing the inverse 
			for (int m = 0; m < rows; m++)
				for (int n = 0; n < columns; n++)
					mat[m][n] = var.mat[m][n + columns];
		}
	}

	int matrix::Old_inverse(matrix var) // better in the small matrixes
	{
		if (var.columns != var.rows)
		{
			cout << "Error!\nNot a Square matrix";// Not a square matrix
			return 1;
		}
		else if (var.rows == 1)
		{
			if (var.mat[0][0] == complex(0, 0))
			{
				cout << "Error!\nCan Not Divide By 0"; //we need 1/element & element=0
				return 1;
			}
			else
			{
				complex temp;
				temp = complex(1, 0);
				mat[0][0] = temp / var.mat[0][0];
			}
		}
		else if (var.rows == 2)
		{
			complex det;
			det = var.determinant();
			if (det == complex(0, 0))
			{
				cout << "Error!\nCan Not Divide By 0"; //we need 1/element & element=0
				return 1;
			}
			else
			{
				complex temp(1, 0);
				complex det_1 = temp / det;
				temp = complex(-1, 0);
				mat[0][0] = det_1*var.mat[1][1];
				mat[0][1] = temp*(det_1*var.mat[0][1]);
				mat[1][0] = temp*(det_1*var.mat[1][0]);
				mat[1][1] = det_1*var.mat[0][0];
			}
		}
		else
		{
			complex det;
			det = var.determinant();
			if (det == complex(0, 0))
			{
				cout << "Error!\nCan Not Divide By 0"; //we need 1/element & element=0
				return 1;
			}
			complex temp(1, 0);
			complex det_1 = temp / det;
			for (int m = 0; m < var.rows; m++)
				for (int n = 0; n < var.columns; n++)
					mat[n][m] = det_1*var.matrix_of_coFactors(m, n);
		}
		rows = var.rows;
		columns = var.columns;
		return 0;
	}

	int matrix::divide(matrix first, matrix second)
	{
		if (second.get_rows() == 1 && second.get_columns() == 1) //if it's a scalar
		{
			for (int row = 0; row < first.rows; row++) //first input rows
				for (int column = 0; column < first.columns; column++) //second input columns
					first.mat[row][column] = first.mat[row][column] / second.mat[0][0];
			(*this) = first;
			return 0;
		}
		//we'll give the imaginaries to this function just to use in the multiply function as matrixes full of zeros instead of defining and intializing 3 new matrixes
		else if (first.columns != second.rows || second.columns != second.rows) //m*n,k*j ---> n=k , out [m,j]
		{
			cout << "Error!\nImproper Dimentions";
			return 1;// the two matrixes don't have proper dimentions
		}
		else
		{
			matrix tempInverse;

			//reusing the inverse code to avoid stack overflow
			if (second.rows != second.columns)
			{
				cout << "Error!\nNot a Square matrix";// Not a square matrix
				return 1;
			}
			else
			{

				//first putting the matrix next to I *(we'll use var instead of bigMat to avoid stack overflow)*
				for (int m = 0; m < second.rows; m++)
				{
					for (int n = 0; n < second.columns * 2; n++)
						if (n >= second.columns)
							second.mat[m][n] = complex(0, 0);
					second.mat[m][m + second.columns] = complex(1, 0);
				}

				tempInverse.rows = second.rows;
				tempInverse.columns = second.columns;
				second.columns = 2 * second.columns;

				//getting zeros under the diagonal
				vector_m temp1;
				complex one(1, 0), minus_one(-1, 0), diag_element;
				for (int diag = 0; (diag < tempInverse.rows - 1) && (diag < tempInverse.columns); diag++) //chooses the element of the diagonal that we're eliminating under
				{
					for (int u_diag = diag + 1; u_diag < tempInverse.rows; u_diag++) //under each diagonal element we'll eliminate
					{
						if (second.mat[u_diag][diag] == complex(0, 0))
							continue;
						temp1 = second.get_a_row(u_diag);
						if (second.mat[diag][diag] == one)
							second.set_a_row(u_diag, temp1 + (second.get_a_row(diag)*(second.mat[u_diag][diag] * minus_one)));
						else if (second.mat[diag][diag] == minus_one)
							second.set_a_row(u_diag, temp1 + (second.get_a_row(diag)*second.mat[u_diag][diag]));
						else if (second.mat[diag][diag] == complex(0, 0))
						{
							for (int trans = u_diag; trans < tempInverse.rows; trans++)
							{
								if (second.mat[trans][diag] != complex(0, 0))
								{
									second.swap_rows(diag, trans);
									second.set_a_row(trans, second.get_a_row(trans)*minus_one);
									u_diag--;
									break;
								}
							}
						}
						else
							second.set_a_row(u_diag, temp1 + (second.get_a_row(diag)*(one / second.mat[diag][diag])*(second.mat[u_diag][diag] * minus_one)));
					}
				}


				//check for zero rows
				for (int m = 0; m < tempInverse.rows; m++)
				{
					if (second.get_a_row(m).is_zero_vec_inverseSpecial(tempInverse.columns))
					{
						cout << "Error!\nMatrix is not invertible";
						return 1;
					}
				}


				//making the diagonal of our matrix = ones
				for (int m = 0; m < tempInverse.rows; m++)
					second.set_a_row(m, second.get_a_row(m)*(one / second.mat[m][m]));


				//eliminating above the diagoanl
				for (int diag = tempInverse.rows - 1; diag >= 0; diag--) //chooses the element of the diagonal that we're eliminating under
				{
					for (int u_diag = diag - 1; u_diag >= 0; u_diag--) //under each diagonal element we'll eliminate
					{
						if (second.mat[u_diag][diag] == complex(0, 0))
							continue;
						temp1 = second.get_a_row(u_diag);
						second.set_a_row(u_diag, temp1 + (second.get_a_row(diag)*(second.mat[u_diag][diag] * minus_one)));
					}
				}


				//returing the inverse 
				for (int m = 0; m < tempInverse.rows; m++)
					for (int n = 0; n < tempInverse.columns; n++)
						tempInverse.mat[m][n] = second.mat[m][n + tempInverse.columns];
			}


			//using the multiplication code to avoid stack overflow
			(*this).set_dimentions(first.rows, tempInverse.columns);

			for (int row = 0; row < rows; row++) //first input rows
				for (int column = 0; column < columns; column++) //second input columns
					mat[row][column] = complex(0, 0);

			for (int row = 0; row < first.rows; row++) //first input rows
				for (int column = 0; column < tempInverse.columns; column++) //second input columns
					for (int x = 0; x < first.columns; x++)
						mat[row][column] += (first.mat[row][x] * tempInverse.mat[x][column]);

			return 0;
		}
	}

	int matrix::fill(string input) //check more on the generaltemp cause that's what you directly take from the user and also enhance the algorizm of filling  like when it's j2+2 or 2+j2
	{
		int i = 1, j = 1, k = 0; //i=digits , j=elements , k=(rows-1)  for the entire input string  k+1=j/numberOfElementsInLastRow
		int numberOfElementsInLastRow = 0, numberOfElementsInThisRow = 0, signs = 0, noOfJs = 0; //numberOfElementsInLastRow is columns no.
		bool has_j_ = false;
		string generalTemp, realTemp, imgTemp, orderOf2signs; //holds the elements or parts of the elements
		if (input == "ans"/* || input == "Ans" || input == "ans." || input == "Ans." || input == "answer" || input == "Answer" || input == "ANSWER"*/)
			return 2; //to assign the values in matC to matA
		else if (input == "rand"/* || input == "Rand" || input == "rand." || input == "Rand." || input == "random" || input == "Random" || input == "RANDOM"*/)
			return 3; //to assign the values in matC to matA
		else if (/*input == "Qrand" || input == "Qrand" || input == "Qrand." || input == "QRand." || input == "Qrandom" || input == "QRandom" || input == "QRANDOM" || */input == "qrand" /*|| input == "qrand." || input == "qRand." || input == "qrandom" || input == "qRandom" || input == "qRANDOM"*/)
			return 4; //to assign the values in matC to matA
		else if (/*input == "Prand" || input == "Prand" || input == "Prand." || input == "PRand." || input == "Prandom" || input == "PRandom" || input == "PRANDOM" || */input == "prand" /*|| input == "prand." || input == "pRand." || input == "prandom" || input == "pRandom" || input == "pRANDOM"*/)
			return 6;
		else if (/*input == "Srand" || input == "Srand" || input == "Srand." || input == "SRand." || input == "Srandom" || input == "SRandom" || input == "SRANDOM" || */input == "srand" /*|| input == "srand." || input == "sRand." || input == "srandom" || input == "sRandom" || input == "sRANDOM"*/)
			return 7;
		else if (input[0] != '[' || input[((input.size()) - 1)] != ']')
		{
			cout << "Error!\nCouldn't find the beginning/end of the matrix!";
			return 1;
		}
		else
		{
			while (j <= 10000 && i != (input.size())) //elements loop
			{
				numberOfElementsInThisRow++;
				while (i < (input.size())) // [(2*n*m)+1] is the max no. of elements if they're all +ve int.s < 0 //digits loop
				{                                // This while loop generates s string with value something like that --> 5.5+2i
					if (input[i] == ' ')
					{
						if (i == 1)
						{
							cout << "Error!\nWrong input .. didn't start with a number";
							return 1;
						}
						i++;
						break;
					}
					else if (input[i] == ';' || input[i] == ']')
					{
						if (k == 0) //at the first row	(first loop) setting colomn no.
							numberOfElementsInLastRow = numberOfElementsInThisRow;
						else
						{
							if (numberOfElementsInLastRow != numberOfElementsInThisRow)
							{
								printf("Error!\nWrong input .. Row no. %d does not have the same no. of elements as the 1st row", k + 1);
								return 1; //two rows with different columns in the same matrix
							}
							else if (k > Size_r - 1)
							{
								printf("Error!\nWrong input .. no. of rows exceeded %d", Size_r);
								return 1; //no. of rows exceeded 100
							}
							else if (numberOfElementsInThisRow > Size_c)
							{
								printf("Error!\nWrong input .. no. of columns exceeded %d", Size_c);
								return 1; //no. of columns exceeded 100
							}
						}
						i++;
						break;
					}
					else
						generalTemp += input[i];
					i++;
				}

				/*general temp is full with one element real+imaginary ... time for separating the real and the imaginary parts*/

				for (int m = 0; m < generalTemp.size(); m++) //must be written right error handeling is down with the conversion
				{
					if (generalTemp[m] == 'j' || generalTemp[m] == 'J' || generalTemp[m] == 'i' || generalTemp[m] == 'I')
					{
						noOfJs++;
						orderOf2signs += 'j';  //we considerd any sqrt(-1) as a 'j', just for easness of checking the order down
					}
					else if (generalTemp[m] == '-' || generalTemp[m] == '+')
					{
						signs++;
						orderOf2signs += '+'; //we considerd any sign as a '+', just for easness of checking the order down
					}
				} // after that last loop we have how many signs are in the generalTemp , how many sqrt(-1)'s and the order they're written in
				if (noOfJs > 1 || signs > 2)
				{
					cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
					return 1; //the element has more than 2 signs(+,-) Or more than 1 sqrt(-1)
				}
				else if (noOfJs == 1)
					has_j_ = true;
				if (has_j_) //Note: that the form j2+1 & 1+j2 are not allowed it has to be 2j
				{
					if (signs == 2)
					{
						if (orderOf2signs == "++j") //real first
						{
							int x = 0;
							for (x = 0; x < generalTemp.size(); x++) //filling realTemp
							{
								if (x == 0)
									realTemp += generalTemp[x];
								else
								{
									if (generalTemp[x] == '+' || generalTemp[x] == '-')
									{
										break;
									}
									else
										realTemp += generalTemp[x];
								}
							} //done filling real part
							for (x = x; x < generalTemp.size(); x++) //filling imgTemp
							{
								imgTemp += generalTemp[x];
							} //done filling imaginary part
						}

						else if (orderOf2signs == "+j+") //imaginary first
						{
							int x = 0;
							for (x = 0; x < generalTemp.size(); x++) //filling imgTemp
							{
								if (x == 0)
									imgTemp += generalTemp[x];
								else
								{
									if (generalTemp[x] == '+' || generalTemp[x] == '-')
									{
										break;
									}
									else
										imgTemp += generalTemp[x];
								}
							} //done filling imaginary part
							for (x = x; x < generalTemp.size(); x++) //filling realTemp
							{
								realTemp += generalTemp[x];
							} //done filling real part					
						}
						else
						{
							cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
							return 1; //the order of the two signs and the sqrt(-1) is neither +j+ nor ++j ---> +j+1 nor +1+j
						}
					}
					else if (signs == 1)
					{
						if (generalTemp[0] == '+' || generalTemp[0] == '-')
						{
							for (int x = 0; x < generalTemp.size(); x++)
							{
								imgTemp += generalTemp[x];
							}
						}
						else
						{
							if (orderOf2signs == "+j") //real first
							{
								int x = 0;
								for (x = 0; x < generalTemp.size(); x++) //filling realTemp
								{
									if (x == 0)
										realTemp += generalTemp[x];
									else
									{
										if (generalTemp[x] == '+' || generalTemp[x] == '-')
										{
											break;
										}
										else
											realTemp += generalTemp[x];
									}
								} //done filling real part
								for (x = x; x < generalTemp.size(); x++) //filling imgTemp
								{
									imgTemp += generalTemp[x];
								} //done filling imaginary part
							}

							else if (orderOf2signs == "j+") //imaginary first
							{
								int x = 0;
								for (x = 0; x < generalTemp.size(); x++) //filling imgTemp
								{
									if (x == 0)
										imgTemp += generalTemp[x];
									else
									{
										if (generalTemp[x] == '+' || generalTemp[x] == '-')
										{
											break;
										}
										else
											imgTemp += generalTemp[x];
									}
								} //done filling imaginary part
								for (x = x; x < generalTemp.size(); x++) //filling realTemp
								{
									realTemp += generalTemp[x];
								} //done filling real part					
							}
							else
							{
								cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
								return 1; //the order of the one sign and the sqrt(-1) is neither j+ nor +j ---> j+1 nor 1+j
							}
						}
					}

					else //must be pure imaginary
					{
						for (int x = 0; x < generalTemp.size(); x++)
						{
							imgTemp += generalTemp[x];
						}
					}
				}
				else //must be pure real
				{
					for (int x = 0; x < generalTemp.size(); x++)
					{
						realTemp += generalTemp[x];
					}
				}

				/*the real part is separated in realTemp so is the imaginary ... time for filling the matrixes*/

				if (imgTemp == "+j" || imgTemp == "+J" || imgTemp == "-j" || imgTemp == "-J" || imgTemp == "+i" || imgTemp == "+I" || imgTemp == "-i" || imgTemp == "-I")
					imgTemp.insert(1, "1");
				else if (imgTemp == "j" || imgTemp == "J" || imgTemp == "i" || imgTemp == "I")
					imgTemp.insert(0, "1");

				/*ERROR Checking + Filling*/

				if (realTemp[0] == '+' || realTemp[0] == '-')
				{
					int dots = 0;
					for (int b = 1; b < realTemp.size(); b++)
					{
						if (realTemp == "")
							break;
						else if (realTemp[b] == '.')
							dots++;
						switch (realTemp[b])
						{
						case'0':
						case'1':
						case'2':
						case'3':
						case'4':
						case'5':
						case'6':
						case'7':
						case'8':
						case'9':
						case'.':
							break;
						default:
							cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
							return 1; //unkown character
						}
					}
					if (dots > 1)
					{
						cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
						return 1; //unkown character
					}
				}
				else
				{
					int dots = 0;
					for (int b = 0; b < realTemp.size(); b++)
					{
						if (realTemp == "")
							break;
						else if (realTemp[b] == '.')
							dots++;
						switch (realTemp[b])
						{
						case'0':
						case'1':
						case'2':
						case'3':
						case'4':
						case'5':
						case'6':
						case'7':
						case'8':
						case'9':
						case'.':
							break;
						default:
							cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
							return 1; //unkown character
						}
					}
					if (dots > 1)
					{
						cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
						return 1; //unkown character
					}
				}


				if (orderOf2signs == "++j" || orderOf2signs == "+j" || orderOf2signs == "+j+")
				{
					int dots = 0;
					for (int b = 1; b < imgTemp.size() - 1; b++)
					{
						if (imgTemp == "")
							break;
						else if (imgTemp[b] == '.')
							dots++;
						switch (imgTemp[b])
						{
						case'0':
						case'1':
						case'2':
						case'3':
						case'4':
						case'5':
						case'6':
						case'7':
						case'8':
						case'9':
						case'.':
							break;
						default:
							cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
							return 1; //unkown character
						}
					}
					if (dots > 1)
					{
						cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
						return 1; //unkown character
					}
				}
				else if (orderOf2signs == "j+")
				{
					int dots = 0;
					for (int b = 0; b < imgTemp.size() - 1; b++)
					{
						if (imgTemp == "")
							break;
						else if (imgTemp[b] == '.')
							dots++;
						switch (imgTemp[b])
						{
						case'0':
						case'1':
						case'2':
						case'3':
						case'4':
						case'5':
						case'6':
						case'7':
						case'8':
						case'9':
						case'.':
							break;
						default:
							cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
							return 1; //unkown character
						}
					}
					if (dots > 1)
					{
						cout << "Error!\nWrong input .. Unknown Characters In The Row No. " << k + 1 << ", Column No. " << numberOfElementsInThisRow;
						return 1; //unkown character
					}
				}


				if (realTemp == "0" || realTemp == "-0")
					mat[k][numberOfElementsInThisRow - 1].set_real(0);
					//mat[k].push_back(complex(0, 0)); //push back is better cause it resizes
				else
					mat[k][numberOfElementsInThisRow - 1].set_real(atof(realTemp.c_str()));
					//mat[k].push_back(complex(atof(realTemp.c_str()), 0));



				if (imgTemp == "-0j" || imgTemp == "-0J" || imgTemp == "-0i" || imgTemp == "-0I")
					mat[k][numberOfElementsInThisRow - 1].set_img(0);
					//mat[k].push_back(complex(0, 0));
				else
					mat[k][numberOfElementsInThisRow - 1].set_img(atof(imgTemp.c_str()));
					//mat[k].push_back(complex(atof(imgTemp.c_str()), 0));


				if ((generalTemp == "") && (k == 0) && (numberOfElementsInThisRow == 1))
				{
					cout << "Error!\nMatrix Can't be Empty";
					return 1; //empty matrix
				}

				if (input[i - 1] == ';') //row end ... intializing for a new row
				{
					k++;
					numberOfElementsInThisRow = 0;
				}
			{ //element end, intialinzing for a new element
				generalTemp.clear();
				realTemp.clear();
				imgTemp.clear();
				orderOf2signs.clear();
				noOfJs = 0;
				signs = 0;
				has_j_ = false;
				j++;
			}
			}
		}

		rows = k + 1;
		columns = numberOfElementsInLastRow;
		return 0;
	}

	void matrix::randomize(void)
	{
		srand(time(NULL)); //randomizes the seed of rand() each execution cause time(null) returns no. of seconds since 1970 which will never be the same number twice (if the same number is feeded to srand() rand will generate the same sequence
		rows = rand() % Rand_D + 1;
		columns = rand() % Rand_D + 1;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				int rr = rand() % Rand - Rand / 2; //this produces numbers between -Rand/2 to +Rand/2
				int RR = rand() % Rand / 10 - Rand / 20;
				int ri = rand() % Rand - Rand / 2; //this produces numbers between -Rand/2 to +Rand/20
				int RI = rand() % Rand / 10 - Rand / 20;
				if (RR != 0 && RI != 0)
				{
					mat[i][j].set_real(rr / (float)RR); //this will create random floating point numbers between -0.2 upto //0.2 
					mat[i][j].set_img(ri / (float)RI);
				}
				else
					j--; //if it's a nan redo this element
			}
		}
	}

	void matrix::square_randomize(void)
	{
		srand(time(NULL)); //randomizes the seed of rand() each execution cause time(null) returns no. of seconds since 1970 which will never be the same number twice (if the same number is feeded to srand() rand will generate the same sequence
		rows = rand() % Rand_D + 1;
		columns = rows;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				int rr = rand() % Rand - Rand / 2; //this produces numbers between -Rand/2 to +Rand/2
				int RR = rand() % Rand / 10 - Rand / 20;
				int ri = rand() % Rand - Rand / 2; //this produces numbers between -Rand/2 to +Rand/20
				int RI = rand() % Rand / 10 - Rand / 20;
				if (RR != 0 && RI != 0)
				{
					mat[i][j].set_real(rr / (float)RR); //this will create random floating point numbers between -0.2 upto //0.2 
					mat[i][j].set_img(ri / (float)RI);
				}
				else
					j--; //if it's a nan redo this element
			}
		}
	}

	void matrix::proper_randomize(int rows0, int columns0)
	{
		srand(time(NULL)); //randomizes the seed of rand() each execution cause time(null) returns no. of seconds since 1970 which will never be the same number twice (if the same number is feeded to srand() rand will generate the same sequence
		rows = rows0;
		columns = columns0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				int rr = rand() % Rand - Rand / 2; //this produces numbers between -Rand/2 to +Rand/2
				int RR = rand() % Rand / 10 - Rand / 20;
				int ri = rand() % Rand - Rand / 2; //this produces numbers between -Rand/2 to +Rand/20
				int RI = rand() % Rand / 10 - Rand / 20;
				if (RR != 0 && RI != 0)
				{
					mat[i][j].set_real(rr / (float)RR); //this will create random floating point numbers between -0.2 upto //0.2 
					mat[i][j].set_img(ri / (float)RI);
				}
				else
					j--; //if it's a nan redo this element
			}
		}
	}

	void matrix::selective_randomize(int rows0, int columns0)
	{
		srand(time(NULL)); //randomizes the seed of rand() each execution cause time(null) returns no. of seconds since 1970 which will never be the same number twice (if the same number is feeded to srand() rand will generate the same sequence
		rows = rows0;
		columns = columns0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				int rr = rand() % 4000 - 2000; //this produces numbers between -2000 - +2000
				int RR = rand() % 400 - 200;
				int ri = rand() % 4000 - 2000; //this produces numbers between -2000 - +2000
				int RI = rand() % 400 - 200;
				if (RR != 0 && RI != 0)
				{
					mat[i][j].set_real(rr / (float)RR); //this will create random floating point numbers between -0.2 upto //0.2 
					mat[i][j].set_img(ri / (float)RI);
				}
				else
					j--; //if it's a nan redo this element
			}
		}
	} //will need a way to get m,n from use

	bool matrix::has_NaN(void)
	{
		for (int row = 0; row < rows; row++) //first input rows
		{
			for (int column = 0; column < columns; column++) //second input columns
			{
				if (mat[row][column].has_NaN())
					return true;
			}
		}
		return false;
	}
//private:
	complex matrix::determinant_R(bool &state) //(R) for (Recursion) : causes stack overflow (not Used)
	{
		state = 0;
		if (columns != rows)
		{
			cout << "Error!\nNot a Square matrix!"; // Not a square matrix
			state = 1;
			complex null;
			return null;
		}
		else if (rows == 1)
		{
			return mat[0][0];
		}
		else if (rows == 2)
		{
			complex det;
			det = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
			return det;
		}
		else
		{
			complex det; matrix Temp;
			int rowAfterTossing, columnAfterTossing, i;

			for (int c = 0; c < rows; c++)
			{
				for (rowAfterTossing = 0; rowAfterTossing < rows - 1; rowAfterTossing++)
				{
					for (columnAfterTossing = 0, i = 0; columnAfterTossing < rows; columnAfterTossing++)
					{
						if (c == columnAfterTossing)
							continue;
						Temp.mat[rowAfterTossing][i] = mat[rowAfterTossing + 1][columnAfterTossing];
						i++;
					}
				}
				Temp.rows = rows - 1;
				Temp.columns = columns - 1;
				complex sign;
				sign = complex(pow(-1, c + 2), 0);
				det += mat[0][c] * Temp.determinant(state)*sign;
			}
			return det;
		}
	}

	complex matrix::matrix_of_coFactors(int d, int c)const
	{
		complex det; //to put the determinant that will appear after eliminaiting the row and the column of the element that i'm consiering
		det = complex(0, 0);
		if (rows == 1)
			return mat[0][0];
		else if (rows == 2)
		{
			det = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
			return det;
		}
		else
		{
			matrix Temp;
			complex sign;
			int rowAfterTossing, columnAfterTossing, i, j;

			for (rowAfterTossing = 0, j = 0; rowAfterTossing < rows; rowAfterTossing++)
			{
				if (d == rowAfterTossing)
					continue;
				for (columnAfterTossing = 0, i = 0; columnAfterTossing < columns; columnAfterTossing++)
				{
					if (c == columnAfterTossing)
						continue;
					Temp.mat[j][i] = mat[rowAfterTossing][columnAfterTossing];
					i++;
				}
				j++;
			}
			Temp.rows = rows - 1;
			Temp.columns = columns - 1;
			sign = complex(pow(-1, c + d + 2), 0);
			det += Temp.determinant()*sign;
			return det;
		}
	}

	complex matrix::multiply_diagonal_elements(void)const
	{
		complex temp;
		temp = complex(1, 0);
		for (int x = 0; x < rows; x++)
			temp *= mat[x][x];
		return temp;
	}

	int matrix::no_of_zero_vectors(void)const
	{
		int zero_vecs = 0;
		for (int m = 0; m < rows; m++)
		{
			if (get_a_row(m).is_zero_vec())
				zero_vecs++;
		}
		return zero_vecs;
	}

	void matrix::create_NaN(void)
	{
		for (int m = 0; m < rows; m++)
			for (int n = 0; n < columns; n++)
				mat[m][n] = complex(nan(""), nan(""));
	}