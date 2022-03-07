#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <vector>

using namespace std;

bitset<8> as_bits(char c);
bitset<6> conv_to_bitset(char(& chars)[6]);
void encode(const char(& charset)[64], const char* input, long size);
void decode(const char(& charset)[64], const char* input, long size);

int main (int argc, char *argv[]) {
  if (argc != 2) {
    cerr << "Input must be ./base64 <--encode/--decode>" << endl;
    exit(1);
  }

  bool isEncode = strcmp(argv[argc - 1], "--encode") == 0;
  bool isDecode = strcmp(argv[argc - 1], "decode") == 0;

  if (!isEncode && !isDecode) {
    cerr << "Input must be ./base64 <--encode/--decode>" << endl;
    exit(1);
  }

  const char b64charset[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/'
  };

  stringstream* istream = new stringstream();

  if (isEncode) {
    cout << "Value to encode: ";
    *istream << cin.rdbuf();
    encode(b64charset, istream->str().c_str(), istream->tellp());
  } else {
    cout << "Value to decode: ";
    *istream << cin.rdbuf();
    decode(b64charset, istream->str().c_str(), istream->tellp());
  }

  delete istream;

  return 0;
}

bitset<8> as_bits(char c) {
  bitset<8> b(c);
  return b;
}

bitset<6> conv_to_bitset(char(& chars)[6]) {
  bitset<6> b;
  for (int i = 0; i < 6; i += 1) b[5 - i] = chars[i];
  return b;
}

void encode(const char(& charset)[64], const char* input, long size) {
  // our output should be 4/3x the size of our input
  char* output = new char[size * (4/3)];
  long outIndex = 0;

  // amount of chars that will be remaining after loop
  int rem = size % 3;

  cout << endl;

  // loop through input in 3-size clip, leaving rem to handle later
  for (int i = 0; i < size - rem; i += 3) {

    vector<bitset<8> > ibitsets = {
      as_bits(input[i]),
      as_bits(input[i+1]),
      as_bits(input[i+2])
    };

    char set[6];

    // deal with set1
    for (int j = 0; j < 6; j += 1) set[j] = ibitsets.at(0)[7 - j];
    // commit set1 output
    output[outIndex] = charset[(int)(conv_to_bitset(set).to_ulong())];
    outIndex += 1;

    // deal with set2
    for (int j = 6; j < 8; j += 1) set[j - 6] = ibitsets.at(0)[7 - j];
    for (int j = 0; j < 4; j += 1) set[j + 2] = ibitsets.at(1)[7 - j];
    // commit set2 output
    output[outIndex] = charset[(int)(conv_to_bitset(set).to_ulong())];
    outIndex += 1;

    // deal with set3
    for (int j = 4; j < 8; j += 1) set[j - 4] = ibitsets.at(1)[7 - j];
    for (int j = 0; j < 2; j += 1) set[j + 4] = ibitsets.at(2)[7 - j];
    // commit set3 output
    output[outIndex] = charset[(int)(conv_to_bitset(set).to_ulong())];
    outIndex += 1;

    // deal with set4
    for (int j = 2; j < 8; j += 1) set[j - 2] = ibitsets.at(2)[7 - j];
    // commit set4 output
    output[outIndex] = charset[(int)(conv_to_bitset(set).to_ulong())];
    outIndex += 1;
  }

  cout << output << endl;

  if (rem == 0) return;

  if (rem == 1) {
    // 8 bits over
    // padding -> ==

  } else if (rem == 2) {
    // 16 bits over
    // padding -> =
  }

  return;
}

void decode(const char(& charset)[64], const char* input, long size) {

  return;
}