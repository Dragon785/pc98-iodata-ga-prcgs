#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <gagraph.h>
#include <string.h>

#include "prcgs.h"

int main(int argc,char* argv[])
{
	if (GAinit(LRESO_65536C))
	{
		printf("Init GA Error\n");
		return -1;
	}
	if (argc!=2)
	{
		printf("Usage lookga prcfile\n");
		return -1;
	}

	unsigned char* red=NULL;
	unsigned char* green=NULL;
	unsigned char* blue=NULL;
	if (StartReadPRCGS(argv[1])==0)
	{
		int width=GetWidth();int height=GetHeight();
		printf("Picture Size (%d,%d)\n",width,height);
		// PRCGSでは文字列の末尾のNULLは保障されていない
		unsigned char databuf[17]={0};
		memcpy(databuf,&Header.appAuthor,8);
		printf("ソフト作者:%s\n",databuf);
		memcpy(databuf,&Header.datAuthor,8);
		printf("データ作者:%s\n",databuf);
		memcpy(databuf,&Header.createYMD,8);
		printf("データ作成年月日:%s\n",databuf);
		memcpy(databuf,&Header.createHMS,8);
		printf("データ作成時刻:%s\n",databuf);
		memcpy(databuf,&Header.datMachine,16);
		printf("データ作成マシン:%s\n",databuf);
		
		uint32_t planeBufSize=(uint32_t)(width)*(uint32_t)(height);
		red=halloc(1,planeBufSize);
		if (red)
		{
			green=halloc(1,planeBufSize);
			if (green)
			{
				blue=halloc(1,planeBufSize);
				if (blue)
				{
					uint16_t* hicol=malloc(2*width);
					if (hicol)
					{
						printf("Extracting PRCGS Data..\n");
						if (Extract(red,green,blue)==0)
						{
#if 0 // decode check
							FILE* fb=fopen("test.rgb","wb");
							fwrite(red,1,planeBufSize,fb);
							fwrite(green,1,planeBufSize,fb);
							fwrite(blue,1,planeBufSize,fb);
							fclose(fb);
#endif

							GAclrScreen();
							GAcrtSel(CRT_GA);
							unsigned char *r=red,*g=green,*b=blue;
							for (int y=0;y<height;++y)
							{
								uint16_t *h=hicol;
								for (uint32_t i=0;i<width;++i)
								{
									uint16_t hr=*r++>>3;
									uint16_t hg=*g++>>2;
									uint16_t hb=*b++>>3;
									*h++=(hr<<11)|(hg<<5)|(hb);
								}
								GArestoreImage(0,y,width-1,y,PIXEL_MODE,(void far*)(hicol));
							}
							(void)(getch());
							GAcrtSel(CRT_PC);
						}
						else
						{
							printf("Extract Failed\n");
						}

						free(hicol);
					}
					else
					{
						printf("Can't Allocate Hicolor Buffer\n");
					}				
				}
				else
				{
					printf("Can't Allocate Blue Buffer\n");
				}
			}
			else
			{
				printf("Can't Allocate Green Buffer\n");
			}
		}
		else
		{
			printf("Cant Allocate Red Buffer\n");				
		}
	}
	else
	{
		printf("Not PRCGS Data\n");
	}
	if (red)
	{
		hfree(red);red=NULL;
	}
	if (green)
	{
		hfree(green);green=NULL;
	}
	if (blue)
	{
		hfree(blue);blue=NULL;
	}

	return -1;
}
