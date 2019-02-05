import random
import os
import sys

def writeFile(shape, docNum):
    coordinates = next(iter(shape.values()));
    
    testName = "test" + str(docNum) + ".txt";
    testFile = open(os.path.join("testFiles", testName), "x");
    toWrite = " ".join(map(str, coordinates));
    testFile.write(toWrite);

    resultFile = open(os.path.join("resultFiles", testName), "x");
    resultFile.write(next(iter(shape)) + "\n");

def expand(coordinates, ratio):
    ret = [];
    for i in range(len(coordinates)):
        ret.append(coordinates[i] * ratio);

    return ret;

def generateSquare():
    xy = random.randint(1, 100);
    return {"square": [xy, 0, xy, xy, 0, xy]};

def generateRectangle():
    type1 = 2, 0, 2, 1, 0, 1;
    type2 = 1, 0, 1, 2, 0, 2;

    select = random.randint(1, 2);
    ratio = random.randint(1, 50);
    if(select == 1):
        return {"rectangle": expand(type1, ratio)};
    else:
        return {"rectangle": expand(type2, ratio)};
    

def generateRhombus():
    type1 = 5, 0, 8, 4, 3, 4;
    type2 = 4, 2, 6, 6, 2, 4;
    select = random.randint(1, 2);

    if(select == 1):
        ratio = random.randint(1, 12);
        return {"rhombus": expand(type1, ratio)};
    else:
        ratio = random.randint(1, 16);
        return {"rhombus": expand(type2, ratio)};

def generateParallelogram():
    type1 = 2, 0, 3, 1, 1, 1;

    return {"parallelogram": expand(type1, 33)};

def generateTrapezoid():
    type1 = 14, 0, 10, 10, 4, 10;

    return {"trapezoid": expand(type1, 7)};

def generateKite():
    type1 = 5, 0, 8, 8, 0, 5;
    type2 = 3, 0, 4, 4, 0, 3;

    select = random.randint(1, 2);

    if(select == 1):
        ratio = random.randint(1, 12);
        return {"kite": expand(type1, ratio)};
    else:
        ratio = random.randint(1, 25);
        return {"kite": expand(type2, ratio)};

def generateQuadrilateral():
    type1 = 7, 0, 2, 2, 1, 1;
    type2 = 4, 4, 8, 5, 2, 6;

    select = random.randint(1, 2);

    if(select == 1):
        ratio = random.randint(1, 14);
        return {"quadrilateral": expand(type1, ratio)};
    else:
        ratio = random.randint(1, 12);
        return {"quadrilateral": expand(type2, ratio)};

validOptions = {
    0 : generateSquare,
    1 : generateRectangle,
    2 : generateRhombus,
    3 : generateParallelogram,
    4 : generateTrapezoid,
    5 : generateKite,
    6 : generateQuadrilateral,
}
def generateValidShape():
    shape = random.randint(0,6);
    return validOptions[shape]();

def generateError1():
    subError = random.randint(0, 3);

    ret = [];
    if(subError == 0 or subError == 3):
        r = list(range(0, 6)) + list(range(7, 101));
        pointNum = random.choice(r) * random.randint(1, 2);
        for i in range(pointNum):
            ret.append(random.randint(1, 100));
    elif(subError == 1):
        r = list(range(1, 48)) + list(range(58, 128));
        for i in range(6):
            ret.append(chr(random.choice(r)));
    else:
        for i in range(6):
            ret.append(random.randint(101, 2147483647));
    
    return {"error 1": ret};


def generateError2():
    validShape = next(iter(generateValidShape().values()));
    withZero = random.randint(1, 2);
    idx1 = random.randint(0, 2);
    if(withZero == 1):
        idx2 = random.choice(list(range(0, idx1)) + list(range(idx1+1, 3)));
        validShape[idx2 * 2] = validShape[idx1 * 2];
        validShape[idx2 * 2 + 1] = validShape[idx1 * 2 + 1];
    else:
        validShape[idx1 * 2] = 0;
        validShape[idx1 * 2 + 1] = 0;

    return {"error 2": validShape};


def generateError3():
    case = random.randint(1, 3);
    validShape = next(iter(generateValidShape().values()));

    if(case == 1):
        validShape[2], validShape[4] = validShape[4], validShape[2];
        validShape[3], validShape[5] = validShape[5], validShape[3];
    elif(case == 2):
        validShape[0], validShape[2] = validShape[2], validShape[0];
        validShape[1], validShape[3] = validShape[3], validShape[1];
    else:
        validShape[0], validShape[4] = validShape[4], validShape[0];
        validShape[1], validShape[5] = validShape[5], validShape[1];
        validShape[2], validShape[4] = validShape[4], validShape[2];
        validShape[3], validShape[5] = validShape[5], validShape[3];

    return {"error 3": validShape};

def generateError4():
    idx = random.randint(0, 1);
    validShape = next(iter(generateValidShape().values()));
    while(validShape[0] == 100 and validShape[2] == 100):
        validShape = next(iter(generateValidShape().values()));
        
    # print(validShape);
    # print("idx" + str(idx));
    x1 = 0;
    y1 = 0;
    x2 = validShape[0];
    y2 = validShape[1];
    #use slope from pt2 and pt3
    if(idx == 1 or x2 == 100):
        x1 = x2;
        y1 = y2;
        x2 = validShape[2];
        y2 = validShape[3];
    
    if(x2 == x1):
        validShape[4] = x2;
        validShape[5] = random.randint(x2 + 1, 100);
        return {"error 4": validShape};
    
    slope = (y2 - y1)/(x2 - x1);
    yIntercept = y1 - slope * x1;

    newX = 0;
    if(slope < 0):
        newX = random.randint(x2 - 1, 100);
    else:
        newX = random.randint(x2 + 1, 100);

    newY = newX * slope + yIntercept;

    # print(slope);
    counter = 0;
    while((newY > 100 or newY < 0 or not newY.is_integer()) and counter < 100):
        if(slope < 0):
            newX = random.randint(x2 - 1, 100);
        else:
            newX = random.randint(x2 + 1, 100);

        newY = newX * slope + yIntercept;
        counter += 1;
    
    if(counter == 99):
        return generateError3();

    if(idx == 1 or x2 == 100):
        validShape[4] = newX;
        validShape[5] = int(newY);
    else:
        validShape[2] = newX;
        validShape[3] = int(newY);
    
    return {"error 4": validShape};

invalidOptions = {
    0 : generateError1,
    1 : generateError2,
    2 : generateError3,
    3 : generateError4,
}
def generateInvalidShape():
    error = random.randint(0,3);
    return invalidOptions[error]();

def makeTestFile():
    for i in range(1000):
        curr = random.randint(1, 2);
        if(curr == 1):
            writeFile(generateValidShape(), i + 1);
        else:
            writeFile(generateInvalidShape(), i + 1);

    # writeValidFile(generateRhombus());
    # generateSquare();
    # generateSquare();
    # print(generateError4());
    # writeFile(generateInvalidShape(), 1);

makeTestFile();