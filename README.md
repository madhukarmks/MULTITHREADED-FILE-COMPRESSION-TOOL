# MULTITHREADED-FILE-COMPRESSION-TOOL

COMPANY: CODETECH IT SOLUTIONS

NAME: MADHUKAR KUMAR

INTERN ID: CT6WOZM

DOMAIN: C++ PROGRAMMING

DURATION: 6 WEEEKS

MENTOR: NEELA SANTOSH KUMAR

**Introduction**

This C++ program is designed to efficiently compress and decompress files using the zlib library. It employs multi-threading to divide large files into chunks and process them concurrently, significantly improving performance. By leveraging the zlib compression algorithm, the application reduces file sizes while maintaining the integrity of the original data.
The program accepts command-line arguments to determine whether to compress or decompress a file. It reads the file, splits it into multiple parts, processes each part in parallel using multiple threads, and then writes the processed data back to a new file.

**Key Features of the Program**

File Compression and Decompression: Uses zlib to perform data compression and decompression.
Multi-Threading for Efficiency: Splits large files into multiple chunks and processes them simultaneously using multiple threads.
Command-Line Interface: Users can specify whether to compress or decompress a file via command-line arguments.
Binary File Handling: Ensures that any type of file (text, images, videos, etc.) can be processed without data corruption.

**Understanding the Code**

1. Header Files and Constants
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <zlib.h>

3. Compression Function   
Initializes a z_stream object for compression.
Uses deflateInit() with Z_BEST_COMPRESSION to set the highest compression level.
Reads input data, processes it using deflate(), and stores the compressed data in output.
Resizes the output buffer to match the actual compressed size.
Cleans up by calling deflateEnd().

6. Decompression Function
Initializes a z_stream object for decompression.
Uses inflateInit() to prepare for decompression.
Reads compressed data, processes it using inflate(), and stores the decompressed data in output.
Resizes the output buffer based on the original file size.
Cleans up by calling inflateEnd().

8. File Processing Function
    size_t fileSize = in.tellg();
    in.seekg(0, std::ios::beg);
    std::vector<char> data(fileSize);
    in.read(data.data(), fileSize);
    in.close();
Opens the input file in binary mode and determines its size using tellg().
Reads the entire file into a vector called data.
Closes the file after reading.

10. Multi-Threaded Processing
Divides the file into NUM_THREADS equal chunks.
Spawns multiple threads to process each chunk independently.
Waits for all threads to complete their execution.

12. Writing Processed Data to Output File
Opens the output file in binary mode.
Writes the compressed or decompressed chunks sequentially.
Closes the file after writing.

14. Main Function (Program Entry Point)
Parses command-line arguments:
"compress" or "decompress"
Input file name
Output file name
Calls processFile() to execute the appropriate operation.

**Advantages of This Program**

Parallel Processing: Speeds up file processing using multiple threads.
Efficient Compression: Uses zlib to optimize file size.
Command-Line Usability: Allows flexible input and output handling.
Binary File Support: Works with all file types without corruption.

**Conclusion**

This C++ program efficiently compresses and decompresses files using multi-threading and zlib. By dividing files into chunks and processing them in parallel, it significantly improves performance. It is a useful tool for managing large files while maintaining data integrity.

**IMAGE**








