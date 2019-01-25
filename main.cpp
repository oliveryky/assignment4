#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>

/**
 * takes in a csv string and returns a vector with the values
 * @param currLine
 * @return vector containing the coordinates of the shape in form of (x1,y1,x2,y2,x3,y3)
 */
std::vector<int> split(const std::string& currLine) {
    std::vector<int> ret;
    std::string value;
    char split = ',';
    std::istringstream stream(currLine);

    while(getline(stream, value, split)) {
        ret.push_back(stoi(value));
    }

    return ret;
}

/**
 * returns distance between two points
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return distance between points (x1,y1) and (x2,y2)
 */
double getDistance(const int& x1, const int& y1, const int& x2, const int& y2) {
    return sqrt(pow((double)(x2 - x1), 2) + pow((double)(y2 - y1), 2));
}

/**
 * returns the slope between (x1,y1) and (x2,y2)
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return the slope, returns infinity if line is vertical
 */
double getSlope (const int& x1, const int& y1, const int& x2, const int& y2) {
    //check for vertical slope
    return (x2 - x1) == 0 ? std::numeric_limits<double>::infinity() : (y2 - y1) / (double)(x2 - x1);
}

/**
 * checks if the shape is a parallelogram
 * @param values
 * @return
 */
bool isParallelogram(const std::vector<int>& values) {
    return getDistance(0, 0, values[4], values[5]) == getDistance(values[0], values[1], values[2], values[3])
    && getDistance(0, 0, values[0], values[1]) == getDistance(values[4], values[5], values[2], values[3]);
}

/**
 * checks if the shape is a trapezoid
 * @param values
 * @return
 */
bool isTrapezoid(const std::vector<int>& values) {
    return getSlope(0, 0, values[4], values[5]) == getSlope(values[0], values[1], values[2], values[3])
                  || getSlope(0, 0, values[0], values[1]) == getSlope(values[4], values[5], values[2], values[3]);
}

/**
 * checks if shape is a kite
 * @param values
 * @return
 */
bool isKite(const std::vector<int>& values) {
    return getDistance(0, 0, values[4], values[5]) == getDistance(0, 0, values[0], values[1])
           && getDistance(values[0], values[1], values[2], values[3]) == getDistance(values[4], values[5], values[2], values[3]);
}

/**
 * checks if shape is rhombus
 * @param values
 * @return
 */
bool isRhombus(const std::vector<int>& values) {
    double a = getDistance(0, 0, values[0], values[1]);
    double b = getDistance(values[0], values[1], values[2], values[3]);
    double c = getDistance(values[4], values[5], values[2], values[3]);
    double d = getDistance(0, 0, values[4], values[5]);
    bool ret = a == b && b == c && c == d && d == a;

    return ret;
}

/**
 * checks if shape is rectangle
 * @param values
 * @return
 */
bool isRectangle(const std::vector<int>& values) {
    return values[1] == 0 && values[0] == values[2] && values[3] == values[5] && values[4] == 0;
}

/**
 * takes a vector of xy-coordinates and returns the most specific shape
 * @param values
 * @return the string name for the shape
 */
std::string parseShape(const std::vector<int>& values) {
    //check for parallelogram, trapzezoid or kite
    if(isParallelogram(values)) {
        bool checkRhombus = isRhombus(values);
        bool checkRectangle = isRectangle(values);

        if(!checkRhombus && !checkRectangle) {
            return "parallelogram";
        }else if(checkRhombus) {
            if(checkRectangle) {
                return "square";
            }else {
                return "rhombus";
            }
        }else {
            return "rectangle";
        }
    }else if(isTrapezoid(values)) {
        return "trapezoid";
    }else if(isKite(values)) {
        return "kite";
    }else {
        return "quadrilateral";
    }
}

/**
 * attempts to open and read the specified file
 * parses each line assuming it is in csv format
 * prints out the most specific name of the shape on each line
 * @param fileName
 */
void readFile(const std::string &fileName) {
    std::ifstream file(fileName.c_str());
    if(file.is_open()) {
        std::string currLine, delimiter = ",";
        int counter = 1;
        while(getline(file, currLine)) {
            //split string
            std::vector<int> values = split(currLine);
            std::cout << "Shape #" << counter++ << " is: " << parseShape(values) << std::endl;
        }
    }
}

int main() {
    readFile("/Users/oliveryu/oliveryky/cs6015/assignment3/shapeInput.txt");
    return 0;
}