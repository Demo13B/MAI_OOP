#pragma once

class Seven {
   private:
    unsigned char value[100];

   public:
    Seven();
    Seven(const size_t& n, const unsigned char t = 0);
    Seven(const std::initializer_list<unsigned char>& t);
    Seven(const std::string& t);

    Seven(const Seven& other);
    Seven(Seven&& other) noexcept;
    virtual ~Seven() noexcept;
};
