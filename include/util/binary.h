#ifndef BINARY_H_
#define BINARY_H_

#include <fstream>
#include <memory>

typedef unsigned char Byte;

/* Read Binary */

typedef struct {
    size_t offset;
    std::ios_base::seekdir withRespectTo;
} StreamPos;

inline const StreamPos STREAM_POS_BEG_OF_FILE {0, std::ios::beg};
inline const StreamPos STREAM_POS_CURR_LOC {0, std::ios::cur};

Byte readByte(std::ifstream &inBinStream, const StreamPos& pos = STREAM_POS_CURR_LOC);

Byte readByte(std::ifstream &inBinStream, size_t offset, std::ios_base::seekdir withRespectTo = std::ios::cur);


std::unique_ptr<Byte[]> readByteArray(std::ifstream &inBinStream,
                                      size_t bytes,
                                      const StreamPos& pos = STREAM_POS_CURR_LOC);

std::unique_ptr<Byte[]> readByteArray(std::ifstream &inBinStream,
                                      size_t bytes,
                                      size_t offset,
                                      std::ios_base::seekdir withRespectTo = std::ios::cur);

/* Aggregate Bytes */

#define BITS_PER_BYTE 8

template<typename T>
T reinterpretBytes(Byte* byteArray, size_t size, bool lsb) { 
    if(sizeof(T) < size)
        throw std::runtime_error("Incompatible reinterpretation of byte array.\n");
    else if(size == 0)
        throw std::runtime_error("Size must be greater than 0.\n");
    else if(size > 8)
        throw std::runtime_error("Can't reinterpret representations larger than 8 bytes.\n");
    
    uint64_t reinterpreted = 0;
    size_t shift;
    for(size_t idx = 0; idx < size; ++idx) {
        shift = (lsb ? idx : (size-1-idx)) * BITS_PER_BYTE;
        reinterpreted += byteArray[idx] << shift;
    }
    return static_cast<T>(reinterpreted);
}

#endif