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
#include "fileWriter.hpp"

// ========================================================================= //
// proc

void describeSettingsFile() {
  SettingsElementDescriptor SED;
  std::vector<SettingsElementDescriptor> vSED;
  
  SED.set("intval", 0);
  vSED.push_back(SED);
  vSED.push_back(SED);                        // this will trigger a warning: duplicate keyword
  
  SED.set("casetest", 0);
  vSED.push_back(SED);
  
  SED.set("defaultvalue", 0, "Auto");
  vSED.push_back(SED);
  
  SED.set("caseDefault", 0, "Auto", true);    // this will trigger a warning: Invalid data type
  vSED.push_back(SED);
  
  SED.set("real", 0.0);
  vSED.push_back(SED);
  
  SED.keyword = "notInIni";                   // this will trigger a warning:
  vSED.push_back(SED);
  
  SED.set("boolean1", true, "YES", true);
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
  
  SED.set("strlist", std::vector<std::string>({"Bela", "Farin", "Rod"}) );
  vSED.push_back(SED);
  // want to see something ugly?
  // std::cout << SED.value.type().name() << std::endl;
  
  SED.set("intlist", {1, 2, 3} );
  vSED.push_back(SED);
  
  SED.set("dbllist", {1.0, 2.0, 3.0} );
  vSED.push_back(SED);
  
  SED.set("incomplete", 0);                   // this will trigger a warning: invalid type
  vSED.push_back(SED);
  
  globalSettings = Settings(vSED);
  globalSettings.saveFile("defaults.ini");
}

void testSettingsFile () {
  
  std::cout << vector_to_string( globalSettings.getKeywords() ) << std::endl;
  
  std::cout << std::endl;
  std::cout << globalSettings.getIndex("BOOLEAN1") << std::endl;
  std::cout << globalSettings.getIndex("BOOLEAN2") << std::endl;
  std::cout << globalSettings.getIndex("BOOLEAN7") << std::endl;
  
  std::cout << globalSettings.getValue<bool>(0) << std::endl;
  std::cout << globalSettings.getValue<bool>("boolean3") << std::endl;
  std::cout << vector_to_string( globalSettings.getValue< std::vector<double> >("dbllist") ) << std::endl;
  
  std::cout << globalSettings.contains("StrList", "maketxt") << std::endl;
  std::cout << globalSettings.contains("StrList", "MAKETXT") << std::endl;
  std::cout << globalSettings.contains("StrList", "not at all") << std::endl;
}
// ========================================================================= //
// main

int main (int argc, char ** argv) {
  // ======================================================================= //
  // read settings
  
  init(argc, argv);
  
  std::cout << globalSettings.to_string();
  
  // ======================================================================= //
  
  std::cout << "main done." << std::endl;
  std::cout << std::endl;
  
  std::vector<int> v(25);
  for   (auto r = 0; r < 5; ++r) {
    for (auto c = 0; c < 5; ++c) {
      v[5 * r + c] = 3 - r + c;
    }
  }
  
  FileWriter<int> FW(v);
  FW.setCols(5);
  FW.setYLabelValues({"a", "b", "c", "d", "e"});
  // FW.writeTXT1D(1);
  FW.writeTXT2D();
}
