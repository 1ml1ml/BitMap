#ifndef __BITMAP__TMJ__2022_3_6
#define __BITMAP__TMJ__2022_3_6

#include <iostream>
#include <initializer_list>

class BitMap
{
	using uint8bit = unsigned char;
	using num_type = size_t;
public:
	BitMap(size_t nSize = 0, const std::initializer_list<num_type>& initList = std::initializer_list<num_type>());
	~BitMap();

	BitMap(const BitMap& other);
	BitMap(BitMap&& other) noexcept;

	BitMap& operator=(const BitMap& other);
	bool operator==(const BitMap& other);
	bool operator!=(const BitMap& othre);

public:
	//向位图中添加一个数
	//输入:nNUm
	//输出:无
	//返回:无
	void set(num_type nNum);

	//从位图中移除一个数
	//输入:nNUm
	//输出:无
	//返回:无
	void reset(num_type nNum);

	//判断一个数是否在位图中
	//输入:nNUm
	//输出:无
	//返回:bool 0表示不存在 1表示存在
	bool test(num_type nNum);

	//将位图全部置0
	//输入:无
	//输出:无
	//返回:无
	void resetAll();

	//获取位图所占用的存储空间
	//输入:无
	//输出:无
	//返回:size_t 内存大小
	inline size_t capacity();

	//获取位图中能存储的最大值
	//输入:无
	//输出:无
	//返回:unsigned long long 最大值
	inline unsigned long long max();

private:
	//获取数字所在行
	//输入:nNum 数字
	//输出:无
	//返回:size_t 所在行
	inline size_t __row(num_type nNum);

	//获取数字所在列
	//输入:nNum 数字
	//输出:无
	//返回:unsigned shor 所在列
	inline unsigned short __line(num_type nNum);

	//为ptr分配内存空间
	//输入:nCapacity 内存大小
	//输出:无
	//返回:uint8bit* 内存指针
	uint8bit* __initPtr(size_t nCapacity);
	uint8bit* __initPtrHelper(size_t nCapacity);

	//释放内存空间
	//输入:无
	//输出:无
	//返回:无
	void __releasePtr();
	void __releasePtrHelper();

	//为ptr重新分配内存空间
	//输入:nCapacity 内存大小
	//输出:无
	//返回:uint8it* 内存指针
	uint8bit* __reInitPtr(size_t nCapacity);

private:
	unsigned short m_nRowBit{ sizeof(uint8bit) * 8 };	//每一行的位数

	uint8bit* m_ptr = nullptr;
	size_t m_nCapacity{ 0 };
	unsigned long long m_nMax{ 0 };
};

#endif
