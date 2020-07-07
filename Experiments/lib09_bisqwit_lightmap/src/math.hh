#ifndef bqtMathHH
#define bqtMathHH

#include <cmath>
#include <array>
#include <functional>

template<typename T, std::size_t MinSz = 1, std::size_t MaxSz = ~std::size_t{}>
concept IsTuple = requires (T t) { {std::get<0>(t) };} and (std::tuple_size_v<std::remove_cvref_t<T>>-MinSz) <= (MaxSz-MinSz);

template<typename T, typename U, std::size_t MinSz = 1, std::size_t MaxSz = ~std::size_t{}>
concept ArithPair = IsTuple<T,MinSz,MaxSz> and (IsTuple<U,MinSz,MaxSz> or std::is_arithmetic_v<std::remove_cvref_t<U>>);

// AsTuple: Flattens any number of tuples/pairs/arrays/elements into a single std::tuple
template<typename T, typename... A>
auto AsTuple(T&& t, A&&... args)
{
    if constexpr(sizeof...(args)) return std::tuple_cat(AsTuple(std::forward<T>(t)), AsTuple(std::forward<A>(args)...));
    else if constexpr(!IsTuple<T>) return std::tuple{ t }; // If not tuple/pair/array
    else if constexpr(!requires{ t[0]; }) return std::forward<T>(t); // If already tuple
    else return std::apply([&]<class...U>(U&&... p) { return std::tuple<std::decay_t<U>...>{ p... }; }, std::forward<T>(t));
}

// AsArray: Flattens any number of tuples/pairs/arrays/elements into a single std::array
template<typename ForcedType, typename... T>
using TypeReturn = std::conditional_t<std::is_same_v<ForcedType,void>, std::common_type_t<T...>, ForcedType>;

template<typename ForcedType = void, typename T, typename... A>
auto AsArray(T&& t, A&&... args)
{
    if constexpr(sizeof...(args)) return AsArray<ForcedType>(AsTuple(std::forward<T>(t), std::forward<A>(args)...));
    else if constexpr(!IsTuple<T>) return std::array{ TypeReturn<ForcedType,T>(t) }; // If not tuple/pair/array
    else return std::apply([&]<class...U>(U&&... p) { return std::array{ TypeReturn<ForcedType,U...>(p)...}; }, std::forward<T>(t));
}

// Sum: Sum of vector elements
auto Sum(const auto& vec) requires IsTuple<decltype(vec)>
{
    return std::apply([](auto&&... v) { return (v + ...); }, vec);
}

// Reduce: Reduce vectors and scalars into a single vector using a functor
// N = number of elements in the resulting vector, which is the minimum of sizes of the source vectors.
template<typename binaryop = std::multiplies<void>, typename T, typename U, typename... R,
         bool IsScalar = std::is_arithmetic_v<U>,
         bool IsArray  = requires{ T{}[0]; },
         std::size_t Tsize = std::tuple_size_v<T>,
         std::size_t N     = std::min(Tsize, std::conditional_t<IsScalar, std::integral_constant<std::size_t,Tsize>,
                                                                          std::tuple_size<U>>::value)>
auto Reduce(const T& vec, const U& val, R&&... more) requires (ArithPair<T,U> && ... && ArithPair<T,R>)
{
    // Reduce using the binary operator. Choose a different path depending on whether U is a scalar or not.
    auto result = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        /**/ if constexpr( IsScalar&& IsArray) return AsArray( binaryop{}(std::get<I>(vec), val) ... );
        else if constexpr( IsScalar&&!IsArray) return AsTuple( binaryop{}(std::get<I>(vec), val) ... );
        else if constexpr(!IsScalar&& IsArray) return AsArray( binaryop{}(std::get<I>(vec), std::get<I>(val)) ... );
        else if constexpr(!IsScalar&&!IsArray) return AsTuple( binaryop{}(std::get<I>(vec), std::get<I>(val)) ... );
    } (std::make_index_sequence<N>{});

    // If more than two operands were given, apply the reduction left-recursively with the rest of the operands.
    if constexpr(sizeof...(more)) return Reduce<binaryop>(std::move(result), std::forward<R>(more)...);
    return result;
}

#if 0
// This is what I did in the video
auto operator +(auto&& a, auto&& b) requires ArithPair<decltype(a),decltype(b)> { return Reduce<std::plus<void>>(a,b); }
auto operator -(auto&& a, auto&& b) requires ArithPair<decltype(a),decltype(b)> { return Reduce<std::minus<void>>(a,b); }
auto operator /(auto&& a, auto&& b) requires ArithPair<decltype(a),decltype(b)> { return Reduce<std::divides<void>>(a,b); }
auto operator *(auto&& a, auto&& b) requires ArithPair<decltype(a),decltype(b)> { return Reduce<std::multiplies<void>>(a,b); }
#elif 1
// This is how it _should_ be. These lines are just a bit too verbose for comfortable viewing.
template<class A, class B> auto operator +(A&& a, B&& b) requires ArithPair<A,B> { return Reduce<std::plus<void>>(std::forward<A>(a), std::forward<B>(b)); }
template<class A, class B> auto operator -(A&& a, B&& b) requires ArithPair<A,B> { return Reduce<std::minus<void>>(std::forward<A>(a), std::forward<B>(b)); }
template<class A, class B> auto operator /(A&& a, B&& b) requires ArithPair<A,B> { return Reduce<std::divides<void>>(std::forward<A>(a), std::forward<B>(b)); }
template<class A, class B> auto operator *(A&& a, B&& b) requires ArithPair<A,B> { return Reduce<std::multiplies<void>>(std::forward<A>(a), std::forward<B>(b)); }
#else
// This won’t even compile. Worth a shot though…
template<class... A> auto operator +(A&&... a) requires ArithPair<A...> { return Reduce<std::plus<void>>(std::forward<A>(a)...); }
#endif

// Dot product and other utilities
template<typename T, typename U = T>
auto Dot(const T& vec, const U& vec2) { return Sum(vec * vec2); }
auto Length(const auto& vec)          { return std::sqrt(Dot(vec, vec)); }
auto Normalized(const auto& vec)      { return vec * (1 / Length(vec)); }
auto CrossProduct(const auto& vec) requires IsTuple<decltype(vec),6,6>
{
    auto Merge = []<std::size_t...I>(auto op,std::index_sequence<I...>, auto src)
    {
        return Reduce<decltype(op)>(std::array{ std::get<I/10>(src)... }, std::array{ std::get<I%10>(src)... });
    };
    return Merge(std::minus<void>{},      std::index_sequence<01,23,45>{},
           Merge(std::multiplies<void>{}, std::index_sequence<15,24,23,05,04,13>{}, vec));
}
auto CrossProduct(const auto& a, const auto& b) requires IsTuple<decltype(a),3> and IsTuple<decltype(b),3>
{
    return CrossProduct(std::tuple{std::get<0>(a), std::get<1>(a), std::get<2>(a),
                                   std::get<0>(b), std::get<1>(b), std::get<2>(b)});
}

class Plane
{
    std::array<float,3> normal;
    float               distance;
public:
    template<typename T>
    Plane(const T& p) requires IsTuple<T,3,3> and ArithPair<std::tuple_element_t<2,T>,std::tuple_element_t<0,T>,3,3>
    {
        // Calculate the normal of the plane: (b-a)×(c-a)
        normal = Normalized(CrossProduct(std::tuple_cat(std::get<1>(p)/*b*/, std::get<2>(p)/*c*/)
                                       - std::tuple_cat(std::get<0>(p)/*a*/, std::get<0>(p)/*a*/)));
        distance = Dot(normal, std::get<0>(p)); // (any of the three points works)
    }
    auto DistanceTo(const auto& point) const { return Dot(normal, point) - distance; } // (normal · point) - distance
    auto GetDistance() const                 { return distance; }
    auto GetNormal() const                   { return normal; }
};

// Alias for backwards compatibility in web version
template<typename op = std::multiplies<void>, typename T = std::array<float,3>, typename U = T, typename... R>
auto Mul(T&& t, U&& u, R&&... rest) { return Reduce<op>(std::forward<T>(t),std::forward<U>(u),std::forward<R>(rest)...); }

#endif
