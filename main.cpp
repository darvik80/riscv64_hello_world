#include <iostream>
#include <boost/lexical_cast.hpp>

int main() {
    std::cout << boost::lexical_cast<int>("1234") << std::endl;
    std::cout << "Да ладно" << std::endl;

    return 0;
}