#ifndef VK_ALGO_5_H
#define VK_ALGO_5_H

#include <fstream>
#include <string>


typedef char byte;

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
        stream.open(file_name);
    }
    ~InputFileStream() {
        stream.close();
    }
    void change_file(const std::string& file_name) {
        stream.close();
        stream.open(file_name);
    }
    virtual bool Read(byte& value) {
        stream.get(value);
        return !stream.eof();
    }
};

class OutputFileStream: public IOutputStream {
private:
    std::ofstream stream;
public:
    OutputFileStream(const std::string& file_name) {
        stream.open(file_name);
    }
    ~OutputFileStream() {
        stream.close();
    }
    void change_file(const std::string& file_name) {
        stream.close();
        stream.open(file_name);
    }
    virtual void Write(byte value) {
        stream.put(value);
    }
    // write bit
};

#endif //VK_ALGO_5_H
