#include <string>
#include <stack>
#ifndef FUNC1
#define FUNC1

	//������� ����������������� char � string 
	std::string chToStr(char);

	//�������� �� �������
	bool isOperation(std::string&, size_t&);

	//���������� ������� � ����������� �� � ���� ��������
	void funcWrite(std::string&, size_t&, std::string&);

	//������� ������ � �����
	double numberparse(std::string&, size_t&);

	//����� ������� ��������
	void math(std::stack<double>&, std::stack<std::string>&);

#endif