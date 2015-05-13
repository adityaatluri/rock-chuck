#include"rockchuck.h"

char* getsrc(char* SrcOut, unsigned len, char* SrcIn){
	std::cout<<SrcIn<<std::endl;
	strcpy(SrcOut,SrcIn);
	return SrcOut;
}
