#include "hw1.h"

namespace algebra
{
    Matrix zeros(size_t n, size_t m)
    {
        return Matrix(n, std::vector<double>(m, 0));
    }

    Matrix ones(size_t n, size_t m)
    {
        return Matrix(n, std::vector<double>(m, 1));
    }

    Matrix random(size_t n, size_t m, double min, double max)
    {
        if (min >= max)
            throw std::logic_error("min >= max");

        Matrix mat = zeros(n, m);
        std::default_random_engine e;
        std::uniform_real_distribution<double> u(min, max);

        for (auto& row : mat)
        {
            for (auto& elem : row)
            {
                elem = u(e);
            }
        }
        return mat;
    }

    void show(const Matrix& matrix)
    {
        for (const auto& row : matrix)
        {
            for (auto& elem : row)
            {
                std::cout << std::setw(7) << std::fixed << std::setprecision(3) << elem;
            }
            std::cout << std::endl;
        }
    }

    Matrix multiply(const Matrix& matrix, double c)
    {
        Matrix mul(matrix);
        for (auto& row : mul)
            for (auto& elem : row)
                elem *= c;

        return mul;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2)
    {
        if (matrix1.empty() && matrix2.empty())
            return matrix1;
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("calculation error\n");

        int m1, n1, m2, n2;
        m1 = matrix1.size();
        n1 = matrix1[0].size();
        m2 = matrix2.size();
        n2 = matrix2[0].size();

        if (n1 != m2)
            throw std::logic_error("dimensions doesn't match");
        
        Matrix mul = zeros(m1, n2);

        for (int i = 0; i < m1; ++i)
            for (int j = 0; j < n2; ++j)
                for (int k = 0; k < n1; ++k)
                    mul[i][j] += matrix1[i][k] * matrix2[k][j];
        
        return mul;
    }

    Matrix sum(const Matrix& matrix, double c)
    {
        if (matrix.empty())
            return matrix;
        
        Matrix sum(matrix);
        for (auto& row : sum)
            for (auto& elem : row)
                elem += c;
        
        return sum;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2)
    {
        if (matrix1.empty() && matrix2.empty())
            return matrix1;
        if (matrix1.empty() || matrix2.empty())
            throw std::logic_error("dimensions doesn't match");

        int m1, n1, m2, n2;
        m1 = matrix1.size();
        n1 = matrix1[0].size();
        m2 = matrix2.size();
        n2 = matrix2[0].size();

        if ((m1 != m2) || (n1 != n2))
            throw std::logic_error("dimensions doesn't match");

        Matrix sum(matrix1);

        for (int i = 0; i < m1; ++i)
            for (int j = 0; j < n1; ++j)
                sum[i][j] += matrix2[i][j];

        return sum;
    }

    Matrix transpose(const Matrix& matrix)
    {
        if (matrix.empty())
            return matrix;
        
        int m, n;
        m = matrix.size();
        n = matrix[0].size();
        Matrix trans = zeros(n, m);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                trans[i][j] = matrix[j][i];

        return trans;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m)
    {
        int m1 = matrix.size();
        Matrix minor = zeros(m1-1, m1-1);

        for (int i = 0; i < m1 - 1; ++i)
        {
            for (int j = 0; j < m1 - 1; ++j)
            {
                int i0 = (i < n) ? i : i + 1;
                int j0 = (j < m) ? j : j + 1;

                minor[i][j] = matrix[i0][j0];
            }
        }
        return minor;
    }

    double determinant(const Matrix& matrix)
    {
        int n = matrix.size();
        if (n == 0)
            return 1;
        if (n != matrix[0].size())
            throw std::logic_error("matrix must be square");

        // if (n == 1)
        //     return matrix[0][0];
        if (n == 2)
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        
        double det = 0;
        for (int i = 0; i < n; ++i)
        {
            int sign = (i % 2) ? -1 : 1;
            Matrix m = minor(matrix, 0, i);
            
            det += sign * matrix[0][i] * determinant(m);
        }
        return det;
    }
}