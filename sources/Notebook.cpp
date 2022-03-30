#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;
#include <string>
#include <iostream>
#include <vector>
using namespace std;

const unsigned int MAX_LINE_WIDTH = 100;
const int HIGH_CHAR = 125;
const int LOW_CHAR = 32;

namespace ariel {

    void checkBoundaries (int page, int row, int column, Direction direction, int length) {
        if (page < 0 || row < 0 || column < 0 || length < 0) {
            throw("Out of bound");
        }
        if (direction == Direction::Horizontal && column + length >  MAX_LINE_WIDTH) {
            throw("Trying to access column larger than 100");
        }
        if (column >= MAX_LINE_WIDTH) {
            throw("Trying to access column larger than 100");
        }
    }

    std::vector<char> line (MAX_LINE_WIDTH, '_');
    string createLine(int page, int row) {
        return to_string(page )+ "and" + to_string(row);
    }

    void Notebook::write (int page, int row , int column , Direction direction, string str) {
        int length = str.length();
        string currString = read(page, row, column, direction, length);
        //string must empty in order to write
        if(currString != std::string (str.length(),'_')){
            throw ("Rewriting not allowed");
        }
        for (unsigned int i = 0; i < str.length(); i++) {
            char ch = str[i];
            if (ch < LOW_CHAR || ch > HIGH_CHAR) {
                throw("Invalid Char not allowed");
            }
        }
        if(direction == Direction::Horizontal) {
            string lineIndex = createLine(page, row);
            
            for (unsigned int i = 0; i < length; i++)
            {
                if(str[i] == '~'){
                    throw ("this place has already been written to");
                }
                book[lineIndex][(unsigned int)column+i] = str[i];
            }
        }
        else {
            for (unsigned int i = 0; i < length; i++)
            {
                string lineIndex = to_string(page)+ "and" + to_string((unsigned int)row+i);
                book[lineIndex][(unsigned int)(column)] = str[i];
            }
        }
    };

    string Notebook::read (int page, int row , int column , Direction direction, int length) {
        checkBoundaries(page, row, column, direction, length);
        string str;
        if(direction == Direction::Horizontal) {

            string lineIndex = createLine(page, row);
            if (book[lineIndex].empty())
            {
                book[lineIndex] = line;
            }    
            for (int i = 0; i < length; i++)
            {
                str += book[lineIndex][(unsigned int)(column+i)];
            }
        }
        else{
            for (int i = 0; i < length; i++)
            {
                string lineIndex = createLine(page, row+i);
                if (book[lineIndex].empty())
                {
                    book[lineIndex] = line;
                }
                str += book[lineIndex][(unsigned int)(column)];
            }
        }
        return str;
    };

    void Notebook::erase (int page, int row , int column , Direction direction, int length) {
        checkBoundaries(page, row, column, direction, length);
        string currString = read(page, row, column, direction, length);
        if(direction == Direction::Horizontal) {
            string lineIndex = createLine(page, row);
            for (int i = 0; i < length; i++)
            {
                book[lineIndex][(unsigned int)(column+i)] = '~';
            }
        }
        else {
            for (int i = 0; i < length; i++)
            {
                string lineIndex = createLine(page, row+i);
                book[lineIndex][(unsigned int)column] = '~';
            }
        }
    }

    string Notebook::show (int pageNumber) {
        if (pageNumber < 0) {
            throw("Negetive page number is not allowed");
        }
        //reads the whole notebook line by line
        string notebook;
        for (int i = 0; i < MAX_LINE_WIDTH; i++) {
            notebook += read(pageNumber, i, 0, Direction::Horizontal, MAX_LINE_WIDTH);
        }
        return notebook;
    };
};