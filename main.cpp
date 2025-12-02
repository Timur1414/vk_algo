#include "2 module/5.h"

int main() {
    InputFileStream in("../file");
    OutputFileStream out("../compressed");
    Encode(in, out);
    in.change_file("../compressed");
    out.change_file("../recovered");
    Decode(in, out);

    return 0;
}
