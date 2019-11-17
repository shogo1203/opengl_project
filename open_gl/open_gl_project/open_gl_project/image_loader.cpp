#include "image_loader.h"

ImageData* ImageLoader::Load(const char* path)
{
	ImageData image_data;
	FILE* file;
	fopen_s(&file, path, "r");
	png_colorp palette;
	png_structp png;
	png_infop info;
	png_bytep row;
	png_bytepp rows;
	png_byte sig_bytes[8];

	if (file == nullptr)
	{
		std::cerr << "failed load to file" << std::endl;
		fclose(file);
		return nullptr;
	}
	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

	if (png == nullptr)
	{
		std::cerr << "failed create to png_structp" << std::endl;
		fclose(file);
		return nullptr;
	}

	info = png_create_info_struct(png);

	if (info == nullptr)
	{
		std::cerr << "failed create to png_infop" << std::endl;
		fclose(file);
		return nullptr;
	}

	if (setjmp(png_jmpbuf(png)))
	{
		fclose(file);
		return nullptr;
	}

	png_init_io(png, file);
	png_set_sig_bytes(png, sizeof(sig_bytes));
	png_read_png(png, info, PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16, nullptr);
	image_data.width = png_get_image_width(png, info);
	image_data.height = png_get_image_height(png, info);
	std::cout << 1 << std::endl;
	std::cout << image_data.width << "," << image_data.height;

	return &image_data;
}
