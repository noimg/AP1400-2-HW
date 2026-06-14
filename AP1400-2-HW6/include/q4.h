#ifndef Q4_H
#define Q4_H

#include <vector>
#include <numeric>

namespace q4 {
    struct Vector2D {
        double x{};
        double y{};
    };
    
    struct Sensor {
        Vector2D pos;
        double accuracy;
    };
    
    namespace detail {
        struct Accumulator {
            double weighted_x = 0.0;
            double weighted_y = 0.0;
            double total_weight = 0.0;
        };
    }
    
    inline Vector2D kalman_filter(const std::vector<Sensor>& sensors) {
        using AccType = std::pair<Vector2D, double>;
    
        auto binary_op = [](AccType acc, const Sensor& s) {
            acc.first.x += s.pos.x * s.accuracy;
            acc.first.y += s.pos.y * s.accuracy;
            acc.second += s.accuracy;
            return acc;
        };
    
        AccType init{Vector2D{0.0, 0.0}, 0.0};
        AccType result = std::accumulate(sensors.begin(), sensors.end(), init, binary_op);
    
        Vector2D estimate;
        if (result.second != 0.0) {
            estimate.x = result.first.x / result.second;
            estimate.y = result.first.y / result.second;
        }
        return estimate;
    }
}

#endif //Q4_H