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
  
  std::string invalidFilenameChars = "*~|:;<> '\"";
  
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
  
  std::string title  = "title";
  std::string xLabel = "x";
  std::string yLabel = "y";
  
  std::vector<std::string> xLabelValues;
  std::vector<std::string> yLabelValues;
  std::vector<std::string> cLabelValues;
  
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
  
  const std::string & getInvalidFilenameChars () const                   {return invalidFilenameChars;}
  void                setInvalidFilenameChars  (const std::string & val) {invalidFilenameChars = val;}
  // ....................................................................... //
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
        std::string("Attempted to set invalid filename base in ") + __PRETTY_FUNCTION__ + ".\n" +
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
        std::string("Attempted to set invalid filename in ") + __PRETTY_FUNCTION__ + ".\n" +
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
        std::string("Attempted to set invalid filename in ") + __PRETTY_FUNCTION__ + ".\n" +
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
        std::string("Attempted to set invalid filename in ") + __PRETTY_FUNCTION__ + ".\n" +
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
        std::string("Attempted to set invalid filename in ") + __PRETTY_FUNCTION__ + ".\n" +
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
        std::string("Attempted to set invalid filename in ") + __PRETTY_FUNCTION__ + ".\n" +
        "  extPDF              : '" + val + "'\n" +
        "  forbidden characters: " + invalidFilenameChars
      );
      
    } else {extPDF = val;}
  }
  // ....................................................................... //
  const std::string & getFileContentDescription() const {return fileContentDescription;}
  void                setFileContentDescription(const std::string & val) {fileContentDescription = val;}
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
        std::string("Attempted to set invalid column in ") + __PRETTY_FUNCTION__ + ".\n" +
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
  const std::vector<std::string> & getCLabelValues      () const {return cLabelValues;}
  void                             setCLabelValues      (const std::vector<std::string> &  val) {cLabelValues = val;}
  void                             setCLabelValues      (const std::vector<std::string> && val) {cLabelValues = val;}
  void                           resetCLabelValues      () {cLabelValues.clear();}
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
        std::string("Attempted to plot invalid column in ") + __PRETTY_FUNCTION__ + ".\n" +
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
        std::string("Attempted to plot invalid column in ") + __PRETTY_FUNCTION__ + ".\n" +
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
  
  void writeTEX1D ([[maybe_unused]] const int colID = 0) const {std::cout << "TEX writer not yet implemented" << std::endl;}
  // ....................................................................... //
  void writeTEX2D () const {std::cout << "TEX writer not yet implemented" << std::endl;}
  
  // ....................................................................... //
  
  void writeScript1DHead (std::ostream & hFile) const {
    hFile << "# =========================================================================== #" << std::endl;
    hFile << "# output format"                                                                 << std::endl;
    hFile << "set terminal postscript enhanced"                                                << std::endl;
    hFile << "set terminal pdf"                                                                << std::endl;
    hFile << "set output '" << filenameBase << extPDF << "'"                                   << std::endl;
    hFile                                                                                      << std::endl;
    hFile << "# =========================================================================== #" << std::endl;
    hFile << "# plot dimensions"                                                               << std::endl;
    hFile << "set xrange  [" 
          << (std::isnan(xRangeMin) ? std::string("*") : std::to_string(xRangeMin))
          << ":"
          << (std::isnan(xRangeMax) ? std::string("*") : std::to_string(xRangeMax))
          << "]"                                                                               << std::endl;
    hFile << "set yrange  [" 
          << (std::isnan(yRangeMin) ? std::string("*") : std::to_string(yRangeMin))
          << ":"
          << (std::isnan(yRangeMax) ? std::string("*") : std::to_string(yRangeMax))
          << "]"                                                                               << std::endl;
    hFile                                                                                      << std::endl;
    hFile << "# =========================================================================== #" << std::endl;
    hFile << "# plot format"                                                                   << std::endl;
    hFile << "set key off"                                                                     << std::endl;
    hFile << "set xlabel \"" << xLabel << "\""                                                 << std::endl;
    hFile << "set ylabel \"" << yLabel << "\" rotate parallel"                                 << std::endl;
    hFile                                                                                      << std::endl;
    if ( cLabelValues.size() ) {
      hFile << "set ytics (";
      int cLabelCounter = 0;
      std::for_each(cLabelValues.begin(), cLabelValues.end(),
        [&cLabelCounter, &hFile] (const auto & lblText) {
          hFile << "\"" << lblText << "\" " << cLabelCounter << ", ";
          ++cLabelCounter;
        }
      );
      hFile.seekp(-2, std::ios_base::cur);
      hFile << ")" << std::endl;
    }
    hFile                                                                                      << std::endl;
    hFile << "# =========================================================================== #" << std::endl;
    hFile << "# make plots"                                                                    << std::endl;
    
    if (hFile.bad()) {throw std::invalid_argument("File stream is not ready");}
  };
  // ....................................................................... //
  void writeScript2DHead (std::ostream & hFile) const {
    hFile << "# =========================================================================== #" << std::endl;
    hFile << "# output format"                                                                 << std::endl;
    hFile << "set terminal postscript enhanced"                                                << std::endl;
    hFile << "set terminal pdf"                                                                << std::endl;
    hFile << "set output '" << filenameBase << extPDF << "'"                                   << std::endl;
    hFile                                                                                      << std::endl;
    hFile << "# =========================================================================== #" << std::endl;
    hFile << "# plot dimensions"                                                               << std::endl;
    hFile << "set xrange  [" 
          << (std::isnan(xRangeMin) ? std::string("*") : std::to_string(xRangeMin))
          << ":"
          << (std::isnan(xRangeMax) ? std::string("*") : std::to_string(xRangeMax))
          << "]"                                                                               << std::endl;
    hFile << "set yrange  [" 
          << (std::isnan(yRangeMin) ? std::string("*") : std::to_string(yRangeMin))
          << ":"
          << (std::isnan(yRangeMax) ? std::string("*") : std::to_string(yRangeMax))
          << "]"                                                                               << std::endl;
    hFile << "set cbrange [" 
          << (std::isnan(cRangeMin) ? std::string("*") : std::to_string(cRangeMin))
          << ":"
          << (std::isnan(cRangeMax) ? std::string("*") : std::to_string(cRangeMax))
          << "]"                                                                               << std::endl;
    hFile                                                                                      << std::endl;
    hFile << "# =========================================================================== #" << std::endl;
    hFile << "# plot format"                                                                   << std::endl;
    hFile << "set palette defined ( 0 \"#000090\",\\"                                          << std::endl;
    hFile << "                      1 \"#000fff\",\\"                                          << std::endl;
    hFile << "                      2 \"#0090ff\",\\"                                          << std::endl;
    hFile << "                      3 \"#0fffee\",\\"                                          << std::endl;
    hFile << "                      4 \"#90ff70\",\\"                                          << std::endl;
    hFile << "                      5 \"#ffee00\",\\"                                          << std::endl;
    hFile << "                      6 \"#ff7000\",\\"                                          << std::endl;
    hFile << "                      7 \"#ee0000\",\\"                                          << std::endl;
    hFile << "                      8 \"#7f0000\")"                                            << std::endl;
    hFile << "set key off"                                                                     << std::endl;
    hFile << "set xlabel \"" << xLabel << "\""                                                 << std::endl;
    hFile << "set ylabel \"" << yLabel << "\" rotate parallel"                                 << std::endl;
    hFile                                                                                      << std::endl;
    if ( cLabelValues.size() ) {
      hFile << "set cbtics (";
      int cLabelCounter = 0;
      std::for_each(cLabelValues.begin(), cLabelValues.end(),
        [&cLabelCounter, &hFile] (const auto & lblText) {
          hFile << "\"" << lblText << "\" " << cLabelCounter << ", ";
          ++cLabelCounter;
        }
      );
      hFile.seekp(-2, std::ios_base::cur);
      hFile << ")" << std::endl;
    }
    hFile                                                                                      << std::endl;
    hFile << "# =========================================================================== #" << std::endl;
    hFile << "# make plots"                                                                    << std::endl;
    
    if (hFile.bad()) {throw std::invalid_argument("File stream is not ready");}
  };
  
  // ....................................................................... //
  
  void writeScript1D () const {
    auto hFile = openThrow(filenameBase + extSCRIPT);
    
    hFile << generateFileComments(fileContentDescription);
    
    writeScript1DHead(hFile);
    
    hFile << "set title \"" << title << "\" offset 0, -1" << std::endl;
    hFile << "plot '" << filenameBase << extGNU << "' u 1:" << dataColumnFormat1D << " with lines" << std::endl;
    
    hFile.close();
    if (autoRunScript) {runScript();}
  }
  // ....................................................................... //
  void writeScript2D () const {
    auto hFile = openThrow(filenameBase + extSCRIPT);
    
    hFile << generateFileComments(fileContentDescription);
    
    writeScript2DHead(hFile);
    
    hFile << "set title \"" << title << "\" offset 0, -1" << std::endl;
    hFile << "plot '" << filenameBase << extGNU << "' u 1:2:" << dataColumnFormat2D << " with image pixels" << std::endl;
    
    hFile.close();
    if (autoRunScript) {runScript();}
  }
  
  // ....................................................................... //
  
  void writeMultiScript1D(const std::vector<std::string> & files,
                          const std::vector<std::string> & titles
  ) const {
    auto hFile = openThrow(filenameBase + extSCRIPT);
    
    hFile << generateFileComments(fileContentDescription);
    
    writeScript1DHead(hFile);
    
    for (auto i = 0u; i < files.size(); ++i) {
      hFile << "set title \"" << (i < titles.size() ? titles[i] : files[i]) << "\" offset 0, -1" << std::endl;
      hFile << "plot '" << files[i] << "' u 1:" << dataColumnFormat1D << " with lines" << std::endl;
    }
    
    hFile.close();
    if (autoRunScript) {runScript();}
  }
  // ....................................................................... //
  void writeMultiScript2D(const std::vector<std::string> & files,
                          const std::vector<std::string> & titles
  ) const {
    auto hFile = openThrow(filenameBase + extSCRIPT);
    
    hFile << generateFileComments(fileContentDescription);
    
    writeScript2DHead(hFile);
    
    for (auto i = 0u; i < files.size(); ++i) {
      hFile << "set title \"" << (i < titles.size() ? titles[i] : files[i]) << "\" offset 0, -1" << std::endl;
      hFile << "plot '" << files[i] << "' u 1:2:" << dataColumnFormat2D << " with image pixels" << std::endl;
    }
    
    hFile.close();
    if (autoRunScript) {runScript();}
  }
  
  // ....................................................................... //
  
  void writeMock () const {
    auto hFile = openThrow(filenameBase + extTXT);
    hFile << generateFileComments(fileContentDescription);
    hFile.close();
  }
  
  // ....................................................................... //
  
  void runScript() const {
    std::cout << "About to run gnuplot scripts..." << std::endl;
    if (std::system(  (std::string("gnuplot ") + filenameBase + extSCRIPT).data()  )) {
      utterWarning("gnuplot did not succeed.");
    }
    std::cout << "done." << std::endl;
  }
  // ----------------------------------------------------------------------- //
  // misc
  
  std::string to_string() const {
    std::string reVal = "File Writer object\n";
    
    reVal += std::string("\thas data points: ") + (empty() ? "no" : "yes") + "\n";
    reVal += std::string("\t#data points:    ") + std::to_string(size()) + "\n";
    reVal += std::string("\t#columns:        ") + std::to_string(cols) + "\n";
    reVal += std::string("\ttitle:           ") + title + "\n";
    reVal += std::string("\tx-label          ") + xLabel + "\n";
    reVal += std::string("\ty-label          ") + yLabel + "\n";
    
    return reVal;
  }
};

#endif
