import os
import filecmp

os.system("sh clear.sh")
os.system("clang++ -c -std=c++11 main.cpp")
os.system("clang++ -o main main.o")
os.system("python3 fuzz.py")
os.system("clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o main")
os.system("rm -f *.profdata")
# os.system("rm resultFiles/*")
# os.system("rm testFiles/*")
# os.system("rm output/*")
# os.system("rm profile/*")
os.system("touch ./profile/main.profdata")
os.system("touch ./default.profraw")
# os.system("rm ./profile/.DS_Store.profraw")
# os.system("rm ./profile/.DS_Store.profdata")
prev = "main"
os.system("LLVM_PROFILE_FILE=\"./profile/" + prev + ".profraw\" ./main")
directory = os.fsencode("testFiles")

for file in os.listdir(directory):
    fileName = os.path.splitext(os.fsdecode(file))[0]
    os.system("LLVM_PROFILE_FILE=\"./profile/" + fileName + ".profraw\" ./main ./testFiles/" + fileName + ".txt > ./output/" + fileName + ".txt")
    os.system("xcrun llvm-profdata merge -sparse ./profile/" + prev + ".profdata ./profile/" + fileName + ".profraw -o ./profile/" + fileName + ".profdata")
    prev = fileName
    if(not filecmp.cmp("./output/" + fileName + ".txt", "./resultFiles/" + fileName + ".txt")):
        print(fileName)

os.system("xcrun llvm-cov show ./main -instr-profile=./profile/" + prev + ".profdata")
# os.system("xcrun llvm-cov show ./main -instr-profile=./profile/" + prev + ".profdata > coverage.txt")
os.system("All Tests Passed")