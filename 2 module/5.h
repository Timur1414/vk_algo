#ifndef VK_ALGO_5_H
#define VK_ALGO_5_H

#include <fstream>
#include <string>


typedef unsigned char byte;

class IInputStream {
public:
    // Возвращает false, если поток закончился
    virtual bool Read(byte& value) = 0;
};

class IOutputStream {
public:
    virtual void Write(byte value) = 0;
};

void Encode(IInputStream&, IOutputStream&);

void Decode(IInputStream&, IOutputStream&);


class InputFileStream: public IInputStream {
private:
    std::ifstream stream;
public:
    InputFileStream(const std::string& file_name) {
        stream.open(file_name, std::ios::binary);
    }
    ~InputFileStream() {
        stream.close();
    }
    void change_file(const std::string& file_name) {
        stream.close();
        stream.clear();
        stream.open(file_name, std::ios::binary);
    }
    virtual bool Read(byte& value) {
        char tmp;
        if (!stream.get(tmp)) {
            return false;
        }
        value = static_cast<unsigned char>(tmp);
        return true;

        // if (!stream.get(value))
        //     return false;
        // return true;

        // stream.get(value);
        // return !stream.eof();
    }
};

class OutputFileStream: public IOutputStream {
private:
    std::ofstream stream;
public:
    OutputFileStream(const std::string& file_name) {
        stream.open(file_name, std::ios::binary);
    }
    ~OutputFileStream() {
        stream.close();
    }
    void change_file(const std::string& file_name) {
        stream.close();
        stream.clear();
        stream.open(file_name, std::ios::binary);
    }
    virtual void Write(byte value) {
        char c = static_cast<char>(value);
        stream.put(c);

        // stream.put(value);
    }
    // write bit
};

#endif //VK_ALGO_5_H
