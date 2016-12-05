//
//  Logger.cpp
//  easy
//
//  Created by 欧阳建华 on 2016/12/5.
//  Copyright © 2016年 hackerc. All rights reserved.
//

#include "Logger.hpp"
#include <thread>
#include <string>
#include <iostream>

namespace easy {
    namespace runtime {
        
        Logger::LogInfoQueue::LogInfoQueue()
        : std::queue<LogInfo>() {
        }
        
        int Logger::LogInfoQueue::enqueue(const easy::runtime::Logger::LogInfo &info) {
            push(info);
            return (int)size();
        }
        
        int Logger::LogInfoQueue::enqueue(easy::runtime::Logger *logger, LogLevel level, const std::string &message) {
            LogInfo info = {logger, level, std::time(nullptr), message};
            return enqueue(info);
        }
        
        Logger::LogInfo Logger::LogInfoQueue::dequeue() {
            LogInfo info = front();
            pop();
            return info;
        }

        Logger::LogInfoQueue& Logger::logInfoQueue() {
            static LogInfoQueue queue;
            return queue;
        }
        
        Logger::Logger()
        {
            
        }
        
        std::string Logger::levelString(LogLevel level) {
            static std::string levels[LogLevelCount] = {
               "information", "debug", "error"
            };
            return levels[level];
        }
        
        void Logger::write(std::time_t time, LogLevel level, const std::string &message) {
            std::cout<<levelString(level)<<": "<<std::asctime(std::localtime(&time))<< message<<"\n";
        }
        
        
        void Logger::Init() {
            static bool initialized = false;
            if(initialized) return;
            std::thread(threadProc).detach();
        }
        
        void Logger::threadProc() {
            LogInfo info;
            while (true) {
                if(Logger::GetLogInfo(info) && info.logger) {
                    info.logger->write(info.time, info.level, info.message);
                }
            }
        }
        bool Logger::GetLogInfo(easy::runtime::Logger::LogInfo &info) {
            if (logInfoQueue().empty()) return false;
            info  = logInfoQueue().dequeue();
            return true;
        }
        
        
        Logger& Logger::debug(const std::string &message) {
            logInfoQueue().enqueue(this, Log_Debug, message);
            return *this;
        }
        
        Logger& Logger::debug(const char *message) {
            return debug(std::string(message));
        }
        
        Logger& Logger::info(const std::string &message) {
            logInfoQueue().enqueue(this, Log_Info, message);
            return *this;
        }
        
        Logger& Logger::info(const char *message) {
            return info(std::string(message));
        }
        
        Logger& Logger::error(const std::string &message) {
            logInfoQueue().enqueue(this, Log_Error, message);
            return *this;
        }
        
        Logger& Logger::error(const char *message) {
            return error(std::string(message));
        }
    }
}
