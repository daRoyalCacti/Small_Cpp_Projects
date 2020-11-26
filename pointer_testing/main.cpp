#include <iostream>
#include <memory>
#include <future>
#include <type_traits>
const size_t size = 10;

void function(int** arr, const size_t s){
	*arr = new int[s];
}

void function2(int** arr, const size_t s){
	*arr[4] = 17;
	for (size_t i = 0; i < s; i++) {
		std::cout<< *arr[i] << std::endl;
	}
}


int main() {
	std::unique_ptr<int[]> array = std::make_unique<int[]>(size);
	for (size_t i = 0; i < size; i++) {
		array[i] = i;
	}

	std::future<void> ret = std::async(&function2, array.get(), size);

	ret.wait();
	std::cout << array[4] << std::endl;

	int* test;
	function(&test, size);
	test[2] = 4;


	return 0;
}
