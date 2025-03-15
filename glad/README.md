# [GLAD][glad] - Auto-Generated OpenGL Bindings

## What's This

[OpenGL][opengl] is a powerful graphics library used for rendering 2D and 3D graphics. However, there is no single, canonical OpenGL library. Each GPU vendor (like NVIDIA, AMD, or Intel) implements OpenGL in their own way. This means that the functions you need to call to use OpenGL can vary depending on the user's system.

[GLAD][glad] is an OpenGL loader that helps you manage these differences. It provides bindings that allow your code to call the correct OpenGL functions for the user's system, regardless of which GPU vendor's implementation is being used. This makes it much easier to write portable OpenGL code that works across different systems and hardware configurations.

[glad]: https://github.com/Dav1dde/glad?tab=readme-ov-file
[opengl]: https://en.wikipedia.org/wiki/OpenGL