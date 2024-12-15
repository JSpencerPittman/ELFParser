#include "partition/partition.h"

#include <cstdio>

using namespace Partition;

PartitionAbstract::PartitionAbstract()
    : m_locOffset(0), m_locSize(0) {}

PartitionAbstract::PartitionAbstract(size_t offset, size_t size)
    : m_locOffset(offset), m_locSize(size) {}

void PartitionAbstract::printLocation() const
{
    printf("Location[Offset]: %lu\n", m_locOffset);
    printf("Location[Size]: %lu\n", m_locSize);
}
