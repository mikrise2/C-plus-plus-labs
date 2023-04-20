#include <iostream>
#include <cstring>
#include <assert.h>

#include "my_vector.hpp"

namespace product {

    class Product {
    public:
        Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price) {
            name_ = new char[strlen(name)];
            strcpy(name_, name);
        }

        friend std::ostream &operator<<(std::ostream &os, Product product) {
            return os << product.name_ << " " << product.quantity_ << " " << product.price_;
        }

    private:
        char *name_;
        int quantity_;
        double price_;
    };

}  // namespace product

using product::Product;

template<typename T>
void test_my_vector(const T t1, const T t2) {
    containers::my_vector<T> myVector;
    myVector.push_back(t1);
    myVector.push_back(t2);
    assert(myVector.size() == 2);
    myVector.pop_back();
    assert(myVector.size() == 1);
    assert(myVector.capacity() == 2);
}


int main() {
    containers::my_vector<int> v;
    v.push_back(2);
    const int n{3};
    v.push_back(n);
    std::cout << v << std::endl;

    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    return 0;
}
