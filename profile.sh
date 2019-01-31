clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
rm -f ./coverage/*.profdata


LLVM_PROFILE_FILE="main.profraw" ./main shapeInput.txt

LLVM_PROFILE_FILE="e1.profraw" ./main error1.txt
LLVM_PROFILE_FILE="e1_1.profraw" ./main error1_1.txt
LLVM_PROFILE_FILE="e1_2.profraw" ./main error1_2.txt
LLVM_PROFILE_FILE="e2.profraw" ./main error2.txt
LLVM_PROFILE_FILE="e2_1.profraw" ./main error2_1.txt
LLVM_PROFILE_FILE="e3.profraw" ./main error3.txt
LLVM_PROFILE_FILE="e3_1.profraw" ./main error3_1.txt
LLVM_PROFILE_FILE="e3_2.profraw" ./main error3_2.txt
LLVM_PROFILE_FILE="e4.profraw" ./main error4.txt
LLVM_PROFILE_FILE="e4_1.profraw" ./main error4_1.txt

xcrun llvm-profdata merge -sparse main.profraw e1.profraw e1_1.profraw e1_2.profraw e2.profraw e2_1.profraw e3.profraw e3_1.profraw e3_2.profraw e4.profraw e4_1.profraw -o main.profdata
xcrun llvm-cov show ./main -instr-profile=main.profdata
