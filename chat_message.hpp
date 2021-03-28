//
// Created by corey on 3/12/21.
//

#ifndef DYNAMICSERV_CHAT_MESSAGE_HPP
#define DYNAMICSERV_CHAT_MESSAGE_HPP
#include <cstdio>
#include <cstdlib>
#include <cstring>


class chat_message: public std::enable_shared_from_this<chat_message> {
public:

    enum { header_length = 4 };
    enum {max_body_length = 9999 };
    std::unique_ptr<char[]> data_;

    chat_message()
            : body_length_(0)
    {
    }

    char* head() {
        return header;
    }

    std::unique_ptr<char[]>& body() {
        return data_;
    }

    std::size_t full_length() const {
        return body_length_+ header_length;
    }


    std::size_t body_length() const
    {
        return body_length_;
    }

    bool decode_header() {
        body_length_ = std::atoi(header);
        data_ = std::make_unique<char[]>(full_length());
        std::strncat(data_.get(), header, header_length);
        if (body_length_ > max_body_length)
        {
            body_length_ = 0;
            return false;
        }
        return true;
    }

private:
    std::size_t body_length_;
    char header[header_length + 1]{};
};

#endif //DYNAMICSERV_CHAT_MESSAGE_HPP
