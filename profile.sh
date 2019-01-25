clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
LLVM_PROFILE_FILE="main.profraw" ./main
llvm-profdata merge -sparse main.profraw -o main.profdata
llvm-cov show ./main -instr-profile=main.profdata