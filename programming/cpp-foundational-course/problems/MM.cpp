// C++ foundational course, MIPT, 2021-2022

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>

template <typename T> class Matrix {
private:   /*  class attributes  */
    std::size_t rows_, columns_;
    T **matrix_;

public:    /*  constructors  */
    Matrix(std::size_t rows = 0, std::size_t columns = 0)
        : rows_{rows}, columns_{columns} {
        this->matrix_ = new T*[rows];
        for (std::size_t i{}; i < rows; ++i)
            matrix_[i] = new T[columns]{};
    }
    Matrix(Matrix &&other)
        : rows_(other.rows_), columns_(other.columns_), matrix_(other.matrix_) {
        other.matrix_ = nullptr;
        other.columns_ = 0; other.rows_ = 0;
    }
    Matrix(const Matrix &) = delete;
    
          /*   destructor  */
    ~Matrix() {
        for (std::size_t i{}; i < this->rows_; ++i)
            delete[] this->matrix_[i];
        delete[] this->matrix_;
    }

private:   /*  private methods  */
    T **allocate_matrix(std::size_t rows = 0, std::size_t columns = 0) {
        T **matrix = new T*[rows];
        for (std::size_t i{}; i < rows; ++i)
            matrix_[i] = new T[columns]{};
        return matrix;
    }
public:    /*  other methods  */
    void fill(T value) {
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j)
                this->matrix_[i][j] = value;
    }

    void transpose() {}

    void swap_rows(std::size_t row1, std::size_t row2) {}
    void swap_columns(std::size_t column1, std::size_t column2) {}

    bool is_square() { return this->rows_ == this->columns_; }
    bool is_symmetric() {
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j) {
                // todo!();
            }

        return true;
    }

    std::string to_string() const {
        std::string str{};
        
        for (std::size_t i{}; i < this->rows_; ++i) {
            for (std::size_t j{}; j < this->columns_; ++j) {
                std::string value = std::to_string(this->matrix_[i][j]);
                if (j == this->columns_ - 1) str += value + '\n';
                else str += value + ' ';
            }
        }

        return str;
    } 

public:    /*  operators  */
    Matrix &operator=(const Matrix &) = delete;
    Matrix &operator=(Matrix &&other) noexcept {
        if (this != &other) {
            for (std::size_t i{}; i < this->rows_; ++i)
                delete[] this->matrix_[i];
            delete[] this->matrix_;
        
            this->rows_ = other.rows_; this->columns_ = other.columns_;
            this->matrix_ = other.matrix_;

            other.rows_ = 0; other.columns_ = 0;
            other.matrix_ = nullptr;
        }
        return *this;
    }
    
    T *operator[](std::size_t idx) { return this->matrix_[idx]; }
    const T *operator[](std::size_t idx) const { return this->matrix_[idx]; }
    
    Matrix operator+(const Matrix &other) const {
        if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
            throw std::invalid_argument("Rows and columns of both matrices must be the same.");
        
        Matrix<T> m = Matrix(this->rows_, this->columns_);
        for (std::size_t i = 0; i < this->rows_; ++i)
            for (std::size_t j = 0; j < this->columns_; ++j) 
                m[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    
        return m;
    }
    
    Matrix &operator+=(const Matrix &other) {
        if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
            throw std::invalid_argument("Rows and columns of both matrices must be the same.");
        
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j) 
                this->matrix_[i][j] += other.matrix_[i][j];

        return *this;
    }
    
    Matrix operator-(const Matrix &other) const {
        if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
            throw std::invalid_argument("Rows and columns of both matrices must be the same.");
        
        Matrix<T> m = Matrix(this->rows_, this->columns_);
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j) 
                m[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
    
        return m;
    }
    
    Matrix &operator-=(const Matrix &other) {
        if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
            throw std::invalid_argument("Rows and columns of both matrices must be the same.");
        
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j) 
                this->matrix_[i][j] -= other.matrix_[i][j];

        return *this;
    }
    
    Matrix operator*(const Matrix &other) {
        if (this->columns_ != other.rows_)
            throw std::invalid_argument("Numbers of columns in matrix A must be the same as the number of rows in matrix B!");

        std::size_t rows = this->rows_, columns = other.columns_;
        Matrix<T> m = Matrix(rows, columns);
   
        for (std::size_t i{}; i < m.rows_; ++i) {
            for (std::size_t j{}; j < m.columns_; ++j) {
                T dot_prod{};
                
                for (std::size_t k{}; k < this->columns_; ++k)
                    dot_prod += this->matrix_[i][k] * other.matrix_[k][j];

                m[i][j] = dot_prod;
            }
        }         

        return m;
    }

    const bool operator==(const Matrix &other) {
        if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
            return false;
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j)
                if (this->matrix_[i][j] != other.matrix_[i][j])
                    return false;
        return true;
    }

public:    /*  getters & setters  */
    const std::size_t rows() const { return this->rows_; }
    const std::size_t columns() const { return this->columns_; }
};

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Matrix, AdditionNoExceptions) {
    Matrix<double> m1 = Matrix<double>(2, 2);
    Matrix<double> m2 = Matrix<double>(2, 2);

    for (std::size_t i{}; i < m1.rows(); ++i)
        for (std::size_t j{}; j < m1.columns(); ++j)
            m1[i][j] = m2[i][j] = i * j;

    Matrix<double> m3 = m1 + m2;
    for (std::size_t i{}; i < m1.rows(); ++i)
        for (std::size_t j{}; j < m1.columns(); ++j) {
            EXPECT_EQ(m3[i][j], 2 * i * j);
        }

    m1 += m2;
    for (std::size_t i{}; i < m1.rows(); ++i)
        for (std::size_t j{}; j < m1.columns(); ++j) {
            EXPECT_EQ(m1[i][j], 2 * i * j);
        }
}

TEST(Matrix, AdditionThrowExceptions) {
    Matrix<double> m1 = Matrix<double>(2, 2);
    Matrix<double> m2 = Matrix<double>(2, 3);
   
    EXPECT_THROW(m1 += m2, std::invalid_argument);

    Matrix<double> m3 = Matrix<double>(1, 1);
    EXPECT_THROW(m3 = m1 + m2, std::invalid_argument);
}

TEST(Matrix, ToString) {
    Matrix<std::uint8_t> m = Matrix<std::uint8_t>(2, 1);
    std::string m_to_str = m.to_string();
    std::string expected = "0\n0\n"; 
    EXPECT_EQ(m_to_str, expected);
}

TEST(MATRIX, DotProductNoExceptions) {
    Matrix<int> m1 = Matrix<int>(2, 2), m2 = Matrix<int>(2, 1);
    m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3; m1[1][1] = 4;
    m2[0][0] = 1; m2[1][0] = 2;

    Matrix<int> m3 = m1 * m2;
 
    EXPECT_NO_THROW(m3 = m1 * m2);
    
    EXPECT_EQ(m3[0][0], 5);
    EXPECT_EQ(m3[1][0], 11);

}

TEST(Matrix, SameMatrices) {
    Matrix<int> m1 = Matrix<int>(2, 2), m2 = Matrix<int>(2, 2);
    for (std::size_t i{}; i < m1.rows(); ++i)
       for (std::size_t j{}; j < m1.columns(); ++j)
            m1[i][j] = m2[i][j] = i * j;
    EXPECT_TRUE(m1 == m2);
}
