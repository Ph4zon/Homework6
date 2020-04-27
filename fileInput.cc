/*
 * Filename             fileInput.cc
 * Date                 04/26/2020
 * Author               Nicholas Rhein
 * Email                ncr170130@utdallas.edu
 * Course               CS3377.502
 * Version              1.0
 * Copyright		    2020, All Rights Reserved
 *
 * Description
 * Gets the input from the binary file
 */

#include "HW6.h"

BinaryFileHeader* getHeader(ifstream &in) {
	BinaryFileHeader *header = new BinaryFileHeader();
	
	in.seekg(0, in.beg);

	in.read((char *) header, sizeof(BinaryFileHeader));
	return header;
}

BinaryFileRecord* getRecord(ifstream &in, int num) {
	BinaryFileRecord *record = new BinaryFileRecord();
	
	in.seekg(sizeof(BinaryFileHeader) + sizeof(BinaryFileRecord) * num, in.beg);
	
	in.read((char *) record, sizeof(BinaryFileRecord));

	return record;
}
