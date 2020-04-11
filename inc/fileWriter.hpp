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
  using namespace std::string_literals;
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
  
  std::string filenameBase = "./FileWriterOutput";
  std::string extTXT       = ".txt";
  std::string extGNU       = ".dat";
  std::string extTEX       = ".tex";
  std::string extPDF       = ".pdf";
  std::string extSCRIPT    = ".gnuscript";
  
  std::string fileContentDescription = "FileWriter Output";
  
  bool autoRunScript = true;
  bool standaloneTEX = true;
  
  // ....................................................................... //
  // form parameters
  
  int cols = 1;
  
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
        "Attempted to set invalid filename base in "s + __PRETTY_FUNCTION__ + ".\n" +
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
        "Attempted to set invalid filename in "s + __PRETTY_FUNCTION__ + ".\n" +
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
        "Attempted to set invalid filename in "s + __PRETTY_FUNCTION__ + ".\n" +
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
        "Attempted to set invalid filename in "s + __PRETTY_FUNCTION__ + ".\n" +
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
        "Attempted to set invalid filename in "s + __PRETTY_FUNCTION__ + ".\n" +
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
        "Attempted to set invalid filename in "s + __PRETTY_FUNCTION__ + ".\n" +
        "  extPDF              : '" + val + "'\n" +
        "  forbidden characters: " + invalidFilenameChars
      );
      
    } else {extPDF = val;}
  }
  // ....................................................................... //
  const std::string & getFileContentDescription() const {return fileContentDescription;}
  void                setFileContentDescription(std::string & val) {fileContentDescription = val;}
  // ....................................................................... //
  bool                getAutoRunScript() const                  {return autoRunScript;}
  void                setAutoRunScript(bool val)                {autoRunScript = val;}
  // ....................................................................... //
  bool                getStandaloneTEX() const                  {return standaloneTEX;}
  void                setStandaloneTEX(bool val)                {standaloneTEX = val;}
  
  // ....................................................................... //
  
  int                              getCols              () const {return cols;}
  void                             setCols              (int val) {
    if (val < 1) {
      throw std::invalid_argument(
        "Attempted to set invalid column in "s + __PRETTY_FUNCTION__ + ".\n" +
        "  cols: " + std::to_string(val)
      );
    }
    cols = val;
  }
  // ....................................................................... //
  const std::string &              getTitle             () const {return title;}
  void                             setTitle             (const std::string & val) {title = val;}
  // ....................................................................... //
  const std::string &              getXLabel            () const {return xLabel;}
  void                             setXLabel            (const std::string & val) {xLabel = val;}
  // ....................................................................... //
  const std::string &              getYLabel            () const {return yLabel;}
  void                             setYLabel            (const std::string & val) {yLabel = val;}
  // ....................................................................... //
  const std::vector<std::string> & getXLabelValues      () const {return xLabelValues;}
  void                             setXLabelValues      (const std::vector<std::string> &  val) {xLabelValues = val;}
  void                             setXLabelValues      (const std::vector<std::string> && val) {xLabelValues = val;}
  // ....................................................................... //
  const std::vector<std::string> & getYLabelValues      () const {return yLabelValues;}
  void                             setYLabelValues      (const std::vector<std::string> &  val) {yLabelValues = val;}
  void                             setYLabelValues      (const std::vector<std::string> && val) {yLabelValues = val;}
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
  
  void writeTXT1D (const int colID = 0) const {
    if (colID < 0) {
      throw std::invalid_argument(
        "Attempted to plot invalid column in "s + __PRETTY_FUNCTION__ + ".\n" +
        "  column: " + std::to_string(colID)
      );
    }
    
    auto hFile = openThrow(filenameBase + extTXT);
    
    hFile << generateFileComments(fileContentDescription);
    
    
    hFile << xLabel;
    hFile << separatorTXT;
    hFile << yLabel;
    hFile << std::endl;
    
    auto ID = 0u, row = 0u, col = 0u;
    
    for (const auto & datapoint : *const_cast<FileWriter*>(this) ) {
      if ( col == static_cast<unsigned>(colID) ) {
        hFile << ( row >= xLabelValues.size() ? std::to_string(row) : xLabelValues[row] );
        hFile << separatorTXT;
        hFile << datapoint;
        hFile << std::endl;
      }
      
      ++ID;
      row = ID / cols;
      col = ID % cols;
    }
    
    hFile.close();
  }
  // ....................................................................... //
  void writeTXT2D () const {
    auto hFile = openThrow(filenameBase + extTXT);
    
    hFile << generateFileComments(fileContentDescription);
    
    hFile << yLabel << "\\"  << xLabel;
    hFile << separatorTXT;
    if ( xLabelValues.size() >= static_cast<unsigned>(cols) ) {
      for (auto i = 0; i < cols; ++i) {
        hFile << xLabelValues[i];
        hFile << separatorTXT;
      }
      
    } else {
      for (auto i = 0; i < cols; ++i) {
        hFile << "column " << i;
        hFile << separatorTXT;
      }
    }
    hFile << std::endl;
    
    auto ID = 0u, row = 0u, col = 0u;
    
    for (const auto & datapoint : *const_cast<FileWriter*>(this) ) {
      if (col == 0) {
        hFile << ( row >= yLabelValues.size() ? std::to_string(row) : yLabelValues[row] );
        hFile << separatorTXT;
      }
      
      hFile << datapoint;
      hFile << separatorTXT;
      
      ++ID;
      row = ID / cols;
      col = ID % cols;
      
      if (col == 0) {hFile << std::endl;}
    }
    
    hFile.close();
  }
  
  // ....................................................................... //
  
  void writeGNU1D (const int colID = 0) const {
    if (colID < 0) {
      throw std::invalid_argument(
        "Attempted to plot invalid column in "s + __PRETTY_FUNCTION__ + ".\n" +
        "  column: " + std::to_string(colID)
      );
    }
    
    auto hFile = openThrow(filenameBase + extGNU);
    
    hFile << generateFileComments(fileContentDescription);
    
    hFile << "# ";
    hFile << xLabel;
    hFile << separatorTXT;
    hFile << yLabel;
    hFile << std::endl;
    
    auto ID = 0u, row = 0u, col = 0u;
    
    for (const auto & datapoint : *const_cast<FileWriter*>(this) ) {
      if ( col == static_cast<unsigned>(colID) ) {
        hFile << ( row >= xLabelValues.size() ? std::to_string(row) : xLabelValues[row] );
        hFile << separatorTXT;
        hFile << datapoint;
        hFile << std::endl;
      }
      
      ++ID;
      row = ID / cols;
      col = ID % cols;
    }
    
    hFile.close();
  }
  // ....................................................................... //
  void writeGNU2D () const {
    auto hFile = openThrow(filenameBase + extGNU);
    
    hFile << generateFileComments(fileContentDescription);
    
    hFile << "# ";
    hFile << xLabel;
    hFile << separatorTXT;
    hFile << yLabel;
    hFile << separatorTXT;
    hFile << "datapoint";
    hFile << std::endl;
    
    auto ID = 0u, row = 0u, col = 0u;
    
    for (const auto & datapoint : *const_cast<FileWriter*>(this) ) {
      hFile << ( col >= xLabelValues.size() ? "column_" + std::to_string(col) : xLabelValues[col] );
      hFile << separatorTXT;
      hFile << ( row >= yLabelValues.size() ? "row_"    + std::to_string(row) : yLabelValues[row] );
      hFile << separatorTXT;
      hFile << datapoint;
      hFile << std::endl;
      
      ++ID;
      row = ID / cols;
      col = ID % cols;
      if (!col) {hFile << std::endl;}   // graphically offset new lines in gnu data files.
    }
    
    hFile.close();
  }
  
  // ....................................................................... //
  
  void writeScript1D () const;
  void writeScript2D () const;
  
  void writeMultiScript1D(const std::vector<const std::string> & GNUfiles) const;
  void writeMultiScript2D(const std::vector<const std::string> & GNUfiles) const;
  
  // ----------------------------------------------------------------------- //
  // misc
  
  std::string to_string() const;
};

#endif
