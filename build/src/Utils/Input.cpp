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

#include "defpch.h"

#include "Utils/Input.h"
#include "Application.h"
#include "Window.h"

#include <GLFW/glfw3.h>

namespace Input
{
    bool GetKeyPress(Key key)
    {
        auto window = Application::Get().GetWindow()->GetNativeWindow();
        bool state = glfwGetKey(window, (int)key);
        return state == GLFW_PRESS;
    }

    bool GetKeyRelease(Key key)
    {
        auto window = Application::Get().GetWindow()->GetNativeWindow();
        bool state = glfwGetKey(window, (int)key);
        return state == GLFW_RELEASE;
    }

    bool GetMouseButtonPress(Key button)
    {
        auto window = Application::Get().GetWindow()->GetNativeWindow();
        bool state = glfwGetMouseButton(window, (int)button);
        return state == GLFW_PRESS;
    }

    bool GetMouseButtonRelease(Key button)
    {
        auto window = Application::Get().GetWindow()->GetNativeWindow();
        bool state = glfwGetMouseButton(window, (int)button);
        return state == GLFW_RELEASE;
    }
}