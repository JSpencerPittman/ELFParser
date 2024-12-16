#ifndef ITERATOR_H_
#define ITERATOR_H_

template <typename ValueType>
class Iterator
{
public:
    // iterator traits
    using value_type = ValueType;
    using pointer = ValueType *;
    using reference = ValueType &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    Iterator(ValueType *ptr) : m_ptr(ptr) {}

    Iterator &operator++()
    {
        m_ptr++;
        return *this;
    }
    Iterator &operator--()
    {
        m_ptr--;
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator retval = *this;
        ++(*this);
        return retval;
    }

    Iterator operator--(int)
    {
        Iterator retval = *this;
        --(*this);
        return retval;
    }

    Iterator &operator+=(difference_type n)
    {
        m_ptr += n;
        return *this;
    }
    Iterator &operator-=(difference_type n)
    {
        m_ptr -= n;
        return *this;
    }

    Iterator operator+(difference_type n) const { return {m_ptr + n}; }
    Iterator operator-(difference_type n) const { return {m_ptr - n}; }

    difference_type operator-(const Iterator &other) const { return m_ptr - other.m_ptr; }
    reference operator[](difference_type n) const { return *(m_ptr + n); }

    bool operator==(Iterator other) const { return m_ptr == other.m_ptr; }
    bool operator!=(Iterator other) const { return m_ptr != other.m_ptr; }

    reference operator*() const { return *m_ptr; }

private:
    const ValueType *m_ptr;
};

#endif
