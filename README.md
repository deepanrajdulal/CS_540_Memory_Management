# Memory Management and Address Translation

## Description

This C++ program demonstrates memory management and address translation using a page/frame table. It consists of two main classes: `PageTable` and `MemoryManager`.

### PageTable Class

- Description: Represents a page/frame table used for mapping logical page numbers to physical frame numbers.
- Functions:
  - **Constructor:** Initializes the page/frame table with mappings based on the provided page size and physical memory size.
  - **getPhysicalFrame():** Retrieves the physical frame number for a given logical page number.

### MemoryManager Class

- **Description:** Manages memory and performs address translation using the page/frame table.
- **Functions:**
  - **Constructor:** Initializes the MemoryManager with a PageTable instance.
  - **translateAddress():** Translates logical addresses to physical addresses and handles page faults by loading pages from secondary memory if necessary.

## Usage

### Compilation
Compile the program using a C++ compiler.

### Execution
Run the compiled program.

### Interaction
Re-run the program to observe different logical addresses being translated to physical addresses.

## Error Handling

The program includes error handling for cases such as page faults. If a page fault occurs, the program displays a message indicating that the page is being loaded from secondary memory.
