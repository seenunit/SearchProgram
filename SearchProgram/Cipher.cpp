#include <afxwin.h>
#include <iostream>
#include <fstream>

using namespace std;

#define NOT_IT(val) val = ~val

int FileCipher(char *pcFile)
{
	char cFileName[_MAX_PATH] = {0};
	strcpy_s(cFileName, _MAX_PATH, pcFile);
	CFile objFile((LPCTSTR)pcFile, CFile::modeRead );
	long lFileByteSize = static_cast<long>(objFile.GetLength());
	objFile.Close();

	char *pcFileByteData = new char[lFileByteSize];//BYTE
	FILE *pFileRead = NULL;
	fopen_s(&pFileRead, cFileName, "rb");
	fread( pcFileByteData, sizeof( char ), lFileByteSize, pFileRead );
	fclose(pFileRead);

	for (int i = 0; i < lFileByteSize; i++ )
		NOT_IT( pcFileByteData[i] );

	FILE *pFileWrite = NULL;
	fopen_s(&pFileWrite, cFileName, "wb" );
	fwrite( pcFileByteData, sizeof( char ), lFileByteSize / sizeof( char ), pFileWrite );
	fclose( pFileWrite );

	delete[] pcFileByteData;

	return 0;
}

int FileEncode(char *pcFile)
{
	char cFileName[_MAX_PATH] = {0};
	strcpy_s(cFileName, _MAX_PATH, pcFile);
	CFile objFile((LPCTSTR)pcFile, CFile::modeRead );
	long lFileByteSize = static_cast<long>(objFile.GetLength());
	objFile.Close();

	char *pcFileByteData = new char[lFileByteSize];//BYTE
	FILE *pFileRead = NULL;
	fopen_s(&pFileRead, cFileName, "rb");
	fread( pcFileByteData, sizeof( char ), lFileByteSize, pFileRead );
	fclose(pFileRead);

	for (int i = 0; i < lFileByteSize; i++ )
		NOT_IT( pcFileByteData[i] );

	long lFileHalfSize = lFileByteSize/2;

	char *pcFileData1 = new char[lFileByteSize];
	char *pcFileData2 = new char[lFileByteSize+1];

	for(int i = 0; i < lFileHalfSize; i++)
		pcFileData1[i] = *(pcFileByteData + i);

	pcFileData1[lFileHalfSize] = '\0';

	for(int j = 0, i = lFileHalfSize; i < lFileByteSize; j++, i++)
		pcFileData2[j] = pcFileByteData[i];

	pcFileData2[lFileHalfSize] = '\0';

	strcat_s(pcFileData2, lFileByteSize+1, pcFileData1);
	
	for(int i = 0; i < lFileByteSize; i++)
		pcFileByteData[i] = pcFileData2[i];

	FILE *pFileWrite = NULL;
	fopen_s(&pFileWrite, cFileName, "wb" );
	fwrite( pcFileByteData, sizeof( char ), lFileByteSize / sizeof( char ), pFileWrite );
	fclose( pFileWrite );

	delete[] pcFileByteData;
	delete[] pcFileData1;
	delete[] pcFileData2;

	return 0;
}

int FileDEcode(char *pcFile)
{
	char cFileName[_MAX_PATH] = {0};
	strcpy_s(cFileName, _MAX_PATH, pcFile);
	CFile objFile((LPCTSTR)pcFile, CFile::modeRead );
	long lFileByteSize = static_cast<long>(objFile.GetLength());
	objFile.Close();

	char *pcFileByteData = new char[lFileByteSize];//BYTE
	FILE *pFileRead = NULL;
	fopen_s(&pFileRead, cFileName, "rb");
	fread( pcFileByteData, sizeof( char ), lFileByteSize, pFileRead );
	fclose(pFileRead);
	
	long lFileHalfSize = lFileByteSize/2;

	char *pcFileData1 = new char[lFileByteSize];
	char *pcFileData2 = new char[lFileByteSize+1];

	for(int i = 0; i < lFileHalfSize; i++)
		pcFileData1[i] = pcFileByteData[i];

	pcFileData1[lFileHalfSize] = '\0';

	for(int j = 0, i = lFileHalfSize; i < lFileByteSize; j++, i++)
		pcFileData2[j] = pcFileByteData[i];

	pcFileData2[lFileHalfSize] = '\0';

	strcat_s(pcFileData2, lFileByteSize+1, pcFileData1);
	
	for (int i = 0; i < lFileByteSize; i++ )
		pcFileByteData[i] = NOT_IT( pcFileData2[i] );

	FILE *pFileWrite = NULL;
	fopen_s(&pFileWrite, cFileName, "wb" );
	fwrite( pcFileByteData, sizeof( char ), lFileByteSize / sizeof( char ), pFileWrite );
	fclose( pFileWrite );

	delete[] pcFileByteData;
	delete[] pcFileData1;
	delete[] pcFileData2;

	return 0;
}


int main(int argc, char* argv[])
{
	if(argc!=2) 
	{
		cout << "Usage: output <filename>\n";
		return 1;
	}
	
	FileCipher(argv[1]);

	return 0;
}