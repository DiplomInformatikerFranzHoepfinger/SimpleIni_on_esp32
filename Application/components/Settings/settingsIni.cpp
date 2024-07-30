/* ************************************************************************ */
/*!
   \file
   \brief       Helper functions for reading and writing settings to a file.
   \author      Wegscheider Peter
   \copyright   Competence Center ISOBUS e.V. \n
                MIT License
*/
/* ************************************************************************ */
#ifdef WIN32
#include <windows.h>
#endif
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include "settingsIni.h"

#define SI_CONVERT_GENERIC
#include "SimpleIni.h"

#define MAXNUMSTRLEN      128U

#if defined(linux)
//#define vswprintf_s swprintf
//#define vsprintf_s snprintf
//#define _strtoui64 strtoull
//#define vswprintf_s swprintf
//#define vsprintf_s snprintf
#define sprintf_s snprintf
#define strcpy_s(dest, size, src) strncpy(dest, src, size)

#define SETTING_NAME "./settings.ini"
#else 
//#define SETTING_NAME ".\\settings.ini"
//#define SETTING_NAME "./settings.ini"
#endif // defined(linux)

#if defined(ESP_PLATFORM)
#define sprintf_s snprintf
#define strcpy_s(dest, size, src) strncpy(dest, src, size)
#define SETTING_NAME "/data/settings.ini"
#endif


/* ************************************************************************ */
struct Settings
{
   std::string filePath = std::string(SETTING_NAME);
   bool        isLoaded = false;
   CSimpleIniA ini;
   CSimpleIniA* getInstance() 
   {
      if (isLoaded == false)
      {
         ini.SetMultiKey(false);
         ini.Reset();
         ini.LoadFile(filePath.c_str());
         isLoaded = true;
      }
      return &ini;
   }
   void Save( bool remove = false)
   {
      if (isLoaded == true)
      {
         ini.SaveFile(filePath.c_str());
         isLoaded = !remove;
      }
   }
   ~Settings()
   {
      Save(true);
   }
};

/* ************************************************************************ */

static struct Settings settings;

/* ************************************************************************ */

int8_t getS8(const char section[], const char key[], const int8_t defaultValue)
{
   int64_t ret = getS64(section, key, defaultValue);
   return ((ret > INT8_MAX) || (ret < INT8_MIN)) ? defaultValue : (int8_t)(ret);
}

int16_t getS16(const char section[], const char key[], const int16_t defaultValue)
{
   int64_t ret = getS64(section, key, defaultValue);
   return ((ret > INT16_MAX) || (ret < INT16_MIN)) ? defaultValue : (int16_t)(ret);
}

int32_t getS32(const char section[], const char key[], const int32_t defaultValue)
{
   int64_t ret = getS64(section, key, defaultValue);
   return ((ret > INT32_MAX) || (ret < INT32_MIN)) ? defaultValue : (int32_t)(ret);
}

int64_t getS64(const char section[], const char key[], const int64_t defaultValue)
{
   uint64_t ret = defaultValue;
   const char* pv;
   pv = settings.getInstance()->GetValue(section, key);
   if (pv == 0)
   {
       char buffer[MAXNUMSTRLEN] = { 0 };
#ifdef WIN32
      sprintf_s(buffer, sizeof(buffer), "%I64d", defaultValue);
#else
      sprintf_s(buffer, sizeof(buffer), "%lld", (long long)defaultValue);
#endif
      settings.getInstance()->SetValue(section, key, buffer);
   }
   else
   {
      ret = strtoll(pv, NULL, 10);
   }
   return ret;
}

/* ************************************************************************ */

uint8_t getU8(const char section[], const char key[], const uint8_t defaultValue)
{
   uint64_t ret = getU64(section, key, defaultValue);
   return (ret > UINT8_MAX) ? defaultValue : (uint8_t)(ret);
}

uint16_t getU16(const char section[], const char key[], const uint16_t defaultValue)
{
   uint64_t ret = getU64(section, key, defaultValue);
   return (ret > UINT16_MAX) ? defaultValue : (uint16_t)(ret);
}

uint32_t getU32(const char section[], const char key[], const uint32_t defaultValue)
{
   uint64_t ret = getU64(section, key, defaultValue);
   return (ret > UINT32_MAX) ? defaultValue : (uint32_t)(ret);
}

uint64_t getU64(const char section[], const char key[], const uint64_t defaultValue)
{
   uint64_t ret = defaultValue;
   const char* pv;
   pv = settings.getInstance()->GetValue(section, key);
   if (pv == 0)
   {
      char buffer[MAXNUMSTRLEN] = { 0 };
#ifdef WIN32
      sprintf_s(buffer, sizeof(buffer), "%I64d", defaultValue);
#else
      sprintf_s(buffer, sizeof(buffer), "%lld", (unsigned long long)defaultValue);
#endif
      settings.getInstance()->SetValue(section, key, buffer);
   }
   else
   {
      ret = strtoull(pv, NULL, 10);
   }
   return ret;
}

/* ************************************************************************ */

uint64_t getX64(const char section[], const char key[], const uint64_t defaultValue)
{
   uint64_t ret = defaultValue;
   const char* pv;
   pv = settings.getInstance()->GetValue(section, key);
   if (pv != 0)
   {
      ret = strtoull(pv, NULL, 16);
   }
   return ret;
}

void getString(const char section[], const char key[], const char defaultValue[], char captionOut[], uint32_t stringSize)
{
   const char* pv;
   pv = settings.getInstance()->GetValue(section, key);
   if ((pv == 0) && (defaultValue != 0))
   {
      settings.getInstance()->SetValue(section, key, defaultValue);
      pv = defaultValue;
   }

   if (pv != 0)
   { 
      strcpy_s(captionOut, stringSize, pv);
   }
}

/* ************************************************************************ */

void setS8(const char section[], const char key[], const int8_t value)
{
   setS64(section, key, value);
}

void setS16(const char section[], const char key[], const int16_t value)
{
   setS64(section, key, value);
}

void setS32(const char section[], const char key[], const int32_t value)
{
   setS64(section, key, value);
}

void setS64(const char section[], const char key[], const int64_t value)
{
   char buffer[MAXNUMSTRLEN];
#ifdef WIN32
   sprintf_s(buffer, sizeof(buffer), "%I64d", value);
#else
   sprintf_s(buffer, sizeof(buffer), "%lld", (long long)value);
#endif
   settings.getInstance()->SetValue(section, key, buffer);
}

/* ************************************************************************ */

void setU8(const char section[], const char key[], const uint8_t value)
{
    setU64(section, key, value);
}

void setU16(const char section[], const char key[], const uint16_t value)
{
    setU64(section, key, value);
}

void setU32(const char section[], const char key[], const uint32_t value)
{
    setU64(section, key, value);
}

void setU64(const char section[], const char key[], const uint64_t value)
{
   char buffer[MAXNUMSTRLEN];
#ifdef WIN32
   sprintf_s(buffer, sizeof(buffer), "%I64u", value);
#else
   sprintf_s(buffer, sizeof(buffer), "%llu", (unsigned long long)value);
#endif
   settings.getInstance()->SetValue(section, key, buffer);
}

/* ************************************************************************ */

void setX64(const char section[], const char key[], const uint64_t value)
{
   char buffer[MAXNUMSTRLEN];
#ifdef WIN32
   sprintf_s(buffer, sizeof(buffer), "%I64x", value);
#else
   sprintf_s(buffer, sizeof(buffer), "%llx", (unsigned long long)value);
#endif
   settings.getInstance()->SetValue(section, key, buffer);
}

void setString(const char section[], const char key[], const char value[])
{
   if ((value != 0) && (*value != 0))
   {  // store key=value
      settings.getInstance()->SetValue(section, key, value);
   }
   else
   {  // remove key
      settings.getInstance()->Delete(section, key);
   }
}

/* ************************************************************************ */

uint32_t getSection(const char section[], char string[], uint32_t stringSize)
{
   uint32_t sectionChars = 0U;
   const CSimpleIni::TKeyVal* pSectionData = settings.getInstance()->GetSection(section);
   if (pSectionData) {
      // iterate over all keys and dump the key name and value
      CSimpleIni::TKeyVal::const_iterator iKeyVal = pSectionData->begin();
      for (; iKeyVal != pSectionData->end(); ++iKeyVal) {
         const char* pItem = iKeyVal->first.pItem;
         const char* pszVal = iKeyVal->second;
         sectionChars += sprintf_s(&string[sectionChars], (stringSize - sectionChars), "%s=%s\n", pItem, pszVal);
         string[sectionChars] = 0; // needed for aux assign read function...
         sectionChars++;
      }
   }
   return sectionChars;
}

void clearSection(const char section[])
{
   if ((section != nullptr) && (section[0] != 0))
   {
      settings.getInstance()->Delete(section, nullptr, false);
//create it again ?  settings.getInstance()->SetValue(section, nullptr, nullptr);
   }
}

/* ************************************************************************ */

void removeEntry(const char section[], const char key[])
{
   if ((section != nullptr) && (section[0] != 0))
   {
      settings.getInstance()->Delete(section, key);
   }
}

void createSection(const char section[])
{
   if ((section != nullptr) && (section[0] != 0))
   {
      settings.getInstance()->SetValue(section, nullptr, nullptr);
   }
}

void removeSection(const char section[])
{
   if ((section != nullptr) && (section[0] != 0))
   {
      settings.getInstance()->Delete(section, nullptr);
   }
}

void initSettings(const char fileName[])
{
   if (settings.isLoaded == true)
   {
      settings.Save();
   }

   if ((fileName != nullptr) && (fileName[0] != 0))
   {
      settings.filePath = std::string(fileName);
   }
   else
   {  /* NULL pointer -> Reset init */
      settings.ini.Reset();
   }
}

void saveSettings(void)
{
   settings.Save();
}

/* ************************************************************************ */
