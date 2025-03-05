#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <zlib.h>

const int CHUNK_SIZE = 16384;
const int NUM_THREADS = 4;

void compressChunk(const std::vector<char>& input, std::vector<char>& output) {
    z_stream strm = {};
    deflateInit(&strm, Z_BEST_COMPRESSION);
    strm.avail_in = input.size();
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(input.data()));
    output.resize(compressBound(input.size()));
    strm.avail_out = output.size();
    strm.next_out = reinterpret_cast<Bytef*>(output.data());
    deflate(&strm, Z_FINISH);
    output.resize(output.size() - strm.avail_out);
    deflateEnd(&strm);
}

void decompressChunk(const std::vector<char>& input, std::vector<char>& output, size_t original_size) {
    z_stream strm = {};
    inflateInit(&strm);
    strm.avail_in = input.size();
    strm.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(input.data()));
    output.resize(original_size);
    strm.avail_out = output.size();
    strm.next_out = reinterpret_cast<Bytef*>(output.data());
    inflate(&strm, Z_FINISH);
    inflateEnd(&strm);
}

void processFile(const std::string& inputFile, const std::string& outputFile, bool compress) {
    std::ifstream in(inputFile, std::ios::binary | std::ios::ate);
    if (!in) {
        std::cerr << "Error opening input file!" << std::endl;
        return;
    }
    size_t fileSize = in.tellg();
    in.seekg(0, std::ios::beg);
    std::vector<char> data(fileSize);
    in.read(data.data(), fileSize);
    in.close();

    size_t chunkSize = fileSize / NUM_THREADS;
    std::vector<std::thread> threads;
    std::vector<std::vector<char>> results(NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == NUM_THREADS - 1) ? fileSize : (i + 1) * chunkSize;
        std::vector<char> chunk(data.begin() + start, data.begin() + end);
        threads.emplace_back([&, i, chunk]() {
            if (compress) {
                compressChunk(chunk, results[i]);
            } else {
                decompressChunk(chunk, results[i], chunk.size());
            }
        });
    }

    for (auto& t : threads) t.join();
    
    std::ofstream out(outputFile, std::ios::binary);
    for (const auto& result : results) {
        out.write(result.data(), result.size());
    }
    out.close();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <compress|decompress> <input_file> <output_file>" << std::endl;
        return 1;
    }
    bool compress = std::string(argv[1]) == "compress";
    processFile(argv[2], argv[3], compress);
    return 0;
}
