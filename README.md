# SysInfoScanner

## Overview

**SysInfoScanner** is a lightweight command-line tool written in C++ that collects essential system information from a Windows machine. It provides hardware and OS-level details including:

* Machine GUID (HWID)
* CPU brand
* RAM statistics
* Drive information (filesystem, total and free space)
* Username and computer name

This tool is useful for diagnostics, logging, or gathering system identifiers.

### Developed by

* **real7lab**
* [Discord Server](https://discord.gg/visionn)

## Features

* Retrieves HWID from Windows Registry.
* Displays the CPU name using CPUID instructions.
* Shows total and available physical memory.
* Lists all fixed and removable drives with detailed stats.
* Prints the current user's name and computer name.

## Installation

### Prerequisites

* Windows OS
* C++ compiler (e.g., MSVC or MinGW)

### Steps

1. Compile the project using a terminal or Visual Studio:

```bash
g++ SysInfoScanner.cpp -o SysInfoScanner -lshlwapi
````

2. Run the program:

```bash
./SysInfoScanner
```

## Output Example

```
=== SYSTEM INFO ===

[~] HWID: 123e4567-e89b-12d3-a456-426614174000

Username: Lab
Computer Name: DESKTOP-123ABC

[~] CPU: Intel(R) Core(TM) i7-8700 CPU @ 3.20GHz

Total RAM: 16384 MB
Available RAM: 10240 MB

[~] Drive Info:
Drive C:\
  Filesystem: NTFS
  Total Space: 476 GB
  Free Space: 120 GB
```

## Troubleshooting

* **"Unknown" HWID:**
  Make sure the program has administrative permissions or registry access is not blocked.

* **Drive info not shown:**
  Ensure the drives are mounted and accessible at runtime.

## License

This project is developed by [real7lab](https://discord.gg/visionn).
