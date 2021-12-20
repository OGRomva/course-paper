#include <iostream>
#include <map>
#include <stack>
#include "functions.h";

//класс, созданный для вызва ошибок
struct errors {
	std::string errorMsg;
	errors(std::string errorMsg) : errorMsg(errorMsg) {};
};

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
	{"ctg", 4},
};

int main() {

	//приветствие пользователя, инструкция пользования калькулятором
	std::cout << "======================================\n Hello! This programm is a calculator\n======================================\n";
	std::cout << " To enter the number pi, write \"p\" \n";
	std::cout << " To enter the function sinus, cosinus, tangent, cotangent and expanent, \n write sin(...), cos(...), tan(...), ctg(...) and exp(...) \n";
	std::cout << "Enter the mathematical expression:\n";

	size_t i = 0;
	std::string strWithExpr;
	bool unaryFlag = true;
	bool haveParenthesis = false;
	const double pi = acos(-1);
	std::getline(std::cin, strWithExpr);

	std::stack <double> numbers;
	std::stack <std::string> operations;
	
 	while (i < strWithExpr.size()) {
		if (strWithExpr[i] == ' ') ++i;

		std::string func = "0";

		if (strWithExpr[i] == 's' || strWithExpr[i] == 'c' || strWithExpr[i] == 't' || strWithExpr[i] == 'e') {
			try {
				funcWrite(strWithExpr, i, func);
			} catch (const errors& error) {
				std::cerr << error.errorMsg << " pos: " << i + 1 << std::endl;
				system("pause");
				return 0;
			}
			if (func != "0") {
				operations.push(func);
				func = "0";
			}
		}

		// если прочитана открывающая скобка
		if (strWithExpr[i] == '(') {
			operations.push(chToStr(strWithExpr[i]));
			haveParenthesis = true;
			unaryFlag = true;
			++i;
		}

		if (haveParenthesis && (i == strWithExpr.size() - 1) && (strWithExpr[i] != ')')) {
			std::cerr << "missing closing parenthesis" << std::endl;
			system("pause");
			return 0;
		}

		// если прочитана закрывающая скобка
		if (strWithExpr[i] == ')') {
			while (operations.top() != "(") {
				try {
					math(numbers, operations);
				} catch (const errors& error) {
					std::cerr << error.errorMsg << " pos: " << i + 1 << std::endl;
					system("pause");
					return 0;
				}
			}
			haveParenthesis = false;
			operations.pop();
			++i;
		}

		// если прочитано число
		if (strWithExpr[i] >= '0' && strWithExpr[i] <= '9' || strWithExpr[i] == 'p' || (unaryFlag && (strWithExpr[i] == '+' || strWithExpr[i] == '-'))) {
			if (strWithExpr[i] == 'p') {
				numbers.push(pi);
				++i;
			} else {
				try {
					numbers.push(numberparse(strWithExpr, i));
				} catch (const errors& error) {
					std::cerr << error.errorMsg << " pos: " << i + 1 << std::endl;
					system("pause");
					return 0;
				}
			}
			unaryFlag = false;
			continue;
		} else if (((strWithExpr[i] == '+' || strWithExpr[i] == '-') && !unaryFlag) || strWithExpr[i] == '/' || strWithExpr[i] == '*' || strWithExpr[i] == '^') { // если прочитана операция
			if (operations.empty()) { // если стек с операциями пуст
				std::string buf = "";
				buf += strWithExpr[i];
				operations.push(buf);
				++i;
			} else if (!operations.empty() && ((operationsRang[operations.top()]) < (operationsRang[chToStr(strWithExpr[i])]))) { // если стек с операциями не пуст и ранг последней в стеке меньше записываемому
				std::string buf = "";
				buf += strWithExpr[i];
				operations.push(buf);
				++i;
			} else if (!operations.empty() && ((operationsRang[operations.top()]) >= (operationsRang[chToStr(strWithExpr[i])])) && operations.top() != "(") { // если стек с операциями не пуст и ранг последней операции в стеке больше или равен текущей записываемой операции
				math(numbers, operations);
				continue;
			} else if (!operations.empty() && operations.top() == "(") {
				std::string buf = "";
				buf += strWithExpr[i];
				operations.push(buf);
				++i;
			}
		}
	}

	while (!operations.empty()) {
		try {
			math(numbers, operations);
		} catch (const errors& error) {
			std::cerr << error.errorMsg << " pos: " << i + 1 << std::endl;
			system("pause");
			return 0;
		}
	}
	std::cout << "Answer: " << numbers.top() << std::endl;
	system("pause");
	return 0;
}