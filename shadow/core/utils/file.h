#pragma once

namespace Shadow {
class File {
public:
    static std::string Read(std::string const& path) {
        std::ifstream fs(path, std::ios::in | std::ios::binary);
        std::string content;

        if(fs) {
            fs.seekg(0, std::ios::end);
            size_t size = fs.tellg();
            if (size == -1) {
                SH_CORE_ERROR("Could not read from file '{0}'", path);
            } else {
                content.resize(size);
                fs.seekg(0, std::ios::beg);
                fs.read(&content[0], size);
                fs.close();
            }
        } else {
            SH_CORE_ERROR("Could not open file '{0}'", path);
        }

        return content;
    }

    static void Write(std::string const& path, std::string const& content, bool append = false) {
        std::ofstream fs;
        if (append)
            fs.open(path, std::ofstream::out | std::ofstream::binary | std::ofstream::app);
        else
            fs.open(path, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);

        fs.write(content.c_str(), sizeof(char)*content.size());

        fs.close();
    }
};
}