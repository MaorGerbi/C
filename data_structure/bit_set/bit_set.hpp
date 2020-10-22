#ifndef __BIT_SET__
#define __BIT_SET__

#include <iostream>    //std::cout 
#include <functional>  //std::bit_and
#include <cstddef>     //size_t
#include <cstring>     //memset
#include <algorithm>   //std::equal
namespace experis {

template <size_t BitSetSize>
class BitSet {
public:
	typedef unsigned char byte;
	BitSet();
	//~BitSet();= default
	//BitSet(const BitSet& a_other);= default
	//BitSet& operator=(const BitSet& a_other);= default

	void ClearAll();
	void TurnAllOn();
	void Set(size_t a_index,bool a_condition);
	void Toggle(size_t a_index);
	bool operator==(const BitSet& a_other) const;
	bool operator!=(const BitSet& a_other) const;
	BitSet& operator&=(const BitSet& a_other);
	BitSet operator&(const BitSet& a_other) const;
	BitSet& operator|=(const BitSet& a_other);
	BitSet operator|(const BitSet& a_other) const;
	BitSet& operator^=(const BitSet& a_other);
	BitSet operator^(const BitSet& a_other) const;
	bool operator[](size_t a_index) const;
	void Print() const; 
	void operator~();
	size_t CountAll() const;
    //
    void Clear(size_t a_index);
    BitSet& operator<<=(size_t a_shifts);
	/*
	add static 
	
    proxyn mystry operator[](size_t)
	b1 <<= 2
	b1 <<= 4 
    */

private:
	size_t getBitSetSize() const {return BitSetSize;}
	
private:
	static size_t numOfByte;
	static size_t setLastBit;
	byte m_BitsContainer[BitSetSize/8 + 1];	
};

//size_t BitSet<BitSetSize>::numOfByte = 8;
//size_t BitSet<BitSetSize>::setLastBit = 128;

template <size_t BitSetSize>
void BitSet<BitSetSize>::Clear(size_t a_index) {
    if ((*this)[a_index]) {
        Toggle(a_index);
    }
}

template <size_t BitSetSize>
BitSet<BitSetSize>& BitSet<BitSetSize>::operator<<=(size_t a_shifts) {
    int startIndex = 0;
    for (int i = a_shifts; i < BitSetSize; ++i) {
        if ((*this)[i] != (*this)[startIndex]) {
            Toggle(startIndex);
        }
    ++startIndex; 
    }

    for (int i = BitSetSize - 1; i > a_shifts; --i) {
        Clear(i);
    }
    return *this;
}   
		
template <size_t BitSetSize>
BitSet<BitSetSize>::BitSet() {
	memset(m_BitsContainer, 0, sizeof(m_BitsContainer));
}

template <size_t BitSetSize>
size_t BitSet<BitSetSize>::CountAll() const {
	size_t onBits = 0;
	for (int i = 0; i < BitSetSize; ++i) {
		if ((*this)[i]) {
			++onBits;
		}
	}
	return onBits;
}

template <size_t BitSetSize>
void BitSet<BitSetSize>::operator~() { 
	BitSet<BitSetSize> bitSetOn;
	bitSetOn.TurnAllOn();
	std::transform (m_BitsContainer, m_BitsContainer + sizeof(m_BitsContainer), bitSetOn.m_BitsContainer, m_BitsContainer, std::bit_xor<char>());
}

template <size_t BitSetSize>
bool BitSet<BitSetSize>::operator[](size_t a_index) const{
	unsigned char mask = 128 >> a_index % 8 ;
	return (m_BitsContainer[a_index / 8] & mask);
}

template <size_t BitSetSize>
BitSet<BitSetSize>& BitSet<BitSetSize>::operator&=(const BitSet& a_other) {
	std::transform (m_BitsContainer, m_BitsContainer + sizeof(m_BitsContainer), a_other.m_BitsContainer, m_BitsContainer, std::bit_and<char>());
	return *this;
}

template <size_t BitSetSize>
BitSet<BitSetSize> BitSet<BitSetSize>::operator&(const BitSet& a_other) const {
	BitSet<BitSetSize> res;
	std::transform (m_BitsContainer, m_BitsContainer + sizeof(m_BitsContainer), a_other.m_BitsContainer, res.m_BitsContainer, std::bit_and<char>());
	return res;
}

template <size_t BitSetSize>
BitSet<BitSetSize>& BitSet<BitSetSize>::operator|=(const BitSet& a_other) {
	std::transform (m_BitsContainer, m_BitsContainer + sizeof(m_BitsContainer), a_other.m_BitsContainer, m_BitsContainer, std::bit_or<char>());
	return *this;
}

template <size_t BitSetSize>
BitSet<BitSetSize> BitSet<BitSetSize>::operator|(const BitSet& a_other) const{
	BitSet<BitSetSize> res;
	std::transform (m_BitsContainer, m_BitsContainer + sizeof(m_BitsContainer), a_other.m_BitsContainer, res.m_BitsContainer, std::bit_or<char>());
	return res;
}

template <size_t BitSetSize>
BitSet<BitSetSize>& BitSet<BitSetSize>::operator^=(const BitSet& a_other) {
	std::transform (m_BitsContainer, m_BitsContainer + sizeof(m_BitsContainer), a_other.m_BitsContainer, m_BitsContainer, std::bit_xor<char>());
}

template <size_t BitSetSize>
BitSet<BitSetSize> BitSet<BitSetSize>::operator^(const BitSet& a_other) const{
	BitSet<BitSetSize> res;
	std::transform (m_BitsContainer, m_BitsContainer + sizeof(m_BitsContainer), a_other.m_BitsContainer, res.m_BitsContainer, std::bit_xor<char>());
	return res;
}

template <size_t BitSetSize>
bool BitSet<BitSetSize>::operator==(const BitSet& a_other) const {
	return BitSetSize == a_other.getBitSetSize() && std::equal (m_BitsContainer, m_BitsContainer + sizeof(m_BitsContainer), a_other.m_BitsContainer);
}

template <size_t BitSetSize>
bool BitSet<BitSetSize>::operator!=(const BitSet& a_other) const {
	return !(*this == a_other);
}

template <size_t BitSetSize>
void BitSet<BitSetSize>::ClearAll() {
	memset(m_BitsContainer, 0, sizeof(m_BitsContainer));
}

template <size_t BitSetSize>
void BitSet <BitSetSize>::TurnAllOn() { 
	memset(m_BitsContainer, 255, sizeof(m_BitsContainer));
}

template <size_t BitSetSize>
void BitSet<BitSetSize>::Toggle(size_t a_index) {
	if (a_index <= BitSetSize) {
		unsigned char mask = 128 >> a_index % 8;
		m_BitsContainer[a_index / 8] ^= mask;
	}
}

template <size_t BitSetSize>
void BitSet<BitSetSize>::Set(size_t a_index,bool a_condition) {
	if (a_index < BitSetSize) {
		unsigned char mask = 128 >> a_index % 8;
		if (a_condition) {
			m_BitsContainer[a_index / 8] |= mask;
		}
		else {
			m_BitsContainer[a_index / 8] &= ~mask;
		}
	}
}

template <size_t BitSetSize>
void BitSet<BitSetSize>::Print() const {
	for (int i = 0; i < BitSetSize; ++i) {
		unsigned char mask = 128 >> i % 8 ;
		if (m_BitsContainer[i / 8] & mask) {
			std::cout << 1;
		}
		else {
			std::cout << 0;
		}
	}
	std::cout << "\n";
}

#endif //__BIT_SET__

}// experis
