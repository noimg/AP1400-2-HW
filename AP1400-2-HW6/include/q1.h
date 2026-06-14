#ifndef Q1_H
#define Q1_H

#include <cmath>

namespace q1 {
    template <typename T, typename F>
    T gradient_descent(T initial, T step, F f = F{}) {
        T x = initial;
        const T h = static_cast<T>(1e-6);
        const T tol = static_cast<T>(1e-7);
        const int max_iter = 100000;
    
        for (int i = 0; i < max_iter; ++i) {
            T grad = (f(x + h) - f(x - h)) / (2 * h);
            T x_new = x - step * grad;
    
            if (std::abs(x_new - x) < tol)
                break;
    
            x = x_new;
        }
        return x;
    }
}

#endif //Q1_H