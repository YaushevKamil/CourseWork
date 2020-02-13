#ifndef MATH_OPERATION_HPP
#define MATH_OPERATION_HPP

#include <cmath>
#include <omp.h>

#include "vector.hpp"
#include "matrix.hpp"

namespace math {
    template <std::size_t  n, typename T>
    inline T length(vector<n, T> vec) {
        T result = {};
        for (std::size_t i = 0; i < n; ++i)
            result += vec[i] * vec[i];
        return sqrt(result);
    }

    template <std::size_t n, typename T>
    inline T lengthSquared(vector<n, T> vec) {
        T result = {};
        for(std::size_t  i = 0; i < n; ++i)
            result += vec[i] * vec[i];
        return result;
    }

    template <std::size_t n, typename T>
    inline float distance(vector<n, T> lhs, vector<n, T> rhs) {
        return length(lhs - rhs);
    }
    template <std::size_t n, typename T>
    inline float distanceSquared(vector<n, T> lhs, vector<n, T> rhs) {
        return lengthSquared(lhs - rhs);
    }

    template <std::size_t n, typename T>
    inline vector<n, T> normalize(vector<n, T> vec) {
        vector<n, T> result;
        T len = length(vec);
        for(std::size_t  i = 0; i < n; ++i)
            result[i] = vec[i] / len;
        return result;
    }

    template <std::size_t  n, typename T>
    inline T dot(vector<n, T> lhs, vector<n, T> rhs) {
        T result = {};
        for(std::size_t i = 0; i < n; ++i)
            result += lhs[i] * rhs[i];
        return result;
    }

    template<typename T>
    inline vector<2, T> perpendicular(const vector<2, T>& vec) {
        vector<2, T> result;
        result.x = -vec.y;
        result.y = vec.x;
        return result;
    }

    template<typename T>
    inline vector<3, T> cross(const vector<3, T>& lhs, const vector<3, T>& rhs) {
        vector<3, T> result;

        result.x = lhs.y*rhs.z - lhs.z*rhs.y;
        result.y = lhs.z*rhs.x - lhs.x*rhs.z;
        result.z = lhs.x*rhs.y - lhs.y*rhs.x;

        return result;
    }

    template <long unsigned int m, long unsigned int n, typename T>
    inline matrix<m, n, T> transpose(matrix<m, n, T>& mat) {
        matrix<n, m, T> result;
        #pragma omp parallel for
        for (std::size_t col = 0; col < m; ++col) {
            for (std::size_t row = 0; row < n; ++row) {
                result[col][row] = mat[row][col];
            }
        }
        return result;
    }

    template <std::size_t  m, std::size_t  n, typename T>
    inline matrix<m, n, T> inverse(/*const*/ matrix<m, n, T>& mat) {
        //assert(m == 4 && n == 4); // TODO: calculate for arbitrary m and n

        T t[6];
        T det;

        T a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
          e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
          i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
          x = mat[3][0], y = mat[3][1], o = mat[3][2], p = mat[3][3];

        t[0] = k * p - o * l; t[1] = j * p - y * l; t[2] = j * o - y * k;
        t[3] = i * p - x * l; t[4] = i * o - x * k; t[5] = i * y - x * j;

        math::mat4 dest;

        dest[0][0] =  f * t[0] - g * t[1] + h * t[2];
        dest[1][0] =-(e * t[0] - g * t[3] + h * t[4]);
        dest[2][0] =  e * t[1] - f * t[3] + h * t[5];
        dest[3][0] =-(e * t[2] - f * t[4] + g * t[5]);

        dest[0][1] =-(b * t[0] - c * t[1] + d * t[2]);
        dest[1][1] =  a * t[0] - c * t[3] + d * t[4];
        dest[2][1] =-(a * t[1] - b * t[3] + d * t[5]);
        dest[3][1] =  a * t[2] - b * t[4] + c * t[5];

        t[0] = g * p - o * h; t[1] = f * p - y * h; t[2] = f * o - y * g;
        t[3] = e * p - x * h; t[4] = e * o - x * g; t[5] = e * y - x * f;

        dest[0][2] =  b * t[0] - c * t[1] + d * t[2];
        dest[1][2] =-(a * t[0] - c * t[3] + d * t[4]);
        dest[2][2] =  a * t[1] - b * t[3] + d * t[5];
        dest[3][2] =-(a * t[2] - b * t[4] + c * t[5]);

        t[0] = g * l - k * h; t[1] = f * l - j * h; t[2] = f * k - j * g;
        t[3] = e * l - i * h; t[4] = e * k - i * g; t[5] = e * j - i * f;

        dest[0][3] =-(b * t[0] - c * t[1] + d * t[2]);
        dest[1][3] =  a * t[0] - c * t[3] + d * t[4];
        dest[2][3] =-(a * t[1] - b * t[3] + d * t[5]);
        dest[3][3] =  a * t[2] - b * t[4] + c * t[5];

        det = 1.0f / (a * dest[0][0] + b * dest[1][0] + c * dest[2][0] + d * dest[3][0]);

        return dest * det;
    }
}

#endif //MATH_OPERATION_HPP
