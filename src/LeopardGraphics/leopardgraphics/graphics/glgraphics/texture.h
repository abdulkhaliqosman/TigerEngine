#pragma once

class Texture
{
public:
	Texture();
	Texture(const char* path);
	~Texture();

	void Load(const char* path);
	void Set(unsigned int uniform, unsigned int texIndex);
	void UnSet(unsigned int textureIndex);
	unsigned int GetHandle();

private:
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int mChannels;
	unsigned int mHandle;

	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;

};