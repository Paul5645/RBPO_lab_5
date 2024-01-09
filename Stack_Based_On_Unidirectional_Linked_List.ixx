

module;
#include <iostream>
#include <new>
export module Dynamic_Structures: Stack_Based_On_Unidirectional_Linked_List;

import :Abstract_Class_Stack;
export namespace Dynamic_Structures
{
    // Класс для динамической структуры данных (стек на основе однонаправленного списка)
    template <typename T>
    class StackBasedOnUnidirectionalLinkedList : public AbstractClassStack<T> {

        // Встроенный класс Node
        template <typename T>
        class Node {
        public:
            T data;
            Node* next;

            Node(T data = T(), Node* next = nullptr)
                : data(data), next(next) {}
        };

        Node<T>* head; // Указатель на первый элемент (дно стека)
        Node<T>* top;  // Указатель на последний элемент (вершина стека)
        int size; // Размер стека

    public:

        int GetSize() const override {
            return size;
        };

        // Функция очистки стека
        void clear();

        // Функция добавления элемента в вершину стека
        bool Push(const T& element) override;

        // Функция удаления элемента из вершины стека
        bool Pop(T& element) override;

        bool Peek(T& element) const override;

        // Конструктор по умолчанию
        StackBasedOnUnidirectionalLinkedList();

        // Конструктор копирования
        StackBasedOnUnidirectionalLinkedList(const StackBasedOnUnidirectionalLinkedList<T>& other);

        // Конструктор перемещения
        StackBasedOnUnidirectionalLinkedList(StackBasedOnUnidirectionalLinkedList<T>&& other);

        // Конструктор, принимающий на вход std::initializer_list
        StackBasedOnUnidirectionalLinkedList(std::initializer_list<T> ilist);

        // Деструктор
        ~StackBasedOnUnidirectionalLinkedList() override;

        // Переопределение оператора присваивания (копирования)
        StackBasedOnUnidirectionalLinkedList<T>& operator=(const StackBasedOnUnidirectionalLinkedList<T>& other);

        // Переопределение оператора присваивания (перемещение)
        StackBasedOnUnidirectionalLinkedList<T>& operator=(StackBasedOnUnidirectionalLinkedList<T>&& other);

        // Переопределение оператора присваивания (с использованием initializer_list)
        StackBasedOnUnidirectionalLinkedList<T>& operator=(std::initializer_list<T> ilist);

        // Переопределение операции потока вывода 
        friend std::ostream& operator<<(std::ostream& os, const StackBasedOnUnidirectionalLinkedList<T>& stack);
    };

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>::StackBasedOnUnidirectionalLinkedList() : head(nullptr), top(nullptr), size(0) {}

    template <typename T>
    StackBasedOnUnidirectionalLinkedList<T>::StackBasedOnUnidirectionalLinkedList(const StackBasedOnUnidirectionalLinkedList<T>& other) : head(nullptr), top(nullptr), size(0) {
        *this = other;  // Используем оператор присваивания
    }

    template <typename T>
    StackBasedOnUnidirectionalLinkedList<T>::StackBasedOnUnidirectionalLinkedList(StackBasedOnUnidirectionalLinkedList<T>&& other) : head(nullptr), top(nullptr), size(0) {
        *this = std::move(other);  // Используем оператор присваивания перемещения
    }

    template <typename T>
    StackBasedOnUnidirectionalLinkedList<T>::StackBasedOnUnidirectionalLinkedList(std::initializer_list<T> ilist) : head(nullptr), top(nullptr), size(0) {
        *this = ilist;  // Используем оператор присваивания
    }

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>::~StackBasedOnUnidirectionalLinkedList() {
        clear();  // Очищаем список, используя функцию clear
    }

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>& StackBasedOnUnidirectionalLinkedList<T>::operator=(const StackBasedOnUnidirectionalLinkedList<T>& other) {
        // Защита от самоприсваивания
        if (this != &other) {
            // Очищаем текущий список
            clear();

            // Проверяем, не пуст ли исходный список
            if (other.head != nullptr) {
                // Создаем новый узел для копирования
                Node<T>* newNode = new Node<T>(other.head->data);
                head = newNode;  // Устанавливаем начало списка
                top = newNode;   // Устанавливаем вершину стека
                size = 1;        // Размер списка увеличивается на 1

                // Копируем оставшиеся элементы из исходного списка
                Node<T>* currentOther = other.head->next;
                while (currentOther != nullptr) {
                    newNode->next = new Node<T>(currentOther->data);
                    newNode = newNode->next;
                    currentOther = currentOther->next;
                    ++size;
                }
            }
        }

        return *this;
    }

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>& StackBasedOnUnidirectionalLinkedList<T>::operator=(StackBasedOnUnidirectionalLinkedList<T>&& other) {
        if (this != &other) {  // Защита от самоприсваивания
            clear();  // Очищаем текущий список

            // Перемещаем данные из other в текущий объект
            head = other.head;
            top = other.top;
            size = other.size;

            // Оставляем other в валидном, но пустом состоянии
            other.head = nullptr;
            other.top = nullptr;
            other.size = 0;
        }

        return *this;
    }

    template<typename T>
    StackBasedOnUnidirectionalLinkedList<T>& StackBasedOnUnidirectionalLinkedList<T>::operator=(std::initializer_list<T> ilist) {
        clear();  // Очистка текущего списка

        // Добавление каждого элемента из списка инициализации
        for (const T& item : ilist) {
            Push(item);
        }

        return *this;  // Возвращение ссылки на текущий объект
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const StackBasedOnUnidirectionalLinkedList<T>& stack) {
        typename StackBasedOnUnidirectionalLinkedList<T>::Node* current = stack.head;

        os << "[";
        while (current != nullptr) {
            os << current->data;
            current = current->next;
            if (current != nullptr) {
                os << ", ";
            }
        }
        os << "]";

        return os;
    }

    template<typename T>
    void StackBasedOnUnidirectionalLinkedList<T>::clear() {
        Node<T>* currentNode = head;
        while (currentNode != nullptr) {
            Node<T>* nextNode = currentNode->next; // Сохраняем ссылку на следующий элемент
            delete currentNode; // Удаляем текущий узел
            currentNode = nextNode; // Переходим к следующему узлу
        }

        top = nullptr; // Обнуляем указатель на вершину стека
        size = 0; // Сбрасываем размер стека
    }

    template<typename T>
    bool StackBasedOnUnidirectionalLinkedList<T>::Push(const T& element) {
        // Создаем новый узел
        Node<T>* newNode = new(std::nothrow) Node<T>(element);

        // Проверяем, был ли узел успешно создан
        if (newNode == nullptr) {
            // Не удалось выделить память
            return false;
        }

        // Если стек пуст, новый узел становится и вершиной, и дном стека
        if (head == nullptr) {
            head = newNode;    
        }
        else {
            // Вставляем новый узел в конец списка
            top->next = newNode;
        }

        top = newNode;// Новый узел становится вершиной стека
        ++size;
        return true;
    }

    template<typename T>
    bool StackBasedOnUnidirectionalLinkedList<T>::Pop(T& element) {
        // Проверяем, пуст ли стек
        if (head == nullptr) {
            // Стек пуст
            return false;
        }

        // Сохраняем данные верхнего элемента
        element = top->data;

        // Удаление верхнего элемента
        Node<T>* toDelete = top;

        // Если в стеке остался только один элемент
        if (head == top) {
            head = nullptr;
            top = nullptr;
        }
        else {
            // В стеке более одного элемента
            Node<T>* currentNode = head;
            while (currentNode->next != top) {
                currentNode = currentNode->next;
            }
            currentNode->next = nullptr;
            top = currentNode;  // Обновляем top
        }

        delete toDelete;  // Удаляем элемент
        --size;           // Уменьшаем размер стека
        return true;
    }

    template<typename T>
    bool StackBasedOnUnidirectionalLinkedList<T>::Peek(T& element) const {
        // Проверяем, пуст ли стек
        if (head == nullptr) {
            // Стек пуст
            return false;
        }

        // Копируем данные верхнего элемента
        element = top->data;

        return true;
    }
}