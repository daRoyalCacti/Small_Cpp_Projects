#include <iostream>
#include <stdlib.h>

#include "filling.h"

typedef uint64_t size_datatype;

const size_datatype no_tests = 5e7; //must be even

const char* addition_output = "./latex/addition.tex";
const char* subtraction_output = "./latex/subtraction.tex";
const char* division_output = "./latex/division.tex";
const char* multiplication_output = "./latex/multiplication.tex";
const char* sqrt_output = "./latex/sqrt.tex";

int main() {
  //clearing all files
  std::ofstream temp_a_file(addition_output); temp_a_file.close();
  std::ofstream temp_s_file(subtraction_output); temp_s_file.close();
  std::ofstream temp_d_file(division_output); temp_d_file.close();
  std::ofstream temp_m_file(multiplication_output); temp_m_file.close();
  std::ofstream temp_sq_file(sqrt_output); temp_sq_file.close();



  uint8_t* uint8 = new uint8_t[no_tests];
  fill(uint8, no_tests);
  write(time_addition(uint8, no_tests), no_tests / 2, addition_output, "uint8");
  write(time_subtraction(uint8, no_tests), no_tests / 2, subtraction_output, "uint8");
  write(time_multiplication(uint8, no_tests), no_tests / 2, multiplication_output, "uint8");
  write(time_division(uint8, no_tests), no_tests / 2, division_output, "uint8");
  write(time_sqrt(uint8, no_tests / 2), no_tests / 4, sqrt_output, "uint8");
  delete [] uint8;
  std::cout << "uint8 done" << std::endl;

  uint16_t* uint16 = new uint16_t[no_tests];
  fill(uint16, no_tests);
  write(time_addition(uint16, no_tests), no_tests / 2, addition_output, "uint16");
  write(time_subtraction(uint16, no_tests), no_tests / 2, subtraction_output, "uint16");
  write(time_multiplication(uint16, no_tests), no_tests / 2, multiplication_output, "uint16");
  write(time_division(uint16, no_tests), no_tests / 2, division_output, "uint16");
  write(time_sqrt(uint16, no_tests / 2), no_tests / 4, sqrt_output, "uint16");
  delete [] uint16;
  std::cout << "uint16 done" << std::endl;

  uint32_t* uint32 = new uint32_t[no_tests];
  fill(uint32, no_tests);
  write(time_addition(uint32, no_tests), no_tests / 2, addition_output, "uint32");
  write(time_subtraction(uint32, no_tests), no_tests / 2, subtraction_output, "uint32");
  write(time_multiplication(uint32, no_tests), no_tests / 2, multiplication_output, "uint32");
  write(time_division(uint32, no_tests), no_tests / 2, division_output, "uint32");
  write(time_sqrt(uint32, no_tests / 2), no_tests / 4, sqrt_output, "uint32");
  delete [] uint32;
  std::cout << "uint32 done" << std::endl;

  uint64_t* uint64 = new uint64_t[no_tests];
  fill(uint64, no_tests);
  write(time_addition(uint64, no_tests), no_tests / 2, addition_output, "uint64");
  write(time_subtraction(uint64, no_tests), no_tests / 2, subtraction_output, "uint64");
  write(time_multiplication(uint64, no_tests), no_tests / 2, multiplication_output, "uint64");
  write(time_division(uint64, no_tests), no_tests / 2, division_output, "uint64");
  write(time_sqrt(uint64, no_tests / 2), no_tests / 4, sqrt_output, "uint64");
  delete [] uint64;
  std::cout << "uint64 done" << std::endl;

  int8_t* int8 = new int8_t[no_tests];
  fill(int8, no_tests);
  write(time_addition(int8, no_tests), no_tests / 2, addition_output, "int8");
  write(time_subtraction(int8, no_tests), no_tests / 2, subtraction_output, "int8");
  write(time_multiplication(int8, no_tests), no_tests / 2, multiplication_output, "int8");
  write(time_division(int8, no_tests), no_tests / 2, division_output, "int8");
  write(time_sqrt(int8, no_tests / 2), no_tests / 4, sqrt_output, "int8");
  delete [] int8;
  std::cout << "int8 done" << std::endl;

  int16_t* int16 = new int16_t[no_tests];
  fill(int16, no_tests);
  write(time_addition(int16, no_tests), no_tests / 2, addition_output, "int16");
  write(time_subtraction(int16, no_tests), no_tests / 2, subtraction_output, "int16");
  write(time_multiplication(int16, no_tests), no_tests / 2, multiplication_output, "int16");
  write(time_division(int16, no_tests), no_tests / 2, division_output, "int16");
  write(time_sqrt(int16, no_tests / 2), no_tests / 4, sqrt_output, "int16");
  delete [] int16;
  std::cout << "int16 done" << std::endl;

  int32_t* int32 = new int32_t[no_tests];
  fill(int32, no_tests);
  write(time_addition(int32, no_tests), no_tests / 2, addition_output, "int32");
  write(time_subtraction(int32, no_tests), no_tests / 2, subtraction_output, "int32");
  write(time_multiplication(int32, no_tests), no_tests / 2, multiplication_output, "int32");
  write(time_division(int32, no_tests), no_tests / 2, division_output, "int32");
  write(time_sqrt(int32, no_tests / 2), no_tests / 4, sqrt_output, "int32");
  delete [] int32;
  std::cout << "int32 done" << std::endl;

  int64_t* int64 = new int64_t[no_tests];
  fill(int64, no_tests);
  write(time_addition(int64, no_tests), no_tests / 2, addition_output, "int64");
  write(time_subtraction(int64, no_tests), no_tests / 2, subtraction_output, "int64");
  write(time_multiplication(int64, no_tests), no_tests / 2, multiplication_output, "int64");
  write(time_division(int64, no_tests), no_tests / 2, division_output, "int64");
  write(time_sqrt(int64, no_tests / 2), no_tests / 4, sqrt_output, "int64");
  delete [] int64;
  std::cout << "int64 done" << std::endl;

  float* sReal = new float[no_tests];
  fill(sReal, no_tests);
  write(time_addition(sReal, no_tests), no_tests / 2, addition_output, "float");
  write(time_subtraction(sReal, no_tests), no_tests / 2, subtraction_output, "float");
  write(time_multiplication(sReal, no_tests), no_tests / 2, multiplication_output, "float");
  write(time_division(sReal, no_tests), no_tests / 2, division_output, "float");
  write(time_sqrt(sReal, no_tests / 2), no_tests / 4, sqrt_output, "float");
  delete [] sReal;
  std::cout << "float done" << std::endl;

  double* dReal = new double[no_tests];
  fill(dReal, no_tests);
  write(time_addition(dReal, no_tests), no_tests / 2, addition_output, "double");
  write(time_subtraction(dReal, no_tests), no_tests / 2, subtraction_output, "double");
  write(time_multiplication(dReal, no_tests), no_tests / 2, multiplication_output, "double");
  write(time_division(dReal, no_tests), no_tests / 2, division_output, "double");
  write(time_sqrt(dReal, no_tests / 2), no_tests / 4, sqrt_output, "double");
  delete [] dReal;
  std::cout << "double done" << std::endl;


  //making results into nice tables
  system("./create_pdf.sh"); //--commented for testing as to not keep creating the pdf
  return 0;
}
