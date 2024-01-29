#ifndef UTF8_STRING
#define UTF8_STRING

namespace UTF8
{

	using ios = std::basic_ios<char8_t, std::char_traits<char8_t>>;
	using streambuf = std::basic_streambuf<char8_t, std::char_traits<char8_t>>;
	using istream = std::basic_istream<char8_t, std::char_traits<char8_t>>;
	using ostream = std::basic_ostream<char8_t, std::char_traits<char8_t>>;
	using iostream = std::basic_iostream<char8_t, std::char_traits<char8_t>>;
	using stringbuf = std::basic_stringbuf<char8_t, std::char_traits<char8_t>, allocator<char8_t>>;
	using istringstream = std::basic_istringstream<char8_t, std::char_traits<char8_t>, allocator<char8_t>>;
	using ostringstream = std::basic_ostringstream<char8_t, std::char_traits<char8_t>, allocator<char8_t>>;
	using stringstream = std::basic_stringstream<char8_t, std::char_traits<char8_t>, allocator<char8_t>>;
	using filebuf = std::basic_filebuf<char8_t, std::char_traits<char8_t>>;
	using ifstream = std::basic_ifstream<char8_t, std::char_traits<char8_t>>;
	using ofstream = std::basic_ofstream<char8_t, std::char_traits<char8_t>>;
	using fstream = std::basic_fstream<char8_t, std::char_traits<char8_t>>;
}

#endif // ! UTF8_STRING
