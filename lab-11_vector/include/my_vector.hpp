#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include "algorithm"
#include "iostream"

namespace containers {

    template<typename T>
    class my_vector {
    public:
        my_vector();
        explicit my_vector(std::size_t n);
        my_vector(my_vector& other);
        my_vector& operator=(const my_vector& other);
        ~my_vector();

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

        void resize(std::size_t n);
        void reserve(std::size_t n);

        T& operator[](std::size_t index);

        void push_back(const T& t);
        void pop_back();
        void clear();

        friend std::ostream& operator<<(std::ostream& os, my_vector vector){
            for(std::size_t i=0;i<vector.size_;i++){
                os<<vector.array_[i];
                if(i!=vector.size_-1)
                    os<<" ";
            }
            return os;
        }

        friend std::istream& operator>>(std::iostream & is, my_vector vector){
            for(std::size_t i=0;i<vector.size_;i++){
                is>>vector.array_[i];
            }
            return is;
        }

    private:
        size_t capacity_;
        size_t size_;
        T* array_;

        friend void swap(my_vector& first, my_vector& second) {
            using std::swap;
            swap(first.size_, second.size_);
            swap(first.capacity_, second.capacity_);
            for(std::size_t i =0;i<first.size_;i++){
                new(first.array_+i) T(second.array_[i]);
            }
        }
    };

}

#include "my_vector_impl.hpp"

#endif  // MY_VECTOR_H_
