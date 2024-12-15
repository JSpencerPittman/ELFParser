#ifndef PARTITION_H_
#define PARTITION_H_

#include <stddef.h>

namespace Partition
{
    class PartitionAbstract
    {
    public:
        PartitionAbstract();
        PartitionAbstract(size_t offset, size_t size);

        virtual size_t bytes() const { return m_locSize; }
        virtual size_t begin() const { return m_locOffset; }
        virtual size_t end() const { return bytes() + begin(); };

        virtual void print() const = 0;

    protected:
        void printLocation() const;

    protected:
        // Location
        size_t m_locOffset;
        size_t m_locSize;
    };
};

#endif