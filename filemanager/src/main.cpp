#include <iostream>
#include <fstream>
#include <string>

#include <md5.hpp>
#include <FileManager.hpp>


using namespace std;

int main()
{
	/*
    char file1[] = "a.png";
    char file2[] = "test.png";

    FileManager fmanager(file1,0, 10000, 2312);

    FileManager cible(file2,fmanager.getFileSize(), fmanager.getChunkSize(), 1);

    MD5 md5;
    string tmpStr;
    ofstream file;


	int size;
	char* serializedTmp;
    for(int i=0; i<fmanager.getNumberChunk() ; i++)
    {
        Chunk tmp = fmanager.getChunk(i);
        serializedTmp = tmp.serialize(size);
        Chunk tmp2(serializedTmp, size);
        if(tmp2.isIntegrate())
        {
            cible.saveChunk(tmp2);
            cout << (float(i+1)/float(fmanager.getNumberChunk()))*100<<endl;
        }
        else
        {
            cout<<"le CRC ne correspond pas!!"<<endl;
        }

    }
*/
cout<<FileManager::getFreeDiskSpace()/(1)<<endl;






}
