#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "File was not passed\n";
        return 1;
    }
    fs::path file_path = argv[1];
    std::error_code ec;
    if (!fs::exists(file_path, ec) || !fs::is_regular_file(file_path, ec)) {
        std::cerr << "File does not exist or is not a regular file.\n";
        return 1;
    }
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading (check permissions).\n";
        return 1;
    }
    std::vector<std::string> lines = {};
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    if (file.bad()) {
        std::cerr << "An I/O error occurred while reading the file.\n";
        return 1;
    }
    for(int i = 0; i < lines.size(); ++i) {
        std::cout << lines.at(i) << "\n";
    }
	return 0;
}
