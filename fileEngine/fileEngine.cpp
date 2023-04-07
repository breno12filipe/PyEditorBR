#include "fileEngine.hpp"

FileEngine::FileEngine(std::string fileName){
    this->fileName_ = fileName;
}

FileEngine::~FileEngine(){
    // Close file instance
}

std::string FileEngine::getFileData(){
    std::string otpTxt;
    std::ifstream FileReading(this->fileName_);
    while (getline (FileReading, otpTxt)) {
        this->fileRepr_.append(otpTxt);
    }
    FileReading.close();
    return this->fileRepr_;
}

void FileEngine::setFileData(std::string &inputCharacter){
    // std::ofstream foutput;
    // std::ifstream finput;
    // finput.open(this->filePath_ + this->fileName_);
    // foutput.open(this->filePath_ + this->fileName_, std::ios::app);
    
    // if(finput.is_open()){
    //     foutput << inputCharacter;
    // }
    
    // finput.close();
    // foutput.close();
}

std::string FileEngine::getFileName(){
    return this->fileName_;
}

std::string FileEngine::getFilePath(){
    return this->fileName_;
}

bool FileEngine::createFile(){
    std::ofstream outFile(this->fileName_);
    outFile << "# This File was created using PyEditorBr ;)" << std::endl;
    outFile.close();
    if (!outFile) {
        std::cerr << "\033[91mERROR CREATING FILE: " << this->fileName_ << this->fileName_ << std::endl;
    }
}