#include <iostream>
#include <exception>

int ** matrix_input(size_t m, size_t n);
int ** concat_rows(const int * const * lhs, size_t m1, size_t n1, const int * const * rhs, size_t m2, size_t n2);
void matrix_output(int** matrix, size_t min_m, size_t m, size_t n, size_t n1, size_t n2);

int main() 
{
    int m_i = 0, n_i = 0;
    std::cin >> m_i >> n_i;
    if (std::cin.fail() || (m_i <= 0) || (n_i <= 0)) {
        std::cerr << "Код ошибки 1";
        return 1;
    }
    size_t m1 = size_t(m_i), n1 = size_t(n_i);
    try {
        const int * const * lhs = matrix_input(m1, n1);
        std::cin >> m_i >> n_i;
        if (std::cin.fail() || (m_i <= 0) || (n_i <= 0)) {
            std::cerr << "Код ошибки 1";
            return 1;
        }
        size_t m2 = size_t(m_i), n2 = size_t(n_i);
        const int * const * rhs = matrix_input(m2, n2);
        int ** new_matrix = concat_rows(lhs, m1, n2, rhs, m2, n2);
        size_t min_m = 0;
        size_t m = 0;
        size_t n = 0;
        if (m2 < m1){
            size_t min_m = m2;
            size_t m = m1;
            size_t n = n1;
        }
        else{
            size_t min_m = m1;
            size_t m = m2;
            size_t n = n2;
        }
        matrix_output(new_matrix, min_m, m, n, n1, n2);
    }
    catch (const std::logic_error& e) {
        std::cerr << "Код ошибки 1";
        return 1;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Код ошибки 2";
        return 2;
    }
    catch (const std::exception& e) {
        std::cerr << "Код оошибки 0";
        return 0;
    }
}

int ** matrix_input(size_t m, size_t n)
{
    int** matrix = new int*[m];
    for (size_t i = 0; i < m; i++) {
        try {
            matrix[i] = new int[n];
        }
        catch (const std::bad_alloc& e) {
            for (size_t k; k < i; k++) {
                delete[] matrix[k];
            }
            delete[] matrix;
            throw;
        }
    }
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
            if (std::cin.fail()) {
                for (size_t k; k < m; k++) {
                    delete[] matrix[k];
                }
                delete[] matrix;
                throw std::logic_error("Ошибка ввода");
            }
        }    
    }
    return matrix;
}

int ** concat_rows(const int * const * lhs, size_t m1, size_t n1, const int * const * rhs, size_t m2, size_t n2)
{
    size_t min_m = 0;
    size_t m = 0;
    size_t n = 0;
    const int * const * max_matr = lhs;
    if (m2 < m1){
        size_t min_m = m2;
        size_t m = m1;
        size_t n = n1;
        const int * const * max_matr = lhs;
    }
    else{
        size_t min_m = m1;
        size_t m = m2;
        size_t n = n2;
        const int * const * max_matr = rhs;
    }
    int ** new_matrix = new int * [m];
    for (size_t i = 0; i < min_m; i++) {
        try {
            new_matrix[i] = new int[n1+n2];
        }
        catch (const std::bad_alloc& e) {
            for (size_t k; k < i; k++) {
                delete[] new_matrix[k];
            }
            delete[] new_matrix;
            throw;
        }
    }
    for (size_t i = min_m; i < m; i++) {
        try {
            new_matrix[i] = new int[n];
        }
        catch (const std::bad_alloc& e) {
            for (size_t k; k < i; k++) {
                delete[] new_matrix[k];
            }
            delete[] new_matrix;
            throw;
        }
    }
    for (size_t i = 0; i < min_m; i++) {
        for (size_t j = 0; j < (n1+n2); j++) {
            if (j < n1){
                new_matrix[i][j] = lhs[i][j];
            }
            else{
                new_matrix[i][j] = rhs[i][j];
            }
            if (std::cin.fail()) {
                for (size_t k; k < m; k++) {
                    delete[] new_matrix[k];
                }
                delete[] new_matrix;
                throw std::logic_error("Ошибка ввода");
            }
        }    
    }
    for (size_t i = min_m; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            new_matrix[i][j] = max_matr[i][j];
            if (std::cin.fail()) {
                for (size_t k; k < m; k++) {
                    delete[] new_matrix[k];
                }
                delete[] new_matrix;
                throw std::logic_error("Ошибка ввода");
            }
        }    
    }
    return new_matrix;
}

void matrix_output(int** matrix, size_t min_m, size_t m, size_t n, size_t n1, size_t n2)
{
    for (size_t i = 0; i < min_m; i++) {
        for (size_t j = 0; j < (n1+n2); j++) {
            std::cout << matrix[i][j] << " ";
        }
    }
    for (size_t i = min_m; i < m; i++) {
        for (size_t j = 0; j < (n); j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
