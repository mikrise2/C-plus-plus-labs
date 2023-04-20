#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include "iterator"

namespace linq {
    namespace impl {
        template<typename T>
        class take_enumerator;

        template<typename T, typename Iter>
        class range_enumerator;

        template<typename T>
        class drop_enumerator;

        template<typename T, typename U, typename F>
        class select_enumerator;

        template<typename T, typename F>
        class until_enumerator;

        template<typename T>
        class until_eq_enumerator;

        template<typename T, typename F>
        class where_enumerator;

        template<typename T>
        class where_neq_enumerator;

        template<typename T>
        class enumerator {
        public:
            virtual const T &operator*() const = 0;

            virtual enumerator &operator++() = 0;

            virtual operator bool() const = 0;

            auto drop(int count) {
                return drop_enumerator<T>(*this, count);
            }

            auto take(int count) {
                return take_enumerator<T>(*this, count);
            }

            template<typename U = T, typename F>
            auto select(F func) {
                return select_enumerator<T, U, F>(*this, func);
            }

            template<typename F>
            auto until(F func) {
                return until_enumerator<T, F>(*this, func);
            }

            template<typename F>
            auto where(F predicate) {
                return where_enumerator(*this, predicate);
            }

            auto where_neq(T element) {
                return where_neq_enumerator(*this, element);
            }

            auto until_eq(T element) {
                return until_eq_enumerator<T>(*this, element);
            }

            std::vector <T> to_vector() {
                std::vector <T> result;
                while (*this) {
                    auto temp = **this;
                    result.push_back(temp);
                    ++*this;
                }
                return result;
            }

            template<typename Iter>
            void copy_to(Iter it) {
                while (*this) {
                    it++ = **this;
                    ++*this;
                }
            }
        };

        template<typename T, typename Iter>
        class range_enumerator : public enumerator<T> {
        public:
            range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {
            }

            virtual const T &operator*() const {
                return *begin_;
            }

            virtual enumerator<T> &operator++() {
                ++begin_;
                return *this;
            }

            virtual operator bool() const {
                return begin_ != end_;
            }

        private:
            Iter begin_, end_;
        };

        template<typename T>
        class drop_enumerator : public enumerator<T> {
        public:
            drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
                while (count > 0 && (bool) parent_) {
                    ++parent_;
                    count--;
                }
            }

            virtual const T &operator*() const {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                return *this;
            }

            virtual operator bool() const {
                return (bool) parent_;
            }

        private:
            enumerator<T> &parent_;
        };

        template<typename T, typename U, typename F>
        class select_enumerator : public enumerator<U> {
        public:
            select_enumerator(enumerator<T> &parent, F func) : parent_(parent), func(func) {
            }

            virtual const U &operator*() const {
                U &&res = func(static_cast<U>(*parent_));
                return res;
            }

            virtual enumerator<U> &operator++() {
                ++parent_;
                return *this;
            }

            virtual operator bool() const {
                return (bool) parent_;
            }

        private:
            enumerator<T> &parent_;
            const F func;
        };

        template<typename T, typename F>
        class until_enumerator : public enumerator<T> {
        public:
            until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate(predicate) {
            }

            virtual const T &operator*() const {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                return *this;
            }

            virtual operator bool() const {
                return !predicate(parent_) && (bool) parent_;
            }

        private:
            enumerator<T> &parent_;
            const F predicate;
        };

        template<typename T>
        class until_eq_enumerator : public enumerator<T> {
        public:
            until_eq_enumerator(enumerator<T> &parent, T element) : parent_(parent), element(element) {
            }

            virtual const T &operator*() const {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                return *this;
            }

            virtual operator bool() const {
                return element != **this && (bool) parent_;
            }

        private:
            enumerator<T> &parent_;
            const T element;
        };

        template<typename T, typename F>
        class where_enumerator : public enumerator<T> {
        public:
            where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent), predicate(predicate) {
            }

            virtual const T &operator*() const {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                return *this;
            }

            virtual operator bool() const {
                while ((bool) parent_ && !predicate(*parent_))
                    ++parent_;
                return (bool) parent_;
            }

        private:
            enumerator<T> &parent_;
            const F predicate;
        };

        template<typename T>
        class where_neq_enumerator : public enumerator<T> {
        public:
            where_neq_enumerator(enumerator<T> &parent, T element) : parent_(parent), element(element) {
            }

            virtual const T &operator*() const {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                ++parent_;
                return *this;
            }

            virtual operator bool() const {
                while ((bool) parent_ && **this == element)
                    ++parent_;
                return (bool) parent_;
            }

        private:
            enumerator<T> &parent_;
            const T element;
        };

        template<typename T>
        class take_enumerator : public enumerator<T> {
        public:
            take_enumerator(enumerator<T> &parent, int count) : count(count), parent_(parent) {}

            virtual const T &operator*() const {
                return *parent_;
            }

            virtual enumerator<T> &operator++() {
                --count;
                if (count > 0)
                    ++parent_;
                return *this;
            }

            virtual operator bool() const {
                return count > 0 && (bool) parent_;
            }

        private:
            int count;
            enumerator<T> &parent_;
        };

    } // namespace impl

    template<typename Itr>
    auto from(Itr begin, Itr end) {
        return std::move(impl::range_enumerator<typename std::iterator_traits<Itr>::value_type, Itr>(begin, end));

    }

} // namespace linq

#endif
