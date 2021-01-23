#include <iostream>

#include "filling.h"


int main() {
	//clearing all files
	std::ofstream temp_a_file(addition_output); temp_a_file.close();
	std::ofstream temp_s_file(subtraction_output); temp_s_file.close();
	std::ofstream temp_d_file(division_output); temp_d_file.close();
	std::ofstream temp_m_file(multiplication_output); temp_m_file.close();
	std::ofstream temp_sq_file(sqrt_output); temp_sq_file.close();


	write_all<uint8_t>("uint8"); 
	std::cout << "uint8 done" << std::endl;

	write_all<uint16_t>("uint16"); 
	std::cout << "uint16 done" << std::endl;

	write_all<uint32_t>("uint32"); 
	std::cout << "uint32 done" << std::endl;

	write_all<uint64_t>("uint64"); 
	std::cout << "uint64 done" << std::endl;

	write_all<int8_t>("int8"); 
	std::cout << "int8 done" << std::endl;

	write_all<int16_t>("int16"); 
	std::cout << "int16 done" << std::endl;

	write_all<int32_t>("int32"); 
	std::cout << "int32 done" << std::endl;

	write_all<int64_t>("int64"); 
	std::cout << "int64 done" << std::endl;

	write_all<float>("float"); 
	std::cout << "float done" << std::endl;

	write_all<double>("double"); 
	std::cout << "double done" << std::endl;


	//making results into nice tables
	//system("./create_pdf.sh"); //--commented for testing as to not keep creating the pdf
	return 0;
}
