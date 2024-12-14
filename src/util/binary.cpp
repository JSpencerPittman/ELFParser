#include "util/binary.h"

typedef unsigned char Byte;

Byte readByte(std::ifstream &inBinStream, const StreamPos &pos)
{
    return std::move(readByte(inBinStream, pos.offset, pos.withRespectTo));
}

Byte readByte(std::ifstream &inBinStream, size_t offset, std::ios_base::seekdir withRespectTo)
{
    if (!inBinStream.is_open())
        throw std::runtime_error("Can't read from unopened stream.");

    inBinStream.seekg(offset, withRespectTo);

    Byte value = inBinStream.get();
    if (!inBinStream.good())
        throw std::runtime_error("Stream failed while reading bytes.");

    return std::move(value);
}

std::unique_ptr<Byte[]> readByteArray(std::ifstream &inBinStream,
                                      size_t size,
                                      const StreamPos &pos)
{
    return readByteArray(inBinStream, size, pos.offset, pos.withRespectTo);
}

std::unique_ptr<Byte[]> readByteArray(std::ifstream &inBinStream, size_t size,
                                      size_t offset, std::ios_base::seekdir withRespectTo)
{
    if (!inBinStream.is_open())
        throw std::runtime_error("Can't read from unopened stream.");

    inBinStream.seekg(offset, withRespectTo);

    auto values = std::make_unique<Byte[]>(size);
    inBinStream.read(reinterpret_cast<char *>(values.get()), size);

    if (!inBinStream.good())
        throw std::runtime_error("Stream failed while reading a byte.");

    return values;
}