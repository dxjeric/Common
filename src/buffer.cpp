//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-24   16:05
//	File Name:	buffer.cpp
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include <assert.h>
#include "buffer.h"
#include "liblog.h"

Block::Block(unsigned int nSize, AllocBufferFun pAllocFun, FreeBufferFun pFreeFun)
{
	m_pData = pAllocFun(nSize);
	m_pRead = m_pWrite = m_pData;
	m_pTail = m_pData + nSize;
	m_nSize = nSize;

	m_fnFreeBuf = pFreeFun;
}

Block::~Block()
{
	if (m_pData)
		m_fnFreeBuf(m_pData);

	m_pData = m_pRead = m_pWrite = m_pTail = NULL;
}

unsigned int Block::GetCanReadDataSize()
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	// 在多线程下，m_pWrite其他地方使用，为了防止函数内部不一致，因此先取出
	char* pWrite = m_pWrite;
	if (m_pRead > pWrite)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "GetReadDataSize m_pRead(0x%08x) > m_pWrite(0x%08x), block buffer(0x%08x), size(%d).", m_pRead, pWrite, m_pData, m_nSize);
		assert(false);
	}

	return pWrite - m_pRead;
}

char* Block::GetReadData(unsigned int& nReadSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);

	char* pWrite = m_pWrite;
	if (m_pRead > pWrite)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "ReadData m_pRead(0x%08x) > m_pWrite(0x%08x), block buffer(), size(%d).", m_pRead, pWrite, m_pData, m_nSize);
		assert(false);
	}

	nReadSize = pWrite - m_pRead;
	return m_pRead;
}

void Block::MarkReadData(unsigned int nSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	unsigned int nFree = GetCanReadDataSize();

	if (nSize > nFree)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "MarkReadData nSize(%d) > nFree(%d).", nSize, nFree);
		assert(false);
	}

	m_pRead += nSize;
}

unsigned int Block::ReadData(char* pDest, unsigned int nReadSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	assert(pDest != NULL && nReadSize > 0);

	unsigned int nFree = GetCanReadDataSize();
	if (nReadSize < nFree)
	{
		memcpy(pDest, m_pRead, nReadSize);
		m_pRead += nReadSize;
		return 0;
	}
	else
	{
		memcpy(pDest, m_pRead, nFree);
		m_pRead += nFree;
		return nReadSize - nFree;
	}
}

unsigned int Block::GetCanWriteDataSize()
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	if (m_pWrite > m_pTail)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "GetWriteSize m_pWrite(0x%08x) > m_pTail(0x%08x).", m_pWrite, m_pTail);
		assert(false);
	}
	
	return m_pTail - m_pWrite;
}

unsigned int Block::WriteData(char* pData, unsigned int nSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	unsigned int nFree = GetCanWriteDataSize();

	if (nSize > nFree)
	{
		memcpy(m_pWrite, pData, nFree);
		m_pWrite += nFree;
		return nSize - nFree;
	}
	else
	{
		memcpy(m_pWrite, pData, nSize);
		m_pWrite += nSize;
		return 0;
	}
}

char* Block::GetWriteBuffer(unsigned int& nFreeSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);
	nFreeSize = GetCanWriteDataSize();

	return m_pWrite;
}

void Block::MarkWriteData(unsigned int nSize)
{
	assert(m_pRead != NULL && m_pWrite != NULL);	
	unsigned int nFreeSize = GetCanWriteDataSize();

	if (nSize > nFreeSize)
	{
		WriteLog(FC_RED, STDOUT_FILE_HANDLE, "MarkWriteData nSize(%d) > nFree(%d).", nSize, nFreeSize);
		assert(false);
	}

	m_pWrite += nSize;
}

void Block::Add(Block* pNew)
{
	pNew->m_pNext = m_pNext;
	pNew->m_pPrev = this;

	m_pNext->m_pPrev = pNew;
	m_pNext = pNew;
}

void Block::Delete()
{
	m_pNext->m_pPrev = m_pPrev;
	m_pPrev->m_pNext = m_pNext;
}
