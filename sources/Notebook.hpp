#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Direction.hpp"

using namespace std;
namespace ariel {
    class Notebook {
         private:
            std::unordered_map<std::string, std::vector<char>> book;
            
        public:
            void write (int page, int row , int column , Direction direction, string str);
            string read (int page, int row , int column , Direction direction, int length);
            void erase (int page, int row , int column , Direction direction, int length);
            string show (int pageNumber);
            
    };
    string createLine(int page, int row);
};