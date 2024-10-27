#include <iostream> // консоль - cout
#include <vector>
//#include <algorithm>    // std::for_each
#include <variant>

// функция случайным образом вырасывающая: int, string, vector
static std::variant<int, std::string, std::vector<int>> get_variant()
{
	std::srand(std::time(nullptr));
	int random_variable = std::rand() % 3;

	std::variant<int, std::string, std::vector<int>> result;
	switch (random_variable)
	{
	case 0:
		result = 5;
		break;
	case 1:
		result = "string";
		break;
	case 2:
		result = std::vector<int>{ 1, 2, 3, 4, 5 };
		break;
	default:
		break;
	}
	return result;
}

// перегружаю оператор << для cout (чтобы выводить std::vector<int>)
static std::ostream& operator<< (std::ostream& out, const std::vector<int>& vect)
{
	for (const auto& val : vect) out << val << " ";
	return out;
}

// перегружаю оператор << для cout (чтобы выводить std::variant<int, std::string, std::vector<int>>)
static std::ostream& operator<< (std::ostream& out, const std::variant<int, std::string, std::vector<int>>& var)
{
	// visit определяет текущий индекс variant и отдает его лямбде
	std::visit( [&out](const auto& elem) { out << elem; }, var);
	return out;
}


// Если что, есть альтернативное решение задачи.Вы можете использовать паттерн Visitor
// и сделать класс, который выполняет разные действия в зависимости от того что есть в variant - е:
struct Visitor
{
	template<class T>
	void operator()(const T& elem) { std::cout << elem; }
	/*
	void operator()(const int a) { std::cout << a; }
	void operator()(const std::string& a) { std::cout << a; }
	void operator()(const std::vector<int>& a) { std::cout << a; }
	*/
};


int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");   // задаём русский текст
    system("chcp 1251");            // настраиваем кодировку консоли
    std::system("cls");

    std::cout   << "Задача 2. std::variant\n"
                << "----------------------\n" << std::endl;

	auto var = get_variant();		// получаю какой то variant
	// если это int -> умножаю на 2 (на мой взгляд, довольно коряво и не понятно)
	if (std::holds_alternative<int>(var)) std::get<int>(var) *= 2;
	std::cout << var << std::endl;	// вывожу в консоль

	std::visit(Visitor(), var);

    return 0;
}