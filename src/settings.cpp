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
// CTor, DTor

Settings::Settings(std::vector<SettingsElementDescriptor> & dsc) {
  // ....................................................................... //
  // sanity checks
  
  if ( dsc.empty() ) {
    throw std::invalid_argument("Passed empty settings element descriptor.");
  }
  
  std::sort(dsc.begin(), dsc.end(), 
            [] (const auto & a, const auto & b) {return a.keyword > b.keyword;}
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
                  [] (const auto & SED) {return SED.valueDefaultText;}
  );
  std::transform( dsc.begin(), dsc.end(),
                  std::back_inserter(values),
                  [] (const auto & SED) {return SED.valueDefault;}
  );
  std::transform( dsc.begin(), dsc.end(),
                  std::back_inserter(valuesCaseSensitive),
                  [] (const auto & SED) {return SED.valueDefaultTextCaseSensitive;}
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

void Settings::getFileContent(std::ifstream & hFile) {
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
  }
  
}

// ========================================================================= //
// I/O interface

void Settings::loadFile(const std::string & filename) {
  std::ifstream hFile(filename);
  if (!hFile.is_open()) {throw std::runtime_error("Could not open file '" + filename + "'\n");}
  
  getFileContent(hFile);
  
  hFile.close();
}
// ......................................................................... //
// void Settings::saveFile(const std::string & filename) const {}
// -----------------------------------------------------------------------.. //
const std::string Settings::to_string() const {
  std::stringstream reVal;
  
  for (auto i = 0u; i < keywords.size(); ++i) {
    reVal << keywords[i] << " = " << "...\n";
  }
  
  return reVal.str();
}
