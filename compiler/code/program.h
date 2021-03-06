#pragma once
//------------------------------------------------------------------------------
/**
    @class Program
    
    A program denotes a complete set of shaders, render states and defines.
    
    (C) 2013 Gustav Sterbrant
*/
//------------------------------------------------------------------------------
#include <string>
#include <vector>
#include <map>
#include "symbol.h"
#include "renderstate.h"
#include "programrow.h"
#include "annotation.h"
#include "shader.h"
namespace AnyFX
{

class Program : public Symbol
{
public:
	/// constructor
	Program();
	/// destructor
	virtual ~Program();

	/// set annotation
	void SetAnnotation(const Annotation& annotation);
	/// consumes a single program row
	void ConsumeRow(const ProgramRow& row);

	/// type checks function linkage
	void TypeCheck(TypeChecker& typechecker);
	/// generate program
	void Generate(Generator& generator);
	/// compiles program
	void Compile(BinWriter& writer);

private:
	friend class EffectEntryPoint;

	/// constructs a shader function using the given functions
	void BuildShaders(const Header& header, const std::vector<Function>& functions, std::map<std::string, Shader*>& shaders);

#pragma region OpenGL
	/// generates GLSL4 target code
	void LinkGLSL4(Generator& typeChecker, Shader* vs, Shader* ps, Shader* hs, Shader* ds, Shader* gs, Shader* cs);
	/// generates GLSL3 target code
	void LinkGLSL3(Generator& typeChecker, Shader* vs, Shader* ps, Shader* hs, Shader* ds, Shader* gs, Shader* cs);

	/// output AnyFX formatted GLSL problem using the Khronos syntax
	void GLSLProblemKhronos(Generator& typeChecker, std::stringstream& stream);
#pragma endregion

#pragma region DirectX
	/// generates HLSL5 target code
	void LinkHLSL5(Generator& typeChecker, Shader* vs, Shader* ps, Shader* hs, Shader* ds, Shader* gs, Shader* cs);
	/// generates HLSL4 target code
	void LinkHLSL4(Generator& typeChecker, Shader* vs, Shader* ps, Shader* hs, Shader* ds, Shader* gs, Shader* cs);
	/// generates HLSL3 target code
	void LinkHLSL3(Generator& typeChecker, Shader* vs, Shader* ps, Shader* hs, Shader* ds, Shader* gs, Shader* cs);
#pragma endregion

	std::vector<std::string> invalidFlags;
	std::vector<std::string> slotNames;
	bool slotMask[ProgramRow::NumProgramRows];
    std::map<std::string, std::string> slotSubroutineMappings[ProgramRow::NumProgramRows];
	Shader* shaders[ProgramRow::NumProgramRows];
    std::string compileFlags;
	unsigned patchSize;

	bool hasAnnotation;
	Annotation annotation;
}; 


//------------------------------------------------------------------------------
/**
*/
inline void 
Program::SetAnnotation( const Annotation& annotation )
{
	this->annotation = annotation;
	this->hasAnnotation = true;
}

} // namespace AnyFX
//------------------------------------------------------------------------------
