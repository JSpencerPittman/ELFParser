#ifndef PARTITION_H_
#define PARTITION_H_

#include <cstdint>

namespace Partition
{
    class PartitionAbstract
    {
    public:
        PartitionAbstract()
            : m_locOffset(0), m_locSize(0) {}
        PartitionAbstract(size_t offset, size_t size)
            : m_locOffset(offset), m_locSize(size) {}

        virtual size_t bytes() const { return m_locSize; }
        virtual size_t begin() const { return m_locOffset; }
        virtual size_t end() const { return bytes() + begin(); };

        virtual void print() const = 0;

        // protected:
        // void printNameAndLocation() const;

    protected:
        // Location
        size_t m_locOffset;
        size_t m_locSize;

        static const char m_name[];
    };
};

#endif