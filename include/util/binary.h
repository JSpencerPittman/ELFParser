#ifndef BINARY_H_
#define BINARY_H_

#include <fstream>
#include <memory>

typedef unsigned char Byte;

/* Read Binary */

// Position within stream
typedef struct
{
    size_t offset;
    std::ios_base::seekdir withRespectTo;
} StreamPos;

inline const StreamPos STREAM_POS_BEG_OF_FILE{0, std::ios::beg};
inline const StreamPos STREAM_POS_CURR_LOC{0, std::ios::cur};

// Read a single byte
Byte readByte(std::ifstream &inBinStream, const StreamPos &pos = STREAM_POS_CURR_LOC);

Byte readByte(std::ifstream &inBinStream, size_t offset, std::ios_base::seekdir withRespectTo = std::ios::cur);

// Read multiple bytes
std::unique_ptr<Byte[]> readByteArray(std::ifstream &inBinStream,
                                      size_t size,
                                      const StreamPos &pos = STREAM_POS_CURR_LOC);

std::unique_ptr<Byte[]> readByteArray(std::ifstream &inBinStream,
                                      size_t size,
                                      size_t offset,
                                      std::ios_base::seekdir withRespectTo = std::ios::cur);

/* Reinterpret Bytes */

#define BITS_PER_BYTE 8

template <typename T>
T reinterpretByteArray(Byte *byteArray, bool lsb)
{
    size_t size = sizeof(T);
    if (sizeof(T) > 8)
        throw std::runtime_error("Can't reinterpret representations larger than 8 bytes.\n");

    uint64_t reinterpreted = 0;
    size_t shift;
    for (size_t idx = 0; idx < size; ++idx)
    {
        shift = (lsb ? idx : (size - 1 - idx)) * BITS_PER_BYTE;
        reinterpreted += byteArray[idx] << shift;
    }
    return std::move(static_cast<T>(reinterpreted));
}

/* Read and reinterpret */
template <typename T>
T readAndReinterpretByteArray(std::ifstream &inBinStream, bool lsb, size_t offset,
                              std::ios_base::seekdir withRespectTo = std::ios::cur)
{
    auto byteArray = readByteArray(inBinStream, sizeof(T), offset, withRespectTo);
    return std::move(reinterpretByteArray<T>(byteArray.get(), lsb));
}

template <typename T>
T readAndReinterpretByteArray(std::ifstream &inBinStream, bool lsb, const StreamPos &pos = STREAM_POS_CURR_LOC)
{
    return std::move(readAndReinterpretByteArray<T>(inBinStream, lsb, pos.offset, pos.withRespectTo));
}


#endif