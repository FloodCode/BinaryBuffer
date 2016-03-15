#include "BinaryBuffer.hpp"

BinaryBuffer::BinaryBuffer()
{
	_size = 0;
	_capacity = _defaultCapacity;
	_data = new uint8_t[_capacity];
	_endian = Endian::LittleEndian;
}

void BinaryBuffer::Append(uint8_t byte)
{
	if (_size == _capacity)
	{
		increaseCapacity();
	}

	_data[_size] = byte;
	_size++;
}

void BinaryBuffer::Append(uint8_t *data, size_t sz)
{
	for (size_t i = 0; i < sz; ++i)
	{
		Append(data[i]);
	}
}

void BinaryBuffer::SetEndian(Endian endian)
{
	_endian = endian;
}

Endian BinaryBuffer::GetEndian()
{
	return _endian;
}

const uint8_t *BinaryBuffer::Data()
{
	return _data;
}

size_t BinaryBuffer::Size()
{
	return _size;
}

size_t BinaryBuffer::Capacity()
{
	return _capacity;
}

std::ostream &operator<<(std::ostream &os, BinaryBuffer &data)
{
	os << std::hex;
	for (size_t i = 0; i < data._size; ++i)
	{
		if (data._data[i] < 0x10)
		{
			os << '0';
		}

		os << static_cast<size_t>(data._data[i]) << " ";
	}
	os << std::dec;

	return os;
}

void BinaryBuffer::increaseCapacity()
{
	uint8_t *oldData = _data;
	_data = new uint8_t[_capacity * 2];

	for (size_t i = 0; i < _capacity; i++)
	{
		_data[i] = oldData[i];
	}

	delete[] oldData;
	_capacity *= 2;
}