/* TODO: File descrption
 * 
 */

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

// ========================================================================= //
// dependencies

// STL
#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <tuple>
#include <any>

//own

// ========================================================================= //
// settings element descriptor

enum class SettingsValueType {String, Integer, Double, Bool, FlagList, StringList, IntegerList, DoubleList};

struct SettingsElementDescriptor {
  std::string       keyword;
  
  SettingsValueType valueType                     = SettingsValueType::Integer;
  std::string       valueDefaultText              = "DEFAULT";
  std::any          valueDefault                  = 0;
  bool              valueDefaultTextCaseSensitive = false;
  
  char              listSeparator                 = ',';
};

// ========================================================================= //
// class

class Settings {
private:
  // ....................................................................... //
  // behaviour objects
  
  static constexpr char invalidFilenameChars[] = "*~[]|:;,<> '\"";
  
  // ....................................................................... //
  // settings file representation
  
  std::string                     source = "default";
  
  char                            commentMarker = '#';
  
  std::vector<std::string>        keywords;
  std::vector<SettingsValueType>  valuesType;
  std::vector<std::string>        valuesText;
  std::vector<std::any>           values;
  std::vector<bool>               valuesCaseSensitive;
  
//   // ....................................................................... //
//   // I/O convenience
//   
//   int warningsIndentFirst   = 3;
//   int warningsIndentHanging = 3;
  
  
  // ----------------------------------------------------------------------- //
  // internal parsing machinery
  
  void getFileContent(std::ifstream & hFile);
  
public:
  // ----------------------------------------------------------------------- //
  // CTor, DTor
  
  Settings() = default;
  ~Settings() = default;
  
  Settings(std::vector<SettingsElementDescriptor> & dsc);
  
  // ----------------------------------------------------------------------- //
  // getters/setters
  
  
  // ----------------------------------------------------------------------- //
  // I/O interface
  
  void loadFile(const std::string & filename);
  void saveFile(const std::string & filename) const;
  
  const std::string to_string() const;
};

#endif
