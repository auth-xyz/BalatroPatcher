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

public:
  Patcher() = default;

  void revert(const std::string &archivePath) const {
    std::string backupPath =
        archivePath.substr(0, archivePath.find_last_of('.')) + "-original.exe";

    // Check if the backup file exists, if it exists rename it to the original, file overwriting the patch
    if (fs::exists(backupPath)) {
      fs::rename(backupPath, archivePath);
      std::cout << "Revert successful.\n";
    } else {
      std::cerr << "Error: Backup file does not exist.\n";
    }
  }

  void updateContents(const std::string &archivePath,
                      const std::string &modFolderPath) {
    if (!fs::exists(modFolderPath) || !fs::is_directory(modFolderPath)) {
      std::cerr << "Error: Mod folder does not exist or is not a directory.\n";
      return;
    }

    backupOriginal(archivePath);

    std::string command = "7za u \"" + archivePath + "\"";

    for (const auto &entry : fs::recursive_directory_iterator(modFolderPath)) {
      if (fs::is_regular_file(entry)) {
        std::string relativePath =
            fs::relative(entry.path(), modFolderPath).string();
        command += " \"" + relativePath + "\"";
      }
    }

    std::string originalPath = fs::current_path().string();
    fs::current_path(modFolderPath);

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


