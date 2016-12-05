//
//  Logger.hpp
//  easy
//
//  Created by 欧阳建华 on 2016/12/5.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#ifndef Logger_hpp
#define Logger_hpp

#include<queue>
#include <string>
#include <ctime>

namespace easy {
    namespace runtime {
        
        class Logger {
        public:
            
            typedef enum _LogLevel {
                Log_Info = 0,
                Log_Debug,
                Log_Error,
                LogLevelCount
            } LogLevel;
            
            struct LogInfo {
                Logger *logger;
                LogLevel level;
                std::time_t time;
                std::string message;
            };
            
            class LogInfoQueue: public std::queue<LogInfo> {
            public:
                LogInfoQueue();
                int enqueue(const LogInfo& info);
                int enqueue(Logger *logger, LogLevel level, const std::string&message);
                LogInfo dequeue();
            };
            
            Logger();
            
            static void Init();
            static std::string levelString(LogLevel level);
            
            Logger& info(const std::string& message);
            Logger& info(const char *message);
            
            Logger& debug(const  std::string& message);
            Logger& debug(const char *message);
            
            Logger& error(const  std::string& message);
            Logger& error(const char *message);
            
        protected:
            virtual void write(LogLevel level, const std::string& message);
            virtual void flush();
        private:
            static  LogInfoQueue& logInfoQueue();
            static bool GetLogInfo(LogInfo &info);
            static void threadProc();
        };
    }
}




#endif /* Logger_hpp */
