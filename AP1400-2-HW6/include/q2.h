#ifndef Q2_H
#define Q2_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace q2 {
    struct Patient
    {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };

    inline std::string trim(const std::string& str) {
        const char* whitespace = " \t\n\r\f\v";
        size_t first = str.find_first_not_of(whitespace);
        if (first == std::string::npos)
            return "";
        size_t last = str.find_last_not_of(whitespace);
        return str.substr(first, last - first + 1);
    }
    
    inline std::vector<Patient> read_file(std::string filename) {
        std::vector<Patient> patients;
        std::ifstream file(filename);
        if (!file.is_open())
            return patients;
    
        std::string line;
    
        // Skip the title line ("lung_cancer")
        std::getline(file, line);
        // Skip the header line ("Name,Surname,Age,Smokes,AreaQ,Alkhol")
        std::getline(file, line);
    
        while (std::getline(file, line)) {
            if (line.empty())
                continue;
    
            std::stringstream ss(line);
            std::string name, surname, age_str, smokes_str, areaq_str, alkhol_str;
    
            std::getline(ss, name, ',');
            std::getline(ss, surname, ',');
            std::getline(ss, age_str, ',');
            std::getline(ss, smokes_str, ',');
            std::getline(ss, areaq_str, ',');
            std::getline(ss, alkhol_str, ',');
    
            name = trim(name);
            surname = trim(surname);
            if (name.empty() && surname.empty())
                continue;
    
            Patient p;
            p.name = name + " " + surname;
            p.age = std::stoul(trim(age_str));
            p.smokes = std::stoul(trim(smokes_str));
            p.area_q = std::stoul(trim(areaq_str));
            p.alkhol = std::stoul(trim(alkhol_str));
    
            patients.push_back(p);
        }
        return patients;
    }
    
    inline void sort(std::vector<Patient>& patients) {
        std::sort(patients.begin(), patients.end(),
                  [](const Patient& a, const Patient& b) {
                      auto weight = [](const Patient& p) {
                          return 3 * p.age + 5 * p.smokes + 2 * p.area_q + 4 * p.alkhol;
                      };
                      return weight(a) > weight(b);
                  });
    }
}

#endif //Q2_H