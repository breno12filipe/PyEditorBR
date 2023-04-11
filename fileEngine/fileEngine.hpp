#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class FileEngine {
    private:
        std::string fileName_;
        std::string fileRepr_;
    public:
        FileEngine(std::string fileName);
        ~FileEngine();
        std::string getFileData();
        std::string getFileName();
        std::string getFilePath();
        bool createFile();
        void saveFile();
};