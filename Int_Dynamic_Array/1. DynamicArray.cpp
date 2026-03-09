/*
Описание задачи
Что делает этот код?
Код реализует динамический массив целых чисел на C++ с ручным управлением памятью. 
Это учебный проект, демонстрирующий фундаментальные концепции программирования на C++:
- Динамическое управление памятью — использование new и delete для выделения/освобождения памяти
- Правило трёх (Rule of Three) — конструктор копирования, оператор присваивания, деструктор
- Инкапсуляция — скрытие деталей реализации за публичным интерфейсом
- Обработка ошибок — проверка выхода за границы массива
- Автоматическое расширение — массив увеличивается при переполнении

Основные возможности:
- Создание массива заданного размера
- Добавление элементов в конец (Push)
- Удаление последнего элемента (Pop)
- Доступ по индексу с проверкой границ (Get)
- Вывод содержимого (Print)
- Копирование массивов (глубокое копирование)
*/

#include <iostream>

class IntDynamicArray {
    int* data_;     // Указатель на динамический массив
    int size_;      // Размер массива (количество элементов)
    int capacity_;  // Вместимость массива (выделенная память)

    // Метод для увеличения массива при переполнении
    void Resize() {
        int newcapacity = capacity_ * 2;     // Увеличиваем вместимость в два раза
        int* newdata = new int[newcapacity];  // Выделяем новую память

        // Копируем старые данные в новый массив
        for (int i = 0; i < size_; ++i) {
            newdata[i] = data_[i];
        }

         // Освобождаем старую память
         delete[] data_;

        // // Обновляем указатель и вместимость
        data_ = newdata;
        capacity_ = newcapacity;

        std::cout << "Массив увеличен\n"; 
    }

  public:
    // Конструктор: создаёт массив заданного размера
    IntDynamicArray(int initialsize = 0) {
        if (initialsize < 0) {
            std::cout << "Ошибка: размер не может быть меньше нуля. Установлен размер 0\n";
            initialsize = 0;
        }
        size_ = initialsize;
        capacity_ = (initialsize > 0 ? initialsize : 1);  // Минимальная вместимость - 1
        data_ = new int[capacity_];

        // Инициализируем элементы нулями
        for (int i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
        std::cout << "Создан массив размером: " << size_ << "и вместимостью :" << capacity_ << '\n';
    }

    // Copy Constructor (Конструктор копирования)
    IntDynamicArray(const IntDynamicArray& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new int[capacity_];
        
        // Копируем данные из другого массива
        for (int i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
    }

    // Copy Assignment Operator (Оператор присваивания копированием)
    IntDynamicArray& operator=(const IntDynamicArray& other) {
        // Проверка на самоприсваивание
        if (this == &other) {
            std::cout << "Оператор присваивания: самоприсваивание, пропускаем\n";
            return *this;
        }
        std::cout << "Оператор присваивания: копируем данные из другого массива\n";
        
        // Освобождаем старую память
        delete[] data_;
        // Копируем размеры
        size_ = other.size_;
        capacity_ = other.capacity_;
        // Выделяем новую память
        data_ = new int[capacity_];

        // Копируем данные
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }
    
    // Деструктор: освобождаем память
    ~IntDynamicArray() {
        delete[] data_;
        std::cout << "Память освобождена\n";
    }

    // Добавляем элемент в конец
    void Push(int value) {
        if (size_ >= capacity_) {
            Resize();  // Проверяем, нужно ли увеличить массив
        }
        data_[size_] = value;
        ++size_;
        std::cout << "Добавлен элемент: " << value << '\n';
    }

    void Pop() {
        if (size_ <= 0) {
            std::cout << "Ошибка: массив пуст, невозможно удалить\n";
            return;
        }
        --size_;
        std::cout << "Удалён последний элемент\n";
    }

    // Получить элемент по индексу с проверкой границ
    int Get(int index) const {
        if (index < 0 || index >= size_) {
            std::cout << "Ошибка: индекс :" << index << " вне границ массива (0.. " << size_ - 1 << ")\n";
            return -1;  // Возвращаем специальное значение при ошибке
        }

        return data_[index];
    }

    // Вывести массив
    void Print() {
        std::cout << "Массив (size=" << size_ << ", capacity=" << capacity_ << "): [";

        for (int i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }

    // Получить текущий размер
    int GetSize() const {
        return size_;
    }

    //  Получить текущую вместимость
    int GetCapacity() const {
        return capacity_;
    }
};


// Пример использования в основной программе
int main() {
    // 1. Создаём массив
    std::cout << "1. Создание массива:\n";
    IntDynamicArray arr1(3);
    arr1.Push(10);
    arr1.Push(20);
    arr1.Push(30);
    arr1.Print();
    std::cout << "\n";
    
    // 2. Тестирование конструктора копирования
    std::cout << "2. Тестирование конструктора копирования:\n";
    IntDynamicArray arr2 = arr1;  // Вызов copy constructor
    arr2.Print();
    std::cout << "\n";
    
    // 3. Тестирование оператора присваивания
    std::cout << "3. Тестирование оператора присваивания:\n";
    IntDynamicArray arr3(2);
    arr3.Push(100);
    arr3.Push(200);
    std::cout << "arr3 до присваивания: ";
    arr3.Print();
    
    arr3 = arr1;  // Вызов copy assignment operator
    std::cout << "arr3 после присваивания: ";
    arr3.Print();
    std::cout << "\n";
    
    // 4. Проверка независимости копий
    std::cout << "4. Проверка независимости копий:\n";
    arr1.Push(40);
    std::cout << "arr1 после изменения: ";
    arr1.Print();
    std::cout << "arr2 (копия) осталась без изменений: ";
    arr2.Print();
    std::cout << "\n";
    
    return 0;
}