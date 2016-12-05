//
//  FileLogger.hpp
//  easy
//
//  Created by 欧阳建华 on 2016/12/5.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#ifndef FileLogger_hpp
#define FileLogger_hpp

#include "Logger.hpp"

#include <fstream>
#include <string>

namespace easy {
    namespace runtime {
        class FileLogger: public Logger {
        public:
            FileLogger(const std::string &workDir = "./");
            std::fstream &getOutFile(LogLevel level);
        protected:
            virtual void write(std::time_t time, LogLevel level, const std::string &message);
        private:
            std::string _workDir;
        private:
            static std::fstream _debugFile;
            static std::fstream _infoFile;
            static std::fstream _errorFile;
            
        };
    }
}
#endif /* FileLogger_hpp */
