#pragma once

#include <algorithm>
#include "MintLib.h"

namespace MintLib {

    void strcpy(char* dest, const char* src);
    void strcat(char* dest, const char* src);
    bool strcmp(const char* lhs, const char* rhs);

    template <class T>
    T&& move(T&& t) {
        return static_cast<T&&>(t);
    }

    class char_traits { // char
    public:
        static void
            assign(char& lhs, const char& rhs);

        static bool
            eq(const char& lhs, const char& rhs);

        static bool
            lt(const char& lhs, const char& rhs);

        static int
            compare(const char* lhs, const char* rhs, std::size_t);

        static std::size_t
            length(const char* str);

        static const char*
            find(const char* str, std::size_t n, const char& a);

        static char*
            move(char* dest, const char* src);

        static char*
            copy(char* dest, const char* src);

        static char*
            assign(char* s, size_t n, const char& symbol);

    };

    template<class T = char, class Traits = MintLib::char_traits, class Alloc = MintLib::allocator<T>>
    class String {
    private:
        size_t _size_ = 0;  // size without '\0'
        size_t _capacity_ = 2;
        T* _data_ = nullptr;
        Alloc alloc;

    public:
        class Iterator {
        private:
            T* current_element = _data_;

        public:
            Iterator(T* first_element) : current_element(first_element) {}
            
            T& operator+(const int& n) { return *(current_element + n); }
            T& operator-(const int& n) { return *(current_element - n); }
            
            T& operator++() { return *++current_element; }
            T& operator--() { return *--current_element; }
            T& operator++(int) { return *current_element++; }
            T& operator--(int) { return *current_element--; }

            T& operator*() { return *current_element; }

            bool operator != (const Iterator& rhs) const {
                return current_element != rhs.current_element;
            }
            bool operator == (const Iterator& rhs) const {
                return current_element == rhs.current_element;
            }
        };

        String() {
            _data_ = alloc.allocate(_capacity_);
            _data_[0] = '\0';
        }

        String(const char* str) {
            size_t str_len = strlen(str);
            _data_ = alloc.allocate(str_len + 1);
            MintLib::strcpy(_data_, str);
            _size_ = str_len;
            _capacity_ = str_len + 1;
        }

        String(const String<>& str) {
            _size_ = str._size_;
            _capacity_ = str._capacity_;
            _data_ = alloc.allocate(_capacity_);
            _data_ = Traits::copy(_data_, str._data_);
        }

        ~String() {
            alloc.deallocate(_data_, _capacity_);
            _data_ = nullptr;
            _size_ = 0;
            _capacity_ = 2;
        }

        T* data() const { return _data_; }

        size_t size() const { return _size_; }

        size_t length() const { return _size_; }

        String& operator=(const MintLib::String<>& str) {
            _data_ = Traits::move(_data_, str._data_);
            _size_ = strlen(_data_);
            _capacity_ = _size_ + 1;
            return *this;
        }

        String& operator=(const char* str) {
            _data_ = Traits::move(_data_, str);
            _size_ = strlen(_data_);
            _capacity_ = _size_ + 1;
            return *this;
        }

        String& assign(size_t count, char ch) {
            if (_size_ < count) {
                alloc.deallocate(_data_, _size_);
                _data_ = alloc.allocate(count);
                _capacity_ = count;
            }
            Traits::assign(_data_, count, ch);
            return *this;
        }

        char& operator[](size_t pos) {
            return _data_[pos];
        }

        String<>& operator += (const String<>& str) {
            int str_cap = str._capacity_;
            int str_size = str._size_;
            char* buffer = alloc.allocate(str_cap + this->_capacity_);
            MintLib::strcpy(buffer, _data_);
            MintLib::strcat(buffer, str._data_);
            _data_ = buffer;
            _size_ = str_size + this->_size_;
            _capacity_ = str_cap + this->_capacity_;
            alloc.deallocate(buffer, _capacity_);
            return *this;
        }

        String<>& operator += (const T* str) {
            int str_size = strlen(str);
            int str_cap = str_size + 1;
            char* buffer = alloc.allocate(str_cap + this->_capacity_);
            MintLib::strcpy(buffer, _data_);
            MintLib::strcat(buffer, str);
            _data_ = buffer;
            _size_ = str_size + this->_size_;
            _capacity_ = str_cap + this->_capacity_;
            alloc.deallocate(buffer, _capacity_);
            return *this;
        }

        void push_back(const T& ch) {
            char* new_data = nullptr;
            if (_size_ + 1 >= _capacity_) {
                new_data = alloc.allocate(_capacity_ * 2 + 1);
                MintLib::strcpy(new_data, _data_);
                _data_ = new_data;
                _capacity_ <<= 1;
            }
            _data_[_size_++] = ch;
            _data_[_size_] = '\0';
        }


        String<>& operator += (const T& symbol) {
            push_back(symbol);
            return *this;
        }


        char& back() {
            return _data_[_size_ - 1];
        }

        bool empty() const{
            return !_size_;
        }

        String::Iterator begin() const {
            return _data_;
        }
        
        String::Iterator end() const {
            return _data_ + _size_;
        }


        friend std::istream& operator>>(std::istream& in, String<>& str);
        friend std::ostream& operator<<(std::ostream& out, const String<>& str);
       
    };

    std::istream& operator>> (std::istream& in, String<>& str);
    
    std::ostream& operator<< (std::ostream& out, const String<>& str);

    using string = String<>;

    std::istream& getline(std::istream& in, MintLib::string& dest);

}

MintLib::string operator +(MintLib::string lhs, const MintLib::string rhs);
MintLib::string operator +(MintLib::string lhs, const char* rhs);
MintLib::string operator +(const char* lhs, const MintLib::string rhs);
bool operator != (const MintLib::string& lhs, const MintLib::string& rhs);
bool operator == (const MintLib::string& lhs, const MintLib::string& rhs);
