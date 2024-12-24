#include "complex.h" 

	complex::complex() //default constructor
	{
		real = 0;
		img = 0;
	}

	complex::complex(float R, float I)//constructor
	{
		real = R;
		img = I;
	}
	
	void complex::operator= (complex scnd)
	{
		real = scnd.real;
		img = scnd.img;
	}
	
	void complex::operator+=(complex scnd)
	{
		(*this) = ((*this) + scnd);
	}
	
	void complex::operator-=(complex scnd)
	{
		(*this) = ((*this) - scnd);
	}
	
	void complex::operator*=(complex scnd)
	{
		(*this) = ((*this) * scnd);
	}
	
	void complex::operator/=(complex scnd)
	{
		(*this) = ((*this) / scnd);
	}
	
	bool complex::operator==(complex scnd)const
	{
		return (real == scnd.real) && (img == scnd.img);
	}
	
	bool complex::operator!=(complex scnd)const
	{
		return (real != scnd.real) || (img != scnd.img);
	}
	
	complex complex::operator+(complex scnd)const
	{
		return complex(real + scnd.real, img + scnd.img);
	}
	
	complex complex::operator-(complex scnd)const
	{
		return complex(real - scnd.real, img - scnd.img);
	}
	
	complex complex::operator*(complex scnd)const
	{
		return complex(real*scnd.real - img*scnd.img, real*scnd.img + img*scnd.real);
	}
	
	complex complex::operator/(complex scnd)const
	{
		if (scnd.real == 0 && scnd.img == 0)
			return complex(nanf(""), nanf(""));
		return complex(((*this)*scnd.cconjugate()).real / (scnd*scnd.cconjugate()).real, ((*this)*scnd.cconjugate()).img / (scnd*scnd.cconjugate()).real);
	}
	
	complex complex::operator^(float powr)const
	{
		complex temp;
		if (powr == 0)
		{
			return complex(1, 0);
		}
		else if (abs((powr - (int)powr)) < Range) //almost an integer
		{
			temp = (*this);
			for (int n = 1; n < abs(round(powr)); n++)
				temp *= (*this);
			if (powr > 0)
				return temp;
			else
				temp = complex(1, 0) / temp;
		}
		else //rational power
		{
			float denom_pow = (abs((powr - (int)powr)));

			temp = (*this);
			for (int n = 1; n < round((int)powr*(1 / denom_pow)) + 1; n++) //power 12.5 = 25/2
				temp *= (*this); //done with the intgeral part of the power

			complex A(pow(temp.get_magnitude(), (denom_pow)), 0);
			complex B(cos(denom_pow*temp.get_phase('R')), sin(denom_pow*temp.get_phase('R')));
			temp = A*B; //now (*this) will have the value of the first^abs(power)

			if (powr > 0)
				return temp;
			else
				temp = complex(1, 0) / temp;
		}
		return temp;
	}
	
	void complex::set_real(float realIn)
	{
		real = realIn;
	}
	
	void complex::set_img(float imgIn)
	{
		img = imgIn;
	}
	
	float complex::get_real(void)const
	{
		return real;
	}
	
	float complex::get_imaginary(void)const
	{
		return img;
	}
	
	float complex::get_phase(char format)const //'R' for rads , 'D' for degrees
	{
		switch (format)
		{
		case 'd':
		case 'D':
			return atan2(img, real) * 180 / PI;
		case'r':
		case'R':
			return atan2(img, real);
		}
	}
	
	float complex::get_magnitude(void)const
	{
		return sqrt(pow(real, 2) + pow(img, 2));
	}
	
	void complex::print(void)const //note that there must be a member of the class calling the function (e.g it must be like x.print_complex())
	{
		if (real < Range && real > -Range) //equivalent to real == 0 with a little range precision
		{
			if (img < Range && img > -Range) //equivalent to img == 0 with a little range precision
				cout << 0;
			else
			{
				if (img < Range + 1 && img > -Range + 1)
					cout << "i";
				else
				{
					if (img < Range + round(img) && img > -Range + round(img))
						cout << round(img) << "i";
					else
						cout << img << "i";
				}
			}
		}
		else
		{
			if (img < Range && img > -Range)
			{
				if (real < Range + round(real) && real > -Range + round(real))
					cout << round(real);
				else
					cout << real;
			}
			else
			{
				if (img < Range + 1 && img > -Range + 1)
				{
					if (real < Range + round(real) && real > -Range + round(real))
						cout << round(real);
					else
						cout << real;
					cout << "+i";
				}
				else
				{
					if (img < Range - 1 && img > -Range - 1)
					{
						if (real < Range + round(real) && real > -Range + round(real))
							cout << round(real);
						else
							cout << real;
						cout << "-i";
					}
					else
					{
						if (img > 0)
						{
							if (real < Range + round(real) && real > -Range + round(real))
								cout << round(real);
							else
								cout << real;
							cout << "+";
							if (img < Range + round(img) && img > -Range + round(img))
								cout << round(img);
							else
								cout << img;
							cout << "i";
						}
						else
						{
							if (real < Range + round(real) && real > -Range + round(real))
								cout << round(real);
							else
								cout << real;

							if (img < Range + round(img) && img > -Range + round(img))
								cout << round(img);
							else
								cout << img;
							cout << "i";
						}
					}
				}
			}
		}
	}
	
	void complex::print(int null)const //note that there must be a member of the class calling the function (e.g it must be like x.print_complex())
	{
		if (has_NaN())
		{
			cout << "Sorry Number is Out of Precision Range, But You Can Still Use It";
			return;
		}
		if (real == 0)
		{
			if (img == 0)
				cout << 0;
			else
			{
				if (img == 1)
					cout << "i";
				else
					cout << img << "i";
			}
		}
		else
		{
			if (img == 0)
				cout << real;
			else
			{
				if (img == 1)
					cout << real << "+i";
				else
				{
					if (img == -1)
						cout << real << "-i";
					else
					{
						if (img < 0)
							cout << real << img << "i";
						else
							cout << real << "+" << img << "i";
					}
				}
			}
		}
	} //not used   //precision controlled print when needed : swap parameters of this and the other print
	
	void complex::conjugate(complex var)
	{
		real = var.real;
		img = var.img*(-1);
	}
	
	int complex::divide(complex first, complex second)
	{
		if (second.real == 0 && second.img == 0)
			(*this) = complex(nanf(0), nanf(0));
		(*this) = complex(((first*second.cconjugate())).real / (second*second.cconjugate()).real, ((first*second.cconjugate())).img / (second*second.cconjugate()).real);
		return 0;
	}
	
	complex complex::p_r(float magnitude, float phase)const //polar to rectangular just for internal use
	{
		//use real as magnitude , img as phase
		return complex(magnitude*cos(phase), magnitude*sin(phase));
	}
	
	complex complex::cconjugate(void)const
	{
		return complex(real, -img);
	} //complex conjugate
	
	bool complex::has_NaN(void)const
	{
		if (isnan(real) || isnan(img))
			return true;
		else
			return false;
	}
//not used
	
	complex complex::r_p() //rectangular to polar just for internal use
	{
		//use real as magnitude , img as phase
		return complex(sqrt(pow(real, 2) + pow(img, 2)), (atan2(img, real) * 180));
	}
	
	complex complex::p_r() //polar to rectangular just for internal use
	{
		//use real as magnitude , img as phase
		return complex(real*cos(img), real*sin(img));
	}
