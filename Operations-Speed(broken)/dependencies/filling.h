#include <limits>
#include <fstream>
#include <cmath>
#include <chrono>

typedef double large_data; /*__int128_t*/

template <typename T, typename U>
/*__attribute__((const))*/ inline void fill(T* data, U num) {
  const large_data min = std::numeric_limits<T>::min();
  const large_data max = std::numeric_limits<T>::max();
  const large_data range = max - min;

  for (U i = 0; i < num; i++) {
    data[i] = static_cast<T>(rand() * (range / RAND_MAX) + min );
  }

}

template <typename T, typename U>
inline void write(T* times, U num, const char* file_location, const char* type) {
  T temp_mean = U(0);
  for (U i = 0; i < num; i++) {
    temp_mean += times[i];
  }

  const double mean = temp_mean / double(num);

  double temp_sd = 0;
  for (U i = 0; i < num; i++) {
    temp_sd += (times[i] - mean) * (times[i] - mean);
  }

  const double sd = sqrt(temp_sd / (double)(num - U(1)));

  T min = std::numeric_limits<T>::max();
  for (U i = 0; i < num; i++) {
    if (times[i] < min) {
      min = times[i];
    }
  }

  T max = std::numeric_limits<T>::min();
  for (U i = 0; i < num; i++) {
    if (times[i] > max) {
      max = times[i];
    }
  }

  std::ofstream output(file_location, std::fstream::app);

  output << type << "&";
  output << mean << "&";
  output << sd << "&";
  output << min << "&";
  output << max;
  output << "\\\\";
  output.close();

}

template<typename T, typename U>
inline double* time_addition(T* data, U num) {
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  volatile T temp;
  T left, right;
  double* times = new double[num / 2];
  U counter = 0;
  for (U i = 0; i < num; i+=2, counter++) {
    left = data[i];
    right = data[i + 1];
    start = std::chrono::high_resolution_clock::now();
    temp = left + right;
    end = std::chrono::high_resolution_clock::now();
    temp++; //compiler seems to be some sort of undesired optimations without this
    times[counter] = std::chrono::duration<double, std::nano>(end - start).count();
  }
  return times;
}

template<typename T, typename U>
inline double* time_subtraction(T* data, U num) {
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  T temp;
  T left, right;
  double* times = new double[num / 2];
  U counter = 0;
  for (U i = 0; i < num; i+=2, counter++) {
    left = data[i];
    right = data[i + 1];
    start = std::chrono::high_resolution_clock::now();
    temp = left - right;
    end = std::chrono::high_resolution_clock::now();
    temp++;
    times[counter] = std::chrono::duration<double, std::nano>(end - start).count();
  }

  return times;
}

template<typename T, typename U>
inline double* time_division(T* data, U num) {
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  volatile T temp;
  T left, right;
  double* times = new double[num / 2];
  U counter = 0;
  for (U i = 0; i < num; i+=2, counter++) {
    left = data[i];
    right = data[i + 1];
    start = std::chrono::high_resolution_clock::now();
    temp = left / (double)right;
    end = std::chrono::high_resolution_clock::now();
    temp++;
    times[counter] = std::chrono::duration<double, std::nano>(end - start).count();
  }

  return times;
}

template<typename T, typename U>
inline double* time_multiplication(T* data, U num) {
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  volatile T temp;
  T left, right;
  double* times = new double[num / 2];
  U counter = 0;
  for (U i = 0; i < num; i+=2, counter++) {
    left = data[i];
    right = data[i + 1];
    start = std::chrono::high_resolution_clock::now();
    temp = left * right;
    end = std::chrono::high_resolution_clock::now();
    temp++;
    times[counter] = std::chrono::duration<double, std::nano>(end - start).count();
  }

  return times;
}

template<typename T, typename U>
inline double* time_sqrt(T* data, U num) {
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  volatile T temp;
  T left;
  double* times = new double[num];
  for (U i = 0; i < num; i++) {
    left = data[i];
    start = std::chrono::high_resolution_clock::now();
    temp = sqrt(left);
    end = std::chrono::high_resolution_clock::now();
    temp++;
    times[i] = std::chrono::duration<double, std::nano>(end - start).count();
  }

  return times;
}
