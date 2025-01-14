//
// Copyright 2018 Autodesk, Inc.  All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
//
//

/*
VCSamples
Copyright (c) Microsoft Corporation

All rights reserved. 

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once
#include <stddef.h>

/*! From https://github.com/Microsoft/VCSamples/tree/master/VC2015Samples/_Hash_seq:\n\n
	<em>
	The internal hash function `std::_Hash_seq(const unsigned char *)`, 
	used to implement `std::hash` on some string types,
	was visible in recent versions of the Standard Library is not anymore visible (VC2017 15.3)\n\n
	</em>
	<em>
	To remove this dependency, add the header (fnv1a.hpp) to any affected code, 
	and then find and replace `_Hash_seq` by `fnv1a_hash_bytes`. 
	You'll get identical behavior to the internal implementation in `_Hash_seq`. 
	</em>
*/
inline size_t fnv1a_hash_bytes(const unsigned char* first, size_t count) {
 #if defined(_WIN64)
	static_assert(sizeof(size_t) == 8, "This code is for 64-bit size_t.");
	const size_t fnv_offset_basis = 14695981039346656037ULL;
	const size_t fnv_prime = 1099511628211ULL;

 #else /* defined(_WIN64) */
	static_assert(sizeof(size_t) == 4, "This code is for 32-bit size_t.");
	const size_t fnv_offset_basis = 2166136261U;
	const size_t fnv_prime = 16777619U;
 #endif /* defined(_WIN64) */

	size_t result = fnv_offset_basis;
	for (size_t next = 0; next < count; ++next)
		{	// fold in another byte
		result ^= (size_t)first[next];
		result *= fnv_prime;
		}
	return (result);
}
