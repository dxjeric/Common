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
class deque
{
public:
	deque();
	~deque();

public:
	// 获取下一个元素
	// get the next element
	T*	GetNext();
	// 获取前一个元素
	// get the previous element
	T*	GetPrev();

	// 添加一个元素
	// add new element
	void Add(T* pNew);

	// 删掉一个元素
	// 删除当前元素
	// delete current element
	void Remove();
	// 删除指定元素
	// delete specific element pDel
	void Remove(T* pDel);

private:
	T*	m_pNext;
	T*	m_pPrev;
};