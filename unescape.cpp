#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <vector>

using namespace std;

//cl unescape.cpp /O2 /EHsc /GA /MT /Feunescape.exe


int main(int argc,char* argv[])
{
	struct _stati64 statbuff;
	vector<BYTE> buff;
	if(argc<2)
	{
		printf("Usage:\nunescape <filename> - unescapes \\x type escapes\n");
		return 0;
	}
	if(-1==_stati64(argv[1],&statbuff))
	{
		printf("Couldn't get info on file\n");
		return -1;
	}
	
	buff.resize(statbuff.st_size);
	FILE*fp=fopen(argv[1],"rb");
	fread(&buff[0],1,statbuff.st_size,fp);
	fclose(fp);
	for(__int64 i=0;i<statbuff.st_size;)
	{
		if( (i<(statbuff.st_size-3)) && (buff[i]=='\\') && (buff[i+1]=='x') )
		{
			char slask[10];
			slask[0]=buff[i+2];
			slask[1]=buff[i+3];
			slask[2]=0;
			int val=strtol(slask,NULL,16);
			i+=4;
			printf("%c",(char)val);
		}
		else
		{
			printf("%c",buff[i++]);
		}
	}
	return 0;
}