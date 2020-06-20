/**
 * Copyright (C) NxtLvL Software Solutions
 *
 * @author Jack Noordhuis <me@jacknoordhuis.net>
 * @copyright NxtLvL Software Solutions
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 *
 */

#ifndef MCPP_BINUTIL_INCLUDE_INPUT_BINARY_BUF_H
#define MCPP_BINUTIL_INCLUDE_INPUT_BINARY_BUF_H

#include <sstream>

#include "variable_length.h"

namespace mcpp::binutil {

class InputBinaryBuf : public std::basic_istringstream<char> {
public:
	/**
	 * Read the value of a basic type from the stream into the given parameter by reference.
	 *
	 * @tparam T Type of the data we are reading.
	 * @param value By-ref param where data will be copied into.
	 */
	template<typename T,
	         typename std::enable_if<std::is_integral<T>::value>::type * = nullptr,
	         typename std::enable_if<!std::is_pointer<T>::value>::type * = nullptr>
	void read(T &value) noexcept {
		basic_istringstream::read(reinterpret_cast<char *>(&value), sizeof(T));
	}

	/**
	 * Read the value of a basic type from the stream into the given parameter by reference.
	 *
	 * @tparam T Type of the data we are reading.
	 * @param value By-ref param where data will be copied into.
	 */
	template<typename T,
		typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr,
		typename std::enable_if<!std::is_pointer<T>::value>::type * = nullptr>
	void read(T &value) noexcept {
		basic_istringstream::read(reinterpret_cast<char *>(&value), sizeof(T));
	}

	template<typename T>
	T read() {
		T temp;
		read(temp);
		return temp;
	}

	void read(v_int &value) {
		auto v = read<v_uint>();
		value.set(static_cast<int>((v.get() << 1) ^ (v.get() >> 31)));
	}

	void read(v_uint &value) {
		unsigned int val = value.get();
		for (unsigned int i = 0; i <= 5; ++i) {
			char v = read<char>();
			val |= static_cast<unsigned int>((v & 0x7f) << (i * 7));
			if ((v & 0x80) == 0) {
				value.set(val);
				return;
			}
		}

		throw std::invalid_argument("VarInt did not terminate after 5 bytes!");
	}

	template<typename T>
	InputBinaryBuf &operator>>(T &val) noexcept {
		read(val);
		return *this;
	}
};

}// namespace mcpp::binutil

#endif//MCPP_BINUTIL_INCLUDE_INPUT_BINARY_BUF_H
