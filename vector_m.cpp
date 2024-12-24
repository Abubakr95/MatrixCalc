#include "vector_m.h"
	
	vector_m::vector_m()
	{
		//the values are set to zero when constructed via complex
		count = 1;
	}

	vector_m::vector_m(int elements)
	{
		count = elements;
	}

	void vector_m::set_element(int pos, complex value)
	{
		vector[pos] = value;
	}

	complex vector_m::get_element(int pos)const
	{
		return vector[pos];
	}

	void vector_m::set_count(int no)
	{
		count = no;
	}

	int vector_m::get_count(void)const
	{
		return count;
	}

	void vector_m::operator=(vector_m var)
	{
		for (int n = 0; n < var.count; n++)
			vector[n] = var.vector[n];
		count = var.count;
	}

	vector_m vector_m::operator*(complex factor)const
	{
		vector_m temp(count);
		for (int n = 0; n < count; n++)
		{
			temp.vector[n] = vector[n] * factor;
		}
		return temp;
	}

	vector_m vector_m::operator/(complex factor)const
	{
		vector_m temp(count);
		if (factor == complex(0, 0))
		{
			for (int n = 0; n, count; n++)
			{
				temp.vector[n] = complex(nanf(""), nanf(""));
				return temp;
			}
		}
		for (int n = 0; n < count; n++)
		{
			temp.vector[n] = vector[n] / factor;
		}
		return temp;
	}

	vector_m vector_m::operator+(vector_m second)const
	{
		/*if (count != second.get_count())
		return;*/
		vector_m temp(count);
		for (int n = 0; n < count; n++)
		{
			temp.vector[n] = vector[n] + second.vector[n];
		}
		return temp;
	}

	vector_m vector_m::operator-(vector_m second)const
	{
		/*if (count != second.get_count())
		return;*/
		vector_m temp(count);
		for (int n = 0; n < count; n++)
		{
			temp.vector[n] = vector[n] - second.vector[n];
		}
		return temp;
	}

	bool vector_m::is_zero_vec()const
	{
		int zeros = 0;
		for (int n = 0; n < count; n++)
			if (vector[n].get_real() == 0 && vector[n].get_imaginary() == 0)
				zeros++;
		if (zeros == count)
			return true;
		return false;
	}

	bool vector_m::is_zero_vec_inverseSpecial(int count)const
	{
		int zeros = 0;
		for (int n = 0; n < count; n++)
			if (vector[n].get_real() == 0 && vector[n].get_imaginary() == 0)
				zeros++;
		if (zeros == count)
			return true;
		return false;
	}

	void vector_m::print_C(void)const //just for cramer
	{
		for (int n = 0; n < count; n++)
		{
			printf("X%d = ", (n + 1));
			vector[n].print();
			if (n != count - 1)
				cout << "\n";
		}
	}

	bool vector_m::has_NaN(void)const
	{
		for (int n = 0; n < count; n++)
		{
			if (vector[n].has_NaN())
				return true;
		}
		return false;
	}