#include "2 module/5.h"

int main() {
    InputFileStream in("../file");
    OutputFileStream out("../compressed.txt");
    Encode(in, out);
    in.change_file("../compressed.txt");
    out.change_file("../recovered.txt");
    Decode(in, out);

    return 0;
}
