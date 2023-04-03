#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class FileEngine {
    private:
        std::string fileName_;
        std::string filePath_;
    public:
        FileEngine(std::string name, std::string path);
        ~FileEngine();
        void getFileData();
        void setFileData(std::string &inputCharacter); // Check the returned type
        std::string getFileName();
        std::string getFilePath();
};