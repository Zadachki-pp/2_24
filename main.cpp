#include <iostream>


class Matrix {
    size_t _n_size;
    size_t _m_size;
    double** matrix;

public:
    Matrix(size_t n, size_t m) {
        _n_size = n;
        _m_size = m;

        matrix = new double*[_n_size];
        for (size_t i = 0; i < _n_size; ++i) {
            matrix[i] = new double[_m_size];
        }
    }

    Matrix(const Matrix& other) {
        _n_size = other._n_size;
        _m_size = other._m_size;

        matrix = new double*[_n_size];
        for (size_t i = 0; i < _n_size; ++i) {
            matrix[i] = new double[_m_size];
        }

        for (size_t i = 0; i < _n_size; ++i) {
            for (size_t j = 0; j < _m_size; ++j) {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (other._n_size != _n_size || other._m_size != _m_size) {
            std::cerr << "Cannot assign matrices of different dimensions" << std::endl;
            exit(1);
        }

        for (size_t i = 0; i < _n_size; ++i) {
            for (size_t j = 0; j < _m_size; ++j) {
                matrix[i][j] = other.matrix[i][j];
            }
        }

        return *this;
    }

    ~Matrix() {
        for (size_t i = 0; i < _n_size; ++i){
            delete[] matrix[i];
        }
        delete matrix;
    }

    void print() {
        for (size_t i = 0; i < _n_size; ++i){
            for (size_t j = 0; j < _m_size; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void randomize() {
        for (size_t i = 0; i < _n_size; ++i) {
            for (size_t j = 0; j < _m_size; ++j) {
                matrix[i][j] = (rand() % 9) + 1;
            }
        }
    }
};


// Like Matrix, BUT BETTER!
class SuperMatrix {
    size_t _n_size;
    size_t _m_size;
    double** matrix;

    void _copy_matrix_from_other(double** other) {
        for (size_t i = 0; i < _n_size; ++i) {
            for (size_t j = 0; j < _m_size; ++j) {
                matrix[i][j] = other[i][j];
            }
        }
    }

public:
    SuperMatrix(size_t n, size_t m) {
        _n_size = n;
        _m_size = m;

        matrix = new double*[_n_size];
        for (size_t i = 0; i < _n_size; ++i) {
            matrix[i] = new double[_m_size];
        }
    }

    SuperMatrix(const SuperMatrix& other) : SuperMatrix(other._n_size, other._m_size) {
        _copy_matrix_from_other(other.matrix);
    }

    SuperMatrix& operator=(const SuperMatrix& other) {
        if (this == &other) {
            return *this;
        }
        if (other._n_size != _n_size || other._m_size != _m_size) {
            std::cerr << "Cannot assign matrices of different dimensions" << std::endl;
            exit(1);
        }

        _copy_matrix_from_other(other.matrix);

        return *this;
    }

    ~SuperMatrix() {
        for (size_t i = 0; i < _n_size; ++i){
            delete[] matrix[i];
        }
        delete matrix;
    }

    void print() {
        for (size_t i = 0; i < _n_size; ++i){
            for (size_t j = 0; j < _m_size; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void randomize() {
        for (size_t i = 0; i < _n_size; ++i) {
            for (size_t j = 0; j < _m_size; ++j) {
                matrix[i][j] = (rand() % 9) + 1;
            }
        }
    }
};

int main() {
    std::cout << "*Create*" << std::endl;
    SuperMatrix m_1(2, 2);
    SuperMatrix m_2(3, 3);

    m_1.randomize();
    m_2.randomize();


    std::cout << "*Print*" << std::endl;
    m_1.print();
    m_2.print();


    std::cout << "*Copy construct*" << std::endl;
    SuperMatrix m_3 = m_1;

    m_1.print();
    m_3.print();


    std::cout << "*Operator =*" << std::endl;
    m_3.randomize();

    m_1.print();
    m_3.print();

    // m_3 = m_2;  ERROR
    m_3 = m_1 = m_3;

    m_1.print();
    m_3.print();


    std::cout << "*Destruct*" << std::endl;
    return 0;
}
