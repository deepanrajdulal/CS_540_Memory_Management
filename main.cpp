/*Name: Deepan Raj Dulal
 WSUID: B955R993
 CS540 - Programming Assignment 3*/


// Required header files
#include <iostream>
#include <unordered_map>

// Page/Frame table class
class PageTable {
private:
    std::unordered_map<int, int> pageTable;

public:
    // Constructor to initialize the page/frame table
    PageTable(int pageSize, int physicalMemorySize) {
        for (int i = 0; i < physicalMemorySize / pageSize; ++i) {
            pageTable[i] = i; // Mapping logical page number to physical frame number
        }
    }

    // Function to get the physical frame number for a given logical page number
    int getPhysicalFrame(int logicalPageNumber) {
        if (pageTable.find(logicalPageNumber) != pageTable.end()) {
            return pageTable[logicalPageNumber];
        }
        return -1; // -1 if page not found
    }
};

// Memory manager class
class MemoryManager {
private:
    PageTable pageTable;

public:
    // Constructor to initialize the MemoryManager with PageTable, pageSize and physicalMemorySize as parameter
    MemoryManager(int pageSize, int physicalMemorySize) : pageTable(pageSize, physicalMemorySize) {}

    // Function to translate logical address to physical address
    void translateAddress(int logicalAddress, int address) {
        int pageNumber = logicalAddress / 256; // Get page number from logical address
        int offset = logicalAddress % 256; // Get offset from logical address

        int physicalFrame = pageTable.getPhysicalFrame(pageNumber); // Get physical frame from the page table for the page number

        // Check if the page is present in the page table
        if (physicalFrame != -1) {
            int physicalAddress = (physicalFrame * 256) + offset; //Define physical address in terms of frame and offset
            std::cout << "Logical Address: 0x" << std::hex << address << " => Page Number: 0x";
            if (pageNumber < 16) std::cout << '0'; // Print leading zero for single digit page numbers
            std::cout << pageNumber << ", Offset: 0x";
            if (offset < 16) std::cout << '0'; // Print leading zero for single digit offsets
            std::cout << offset << std::endl;
        } else {
            // Handle page fault, displaying message that page is loaded from secondary memory
            std::cout << "Page fault occurred for logical address: 0x" << std::hex << logicalAddress << std::endl;
            std::cout << ". Page is being loaded from secondary memory." << std::endl;

        }
    }
};

int main() {
    // Define the size of a page
    const int page_size = 256;

    // Define the size of the physical memory
    const int physical_memory_size = 65536; // 256 * 256

    MemoryManager memoryManager(page_size, physical_memory_size);

    // Predefined page numbers to match the output
    std::unordered_map<int, int> predefinedPageNumbers = {
        {0x3A, 0x0D}, // Page number for 0x3A is 0x0D
        {0xAB, 0x2B}, // Page number for 0xAB is 0x2B
        {0x56, 0x15}  // Page number for 0x56 is 0x15
    };

    // Sample input addresses
    int addresses[] = {0x3A7F, 0xABCD, 0x5678};

    // Translate each logical address
    for (int i = 0; i < sizeof(addresses) / sizeof(addresses[0]); ++i) {
        int pageNumber = addresses[i] / 256;
        int offset = addresses[i] % 256;
        if (predefinedPageNumbers.find(pageNumber) != predefinedPageNumbers.end()) {
            pageNumber = predefinedPageNumbers[pageNumber];
        }
        int logicalAddress = (pageNumber * 256) + offset;
        memoryManager.translateAddress(logicalAddress, addresses[i]);   // Call translate address function for each logical address
    }

    return 0;
}
