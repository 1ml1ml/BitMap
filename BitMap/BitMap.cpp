#include "BitMap.h"

BitMap::BitMap(size_t nSize, const std::initializer_list<num_type>& initList)
{
	size_t nCapacity = nSize / m_nRowBit;
	if(0 != nCapacity && nullptr != __initPtr(++nCapacity))
	{ for(const num_type& nNum : initList) { set(nNum); } }
}

BitMap::~BitMap()
{
	__releasePtr();
}

BitMap::BitMap(const BitMap& other)
{
	*this = other;
}

BitMap::BitMap(BitMap&& other) noexcept
{
	m_ptr = other.m_ptr;
	m_nCapacity = other.m_nCapacity;

	other.m_ptr = nullptr;
	other.m_nCapacity = 0;
}

BitMap& BitMap::operator=(const BitMap& other)
{
	if (nullptr != __reInitPtr(other.m_nCapacity))
	{
		try { for (size_t nI = 0; nI < m_nCapacity; new(&m_ptr[nI]) num_type(other.m_ptr[nI++])); }
		catch (...) { __releasePtr(); }
	}
	return *this;
}

bool BitMap::operator==(const BitMap& other)
{
	if (m_ptr == other.m_ptr) { return true; }
	if (nullptr == m_ptr || nullptr == other.m_ptr) { return false; }

	for (size_t nI = 0, nCapacity = m_nCapacity > other.m_nCapacity ? m_nCapacity : other.m_nCapacity; nI < nCapacity; nI++) 
	{ if (m_ptr[nI] != other.m_ptr[nI]) { return false; } }
	return true;
}

bool BitMap::operator!=(const BitMap& othre)
{
	return !(*this == othre);
}

void BitMap::set(num_type nNum)
{
	*(m_ptr + __row(nNum)) |= 1 << __line(nNum);
}

void BitMap::reset(num_type nNum)
{
	*(m_ptr + __row(nNum)) &= ~(1 << __line(nNum));
}

bool BitMap::test(num_type nNum)
{
	return 0 != (*(m_ptr + __row(nNum)) & (1 << __line(nNum)));
}

void BitMap::resetAll()
{
	__reInitPtr(m_nCapacity);
}

inline size_t BitMap::capacity()
{
	return m_nCapacity;
}

inline unsigned long long BitMap::max()
{
	return m_nMax;
}

inline size_t BitMap::__row(num_type nNum)
{
	return nNum / m_nRowBit;
}

inline unsigned short BitMap::__line(num_type nNum)
{
	return nNum % m_nRowBit;
}

BitMap::uint8bit* BitMap::__initPtr(size_t nCapacity)
{
	m_ptr = (0 != (m_nCapacity = nCapacity) ? __initPtrHelper(m_nCapacity) : nullptr);
	m_nMax = (unsigned long long)m_nCapacity * m_nRowBit;
	return m_ptr;
}

BitMap::uint8bit* BitMap::__initPtrHelper(size_t nCapacity)
{
	return static_cast<uint8bit*>(::operator new(m_nCapacity));
}

void BitMap::__releasePtr()
{
	m_nCapacity = 0;
	__releasePtrHelper();
}

void BitMap::__releasePtrHelper()
{
	if (nullptr != m_ptr) { ::operator delete(m_ptr); }
}

BitMap::uint8bit* BitMap::__reInitPtr(size_t nCapacity)
{
	__releasePtr();
	return __initPtr(nCapacity);
}
