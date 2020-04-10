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

enum class SettingsValueType {String, Integer, Double, Boolean, StringList, IntegerList, DoubleList};

struct SettingsElementDescriptor {
  std::string       keyword;
  
  SettingsValueType valueType              = SettingsValueType::Integer;
  std::string       valueText              = "DEFAULT";
  std::any          value                  = 0;
  bool              valueTextCaseSensitive = false;
  
  char              listSeparator          = ',';
};

// ========================================================================= //
// class

class Settings {
private:
  // ....................................................................... //
  // behaviour objects
  
  static constexpr char invalidFilenameChars[] = "*~[]|:;,<> '\"";
  static const std::vector<std::string> representationsOfTrue;
  
  // ....................................................................... //
  // settings file representation
  
  std::string                     source = "default";
  
  char                            commentMarker = '#';
  
  std::vector<std::string>        keywords;
  std::vector<SettingsValueType>  valuesType;
  std::vector<std::string>        valuesText;
  std::vector<std::any>           values;
  std::vector<bool>               valuesCaseSensitive;
  std::vector<char>               valuesListSeparator;
  
  std::vector<bool>               foundInFile;
  
  
  // ----------------------------------------------------------------------- //
  // internal parsing machinery
  
  bool interpretValue(std::string & valueText, const int idx);
  
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
