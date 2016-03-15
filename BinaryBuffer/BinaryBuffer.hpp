#ifndef BINARY_BUFFER_HPP
#define BINARY_BUFFER_HPP
#include <cstdint>
#include <ostream>

enum Endian
{
	BigEndian = 0x1, LittleEndian = 0x2
};

class BinaryBuffer
{
public:
	BinaryBuffer();
	void Append(uint8_t byte);
	void Append(uint8_t *data, size_t sz);
	template<typename T>
	void Append(T data)
	{
		if (_endian == Endian::LittleEndian)
		{
			if (_size + sizeof(data) >= _capacity)
			{
				increaseCapacity();
			}

			T *dataPtr = reinterpret_cast<T *>(&_data[_size]);
			*dataPtr = data;
			_size += sizeof(data);
		}
		else
		{
			uint8_t *byteDataPtr = reinterpret_cast<uint8_t *>(&data);
			for (size_t i = sizeof(T); i > 0; --i)
			{
				Append(byteDataPtr[i - 1]);
			}
		}
	}
	template<typename T>
	void Append(T *data, size_t sz)
	{
		for (size_t i = 0; i < sz; ++i)
		{
			Append<T>(data[i]);
		}
	}
	void SetEndian(Endian endian);
	Endian GetEndian();
	const uint8_t *Data();
	size_t Size();
	size_t Capacity();
	friend std::ostream &operator<<(std::ostream &stream, BinaryBuffer &data);

private:
	uint8_t *_data;
	size_t _capacity;
	size_t _size;
	Endian _endian;

	static const size_t _defaultCapacity = 64U;

	void increaseCapacity();

};

#endif // BINARY_BUFFER_HPP
