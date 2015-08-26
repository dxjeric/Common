//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-24   16:05
//	File Name:	buffer.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include <stdio.h>

#include "buffer_config.h"
#include "deque.h"


// 数据块
class Block : public deque_node<Block>
{
public:
	// nSize is the bytes of block can store
	// pAllocFun: alloc store data buf
	// pFreeFun: free buff
	Block(unsigned int nSize, AllocBufferFun pAllocFun, FreeBufferFun pFreeFun);
	~Block();

public:
	// character of deque
	// add the pNew after self
	void	Add(Block* pNew);
	// delete self from the deque
	void	Delete();

public:
	// 在多线程下使用，读操作（写操作）必须在同一个线程，可以保证读写的数据一致。	

	// 获取可读取的数据长度
	// character of buffer block
	// get the size of data can be read from the block
	unsigned int GetCanReadDataSize();
	// 将存储的数据读到pDest中，最多可读nReadSize。返回值为真实读取的大小
	// read up to nReadSize bytes from block into the buffer starting at pDest
	// return the number of bytes read
	unsigned int ReadData(char* pDest, unsigned int nReadSize);
	// 获取block中可以读取数据的开始位置， nReadSize返回可读取的长度
	// if there is no free data, NULL is returned, otherwise, the point starting at block data that can be read is returned, 
	// and nReadsize is set to the size of free data
	char* GetReadData(unsigned int& nReadSize);
	// 标记已读nSize长度的buffer
	// mark block had been read into data of nSize bytes
	void MarkReadData(unsigned int nSize);


	// get the size of free data that can be wrote into block	
	unsigned int GetCanWriteDataSize();
	// write data into block
	// write the pData into block, and size of pData is nSize, return value is the number of bytes has wrote into block	
	unsigned int WriteData(char* pData, unsigned int nSize);
	// GetWriteBuffer and MarkWriteData must call together, same as call WriteData
	// call step 1: call GetWriteBuffer, get point of free data and the nFreeSize
	// call step 2: write data into block by using free data point
	// call step 3: call MarkWriteData, nSize is the size that had wrote into block in step 2
	// get point of free data and the size
	char* GetWriteBuffer(unsigned int& nFreeSize);
	// mark block had been wrote into data of nSize bytes
	void MarkWriteData(unsigned int nSize);

private:
	// 数据存放区域	
	// the buffer of block store data starting at pDest
	char*	m_pData;
	// 读指针位置
	// the point for the data will be read
	char*	m_pRead;
	// 写指针位置
	// the point for the data will be wrote
	char*	m_pWrite;
	// buf终止位置
	// the point is the end of m_pData
	char*	m_pTail;
	//  buf大小
	// size of m_pData
	unsigned int m_nSize;

	// free m_pData
	FreeBufferFun	m_fnFreeBuf;
};


class Buffer
{

};