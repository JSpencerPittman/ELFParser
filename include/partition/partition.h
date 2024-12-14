#ifndef PARTITION_H_
#define PARTITION_H_

namespace Partition
{
    class Partition
    {
    public:
        Partition() {}

        virtual size_t bytes() const = 0;
        virtual size_t begin() const = 0;
        virtual size_t end() const = 0;

        virtual void print() const = 0;
    };
};

#endif