/*******************************************************************************
        Copyright(C) 2016~2026, Free software engineer and contributor
 *******************************************************************************
  Filename   : base/source_info.cpp
  Author     : cqli[lichangqing1983@sina.com]
  Date       : 2016-05-19
  Description: 
  History    : 
*******************************************************************************/

#include "ufc/base/source_info.hpp"
#include <cstring>

namespace ufc {

	inline void source_info::init()
    {
    	std::memset(_file, 0, sizeof(_file));
    	_line = 0;
    	std::memset(_function, 0, sizeof(_function));
    }

	source_info::source_info()
    {
    	init();
    }

	source_info::source_info(const source_info& rhs)
    {
    	init();
    	std::strncpy(_file, rhs._file, sizeof(_file) - 1);
    	_line = rhs._line;
    	std::strncpy(_function, rhs._file, sizeof(_function) - 1);
    }

	source_info::source_info(const char* __file, uint32_t __line, const char* __function)
    {
    	init();
    	if (__file)
        	std::strncpy(_file, __file, sizeof(_file) - 1);
    	_line = __line;
    	if (__function)
        	std::strncpy(_function, __function, sizeof(_function) - 1);
    }

	source_info::~source_info()
    {
    }

	source_info& source_info::operator = (const source_info& __other)
    {
    	if (&__other != this)
        {
        	init();
        	std::strncpy(_file, __other._file, sizeof(_file) - 1);
        	_line = __other._line;
        	std::strncpy(_function, __other._file, sizeof(_function) - 1);
        }
    	return *this;
    }

	const char* source_info::file() const
    {
    	return _file;
    }

	uint32_t source_info::line() const
    {
    	return _line;
    }

	const char* source_info::function() const
    {
    	return _function;
    }

}//namespace ufc
