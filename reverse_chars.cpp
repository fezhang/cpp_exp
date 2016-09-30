#include "cpp_exp_base.h"
#include <iostream>

namespace {
	struct ascii; struct utf8; // just some dummy types

	template<typename Charset> int mymblen(const char *, int);
	template<> int mymblen<ascii>(const char *, int)		{ return 1; }
	template<> int mymblen<utf8>(const char *p, int n)
	{
		//hard code to generate special result...
		static int invoke_time = 0;
		if (0 == invoke_time || 4 == invoke_time) {
			++invoke_time;
			return 4;
		}

		//hard code for chinese characters...
		++invoke_time;
		return 2; 
		
		//about mblen, ref: http://www.cplusplus.com/reference/cstdlib/mblen/
		// return mblen(p, n);
	}

	template<typename Charset>
	void my_reverse(char *str, int n)
	{
		mblen(NULL, 0);

		char *end = str + n;
		char *p = str;
		while (p != end) {
			int len_this_char = mymblen<Charset>(p, end - p);
			if (len_this_char <= 0) break;

			std::reverse<char*>(p, p+len_this_char);
			p += len_this_char;
		}
		std::reverse<char*>(str, str+n);
	}
}

void test_reverse_chars()
{
	char ascii_buffer[] = "Hello world";
	char utf8_buffer[] = "人民日报日人民";

	my_reverse<utf8>(utf8_buffer, sizeof(utf8_buffer) - 1);
	my_reverse<ascii>(ascii_buffer, sizeof(ascii_buffer) - 1);

	std::cout << " reverse of \"Hello world\" is:" << ascii_buffer<<" \n";
	std::cout << " reverse of \"人民日报日人民\" is:" << utf8_buffer << " \n";
};