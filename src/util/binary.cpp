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

    inBinStream.clear();
    inBinStream.seekg(offset, withRespectTo);

    Byte value = inBinStream.get();
    if (!inBinStream.good()) {
        throw std::runtime_error("Stream failed while reading bytes.");
    }

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

    inBinStream.clear();
    inBinStream.seekg(offset, withRespectTo);

    auto values = std::make_unique<Byte[]>(size);
    inBinStream.read(reinterpret_cast<char *>(values.get()), size);

    if (!inBinStream.good())
        throw std::runtime_error("Stream failed while reading a byte.");

    return values;
}

std::string readString(std::ifstream &inBinStream, const StreamPos &pos)
{
    return readString(inBinStream, pos.offset, pos.withRespectTo);
}

std::string readString(std::ifstream &inBinStream, size_t offset,
                       std::ios_base::seekdir withRespectTo)
{
    if (!inBinStream.is_open())
        throw std::runtime_error("Can't read from unopened stream.");

    // Determine length of string
    inBinStream.clear();
    inBinStream.seekg(offset, withRespectTo);

    size_t sizeOfString = 0;
    while (readByte(inBinStream) != 0)
        ++sizeOfString;
    if (!inBinStream.good())
        throw std::runtime_error("Stream failed while reading a byte.");


    // Load string
    auto stringRaw = readByteArray(inBinStream, sizeOfString, offset,
                                                      withRespectTo);
    return { reinterpret_cast<char*>(stringRaw.get()) };
}