#include<stdio.h>
#include<sstream>
#include <array>
using namespace std;
#include <iterator>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#ifdef TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#include <clocale>
#ifndef TEXTTABLE_USE_EN_US_UTF8
#define TEXTTABLE_USE_EN_US_UTF8
#endif
#endif

class TextTable {
public:
  enum class Alignment { LEFT, RIGHT };
  typedef std::vector<std::string> Row;
  TextTable()
      : _horizontal('-'), _vertical('|'), _corner('+'), _has_ruler(true) {}

  TextTable(char horizontal, char vertical, char corner)
      : _horizontal(horizontal), _vertical(vertical), _corner(corner),
        _has_ruler(true) {}

  explicit TextTable(char vertical)
      : _horizontal('\0'), _vertical(vertical), _corner('\0'),
        _has_ruler(false) {}

  void setAlignment(unsigned i, Alignment alignment) {
    _alignment[i] = alignment;
  }

  Alignment alignment(unsigned i) const { return _alignment[i]; }

  char vertical() const { return _vertical; }

  char horizontal() const { return _horizontal; }

  void add(const std::string& content) { _current.push_back(content); }

  void endOfRow() {
    _rows.push_back(_current);
    _current.assign(0, "");
  }

  template <typename Iterator> void addRow(Iterator begin, Iterator end) {
    for (auto i = begin; i != end; ++i) {
      add(*i);
    }
    endOfRow();
  }

  template <typename Container> void addRow(const Container& container) {
    addRow(container.begin(), container.end());
  }

  const std::vector<Row>& rows() const { return _rows; }

  void setup() const {
    determineWidths();
    setupAlignment();
  }

  std::string ruler() const {
    std::string result;
    result += _corner;
    for (auto width = _width.begin(); width != _width.end(); ++width) {
      result += repeat(*width, _horizontal);
      result += _corner;
    }

    return result;
  }

  int width(unsigned i) const { return _width[i]; }

  bool has_ruler() const { return _has_ruler; }

  int correctDistance(const std::string& string_to_correct) const {
    return static_cast<int>(string_to_correct.size()) -
           static_cast<int>(glyphLength(string_to_correct));
  };

private:
  const char _horizontal;
  const char _vertical;
  const char _corner;
  const bool _has_ruler;
  Row _current;
  std::vector<Row> _rows;
  std::vector<unsigned> mutable _width;
  std::vector<unsigned> mutable _utf8width;
  std::map<unsigned, Alignment> mutable _alignment;

  static std::string repeat(unsigned times, char c) {
    std::string result;
    for (; times > 0; --times)
      result += c;

    return result;
  }

  unsigned columns() const { return _rows[0].size(); }

  unsigned glyphLength(const std::string& s) const {
    unsigned int _byteLength = s.length();
#ifdef TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#ifdef TEXTTABLE_USE_EN_US_UTF8
    std::setlocale(LC_ALL, "en_US.utf8");
#else
#error You need to specify the encoding if the TextTable library uses multybyte string encoding!
#endif
    unsigned int u = 0;
    const char *c_str = s.c_str();
    unsigned _glyphLength = 0;
    while (u < _byteLength) {
      u += std::mblen(&c_str[u], _byteLength - u);
      _glyphLength += 1;
    }
    return _glyphLength;
#else
    return _byteLength;
#endif
  }

  void determineWidths() const {
    if (_rows.empty()) {
      return;
    }
    _width.assign(columns(), 0);
    _utf8width.assign(columns(), 0);
    for (auto rowIterator = _rows.begin(); rowIterator != _rows.end();
         ++rowIterator) {
      Row const &row = *rowIterator;
      for (unsigned i = 0; i < row.size(); ++i) {
        _width[i] =
            _width[i] > glyphLength(row[i]) ? _width[i] : glyphLength(row[i]);
      }
    }
  }

  void setupAlignment() const {
    if (_rows.empty()) {
      return;
    }
    for (unsigned i = 0; i < columns(); ++i) {
      if (_alignment.find(i) == _alignment.end()) {
        _alignment[i] = Alignment::LEFT;
      }
    }
  }
};

inline std::ostream &operator<<(std::ostream &stream, const TextTable& table) {
  if (table.rows().empty()) {
    return stream;
  }
  table.setup();
  if (table.has_ruler()) {
    stream << table.ruler() << "\n";
  }
  for (auto rowIterator = table.rows().begin();
       rowIterator != table.rows().end(); ++rowIterator) {
    TextTable::Row const &row = *rowIterator;
    stream << table.vertical();
    for (unsigned i = 0; i < row.size(); ++i) {
      auto alignment = table.alignment(i) == TextTable::Alignment::LEFT
                           ? std::left
                           : std::right;
      // std::setw( width ) works as follows: a string which goes in the stream
      // with byte length (!) l is filled with n spaces so that l+n=width. For a
      // utf8 encoded string the glyph length g might be smaller than l. We need
      // n spaces so that g+n=width which is equivalent to g+n+l-l=width ==> l+n
      // = width+l-g l-g (that means glyph length minus byte length) has to be
      // added to the width argument. l-g is computed by correctDistance.
      stream << std::setw(table.width(i) + table.correctDistance(row[i]))
             << alignment << row[i];
      stream << table.vertical();
    }
    stream << "\n";
    if (table.has_ruler()) {
      stream << table.ruler() << "\n";
    }
  }

  return stream;
}

struct Mahasiswa {
   char nim[20];
   char nama[30];
   int nAbsensi; // n stands for nilai
   int nTugas;
   int nUTS;
   int nUAS;
   float hasil;
} mhs;

struct jumlahData {
    int jData; // it mean jumlah datanya
} jmlh;

std::vector<Mahasiswa> arr;

int main() {
    cout<<"Masukkan data yang akan di input : ";
    cin>>jmlh.jData;
    cout<<endl;
    
    int i;
    
    for(i = 0; i < jmlh.jData; i++) {
        cout<<"Input data ke "<<i + 1<<endl;
        cout<<"=========="<<endl;
        cout<<"Masukkan NIM           : "; cin>>mhs.nim;
        cout<<"Masukkan Nama          : "; cin>>mhs.nama;
        cout<<"Masukkan Nilai Absensi : "; cin>>mhs.nAbsensi;
        cout<<"Masukkan Nilai Tugas   : "; cin>>mhs.nTugas;
        cout<<"Masukkan Nilai UTS     : "; cin>>mhs.nUTS;
        cout<<"Masukkan Nilai UAS     : ";cin>>mhs.nUAS;
        cout<<"=========="<<endl;
       
        mhs.hasil = (mhs.nAbsensi * 0.10) + (mhs.nTugas * 0.20) + (mhs.nUTS * 0.30) + (mhs.nUAS * 0.40);
       
        arr.push_back(mhs);
       
        cout<<endl;
    }
    
    TextTable t( '-', '|', '+' );

    t.add( "No." );
    t.add( "NIM" );
    t.add( "Nama Mhs" );
    t.add( "Nilai Absen" );
    t.add( "Nilai Tugas" );
    t.add( "Nilai UTS" );
    t.add( "Nilai UAS" );
    t.add( "Nilai Akhir" );
    t.endOfRow();
    
    for(i = 0; i < jmlh.jData; i++) {
        t.add( std::to_string(i + 1) );
        t.add( arr[i].nim );
        t.add( arr[i].nama );
        t.add( std::to_string(arr[i].nAbsensi) );
        t.add( std::to_string(arr[i].nTugas) );
        t.add( std::to_string(arr[i].nUTS) );
        t.add( std::to_string(arr[i].nUAS) );
        t.add( std::to_string((int)arr[i].hasil) );
        t.endOfRow();
    }
    
    std::cout<<t;
    
    cout<<endl;
    
    cout<<"Program ini dibuat oleh  : Lukman Bayhaqi"<<endl;
    cout<<"NIM                      : 41820110059"<<endl;
    cout<<"Program Studi            : Sistem Informasi"<<endl;
    
    return 0;
}
