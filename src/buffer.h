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

char* default_alloc(unsigned int nSize);
void  default_free(char* pBuf);


// 数据块
class Block : public deque_node<Block>
{
public:
	/*
	* nSize is the bytes of block can store
	* pAllocFun: alloc store data buf
	* pFreeFun: free buff
	*/
	Block(unsigned int nSize, AllocBufferFun pAllocFun = default_alloc, FreeBufferFun pFreeFun = default_free);
	~Block();

public:
	// character of deque
	/*
	* add the pNew after self
	*/
	void	Add(Block* pNew);
	/*
	* delete self from the deque
	*/
	void	Delete();

public:
	// 在多线程下使用，读操作（写操作）必须在同一个线程，可以保证读写的数据一致。	
	/*
	* 获取可读取的数据长度
	* character of buffer block
	* get the size of data can be read from the block
	*/
	unsigned int GetCanReadDataSize();
	/*
	* 将存储的数据读到pDest中，最多可读nReadSize。返回值为真实读取的大小
	* read up to nReadSize bytes from block into the buffer starting at pDest
	* return the number of bytes read
	*/
	unsigned int ReadData(char* pDest, unsigned int nReadSize);
	/*
	* 获取block中可以读取数据的开始位置， nReadSize返回可读取的长度
	* if there is no free data, NULL is returned, otherwise, the point starting at block data that can be read is returned, 
	* and nReadsize is set to the size of free data
	*/
	char* GetReadData(unsigned int& nReadSize);
	/*
	* 标记已读nSize长度的buffer
	* mark block had been read into data of nSize bytes
	*/
	void MarkReadData(unsigned int nSize);


	/*
	* get the size of free data that can be wrote into block
	*/
	unsigned int GetCanWriteDataSize();
	/*
	* write data into block
	* write the pData into block, and size of pData is nSize, return value is the number of bytes has wrote into block	
	* 写入数据，返回为真实写入的长度
	*/
	unsigned int WriteData(char* pData, unsigned int nSize);

	/*
	* GetWriteBuffer 和 MarkWriteData 需要在同一个原子中调用, 两者一起类似于WriteData
	* 1: 调用GetWriteBuffer获取可写指针以及可写长度
	* 2: 使用可写指针，向buffer中写入数据
	* 3: 调用MarkWriteData，标记前面写入长度nSize的数据
	* GetWriteBuffer and MarkWriteData must call together, same as call WriteData
	* call step 1: call GetWriteBuffer, get point of free data and the nFreeSize
	* call step 2: write data into block by using free data point
	* call step 3: call MarkWriteData, nSize is the size that had wrote into block in step 2
	* get point of free data and the size
	*/
	char* GetWriteBuffer(unsigned int& nFreeSize);
	/*
	* mark block had been wrote into data of nSize bytes
	*/
	void MarkWriteData(unsigned int nSize);

	/*
	* 清空数据
	*/
	void Clear();

	/*
	* 整个buffer的数据是否读完
	*/
	bool IsReadAll() { return (m_pTail == m_pRead); };
	/*
	* 整个buffer已经是否写完
	*/
	bool IsWriteAll() { return (m_pTail == m_pWrite); };


private:
	/*	
	* 数据存放区域
	* the buffer of block store data starting at pDest
	*/
	char*	m_pData;
	/*
	* 读指针位置
	* the point for the data will be read
	*/
	char*	m_pRead;
	/*
	* 写指针位置
	* the point for the data will be wrote
	*/
	char*	m_pWrite;
	/*
	* buf终止位置
	* the point is the end of m_pData
	*/
	char*	m_pTail;
	/*
	* buf大小
	* size of m_pData
	*/
	unsigned int m_nSize;

	/*
	* free m_pData
	* buffer 释放函数
	*/
	FreeBufferFun	m_fnFreeBuf;
};


class Buffer
{
public:
	Buffer(unsigned int nLimit = 0, unsigned int nBlockSize = ALLOC_BUFFER_SIZE, AllocBufferFun pAllocFun = default_alloc, FreeBufferFun pFreeFun = default_free);
	~Buffer();

public:
	// set buffer config
	/*
	* the max number of buffer can new block
	*/
	void SetBlockLimit(unsigned int nLimit);
	/*
	* set functions block alloc buffer and free buffer
	*/
	void SetAllocAndFreeFuns(AllocBufferFun pAllocFun, FreeBufferFun pFreeFun);
	/*
	* set the block buffer size
	*/
	void SetBlockSize(unsigned int nBlockSize);

	// Read Data
	/*
	* 获取可读数据的大小
	* get the size of data can be read
	*/
	unsigned int GetCanReadSize();
	/*
	* 从buffer中读取数据，最大可读取nSize. 返回值为总读取值
	*/
	unsigned int ReadData(char* pDest, unsigned int nSize);
	/*
	* 获取可读数据指针以及可读长度，返回数据为m_pReadBlock的可读数据及长度，而不是所有的可读Block的数据
	*/
	char* GetReadData(unsigned int& nSize);
	/*
	* 标记数据已读。只标记m_pReadBlock
	*/
	void MarkReadData(unsigned int nSize);


	// Write Data
	/*
	* 将数据写入buffer,如果block有上限，则有可能写失败
	*/
	bool WriteData(char* pData, unsigned int nSize);
	/*
	* 获取可写指针以及长度，这里返回的只有m_pWriteBlock的可写指针和长度
	*/
	char* GetWriteBuffer(unsigned int& nSize);
	/*
	* 标记写入了nSize的数据，只标记m_pWriteBlock
	* 如果完全标记，m_pWriteBlock指向下一个，如果下一个block是m_pReadBlock，
	* 则需要创建一个block，将m_pWriteBlock指向新建的block，如果创建失败则返回flase
	*/
	bool MarkWriteData(unsigned int nSize);

private:
	/*
	* 创建第一个block
	*/
	void Init();

	/*
	* 创建一个新的block, 只有在写的时候才会创建
	*/
	Block*	NewBlock();

public:
	/*
	* 正在读的block
	*/
	Block*		m_pReadBlock;
	/*
	* 正在写的block
	*/
	Block*		m_pWriteBlock;

	/*
	* Block的数量
	*/
	unsigned int m_nBlockCount;
	/*
	* Block的上限, 0 表示不做限制
	*/
	unsigned int m_nBlockLimit;
	/*
	* block中数据块的大小
	*/
	unsigned int m_nBlockSize;
	/*
	* alloc function
	*/
	AllocBufferFun	m_pAllocFun;
	/*
	* free function
	*/
	FreeBufferFun	m_pFreeFun;
};