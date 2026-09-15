# FreeFileSync

[English](README.md) | [Deutsch](README_DE.md) | [简体中文](README_zh-CN.md) | [日本語](README_JP.md)

[![Version](https://img.shields.io/badge/version-14.12-blue.svg)](https://freefilesync.org)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)](https://freefilesync.org/download.php)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B23)

## はじめに

**FreeFileSync** は、重要なファイルのバックアップと同期を行うための、無料でオープンソースのフォルダ比較・同期ソフトウェアです。毎回すべてのファイルをコピーするのではなく、ソースフォルダとターゲットフォルダの差分を検出し、必要な最小限のデータのみを転送します。

FreeFileSync はクロスプラットフォーム対応で、**Windows**、**macOS**、**Linux** で動作します。また、フォルダをリアルタイムに監視して変更検知時に同期を自動実行するツール **RealTimeSync** も同梱されています。

- **公式ウェブサイト**: [https://freefilesync.org](https://freefilesync.org)
- **公式ダウンロード**: [https://freefilesync.org/download.php](https://freefilesync.org/download.php)
- **ソースリポジトリ**: [https://github.com/BerryUIKI/FreeFileSync-Source](https://github.com/BerryUIKI/FreeFileSync-Source)

---

## 主な機能

- **クロスプラットフォーム互換性**: Windows、macOS、Linux でネイティブに動作します。
- **柔軟な同期モード**: 双方向同期（Two-way）、ミラー同期（Mirror）、更新同期（Update）、およびカスタム同期に対応。
- **多彩なプロトコル対応**: ローカルディスク、ネットワーク共有（SMB）、SFTP（SSHファイル転送）、FTP/FTPS、Google Drive との同期をサポート。
- **高速なスキャン性能**: マルチスレッドによるディレクトリ走査と最適化されたバイナリデータベースによる差分管理。
- **競合およびエラー処理**: 確実な競合検出と解決、自動リトライ、フェイルセーフなファイルコピー。
- **自動化とリアルタイム監視**: コマンドラインによるバッチ処理と、RealTimeSync による自動フォルダ監視。
- **高度なフィルタリング**: ワイルドカード、更新日時、ファイルサイズ、正規表現による除外/包含ルール。
- **データ保護**: バージョニング機能（変更前・削除前ファイルを指定フォルダやごみ箱に退避）。

---

## ソースコードからのビルド

### 必要環境

FreeFileSync のビルドには C++23 対応のコンパイラと各種開発ライブラリが必要です：

- **コンパイラ**: C++23 (`-std=c++23`) をサポートする GCC 13+ または Clang 17+
- **wxWidgets**: バージョン 3.2 以降（`wx-config`、`std`, `aui`, `richtext` コンポーネント）
- **GTK+**: GTK 3.0 開発ヘッダー（`gtk+-3.0`）
- **ネットワーク & 暗号化ライブラリ**:
  - OpenSSL (`openssl`)
  - libcurl (`libcurl`)
  - libssh2 (`libssh2`)
  - libidn2 (`libidn2`)
- **圧縮ライブラリ**: zlib
- **SELinux** *(オプション)*: `libselinux`

#### Linux (Debian / Ubuntu) での依存関係インストール

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

### ビルド手順

1. **リポジトリをクローン**:
   ```bash
   git clone https://github.com/BerryUIKI/FreeFileSync-Source.git
   cd FreeFileSync-Source
   ```

2. **FreeFileSync をビルド**:
   ```bash
   cd FreeFileSync/Source
   make -j$(nproc)
   ```

3. **RealTimeSync をビルド** *(オプション)*:
   ```bash
   cd RealTimeSync
   make -j$(nproc)
   ```

ビルドが完了すると、各ディレクトリに対応する実行ファイルが生成されます。

---

## 使い方

### GUI（グラフィカル操作）
1. `FreeFileSync` を起動します。
2. 左右のフォルダ欄に同期元のフォルダと同期先のフォルダを指定（またはドラッグ＆ドロップ）します。
3. 比較方法（ファイル日時とサイズ、内容、ファイルサイズ）および同期設定（双方向、ミラー、更新、カスタム）を選択します。
4. **比較** ボタンをクリックして差分を確認し、**同期処理** ボタンをクリックして同期を開始します。

### RealTimeSync によるリアルタイム監視
1. `RealTimeSync` を起動します。
2. 監視対象のフォルダパスとアイドル待機時間を指定します。
3. 変更検出時に実行するコマンド（保存済みのバッチ設定 `.ffs_batch` の実行）を設定します。
4. **開始** をクリックするとタスクトレイに常駐し、監視を開始します。

---

## コントリビューション

オープンソースコミュニティからの貢献を歓迎します：

1. リポジトリをフォークします: [https://github.com/BerryUIKI/FreeFileSync-Source](https://github.com/BerryUIKI/FreeFileSync-Source)
2. トピックブランチを作成します（`git checkout -b feature/my-feature`）。
3. 変更を加え、わかりやすいコミットメッセージでコミットします。
4. フォーク先のリポジトリへプッシュします（`git push origin feature/my-feature`）。
5. メインリポジトリへ Pull Request を送信します。

---

## ライセンス

FreeFileSync は個人・非商用目的において **GNU General Public License v3.0 (GPLv3)** に基づいて配布されています。商用および公的機関等での利用には FreeFileSync Business Edition の購入が必要です。

ライセンスの全条項については [LICENSE](LICENSE) および [License.txt](License.txt) をご参照ください。付属する外部ライブラリのライセンスは以下のとおりです：
- **wxWidgets**: wxWindows Library Licence 3.1
- **OpenSSL**: OpenSSL License / SSLeay License
- **libcurl**: curl License (MIT スタイル)
- **libssh2**: libssh2 License (BSD 3-Clause)
- **PuTTY**: PuTTY Licence (MIT スタイル)

---

## サポートとリソース

- **公式フォーラム**: [https://freefilesync.org/forum/](https://freefilesync.org/forum/)
- **よくある質問 (FAQ)**: [https://freefilesync.org/faq.php](https://freefilesync.org/faq.php)
- **マニュアル & チュートリアル**: [https://freefilesync.org/manual.php](https://freefilesync.org/manual.php)
- **リポジトリ Issues**: [https://github.com/BerryUIKI/FreeFileSync-Source/issues](https://github.com/BerryUIKI/FreeFileSync-Source/issues)

---

## 謝辞

FreeFileSync を開発・保守されている Zenju 氏およびコミュニティの皆様、翻訳者、コントリビューター、すべてのユーザーに感謝いたします。
