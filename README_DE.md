# FreeFileSync

[English](README.md) | [Deutsch](README_DE.md) | [简体中文](README_zh-CN.md) | [日本語](README_JP.md)

[![Version](https://img.shields.io/badge/version-14.12-blue.svg)](https://freefilesync.org)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)](https://freefilesync.org/download.php)
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B23)

## Einführung

**FreeFileSync** ist eine freie Open-Source-Software für Ordnervergleich und -synchronisation zur Sicherung wichtiger Dateien. Anstatt bei jedem Vorgang sämtliche Daten erneut zu kopieren, analysiert FreeFileSync die Unterschiede zwischen Quell- und Zielverzeichnis und überträgt lediglich die minimal erforderliche Datenmenge.

FreeFileSync ist plattformübergreifend für **Windows**, **macOS** und **Linux** verfügbar. Das Paket umfasst zudem **RealTimeSync**, ein Hilfswerkzeug zur Verzeichnisüberwachung und automatisierten Ausführung von Synchronisationsjobs bei erkannten Dateiänderungen.

- **Offizielle Website**: [https://freefilesync.org](https://freefilesync.org)
- **Downloads**: [https://freefilesync.org/download.php](https://freefilesync.org/download.php)
- **Quellcode-Repository**: [https://github.com/BerryUIKI/FreeFileSync-Source](https://github.com/BerryUIKI/FreeFileSync-Source)

---

## Funktionen

- **Plattformübergreifend**: Läuft nativ auf Windows, macOS und Linux.
- **Flexible Synchronisationsmodi**: Unterstützt Zwei-Wege-, Spiegelungs-, Aktualisierungs- sowie vollständig benutzerdefinierte Synchronisation.
- **Vielseitige Protokolle**: Nahtlose Synchronisation mit lokalen Laufwerken, Netzwerkfreigaben (SMB), SFTP (SSH File Transfer Protocol), FTP/FTPS und Google Drive.
- **Hohe Performance**: Mehrfädige Verzeichnisabtastung und optimierte Binärdatenbanken für effiziente inkrementelle Abgleiche.
- **Konflikt- und Fehlerbehandlung**: Umfassende Konflikterkennung, automatische Wiederholungsversuche und ausfallsichere Kopiermechanismen.
- **Automatisierung**: Stapelverarbeitung über die Befehlszeile sowie automatisierte Ordnerüberwachung via RealTimeSync.
- **Erweiterte Filterung**: Ein- und Ausschlussregeln basierend auf Platzhaltern, Dateiänderungszeit, Dateigröße und regulären Ausdrücken.
- **Datensicherheit**: Versionierung zur Aufbewahrung älterer Dateistände in gesonderten Ordnern oder im Papierkorb.

---

## Aus dem Quellcode erstellen

### Voraussetzungen

Zur Übersetzung wird ein moderner C++23-Compiler sowie gängige Entwicklungsbibliotheken benötigt:

- **Compiler**: GCC 13+ oder Clang 17+ mit C++23-Unterstützung (`-std=c++23`)
- **wxWidgets**: Version 3.2 oder neuer (`wx-config` mit `std`, `aui`, `richtext`)
- **GTK+**: GTK 3.0 Header (`gtk+-3.0`)
- **Netzwerk & Kryptographie**:
  - OpenSSL (`openssl`)
  - libcurl (`libcurl`)
  - libssh2 (`libssh2`)
  - libidn2 (`libidn2`)
- **Kompression**: zlib
- **SELinux** *(optional)*: `libselinux`

#### Abhängigkeiten unter Linux (Debian / Ubuntu) installieren

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

### Bauanleitung

1. **Repository klonen**:
   ```bash
   git clone https://github.com/BerryUIKI/FreeFileSync-Source.git
   cd FreeFileSync-Source
   ```

2. **FreeFileSync kompilieren**:
   ```bash
   cd FreeFileSync/Source
   make -j$(nproc)
   ```

3. **RealTimeSync kompilieren** *(optional)*:
   ```bash
   cd RealTimeSync
   make -j$(nproc)
   ```

Nach Abschluss der Übersetzung liegen die Binärdateien in den jeweiligen Verzeichnissen bereit.

---

## Verwendung

### Grafische Oberfläche
1. Starten Sie `FreeFileSync`.
2. Wählen Sie Quell- und Zielordner aus oder ziehen Sie diese per Drag & Drop in die Ordnerfelder.
3. Passen Sie die Vergleichsmethode (Dateizeit und -größe, Inhalt oder Dateigröße) sowie die Synchronisationsrichtung an.
4. Klicken Sie auf **Vergleichen** und anschließend auf **Synchronisieren**.

### RealTimeSync
1. Starten Sie `RealTimeSync`.
2. Legen Sie die zu überwachenden Verzeichnisse sowie eine Leerlaufzeit fest.
3. Hinterlegen Sie den Befehlsaufruf für die gespeicherte FreeFileSync-Batchdatei (`.ffs_batch`).
4. Klicken Sie auf **Start**, um die Überwachung im Infobereich zu starten.

---

## Mitwirken

Beiträge aus der Open-Source-Community sind stets willkommen:

1. Forken Sie das Repository unter [https://github.com/BerryUIKI/FreeFileSync-Source](https://github.com/BerryUIKI/FreeFileSync-Source).
2. Erstellen Sie einen Feature-Branch (`git checkout -b feature/mein-beitrag`).
3. Führen Sie Ihre Änderungen durch und committen Sie diese mit einer aussagekräftigen Nachricht.
4. Pushen Sie Ihren Branch in Ihren Fork (`git push origin feature/mein-beitrag`).
5. Öffnen Sie einen Pull Request mit einer Beschreibung der Änderungen.

---

## Lizenz

FreeFileSync wird für den privaten Gebrauch unter der **GNU General Public License v3.0 (GPLv3)** bereitgestellt; für den kommerziellen und behördlichen Einsatz gelten die Bestimmungen der FreeFileSync Business Edition.

Vollständige Lizenzbedingungen finden sich in [LICENSE](LICENSE) und [License.txt](License.txt), inklusive der Lizenzen eingebundener Bibliotheken:
- **wxWidgets**: wxWindows Library Licence 3.1
- **OpenSSL**: OpenSSL License / SSLeay License
- **libcurl**: curl License (MIT-Stil)
- **libssh2**: libssh2 License (BSD 3-Clause)
- **PuTTY**: PuTTY Licence (MIT-Stil)

---

## Support & Hilfe

- **Offizielles Forum**: [https://freefilesync.org/forum/](https://freefilesync.org/forum/)
- **Häufig gestellte Fragen (FAQ)**: [https://freefilesync.org/faq.php](https://freefilesync.org/faq.php)
- **Handbuch & Anleitungen**: [https://freefilesync.org/manual.php](https://freefilesync.org/manual.php)
- **Repository-Issues**: [https://github.com/BerryUIKI/FreeFileSync-Source/issues](https://github.com/BerryUIKI/FreeFileSync-Source/issues)

---

## Danksagung

Ein besonderer Dank gilt Zenju und der gesamten FreeFileSync-Community für die Entwicklung und Pflege dieser Software sowie allen Übersetzern und Nutzern weltweit.
