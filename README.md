AnyFX
=====

AnyFX is an effects library which uses unified programming API for handling shaders implemented in any underlying shading language.

AnyFX is a programming language, but also not that it's not a shading language by itself. AnyFX operates by defining what one could call a padding, around which actual HLSL/GLSL shader code is written. The language specification can be found in the repository and is called 'anyfx spec.pdf'.

In its current state, AnyFX is designed as an OpenGL alternative to the Microsoft Effects library used for DirectX, using the same principles of defining multiple shaders, render states, variables and program objects in a single file, which is then compiled and easily accessed in an application. 


AnyFX also uses CMake to setup the project, and is fully implemented in C/C++. 

AnyFX uses the following libraries (all of which are included), all of which follows either the BSD or GNU lesser general license:

mcpp
antlr3c
glew

The AnyFX demo project (which is optional) also uses:

DevIL
glm

AnyFX is split into two major parts, the compiler and the API. The compiler will take one AnyFX formatted effect file and output a binary blob which can then be read by the API. The API then provides a simple interface to use the resources generated from the effect. 

OpenGL 4
=====
AnyFX is extremely high performant using OpenGL4, using the latest APIs which enables variable updates to be done without glUniform* and thus asynchronously with the draw calls. It also enables a state switch system which guarantees no state gets changed to its current state without using glGet*. It also enables shader program variations without the extensive use of glUseProgram through the functionality of subroutines.


Setup
====

AnyFX can be setup in different ways. When running CMake, you will see four variables. These are:

ANYFX_BUILD_COMPILER_LIBRARY
ANYFX_BUILD_DEMO
ANYFX_BUILD_GRAMMAR
ANYFX_TRANSPOSE_MATRICES

The ANYFX_BUILD_COMPILER_LIBRARY will switch if the compiler should build as its own application, or be a library which you can link to your own application and use. When using the compiler as a library, you simply include the contained anyfxcompiler.h in your software.

The ANYFX_BUILD_DEMO will build an included demo project, which features a set of default GLSL shaders as well as an AnyFX example called demo.fx, which utilizes most AnyFX features.

The ANYFX_BUILD_GRAMMAR will detect any changes in the AnyFX.g ANTLR grammar file, and will trigger a rebuild of the entire ANTLR lexer and parser. Switch this to ON if you wish to experiment with the language syntax.

The ANYFX_TRANSPOSE_MATRICES is deprecated and will be removed soon. 

If you wish to put AnyFX in any folder like structure in your project, just set the ANYFX_FOLDER variable to your folder name. 

Features
====

AnyFX is currently platform independent, although it lacks support for DirectX and HLSL at its current state. So note that AnyFX is currently only implemented for OpenGL, and currently is focused on OpenGL 4.0+ support, meaning there is no direct (as of yet) backwards compatibility with earlier versions of OpenGL, OpenGLES or GLSL. The language specification is defined in the _anyfx\_spec.pdf_ file included in the repository.

AnyFX supports the following GLSL features:
- Vertex and fragment shaders.
- Hull/domain and geometry shaders.
- Compute shaders.
- Offline compilation and validation. (but not using program binaries)
- Cross-shader variables.
- Uniform blocks.
- Subroutines.

And the following OpenGL features:
- Sampler objects.
- Render states.
- Program assembly.
- Per-program variable usage.
- Uniform buffers:
  - Persistently mapped uniform buffers.  
  - Explicitly synced or implicitly synced dependent on need.
  - Multiple buffering to avoid stalls.
  - Application global uniform block sharing.
- Incremental state update.

AnyFX is completely incremental. This means AnyFX will never perform a state change unless it actually changes the OpenGL state (by always keeping a copy of the state in memory, not by calling glGet* each frame). This ensures redundant state changes never happen, although AnyFX cannot optimize the order in which state switches occur. 
