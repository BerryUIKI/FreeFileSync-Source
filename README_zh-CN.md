# FreeFileSync

[English](README.md) | [Deutsch](README_DE.md) | [简体中文](README_zh-CN.md) | [日本語](README_JP.md)

[![Version](https://img.shields.io/badge/version-14.12-blue.svg)](https://freefilesync.org)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)](https://freefilesync.org/download.php)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B23)

## 简介

**FreeFileSync** 是一款免费且开源的文件夹比较与同步软件，旨在为重要文件创建和管理备份副本。FreeFileSync 并不在每次同步时复制所有文件，而是智能检测源文件夹与目标文件夹之间的差异，仅传输所需的最少数据量。

FreeFileSync 具备跨平台支持，可在 **Windows**、**macOS** 与 **Linux** 上运行。此外还包含 **RealTimeSync** 组件，用于实时监控目录并在检测到文件变更时自动触发同步作业。

- **官方网站**: [https://freefilesync.org](https://freefilesync.org)
- **官方下载**: [https://freefilesync.org/download.php](https://freefilesync.org/download.php)
- **源码仓库**: [https://github.com/BerryUIKI/FreeFileSync-Source](https://github.com/BerryUIKI/FreeFileSync-Source)

---

## 主要特性

- **跨平台兼容性**：在 Windows、macOS 和 Linux 上原生运行。
- **灵活的同步模式**：支持双向同步（Two-way）、镜像同步（Mirror）、更新同步（Update）以及完全自定义同步规则。
- **多协议支持**：无缝支持本地磁盘、网络共享（SMB）、SFTP（SSH 文件传输协议）、FTP/FTPS 以及 Google Drive。
- **高性能扫描**：多线程目录遍历与优化的二进制数据库跟踪，实现快速增量同步。
- **冲突与错误处理**：完备的冲突检测与解决机制、自动重试与安全的文件拷贝策略。
- **自动化与监控**：支持命令行批处理作业，并通过 RealTimeSync 实现实时监控与自动化。
- **高级过滤选项**：支持通配符、文件时间、大小及正则表达式的包含/排除过滤规则。
- **数据保护**：支持版本控制功能（将旧版本文件保存至指定文件夹或系统回收站）。

---

## 从源码构建

### 环境先决条件

FreeFileSync 需要支持 C++23 标准的现代编译器与相关开发依赖库：

- **编译器**：支持 C++23 (`-std=c++23`) 的 GCC 13+ 或 Clang 17+
- **wxWidgets**：3.2 或更高版本（`wx-config`，包含 `std`, `aui`, `richtext` 组件）
- **GTK+**：GTK 3.0 开发头文件（`gtk+-3.0`）
- **网络与加密库**：
  - OpenSSL (`openssl`)
  - libcurl (`libcurl`)
  - libssh2 (`libssh2`)
  - libidn2 (`libidn2`)
- **压缩库**：zlib
- **SELinux** *(可选)*：`libselinux`

#### 在 Linux (Debian / Ubuntu) 上安装依赖

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

*(Fedora / RHEL):*
```bash
sudo dnf install gcc-c++ wxGTK3-devel gtk3-devel libcurl-devel libssh2-devel openssl-devel libidn2-devel zlib-devel
```

### 构建步骤

1. **克隆代码仓库**:
   ```bash
   git clone https://github.com/BerryUIKI/FreeFileSync-Source.git
   cd FreeFileSync-Source
   ```

2. **编译 FreeFileSync**:
   ```bash
   cd FreeFileSync/Source
   make -j$(nproc)
   ```

3. **编译 RealTimeSync** *(可选)*:
   ```bash
   cd RealTimeSync
   make -j$(nproc)
   ```

编译完成后，生成的可执行文件将位于相应的构建目录中。

---

## 使用指南

### 图形界面操作
1. 启动 `FreeFileSync`。
2. 将源文件夹与目标文件夹选择或拖放到左侧与右侧的文件夹路径框中。
3. 配置比较方式（文件时间与大小、文件内容或文件大小）与同步方式（双向、镜像、更新、自定义）。
4. 点击 **比较** 按钮查看文件变动，确认无误后点击 **同步** 按钮开始执行。

### RealTimeSync 实时监控
1. 启动 `RealTimeSync`。
2. 配置要监听的目录路径以及空闲延迟时间。
3. 设置检测到变动时执行的命令（通常调用已保存的 FreeFileSync 批处理配置 `.ffs_batch`）。
4. 点击 **开始** 即可在系统托盘常驻并自动监控。

---

## 参与贡献

欢迎社区贡献者参与改进 FreeFileSync-Source：

1. Fork 本仓库：[https://github.com/BerryUIKI/FreeFileSync-Source](https://github.com/BerryUIKI/FreeFileSync-Source)。
2. 创建专属功能分支（`git checkout -b feature/my-feature`）。
3. 提交修改并书写清晰的 Commit 提交信息。
4. 将分支推送到你的 Fork 仓库（`git push origin feature/my-feature`）。
5. 向主仓库提交 Pull Request 说明修改内容与背景。

---

## 软件许可证

FreeFileSync 在个人非商业用途下基于 **GNU 通用公共许可证第 3 版 (GPLv3)** 授权分发；商业、政府及其他非个人使用需遵循 FreeFileSync 商业版（Business Edition）许可条款。

完整许可证条款请参阅 [LICENSE](LICENSE) 与 [License.txt](License.txt)，第三方开源库许可包括：
- **wxWidgets**: wxWindows Library Licence 3.1
- **OpenSSL**: OpenSSL License / SSLeay License
- **libcurl**: curl License (MIT 风格)
- **libssh2**: libssh2 License (BSD 3-Clause)
- **PuTTY**: PuTTY Licence (MIT 风格)

---

## 支持与社区

- **官方讨论社区**: [https://freefilesync.org/forum/](https://freefilesync.org/forum/)
- **常见问题解答 (FAQ)**: [https://freefilesync.org/faq.php](https://freefilesync.org/faq.php)
- **使用手册与教程**: [https://freefilesync.org/manual.php](https://freefilesync.org/manual.php)
- **仓库 Issue 反馈**: [https://github.com/BerryUIKI/FreeFileSync-Source/issues](https://github.com/BerryUIKI/FreeFileSync-Source/issues)

---

## 致谢

感谢 Zenju 与 FreeFileSync 社区创造并维护这一优秀的同步工具，并感谢所有翻译者、贡献者与广大用户的支持。
