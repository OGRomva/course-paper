#include "functions.h";

//класс, созданный для вызова исключений
struct errors {
	std::string errorMsg;
	errors(std::string errorMsg) : errorMsg(errorMsg) {};
};

//функция преобразовывающая char в string 
std::string chToStr(char a) {
	std::string buf;
	buf.push_back(a);
	return buf;
}

//проверка на функцию
bool isOperation(std::string& strWithExpr, size_t& i) {
	if (strWithExpr[i] == '+' ||
		strWithExpr[i] == '-' ||
		strWithExpr[i] == '*' ||
		strWithExpr[i] == '/' ||
		strWithExpr[i] == '^' ||
		strWithExpr[i] == 's' ||
		strWithExpr[i] == 'c' ||
		strWithExpr[i] == 't' ||
		strWithExpr[i] == 'e' ||
		strWithExpr[i] == ')') return true;
	return false;
}

//нахождение функции и записывание ее в стек операций
void funcWrite(std::string& strWithExpr, size_t& i, std::string& func) {
	func = "";

	switch (strWithExpr[i]) {
	case 's':
		if (strWithExpr[i + 1] == 'i' && strWithExpr[i + 2] == 'n') {
			func = func + strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
			i += 3;
		} else throw errors("invalid name function");
		break;
	case 'c':
		if (strWithExpr[i + 1] == 'o' && strWithExpr[i + 2] == 's') {
			func = func + strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
			i += 3;
		} else if (strWithExpr[i + 1] == 't' && strWithExpr[i + 2] == 'g') {
			func = func + strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
			i += 3;
		} else throw errors("invalid name function");
		break;
	case 't':
		if (strWithExpr[i + 1] == 'a' && strWithExpr[i + 2] == 'n') {
			func = func + strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
			i += 3;
		} else throw errors("invalid name function");
		break;
	case 'e':
		if (strWithExpr[i + 1] == 'x' && strWithExpr[i + 2] == 'p') {
			func = func + strWithExpr[i] + strWithExpr[i + 1] + strWithExpr[i + 2];
			i += 3;
		} else throw errors("invalid name function");
		break;
	default: func = "0";
	}
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
		} else if (!isdigit(strWithExpr[i]) &&
			strWithExpr[i] != '+' &&
			strWithExpr[i] != '/' &&
			strWithExpr[i] != '-' &&
			strWithExpr[i] != '*' &&
			strWithExpr[i] != '^' &&
			strWithExpr[i] != ' ' &&
			strWithExpr[i] != ')') {
			shouldExit = true;
			throw errors("incorrect fractional number notation");
		} else if (strWithExpr[i] == ' ' || isOperation(strWithExpr, i)) shouldExit = true;
	}
	return std::stod(buf);
}

//вызов функции рассчета
void math(std::stack<double>& numbers, std::stack<std::string>& operations) {
	double a, b, c;
	const double eps = 1e-10;

	a = numbers.top();
	numbers.pop();

	//оператор сложения
	if (operations.top() == "+") {
		if (numbers.empty()) {
			throw errors("the absence of a second operand for a binary operation");
		} else {
			b = numbers.top();
			numbers.pop();
			c = a + b;
			numbers.push(c);
			operations.pop();
		}

	//оператор умножения
	} else if (operations.top() == "*") {
		if (numbers.empty()) {
			throw errors("the absence of a second operand for a binary operation");
		} else {
			b = numbers.top();
			numbers.pop();
			c = a * b;
			numbers.push(c);
			operations.pop();
		}
	//оператор вычитания
	} else if (operations.top() == "-") {
		if (numbers.empty()) {
			throw errors("the absence of a second operand for a binary operation");
		} else {
			b = numbers.top();
			numbers.pop();
			c = b - a;
			numbers.push(c);
			operations.pop();
		}
	//оператор деления
	} else if (operations.top() == "/") {
		if (numbers.empty()) {
			throw errors("the absence of a second operand for a binary operation");
		} else {
			if (a != 0) {
				b = numbers.top();
				numbers.pop();
				c = b / a;
				numbers.push(c);
				operations.pop();
			} else throw errors("in this expression, division by zero is prohibited");
		}
	//оператор возведения в степень
	} else if (operations.top() == "^") {
		if (numbers.empty()) {
			throw errors("the absence of a second operand for a binary operation");
		} else {
			b = numbers.top();
			numbers.pop();
			c = pow(b, a);
			numbers.push(c);
			operations.pop();
		}
	//функция синуса
	} else if (operations.top() == "sin") {
		if (fabs(sin(a)) < eps) c = 0;
		else c = sin(a);
		numbers.push(c);
		operations.pop();

	//функция косинуса
	} else if (operations.top() == "cos") {
		if (fabs(cos(a)) < eps) c = 0;
		else c = cos(a);
		numbers.push(c);
		operations.pop();

	//функция тангенса
	} else if (operations.top() == "tan") {
		double ta, tb;
		if (fabs(sin(a)) < eps) ta = 0;
		else ta = sin(a);
		if (fabs(cos(a)) < eps) tb = 0;
		else tb = cos(a);
		operations.pop();

		if (tb == 0) throw errors("invalid argument for tangent");
		else {
			c = ta / tb;
			numbers.push(c);
		}

	//функция котангенса
	} else if (operations.top() == "ctg") {
		double ta, tb;
		if (fabs(sin(a)) < eps) ta = 0;
		else ta = sin(a);
		if (fabs(cos(a)) < eps) tb = 0;
		else tb = cos(a);
		operations.pop();

		if (ta == 0) {
			throw errors("Invalid argument for cotangent");
		} else {
			c = tb / ta;
			numbers.push(c);
		}
	} else if (operations.top() == "exp") {
		c = exp(a);
		operations.pop();
		numbers.push(c);
	}
}
