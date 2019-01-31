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
std::vector<int> split(const std::string &currLine) {
    std::vector<int> ret;
    std::string value;
    char split = ',';
    std::istringstream stream(currLine);

    while (getline(stream, value, split)) {
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
double getDistance(const int &x1, const int &y1, const int &x2, const int &y2) {
    return sqrt(pow((double) (x2 - x1), 2) + pow((double) (y2 - y1), 2));
}

/**
 * returns the slope between (x1,y1) and (x2,y2)
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return the slope, returns infinity if line is vertical
 */
double getSlope(const int &x1, const int &y1, const int &x2, const int &y2) {
    //check for vertical slope
    return (x2 - x1) == 0 ? std::numeric_limits<double>::infinity() : (y2 - y1) / (double) (x2 - x1);
}

/**
 * checks if the shape is a parallelogram
 * @param values
 * @return
 */
bool isParallelogram(const std::vector<int> &values) {
    return getDistance(0, 0, values[4], values[5]) == getDistance(values[0], values[1], values[2], values[3])
           && getDistance(0, 0, values[0], values[1]) == getDistance(values[4], values[5], values[2], values[3]);
}

/**
 * checks if the shape is a trapezoid
 * @param values
 * @return
 */
bool isTrapezoid(const std::vector<int> &values) {
    return getSlope(0, 0, values[4], values[5]) == getSlope(values[0], values[1], values[2], values[3])
           || getSlope(0, 0, values[0], values[1]) == getSlope(values[4], values[5], values[2], values[3]);
}

/**
 * checks if shape is a kite
 * @param values
 * @return
 */
bool isKite(const std::vector<int> &values) {
    return getDistance(0, 0, values[4], values[5]) == getDistance(0, 0, values[0], values[1])
           && getDistance(values[0], values[1], values[2], values[3]) ==
              getDistance(values[4], values[5], values[2], values[3]);
}

/**
 * checks if shape is rhombus
 * @param values
 * @return
 */
bool isRhombus(const std::vector<int> &values) {
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
bool isRectangle(const std::vector<int> &values) {
    return values[1] == 0 && values[0] == values[2] && values[3] == values[5] && values[4] == 0;
}

/**
 * takes a vector of x,y-coordinates and returns the most specific shape
 * @param values
 * @return the string name for the shape
 */
std::string parseShape(const std::vector<int> &values) {
    //check for parallelogram, trapzezoid or kite
    if (isParallelogram(values)) {
        bool checkRhombus = isRhombus(values);
        bool checkRectangle = isRectangle(values);

        if (!checkRhombus && !checkRectangle) {
            return "parallelogram";
        } else if (checkRhombus) {
            if (checkRectangle) {
                return "square";
            } else {
                return "rhombus";
            }
        } else {
            return "rectangle";
        }
    } else if (isTrapezoid(values)) {
        return "trapezoid";
    } else if (isKite(values)) {
        return "kite";
    } else {
        return "quadrilateral";
    }
}

std::vector<std::string> toArray(const std::string &currLine) {
    std::vector<std::string> ret;
    std::string value;
    char split = ',';
    std::istringstream stream(currLine);

    while (getline(stream, value, split)) {
        ret.push_back(value);
    }

    return ret;
}

bool checkData(const std::vector<std::string> tempData) {
    //if there's less than 6 points
    if (tempData.size() != 6) {
        return false;
    }

    //for each string check if there are any invalid characters
    for (std::string str: tempData) {
        for (char c: str) {
            if (c < '0' || c > '9') {
//                std::cout << "bad char" << std::endl;
                return false;
            }
        }

        //if this point is reached then that means the current value is a valid number
        //check if it is in range
        int currVal = stoi(str);
        if (currVal < 0 || currVal > 100) {
//            std::cout << "bad val" << std::endl;
            return false;
        }
    }

    return true;
}

bool checkDupPoints(const std::vector<int> &values) {
    for (int i = 0; i < 6; i += 2) {
        int x = values[i];
        int y = values[i + 1];
        if(x == 0 && y == 0) {
            return false;
        }

        for (int j = i + 2; j < 6; j += 2) {
            if ((x == values[j] && y == values[j + 1])) {
                return false;
            }
        }
    }

    return true;
}

bool hasIntersection(const std::vector<int> &values) {
    double ax = values[0]; // direction of line a
    double ay = values[1]; // ax and ay as above
    double bx = values[2] - values[4]; // direction of line b, reversed
    double by = values[3] - values[5]; // really -by and -by as above
    double dx = values[2]; // right-hand side
    double dy = values[3];
    double det = ax * by - ay * bx;
    if (det == 0) return false;
    double r = (dx * by - dy * bx) / det;
    double s = (ax * dy - ay * dx) / det;
    return !(r < 0 || r > 1 || s < 0 || s > 1);
}

bool hasColinearPoints(const std::vector<int> &values) {
    //check if co-linearity of 1,2,3 is same and 2,3,4. If either is true, return true.
    int val = (values[1]) * (values[2] - values[0]) - (values[0]) * (values[3] - values[1]);
    if (val == 0) {
        return ((values[3] - values[1]) * (values[4] - values[2]) -
                (values[2] - values[0]) * (values[5] - values[3])) == 0;
    }
    return false;
}

std::string compileShape(const std::string &currLine) {
    std::vector<std::string> tempData = toArray(currLine);
    if (!checkData(tempData)) {
        return "error 1";
    }

    //given the data points are valid
    std::vector<int> values = split(currLine);
    if (!checkDupPoints(values)) {
        return "error 2";
    }

    if (hasIntersection(values)) {
        return "error 3";
    }

    if (hasColinearPoints(values)) {
        return "error 4";
    }

    return parseShape(values);
}

/**
 * attempts to open and read the specified file
 * parses each line assuming it is in csv format
 * prints out the most specific name of the shape on each line
 * @param fileName
 */
void readFile(const std::string &fileName) {
    std::ifstream file(fileName.c_str());
    if (file.is_open()) {
        std::string currLine, delimiter = ",";
        int counter = 1;
        while (getline(file, currLine)) {
            //split string
            std::cout << compileShape(currLine) << std::endl;
        }
    }
}

//TODO: input validation
//when printing may indicate errors when printing
/*
 * points overlapping
 */
int main(int argc, char* argv[]) {
    readFile(argv[1]);
//    readFile("/Users/oliveryu/Documents/assignment4/assignment4/shapeInput.txt");
//    readFile("/Users/oliveryu/Documents/assignment4/assignment4/temp.txt");
    return 0;
}