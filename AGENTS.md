# AGENTS.md — Maintenance & Developer Guide for AI Agents

Welcome to the **FreeFileSync-Source** repository. This document provides technical instructions, architectural context, and operating guidelines for AI agents and maintainers managing this repository.

---

## 1. Project Overview

This repository maintains the open-source distribution of **FreeFileSync** and **RealTimeSync**, provides automated multi-architecture CI builds, and continuously publishes releases on GitHub.

- **Upstream Project**: [FreeFileSync.org](https://freefilesync.org)
- **Language & Standard**: C++23 (`-std=c++23`)
- **Primary Dependencies**: wxWidgets (>= 3.2), GTK+ 3.0, OpenSSL, libcurl, libssh2, libidn2, zlib, libselinux.
- **License**: GNU General Public License v3.0 (GPLv3) with upstream commercial terms.

---

## 2. Directory Structure

```
FreeFileSync-Source/
├── .github/
│   └── workflows/
│       └── ci.yml                 # Multi-platform CI/CD and release workflow
├── FreeFileSync/
│   ├── Build/
│   │   └── Resources/             # UI resources (icons, sounds, languages, styles)
│   └── Source/
│       ├── Makefile               # FreeFileSync build Makefile
│       ├── application.cpp        # Application entry and initialization
│       ├── version/version.h      # Version definition (ffsVersion)
│       └── RealTimeSync/
│           ├── Makefile           # RealTimeSync build Makefile
│           └── application.cpp    # RealTimeSync entry
├── wx+/                           # wxWidgets helper abstractions & dark mode
│   ├── darkmode.h                 # ColorTheme / Appearance definitions
│   └── darkmode.cpp               # Theme & color hook implementations
├── zen/                           # Low-level core utility library
├── zenXml/                        # XML serialization library
├── xBRZ/                          # Image scaling algorithm
├── libcurl/                       # curl C++ wrappers
├── libssh2/                       # libssh2 C++ wrappers
├── scripts/
│   └── extract_changelog.py       # Release notes parser from Changelog.txt
├── Changelog.txt                  # Full upstream changelog history
├── Bugs.txt                       # Known issues and bugs log
├── License.txt / LICENSE          # License terms (GPLv3)
├── README.md                      # English documentation
├── README_zh-CN.md                # 简体中文 documentation
├── README_DE.md                   # Deutsch documentation
└── README_JP.md                   # 日本語 documentation
```

---

## 3. Upstream Synchronization Workflow

When a new version of FreeFileSync is released upstream:

### Step 1: Download & Inspect Upstream Source
1. Check the latest version at `https://freefilesync.org/download.php`.
2. Download the official source package:
   ```bash
   curl -L -A "Mozilla/5.0" -o FreeFileSync_<version>_Source.zip "https://freefilesync.org/download/FreeFileSync_<version>_Source.zip"
   ```
3. Extract the archive into a temporary folder.

### Step 2: Sync Source Trees & Documents
1. Overwrite all source directories:
   - `FreeFileSync/`
   - `libcurl/`
   - `libssh2/`
   - `wx+/`
   - `xBRZ/`
   - `zen/`
   - `zenXml/`
2. Update `Changelog.txt`, `Bugs.txt`, and `License.txt`.
3. Update root `LICENSE` with any license modifications.

### Step 3: Apply Linux Distribution Compatibility Patches
Upstream source assumes custom-patched wxWidgets builds. Standard Linux distributions (Ubuntu, Debian, Fedora, Arch) require distribution compatibility adjustments:

1. **Disable `wxUSE_EXCEPTIONS` check in entrypoints**:
   In `FreeFileSync/Source/application.cpp` and `FreeFileSync/Source/RealTimeSync/application.cpp`:
   ```cpp
   int Application::OnRun()
   {
   #if 0 // wxUSE_EXCEPTIONS check disabled for distribution wxWidgets packages
   #error why is wxWidgets uncaught exception handling enabled!?
   #endif
       [[maybe_unused]] const int rc = wxApp::OnRun();
       return static_cast<int>(exitCode_);
   }
   ```

2. **Compatibility fallback for `wxApp::Appearance`**:
   `wxApp::Appearance` and `wxApp::SetAppearance` were introduced in wxWidgets 3.3+.
   - In `wx+/darkmode.h`: Wrap `using ColorTheme = wxApp::Appearance;` with `#if wxCHECK_VERSION(3, 3, 0) ... #else enum class ColorTheme { System, Light, Dark }; #endif`.
   - In `wx+/darkmode.cpp`: Guard `darkModeAvailable()` and `changeColorTheme()` with `#if wxCHECK_VERSION(3, 3, 0)`.

3. **Compatibility guard for `DisableAutomaticBoundingBoxUpdates`**:
   In `wx+/dc.h`: Wrap `static_cast<wxDC&>(*this).DisableAutomaticBoundingBoxUpdates();` with `#if wxCHECK_VERSION(3, 3, 0) ... #endif` (method only exists in wxWidgets 3.3+).

4. **Compatibility fallback for `wxReadOnlyDC` and `wxInfoDC`**:
   `wxReadOnlyDC` and `wxInfoDC` were introduced in wxWidgets 3.3+.
   - In `wx+/grid.h` and `wx+/dc.h`: Add `#if !wxCHECK_VERSION(3, 3, 0) using wxReadOnlyDC = wxDC; using wxInfoDC = wxClientDC; #endif`.

5. **Disambiguate `conversionType(wxCStrData)` in `zen/string_traits.h`**:
   In standard Linux wxWidgets packages (`wxUSE_UNICODE_UTF8`), `wxString::c_str()` returns `wxCStrData` which provides implicit conversion operators to both `const char*` and `const wchar_t*`. In `zen/string_traits.h`, calling `conversionType(std::declval<S>().c_str())` is therefore ambiguous.
   - Forward-declare `class wxCStrData;` before `namespace zen`.
   - Add `static wchar_t conversionType(const wxCStrData&);` to `GetCharTypeImpl<S, StringType::class_>`.

6. **Compatibility fallback for `wxLogCollector`**:
   `wxLogCollector` was introduced in wxWidgets 3.3.1+.
   - Created `wx+/log.h` with a custom `wxLogCollector` class inheriting from `wxLog` when `!wxCHECK_VERSION(3, 3, 1)`.
   - Included `<wx+/log.h>` in `localization.cpp`, `image_resources.cpp`, `batch_status_handler.cpp`, `gui_status_handler.cpp`, and `main_dlg.cpp`.

7. **Compatibility fallback for C++23 "deducing this" on GCC < 14**:
   C++23 explicit object parameter (`this const auto& self`) for recursive lambdas requires GCC 14+. Standard Linux distributions such as Ubuntu 24.04 ship with GCC 13 by default.
   - Refactored recursive lambdas in `FreeFileSync/Source/base/versioning.cpp` and `zen/dir_watcher.cpp` to use the portable zero-overhead self-passing lambda pattern.

8. **Compatibility guards for `libssh2` constants and error codes**:
   Distribution packages of `libssh2` (e.g. `libssh2-1-dev` 1.11.0 on Ubuntu 24.04) keep `MAX_SFTP_OUTGOING_SIZE` and `MAX_SFTP_READ_SIZE` in private headers, and may not define recent error codes such as `LIBSSH2_ERROR_MAC_FAILURE`, `LIBSSH2_ERROR_RANDGEN`, etc.
   - Defined `MAX_SFTP_OUTGOING_SIZE` and `MAX_SFTP_READ_SIZE` (30000) under `#ifndef` in `libssh2/libssh2_wrap.h`.
   - Guarded newer `LIBSSH2_ERROR_*` return cases in `libssh2/libssh2_wrap.h` with `#ifdef`.

9. **Index-based iteration for `wxAuiPaneInfoArray`**:
   In wxWidgets 3.2, `wxAuiManager::GetAllPanes()` returns `wxAuiPaneInfoArray` which privately inherits from `wxVector<wxAuiPaneInfo*>`, making `begin()`/`end()` inaccessible for C++ range-based for loops.
   - Replaced range-based loops over `auiMgr_.GetAllPanes()` with indexed `for (size_t i = 0; i < panes.GetCount(); ++i)` loops in `ui/main_dlg.cpp` and `ui/gui_status_handler.cpp`.

10. **Compatibility guard for `wxGridColumnHeaderRenderer::DrawHighlighted`**:
    `DrawHighlighted` was introduced in wxWidgets 3.3+ (transparent overlay selection). In wxWidgets 3.2, the method does not exist on `wxGridColumnHeaderRendererDefault`.
    - Wrapped `DrawHighlighted` with `#if wxCHECK_VERSION(3, 3, 0)` in `FreeFileSync/Source/ui/small_dlgs.cpp`.

11. **Compatibility guards for `libcurl` version differences**:
    In libcurl < 8.8.0 (Ubuntu 24.04 ships with curl 8.5.0), `CURLE_OBSOLETE34` was still named `CURLE_HTTP_POST_ERROR`, `CURLE_OBSOLETE41` was `CURLE_FUNCTION_NOT_FOUND`, while `CURLE_TOO_LARGE` was added in 8.6.0 and `CURLE_ECH_REQUIRED` in 8.8.0.
    - Guarded `CURLE_OBSOLETE34` / `CURLE_HTTP_POST_ERROR` and `CURLE_OBSOLETE41` / `CURLE_FUNCTION_NOT_FOUND` with `#if LIBCURL_VERSION_NUM >= 0x080800`.
    - Guarded `CURLE_TOO_LARGE` (0x080600) and `CURLE_ECH_REQUIRED` (0x080800) in `libcurl/curl_wrap.cpp`.

12. **Compatibility fallback for `wxColorHook`**:
    Upstream assumes a custom-patched wxWidgets build that adds `wxColorHook` and `refGlobalColorHook()` into `wx/settings.h` (documented in `Bugs.txt`).
    - Added self-contained fallback definitions for `struct wxColorHook` and `refGlobalColorHook()` in `wx+/darkmode.cpp`.

13. **Compatibility fallback for `wxSYS_COLOUR_GRIDLINES`**:
    `wxSYS_COLOUR_GRIDLINES` is not a standard wxWidgets system color constant and is only present in custom wxWidgets forks.
    - Defined `wxSYS_COLOUR_GRIDLINES` fallback as `wxSYS_COLOUR_3DLIGHT` in `wx+/grid.h`.

14. **Compatibility fallback for `wxSystemAppearance::AreAppsDark`**:
    In wxWidgets 3.2 on Linux/GTK, `wxSystemAppearance::AreAppsDark()` was only defined on Windows (`__WXMSW__`).
    - Added fallback to `IsDark()` when `!defined(__WXMSW__) && !wxCHECK_VERSION(3, 3, 0)` in `wx+/darkmode.cpp`.

15. **Explicit `gtk+-3.0` linkage in Makefiles**:
    Modern Linux linkers enforce `--as-needed` / `--no-copy-dt-needed-entries`, which disallows implicit DSO linkage from wxWidgets for direct GTK calls (such as `gtk_css_provider_load_from_path`).
    - Added `LDFLAGS += \`pkg-config --libs gtk+-3.0\`` to `FreeFileSync/Source/Makefile` and `FreeFileSync/Source/RealTimeSync/Makefile`.

---

## 4. CI/CD & Automated Releases

The GitHub Actions workflow in [`.github/workflows/ci.yml`](.github/workflows/ci.yml) manages compilation, packaging, and automatic publishing.

### Key Rules
- **Automatic Publishing on Push to Main**: Every update pushed to the `main` branch automatically triggers CI compilation and updates/publishes the release for the current version (`v<version>`).
- **Tag-Based Releases**: Pushing a tag matching `v*` (e.g. `v14.12`) triggers the exact same pipeline.
- **Architectures Built**:
  - `Linux x86_64` (Runner: `ubuntu-24.04`)
  - `Linux aarch64` / ARM64 (Runner: `ubuntu-24.04-arm`)
- **Release Artifacts**:
  - `FreeFileSync_<version>_Linux_<arch>.tar.gz` (Portable binary bundle with `Bin/`, `Resources/`, and launcher scripts).
  - `FreeFileSync_<version>_Source.tar.gz` and `.zip` (Clean source archives).
  - `SHA256SUMS.txt` (Aggregated SHA-256 checksums).
- **Release Notes**: Automatically parsed from `Changelog.txt` by [`scripts/extract_changelog.py`](scripts/extract_changelog.py).

---

## 5. Local Build & Test Commands

### Prerequisites (Debian/Ubuntu)
```bash
sudo apt update
sudo apt install build-essential pkg-config libwxgtk3.2-dev libgtk-3-dev \
    libcurl4-openssl-dev libssh2-1-dev libssl-dev libidn2-dev zlib1g-dev libselinux1-dev
```

### Build FreeFileSync
```bash
cd FreeFileSync/Source
make -j$(nproc)
```

### Build RealTimeSync
```bash
cd FreeFileSync/Source/RealTimeSync
make -j$(nproc)
```

### Run
```bash
# From repository root after build:
./FreeFileSync/Build/Bin/FreeFileSync_$(uname -m)
```

---

## 6. Guidelines for AI Agents

1. **Documentation Integrity**: When updating version numbers, synchronize badges and text across `README.md`, `README_zh-CN.md`, `README_DE.md`, and `README_JP.md`.
2. **YAML Validation**: Always validate `.github/workflows/*.yml` with a YAML parser before committing.
3. **Commit Messages**: Follow standard descriptive commit conventions:
   `FreeFileSync <version>: <summary of changes>`
