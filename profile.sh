clang++ -std=c++11 -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
rm -f ./coverage/*.profdata


LLVM_PROFILE_FILE="main.profraw" ./main shapeInput.txt
llvm-profdata merge -sparse main.profraw -o main.profdata
llvm-cov show ./main -instr-profile=main.profdata