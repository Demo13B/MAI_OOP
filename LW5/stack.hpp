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
    Stack()
        : _size(0), _alloc() { _data = new T*[MAX_SIZE]; }

    Stack(const Stack<T, MAX_SIZE, Alloc>& other) {
        _alloc;
        _size = other.size;
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