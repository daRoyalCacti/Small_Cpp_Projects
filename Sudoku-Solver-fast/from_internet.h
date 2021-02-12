#pragma once

//generating an integer sequence starting from 0 at compile time
//https://ngathanasiou.wordpress.com/2015/02/19/compile-time-integer-sequences/
// a sequence container -------------------------
template<int ...>
struct ints 
{ 
};
// integer sequence -----------------------------
template<int N, int... Is>
struct int_seq : int_seq<N - 1, N, Is...> 
{ 
};

template<int... Is>
struct int_seq<0, Is...> 
{
	using type = ints<0, Is...>;
};
// convenience alias -----------------------------
template<int N>
using IS = typename int_seq<N>::type; 	//IS := integer sequence
//IS<4> returns ints<0,1,2,3,4>



//generating an array full of a constant value
//https://stackoverflow.com/questions/1065774/initialization-of-all-elements-of-an-array-to-one-default-value-in-c
template<std::size_t size, typename T, std::size_t... indexes>
constexpr auto make_array_n_impl(T && value, std::index_sequence<indexes...>) {
    // Use the comma operator to expand the variadic pack
    // Move the last element in if possible. Order of evaluation is well-defined
    // for aggregate initialization, so there is no risk of copy-after-move
    return std::array<std::decay_t<T>, size>{ (static_cast<void>(indexes), value)..., std::forward<T>(value) };
}



template<typename T>
constexpr auto make_array_n(std::integral_constant<std::size_t, 0>, T &&) {
    return std::array<std::decay_t<T>, 0>{};
}

template<std::size_t size, typename T>
constexpr auto make_array_n(std::integral_constant<std::size_t, size>, T && value) {
    return make_array_n_impl<size>(std::forward<T>(value), std::make_index_sequence<size - 1>{});
}


template<std::size_t size, typename T>
constexpr auto make_array_n(T && value) {
    return make_array_n(std::integral_constant<std::size_t, size>{}, std::forward<T>(value));
}
//make_array_n<5>(2) returns {2,2,2,2,2}

