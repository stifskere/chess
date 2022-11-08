#ifndef CHESS_STRING_UTILITIES_H
#define CHESS_STRING_UTILITIES_H
#include <iostream>
#include <sstream>
#include <vector>

namespace string_utilities {
    template <typename T>
    std::string to_str(T obj) {
        std::stringstream s{};
        s << obj;
        return s.str();
    }

    template <typename... Args>
    std::string format(std::string main, Args... fmt) {
        std::vector<std::string> argsArr{};
        ((argsArr.push_back(to_str(fmt))), ...);
        for (int i = 0; i < argsArr.size(); i++){
            int index = (int)(main.find("{" + to_str(i) + "}"));
            while (index != std::string::npos) {
                main.replace(index, to_str(i).length() + 2, argsArr[i]);
                index = (int)(main.find("{" + to_str(i) + "}"));
            }
        }
        return main;
    }
}

#endif
