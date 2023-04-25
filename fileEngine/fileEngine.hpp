#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
  void saveFile(std::string &stringInput);
};