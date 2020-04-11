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
#include <iterator>

#include <cmath>

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
  
  // ....................................................................... //
  // data source
  
  typename std::vector<T>::const_iterator itBegin;
  typename std::vector<T>::const_iterator itEnd;
  
  // ....................................................................... //
  // file format members
  
  char separatorTXT = '\t';
  char separatorGNU = '\t';
  
  std::string filenameBase;
  std::string extTXT    = ".txt";
  std::string extGNU    = ".dat";
  std::string extTEX    = ".tex";
  std::string extPDF    = ".pdf";
  std::string extSCRIPT = ".gnuscript";
  
  bool autoRunScript = true;
  bool standaloneTEX = true;
  
  // ....................................................................... //
  // form parameters
  
  int cols = -1;
  
  std::string title;
  std::string xLabel = "x";
  std::string yLabel = "y";
  
  std::vector<std::string> xLabelValues;
  std::vector<std::string> yLabelValues;
  
  double xRangeMin = 0;
  double xRangeMax = std::nan("inf");
  
  double yRangeMin = 0;
  double yRangeMax = std::nan("inf");
  
  double cRangeMin = 0;
  double cRangeMax = std::nan("inf");
  
  std::string dataColumnFormat1D = "($2 >= 0 ? $2 : 1/0)";
  std::string dataColumnFormat2D = "($3 >= 0 ? $3 : 1/0)";
  
  
public:
  // ----------------------------------------------------------------------- //
  // CTor, DTor
  
  FileWriter() = default;
  FileWriter(const std::vector<T> & data) {setSource(data);}
  
  // ----------------------------------------------------------------------- //
  // iterators and vector interface convenience
  
  typename std::vector<T>::const_iterator begin() {return itBegin;}
  typename std::vector<T>::const_iterator end()   {return itEnd;}
  
  // ....................................................................... //
  
  std::size_t size () const {return std::distance(itBegin, itEnd);}
  bool        empty() const {return itBegin == itEnd;}
  
  // ....................................................................... //
  
  void                setSource(const std::vector<T> & data) {
    itBegin = data.begin();
    itEnd   = data.end  ();
  }
  
  
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
  const std::string & getExtPDF       () const                  {return extPDF;}
  void                setExtPDF       (const std::string & val) {
    if (val.find_first_of(invalidFilenameChars) != std::string::npos) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  extPDF              : '" + val + "'\n" +
        "  forbidden characters: " + invalidFilenameChars
      );
      
    } else {extPDF = val;}
  }
  // ....................................................................... //
  bool                getAutoRunScript() const                  {return autoRunScript;}
  void                setAutoRunScript(bool val)                {autoRunScript = val;}
  // ....................................................................... //
  bool                getStandaloneTEX() const                  {return standaloneTEX;}
  void                setStandaloneTEX(bool val)                {standaloneTEX = val;}
  
  // ....................................................................... //
  
  int                              getCols              () const {return cols;}
  void                             setCols              (int val) {
    if (val < 0) {
      throw std::invalid_argument(
        "Attempted to set invalid filename base in " + __PRETTY_FUNCTION__ + ".\n" +
        "  cols: " + val
      );
    }
    cols = val;
  }
  // ....................................................................... //
  const std::string &              getTitle             () const {return title;}
  void                             setTitle             (const std::string & val);
  // ....................................................................... //
  const std::string &              getXLabel            () const {return xLabel;}
  void                             setXLabel            (const std::string & val);
  // ....................................................................... //
  const std::string &              getYLabel            () const {return yLabel;}
  void                             setYLabel            (const std::string & val);
  // ....................................................................... //
  const std::vector<std::string> & getXLabelValues      () const {return xLabelValues;}
  void                             setXLabelValues      (const std::vector<std::string> & val);
  // ....................................................................... //
  const std::vector<std::string> & getYLabelValues      () const {return yLabelValues;}
  void                             setYLabelValues      (const std::vector<std::string> & val);
  // ....................................................................... //
  double                           getXRangeMin         () const {return xRangeMin;}
  void                             setXRangeMin         (double val) {xRangeMin = val;}
  // ....................................................................... //
  double                           getXRangeMax         () const {return xRangeMax;}
  void                             setXRangeMax         (double val) {xRangeMax = val;}
  // ....................................................................... //
  double                           getYRangeMin         () const {return yRangeMin;}
  void                             setYRangeMin         (double val) {yRangeMin = val;}
  // ....................................................................... //
  double                           getYRangeMax         () const {return yRangeMax;}
  void                             setYRangeMax         (double val) {yRangeMax = val;}
  // ....................................................................... //
  double                           getCRangeMin         () const {return cRangeMin;}
  void                             setCRangeMin         (double val) {cRangeMin = val;}
  // ....................................................................... //
  double                           getCRangeMax         () const {return cRangeMax;}
  void                             setCRangeMax         (double val) {cRangeMax = val;}
  // ....................................................................... //
  const std::string &              getDataColumnFormat1D() const {return dataColumnFormat1D;}
  void                             setDataColumnFormat1D(const std::string & val) {dataColumnFormat1D = val;}
  // ....................................................................... //
  const std::string &              getDataColumnFormat2D() const {return dataColumnFormat2D;}
  void                             setDataColumnFormat2D(const std::string & val) {dataColumnFormat2D = val;}
  // ....................................................................... //
  
  const std::string   getFilenameTXT    () const {return filenameBase + extTXT;}
  const std::string   getFilenameGNU    () const {return filenameBase + extGNU;}
  const std::string   getFilenameTEX    () const {return filenameBase + extTEX;}
  const std::string   getFilenameSCRIPT () const {return filenameBase + extSCRIPT;}
  const std::string   getFilenamePDF    () const {return filenameBase + extPDF;}
  
  // ----------------------------------------------------------------------- //
  // writers
  
  void writeTXT1D () const;
  void writeTXT2D () const;
  
  void writeScript1D () const;
  void writeScript2D () const;
  
  void writeMultiScript1D(const std::vector<const std::string> & GNUfiles) const;
  void writeMultiScript2D(const std::vector<const std::string> & GNUfiles) const;
  
  // ----------------------------------------------------------------------- //
  // misc
  
  void show() {
    for (auto x : *this) {std::cout << x << std::endl;}
  }
  
  
};

#endif
