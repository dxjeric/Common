//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-25   11:04
//	File Name:	deque.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	
//-------------------------------------------------------------------------------------------------
template<class T>
class deque_node
{
public:
	deque_node()
	{
		m_pNext = NULL;
		m_pPrev = NULL;
	};
	~deque_node()
	{
		m_pNext = NULL;
		m_pPrev = NULL;
	};
public:
	T*	m_pNext;
	T*	m_pPrev;
};