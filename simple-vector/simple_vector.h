#pragma once
#include "array_ptr.h"

#include <cassert>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <iterator>

class ReserveProxyObj {
public:
    explicit ReserveProxyObj (size_t capacity_to_reserve)
        :capacity_(capacity_to_reserve)
    {
    }

    size_t ReserveCapasity(){
        return capacity_;
    }

private:
    size_t capacity_;

};

ReserveProxyObj Reserve(size_t capacity_to_reserve) {
    return ReserveProxyObj(capacity_to_reserve);
}

template <typename Type>
class SimpleVector {
public:
    using Iterator = Type*;
    using ConstIterator = const Type*;

    SimpleVector() noexcept = default;

    explicit SimpleVector(size_t size)
        : SimpleVector(size, Type{})
    {
    }

    SimpleVector(size_t size, const Type& value)
        : items_(size),
          size_(size),
          capacity_(size)
    {
        std::fill(items_.Get(), items_.Get() + size_, value);
    }

    SimpleVector(std::initializer_list<Type> init)
        : items_(init.size()),
          size_(init.size()),
          capacity_(init.size())
    {
        std::copy(init.begin(), init.end(), items_.Get());
    }

    SimpleVector(const SimpleVector& other)
        : items_(other.size_),
          size_{other.size_},
          capacity_{other.capacity_}
    {
        std::uninitialized_copy(other.begin(), other.end(), items_.Get());
    }

    SimpleVector(SimpleVector&& other) {
        this->swap(other);
    }

    SimpleVector& operator=(const SimpleVector& rhs) {
        if (this != &rhs) {
            if (rhs.IsEmpty()) {
                Clear();
                return *this;
            }
            SimpleVector<Type> tmp(rhs.size_);
            std::uninitialized_copy(rhs.begin(), rhs.end(), tmp.begin());
            this->swap(tmp);
        }
        return *this;
    }

    SimpleVector& operator=(SimpleVector&& rhs) {
        if (this != &rhs) {
            if (rhs.IsEmpty()) {
                Clear();
                return *this;
            }
            this->swap(rhs);
        }
        return *this;
    }

    Type& operator[](size_t index) noexcept {
        assert(size_ >= index);
        return items_[index];
    }

    const Type& operator[](size_t index) const noexcept {
        assert(size_ >= index);
        return items_[index];
    }

    Type& At(size_t index) {
        if (!(index < size_)) {
            throw std::out_of_range("range error\n");
        }
        return items_[index];
    }

    const Type& At(size_t index) const {
        if (!(index < size_)) {
            throw std::out_of_range("range error\n");
        }
        return items_[index];
    }

    size_t GetSize() const noexcept {
        return size_;
    }

    size_t GetCapacity() const noexcept {
        return capacity_;
    }

    bool IsEmpty() const noexcept {
        return size_ == 0;
    }

    void Clear() noexcept {
        size_ = 0;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) return;
        ArrayPtr<Type> tmp(new_capacity);
        std::move(begin(), end(), tmp.Get());
        capacity_ = new_capacity;
        items_.swap(tmp);
    }

    void Resize(size_t new_size) {
        if (size_ == new_size) return;

        if (size_ < new_size && capacity_ < new_size) {
            auto new_capacity = std::max(new_size, capacity_ * 2);
            ArrayPtr<Type> tmp(new_capacity);
            std::move(begin(), end(), tmp.Get());
            for (auto it = &tmp[size_]; it != &tmp[new_size]; ++it) {
                *(it) = std::move(Type{});
            }
            size_ = new_size;
            capacity_ = new_capacity;
            items_.swap(tmp);
        } else if (size_ < new_size && capacity_ > new_size) {
            for (auto it = &items_[size_]; it != &items_[new_size]; ++it) {
                *(it) = std::move(Type{});
            }
            size_ = new_size;
        } else {
            size_ = new_size;
        }
    }

    void PushBack(const Type& item) {
        if (size_ < capacity_) {
            items_[size_] = item;
        } else {
            auto new_capacity = std::max(size_t(1), capacity_ * 2);
            ArrayPtr<Type> tmp(new_capacity);
            std::copy(begin(), end(), tmp.Get());
            tmp[size_] = item;
            capacity_ = new_capacity;
            items_.swap(tmp);
        }
        ++size_;
    }

    void PushBack(Type&& item) {
        if (size_ < capacity_) {
            auto it_end = begin() + size_;
            *it_end = std::move(item);
        } else {
            auto new_capacity = std::max(size_t(1), capacity_ * 2);
            ArrayPtr<Type> tmp(new_capacity);
            std::move(begin(), end(), tmp.Get());
            auto it_end = tmp.Get() + size_;
            *it_end = std::move(item);
            capacity_ = new_capacity;
            items_.swap(tmp);
        }
        ++size_;
    }

    Iterator Insert(ConstIterator pos, const Type& value) {
        assert(pos >= begin() && pos <= end());
        auto pos_value = std::distance(begin(), Iterator(pos));
        if (size_ < capacity_) {
            std::copy_backward(Iterator(pos), end(), end() + 1);
            items_[pos_value] = value;
        } else {
            auto new_capacity = std::max(size_t(1), capacity_ * 2);
            ArrayPtr<Type> tmp(new_capacity);
            auto it_pos = begin() + pos_value;
            std::copy(begin(), it_pos, tmp.Get());
            std::copy_backward(it_pos, end(), tmp.Get() + (size_ + 1));
            tmp[pos_value] = value;
            capacity_ = new_capacity;
            items_.swap(tmp);
        }
        ++size_;
        return Iterator{&items_[pos_value]};
    }

    Iterator Insert(ConstIterator pos, Type&& value) {
        assert(pos >= begin() && pos <= end());
        auto pos_value = std::distance(begin(), Iterator(pos));
        if (size_ < capacity_) {
            std::move_backward(Iterator(pos), end(), end() + 1);
            auto it_pos = begin() + pos_value;
            *it_pos = std::move(value);
        } else {
            auto new_capacity = std::max(size_t(1), capacity_ * 2);
            ArrayPtr<Type> tmp(new_capacity);
            std::move(begin(), begin() + pos_value, tmp.Get());
            std::move_backward(begin() + pos_value, end(), tmp.Get() + (size_ + 1));
            auto it_pos = tmp.Get() + pos_value;
            *it_pos = std::move(value);
            capacity_ = new_capacity;
            items_.swap(tmp);
        }
        ++size_;
        return Iterator{&items_[pos_value]};
    }

    void PopBack() noexcept {
        assert(size_ != 0);
        --size_;
    }

    Iterator Erase(ConstIterator pos) {
        assert(pos >= begin() && pos < end());
        std::move(Iterator(pos) + 1, end(), Iterator(pos));
        --size_;
        return Iterator(pos);
    }

    void swap(SimpleVector& other) noexcept {
        items_.swap(other.items_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    Iterator begin() noexcept {
        return items_.Get();
    }
    Iterator end() noexcept {
        return items_.Get() + size_;
    }

    ConstIterator begin() const noexcept {
        return cbegin();
    }
    ConstIterator end() const noexcept {
        return cend();
    }

    ConstIterator cbegin() const noexcept {
        return items_.Get();
    }

    ConstIterator cend() const noexcept {
        return items_.Get() + size_;
    }

    SimpleVector(ReserveProxyObj capacity_to_reserve) {
        Reserve(capacity_to_reserve.ReserveCapasity());
    }
private:
    ArrayPtr<Type> items_;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

template <typename Type>
inline bool operator==(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return (lhs.GetSize() == rhs.GetSize()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
inline bool operator<(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return (lhs == rhs) || (lhs < rhs);
}

template <typename Type>
inline bool operator>(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return rhs < lhs;
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return (lhs == rhs) || (rhs < lhs);
}