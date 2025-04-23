
#define _CRT_SECURE_NO_WARNINGS

#ifndef JPEGDECODER_H
#define JPEGDECODER_H

#include <stdio.h>
#include <map>
#include <string>
#include <math.h>

#ifndef DEFUINT8
#define DEFUNIT8
typedef unsigned char uint8_t;
#endif

/* @brief �� Zig-Zag �����
 */
 /*
 static const int UnZigZagTable[64] =
 {
	  0,  1,  8, 16,  9,  2,  3, 10,
	 17, 24, 32, 25, 18, 11,  4,  5,
	 12, 19, 26, 33, 40, 48, 41, 34,
	 27, 20, 13,  6,  7, 14, 21, 28,
	 35, 42, 49, 56, 57, 50, 43, 36,
	 29, 22, 15, 23, 30, 37, 44, 51,
	 58, 59, 52, 45, 38, 31, 39, 46,
	 53, 60, 61, 54, 47, 55, 62, 63
 };
 */

static int const UnZigZagTable[64] =
{
	 0,  1,  5,  6, 14, 15, 27, 28,
	 2,  4,  7, 13, 16, 26, 29, 42,
	 3,  8, 12, 17, 25, 30, 41, 43,
	 9, 11, 18, 24, 31, 40, 44, 53,
	10, 19, 23, 32, 39, 45, 52, 54,
	20, 22, 33, 38, 46, 41, 55, 60,
	21, 34, 37, 47, 50, 56, 59, 61,
	35, 36, 48, 49, 57, 58, 62, 63
};

/* @brief ��ɢ���ұ任ϵ������
 */
static const double MtxDCT[8][8] =
{
	{0.3536,    0.3536,    0.3536,    0.3536,    0.3536,    0.3536,    0.3536,    0.3536},
	{0.4904,    0.4157,    0.2778,    0.0975,   -0.0975,   -0.2778,   -0.4157,   -0.4904},
	{0.4619,    0.1913,   -0.1913,   -0.4619,   -0.4619,   -0.1913,    0.1913,    0.4619},
	{0.4157,   -0.0975,   -0.4904,   -0.2778,    0.2778,    0.4904,    0.0975,   -0.4157},
	{0.3536,   -0.3536,   -0.3536,    0.3536,    0.3536,   -0.3536,   -0.3536,    0.3536},
	{0.2778,   -0.4904,    0.0975,    0.4157,   -0.4157,   -0.0975,    0.4904,   -0.2778},
	{0.1913,   -0.4619,    0.4619,   -0.1913,   -0.1913,    0.4619,   -0.4619,    0.1913},
	{0.0975,   -0.2778,    0.4157,   -0.4904,    0.4904,   -0.4157,    0.2778,   -0.0975}
};

/* @brief ����ɢ���ұ任ϵ������
 */
static const double MtxIDCT[8][8] =
{
	{0.3536,    0.4904,    0.4619,    0.4157,    0.3536,    0.2778,    0.1913,    0.0975},
	{0.3536,    0.4157,    0.1913,   -0.0975,   -0.3536,   -0.4904,   -0.4619,   -0.2778},
	{0.3536,    0.2778,   -0.1913,   -0.4904,   -0.3536,    0.0975,    0.4619,    0.4157},
	{0.3536,    0.0975,   -0.4619,   -0.2778,    0.3536,    0.4157,   -0.1913,   -0.4904},
	{0.3536,   -0.0975,   -0.4619,    0.2778,    0.3536,   -0.4157,   -0.1913,    0.4904},
	{0.3536,   -0.2778,   -0.1913,    0.4904,   -0.3536,   -0.0975,    0.4619,   -0.4157},
	{0.3536,   -0.4157,    0.1913,    0.0975,   -0.3536,    0.4904,   -0.4619,    0.2778},
	{0.3536,   -0.4904,    0.4619,   -0.4157,    0.3536,   -0.2778,    0.1913,   -0.0975}
};


/* Matrix */
class Mtx
{
public:
	int *operator[] (int row)
	{
		return data[row];
	}
private:
	int data[8][8];
};


class Pixel
{
public:
	int R, G, B;
};

/*  Y : Cr : Cb  =  4 : 1 : 1 */
class MCU
{
public:
	Mtx    yMtx[4];
	Mtx    crMtx;
	Mtx    cbMtx;
};

class BitmapImage
{
public:
	BitmapImage() : Data(NULL), Height(0), Width(0) {}
	~BitmapImage()
	{
		if (Data != NULL)
			delete[]Data;
	}

	void CreateImage()
	{
		Data = new uint8_t[Height * Width * 3];
	}

	uint8_t *Data;  // image data
	int		Height; // rows of image
	int		Width;  // cols of image
};

class HuffmanTable
{
public:
	std::map<std::string, uint8_t> &operator[] (int index)
	{
		switch (index)
		{
		case 0:  return DC[0]; break; /* 00 */
		case 1:  return DC[1]; break; /* 01 */
		case 16: return AC[0]; break; /* 10 */
		case 17: return AC[1]; break; /* 11 */
		default: return DC[0]; break;
		}
	}
private:
	std::map<std::string, uint8_t> DC[2];
	std::map<std::string, uint8_t> AC[2];
};




class JpegDecoder
{
public:
	JpegDecoder(const char *fileName) : endOfDecoder(false), readCount(0x80), dcY(0), dcCr(0), dcCb(0), idxOfBlock(0)
	{
		fp = fopen(fileName, "rb+");
	}

	~JpegDecoder()
	{
		fclose(fp);
	}


	BitmapImage &Decoder();


protected:
	/* @brief Decoder a matrix of mcu
	   @params:
			block: ����ֵ
			table: huffman table type ( 00, 01, 10, 11 )
			quant: ������
	*/
	void DecoderMtx(Mtx &block, int table, uint8_t *quant, int &dc);

	/*  ������һ��MCU */
	void DecoderNextMCU();

	/* ��ȡ�������� */
	void DecoderHuffman()
	{
		int offset = 181;
		fseek(fp, offset, SEEK_SET);
		DecoderTable(); 		/* DC-0 */

		offset = 4;
		fseek(fp, offset, SEEK_CUR);
		DecoderTable();			/* DC-1 */

		fseek(fp, offset, SEEK_CUR);
		DecoderTable();			/* AC-0 */

		fseek(fp, offset, SEEK_CUR);
		DecoderTable();			/* AC-1 */
	}

	/* ���� һ���������� */
	void DecoderTable();

	/* ��ȡ������ */
	void DecoderQuant()
	{
		/* read Quant Table of Y */
		int offset = 25;
		fseek(fp, offset, SEEK_SET);
		fread(quantY, 1, 64, fp);

		/* read Quant Table of C */
		offset = 5;
		fseek(fp, offset, SEEK_CUR);
		fread(quantC, 1, 64, fp);
	}

	/* ��ȡͼ�� ��� */
	void DecoderSize()
	{
		uint8_t buf[2];
		/* read height */
		int offset = 163;
		fseek(fp, offset, SEEK_SET);
		fread(buf, 1, 2, fp);
		img.Height = (buf[0] << 8) + buf[1];

		/* read width */
		fread(buf, 1, 2, fp);
		img.Width = (buf[0] << 8) + buf[1];

		/* create image */
		img.CreateImage();

		/* compute number of MCU block */
		xNumberOfBlock = (img.Height + 15) / 16;
		yNumberOfBlock = (img.Width + 15) / 16;
	}


	/* �������˻� */
	Mtx MtxMulI2D(Mtx &left, const double right[8][8])
	{
		Mtx dctBuf;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				double tempVal = 0.0;
				for (int k = 0; k < 8; k++)
				{
					tempVal += left[i][k] * right[k][j];
				}
				dctBuf[i][j] = round(tempVal);
			}
		}
		return dctBuf;
	}

	/* �������˻� */
	Mtx MtxMulD2I(const double left[8][8], Mtx &right)
	{
		Mtx dctBuf;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				double tempVal = 0.0;
				for (int k = 0; k < 8; k++)
				{
					tempVal += left[i][k] * right[k][j];
				}
				dctBuf[i][j] = round(tempVal);
			}
		}
		return dctBuf;
	}

	void UnZigZag(Mtx &block)
	{
		int tempBuf[64];
		for (int i = 0; i < 64; i++) tempBuf[i] = block[i / 8][i % 8];

		for (int i = 0; i < 64; i++) block[i / 8][i % 8] = tempBuf[UnZigZagTable[i]];
	}

	/* ��ȡ����������õ���ʵ���ݵ���Ч���ȣ� ��ȡָ����λ�� */
	int GetRealValue(int length);

	void DCT(Mtx &block)
	{
		block = MtxMulD2I(MtxDCT, block);
		block = MtxMulI2D(block, MtxIDCT);
	}

	/* ����ɢ���ұ任 */
	void IDCT(Mtx &block)
	{
		block = MtxMulD2I(MtxIDCT, block);
		block = MtxMulI2D(block, MtxDCT);
	}


	/* ������ */
	Mtx InveseSample(Mtx &block, int number);

	/* ��ɫ�ռ�ת�� */
	void ConvertClrSpace(Mtx &Y, Mtx &Cr, Mtx &Cb, Pixel out[8][8]);

	/* �� MCU ��Ԫ YCrCb ��ɫת��Ϊ RGB ��ɫ */
	void Convert();

	void WriteToRGBBuffer(Pixel buf[8][8], int blockIndex);

	/* ���� DC ֵ�� 0 */
	void ResetDC()
	{
		dcY = dcCr = dcCb = 0x0;
	}


	void WirteBlock(Pixel block[16][16])
	{
		int x = (idxOfBlock / yNumberOfBlock) * 16; //
		int y = (idxOfBlock % yNumberOfBlock) * 16; //
		idxOfBlock++;

		for (int i = 0; i < 16; i++)
		{
			if ((x + i) >= img.Height) break;
			for (int j = 0; j < 16; j++)
			{
				if (y + j >= img.Width) continue;
				int offset = ((x + i) * img.Width + (y + j)) * 3;
				img.Data[offset + 0] = block[i][j].B;
				img.Data[offset + 1] = block[i][j].G;
				img.Data[offset + 2] = block[i][j].R;
			}
		}
	}



	/* ��λ���������ĵ�һ���ֽ� */
	void ToStartOfData()
	{
		int offset = 623; // �ļ�ͷ�ĳ���
		fseek(fp, offset, SEEK_SET);  // ͷ�ļ�ͷ��ʼ
		fread(&currentVal, 1, 1, fp); // ��ȡ��һ������
	}

	/* @brief ��ȡ��һ�� Key �� value
		@params:
				table: type of huffman ( 00, 01, 10, 11 )
	*/
	int FindKeyValue(int table);

	int NextBit()
	{
		if (readCount == 0x0)
		{
			// reset
			readCount = 0x80;
			fread(&currentVal, 1, 1, fp);

			// check
			if (currentVal == 0xFF) //���ֵ
			{
				fread(&currentVal, 1, 1, fp); //��ȡ��һ���ֽ�
				switch (currentVal)
				{
				case 0x00: currentVal = 0xFF; break;
				case 0xD9: endOfDecoder = true; break;
				case 0xD0:
				case 0xD1:
				case 0xD2:
				case 0xD3:
				case 0xD4:
				case 0xD5:
				case 0xD6:
				case 0xD7: ResetDC(); break;
				default:break;
				};
			}
		}

		if (endOfDecoder) return 0; // end of decoder

		int retVal = currentVal & readCount; // ��ȡ��ǰλ��ֵ (1 or 0)
		readCount >>= 1;
		return (retVal > 0 ? 1 : 0);
	}
private:
	BitmapImage	 img; // image data
	FILE         *fp; // �ļ�ָ��
	uint8_t		 quantY[64]; // Y ������
	uint8_t		 quantC[64]; // Cr, Cb ����������
	HuffmanTable huffman;    // ��������
	MCU			 mcu;        // ��С���루���룩��Ԫ
	int          dcY;        // Y ������ DC ���ֵ
	int          dcCr;       // Cr ������ DC ���ֵ
	int          dcCb;       // Cb ������ DC ���ֵ

	Pixel        rgbBuf[16][16]; // ������RGBֵ
	int          idxOfBlock;  // index of block number
	int          xNumberOfBlock;
	int          yNumberOfBlock;

	bool		endOfDecoder;
	uint8_t		currentVal; // ��ǰ��������
	uint8_t		readCount;  // �Ѷ�ȡ bit ��, >=8 ʱ���ļ���ȡ��һ���ֽ����ݵ� currentVal
};


#endif
