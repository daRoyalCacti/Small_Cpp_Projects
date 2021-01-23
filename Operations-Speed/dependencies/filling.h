#include <limits>
#include <fstream>
#include <cmath>
#include <chrono>
#include <random>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>



typedef uint64_t size_datatype;

constexpr size_datatype no_tests =  5e7; //must be even
constexpr size_datatype num_per_avg = 1e5;
constexpr size_datatype no_avg = no_tests/num_per_avg; 

//could use std::string_view to constexpr
// - although there is no conversion to const char* which is required by ofstream
const char* addition_output = "./latex/addition.tex";
const char* subtraction_output = "./latex/subtraction.tex";
const char* division_output = "./latex/division.tex";
const char* multiplication_output = "./latex/multiplication.tex";
const char* sqrt_output = "./latex/sqrt.tex";



struct time_data {
	double mean_time;
	double std_time;
	double min_time;
	double max_time;
};

template<size_t s>
inline time_data create_time_data(std::array<double,s> time) {
	const double mean = std::accumulate(time.begin(), time.end(), 0.0) / time.size();
	
	//https://en.cppreference.com/w/cpp/algorithm/inner_product
	//taking the inner product of time with repesect to iteself using the specified inner product
	// - first lambda is how the combine the innerproducts of each element
	// - second lambda is the actual inner product function
	const double sq_sum = std::inner_product( time.begin(), time.end(), time.begin(), 0.0, 
			[](const double &x, const double &y){return x+y; }, 
			[mean](const double &x, const double &y) {return (x-mean)*(y-mean);}   );
	
	const double std = sqrt(sq_sum / (s - 1));

	const double min_t = *std::min_element(time.begin(), time.end());
	const double max_t = *std::max_element(time.begin(), time.end());


	return time_data{ mean, std, min_t, max_t};
}



template <typename T>
inline T generate_rand_type() {
	static std::mt19937 generator;

	constexpr auto min = std::numeric_limits<T>::min();
	constexpr auto max = std::numeric_limits<T>::max();
	//const large_data range = max - min;

	if (min == 0) {	//unsigned data
		static std::uniform_real_distribution<double> distribution1(0.0, 1.0);

			
		return static_cast<T>( distribution1(generator) * max  );

	} else {	//signed data
		//assuming range is symmetric about 0
		static std::uniform_real_distribution<double> distribution2(-1.0, 1.0);

		return static_cast<T>( distribution2(generator)  * max);

	}
}


template <typename T, size_t s>
inline void fill(std::array<T, s> &data) {
	for (auto& d : data)	
			d = generate_rand_type<T>();
}

inline void write(time_data data, const char* &file_location, const char* &type) {
	std::ofstream output(file_location, std::fstream::app);

	output << type << "&";
	output << data.mean_time << "&";
	output << data.std_time << "&";
	output << data.min_time << "&";
	output << data.max_time;
	output << "\\\\";
	output.close();

}

template<typename T>
inline time_data time_addition() {

	std::array<T, num_per_avg> data; 

	std::array<double, no_avg> times;	//time in milliseconds
	std::array<T, num_per_avg / 2> temp_data;

	for (size_t i = 0; i < no_avg; i++) {
		fill(data);
		const auto start = std::chrono::high_resolution_clock::now();
		for (size_t j = 0; j < num_per_avg; j+=2) {
			temp_data[j/2] = data[j] + data[j+1];
		}
		const auto end = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration<double, std::nano>(end-start).count() / num_per_avg;	//averaging the time of all runs

		//doing something with temp_data so it doesn't get optimsed away
		const auto it = std::find(temp_data.begin(), temp_data.end(), -0.001);	//should never find it
		if (it != temp_data.end()) {
			std::cout << "addition gave time -0.001" <<  std::endl;
		}
	}

	return create_time_data(times);
}


template<typename T>
inline time_data time_subtraction() {

	std::array<T, num_per_avg> data; 

	std::array<double, no_avg> times;	//time in milliseconds
	std::array<T, num_per_avg / 2> temp_data;

	for (size_t i = 0; i < no_avg; i++) {
		fill(data);
		const auto start = std::chrono::high_resolution_clock::now();
		for (size_t j = 0; j < num_per_avg; j+=2) {
			temp_data[j/2] = data[j] - data[j+1];
		}
		const auto end = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration<double, std::nano>(end-start).count() / num_per_avg;	//averaging the time of all runs

		//doing something with temp_data so it doesn't get optimsed away
		const auto it = std::find(temp_data.begin(), temp_data.end(), -0.001);	//will never find it
		if (it != temp_data.end()) {
			std::cout << "subtraction gave time -0.001" << std::endl;
		}
	}

	return create_time_data(times);
}
template<typename T>
inline time_data time_multiplication() {

	std::array<T, num_per_avg> data; 

	std::array<double, no_avg> times;	//time in milliseconds
	std::array<T, num_per_avg / 2> temp_data;

	for (size_t i = 0; i < no_avg; i++) {
		fill(data);
		const auto start = std::chrono::high_resolution_clock::now();
		for (size_t j = 0; j < num_per_avg; j+=2) {
			temp_data[j/2] = data[j] * data[j+1];
		}
		const auto end = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration<double, std::nano>(end-start).count() / num_per_avg;	//averaging the time of all runs

		//doing something with temp_data so it doesn't get optimsed away
		const auto it = std::find(temp_data.begin(), temp_data.end(), -0.001);	//will never find it
		if (it != temp_data.end()) {
			std::cout << "multiplication gave time -0.001" << std::endl;
		}
	}

	return create_time_data(times);
}
template<typename T>
inline time_data time_division() {

	std::array<T, num_per_avg> data; 

	std::array<double, no_avg> times;	//time in milliseconds
	std::array<T, num_per_avg / 2> temp_data;

	for (size_t i = 0; i < no_avg; i++) {
		fill(data);
		//making sure no element of data is 0
		for (auto& d : data) {
			if (d < 0.00001) {
				while (d < 0.00001) {
					d = generate_rand_type<T>();
				}
			}
		}

		const auto start = std::chrono::high_resolution_clock::now();
		for (size_t j = 0; j < num_per_avg; j+=2) {
			temp_data[j/2] = data[j] / data[j+1];
		}
		const auto end = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration<double, std::nano>(end-start).count() / num_per_avg;	//averaging the time of all runs

		//doing something with temp_data so it doesn't get optimsed away
		const auto it = std::find(temp_data.begin(), temp_data.end(), -0.001);	//will never find it
		if (it != temp_data.end()) {
			std::cout << "division gave time -0.001" << std::endl;
		}
	}

	return create_time_data(times);
}

template<typename T>
inline time_data time_sqrt() {

	std::array<T, num_per_avg> data; 

	std::array<double, no_avg> times;	//time in milliseconds
	std::array<T, num_per_avg> temp_data;

	for (size_t i = 0; i < no_avg; i++) {
		fill(data);
		//making sure all data is positive
		for (auto &d : data) {
			if (d < 0) {
				d = -d;
			}
		}
		const auto start = std::chrono::high_resolution_clock::now();
		for (size_t j = 0; j < num_per_avg; j++) {
			temp_data[j] = std::sqrt(data[j]);
		}
		const auto end = std::chrono::high_resolution_clock::now();
		times[i] = std::chrono::duration<double, std::nano>(end-start).count() / num_per_avg;	//averaging the time of all runs

		//doing something with temp_data so it doesn't get optimsed away
		const auto it = std::find(temp_data.begin(), temp_data.end(), -0.001);	//will never find it
		if (it != temp_data.end()) {
			std::cout << "sqrt gave time -0..01" << std::endl;
		}
	}

	return create_time_data(times);
}



template <typename T>
inline void write_all(const char* name) {
	std::cout << "addition\n";
	write(time_addition<T>(), addition_output, name);
	std::cout << "subtraction\n";
	write(time_subtraction<T>(), subtraction_output, name);
	std::cout << "multiplication\n";
	write(time_multiplication<T>(), multiplication_output, name);
	std::cout << "division\n";
	write(time_division<T>(), division_output, name);
	std::cout << "sqrt\n";
	write(time_sqrt<T>(), sqrt_output, name);
}
