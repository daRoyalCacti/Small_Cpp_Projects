#include <iostream>

#include <utility>
#include <array>
#include <cmath>

double halton_sequence_r(size_t index, unsigned base) {
    double f = 1;
    double r = 0;

    //unsigned  counter = 0;
    while (index>0) {
        f = f/base;
        r = r + f*static_cast<double>(index%base);
        index = static_cast<size_t>(index/base);
        //++counter;
    }
    //std::cout << counter << "\n";

    return r;
}


constexpr size_t halton_sequence_size = 1e4;

template <size_t Index, size_t Base, size_t counter>
struct Halton {
    static constexpr size_t i = Halton<Index, Base, counter+1>::i/ Base;
    static constexpr double f = Halton<Index, Base, counter+1>::f/Base;
    static constexpr double r = (Halton<Index, Base, counter+1>::i>0) ? (Halton<Index, Base, counter+1>::r + f*(Halton<Index, Base, counter+1>::i % Base)) : Halton<Index, Base, counter+1>::r;
};

/*template <size_t Index, size_t Base>
struct Halton<Index, Base, 0> {
    static constexpr size_t i = Index * Base;
    static constexpr double f = 1 * Base;
};*/

template <size_t Index, size_t Base>
struct Halton<Index, Base, 100> {   //some testing showed that for the first million numbers, only a depth of 20 was required --- 100 then should be plenty
    static constexpr size_t i = Index;
    static constexpr double f = 1;
    static constexpr double r = 0;
};

template <size_t Index, size_t Base>
struct Halton_i {
    static constexpr size_t i = Halton<Index, Base, 1>::i;
    static constexpr double f = Halton<Index, Base, 1>::f;
    static constexpr double r = Halton<Index, Base, 1>::r;
};


//for making the numbers accessable at runtime
template<size_t Base, size_t ... I>
double Halton_impl(std::index_sequence<I...>, size_t i) {
    constexpr std::array<double, sizeof...(I)> a = {Halton_i<I, Base>::r...};

    return a[i];
}
template<size_t Base>
double get_Halton(size_t i) {
    return Halton_impl<Base>(std::make_index_sequence<halton_sequence_size+1>(), i);
}


int main() {

    //halton_sequence_r(1e6, 2);


    for (int i = 0; i < 10; i++) {
        std::cout << halton_sequence_r(i+1, 2) << "\t" << get_Halton<2>(i+1) << "\n";
    }

    constexpr double epsilon = 1e-7;
    for (size_t i = 0; i < halton_sequence_size; i++) {
        if (fabs(halton_sequence_r(i+1, 2) - get_Halton<2>(i+1)) > epsilon) {
            std::cerr << "2 not equal, i = " << i << " Base = " << 2 << "\n";
        }
        if (fabs(halton_sequence_r(i+1, 3) - get_Halton<3>(i+1)) > epsilon) {
            std::cerr << "2 not equal, i = " << i << " Base = " << 3 << "\n";
        }
        /*if (fabs(halton_sequence_r(i+1, 4) - get_Halton<4>(i+1)) > epsilon) {
            std::cerr << "2 not equal, i = " << i << " Base = " << 4 << "\n";
        }
        if (fabs(halton_sequence_r(i+1, 5) - get_Halton<5>(i+1)) > epsilon) {
            std::cerr << "2 not equal, i = " << i << " Base = " << 5 << "\n";
        }
        if (fabs(halton_sequence_r(i+1, 6) - get_Halton<6>(i+1)) > epsilon) {
            std::cerr << "2 not equal, i = " << i << " Base = " << 6 << "\n";
        }*/
    }


    return 0;
}
