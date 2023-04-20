#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <cmath>

#define BYTE_SIZE 8
#define BOOL_SIZE 1

namespace lab_13 {

    template<typename T, std::size_t N>
    class my_array {
    private:
        char data[sizeof(T) * N];

        class proxy {
        private:
            char *data;
            std::size_t ind;
            std::size_t elem_size;
        public:
            proxy(char *data, int ind, int elem_size) : data(data), ind(ind), elem_size(elem_size) {}

            explicit operator T &() const {
                char *bytes = data + ind * elem_size;
                return *((T *) bytes);
            }

            proxy &operator=(T new_value) {
                void *new_value_void = &new_value;
                char *new_value_chr = (char *) new_value_void;

                for (int i = (int) (ind * elem_size / BYTE_SIZE), j = 0;
                     i < (int) ((ind + 1) * elem_size / BYTE_SIZE); i++, j++) {
                    data[i] = new_value_chr[j];
                }
                return *this;
            }

            proxy &operator=(const proxy &other) {
                data = other.data;
                ind = other.ind;
                elem_size = other.elem_size;
                return *this;
            }
        };


    public:
        my_array() = default;

        ~my_array() = default;

        T &operator[](std::size_t index) const {
            const proxy &temp = proxy(const_cast<char *>(data), index, sizeof(T) * BYTE_SIZE);
            return (T &) temp;
        }

        T &at(std::size_t index) const {
            if (index >= 0 && index < N) {

                const proxy &temp = proxy(const_cast<char *>(data), index, sizeof(T) * BYTE_SIZE);
                return (T &) temp;
            }
            throw std::out_of_range("");
        }

        proxy operator[](std::size_t index) {
            return proxy(const_cast<char *>(data), index, sizeof(T) * BYTE_SIZE);
        }

        bool empty() const {
            return N == 0;
        }

        std::size_t size() const {
            return N;
        }

        void fill(T val) {
            for (int i = 0; i < ((int) (N)); i++) {
                proxy(data, i, sizeof(T) * BYTE_SIZE) = val;
            }
        }
    };

    template<std::size_t N>
    class my_array<bool, N> {
    private:
        char data[(int) (ceil((double) N / BYTE_SIZE))];

        class proxy {
        private:
            char *data;
            std::size_t ind;
            std::size_t elem_size;
        public:
            proxy(char *data, int ind, int elem_size) : data(data), ind(ind), elem_size(elem_size) {}

            explicit operator bool &() const {

                char &byte = data[ind / BYTE_SIZE];
                const bool &elem = (byte >> (BYTE_SIZE - ind % BYTE_SIZE)) & 1;
                return (bool &) elem;

            }

            proxy &operator=(bool new_value) {
                void *new_value_void = &new_value;
                char *new_value_chr = (char *) new_value_void;
                char &byte = data[(int) (ind / BYTE_SIZE)];
                byte &= (int) ((1 << BYTE_SIZE) - (1 << (BYTE_SIZE - ind % BYTE_SIZE)) +
                               (1 << (BYTE_SIZE - (ind + 1) % BYTE_SIZE)) - 1);
                byte |= new_value_chr[0] << (BYTE_SIZE - ind % BYTE_SIZE);
                return *this;
            }

            proxy &operator=(const proxy &other) {
                data = other.data;
                ind = other.ind;
                elem_size = other.elem_size;
                return *this;
            }
        };


    public:
        my_array() = default;

        ~my_array() = default;

        bool &operator[](std::size_t index) const {
            const proxy &temp = proxy(const_cast<char *>(data), index,
                                      BOOL_SIZE);
            return (bool &) temp;
        }

        bool &at(std::size_t index) const {
            if (index >= 0 && index < N) {

                const proxy &temp = proxy(const_cast<char *>(data), index, BOOL_SIZE);
                return (bool &) temp;
            }
            throw std::out_of_range("");
        }

        proxy operator[](std::size_t index) {
            return proxy(const_cast<char *>(data), index, BOOL_SIZE);
        }

        bool empty() const {
            return N == 0;
        }

        std::size_t size() const {
            return N;
        }

        void fill(bool val) {
            for (int i = 0; i < ((int) (N)); i++) {
                proxy(data, i, BOOL_SIZE) = val;
            }
        }
    };
}

#endif
