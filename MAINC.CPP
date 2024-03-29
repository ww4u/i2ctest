//****************************************
//**  Web:  http://usendz.taobao.com  **
//****************************************
//**     USB2IIC&SPI for SDK              **
//****************************************
//
#include    "USBIO.H"

UINT mIndex = 0;

//! query
int i2cQuery( int index, unsigned char *pDatas, int len,
                          unsigned char *pOut,   int oLen  )
{
    //! set clock
    USBIO_SetStream(index,0x82);

    if(!USBIO_StreamI2C(index,len,pDatas,oLen,pOut))
    {
        return -1;
    }

    return 0;
}


int main ( )
{
    if(USBIO_OpenDevice(mIndex) == INVALID_HANDLE_VALUE)
    {
        printf( "open fail\n" );
        return -1;
    }

    int ret;

    unsigned char inData[]={ 0x6c, 0x0c };
    unsigned char outData[ 2 ];

    ret = i2cQuery( mIndex, inData, sizeof(inData), outData, sizeof(outData) );
    if ( ret != 0 )
    {
        printf( "query fail\n" );
    }
    else
    {
//        printf( "success %d,%d\n", outData[0], outData[1] );
        unsigned short word;

        word = (outData[0]<<8) | ( outData[1] );
        float angle = word * 360.0f/ (1<<12);
        printf( "success %f\n", angle );
    }

    USBIO_CloseDevice(mIndex);
}

//程序入口
int _main ( )
{
	UINT mErrCnt = 0;
	UCHAR Numf = 0;
	
	printf( "\nInitialing ......");
	printf( "\n****************************************************\n");
	// 需要使用DLL则需要先加载
	printf( "Load DLL: USBIOX.DLL ......\n" );
//    if (LoadLibrary("USBIOX.DLL") == NULL ) return -1;  // 加载DLL失败,可能未安装到系统中
	printf( "USBIO_OpenDevice: 0\n" );
	

	if(USBIO_OpenDevice(mIndex) == INVALID_HANDLE_VALUE)
	{
		printf("\nfail to open device!!");
		getch();
        return -1;
	}  //使用之前必须打开设备 
	
    printf("\nOpen device sucessfully!");
	printf("\nPress any key to continue......");
	getch();

    
	while(Numf<5)
	{
		system("cls");
		printf( "\n************************ USB2IIC&SPI for SDK V1.0 ***************************\n");
        printf( "                                        Copyright (C) USEN TECH. 2012.02   ");
		printf( "\n***************************************************************************\n");
		printf("\nFunction Select:\n");
		printf("\n(1) GPIO TEST");
		printf("\n(2) I2C(USBIO_StreamI2C) TEST");
		printf("\n(3) SPI(USBIO_SPI4) TEST");
		printf("\n(4) SPI(USBIO_BitSPI) TEST");
		printf("\nOTHERS EXIT");
		printf("\n\nPlease select the function:");
		scanf("%d",&Numf);
		
		switch(Numf)
		{
		case 1:
			GPIO();	
			break;
		case 2:
			I2CStream();
			break;
		case 3:
			SPIByte();
			break;
		case 4:
			SPIBit();
			break;
		default:
			Numf = 10;
			break;
		}
	}

	//关闭USB2I2C设备,如果不继续使用则必须关闭设备,就象读写完硬盘中的数据文件后要关闭一样
	printf("\n **************************** USBIO_CloseDevice:%d ******************************",mIndex);
	USBIO_CloseDevice(mIndex);
	printf("\n                            Exit...                                                     \n" );

    return 0;
}




