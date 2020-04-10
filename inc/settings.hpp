/* TODO: File descrption
 * 
 */

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

// ========================================================================= //
// dependencies

// STL
#include <stdexcept>

#include <iostream>
#include <fstream>

#include <type_traits>

#include <string>
#include <vector>
#include <tuple>
#include <any>

//own

// ========================================================================= //
// settings element descriptor

enum class SettingsValueType {String, Integer, Real, Boolean, StringList, IntegerList, RealList};

struct SettingsElementDescriptor {
  std::string       keyword;
  
  std::any          value         = 0;
  SettingsValueType valueType     = SettingsValueType::Integer;
  std::string       valueText     = "DEFAULT";
  bool              caseSensitive = false;
  
  char              listSeparator = ',';
  
  // ....................................................................... //
  // convenience template
  
  template<typename T>
  void set( std::string key,
            const T &   val, 
            std::string def           = "DEFAULT",
            bool        caseSensitive = false
  ) {
    keyword       = key;
    value         = val;
    valueText     = def;
    caseSensitive = caseSensitive;
    
    if      ( std::is_same<bool,                              T>::value ) {valueType = SettingsValueType::Boolean    ;}
    else if ( std::is_integral<                               T>::value ) {valueType = SettingsValueType::Integer    ;}
    else if ( std::is_floating_point<                         T>::value ) {valueType = SettingsValueType::Real       ;}
    else if ( std::is_constructible<std::string,              T>::value ) {valueType = SettingsValueType::String     ;}
    else if ( std::is_constructible<std::vector<std::string>, T>::value ) {valueType = SettingsValueType::StringList ;}
    else if ( std::is_constructible<std::vector<int>,         T>::value ) {valueType = SettingsValueType::IntegerList;}
    else if ( std::is_constructible<std::vector<double>,      T>::value ) {valueType = SettingsValueType::RealList   ;}
    else {throw std::invalid_argument("Type not supported.");}
  }
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
  std::vector<std::any>           values;
  std::vector<SettingsValueType>  valuesType;
  std::vector<std::string>        valuesText;
  std::vector<bool>               valuesCaseSensitive;
  std::vector<char>               valuesListSeparator;
  
  std::vector<bool>               foundInFile;
  
  
  // ----------------------------------------------------------------------- //
  // internal parsing machinery
  
  void interpretValue(std::string & valueText, const int idx);
  
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
