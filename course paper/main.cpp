#include <iostream>
#include <map>
#include <stack>
#include <string>

//через map мы будем определять ранг операции, на создавая отдельных функций
std::map<std::string, int> operationsRang {
	{"+", 1},
	{"-", 1},
	{"*", 2},
	{"/", 2},
	{"^", 3},
	{"exp", 3},
	{"sin", 4},
	{"cos", 4},
	{"tan", 4},
	{"ctg", 4}
};
const double eps = 1e-10;

//проверка на функцию
bool isOperation(std::string& strWithExpr, size_t& i) {
	if (strWithExpr[i] == '+' || strWithExpr[i] == '-' || strWithExpr[i] == '*' || strWithExpr[i] == '/' || strWithExpr[i] == 's' || strWithExpr[i] == 'c' || strWithExpr[i] == 't' || strWithExpr[i] == 'e') return true;
	return false;
}

//нахождение функции и записывание ее в стек операций
std::string funcWrite(std::string& strWithExpr, size_t& i, std::stack<std::string>& operations) {
	std::string func;

	switch (strWithExpr[i]) {
		case 's':
			if (strWithExpr[i + 1] == 'i' && strWithExpr[i + 2] == 'n') {
				func += strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
				i += 3;
			} else {
				std::cerr << "invalid name function. pos: "<< i << std::endl;
			}
			break;
		case 'c':
			if (strWithExpr[i + 1] == 'o' && strWithExpr[i + 2] == 's') {
				func += strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
				i += 3;
			} else if (strWithExpr[i + 1] == 't' && strWithExpr[i + 2] == 'g') {
				func += strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
				i += 3;
			} else {
				std::cerr << "invalid name function. pos: " << i << std::endl;
			}
			break;
		case 't':
			if (strWithExpr[i + 1] == 'a' && strWithExpr[i + 2] == 'n') {
				func += strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
				i += 3;
			} else {
				std::cerr << "invalid name function. pos: " << i << std::endl;
			}
			break;
		case 'e':
			if (strWithExpr[i + 1] == 'x' && strWithExpr[i + 2] == 'p') {
				func += strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
				i += 3;
			} else {
				std::cerr << "invalid name function. pos: " << i << std::endl;
			}
			break;
		default: return "0";
	}
	return func;
}

//парсинг строки в число
double numberparse(std::string& strWithExpr, size_t& i) {
	std::string buf;
	bool shouldExit = false;

	if (strWithExpr[i] == '+') ++i;
	if (strWithExpr[i] == '-') {
		buf.push_back(strWithExpr[i]);
		++i;
	}

	while (i < strWithExpr.size() && !shouldExit) {

		if (isdigit(strWithExpr[i])) {
			buf.push_back(strWithExpr[i]);
			++i;
		} else if (strWithExpr[i] == '.') {
			buf.push_back(strWithExpr[i]);
			++i;
		} else if (strWithExpr[i] == ' ' || isOperation(strWithExpr, i)) {
			shouldExit = true;
		}
	}
	return std::stod(buf);
}

//вызов функции рассчета
void math(std::stack<double>& numbers, std::stack<std::string>& operations) {
	double a,b,c;
	
	a = numbers.top();
	numbers.pop();

	//оператор сложения
	if (operations.top() == "+") {
		b = numbers.top();
		numbers.pop();
		c = a + b;
		numbers.push(c);
		operations.pop();

	//оператор умножения
	} else if (operations.top() == "*") {
		b = numbers.top();
		numbers.pop();
		c = a * b;
		numbers.push(c);
		operations.pop();

	//оператор вычитания
	} else if (operations.top() == "-") {
		b = numbers.top();
		numbers.pop();
		c = b - a;
		numbers.push(c);
		operations.pop();

	//оператор деления
	} else if (operations.top() == "/") {
		if (a != 0) {
			b = numbers.top();
			numbers.pop();
			c = b / a;
			numbers.push(c);
			operations.pop();
		} else {
			std::string errorMsg = "in this expression, division by zero is prohibited";
			throw std::runtime_error(errorMsg);
		}
	//оператор возведения в степень
	} else if (operations.top() == "^") {
		b = numbers.top();
		numbers.pop();
		c = pow(b,a);
		numbers.push(c);
		operations.pop();

	//функция синуса
	} else if (operations.top() == "sin") {
		if (fabs(sin(a)) > eps) c = 0;
		else c = sin(a);
		numbers.push(c);
		operations.pop();

	//функция косинуса
	} else if (operations.top() == "cos") {
		if (fabs(cos(a)) > eps) c = 0;
		else c = cos(a);
		numbers.push(c);
		operations.pop();

	//функция тангенса
	} else if (operations.top() == "tan") {
		double ta,tb;
		if (fabs(sin(a)) > eps) ta = 0;
		else ta = sin(a);
		if (fabs(cos(a)) > eps) tb = 0;
		else tb = cos(a);
		operations.pop();

		if (tb == 0) throw std::runtime_error("invalid argument for tangent");
		else {
			c = ta / tb;
			numbers.push(c);
		}

	//функция котангенса
	} else if (operations.top() == "ctg") {
		double ta, tb;
		if (fabs(sin(a)) > eps) ta = 0;
		else ta = sin(a);
		if (fabs(cos(a)) > eps) tb = 0;
		else tb = cos(a);
		operations.pop();

		if (ta == 0) throw std::runtime_error("invalid argument for cotangent");
		else {
			c = tb / ta;
			numbers.push(c);
		}
	} else if (operations.top() == "exp") {
		c = exp(a);
		operations.pop();
	}
}




int main() {
	//приветствие пользователя, инструкция япользования калькулятором
	std::cout << "======================================\n Hello! This programm is a calculator\n======================================\n";
	std::cout << "Enter the mathematical expression:\n";

	size_t i = 0;
	std::string strWithExpr;
	bool unaryFlag = true;
	std::getline(std::cin, strWithExpr);

	std::stack <double> numbers;
	std::stack <std::string> operations;
	
 	while (i < strWithExpr.size()) {
		if (strWithExpr[i] == ' ') ++i;

		std::string func;

		if (strWithExpr[i] == 's' || strWithExpr[i] == 'c' || strWithExpr[i] == 't' || strWithExpr[i] == 'e') {
			
		}

		if (strWithExpr[i] >= '0' && strWithExpr[i] <= '9' || (unaryFlag && (strWithExpr[i] == '+' || strWithExpr[i] == '-'))) {
			try {
				numbers.push(numberparse(strWithExpr, i));
				unaryFlag = false;
				continue;
			} catch (const std::runtime_error& e) {
				std::cerr << e.what() << std::endl;
				system("pause");
				return 0;
			}
			
		} else if (((strWithExpr[i] == '+' || strWithExpr[i] == '-') && !unaryFlag) || strWithExpr[i] == '/' || strWithExpr[i] == '*' || strWithExpr[i] == '^' ) {
			if (operations.empty()) { // если стек с операциями пуст
				std::string buf = "";
				buf += strWithExpr[i];
				operations.push(buf);
				++i;
			} else if (!operations.empty() && ((operationsRang[operations.top()]) >= ())) { // если стек с операциями не пуст и ранг последней в стеке выше или равен записываемому
				
			}
		}
	}

	
	while (!operations.empty()) {
		math(numbers, operations);
	}

	std::cout << "Answer: " << numbers.top() << std::endl;
	system("pause");
	return 0;
}