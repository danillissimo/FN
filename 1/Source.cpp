#include <iostream>
#include <unordered_map>

typedef char                     TCHAR;
typedef std::basic_string<TCHAR> string;

// Can be performed in place as doesn't require any data movement operations
string & convert_inline(string & str)
{
	constexpr TCHAR single = '(';
	constexpr TCHAR multi  = ')';

	std::unordered_map<TCHAR, TCHAR> replacements;
	// Can pontentiley perform some sweet capacity reservation here,
	// reducing number of reallocations and hash collisions

	for (TCHAR ch : str)
	{
		auto replacement = replacements.find(ch);
		if (replacement != replacements.end( ))
		{
			replacement->second = multi;
		}
		else
		{
			replacements.insert(std::make_pair(ch, single));
		}
	}


	const size_t len = str.length( );
	for (size_t i = 0; i < len; i++)
	{
		TCHAR & ch = str[i];
		ch         = replacements[ch];
	}

	return str;
}

string && convert(const string & str)
{
	string result(str);
	convert_inline(result);
	return std::move(result);
}

int main( )
{
	const TCHAR * tests[] = { "din", "recede", "Success", "(( @" };
	for (const TCHAR * test : tests)
	{
		string str(test);
		std::cout << convert_inline(str) << std::endl;
	}

	return 0;
}
