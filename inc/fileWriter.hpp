/* TODO: File descrption
 * 
 */

#ifndef FILEWRITER_HPP
#define FILEWRITER_HPP

// ========================================================================= //
// dependencies

// STL
#include <stdexcept>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include<iterator>

//own
#include "globals.hpp"

// ========================================================================= //
// template class

template <typename T>
class FileWriter {
private:
  // ....................................................................... //
  // behaviour objects
  
  static constexpr char invalidFilenameChars[] = "*~[]|:;,<> '\"";
  
  char separatorTXT = '\t';
  char separatorGNU = '\t';
  
  std::string filenameBase;
  std::string extTXT    = ".txt";
  std::string extGNU    = ".dat";
  std::string extTEX    = ".tex";
  std::string extSCRIPT = ".gnuscript";
  
  bool autoRunScript = true;
  
  int cols = -1;
  int rows = -1;
  
  // ....................................................................... //
  // data source
  
  typename std::vector<T>::const_iterator itBegin;
  typename std::vector<T>::const_iterator itEnd;
  
  
public:
  // ----------------------------------------------------------------------- //
  // CTor, DTor
  
  FileWriter(const std::vector<T> & data) {
    itBegin = data.begin();
    itEnd   = data.end  ();
  }
  
  // ----------------------------------------------------------------------- //
  // iterators
  
  typename std::vector<T>::const_iterator begin() {return itBegin;}
  typename std::vector<T>::const_iterator end()   {return itEnd;}
  
  // ----------------------------------------------------------------------- //
  // getter / setter
  
  char                getSeparatorTXT () const                  {return separatorTXT;}
  void                setSeparatorTXT (char val)                {separatorTXT = val;}
  // ....................................................................... //
  char                getSeparatorGNU () const                  {return separatorGNU;}
  void                setSeparatorGNU (char val)                {separatorGNU = val;}
  // ....................................................................... //
  const std::string & getFilenameBase () const                  {return filenameBase;}  
  void                setFilenameBase (const std::string & val) {
    if (val.find_first_of(invalidFilenameChars) != std::string::npos) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  filenameBase        : '" + val + "'\n" +
        "  forbidden characters: " + invalidFilenameChars
      );
      
    } else {filenameBase = val;}
  }
  // ....................................................................... //
  const std::string & getExtTXT       () const                  {return extTXT;}
  void                setExtTXT       (const std::string & val) {
    if (val.find_first_of(invalidFilenameChars) != std::string::npos) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  extTXT              : '" + val + "'\n" +
        "  forbidden characters: " + invalidFilenameChars
      );
      
    } else {extTXT = val;}
  }
  // ....................................................................... //
  const std::string & getExtGNU       () const                  {return extGNU;}
  void                setExtGNU       (const std::string & val) {
    if (val.find_first_of(invalidFilenameChars) != std::string::npos) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  extGNU              : '" + val + "'\n" +
        "  forbidden characters: " + invalidFilenameChars
      );
      
    } else {extGNU = val;}
  }
  // ....................................................................... //
  const std::string & getExtTEX       () const                  {return extTEX;}
  void                setExtTEX       (const std::string & val) {
    if (val.find_first_of(invalidFilenameChars) != std::string::npos) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  extTEX              : '" + val + "'\n" +
        "  forbidden characters: " + invalidFilenameChars
      );
      
    } else {extTEX = val;}
  }
  // ....................................................................... //
  const std::string & getExtSCRIPT    () const                  {return extSCRIPT;}
  void                setExtSCRIPT    (const std::string & val) {
    if (val.find_first_of(invalidFilenameChars) != std::string::npos) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  extSCRIPT           : '" + val + "'\n" +
        "  forbidden characters: " + invalidFilenameChars
      );
      
    } else {extSCRIPT = val;}
  }
  // ....................................................................... //
  bool                getAutoRunScript() const                  {return autoRunScript;}
  void                setAutoRunScript(bool val)                {autoRunScript = val;}
  // ....................................................................... //
  int                 getCols         () const                  {return cols;}
  void                setCols         (int val)                 {
    if (val < 0) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  cols: " + val
      );
    }
    cols = val;
  }
  // ....................................................................... //
  int                 getRows         () const                  {return rows;}
  void                setRows         (int val)                 {
    if (val < 0) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  rows: " + val
      );
    }
    rows = val;
  }
  
  // ----------------------------------------------------------------------- //
  // misc
  
  void show() {
    for (auto x : *this) {std::cout << x << std::endl;}
  }
  
  
};

#endif
