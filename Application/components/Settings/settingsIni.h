/* ************************************************************************ */
/*!
   \file
   \brief       Helper functions for reading and writing settings to a file.
   \author      Wegscheider Peter
   \copyright   Competence Center ISOBUS e.V. \n
                MIT License
*/
/* ************************************************************************ */
#ifndef DEF_SETTINGS_H
#define DEF_SETTINGS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************ */

    int8_t   getS8(const char section[], const char key[], const int8_t defaultValue);
    int16_t  getS16(const char section[], const char key[], const int16_t defaultValue);
    int32_t  getS32(const char section[], const char key[], const int32_t defaultValue);
    int64_t  getS64(const char section[], const char key[], const int64_t defaultValue);
    uint8_t  getU8(const char section[], const char key[], const uint8_t defaultValue);
    uint16_t getU16(const char section[], const char key[], const uint16_t defaultValue);
    uint32_t getU32(const char section[], const char key[], const uint32_t defaultValue);
    uint64_t getU64(const char section[], const char key[], const uint64_t defaultValue);
    uint64_t getX64(const char section[], const char key[], const uint64_t defaultValue);
    void     getString(const char section[], const char key[], const char defaultValue[], char string[], uint32_t stringSize);
/* ************************************************************************ */
    void setS8(const char section[], const char key[], const int8_t value);
    void setS16(const char section[], const char key[], const int16_t value);
    void setS32(const char section[], const char key[], const int32_t value);
    void setS64(const char section[], const char key[], const int64_t value);
    void setU8(const char section[], const char key[], const uint8_t value);
    void setU16(const char section[], const char key[], const uint16_t value);
    void setU32(const char section[], const char key[], const uint32_t value);
    void setU64(const char section[], const char key[], const uint64_t value);
    void setX64(const char section[], const char key[], const uint64_t value);
    void setString(const char section[], const char key[], const char value[]);
/* ************************************************************************ */
    uint32_t getSection(const char section[], char string[], uint32_t stringSize);
    void     clearSection(const char section[]);
/* ************************************************************************ */
    void removeEntry(const char section[], const char key[]);
    void createSection(const char section[]);
    void removeSection(const char section[]);
/* ************************************************************************ */
    void initSettings(const char fileName[]);
    void saveSettings(void);

/* ************************************************************************ */
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* DEF_SETTINGS_H */
/* ************************************************************************ */
