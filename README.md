# FreeFileSync

[English](README.md) | [Deutsch](README_DE.md) | [简体中文](README_zh-CN.md) | [日本語](README_JP.md)

[![CI / CD](https://github.com/BerryUIKI/FreeFileSync-Source/actions/workflows/ci.yml/badge.svg)](https://github.com/BerryUIKI/FreeFileSync-Source/actions/workflows/ci.yml)
[![Version](https://img.shields.io/badge/version-14.12-blue.svg)](https://freefilesync.org)
[![Releases](https://img.shields.io/github/v/release/BerryUIKI/FreeFileSync-Source?color=orange)](https://github.com/BerryUIKI/FreeFileSync-Source/releases)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)](https://freefilesync.org/download.php)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B23)

## Introduction

**FreeFileSync** is a free and open-source folder comparison and synchronization software designed to create and manage backup copies of important files. Rather than copying every file every time, FreeFileSync determines the differences between source and target folders and transfers only the minimum amount of data required.

FreeFileSync is cross-platform and available for **Windows**, **macOS**, and **Linux**. It also includes **RealTimeSync**, a companion tool for monitoring directories and triggering automated synchronization jobs upon change detection.

- **Official Website**: [https://freefilesync.org](https://freefilesync.org)
- **Official Downloads**: [https://freefilesync.org/download.php](https://freefilesync.org/download.php)
- **GitHub Releases (Automated Builds)**: [https://github.com/BerryUIKI/FreeFileSync-Source/releases](https://github.com/BerryUIKI/FreeFileSync-Source/releases)
- **Source Repository**: [https://github.com/BerryUIKI/FreeFileSync-Source](https://github.com/BerryUIKI/FreeFileSync-Source)

---

## Features

- **Cross-Platform Compatibility**: Runs natively on Windows, macOS, and Linux.
- **Flexible Synchronization Modes**: Supports Two-Way, Mirror, Update, and fully Customizable sync variants.
- **Multiple Protocols**: Seamless synchronization with local disks, network shares (SMB), SFTP (SSH File Transfer Protocol), FTP/FTPS, and Google Drive.
- **High-Performance Scanning**: Multi-threaded directory traversers and optimized binary database tracking for incremental synchronization.
- **Conflict & Error Handling**: Comprehensive conflict resolution, automatic retry mechanisms, and fail-safe file copy routines.
- **Automation & Monitoring**: Batch processing via command-line interface and real-time directory monitoring through RealTimeSync.
- **Advanced Filtering**: Inclusion/exclusion rules based on wildcards, file age, file size, and regular expressions.
- **Data Protection**: Support for Versioning (holding previous revisions in custom folders or the Recycle Bin/Trash).

---

## Precompiled Releases & CI/CD

Automated multi-architecture binaries (Linux `x86_64` and `aarch64` / ARM64) and source archives are continuously built and published via GitHub Actions.

Download prebuilt portable packages from [GitHub Releases](https://github.com/BerryUIKI/FreeFileSync-Source/releases). Each release includes standalone binaries, launcher scripts, resources, and SHA-256 checksums.

---

## Building from Source

### Prerequisites

FreeFileSync requires a modern C++23 compiler and standard development libraries:

- **Compiler**: GCC 13+ or Clang 17+ supporting C++23 (`-std=c++23`)
- **wxWidgets**: Version 3.2 or later (`wx-config` with `std`, `aui`, `richtext`)
- **GTK+**: GTK 3.0 development headers (`gtk+-3.0`)
- **Networking & Crypto**:
  - OpenSSL (`openssl`)
  - libcurl (`libcurl`)
  - libssh2 (`libssh2`)
  - libidn2 (`libidn2`)
- **Compression**: zlib
- **SELinux** *(optional)*: `libselinux`

#### Installing Dependencies on Linux (Debian / Ubuntu)

```bash
sudo apt update
sudo apt install build-essential \
    libwxgtk3.2-dev \
    libgtk-3-dev \
    libcurl4-openssl-dev \
    libssh2-1-dev \
    libssl-dev \
    libidn2-dev \
    zlib1g-dev
```

*(On Fedora / RHEL):*
```bash
sudo dnf install gcc-c++ wxGTK3-devel gtk3-devel libcurl-devel libssh2-devel openssl-devel libidn2-devel zlib-devel
```

### Build Instructions

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/BerryUIKI/FreeFileSync-Source.git
   cd FreeFileSync-Source
   ```

2. **Build FreeFileSync**:
   ```bash
   cd FreeFileSync/Source
   make -j$(nproc)
   ```

3. **Build RealTimeSync** *(optional)*:
   ```bash
   cd RealTimeSync
   make -j$(nproc)
   ```

Upon completion, the compiled binaries will be generated in the respective build directories.

---

## Usage

### Interactive GUI
1. Launch `FreeFileSync`.
2. Select or drag-and-drop the source and target folders into the left and right folder slots.
3. Configure comparison settings (File time and size, File content, or File size) and synchronization rules (Two-way, Mirror, Update, Custom).
4. Click **Compare** to inspect differences, then click **Synchronize** to execute.

### RealTimeSync
1. Launch `RealTimeSync`.
2. Specify directory paths to watch and an idle timeout.
3. Configure the command line to execute your saved FreeFileSync batch configuration (`.ffs_batch`).
4. Click **Start** to monitor in the system tray.

---

## Contributing

Contributions from the open-source community are welcome:

1. Fork the repository at [https://github.com/BerryUIKI/FreeFileSync-Source](https://github.com/BerryUIKI/FreeFileSync-Source).
2. Create a dedicated topic branch (`git checkout -b feature/my-improvement`).
3. Commit your changes with concise and descriptive commit messages.
4. Push your branch to your fork (`git push origin feature/my-improvement`).
5. Open a Pull Request detailing your changes and reasoning.

---

## License

FreeFileSync is distributed as open-source software under the **GNU General Public License v3.0 (GPLv3)** for private use, with commercial use governed by the FreeFileSync Business Edition terms.

See the [LICENSE](LICENSE) and [License.txt](License.txt) files for full licensing terms and conditions, including notices for included and linked components:
- **wxWidgets**: wxWindows Library Licence 3.1
- **OpenSSL**: OpenSSL License / SSLeay License
- **libcurl**: curl License (MIT-style)
- **libssh2**: libssh2 License (BSD 3-Clause)
- **PuTTY**: PuTTY Licence (MIT-style)

---

## Support & Resources

- **Official FreeFileSync Forum**: [https://freefilesync.org/forum/](https://freefilesync.org/forum/)
- **Frequently Asked Questions (FAQ)**: [https://freefilesync.org/faq.php](https://freefilesync.org/faq.php)
- **Tutorials & Manuals**: [https://freefilesync.org/manual.php](https://freefilesync.org/manual.php)
- **Repository Issues**: [https://github.com/BerryUIKI/FreeFileSync-Source/issues](https://github.com/BerryUIKI/FreeFileSync-Source/issues)

---

## Acknowledgments

Special thanks to Zenju and the FreeFileSync community for creating and maintaining this synchronization tool, as well as to all translators, contributors, and users worldwide.
