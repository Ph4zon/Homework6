#ifndef HW6_H
#define HW6_H
#include <iostream>
#include <fstream>

using namespace std;

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
	public:
		uint8_t strLength;
		char stringBuffer[maxRecordStringLength];
};

class BinaryFileHeader
{
	public:
		uint32_t magicNumber; /* Should be 0xFEEDFACE */
		uint32_t versionNumber;
		uint64_t numRecords;
};

BinaryFileHeader* getHeader(ifstream &in);
BinaryFileRecord* getRecord(ifstream &in, int num);

#endif
