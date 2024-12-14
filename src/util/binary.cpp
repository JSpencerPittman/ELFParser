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
                                      size_t bytes,
                                      const StreamPos &pos)
{
    return readByteArray(inBinStream, bytes, pos.offset, pos.withRespectTo);
}

std::unique_ptr<Byte[]> readByteArray(std::ifstream &inBinStream, size_t bytes,
                                      size_t offset, std::ios_base::seekdir withRespectTo)
{
    if (!inBinStream.is_open())
        throw std::runtime_error("Can't read from unopened stream.");

    inBinStream.seekg(offset, withRespectTo);

    auto values = std::make_unique<Byte[]>(bytes);
    inBinStream.read(reinterpret_cast<char *>(values.get()), bytes);

    if (!inBinStream.good())
        throw std::runtime_error("Stream failed while reading a byte.");

    return values;
}