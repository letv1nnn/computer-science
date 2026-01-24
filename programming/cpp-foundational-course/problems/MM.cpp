// C++ foundational course, MIPT, 2021-2022

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>

template <typename T> class Matrix {
private:   /*  class attributes  */
    std::size_t rows_, columns_;
    T **matrix_;

public:    /*  constructors  */
    Matrix(std::size_t rows = 0, std::size_t columns = 0)
        : rows_{rows}, columns_{columns}, matrix_(allocate_matrix(rows, columns)) {}
    Matrix(Matrix &&other)
        : rows_(other.rows_), columns_(other.columns_), matrix_(other.matrix_) {
        other.matrix_ = nullptr;
        other.columns_ = 0; other.rows_ = 0;
    }
    Matrix(const Matrix &other) 
        : rows_(other.rows_), columns_(other.columns_), matrix_(allocate_matrix(other.rows_, other.columns_)) {
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j)
                this->matrix_[i][j] = other[i][j];
    }
          /*   destructor  */
    ~Matrix() {
        if (!this->matrix_) return;
        for (std::size_t i{}; i < this->rows_; ++i)
            delete[] this->matrix_[i];
        delete[] this->matrix_;
    }

private:   /*  private methods  */
    T **allocate_matrix(std::size_t rows = 0, std::size_t columns = 0) const {
        T **matrix = new T*[rows];
        for (std::size_t i{}; i < rows; ++i)
            matrix[i] = new T[columns]{};
        return matrix;
    }
public:    /*  other methods  */
    void fill(T value) {
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j)
                this->matrix_[i][j] = value;
    }

    Matrix transpose() const {
        std::size_t rows = this->columns_, columns = this->rows_;
        Matrix<T> m = Matrix<T>(rows, columns);
        
        for (std::size_t i{}; i < rows; ++i)
            for (std::size_t j{}; j < columns; ++j)
                m[i][j] = this->matrix_[j][i];

        return m;
    }

    void transpose() {
        std::size_t rows = this->columns_, columns = this->rows_;
        Matrix<T> m(rows, columns);
        
        for (std::size_t i{}; i < rows; ++i)
            for (std::size_t j{}; j < columns; ++j)
                m[i][j] = this->matrix_[j][i];

        *this = std::move(m);
    }

    void swap_rows(std::size_t row1, std::size_t row2) {
        if (row1 >= this->rows_ || row2 >= this->rows_)
            throw std::invalid_argument("index out of range");
        std::swap(this->matrix_[row1], this->matrix_[row2]);
    }
    void swap_columns(std::size_t column1, std::size_t column2) {
        if (column1 >= this->columns_ || column2 >= this->columns_)
            throw std::invalid_argument("index out of range");
        for (std::size_t i = 0; i < rows_; ++i)
            std::swap(matrix_[i][column1], matrix_[i][column2]);
    }

    bool is_square() const { return this->rows_ == this->columns_; }
    bool is_symmetric() const {
        if (!this->is_square()) return false;
        for (std::size_t i{}; i < this->rows_; ++i)
            for (std::size_t j{}; j < this->columns_; ++j)
                if (this->matrix_[i][j] != this->matrix_[j][i])
                    return false;
        return true;
    }


    std::string to_string() const {
        std::ostringstream out;

        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < columns_; ++j) {
                out << matrix_[i][j];
                if (j + 1 < columns_) out << ' ';
            }
            out << '\n';
        }
        return out.str();
    }

public:    /*  operators  */
    Matrix &operator=(const Matrix &other) {
        if (this == &other) return *this;

        for (std::size_t i = 0; i < rows_; ++i)
            delete[] matrix_[i];
        delete[] matrix_;

        rows_ = other.rows_;
        columns_ = other.columns_;
        matrix_ = allocate_matrix(rows_, columns_);

        for (std::size_t i = 0; i < rows_; ++i)
            for (std::size_t j = 0; j < columns_; ++j)
                matrix_[i][j] = other[i][j];

        return *this;
    }

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
    
    Matrix operator*(const Matrix &other) const {
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

    bool operator==(const Matrix &other) const {
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
    EXPECT_EQ(m_to_str, "\0\n\0\n");
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

TEST(Matrix, IsSquare) {
    Matrix<std::string> m = Matrix<std::string>(2, 2);
    EXPECT_TRUE(m.is_square());

    m = Matrix<std::string>(1, 2);
    EXPECT_FALSE(m.is_square());
}

TEST(Matrix, IsSymmetric) {
    Matrix<std::string> m = Matrix<std::string>(2, 2);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 2; m[1][1] = 10;
    EXPECT_TRUE(m.is_symmetric());

    m = Matrix<std::string>(2, 2);
    m[0][0] = 1; m[0][1] = 21; m[1][0] = 2; m[1][1] = 10;
    EXPECT_FALSE(m.is_symmetric());
}

TEST(Matrix, SwapColumns) {
    Matrix<int> m(2,2);
    m[0][0]=1; m[0][1]=2, m[1][0]=3; m[1][1]=4;

    m.swap_columns(0,1);

    EXPECT_EQ(m[0][0],2);
    EXPECT_EQ(m[0][1],1);
    EXPECT_EQ(m[1][0],4);
    EXPECT_EQ(m[1][1],3);
}

TEST(Matrix, SwapRows) {
    Matrix<int> m(2,2);
    m[0][0]=1; m[0][1]=2;
    m[1][0]=3; m[1][1]=4;

    m.swap_rows(0,1);

    EXPECT_EQ(m[0][0],3);
    EXPECT_EQ(m[0][1],4);
    EXPECT_EQ(m[1][0],1);
    EXPECT_EQ(m[1][1],2);
}

TEST(Matrix, SwapOutOfRange) {
    Matrix<int> m(2,2);

    EXPECT_THROW(m.swap_rows(0,2), std::invalid_argument);
    EXPECT_THROW(m.swap_columns(1,3), std::invalid_argument);
}

TEST(Matrix, DotProductThrows) {
    Matrix<int> a(2,3);
    Matrix<int> b(2,2);

    EXPECT_THROW(a * b, std::invalid_argument);
}

