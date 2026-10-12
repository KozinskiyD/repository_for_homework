#include <iostream>
#include <stdexcept>

int** delete_matrix(int** matrix, int rows) {
    if (matrix == nullptr) {
        return nullptr;
    }

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return nullptr;
}

int** create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("rows and cols должны быть больше нуля");
    }

    int** matrix = new int*[rows]{};

    try {
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols];
        }
    } catch (const std::exception&) {
        delete_matrix(matrix, rows);
        throw;
    }

    return matrix;
}

int main() {
    int rows = 0, cols = 0;

    int** matrix = nullptr;
    int** transposed = nullptr;

    try {
        if (!(std::cin >> rows >> cols)) {
            throw std::runtime_error("Ошибка ввода rows и cols матрицы");
        }

        matrix = create_matrix(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!(std::cin >> matrix[i][j])) {
                    throw std::runtime_error("Ошибка ввода элементов матрицы");
                }
            }
        }

        transposed = create_matrix(cols, rows);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                transposed[j][i] = matrix[i][j];
            }
        }

        std::cout << '\n';
        std::cout << "Транспонированная матрица: \n";
        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                std::cout << transposed[i][j] << ' ';
            }
            std::cout << '\n';
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Не удалось ввести матрицу" << e.what() << '\n';
        delete_matrix(matrix, rows);
        delete_matrix(transposed, cols);
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: Не удалось ввести матрицу" << e.what() << '\n';
        delete_matrix(matrix, rows);
        delete_matrix(transposed, cols);
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: Не удалось выделить память" << e.what() << '\n';
        delete_matrix(matrix, rows);
        delete_matrix(transposed, cols);
        return 2;
    }

    delete_matrix(matrix, rows);
    delete_matrix(transposed, cols);

    return 0;
}
