/*
 * Filename             HW6Cdk.cc
 * Date                 04/26/2020
 * Author               Nicholas Rhein
 * Email                ncr170130@utdallas.edu
 * Course               CS3377.502
 * Version              1.0
 * Copyright		    2020, All Rights Reserved
 *
 * Description
 * Main program that creates the cdk matrix and puts the first 4 records into the cells
 */

#include "HW6.h"
#include "cdk.h"
#include <sstream>
#include <iomanip>
#include <algorithm>


#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

	WINDOW	*window;
	CDKSCREEN	*cdkscreen;
	CDKMATRIX     *myMatrix;           // CDK Screen Matrix

	const char 		*columnTitles[MATRIX_WIDTH+1] = {"0", "a", "b", "c", "d", "e"};
	const char 		*rowTitles[MATRIX_HEIGHT+1] = {"0", "a", "b", "c"};
	int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
	int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

	/*
	 * Initialize the Cdk screen.
	 *
	 * Make sure the putty terminal is large enough
	 */
	window = initscr();
	cdkscreen = initCDKScreen(window);
	
	/* Start CDK Colors */
	initCDKColor();

	/*
	 * Create the matrix.  Need to manually cast (const char**) to (char **)
	 */
	myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
				  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
					     boxTypes, 1, 1, ' ', ROW, true, true, false);
	
	if (myMatrix ==NULL)
	  {
	    printf("Error creating Matrix\n");
	    _exit(1);
	  }

	/* Display the Matrix */
	drawCDKMatrix(myMatrix, true);
	
	/*
	 * Dipslay a message
	 */
//	setCDKMatrixCell(myMatrix, 1, 2, "Test Message");
	ifstream in;
	in.open("/scratch/perkins/cs3377.bin", ios::in | ios::binary);
	BinaryFileHeader *header = getHeader(in);
	BinaryFileRecord *record;
	
	stringstream stream;
	stream << hex << "0x" << uppercase << header->magicNumber;
	string result(stream.str());
	char magic[32] = "Magic: ";
	char version[32];
	char numRecords[32];

	strcat(magic, result.c_str());
	snprintf(version, 32, "Version: %u", header->versionNumber);
	snprintf(numRecords, 32, "NumRecords: %u", header->numRecords);

//	cout << magic << endl;
//	cout << version <<  endl;
//	cout << numRecords << endl;

	setCDKMatrixCell(myMatrix, 1, 1, magic);
	setCDKMatrixCell(myMatrix, 1, 2, version);
	setCDKMatrixCell(myMatrix, 1, 3, numRecords);

	char strlen[32];

	for (int i = 0; i < min((uint64_t)4, header->numRecords); i++) {
		record = getRecord(in, i);
		snprintf(strlen, 32, "strlen: %u", record->strLength);
		setCDKMatrixCell(myMatrix, i+2, 1, strlen);
		setCDKMatrixCell(myMatrix, i+2, 2, record->stringBuffer);
		delete record;
	}

	drawCDKMatrix(myMatrix, true);    /* required  */
	
	/* so we can see results */
	sleep (10);


	// Cleanup screen
	endCDK();
	delete header;
}
