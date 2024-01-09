import Dynamic_Structures;
#include <iostream>
using namespace Dynamic_Structures;
// Функция, демонстрирующая работу со стеками, унаследованными от базового класса
template <typename T>
void demonstrateAbstractStructure(AbstractClassStack<T>& structure, const std::initializer_list<T>& elements) {
    std::cout << "Добавление элементов в структуру: ";
    for (const auto& element : elements) {
        structure.Push(element);
        std::cout << element << "  ";
    }
    std::cout << "\n";

    std::cout << "Размер структуры: " << structure.GetSize() << "\n";

    T topElement;
    if (structure.Peek(topElement)) {
        std::cout << "Верхний элемент: " << topElement << "\n";
    }

    std::cout << "Извлечение элементов из структуры: ";
    while (structure.GetSize() > 0) {
        structure.Peek(topElement);
        std::cout << topElement << "  ";
        structure.Pop(topElement);
    }
    std::cout << "\n";
};


int main() {

    std::cout << "\n" << "Стек на основе однонаправленного списка" << "\n";
    Dynamic_Structures::StackBasedOnUnidirectionalLinkedList<int> intStack;
    demonstrateAbstractStructure(intStack, { 1, 2, 3, 4, 5});

    std::cout << "\n" <<"Стек на основе двунаправленного циклического списка" << "\n";
    Dynamic_Structures::StackBasedOnUnidirectionalLinkedList<double> doubleStack;
    demonstrateAbstractStructure(doubleStack, { 1.1, 2.2, 3.3, 4.4, 5.5 });

	return 0;
}