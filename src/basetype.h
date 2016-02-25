//-------------------------------------------------------------------------------------------------
//	Created:	2015-8-17   19:57
//	File Name:	basetype.h
//	Author:		Eric(沙鹰)
//	PS:			如果发现说明错误，代码风格错误，逻辑错问题，设计问题，请告诉我。谢谢！
//				Please to send me Email if you find any bug, better code design, etc.
//  Email:		frederick.dang@gmail.com
//	Purpose:	统一linux和windows的类型
//-------------------------------------------------------------------------------------------------
#ifdef linux 
typedef unsigned long	DWORD;
typedef	unsigned short	WORD;
typedef int				BOOL;
#endif // linux