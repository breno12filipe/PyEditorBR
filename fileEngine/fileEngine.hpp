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
        void setFileData(std::string &inputCharacter); // Check the returned type
        std::string getFileName();
        std::string getFilePath();
        bool createFile();
};