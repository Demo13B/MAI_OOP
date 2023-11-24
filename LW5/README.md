# Лабораторная работа 5. Итераторы и аллокаторы
## Автор: Салихов Тимур, группа М8О-212Б-22, вариант 2
1. Аллокатор
- a. Реализовать свой аллокатор памяти. Проверить что он корректно работает для контейнера std::map.
- b. Аллокатор должен параметризоваться количеством выделяемых за раз элементов.
- c. Освобождение конкретного элемента не предполагается - аллокатор должен освобождать всю память самостоятельно.
2. Контейнер
- a. Реализовать свой контейнер (согласно варианта задания), который по аналогии с контейнерами stl, параметрезуя аллокатором.
3. Итератор
- a. Реализовать итераторы (обычный и const)
- b. Итератор должен соответствовать std::forward_iterator_tag

Прикладной код должен содержать следующие вызовы:
- создание экземпляра std::map с созданным аллокатором
- заполнение 10 элементами, где ключ — это число от 0 до 9, а значение - факториал ключа
- вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
- создание экземпляра своего контейнера для хранения int с собственным vаллокатором – заполнение контейнера и печать его элементов

Вариант 2: Контейнер: Стек, Аллокатор: std::vector

## Программы

### main.cpp
```cpp
#include <iostream>
#include <map>
#include "allocator.hpp"
#include "stack.hpp"

auto main() -> int {
    // Map doesn't want to work on Mac for some reason, on Linux works as intended
    //
    // std::map<int, int, std::less<int>, mai::Allocator<std::pair<const int, int>>> m;
    // m[0] = 1;
    // for (size_t i = 1; i != 10; ++i) {
    //     m[i] = m[i - 1] * i;
    // }

    // std::cout << "Here are the elements of map: " << std::endl;
    // for (auto [k, v] : m) {
    //     std::cout << k << " " << v << std::endl;
    // }

    // Allocator with standard containers
    std::vector<int, mai::Allocator<int>> v(10);
    v[0] = 1;
    for (size_t i = 1; i != 10; ++i) {
        v[i] = v[i - 1] * i;
    }

    std::cout << "Here are the elements of a vector: " << std::endl;
    for (size_t i = 0; i != 10; ++i) {
        std::cout << i << " " << v[i] << std::endl;
    }
    std::cout << std::endl;

    // Custom STL container
    mai::Stack<int, 100, mai::Allocator<int>> s;
    for (size_t i = 0; i != 10; ++i)
        s.push(rand() % 100);

    std::cout << s << std::endl;

    for (size_t i = 0; i != 3; ++i)
        s.pop();

    std::cout << s << std::endl;

    for (size_t i = 0; i != 3; ++i)
        s.push(rand() % 100);

    std::cout << s << std::endl;

    return 0;
}

```

### allocator.hpp
```cpp
#pragma once
#include <memory>
#include <vector>

namespace mai {
template <class T, size_t SIZE = 1000>
class Allocator {
   public:
    std::vector<T> data;
    size_t free_slots;

    using value_type = T;
    using pointer = T*;
    using const_ointer = const T*;
    using size_type = size_t;

    Allocator() {
        data.resize(SIZE);
        free_slots = SIZE;
    }

    ~Allocator() = default;

    auto allocate(size_t n) -> pointer {
        if (n > free_slots) {
            throw std::bad_alloc();
        }

        free_slots -= n;

        return &data[free_slots];
    }

    auto deallocate(pointer p, size_t n) -> void {
        free_slots += n;
    }

    template <class U, class... Args>
    auto construct(U* p, Args&&... args) -> void {
        new (p) U(std::forward<Args>(args)...);
    }

    auto destroy(pointer p) -> void {
        p->~T();
    }

    template <class U>
    struct rebind {
        using other = Allocator<U>;
    };
};

template <class T, class U>
constexpr auto operator==(const Allocator<T>& lhs, const Allocator<U>& rhs) -> bool {
    return true;
}

template <class T, class U>
constexpr auto operator!=(const Allocator<T>& lhs, const Allocator<U>& rhs) -> bool {
    return false;
}

}  // namespace mai
```

### stack.hpp
```cpp
#pragma once
#include <memory>

namespace mai {
template <class T, size_t MAX_SIZE = 100, class Alloc = std::allocator<T>>
class Stack {
   private:
    T** _data;
    size_t _size;

    using Alloc_traits = std::allocator_traits<Alloc>;
    Alloc _alloc;

   public:
    class Iterator {
       private:
        friend Stack;
        T** _p;

       public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        Iterator()
            : _p(nullptr) {}

        Iterator(T** p)
            : _p(p) {}

        ~Iterator() noexcept {
            _p = nullptr;
        }

        inline auto operator*() const -> reference {
            return **_p;
        }

        inline auto operator++() -> Iterator& {
            ++_p;
            return *this;
        }

        inline auto operator++(int) -> Iterator {
            Iterator tmp = *this;
            ++_p;
            return tmp;
        }

        inline auto operator==(const Iterator& other) const -> bool {
            return _p == other._p;
        }

        inline auto operator!=(const Iterator& other) const -> bool {
            return _p != other._p;
        }
    };

    class ConstIterator {
       private:
        friend Stack;
        T** _p;

       public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        ConstIterator()
            : _p(nullptr) {}

        ConstIterator(T** p)
            : _p(p) {}

        ~ConstIterator() noexcept {
            _p = nullptr;
        }

        inline auto operator*() const -> value_type {
            value_type res = **_p;
            return res;
        }

        inline auto operator++() -> ConstIterator& {
            ++_p;
            return *this;
        }

        inline auto operator++(int) -> ConstIterator {
            ConstIterator tmp = *this;
            ++_p;
            return tmp;
        }

        inline auto operator==(const ConstIterator& other) const -> bool {
            return _p == other._p;
        }

        inline auto operator!=(const ConstIterator& other) const -> bool {
            return _p != other._p;
        }
    };

    auto begin() noexcept -> Iterator {
        return Iterator(_data);
    }

    auto end() noexcept -> Iterator {
        return Iterator(_data + _size);
    }

    auto cbegin() const noexcept -> ConstIterator {
        return ConstIterator(_data);
    }

    auto cend() const noexcept -> ConstIterator {
        return ConstIterator(_data + _size);
    }

    Stack()
        : _size(0), _alloc() { _data = new T*[MAX_SIZE]; }

    Stack(const Stack<T, MAX_SIZE, Alloc>& other) {
        _size = other._size;
        for (size_t i = 0; i != _size; ++i) {
            _data[i] = Alloc_traits::allocate(_alloc, 1);
            *_data[i] = *other._data[i];
        }
    }

    ~Stack() noexcept {
        for (size_t i = 0; i != _size; ++i) {
            Alloc_traits::destroy(_alloc, _data[i]);
            Alloc_traits::deallocate(_alloc, _data[i], 1);
        }

        delete[] _data;
        _size = 0;
    }

    inline auto size() const -> size_t {
        return _size;
    }

    inline auto empty() const -> bool {
        return _size == 0;
    }

    inline auto push(const T& element) -> void {
        _data[_size] = Alloc_traits::allocate(_alloc, 1);
        *_data[_size] = element;
        _size++;
    }

    inline auto pop() -> T {
        _size--;
        T value = *_data[_size];
        Alloc_traits::destroy(_alloc, _data[_size]);
        Alloc_traits::deallocate(_alloc, _data[_size], 1);
        return value;
    }

    inline auto operator=(const Stack<T, MAX_SIZE, Alloc>& other) -> Stack& {
        for (size_t i = 0; i != _size; ++i) {
            Alloc_traits::destroy(_alloc, _data[i]);
            Alloc_traits::deallocate(_alloc, _data[i], 1);
        }

        _size = other._size;

        for (size_t i = 0; i != _size; ++i) {
            _data[i] = Alloc_traits::allocate(_alloc, 1);
            *_data[i] = *other._data[i];
        }

        return *this;
    }

    inline auto operator[](size_t index) const -> T {
        T value = *_data[index];
        return value;
    }
};

template <class T, size_t MAX_SIZE = 100, class Alloc>
inline auto operator<<(std::ostream& os, const Stack<T, MAX_SIZE, Alloc>& s) -> std::ostream& {
    os << "Stack elements: ";

    for (size_t i = 0; i != s.size(); ++i) {
        os << s[i] << " ";
    }

    return os;
}
}  // namespace mai
```

### tests.cpp
```cpp
#include <gtest/gtest.h>
#include "allocator.hpp"
#include "stack.hpp"

TEST(TestS1, Test1) {
    ASSERT_TRUE(1 == 1);
}

TEST(Allocator, Vector_push_back) {
    std::vector<int, mai::Allocator<int>> v;
    v.push_back(42);
    v.push_back(13);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 13);
}

TEST(Allocator, Vector_deleting_elements) {
    std::vector<int, mai::Allocator<int>> v;
    v.push_back(42);
    v.push_back(13);
    v.pop_back();
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v.size(), 1);
}

TEST(Allocator, Vector_changing_elements) {
    std::vector<int, mai::Allocator<int>> v;
    v.push_back(42);
    v.push_back(13);
    v.pop_back();
    v.push_back(5);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 5);
}

TEST(Stack, push) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    EXPECT_EQ(s[0], 42);
    EXPECT_EQ(s[1], 15);
}

TEST(Stack, pop) {
    mai::Stack<int, 2, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(5);
    int n = s.pop();
    EXPECT_EQ(n, 5);
}

TEST(Stack, pop_and_push) {
    mai::Stack<int, 2, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(5);
    EXPECT_EQ(s[0], 42);
    EXPECT_EQ(s[1], 5);
    int n = s.pop();
    s.push(67);
    EXPECT_EQ(n, 5);
    EXPECT_EQ(s[0], 42);
    EXPECT_EQ(s[1], 67);
}

TEST(Stack, size) {
    mai::Stack<int, 2, mai::Allocator<int, 2>> s;
    EXPECT_EQ(s.size(), 0);
    s.push(13);
    EXPECT_EQ(s.size(), 1);
    s.push(32);
    EXPECT_EQ(s.size(), 2);
    s.pop();
    s.pop();
    EXPECT_EQ(s.size(), 0);
}

TEST(Stack, empty) {
    mai::Stack<int, 2, mai::Allocator<int, 2>> s;
    EXPECT_TRUE(s.empty());
    s.push(1);
    EXPECT_FALSE(s.empty());
    s.pop();
    EXPECT_TRUE(s.empty());
}

TEST(Stack, copy_operator) {
    mai::Stack<int, 10, mai::Allocator<int, 10>> s1;
    mai::Stack<int, 10, mai::Allocator<int, 10>> s2;
    s1.push(2);
    s1.push(3);
    s2 = s1;
    EXPECT_EQ(s2[0], 2);
    EXPECT_EQ(s2[1], 3);
}

TEST(Iterator, begin) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.begin();
    EXPECT_EQ(*it, 42);
}

TEST(Iterator, increment) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.begin();
    EXPECT_EQ(*it, 42);
    ++it;
    EXPECT_EQ(*it, 15);
}

TEST(Iterator, change_value) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.begin();
    EXPECT_EQ(*it, 42);
    *it = 4;
    EXPECT_EQ(s[0], 4);
}

TEST(ConstIterator, begin) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.cbegin();
    EXPECT_EQ(*it, 42);
}

TEST(ConstIterator, increment) {
    mai::Stack<int, 100, mai::Allocator<int, 2>> s;
    s.push(42);
    s.push(15);
    auto it = s.cbegin();
    EXPECT_EQ(*it, 42);
    ++it;
    EXPECT_EQ(*it, 15);
}

```