#include "fileEngine.hpp"

FileEngine::FileEngine(std::string name, std::string path){
    this->fileName_ = name;
    this->filePath_ = path;

    // Create the file
    std::ofstream outFile(filePath_ + fileName_);
    outFile << "# This File was created using PyEditorBr ;)" << std::endl;
    outFile.close();

    if (!outFile) {
        std::cerr << "\033[91mERROR CREATING FILE: " << this->filePath_ << this->fileName_ << std::endl;
    }
}

FileEngine::~FileEngine(){
    // Close file instance
}

void FileEngine::getFileData(){
    
}

void FileEngine::setFileData(std::string &inputCharacter){
    std::ofstream foutput; 
    std::ifstream finput;
    finput.open(this->filePath_ + this->fileName_);
    foutput.open(this->filePath_ + this->fileName_, std::ios::app); 
    
    if(finput.is_open()){
        foutput << inputCharacter; 
    }
    
    finput.close();
    foutput.close(); 
    
}

std::string FileEngine::getFileName(){
    return this->fileName_;
}

std::string FileEngine::getFilePath(){
    return this->filePath_;
}