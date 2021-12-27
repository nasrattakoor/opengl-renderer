//#pragma once
//
//#include "Renderer.h"
//#include "vendor/stb_image/stb_image.h"
//
//class Texture
//{
//public:
//	Texture(const std::string& path)
//		: filePath(path)
//	{
//		// create texture and bind 
//		GLCall(glGenTextures(1, &id));
//		GLCall(glBindTexture(GL_TEXTURE_2D, id));
//
//		// stores out image upside down
//		// in OpenGL, (0,0) is the bottom left. Typically, including with the PNG format, images are written from the top left of the image. If your texture's upside down, just play with this flag.
//		stbi_set_flip_vertically_on_load(1);
//		
//		// load image
//		localBuffer = stbi_load(filePath.c_str(), &width, &height, &bytesPerPixel, 4 /* r-g-b-a */);
//
//		// you must set these 4 parameters
//		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
//		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
//
//		// send our pixel data to the GPU
//		GLCall(glTexImage2D(
//			GL_TEXTURE_2D,
//			0, 
//			GL_RGBA8, 			// internal format - how OpenGL will store the pixel data
//			width, height, 
//			0,					// border
//			GL_RGBA,			// format of data we're providing
//			GL_UNSIGNED_BYTE,	// type of each pixel element
//			localBuffer 		// you can pass nullptr if you just want to allocate space for it
//		));
//
//		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
//
//		// deallocate CPU-side pixel buffer
//		if (localBuffer)
//			stbi_image_free(localBuffer);
//	}
//
//	//
//	void Bind(unsigned int slot = 0) const
//	{
//		// the active texture is the current slot that OpenGL will bind textures to
//		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
//		GLCall(glBindTexture(GL_TEXTURE_2D, id));
//	}
//
//	void Unbind() const
//	{
//		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
//	}
//
//	~Texture()
//	{
//		GLCall(glDeleteTextures(1, &id));
//	}
//
//private:
//	GLuint id = 0;
//	std::string filePath;
//	unsigned char* localBuffer = nullptr;
//	int width = 0;
//	int height = 0;
//	int bytesPerPixel = 0;
//};