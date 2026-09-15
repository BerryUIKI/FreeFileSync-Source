#!/usr/bin/env python3
import os
import re
import sys

def main():
    if len(sys.argv) < 2:
        print("Usage: extract_changelog.py <version> [changelog_path] [checksums_path] [output_path]")
        sys.exit(1)

    version = sys.argv[1].lstrip("v")
    changelog_path = sys.argv[2] if len(sys.argv) > 2 else "Changelog.txt"
    checksums_path = sys.argv[3] if len(sys.argv) > 3 else "release_assets/SHA256SUMS.txt"
    output_path = sys.argv[4] if len(sys.argv) > 4 else "release_notes.md"

    notes = ""
    if os.path.exists(changelog_path):
        with open(changelog_path, "r", encoding="utf-8") as f:
            text = f.read()
        pattern = r"(FreeFileSync\s+" + re.escape(version) + r"[\s\S]*?)(?=\nFreeFileSync\s+\d+\.\d+|\Z)"
        match = re.search(pattern, text)
        if match:
            notes = match.group(1).strip()

    if not notes:
        notes = f"FreeFileSync {version}\n------------------------\nRelease of FreeFileSync {version}."

    checksums = ""
    if os.path.exists(checksums_path):
        with open(checksums_path, "r", encoding="utf-8") as f:
            checksums = f.read().strip()

    with open(output_path, "w", encoding="utf-8") as out:
        out.write(f"## FreeFileSync {version}\n\n")
        out.write(notes + "\n\n")
        if checksums:
            out.write("### Checksums (SHA-256)\n```\n")
            out.write(checksums + "\n")
            out.write("```\n")

    print(f"Generated {output_path} successfully.")

if __name__ == "__main__":
    main()
