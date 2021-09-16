/**
 * View: a non-owning container of contigious memory
 */

#pragma once

#include <cstddef>
#include <iterator>

#include "platform/assert.h"

namespace emb {

template<typename T>
class view
{
public:
    /**
     * Types
     */

    using value_type = T;
    using pointer = value_type*;
    using const_pointer = const pointer;
    using reference = value_type&;
    using const_reference = const reference;
    using size_type = size_t;
    using iterator = pointer;
    using const_iterator = const iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = const reverse_iterator;

    /**
     * Constructors
     */

    view() : _data{nullptr}, _size{0}
    {
    }

    view(view const& other) = default;

    view& operator=(view const& other) = default;

    view(pointer data, size_type size) : _data{data}, _size{size}
    {
        // todo: assertions
    }

    view(pointer first, pointer last) : _data{first}, _size{last - first}
    {
        // todo: assertions
    }

    template<size_t N>
    view(value_type (&array)[N]) : _data{array}, _size{N}
    {
    }

    /**
     * Accessors
     */

    size_type size() const
    {
        return _size;
    }

    pointer data()
    {
        return _data;
    }

    const_pointer cdata() const
    {
        return _data;
    }

    value_type operator[](size_type index)
    {
        assert(index < _size);
        return _data + index;
    }

    /**
     * Iterators
     */

    iterator begin()
    {
        return data();
    }

    const_iterator cbegin() const
    {
        return data();
    }

    iterator end()
    {
        return data() + size();
    }

    const_iterator cend() const
    {
        return data() + size();
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(data() + size() - 1);
    }

    const_reverse_iterator crbegin()
    {
        return reverse_iterator(data() + size() - 1);
    }

    reverse_iterator rend()
    {
        return data() - 1;
    }

    const_reverse_iterator crend()
    {
        return data() - 1;
    }

private:
    pointer _data;
    size_type _size;
};

}  // namespace emb
