#ifndef LOGGER_H
#define LOGGER_H

#ifdef Arduino_h
// arduino is not compatible with std::vector
#undef min
#undef max
#endif
#include <vector>

#include <inttypes.h>
#include <stdarg.h>

#include "Appender.h"
#include "SerialAppender.h"

namespace log4arduino {

  class Logger {

    public:

      Logger(const char* name = "default", bool addDefaultSerialAppender = true);

      template <class T, typename... Args> 
      void fatal(T msg, Args... args) {
        
        print(Appender::FATAL, msg, args...);
      }

      template <class T, typename... Args> 
      void error(T msg, Args... args) {
        
        print(Appender::ERROR, msg, args...);
      }

      template <class T, typename... Args> 
      void warning(T msg, Args... args) {
        
        print(Appender::WARNING, msg, args...);
      }

      template <class T, typename... Args> 
      void verbose(T msg, Args... args) {
        
        print(Appender::VERBOSE, msg, args...);
      }

      template <class T, typename... Args> 
      void trace(T msg, Args... args) {
        
        print(Appender::TRACE, msg, args...);
      }

      const char* getName();

      std::vector<Appender*>& getAppender();

      void addFormatterToAll(Appender::FormatterFunction formatterFunction);

      void addFilterToAll(Appender::FilterFunction filterFunction);

      void addLevelToAll(Appender::Level level);

      template <class T>
      void print(Appender::Level level, T msg, ...) {
        
        va_list args;
        va_start(args, msg);
        String str = String(msg); // use String constructor to handle PROGMEN and other character representations
        for (auto && fn : _appender) {
          fn->print(level, str.c_str(), &args);
        }
        va_end(args);
      }

    private:

      const char* _name;

      std::vector<Appender*> _appender;
  };

  extern Logger LOG;
}

#endif // LOGGER_H
