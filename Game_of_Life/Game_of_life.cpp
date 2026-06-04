/*
«Игра "Жизнь"»
Упрощённая консольная реализация игры «Жизнь», придуманная английским математиком Джоном Конвеем в 1970 году.

Содержание
1. Правила игры
- Место действия игры — Вселенная. Это размеченная на клетки ограниченная плоскость.
- Каждая клетка на этой плоскости может находиться в двух состояниях: быть «живой», то есть заполненной, или быть «мёртвой», то есть пустой. 
- Клетка имеет восемь соседей, окружающих её. 
- Распределение живых клеток в начале игры называется первым поколением. 

Каждое следующее поколение рассчитывается на основе предыдущего по правилам:
1.	В пустой (мёртвой) клетке, рядом с которой ровно три живых клетки, зарождается жизнь.
2.	Если у живой клетки есть две или три живых соседки, то эта клетка продолжает жить. 
    В противном случае, если соседей меньше двух или больше трёх, клетка умирает «от одиночества» или «от перенаселённости».

Игра прекращается, если:
•	на поле не останется ни одной «живой» клетки;
•	при очередном шаге ни одна из клеток не меняет своего состояния, то есть складывается стабильная конфигурация.
Игрок не принимает прямого участия в игре, а только расставляет начальную конфигурацию «живых» клеток, которые затем взаимодействуют согласно правилам уже без его участия. 
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <unistd.h>


// Создадим структуру поля - вселенной
struct Field {
  int rows;      // строки
  int cols;      // столбцы
  char** cells;  // массив
};

// Функция создания дмумерного массива
void CreatWorld2D(Field& field) {
  field.cells = new char*[field.rows];
  
  for (int i = 0; i < field.rows; ++i) {
    field.cells[i] = new char[field.cols];
  }
}

// Функция заполнения массива мёртвыми клетками '-'
void FillWorld2D(Field& field) {
  for (int i = 0; i < field.rows; ++i) {
    for (int j = 0; j < field.cols; ++j) {
      field.cells[i][j] = '-';
    }
  }
}

// Функция удаления массива
void DeleteWorld2D(Field& field) {
  for (int i = 0; i < field.rows; ++i) {
    delete[] field.cells[i];
  }
  delete[] field.cells;
  
  field.cells = nullptr;
}

// Функция вывода массива на экран
void PrintField2D(const Field& field) {
  for (int i = 0; i < field.rows; ++i) {
    for (int j = 0; j < field.cols; ++j) {
      std::cout << std::setw(2) << field.cells[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

// Функция загрузки поля из файла
void LoadFieldFromFile(const std::string& file, Field& field) {  
  std::ifstream file_name(file);
  
  if (!file_name.is_open()) {
    std::cout << "Файл не найден. Поверьте расположение файла и внестите его адрес в первый аргумент функции\n";
    return;
  }
    file_name >> field.rows >> field.cols;

    CreatWorld2D(field);

    FillWorld2D(field);

    // Координаты живых клеток
    int row = 0;
    int col = 0;

    while (file_name >> row >> col) {
      field.cells[row][col] = '*';
    }
}

// Функция подсчета соседей
int CountNeighbours(const Field& field, int row, int col) {
  int count = 0;
  // Перебираем все 9 позиций вокруг клетки
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      
      // Пропускаем саму клетку, ведь мы ищем соседей
      if (i == 0 && j == 0) {
        continue;
      }

      int new_row = row + i;
      int new_col = col + j;

      // Проверяем выход за границы поля
      if (new_row >= 0 && new_row < field.rows && new_col >= 0 && new_col < field.cols) {
        if (field.cells[new_row][new_col] == '*') {
          ++count;
        }
      }
    }
  }
  return count;
}

// Функция определения нового состояния клетки. 
// Живая клетка с 2 или 3 соседями остается жить. Иначе умирает. Мёртвая клетка с 3 соседями оживает.
char GetNextCellStatus(const Field& field, int row, int col) {
  int neighbours = CountNeighbours(field, row, col);

  // Если клетка живая
  if (field.cells[row][col] == '*') {
    if (neighbours == 2 || neighbours == 3) {
      return '*';
    }
    return '-';
  }
  // Если клетка мертвая
  if (neighbours == 3) {
    return '*';
  }
  return '-';
}

// Функция заполнения массива следующего поколения, вызывая GetNextCellStatus для каждой клетки
void CreateNextGeneration(const Field& current, Field& next) {
  for (int row = 0; row < current.rows; ++row) {
    for (int col = 0; col < current.cols; ++col) {
      next.cells[row][col] = GetNextCellStatus(current, row, col);
    }
  }
}

// Функция проверяет одинаковые ли поколения
bool CompareFields(const Field& first, const Field& second) {
  if (first.rows != second.rows || first.cols != second.cols) {
    return false;
  }
  for (int row = 0; row < first.rows; ++row) {
    for (int col = 0; col < first.cols; ++col) {
      if (first.cells[row][col] != second.cells[row][col]) {
        return false;
      }
    }
  }
  return true;
}

// Функция подсчета живых клеток
int CountLiveCells(const Field& field) {
  int count = 0;
  for (int i = 0; i < field.rows; ++i) {
    for (int j = 0; j < field.cols; ++j) {
      if (field.cells[i][j] == '*') {
        ++count;
      }
    }
  }
  return count;
}

// Функция копирования полей
void ChangeField(Field& current, Field& next) {
  char** temp = current.cells;
  current.cells = next.cells;
  next.cells = temp;
}


int main() {
  std::system("clear");
  // Создадим текущий мир и мир следующего поколения
  Field current_universe;
  Field next_universe;
  LoadFieldFromFile("input.txt", current_universe);

  // Копируем размеры поля (мира) текущего в следующий
  next_universe.rows = current_universe.rows;
  next_universe.cols = current_universe.cols;

  CreatWorld2D(next_universe);
  FillWorld2D(next_universe);

  int generation = 0;

  while (true) {
    std::cout << "Generation: " << generation << '\n';
    std::cout << "Alive cells: " << CountLiveCells(current_universe) << "\n\n";

    PrintField2D(current_universe);
    std::cout << '\n';

    CreateNextGeneration(current_universe, next_universe);

    if (CountLiveCells(next_universe) == 0) {
      std::cout << "Game over: no living cells.\n";
      break;
    }
    if (CompareFields(current_universe, next_universe)) {
      std::cout << "Game over: stable configuration.\n";
      break;
    }
    ChangeField(current_universe, next_universe);
    ++generation;

    sleep(1);
  }
  DeleteWorld2D(next_universe);
  DeleteWorld2D(current_universe);

  return 0;
}