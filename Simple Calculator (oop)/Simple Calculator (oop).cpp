

#include <iostream>
using namespace std;


class clsCalcualtor
{
	float _result = 0, _input = 0, _PreviosResult = 0;
	string _Operation = "";



public:

	void Clear()
	{
		_Operation = "Clear";
		_input = 0;
		_PreviosResult = _result;
		_result = 0;
	}

	void Add(float Number)
	{
		_Operation = "Add";
		_input = Number;
		_PreviosResult = _result;
		_result += Number;
	}

	void Substract(float Number)
	{
		_Operation = "Subtract";
		_input = Number;
		_PreviosResult = _result;
		_result -= Number;
	}

	void Divide(float Number)
	{
		if (Number == 0)
			Number = 1;
		_Operation = "Divide";
		_input = Number;
		_PreviosResult = _result;
		_result /= Number;
	}

	void Multibly(float Number)
	{
		_Operation = "Multiply";
		_input = Number;
		_PreviosResult = _result;
		_result *= Number;
	}

	void CancleLastOperation()
	{
		_Operation = "Canceling Last operation";
		_input = 0;
		_result = _PreviosResult;
		_PreviosResult = _result;
	}

	float GetResult()
	{
		return _result;
	}

	void PrintResult()
	{
		cout << "Result ";
		(_Operation != "") ?
			cout << " After " << _Operation << " " << _input << " is : " << _result << endl : cout << "is : " << _result << endl;
	}

};

int main()
{
	clsCalcualtor Calculator1;

	Calculator1.PrintResult();

	Calculator1.Add(40);
	Calculator1.PrintResult();

	Calculator1.Substract(10);
	Calculator1.PrintResult();

	Calculator1.Divide(0);
	Calculator1.PrintResult();

	Calculator1.Divide(2);
	Calculator1.PrintResult();

	Calculator1.Multibly(3);
	Calculator1.PrintResult();

	Calculator1.CancleLastOperation();
	Calculator1.PrintResult();

	Calculator1.Clear();
	Calculator1.PrintResult();
}


