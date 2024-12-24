#include <Windows.h>
#include <conio.h>
#include <chrono>
#include "matrix.h"

#define period 70 //speed of spinnig

void loading(int time, int count) //count is the number of slashes //time is the period of spinning //period is the speed of spinning
{
	for (int i = 0; i < time; i++)
	{
		if (_kbhit())
			break;
		for (int k = 0; k < count; k++)cout << "\\";
		Sleep(period);
		for (int k = 0; k < count; k++)cout << "\b";
		for (int k = 0; k < count; k++)cout << "|";
		Sleep(period);
		if (_kbhit())
		{
			cout << "\b";
			break;
		}
		for (int k = 0; k < count; k++)cout << "\b";
		for (int k = 0; k < count; k++)cout << "/";
		Sleep(period);
		for (int k = 0; k < count; k++)cout << "\b";
		for (int k = 0; k < count; k++)cout << "-";
		Sleep(period);
		for (int k = 0; k < count; k++)cout << "\b"; //change count to 1 and this can be commented to give a nice effect	
	}
}

void intro(void)
{
	cout << "////////////////////////////////////////////////////////////////////////////////";
	cout << "///**///***////***/////////////////////////////////////////*****//**//**/*****//";
	cout << "//*//*//**//*/**/**/////                              /////**//**/**/**//**//**/";
	cout << "/**//**/****//**/**///   Welcome To Matrix Calculator   ///*****//***////*****//";
	cout << "/******/**//*/**/**/////                              /////**//**/***////*****//";
	cout << "/**//**/**//*/**/**////////////////////////////////////////**//**/**/**//**//**/";
	cout << "/**//**/***////***/////////////////////////////////////////*****//**//**/**//**/";
	cout << "/////////////////////            *How to Use*             //////////////////////";
	cout << "//                                                                            //";
	cout << "//  Example 1:          Example 2:          Example 3:          Example 4*:   //";
	cout << "//                                                                            //";
	cout << "//  [1 2 3;4 5 6]       [1 2+i;2 1+i]       [3 6;7 2]           [5 7;9 4]     //";
	cout << "//  +                   D                   ^                   C             //";
	cout << "//  [1 2 3;4 5 6]       =                   2                   [6;9]         //";
	cout << "//  =                   [-3-i]              =                   X1 = 0.9069   //";
	cout << "//  [2 4 6;8 10 12]                         [51 30;35 46]       X2 = 0.2093   //";
	cout << "//                                                                            //";
	cout << "//      Supported Operations: + , - , * , / , ^ , T , D , I , C , E , R       //";
	cout << "//  T:Transpose  D:Determinanat  I:Inverse  C:Cramer  E:Elimination  R:Rank   //";
	cout << "//      *Enter coefficient matrix followed by \"C\" then the answer column    //";
	cout << "//                                                                            //";
	cout << "////////////////////////////////////////////////////////////////////////////////";
	cout << "////////////////////////////////////////////////////////////////////////////////\n";
}

int main() //note that the run time that is calculated is just for filling and the opertaion it self ignoring the const. periodes like the checks for exit and skip
{
	intro();
	loading(20, 1); //any key to skip preferably (down arrow)
	system("pause");
	matrix matA, matC; //variables are declared here to avoid re-construction
	string input;
	auto start = chrono::high_resolution_clock::now();
	auto elapsed = chrono::high_resolution_clock::now() - start;
	int fill;
	char operation/*, repeat*/;
start:
	cout << "Waiting for input:\n\n";
error_start:
	while (1)
	{
		cin.sync();
		getline(cin, input);

		start = chrono::high_resolution_clock::now();
		if (input == "skip" || input == "Skip" || input == "SKIP")
			goto start;
		else if (input == "exit" || input == "Exit" || input == "EXIT")
			goto Out;

		fill = matA.fill(input); //to be calculated once of better run time
		if (fill == 1)
		{
			cout << "\nPlease Try Again:\n\n";
			input.clear();
			goto error_start;
		}
		else if (fill == 2)
		{
			matA = matC;
			matA.print();
			cout << endl;
			cout << "Dimentions(Rows x Columns): " << matA.get_rows() << " x " << matA.get_columns() << endl;
		}
		else if (fill == 3)
		{
			matA.randomize();
			matA.print();
			cout << endl;
			cout << "Dimentions(Rows x Columns): " << matA.get_rows() << " x " << matA.get_columns() << endl;
		}
		else if (fill == 4)
		{
			matA.square_randomize();
			matA.print();
			cout << endl;
			cout << "Dimentions(Rows x Columns): " << matA.get_rows() << " x " << matA.get_columns() << endl;
		}
		else if (fill == 6)
		{
			cout << "\nSorry, You Can Not Use prand As The First Operand\nPlease Try Again:\n\n";
			input.clear();
			goto error_start;
		}
		else if (fill == 7)
		{
			int r, c;
			cin >> r >> c; //run time not right this case
			cin.sync();
			matA.selective_randomize(r, c);
			matA.print();
			cout << endl;
			cout << "Dimentions(Rows x Columns): " << matA.get_rows() << " x " << matA.get_columns() << endl;
		}
		else if (fill == 0)
			cout << "Dimentions(Rows x Columns): " << matA.get_rows() << " x " << matA.get_columns() << endl;


		elapsed = chrono::high_resolution_clock::now() - start;
		long long microseconds = chrono::duration_cast<chrono::microseconds>(elapsed).count();



	opr_start:
		input.clear();
		getline(cin, input);
		if (input == "skip" || input == "Skip" || input == "SKIP")
			goto start;
		else if (input == "exit" || input == "Exit" || input == "EXIT")
			goto Out;
		else if (input.size() > 1)
		{
			cout << "Error!\nInvalid/Unsupported Operation\n" << "Please Choose The Operation Again:\n\n";
			matA.print();
			cout << endl;
			goto opr_start;
		}
		operation = input[0];
		input.clear();


		/*--------------------------------------------------------------------------------------------------------------------------------*/
		if (operation == '+' || operation == '-' || operation == '*' || operation == '/' || operation == 'C')
		{
			matrix matB;
		E1:
			cin.sync(); //because getline is right after cin >> opertaion so it just grasps that input (e.g the operation) as input2
			getline(cin, input);

			start = chrono::high_resolution_clock::now();

			if (input == "skip" || input == "Skip" || input == "SKIP")
				goto start;
			else if (input == "exit" || input == "Exit" || input == "EXIT")
				goto Out;

			fill = matB.fill(input);
			if (fill == 1)
			{
				cout << "\nPlease Enter the Second Matrix Again:\n\n";
				matA.print();
				cout << endl << operation << endl;
				input.clear();
				goto E1;
			}
			else if (fill == 2)
			{
				matB = matC;
				matB.print();
				cout << endl;
				cout << "Dimentions(Rows x Columns): " << matB.get_rows() << " x " << matB.get_columns() << endl;
			}
			else if (fill == 3 || fill == 4 || fill == 7)
			{
				cout << "\nSorry, You Can Not Use a Random Matrix As The Second Operand\nConsider Using prand Instead\nPlease Enter the Second Matrix Again:\n\n";
				matA.print();
				cout << endl << operation << endl;
				input.clear();
				goto E1;
			}
			else if (fill == 6)
			{
				if (operation == '+' || operation == '-')
					matB.proper_randomize(matA.get_rows(), matA.get_columns());
				else if (operation == '*')
					matB.proper_randomize(matA.get_columns(), matA.get_rows());
				else if (operation == '/')
					matB.proper_randomize(matA.get_columns(), matA.get_columns());
				else
					matB.proper_randomize(matA.get_rows(), 1);
				matB.print();
				cout << endl;
				cout << "Dimentions(Rows x Columns): " << matB.get_rows() << " x " << matB.get_columns() << endl;
			}
			else if (fill == 7) //keep it for later
			{
				int r, c;
				cin >> r >> c;
				cin.sync();
				matB.selective_randomize(r, c);
				matB.print();
				cout << endl;
				cout << "Dimentions(Rows x Columns): " << matB.get_rows() << " x " << matB.get_columns() << endl;
			}
			else if (fill == 0)
				cout << "Dimentions(Rows x Columns): " << matB.get_rows() << " x " << matB.get_columns() << endl;



			switch (operation)
			{
			case '+':
			{
				if (matC.add(matA, matB) == 1)
				{
					cout << "\nPlease Try Again:\n\n";
					goto error_start;
				}
				break; //Done
			}

			case '-':
			{
				if (matC.subtract(matA, matB) == 1)
				{
					cout << "\nPlease Try Again:\n\n";
					goto error_start;
				}
				break; //Done
			}

			case '*': //using show_result with the output dimentions rowsIn1 , columnIn2
			{
				if (matC.multiply(matA, matB) == 1)
				{
					cout << "\nPlease Try Again:\n\n";
					goto error_start;
				}
				break; //Done
			}

			case '/': //multiplying A(A^(-1)) --> columns of A should be the same as rows of A^(-1)
			{
				if (matC.divide(matA, matB) == 1)
				{
					cout << "\nPlease Try Again:\n\n";
					goto error_start;
				}
				break; //Done
			}

			case 'C':
			{
				vector_m vec_C; //result vec
				bool state1;
				vec_C = matA.cramer(matB, state1);
				if (state1)
				{
					cout << "\nPlease Try Again:\n\n";
					goto error_start;
				}
				if (vec_C.has_NaN())
				{
					cout << "Sorry Result is Out of Precision Range\n";
					matC.intialize();
					goto start;
				}
				vec_C.print_C();
				break; //Done
			}
			}
			if (operation != 'C')
			{
				if (matC.has_NaN())
				{
					cout << "Sorry Result is Out of Precision Range\n";
					matC.intialize();
					goto start;
				}
				cout << "=\n";
				matC.print();
				cout << endl << "Dimentions(Rows x Columns): " << matC.get_rows() << " x " << matC.get_columns();
			}
			//matB.deletem(); //not important as after the while restarts matB stays at the smae location so no memory leak
			elapsed = chrono::high_resolution_clock::now() - start;
			long long microseconds0 = chrono::duration_cast<chrono::microseconds>(elapsed).count();
			cout << "\n\n\nExecution Time: " << (microseconds0 + microseconds) / 1000 << " ms" << endl;
		}

		/*--------------------------------------------------------------------------------------------------------------------------------*/
		else if (operation == '^' || operation == 'I' || operation == 'T' || operation == 'D')
		{
			switch (operation)
			{
			case '^':
			{
				input.clear();
				getline(cin, input);
				if (input == "skip" || input == "Skip" || input == "SKIP")
					goto start;
				else if (input == "exit" || input == "Exit" || input == "EXIT")
					goto Out;
				string Power = input;
				input.clear();

				start = chrono::high_resolution_clock::now();
				if (matC.power(matA, Power) == 1)
				{
					cout << "\nPlease Try Again:\n\n";
					goto error_start;
				}
				break; //Done
			}
			case 'I': //not working
			{
				start = chrono::high_resolution_clock::now();
				if (matC.inverse(matA) == 1)
				{
					cout << "\nPlease Try Again:\n\n";
					goto error_start;
				}
				break; //Done
			}
			case 'T':
			{
				start = chrono::high_resolution_clock::now();
				if (matC.transpose(matA) == 1)
				{
					cout << "\nPlease Try Again:\n\n";
					goto error_start;
				}
				break; //Done
			}
			case 'D':
			{
				start = chrono::high_resolution_clock::now();

				complex temp;
				bool state;
				temp = matA.determinant(state);
				if (state)
				{
					cout << "\nPlease Try Again:\n\n";
					state = 0;
					goto error_start;
				}
				matC.set_element(0, 0, temp); //to be used with (ans)
				matC.set_dimentions(1, 1);

				break; //Done
			}
			}
			if (matC.has_NaN())
			{
				cout << "Sorry Result is Out of Precision Range\n";
				matC.intialize();
				goto start;
			}
			cout << "=\n";
			matC.print();
			if (operation != 'D')cout << endl << "Dimentions(Rows x Columns): " << matC.get_rows() << " x " << matC.get_columns();

			auto elapsed = chrono::high_resolution_clock::now() - start;
			long long microseconds0 = chrono::duration_cast<chrono::microseconds>(elapsed).count();
			cout << "\n\n\nExecution Time: " << (microseconds0 + microseconds) / 1000 << " ms" << endl;
		}

		/*----------------------------------------------------------------------------------------------------------------------------------*/
		else if (operation == 'E' || operation == 'R')
		{
			cout << "Do You Want The Detailed Solution ? [Y/N]: ";
			input.clear();
		again0:
			cin.sync();
			getline(cin, input);
			if (input == "skip" || input == "Skip" || input == "SKIP")
				goto start;
			else if (input == "exit" || input == "Exit" || input == "EXIT")
				goto Out;

			char detail = input[0];
			input.clear();
			start = chrono::high_resolution_clock::now();

			switch (detail)
			{
			case'Y':
			case'y':
			{
				if (operation == 'E')
					matC.eliminate_d(matA);
				else
				{
					int R;
					matC = matA;
					R = matC.rank_d();
					cout << "\nRank = " << R;
				}
				break;
			}
			case'N':
			case'n':
			{
				if (operation == 'E')
				{
					matC.eliminate(matA);
					cout << "=\n";
					matC.print();
				}
				else
				{
					int R;
					matC = matA;
					R = matC.rank();
					cout << "=\n";
					matC.print();
					cout << "\nRank = " << R;
				}
				break;
			}
			default:
				cout << "Wrong Choice! Please Try Again :";
				goto again0;
				break; //Done
			}
			auto elapsed = chrono::high_resolution_clock::now() - start;
			long long microseconds0 = chrono::duration_cast<chrono::microseconds>(elapsed).count();
			cout << "\n\nExecution Time: " << (microseconds0 + microseconds) / 1000 << " ms" << endl;
		}
		else
		{
			cout << "Error!\nInvalid/Unsupported Operation\n" << "Please Choose The Operation Again:\n\n";
			matA.print();
			cout << endl;
			goto opr_start;
		}
		/*cout << endl << endl << "Do you want to re-calculate ? [Y/N]: ";
		input.clear();
		again:
		cin.sync();
		getline(cin, input);

		if (input == "skip" || input == "Skip" || input == "SKIP")
		goto start;
		else if (input == "exit" || input == "Exit" || input == "EXIT")
		goto Out;

		repeat = input[0];
		input.clear();
		switch (repeat)
		{
		case'Y':
		case'y':
		input.clear();
		cout << endl << endl;
		goto start;
		break;
		case'N':
		case'n':
		goto Out;
		break;
		default:
		cout << "Wrong Choice! Please Try Again :";
		goto again;
		}
		}
		Out:
		cout << endl << "Thank You!" << endl;
		system("pause");
		return 0;*/
		goto start;
	}
Out:
	cout << endl << "Thank You!" << endl;
	system("pause");
	return 0;
}