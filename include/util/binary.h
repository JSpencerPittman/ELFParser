#ifndef BINARY_H_
#define BINARY_H_

#include <fstream>
#include <memory>

typedef unsigned char Byte;
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



#endif