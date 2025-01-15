#pragma once
#ifndef SERIAL_LOG_H
#define SERIAL_LOG_H

#ifdef SERIAL_LOG_DEBUG
  #if SERIAL_LOG_DEBUG
    static void SERIAL_LOG(const char* format, ...) {
      va_list args;
      va_start(args, format);
      Serial.printf(format, args);
      va_end(args);
    }
  #else
    #define SERIAL_LOG(...)
  #endif
#else
  #define SERIAL_LOG(...)
#endif

#endif // SERIAL_LOG_H
