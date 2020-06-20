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

#ifndef MCPP_BINUTIL_INCLUDE_VARIABLE_LENGTH_H
#define MCPP_BINUTIL_INCLUDE_VARIABLE_LENGTH_H

#include <type_traits>

namespace mcpp::binutil {

/**
 *
 */
template<typename T>
class VariableLength {
protected:
	T value;

public:
	VariableLength() {}
	VariableLength(T value) : value(value) {}

	[[nodiscard]] T &get() noexcept {
		return value;
	}

	void set(T val) noexcept {
		value = val;
	}
};
}// namespace mcpp::binutil

#ifndef TYPE_VARINT
#define TYPE_VARINT v_int
using TYPE_VARINT = mcpp::binutil::VariableLength<int>;
#endif

#ifndef TYPE_UNISGNED_VARINT
#define TYPE_UNISGNED_VARINT v_uint
using v_uint = mcpp::binutil::VariableLength<unsigned int>;
#endif

#ifndef TYPE_VARLONG
#define TYPE_VARLONG v_long
using TYPE_VARLONG = typename mcpp::binutil::VariableLength<long>;
#endif

#ifndef TYPE_UNISGNED_VARLONG
#define TYPE_UNISGNED_VARLONG v_ulong
using TYPE_UNISGNED_VARLONG = typename mcpp::binutil::VariableLength<unsigned long>;
#endif

#endif//MCPP_BINUTIL_INCLUDE_VARIABLE_LENGTH_H
