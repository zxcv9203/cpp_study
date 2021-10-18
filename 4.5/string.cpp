#include <iostream>
#include <string.h>

class MyString {
	private:
		char *string_content;
		int string_length;
	public:
		MyString(char c);
		MyString(const char *str);
		MyString(const MyString &str);
};

MyString::MyString(char c) {
	string_content = new char[1];
	string_content[0] = c;
	string_length = 1;
}

MyString::MyString(const char *str) {
	string_length = strlen(str);
	string_content = new char[string_length];

	for (int i = 0; i != string_length; i++)
		string_content[i] = str[i];
}

MyString::MyString(const MyString &str) {
	string_length = str.string_length;
	for (int i = 0; i != string_length; i++)
		string_content[i] = str.string_content[i];
}