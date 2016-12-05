//
//  FileLogger.cpp
//  easy
//
//  Created by 欧阳建华 on 2016/12/5.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#include "FileLogger.hpp"
#include <fstream>

namespace easy {
    namespace runtime {
        
        std::fstream FileLogger::_debugFile;
        std::fstream FileLogger::_infoFile;
        std::fstream FileLogger::_errorFile;
        
        FileLogger::FileLogger(const std::string& workDir)
        : _workDir(workDir){
            if (!_debugFile.is_open()) {
                _debugFile.open(_workDir + "/debug.log");
            }
            if(!_infoFile.is_open()) {
                _infoFile.open(_workDir + "/info.log");
            }
            
            if(!_errorFile.is_open()) {
                _errorFile.open(_workDir + "/error.log");
            }
         }
        
        std::fstream& FileLogger::getOutFile(LogLevel level) {
            switch (level) {
                case Log_Info:
                    return _infoFile;
                case Log_Debug:
                    return _debugFile;
                case Log_Error:
                    return _errorFile;
                default:
                    break;
            }
            return _infoFile;
        }
        
        void FileLogger::write(std::time_t time, LogLevel level, const std::string &message) {
            std::string timeString = std::asctime(std::localtime(&time));
            std::fstream & file = getOutFile(level);
            if(file.is_open()) {
                file<<levelString(level)<<": "<<message<<timeString;
            }
        }
    }
}
