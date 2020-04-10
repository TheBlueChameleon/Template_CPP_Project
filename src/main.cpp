/* TODO: File descrption
 * 
 */

// ========================================================================= //
// dependencies

// STL
#include <iostream>
#include <iomanip>

#include <vector>
#include <string>

// own
#include "globals.hpp"

// ========================================================================= //
// proc

int main (int argc, char ** argv) {
  // ======================================================================= //
  // read settings
  
  SettingsElementDescriptor SED;
  std::vector<SettingsElementDescriptor> vSED;
  
  SED.keyword = "intval";
  vSED.push_back(SED);
  vSED.push_back(SED);      // this will trigger a warning: duplicate keyword
  
  SED.keyword = "casetest";
  vSED.push_back(SED);
  
  SED.keyword = "defaultvalue";
  SED.valueText = "Auto";
  vSED.push_back(SED);
  
  SED.keyword = "caseDefault";
  SED.valueTextCaseSensitive = true;     // this will trigger a warning: Invalid data type
  vSED.push_back(SED);
  
  SED.keyword = "double";
  SED.valueType = SettingsValueType::Double;
  vSED.push_back(SED);
  
  SED.keyword = "notInIni";             // this will trigger a warning:
  vSED.push_back(SED);
  
  SED.keyword = "boolean1";
  SED.valueType = SettingsValueType::Boolean;
  vSED.push_back(SED);
  SED.keyword = "boolean2";
  vSED.push_back(SED);
  SED.keyword = "boolean3";
  vSED.push_back(SED);
  SED.keyword = "boolean4";
  vSED.push_back(SED);
  SED.keyword = "boolean5";
  vSED.push_back(SED);
  SED.keyword = "boolean6";
  vSED.push_back(SED);
  
  SED.keyword = "strlist";
  SED.valueType = SettingsValueType::StringList;
  vSED.push_back(SED);
  
  SED.keyword = "intlist";
  SED.valueType = SettingsValueType::StringList;
  vSED.push_back(SED);
  
  SED.keyword = "dbllist";
  SED.valueType = SettingsValueType::StringList;
  vSED.push_back(SED);
  
  SED.keyword = "incomplete";           // this will trigger a warning: invalid type
  SED.valueType = SettingsValueType::Integer;
  vSED.push_back(SED);
  
  globalSettings = Settings(vSED);
  init(argc, argv);
  
  std::cout << globalSettings.to_string();
  
  // ======================================================================= //
  
  std::cout << "main done." << std::endl;
}
