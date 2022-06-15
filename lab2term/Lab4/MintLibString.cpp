#include "MintLibString.h"

void MintLib::strcpy(char* dest, const char* src) {
    while (*dest++ = *src++);
}

void MintLib::strcat(char* dest, const char* src) {
    while (*dest++);
    while (*dest++ = *src++);
}

bool MintLib::strcmp(const char* lhs, const char* rhs) {
    while (*lhs && *rhs && *lhs++ == *rhs++);
    return (int)(*lhs) - (int)(*rhs);
}

std::istream& MintLib::getline(std::istream& in, MintLib::string& dest) {
    MintLib::string tmp;
    char symbol = 0;
    while (in.get(symbol) && symbol != '\n')
        tmp += symbol;
    dest = tmp;
    return in;
}

MintLib::string operator +(MintLib::string lhs, const MintLib::string rhs) {
    lhs += rhs;
    return lhs;
}

MintLib::string operator +(MintLib::string lhs, const char* rhs) {
    lhs += rhs;
    return lhs;
}

MintLib::string operator +(const char* lhs, const MintLib::string rhs) {
    MintLib::string tmp = lhs;
    tmp += rhs;
    return tmp;
}

bool operator != (const MintLib::string& lhs, const MintLib::string& rhs) {
    return (MintLib::strcmp(lhs.data(), rhs.data()));
}

bool operator == (const MintLib::string& lhs, const MintLib::string& rhs) {
    return !(MintLib::strcmp(lhs.data(), rhs.data()));
}


std::istream& MintLib::operator>> (std::istream& in, String<>& str) {
    in >> str._data_;
    return in;
}

std::ostream& MintLib::operator<< (std::ostream& out, const String<>& str) {
    out << str._data_;
    return out;
}

#pragma region CharTraitsFunc

void MintLib::char_traits::assign(char& lhs, const char& rhs) { lhs = rhs; }

bool MintLib::char_traits::eq(const char& lhs, const char& rhs) { return lhs == rhs; }

bool MintLib::char_traits::lt(const char& lhs, const char& rhs) { return lhs < rhs; }

int MintLib::char_traits::compare(const char* lhs, const char* rhs, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        if (MintLib::char_traits::lt(lhs[i], rhs[i])) {    // lhs[i] < rhs[i]
            return -1;
        }
        else if (MintLib::char_traits::lt(rhs[i], lhs[i])) { // lhs[i] > rhs[i]
            return 1;
        }
    }
    return 0;
}

std::size_t MintLib::char_traits::length(const char* str) {
    std::size_t index = 0;
    while (str[index++]);
    return index;
}

// returns pointer to the first find character
const char* MintLib::char_traits::find(const char* str, std::size_t n, const char& a) {
    for (std::size_t i = 0; i < n; ++i) {
        if (eq(str[i], a)) {
            return str + i;
        }
    }
    return nullptr; // not found
}

char* MintLib::char_traits::move(char* dest, const char* src) {
    MintLib::allocator<char> alloc;
    size_t n = strlen(src);
    size_t dest_len = strlen(dest);
    
    if (dest_len != n) {
        alloc.deallocate(dest, dest_len);
        dest = alloc.allocate(n + 1);
    }

    for (size_t i = 0; i < n; ++i) {
        dest[i] = MintLib::move(src[i]);
    }
    dest[n] = '\0';

    return dest;
}

char* MintLib::char_traits::copy(char* dest, const char* src) {
    MintLib::strcpy(dest, src);
    return dest;
}

char* MintLib::char_traits::assign(char* s, size_t n, const char& symbol) {
    std::fill_n(s, n, symbol);
    return s;
}

#pragma endregion
