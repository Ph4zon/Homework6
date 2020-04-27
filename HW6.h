/*
 * Filename             HW6.h
 * Date                 04/26/2020
 * Author               Nicholas Rhein
 * Email                ncr170130@utdallas.edu
 * Course               CS3377.502
 * Version              1.0
 * Copyright		    2020, All Rights Reserved
 *
 * Description
 * Header file for Homework 6
 */

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
