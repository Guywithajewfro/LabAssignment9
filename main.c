/*
	Modified by Daniel Nunez
	4/11/24
	CS1 Lab Assignment 9
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50
#define TABLESIZE 99999

// RecordType
typedef struct record {
	int		id;
	char	name;
	int		order; 
} RecordType;

// Fill out this structure
typedef struct hash {
	RecordType *rPoint;
} HashType;

// Compute the hash function
int hash(int x) {
	int value = 0;
	for (int i=0; i<x; i++) {
		value = ((value * 128) + x) % TABLESIZE;
	}
	return value;
}	//Ends hash

// parses input file to an integer array
int parseData(char* inputFileName, RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (RecordType *) malloc(sizeof(RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(HashType *pHashArray, int hashSz)
{
	for (int i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all
		int hashVal = hash(hashSz);
		if (pHashArray->rPoint->id != 0) {
			printRecords(pHashArray->rPoint, hashVal);
		}
	}
}

int main(void)
{
	RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	//Enter code here
	HashType *pHash;
	displayRecordsInHash(pHash, recordSz);
}