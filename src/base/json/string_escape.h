// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file defines utility functions for escaping strings suitable for JSON.

#ifndef BASE_JSON_STRING_ESCAPE_H_
#define BASE_JSON_STRING_ESCAPE_H_

#include <string>
#include <string_view>

namespace base {

// Appends to |dest| an escaped version of |str|. Valid UTF-8 code units and
// characters will pass through from the input to the output. Invalid code
// units and characters will be replaced with the U+FFFD replacement character.
// This function returns true if no replacement was necessary and false if
// there was a lossy replacement. On return, |dest| will contain a valid UTF-8
// JSON string.
//
// Non-printing control characters will be escaped as \uXXXX sequences for
// readability.
//
// If |put_in_quotes| is true, then a leading and trailing double-quote mark
// will be appended to |dest| as well.
void EscapeJSONString(std::string_view str,
                      bool put_in_quotes,
                      std::string* dest);

// Performs a similar function to the UTF-8 std::string_view version above,
// converting UTF-16 code units to UTF-8 code units and escaping non-printing
// control characters. On return, |dest| will contain a valid UTF-8 JSON string.
void EscapeJSONString(std::u16string_view str,
                      bool put_in_quotes,
                      std::string* dest);

// Given an arbitrary byte string |str|, this will escape all non-ASCII bytes
// as \uXXXX escape sequences. This function is *NOT* meant to be used with
// Unicode strings and does not validate |str| as one.
//
// CAVEAT CALLER: The output of this function may not be valid JSON, since
// JSON requires escape sequences to be valid UTF-16 code units. This output
// will be mangled if passed to to the base::JSONReader, since the reader will
// interpret it as UTF-16 and convert it to UTF-8.
//
// The output of this function takes the *appearance* of JSON but is not in
// fact valid according to RFC 4627.
std::string EscapeBytesAsInvalidJSONString(std::string_view str,
                                           bool put_in_quotes);

}  // namespace base

#endif  // BASE_JSON_STRING_ESCAPE_H_
