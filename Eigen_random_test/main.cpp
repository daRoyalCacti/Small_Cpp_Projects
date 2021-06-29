//https://eigen.tuxfamily.org/dox/modules.html
#include <iostream>
#include <random>
#include <chrono>
#include <vector>

#include <Eigen/Dense>

#define EIGEN_USE_MKL_ALL   //https://eigen.tuxfamily.org/dox/TopicUsingIntelMKL.html
                            //https://eigen.tuxfamily.org/dox/TopicUsingBlasLapack.html

using namespace Eigen;


typedef Vector3d vec3;

inline double random_double() {
    //Returns number from U[0,1)
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(const double min, const double max) {
    //Returns number from U[min, max)
    return min + (max-min)*random_double();
}

vec3 random_vec3() {
    return vec3(random_double(), random_double(), random_double());
}

vec3 random_vec3_1(const double a, const double b) {
    //return (b-a)*random_vec3() + vec3(a, a, a);
    return vec3(random_double(a, b), random_double(a, b), random_double(a, b));
}

vec3 random_vec3_2(const double a, const double b) {
    return (b-a)*random_vec3() + vec3(a, a, a);
}

constexpr unsigned N = 1e7;

int main() {
    std::vector<double> as, bs;
    as.resize(N); bs.resize(N);

    for (int i = 0; i < N; i++) {
        as[i] = random_double(-100, 100);
        bs[i] = random_double(-100, 100);
    }

    std::vector<vec3> res1, res2;
    res1.resize(N); res2.resize(N);

    const auto start1 = std::chrono::system_clock::now();
    for (int i = 0; i < N; i++)
        res1[i] = random_vec3_1(as[i], bs[i]);
    const auto end1 = std::chrono::system_clock::now();
    const std::chrono::duration<double> elapsed_seconds1 = end1- start1;

    const auto start2 = std::chrono::system_clock::now();
    for (int i = 0; i < N; i++)
        res2[i] = random_vec3_2(as[i], bs[i]);
    const auto end2 = std::chrono::system_clock::now();
    const std::chrono::duration<double> elapsed_seconds2 = end2- start2;

    int useless = 1;
    for (int i = 0; i < N; i++) {
        if (res1[i] != res2[i])
            useless = 0;
    }

        std::cout << "Some useless stuff so the compiler doesn't optimise away everything " << useless << "\n";
    std::cout << "for 1: " << elapsed_seconds1.count() << "s\n";
    std::cout << "for 2: " << elapsed_seconds2.count() << "s\n";
}

