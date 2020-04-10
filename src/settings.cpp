 // ========================================================================= //
// dependencies

// STL
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <any>

#include <algorithm>
#include <numeric>

// own
#include "settings.hpp"
#include "globals.hpp"

// ========================================================================= //
// static members

const std::vector<std::string> Settings::representationsOfTrue = {"TRUE", "YES"};

// ========================================================================= //
// CTor, DTor

Settings::Settings(std::vector<SettingsElementDescriptor> & dsc) {
  // ....................................................................... //
  // sanity checks
  
  if ( dsc.empty() ) {
    throw std::invalid_argument("Passed empty settings element descriptor.");
  }
  
  std::sort(dsc.begin(), dsc.end(), 
            [] (const auto & a, const auto & b) {return a.keyword < b.keyword;}
  );
  
  auto last = std::unique(dsc.begin(), dsc.end(),
                          [] (const auto & a, const auto & b) {return a.keyword == b.keyword;}
  );
  if (last != dsc.end()) {
    utterWarning ("Duplicate instantiation of at least one keyword!\nIgnoring duplicate instances.");
    dsc.erase(last, dsc.end()); 
  }
  
  
  // ....................................................................... //
  // copy descriptor
  
  foundInFile = std::vector<bool>( dsc.size(), false );
  
  std::transform( dsc.begin(), dsc.end(),
                  std::back_inserter(keywords),
                  [] (const auto & SED) {return SED.keyword;}
  );
  std::transform( dsc.begin(), dsc.end(),
                  std::back_inserter(valuesType),
                  [] (const auto & SED) {return SED.valueType;}
  );
  std::transform( dsc.begin(), dsc.end(),
                  std::back_inserter(valuesText),
                  [] (const auto & SED) {return SED.valueText;}
  );
  std::transform( dsc.begin(), dsc.end(),
                  std::back_inserter(values),
                  [] (const auto & SED) {return SED.value;}
  );
  std::transform( dsc.begin(), dsc.end(),
                  std::back_inserter(valuesCaseSensitive),
                  [] (const auto & SED) {return SED.valueTextCaseSensitive;}
  );
  std::transform( dsc.begin(), dsc.end(),
                  std::back_inserter(valuesListSeparator),
                  [] (const auto & SED) {return SED.listSeparator;}
  );
  
  // ....................................................................... //
  // apply case sensitivity
  
  std::transform( keywords.begin(), keywords.end(),
                  keywords.begin(),
                  [] (const auto & keyword) {return uppercase(keyword);}
  );
  std::transform( valuesText.begin(), valuesText.end(),
                  valuesCaseSensitive.begin(),
                  valuesText.begin(),
                  [] (const auto & valueText, const auto & caseSensitive) {return caseSensitive ? valueText: uppercase(valueText);}
  );
}

// ========================================================================= //
// internal parsing machinery

bool Settings::interpretValue(std::string & valueText, const int idx) {
  std::vector<std::string> strL;
  
  switch (valuesType[idx]) {
    case SettingsValueType::String     :
      values[idx] = valueText;
      return true;
      
    case SettingsValueType::Integer    : 
      try {values[idx] = std::stoi(valueText); return true;} 
      catch (const std::exception& e) {
        utterWarning("Invalid data type in keyword '" + keywords[idx] + "', expected integer.\nReverting to Default (" + valuesText[idx] + ")");
      }
      return false;
      
    case SettingsValueType::Double     :
      try {values[idx] = std::stod(valueText); return true;} 
      catch (const std::exception& e) {
        utterWarning("Invalid data type in keyword '" + keywords[idx] + "', expected double.\nReverting to Default (" + valuesText[idx] + ")");
      }
      
    case SettingsValueType::Boolean    :
      values[idx] = std::find(representationsOfTrue.begin(), representationsOfTrue.end(), 
                              uppercase(valueText)
                              ) != representationsOfTrue.end();
      return true;
      
    case SettingsValueType::StringList :
      strL = splitString( valueText, valuesListSeparator[idx] );
      std::transform( strL.begin(), strL.end(),
                      strL.begin(),
                      [] (const auto & s) {return trim_copy(s);}
      );
      values[idx] = strL;
      valueText = vector_to_string(std::any_cast< std::vector<std::string> >(values[idx]), false);     //
      return true;
      
    case SettingsValueType::IntegerList:
      values[idx] = 0;
      return true;
      
    case SettingsValueType::DoubleList :
      values[idx] = 0;
      return true;
      
    default:
      throw( std::invalid_argument("value type #" + std::to_string( static_cast<int>(valuesType[idx]) )+ " not supported.") );
  }
  return 0;
}

// ========================================================================= //
// I/O interface

void Settings::loadFile(const std::string & filename) {
  std::ifstream hFile(filename);
  if (!hFile.is_open()) {throw std::runtime_error("Could not open file '" + filename + "'\n");}
  
  
  std::string key, value;
  int separationIdx, lineIdx = 0;
  
  for (std::string line; std::getline(hFile, line); ) {
    ++lineIdx;
    
    // prepare line: trim and split in key/value.
    trim(line);                                   // i.e. remove whitespaces, tabs, ... from front and end
    if (line.empty()  )           {continue;}     // and skip empty lines ...
    if (line[0] == commentMarker) {continue;}     // ... as well as comments
    
    separationIdx = line.find('=');
    
    key   = line.substr(0, separationIdx);
    value = line.substr(separationIdx + 1);
    
    to_uppercase(key);
    
    trim(key);
    trim(value);
    
    
    
    std::cout << "'" << key << "', '" << value << "'" << std::endl;
    
    
    
    auto posIt = std::find(keywords.begin(), keywords.end(), key);
    if (posIt == keywords.end()) {
      utterWarning("keyword '" + key + "' not accepted\n(Ignoring keyword))");
      
    } else {
      auto idx = std::distance(keywords.begin(), posIt);
      foundInFile[idx] = true;
      
      if ( !valuesCaseSensitive[idx] ) {to_uppercase(value);}
      if ( value != valuesText[idx]  ) {                            // check whethter default tag was read
        if (interpretValue(value, idx)) {                           // if interpretation successful: update text representation
          valuesText[idx] = value;                                  // otherwise, implicitly keep default.
        }
        
      }
    }
    
    std::cout << std::endl;
  }
  
  hFile.close();
}
// ......................................................................... //
// void Settings::saveFile(const std::string & filename) const {}
// -----------------------------------------------------------------------.. //
const std::string Settings::to_string() const {
  std::stringstream reVal;
  
  reVal << std::boolalpha;
  
  for (auto i = 0u; i < keywords.size(); ++i) {
    reVal << keywords[i] << " (found in file: " << foundInFile[i] << ") = " << valuesText[i] << "\n";
  }
  
  return reVal.str();
}
