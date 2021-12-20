#include <string>
#include <stack>
#ifndef FUNC1
#define FUNC1

	//функция преобразовывающая char в string 
	std::string chToStr(char);

	//проверка на функцию
	bool isOperation(std::string&, size_t&);

	//нахождение функции и записывание ее в стек операций
	void funcWrite(std::string&, size_t&, std::string&);

	//парсинг строки в число
	double numberparse(std::string&, size_t&);

	//вызов функции рассчета
	void math(std::stack<double>&, std::stack<std::string>&);

#endif