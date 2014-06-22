#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;
#pragma once

class music
{
    const unsigned char maskByte = 254;
    unsigned char mask[8];
    const int maskSize = 8;
    int WriteByte(int position, unsigned char text, fstream &audio);
    unsigned char ReadByte(int position, ifstream &audio);
public:
    void Write(fstream &audio, ifstream &text);
    void Read(ifstream &audio, ofstream &text);
    music();
};
