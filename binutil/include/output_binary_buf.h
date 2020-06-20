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

#ifndef MCPP_BINUTIL_INCLUDE_OUTPUT_BINARY_BUF_H
#define MCPP_BINUTIL_INCLUDE_OUTPUT_BINARY_BUF_H

#include <sstream>

#include "variable_length.h"

namespace mcpp::binutil {

class OutputBinaryBuf : public std::basic_ostringstream<char> {
public:

	template<typename T,
		typename std::enable_if<std::is_integral<T>::value>::type * = nullptr,
		typename std::enable_if<!std::is_pointer<T>::value>::type * = nullptr>
	void write(T value) noexcept {
		basic_ostringstream::write(reinterpret_cast<char *>(&value), sizeof(T));
	}

	template<typename T,
		typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr,
		typename std::enable_if<!std::is_pointer<T>::value>::type * = nullptr>
	void write(T value) noexcept {
		basic_ostringstream::write(reinterpret_cast<char *>(&value), sizeof(T));
	}

	void write(v_int &value) {
		unsigned int v = static_cast<unsigned int>(value.get());
		v_uint temp;
		temp.set(static_cast<unsigned int>((v << 1) ^ (v >> 31)));
		write(temp);
	}

	void write(v_uint &value) {
		unsigned int v = value.get();
		for (unsigned int i = 0; i < 5; ++i) {
			if ((v >> 7) != 0) {
				write(static_cast<char>(v | 0x80));
			} else {
				write(static_cast<char>(v & 0x7f));
				return;
			}

			v >>= 7;
		}

		throw std::invalid_argument("Value too large to be encoded as a VarInt");
	}

	template<typename T>
	OutputBinaryBuf &operator<<(T val) noexcept {
		write(val);
		return *this;
	}
};

}// namespace mcpp::binutil
#endif//MCPP_BINUTIL_INCLUDE_OUTPUT_BINARY_BUF_H
