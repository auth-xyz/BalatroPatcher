#pragma once
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class Patcher {
private:
  std::vector<std::string> overwrittenFiles;

  void logOverwrittenFiles() const {
    std::cout << "\nOverwritten files:\n";
    for (const auto &file : overwrittenFiles) {
      std::cout << "  " << file << "\n";
    }
  }

  void backupOriginal(const std::string &archivePath) const {
    std::string backupPath =
        archivePath.substr(0, archivePath.find_last_of('.')) + "-original.exe";

    if (fs::exists(backupPath)) {
      std::cout << "Backup already exists: " << backupPath << std::endl;
    } else {
      fs::copy(archivePath, backupPath);
      std::cout << "Backup created: " << backupPath << std::endl;
    }
  }

  std::string extractArchive(const std::string &archivePath) const {
    std::string extractFolder =
        archivePath.substr(0, archivePath.find_last_of('.')) + "_extracted";

    if (!fs::exists(extractFolder)) {
      fs::create_directory(extractFolder);
    }

    std::string command = "7za x -o\"" + extractFolder + "\" \"" + archivePath + "\"";
    std::cout << "Running extraction command: " << command << "\n";

    int result = system(command.c_str());
    if (result != 0) {
      std::cerr << "Error: Extraction failed with code " << result << ".\n";
      return "";
    }

    std::cout << "Extraction successful. Files extracted to: " << extractFolder << "\n";
    return extractFolder;
  }

public:
  Patcher() = default;

  void revert(const std::string &archivePath) const {
    std::string backupPath =
        archivePath.substr(0, archivePath.find_last_of('.')) + "-original.exe";

    if (fs::exists(backupPath)) {
      fs::rename(backupPath, archivePath);
      std::cout << "Revert successful.\n";
    } else {
      std::cerr << "Error: Backup file does not exist.\n";
    }
  }

  void updateContents(const std::string &archivePath,
                      const std::string &modFolderPath) {
    std::string actualModFolderPath = modFolderPath;

    if (fs::is_regular_file(modFolderPath)) {
      std::string extractedFolder = extractArchive(modFolderPath);
      if (extractedFolder.empty()) {
        std::cerr << "Error: Unable to extract mod archive.\n";
        return;
      }
      actualModFolderPath = extractedFolder;
    }

    if (!fs::exists(actualModFolderPath) || !fs::is_directory(actualModFolderPath)) {
      std::cerr << "Error: Mod folder does not exist or is not a directory.\n";
      return;
    }

    backupOriginal(archivePath);

    std::string command = "7za u \"" + archivePath + "\"";

    for (const auto &entry : fs::recursive_directory_iterator(actualModFolderPath)) {
      if (fs::is_regular_file(entry)) {
        std::string relativePath =
            fs::relative(entry.path(), actualModFolderPath).string();
        command += " \"" + relativePath + "\"";
      }
    }

    std::string originalPath = fs::current_path().string();
    fs::current_path(actualModFolderPath);

    std::cout << "Running command: " << command << "\n";
    int result = system(command.c_str());

    fs::current_path(originalPath);

    if (result == 0) {
      std::cout << "Update successful.\n";
    } else {
      std::cerr << "Error: Update failed with code " << result << ".\n";
    }
  }
};

