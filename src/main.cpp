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
  
  SED.keyword = "N_modes_incoming";
  vSED.push_back(SED);
  vSED.push_back(SED);
  
  globalSettings = Settings(vSED);
  init(argc, argv);
  
  std::cout << globalSettings.to_string();
  
  // ======================================================================= //
  
  std::cout << "main done." << std::endl;
}
