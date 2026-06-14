#ifndef Q3_H
#define Q3_H

#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstddef>

namespace q3 {
    struct Flight {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };
    
    // Min-heap comparator: smallest weighted sum on top
    struct FlightComparator {
        bool operator()(const Flight& a, const Flight& b) const {
            size_t sum_a = a.duration + a.connection_times + 3 * a.price;
            size_t sum_b = b.duration + b.connection_times + 3 * b.price;
            return sum_a > sum_b;
        }
    };
    
    // Converts a time string "XhYm" to total minutes
    inline size_t parse_duration(const std::string& s) {
        size_t hours = 0, minutes = 0;
        auto h_pos = s.find('h');
        auto m_pos = s.find('m');
        if (h_pos != std::string::npos)
            hours = std::stoul(s.substr(0, h_pos));
        if (m_pos != std::string::npos) {
            size_t start = (h_pos != std::string::npos) ? h_pos + 1 : 0;
            minutes = std::stoul(s.substr(start, m_pos - start));
        }
        return hours * 60 + minutes;
    }
    
    // Sums all connection times in a comma-separated list
    inline size_t parse_connection_times(const std::string& s) {
        size_t total = 0;
        std::stringstream ss(s);
        std::string token;
        while (std::getline(ss, token, ',')) {
            size_t b = token.find_first_not_of(" \t");
            size_t e = token.find_last_not_of(" \t");
            if (b != std::string::npos)
                token = token.substr(b, e - b + 1);
            total += parse_duration(token);
        }
        return total;
    }
    
    // Reads flights from file; returns a min-heap priority queue.
    // No `for` keyword is used.
    inline std::priority_queue<Flight, std::vector<Flight>, FlightComparator>
    gather_flights(const std::string& filename) {
        std::priority_queue<Flight, std::vector<Flight>, FlightComparator> flights;
        std::ifstream file(filename);
        if (!file.is_open())
            throw std::runtime_error("Cannot open file: " + filename);
    
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            Flight f;
            std::stringstream ss(line);
            std::string part;
            while (std::getline(ss, part, '-')) {
                size_t b = part.find_first_not_of(" \t");
                size_t e = part.find_last_not_of(" \t");
                if (b == std::string::npos) continue;
                std::string clean = part.substr(b, e - b + 1);
    
                if (clean.find("flight_number:") == 0)
                    f.flight_number = clean.substr(14);
                else if (clean.find("duration:") == 0)
                    f.duration = parse_duration(clean.substr(9));
                else if (clean.find("connections:") == 0)
                    f.connections = std::stoul(clean.substr(12));
                else if (clean.find("connection_times:") == 0)
                    f.connection_times = parse_connection_times(clean.substr(17));
                else if (clean.find("price:") == 0)
                    f.price = std::stoul(clean.substr(6));
            }
            flights.push(f);
        }
        return flights;
    }
}

#endif //Q3_H