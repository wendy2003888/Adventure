#include "png.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int PNG_SIG_LEN = 8;


bool Validate(istream* is) {

    png_byte pngsig[PNG_SIG_LEN];

    is->read((char*)pngsig, PNG_SIG_LEN);

    return !png_check_sig(pngsig, PNG_SIG_LEN);
}

void ReadFromBuffer(png_structp png_ptr, png_bytep data, png_size_t len) {
    png_voidp png_io = png_get_io_ptr(png_ptr);
    ((istream*)png_io)->read((char*)data, len);
}

int main() {
    const string file_path = "./0_cat.png";
    std::ifstream file(file_path, ifstream::binary | ifstream::ate);
    int size = file.tellg();
    file.seekg(0, std::ifstream::beg);

    vector<char> buffer(size);
    if (file.read(buffer.data(), size)) {
        stringstream ss(string(buffer.begin(), buffer.end()));

        if (Validate(&ss)) {
            std::cerr << "Not valid png image" << std::endl;
            return 0;
        }

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
          NULL);
        if (!png_ptr)
            return 0;

        png_infop info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) {
            png_destroy_read_struct(&png_ptr, NULL, NULL);
            return 0;
        }

        png_set_read_fn(png_ptr, (png_voidp)&ss, ReadFromBuffer); // for stream

        png_set_sig_bytes(png_ptr, PNG_SIG_LEN);

        png_read_info(png_ptr, info_ptr);

        png_uint_32 img_w =  png_get_image_width(png_ptr, info_ptr);
        png_uint_32 img_h = png_get_image_height(png_ptr, info_ptr);

        cout<<img_w<<" "<<img_h<<endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    }
    return 0;
}
