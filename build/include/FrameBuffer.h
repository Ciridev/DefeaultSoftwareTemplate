// | MIT License
// | 
// | Copyright (c) 2022 Ciridev
// | 
// | Permission is hereby granted, free of charge, to any person obtaining a copy
// | of this software and associated documentation files (the "Software"), to deal
// | in the Software without restriction, including without limitation the rights
// | to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// | copies of the Software, and to permit persons to whom the Software is
// | furnished to do so, subject to the following conditions:
// | 
// | The above copyright notice and this permission notice shall be included in all
// | copies or substantial portions of the Software.
// | 
// | THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// | IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// | FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// | AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// | LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// | OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// | SOFTWARE.

#pragma once

#include <glad/glad.h>

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void Resize(unsigned int width, unsigned int height);

	void Enable() const { glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId); 	glViewport(0, 0, m_Width, m_Height);}
	void Disable() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	unsigned int GetColorAttachment() const { return m_ColorAttachmentId; }
	
	void DeleteColorAttachment() { glDeleteTextures(1, reinterpret_cast<unsigned int*>(&m_ColorAttachmentId)); }

	void Invalidate();

private:
	unsigned int m_FrameBufferId = 0;
	unsigned int m_ColorAttachmentId = 0;
	unsigned int m_Width = 0, m_Height = 0;

	friend class Renderer;
};