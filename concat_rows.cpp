#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <limits>

int** concat_rows(const int* const* lhs, size_t n1, size_t m1, 
                  const int* const* rhs, size_t n2, size_t m2) {
    if (lhs == nullptr || rhs == nullptr) {
        throw std::invalid_argument("Error: Array is empty");
    }

    size_t max_n = 0;
    if (n1 >= n2) {
        max_n = n1;
    } else {
        max_n = n2;
    }
    
    int** result = nullptr;
    size_t loc_rows = 0; 

    try {
        result = new int*[max_n];

        for (size_t i = 0; i < max_n; i++) {
            size_t m3 = 0;
            
            if (i < n1) {
                if (m1 > std::numeric_limits<size_t>::max() - m3) {
                    throw std::overflow_error("Error: overflow m1 + m2");
                }
                m3 += m1;
            }
            if (i < n2) {
                if (m2 > std::numeric_limits<size_t>::max() - m3) {
                    throw std::overflow_error("Error: overflow m1 + m2");
                }
                m3 += m2;
            }

            result[i] = new int[m3];
            loc_rows++; 

            size_t k = 0;
            if (i < n1) {
                for (size_t j = 0; j < m1; j++) {
                    result[i][k] = lhs[i][j];
                    k++; 
                }
            }
            if (i < n2) {
                for (size_t j = 0; j < m2; j++) {
                    result[i][k] = rhs[i][j]; 
                    k++; 
                }
            }
        }
    } catch (const std::bad_alloc&) {
        for (size_t i = 0; i < loc_rows; i++) {
            delete[] result[i];
        }
        delete[] result; 
        
        throw std::runtime_error("Error: memory allocation");
        
    } catch (const std::overflow_error& e) {
        for (size_t i = 0; i < loc_rows; i++) {
            delete[] result[i];
        }
        delete[] result;
        
        throw std::runtime_error(e.what());
    }

    return result;
}

void del_matrix(int** arr, size_t n) {
    if (arr != nullptr) {
        for (size_t i = 0; i < n; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
}

int main() {
    size_t n1 = 0, m1 = 0;
    size_t n2 = 0, m2 = 0;
    size_t max_n = 0;


    std::cout << "Введите размерность 1ой матрицы n1 x m1\n";
    if (!(std::cin >> n1 >> m1)) {
        std::cerr << "Error: invalid input";
        return 1;
    } else if (n1 == 0 && m1 == 0) {
        std::cerr << "Error: n1 & m1 are zero values";
    }

    std::cout << "Введите размерность 2ой матрицы n2 x m2\n";
    if (!(std::cin >> n2 >> m2)) {
        std::cerr << "Error: invalid input";
        return 1;
    } else if (n2 == 0 && m2 == 0) {
        std::cerr << "Error: n2 & m2 are zero values";
    }

    if (n1 >= n2) {
        max_n = n1;
    } else {
        max_n = n2;
    }

    int** lhs = nullptr;
    int** rhs = nullptr;
    int** result = nullptr;
    
    size_t lhs_located = 0;
    size_t rhs_located = 0;

    try {
        std::cout << "Матрица 1\n";
        lhs = new int*[n1]; 
        for (size_t i = 0; i < n1; i++) {
            lhs[i] = new int[m1];
            lhs_located++; 
            for (size_t j = 0; j < m1; j++) {
                if (!(std::cin >> lhs[i][j])) {
                    std::cerr << "Error: invalid input";
                    del_matrix(lhs, lhs_located); 
                    return 1;
                }
            }
        }

        std::cout << "Матрица 2\n";
        rhs = new int*[n2]; 
        for (size_t i = 0; i < n2; i++) {
            rhs[i] = new int[m2];
            rhs_located++; 
            for (size_t j = 0; j < m2; j++) {
                if (!(std::cin >> rhs[i][j])) {
                    std::cerr << "Error: invalid input";
                    del_matrix(lhs, lhs_located);
                    del_matrix(rhs, rhs_located);
                    return 1;
                }
            }
        }

        result = concat_rows(lhs, n1, m1, rhs, n2, m2);

        std::cout << "Результат соединения:\n";
        for (size_t i = 0; i < max_n; i++) {
            size_t m3 = 0;
            if (i < n1) m3 += m1;
            if (i < n2) m3 += m2;

            for (size_t j = 0; j < m3; j++) {
                std::cout << result[i][j] << " ";
            }
            std::cout << '\n';
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        
        del_matrix(lhs, lhs_located);
        del_matrix(rhs, rhs_located);
        del_matrix(result, max_n); 
        return 2;
    }

    del_matrix(lhs, lhs_located);
    del_matrix(rhs, rhs_located);
    del_matrix(result, max_n);

    return 0;
}
