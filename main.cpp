#include <iostream>
#include <list>
#include <vector>
#include <cstdint>


template <typename T,
    typename Fake = typename std::enable_if<
        // std::is_same<typename std::remove_reference<T>::type, std::string>::value, 
        std::is_same<T, std::string>::value, 
        void>::type>
auto impl(T t, int) {
    std::cout << t << std::endl;
}


template <typename T>
auto impl(T t, long) -> decltype(t.clear()) {
    uint i = 0;
    for (auto el : t) {
        std::cout << el;
        if (i < (t.size() - 1)) std::cout << ".";
        else                    std::cout << std::endl;
        i++;
    }
}


template <typename T, typename T2=void,
    typename Fake = typename std::enable_if<
        // std::is_integral<typename std::remove_reference<T>::type>::value, 
        std::is_integral<T>::value, 
        void>::type>
auto impl(T t, int) {
    uint8_t*    p = (uint8_t *)&t;
    for (int i = sizeof(T) - 1; i >= 0 ; --i) {
        std::cout << (int)p[i];
        if (i > 0)  std::cout << ".";
        else        std::cout << std::endl;
    }
}


template <typename T>
auto print_ip(T t) {
    impl(t, 20);
}


int main() {
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    //print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0    

    return 0;
}