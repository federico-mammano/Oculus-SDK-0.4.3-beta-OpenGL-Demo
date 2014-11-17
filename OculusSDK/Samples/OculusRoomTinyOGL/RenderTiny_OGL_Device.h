/************************************************************************************

Filename    :   RenderTiny_OGL_Device.h
Content     :   RenderDevice implementation header for OpenGL.
Created     :   November 8, 2014
Authors     :   Federico Mammano, from the original code written by: 
				Andrew Reisse

Copyright   :   Copyright 2012 Oculus VR, Inc. All Rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

************************************************************************************/

#ifndef INC_RenderTiny_OGL_Device_h
#define INC_RenderTiny_OGL_Device_h

#include "Kernel/OVR_Math.h"
#include "Kernel/OVR_Array.h"
#include "Kernel/OVR_String.h"
#include "Kernel/OVR_Color.h"
#include "Kernel/OVR_Log.h"
#include "OVR_CAPI.h"

#if defined(OVR_OS_WIN32)
    #include <WinSock2.h>
    #include <WS2tcpip.h>
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL/wglext.h>
#elif defined(OVR_OS_MAC)
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
#else
    #include <GL/gl.h>
    #include <GL/glext.h>
    #include <GL/glx.h>
#endif
namespace OVR { namespace RenderTiny {

#if !defined(OVR_OS_MAC)

// GL extension Hooks for PC.
#if defined(OVR_OS_WIN32)

extern PFNWGLGETSWAPINTERVALEXTPROC             wglGetSwapIntervalEXT;
extern PFNWGLSWAPINTERVALEXTPROC                wglSwapIntervalEXT;
extern PFNWGLCHOOSEPIXELFORMATARBPROC           wglChoosePixelFormatARB;
extern PFNWGLCREATECONTEXTATTRIBSARBPROC        wglCreateContextAttribsARB;

#elif defined(OVR_OS_LINUX)

extern PFNGLXSWAPINTERVALEXTPROC                glXSwapIntervalEXT;

#endif

extern PFNGLGENFRAMEBUFFERSPROC                 glGenFramebuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC              glDeleteFramebuffers;
extern PFNGLDELETESHADERPROC                    glDeleteShader;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC          glCheckFramebufferStatus;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC         glFramebufferRenderbuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC            glFramebufferTexture2D;
extern PFNGLBINDFRAMEBUFFEREXTPROC              glBindFramebuffer;
extern PFNGLACTIVETEXTUREPROC                   glActiveTexture;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC        glDisableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC             glVertexAttribPointer;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC         glEnableVertexAttribArray;
extern PFNGLBINDBUFFERPROC                      glBindBuffer;
extern PFNGLUNIFORMMATRIX3FVPROC                glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC                glUniformMatrix4fv;
extern PFNGLDELETEBUFFERSPROC                   glDeleteBuffers;
extern PFNGLBUFFERDATAPROC                      glBufferData;
extern PFNGLGENBUFFERSPROC                      glGenBuffers;
extern PFNGLMAPBUFFERPROC                       glMapBuffer;
extern PFNGLUNMAPBUFFERPROC                     glUnmapBuffer;
extern PFNGLGETSHADERINFOLOGPROC                glGetShaderInfoLog;
extern PFNGLGETSHADERIVPROC                     glGetShaderiv;
extern PFNGLCOMPILESHADERPROC                   glCompileShader;
extern PFNGLSHADERSOURCEPROC                    glShaderSource;
extern PFNGLCREATESHADERPROC                    glCreateShader;
extern PFNGLCREATEPROGRAMPROC                   glCreateProgram;
extern PFNGLATTACHSHADERPROC                    glAttachShader;
extern PFNGLDETACHSHADERPROC                    glDetachShader;
extern PFNGLDELETEPROGRAMPROC                   glDeleteProgram;
extern PFNGLUNIFORM1IPROC                       glUniform1i;
extern PFNGLGETUNIFORMLOCATIONPROC              glGetUniformLocation;
extern PFNGLGETACTIVEUNIFORMPROC                glGetActiveUniform;
extern PFNGLUSEPROGRAMPROC                      glUseProgram;
extern PFNGLGETPROGRAMINFOLOGPROC               glGetProgramInfoLog;
extern PFNGLGETPROGRAMIVPROC                    glGetProgramiv;
extern PFNGLLINKPROGRAMPROC                     glLinkProgram;
extern PFNGLBINDATTRIBLOCATIONPROC              glBindAttribLocation;
extern PFNGLGETATTRIBLOCATIONPROC               glGetAttribLocation;
extern PFNGLUNIFORM4FVPROC                      glUniform4fv;
extern PFNGLUNIFORM3FVPROC                      glUniform3fv;
extern PFNGLUNIFORM2FVPROC                      glUniform2fv;
extern PFNGLUNIFORM1FVPROC                      glUniform1fv;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC            glCompressedTexImage2D;
extern PFNGLRENDERBUFFERSTORAGEPROC             glRenderbufferStorage;
extern PFNGLBINDRENDERBUFFERPROC                glBindRenderbuffer;
extern PFNGLGENRENDERBUFFERSPROC                glGenRenderbuffers;
extern PFNGLDELETERENDERBUFFERSPROC             glDeleteRenderbuffers;
extern PFNGLGENVERTEXARRAYSPROC                 glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC              glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC                 glBindVertexArray;

extern void InitGLExtensions();

#endif



//// GLVersion

/*
    FIXME: CODE DUPLICATION WARNING

    Right now we have this same code in CommonSrc and in CAPI::GL.
    At some point we need to consolidate these, in Kernel or Util.
    Be sure to update both locations for now!
*/

struct GLVersionAndExtensions
{
    // Version information
    int         MajorVersion;        // Best guess at major version
    int         MinorVersion;        // Best guess at minor version
    bool        IsGLES;              // Open GL ES?

    // Extension information
    bool        SupportsVAO;         // Supports Vertex Array Objects?
    bool        SupportsDrawBuffers; // Supports Draw Buffers?
    const char* Extensions;          // Other extensions string (will not be null)

    GLVersionAndExtensions()
    {
        IsGLES = false;
        MajorVersion = 0;
        MinorVersion = 0;
        SupportsDrawBuffers = false;
        SupportsVAO = false;
        Extensions = "";
    }
};

void GetGLVersionAndExtensions(GLVersionAndExtensions& versionInfo);


class RenderDevice;
class Buffer;


//-----------------------------------------------------------------------------------

// Rendering primitive type used to render Model.
enum PrimitiveType
{
    Prim_Triangles,
    Prim_Lines,
    Prim_TriangleStrip,
    Prim_Unknown,
    Prim_Count
};

// Types of shaders taht can be stored together in a ShaderSet.
enum ShaderStage
{
    Shader_Vertex   = 0,
    Shader_Fragment = 2,
    Shader_Pixel    = 2,
    Shader_Count    = 3,
};

class Fill : public RefCountBase<Fill>
{
public:
    enum Flags
    {
        F_Solid = 1,
        F_Wireframe = 2,
    };

    virtual ~Fill() {}

    virtual void Set(PrimitiveType prim = Prim_Unknown) const = 0;
    virtual void Unset() const {}

    virtual void SetTexture(int i, class Texture* tex, ShaderStage stage = Shader_Pixel) { OVR_UNUSED3(i,tex,stage); }
    virtual Texture* GetTexture(int i, ShaderStage stage = Shader_Pixel) { OVR_UNUSED2(i,stage); return 0; }
};

// Built-in shader types; used by LoadBuiltinShader.
enum BuiltinShaders
{
    VShader_MV                                      = 0,
    VShader_MVP                                     ,
    VShader_PostProcess                             ,
    VShader_PostProcessMesh                         ,
    VShader_PostProcessMeshTimewarp                 ,
    VShader_PostProcessMeshPositionalTimewarp       ,
    VShader_PostProcessHeightmapTimewarp            ,
    VShader_Count                                   ,
                                                    
    FShader_Solid                                   = 0,
    FShader_Gouraud                                 ,
    FShader_Texture                                 ,
    FShader_AlphaTexture                            ,
	FShader_AlphaBlendedTexture                     ,
    FShader_PostProcessWithChromAb                  ,
    FShader_LitGouraud                              ,
    FShader_LitTexture                              ,
	FShader_MultiTexture                            ,
    FShader_PostProcessMeshWithChromAb              ,
    FShader_PostProcessMeshWithChromAbTimewarp      ,
    FShader_PostProcessMeshWithChromAbPositionalTimewarp ,
    FShader_PostProcessHeightmapTimewarp            ,
    FShader_Count                                   ,
};


enum MapFlags
{
    Map_Discard        = 1,
    Map_Read           = 2, // do not use
    Map_Unsynchronized = 4, // like D3D11_MAP_NO_OVERWRITE
};

// Buffer types used for uploading geometry & constants.
enum BufferUsage
{
    Buffer_Unknown  = 0,
    Buffer_Vertex   = 1,
    Buffer_Index    = 2,
    Buffer_Uniform  = 4,
    Buffer_TypeMask = 0xff,
    Buffer_ReadOnly = 0x100, // Buffer must be created with Data().
};

enum TextureFormat
{
    Texture_RGBA            = 0x100,
    Texture_R               = 0x200,
	Texture_A				= 0x400,
	Texture_BGRA            = 0x800,
    Texture_DXT1            = 0x1100,
    Texture_DXT3            = 0x1200,
    Texture_DXT5            = 0x1300,
    Texture_Depth           = 0x8000,
    Texture_TypeMask        = 0xff00,
    Texture_Compressed      = 0x1000,
    Texture_SamplesMask     = 0x00ff,
	Texture_RenderTarget    = 0x10000,
	Texture_SampleDepth		= 0x20000,
    Texture_GenMipmaps      = 0x40000,
    Texture_SRGB			= 0x80000,
};

// Texture sampling modes.
enum SampleMode
{
    Sample_Linear       = 0,
    Sample_Nearest      = 1,
    Sample_Anisotropic  = 2,
    Sample_FilterMask   = 3,

    Sample_Repeat       = 0,
    Sample_Clamp        = 4,
    Sample_ClampBorder  = 8, // If unsupported Clamp is used instead.
    Sample_AddressMask  =12,

    Sample_Count        =13,
};

enum MeshType
{
    Mesh_Scene,
    Mesh_Distortion,
    Mesh_Heightmap,
	Mesh_Distortion_OGL,
};

// Post-processing type to apply to scene after rendering. PostProcess_Distortion
// applied distortion as described by DistortionRenderDesc.
enum PostProcessType
{
    PostProcess_None,
    PostProcess_PixelDistortion,
    PostProcess_MeshDistortion,
    PostProcess_MeshDistortionTimewarp,
    PostProcess_MeshDistortionPositionalTimewarp,
    PostProcess_MeshDistortionHeightmapTimewarp,
    PostProcess_NoDistortion,
};

enum DisplayMode
{
    Display_Window = 0,
    Display_Fullscreen = 1,
    Display_FakeFullscreen
};
    
struct DisplayId
{
    // Windows
    String MonitorName; // Monitor name for fullscreen mode
    
    // MacOS
    int   CgDisplayId; // CGDirectDisplayID
    
    DisplayId() : CgDisplayId(-2) {}
    DisplayId(int id) : CgDisplayId(id) {}
    DisplayId(String m, int id = -2) : MonitorName(m), CgDisplayId(id) {}
    
    operator bool () const
    {
        return MonitorName.GetLength() || CgDisplayId;
    }
    
    bool operator== (const DisplayId& b) const
    {
        if (MonitorName.IsEmpty() || b.MonitorName.IsEmpty())
        {
            return CgDisplayId == b.CgDisplayId;
        }
        else
        {
            return  strstr(MonitorName.ToCStr(), b.MonitorName.ToCStr()) ||
                    strstr(b.MonitorName.ToCStr(), MonitorName.ToCStr());
        }
    }
};


// Rendering parameters used by RenderDevice::CreateDevice.
struct RendererParams
{
    int         Multisample;
    int         Fullscreen;
    DisplayId   Display;
    // Resolution of the rendering buffer used during creation.
    // Allows buffer of different size then the widow if not zero.
    Sizei       Resolution;

    RendererParams(int ms = 1) : Multisample(ms), Fullscreen(0), Resolution(0) {}
    
    bool IsDisplaySet() const
    {
        return Display;
    }
};

// Rendering parameters/pointers describing GL rendering setup.
struct RenderParams
{
#if defined(OVR_OS_WIN32)
    HWND   Window;
    HDC    DC;
#elif defined(OVR_OS_LINUX)
    _XDisplay*  Disp;
    Window      Win;
#endif

    ovrSizei  RTSize;
    int    Multisample;
};

class Shader : public RefCountBase<Shader>
{
    friend class ShaderSet;

protected:
    ShaderStage Stage;

public:
	GLuint      GLShader;

    Shader(RenderDevice*, ShaderStage st, GLuint s) : Stage(st), GLShader(s) {}
    Shader(RenderDevice*, ShaderStage st, const char* src) : Stage(st), GLShader(0)
    {
        Compile(src);
    }
    Shader(ShaderStage s) : Stage(s) {}
    ~Shader();
	bool Compile(const char* src);

    GLenum GLStage() const
    {
        switch (Stage)
        {
        default:  OVR_ASSERT(0); return GL_NONE;
        case Shader_Vertex: return GL_VERTEX_SHADER;
        case Shader_Fragment: return GL_FRAGMENT_SHADER;
        }
    }

    ShaderStage GetStage() const { return Stage; }

    virtual void Set(PrimitiveType) const { }
    virtual void SetUniformBuffer(class Buffer* buffers, int i = 0) { OVR_UNUSED2(buffers, i); }
    virtual bool UseTransposeMatrix() const { return 0; }

protected:
    virtual bool SetUniform(const char* name, int n, const float* v) { OVR_UNUSED3(name, n, v); return false; }
};

// A group of shaders, one per stage.
// A ShaderSet is applied to a RenderDevice for rendering with a given fill.
class ShaderSet : public RefCountBase<ShaderSet>
{
protected:
    Ptr<Shader> Shaders[Shader_Count];

public:
    GLuint Prog;

    struct Uniform
    {
        String Name;
        int    Location, Size;
        int    Type; // currently number of floats in vector
    };
    Array<Uniform> UniformInfo;

    int     ProjLoc, ViewLoc;
    int     TexLoc[8];
    bool    UsesLighting;
    int     LightingVer;

    ShaderSet() { Prog = glCreateProgram(); }
    ~ShaderSet() { glDeleteProgram(Prog); }

    virtual void SetShader(Shader *s)
    {
        Shaders[s->GetStage()] = s;
		Shader* gls = (Shader*)s;
		glAttachShader(Prog, gls->GLShader);
		if (Shaders[Shader_Vertex] && Shaders[Shader_Fragment])
			Link();
    }
    virtual void UnsetShader(int stage)
    {
		Shader* gls = (Shader*)Shaders[stage];
		if (gls)
			glDetachShader(Prog, gls->GLShader);
		Shaders[stage] = NULL;
    }
	Shader* GetShader(int stage) { return Shaders[stage]; }

	virtual void Set(PrimitiveType prim) const;

    // Set a uniform (other than the standard matrices). It is undefined whether the
    // uniforms from one shader occupy the same space as those in other shaders
    // (unless a buffer is used, then each buffer is independent).     
    virtual bool SetUniform(const char* name, int n, const float* v);
    bool SetUniform1f(const char* name, float x)
    {
        const float v[] = {x};
        return SetUniform(name, 1, v);
    }
    bool SetUniform2f(const char* name, float x, float y)
    {
        const float v[] = {x,y};
        return SetUniform(name, 2, v);
    }
    bool SetUniform3f(const char* name, float x, float y, float z)
    {
        const float v[] = {x,y,z};
        return SetUniform(name, 3, v);
    }
    bool SetUniform4f(const char* name, float x, float y, float z, float w = 1)
    {
        const float v[] = {x,y,z,w};
        return SetUniform(name, 4, v);
    }
    bool SetUniformv(const char* name, const Vector3f& v)
    {
        const float a[] = {v.x,v.y,v.z,1};
        return SetUniform(name, 4, a);
    }
    bool SetUniform4fv(const char* name, int n, const Vector4f* v)
    {
        return SetUniform(name, 4*n, &v[0].x);
    }
	virtual bool SetUniform4x4f(const char* name, const Matrix4f& m);

    bool Link();
};


// Fill combines a ShaderSet (vertex, pixel) with textures, if any.
// Every model has a fill.
class ShaderFill : public Fill
{
    Ptr<ShaderSet> Shaders;
    Ptr<Texture>   Textures[8];
    Ptr<Texture>   VtxTextures[8];

public:
    ShaderFill(ShaderSet* sh) : Shaders(sh) {  }
    ShaderFill(ShaderSet& sh) : Shaders(sh) {  }
    void Set(PrimitiveType prim) const;
    ShaderSet* GetShaders() { return Shaders; }

    virtual void SetTexture(int i, class Texture* tex, ShaderStage stage = Shader_Pixel)
    {
        if (i < 8)
        {
                 if(stage == Shader_Pixel)  Textures[i] = tex;
            else if(stage == Shader_Vertex) VtxTextures[i] = tex;
            else OVR_ASSERT(false);
        }
    }
    virtual Texture* GetTexture(int i, ShaderStage stage = Shader_Pixel)
    {
        if (i < 8)
        {
                 if(stage == Shader_Pixel)      return Textures[i];
            else if(stage == Shader_Vertex)     return VtxTextures[i];
            else OVR_ASSERT(false);             return 0;
        }
        else
        {
            return 0;
        }
    }
};

class ShaderBase : public Shader
{
public:    
    RenderParams*   pParams;
    unsigned char*  UniformData;
    int             UniformsSize;

	enum VarType
	{
		VARTYPE_FLOAT,
		VARTYPE_INT,
		VARTYPE_BOOL,
	};

	struct Uniform
	{
		const char* Name;
		VarType Type;
		int     Offset, Size;
	};
    const Uniform* UniformRefl;
    size_t UniformReflSize;

	ShaderBase(RenderParams* rp, ShaderStage stage) : Shader(stage), pParams(rp), UniformData(0), UniformsSize(0) {}
	~ShaderBase()
	{
		if (UniformData)    
			OVR_FREE(UniformData);
	}

    void InitUniforms(const Uniform* refl, size_t reflSize);
	bool SetUniform(const char* name, int n, const float* v);
	bool SetUniformBool(const char* name, int n, const bool* v);
};


template<ShaderStage SStage, GLenum SType>
class ShaderImpl : public ShaderBase
{
    friend class ShaderSet;

public:
    ShaderImpl(RenderParams* rp, void* s, size_t size, const Uniform* refl, size_t reflSize)
		: ShaderBase(rp, SStage)
		, GLShader(0)
    {
		bool success;
        OVR_UNUSED(size);
        success = Compile((const char*) s);
        OVR_ASSERT(success);
        OVR_UNUSED(success);
		InitUniforms(refl, reflSize);
    }
    ~ShaderImpl()
    {      
		if (GLShader)
		{
			glDeleteShader(GLShader);
			GLShader = 0;
		}
    }
    bool Compile(const char* src)
	{
		if (!GLShader)
			GLShader = glCreateShader(GLStage());

		glShaderSource(GLShader, 1, &src, 0);
		glCompileShader(GLShader);
		GLint r;
		glGetShaderiv(GLShader, GL_COMPILE_STATUS, &r);
		if (!r)
		{
			GLchar msg[1024];
			glGetShaderInfoLog(GLShader, sizeof(msg), 0, msg);
			if (msg[0])
				OVR_DEBUG_LOG(("Compiling shader\n%s\nfailed: %s\n", src, msg));

			return 0;
		}
		return 1;
	}
	
    GLenum GLStage() const
    {
		return SType;
	}

private:
	GLuint GLShader;
};

typedef ShaderImpl<Shader_Vertex,  GL_VERTEX_SHADER> VertexShader;
typedef ShaderImpl<Shader_Fragment, GL_FRAGMENT_SHADER> FragmentShader;

// Buffer for vertex or index data. Some renderers require separate buffers, so that
// is recommended. Some renderers cannot have high-performance buffers which are readable,
// so reading in Map should not be relied on.
//
// Constraints on buffers, such as ReadOnly, are not enforced by the API but may result in 
// rendering-system dependent undesirable behavior, such as terrible performance or unreported failure.
//
// Use of a buffer inconsistent with usage is also not checked by the API, but it may result in bad
// performance or even failure.
//
// Use the Data() function to set buffer data the first time, if possible (it may be faster).

class Buffer : public RefCountBase<Buffer>
{
public:
    RenderDevice*		Ren;
    size_t				Size;
    GLenum				Use;
    GLuint				GLBuffer;

public:
    Buffer(RenderDevice* r) : Ren(r), Size(0), Use(0), GLBuffer(0) {}
    ~Buffer();

    GLuint         GetBuffer() { return GLBuffer; }

    virtual size_t GetSize() { return Size; }
    virtual void*  Map(size_t start, size_t size, int flags = 0);
    virtual bool   Unmap(void *m);
	// Allocates a buffer, optionally filling it with data.
    virtual bool   Data(int use, const void* buffer, size_t size);
};

class Texture : public RefCountBase<Texture>
{
public:
    RenderDevice*					Ren;
    GLuint							TexId;
    int								Width, Height;

    Texture(RenderDevice* r, int w, int h);
    ~Texture();

    virtual int GetWidth() const { return Width; }
    virtual int GetHeight() const { return Height; }
	virtual int GetSamples() const { return 1; }
    
	virtual void SetSampleMode(int);
	virtual ovrTexture Get_ovrTexture();

    virtual void Set(int slot, ShaderStage stage = Shader_Fragment) const;

	virtual void* GetInternalImplementation() { return NULL; };
};


struct RenderTarget
{
    Ptr<Texture>        pColorTex;
    Ptr<Texture>        pDepthTex;
    Sizei               Size;
};


//-----------------------------------------------------------------------------------

// Node is a base class for geometry in a Scene, it contains base position
// and orientation data.
// Model and Container both derive from it.
// 
class Node : public RefCountBase<Node>
{
    Vector3f     Pos;
    Quatf        Rot;

    mutable Matrix4f  Mat;
    mutable bool      MatCurrent;

public:
    Node() : Pos(Vector3f(0)), MatCurrent(1) { }
    virtual ~Node() { }

    enum NodeType
    {
        Node_NonDisplay,
        Node_Container,
        Node_Model
    };
    virtual NodeType GetType() const { return Node_NonDisplay; }

    const Vector3f&  GetPosition() const      { return Pos; }
    const Quatf&     GetOrientation() const   { return Rot; }
    void             SetPosition(Vector3f p)  { Pos = p; MatCurrent = 0; }
    void             SetOrientation(Quatf q)  { Rot = q; MatCurrent = 0; }

    void             Move(Vector3f p)         { Pos += p; MatCurrent = 0; }
    void             Rotate(Quatf q)          { Rot = q * Rot; MatCurrent = 0; }


    // For testing only; causes Position an Orientation
    void  SetMatrix(const Matrix4f& m)
    {
        MatCurrent = true;
        Mat = m;        
    }

    const Matrix4f&  GetMatrix() const 
    {
        if (!MatCurrent)
        {
            Mat = Matrix4f(Rot);
            Mat = Matrix4f::Translation(Pos) * Mat;
            MatCurrent = 1;
        }
        return Mat;
    }

    virtual void     Render(const Matrix4f& ltw, RenderDevice* ren) { OVR_UNUSED2(ltw, ren); }
};


// Vertex type; same format is used for all shapes for simplicity.
// Shapes are built by adding vertices to Model.
struct Vertex
{
    Vector3f  Pos;
    Color     C;
    float     U, V;
	float     U2, V2;
    Vector3f  Norm;

    Vertex (const Vector3f& p, const Color& c = Color(64,0,0,255), 
            float u = 0, float v = 0, Vector3f n = Vector3f(1,0,0))
      : Pos(p), C(c), U(u), V(v), U2(u), V2(v), Norm(n) {}
    Vertex(float x, float y, float z, const Color& c = Color(64,0,0,255),
           float u = 0, float v = 0) : Pos(x,y,z), C(c), U(u), V(v), U2(u), V2(v) { }

	// for multiple UV coords
	Vertex(const Vector3f& p, const Color& c,
           float u, float v, float u2, float v2, Vector3f n) : Pos(p), C(c), U(u), V(v), U2(u2), V2(v2), Norm(n) { }

    bool operator==(const Vertex& b) const
    {
        return Pos == b.Pos && C == b.C && U == b.U && V == b.V;
    }
};

struct DistortionVertex
{
    Vector2f Pos;
    Vector2f TexR;
    Vector2f TexG;
    Vector2f TexB;
    Color Col;
};

struct HeightmapVertex
{
    Vector2f Pos;
    Vector3f Tex;
};

// LightingParams are stored in a uniform buffer, don't change it without fixing all renderers
// Scene contains a set of LightingParams that is uses for rendering.
struct LightingParams
{
    Vector4f Ambient;
    Vector4f LightPos[8];
    Vector4f LightColor[8];
    float    LightCount;    
    int      Version;

    LightingParams() : LightCount(0), Version(0) {}


    void Update(const Matrix4f& view, const Vector4f* SceneLightPos)
    {    
        Version++;
        for (int i = 0; i < LightCount; i++)
        {
            LightPos[i] = view.Transform(SceneLightPos[i]);
        }
    }

    void Set(ShaderSet* s) const
    {
        s->SetUniform4fv("Ambient", 1, &Ambient);
        s->SetUniform1f("LightCount", LightCount);
        s->SetUniform4fv("LightPos", (int)LightCount, LightPos);
        s->SetUniform4fv("LightColor", (int)LightCount, LightColor);
    }
};


//-----------------------------------------------------------------------------------

// Model is a triangular mesh with a fill that can be added to scene.
// 
class Model : public Node
{
public:
    Array<Vertex>     Vertices;
    Array<uint16_t>   Indices;
    PrimitiveType     Type;
    Ptr<ShaderFill>   Fill;
    bool              Visible;	

    // Some renderers will create these if they didn't exist before rendering.
    // Currently they are not updated, so vertex data should not be changed after rendering.
    Ptr<Buffer>       VertexBuffer;
    Ptr<Buffer>       IndexBuffer;

    Model(PrimitiveType t = Prim_Triangles) : Type(t), Fill(NULL), Visible(true) { }
    ~Model() { }

    PrimitiveType GetPrimType() const      { return Type; }

    void          SetVisible(bool visible) { Visible = visible; }
    bool          IsVisible() const        { return Visible; }


    // Node implementation.
    virtual NodeType GetType() const       { return Node_Model; }
    virtual void    Render(const Matrix4f& ltw, RenderDevice* ren);


    // Returns the index next added vertex will have.
    uint16_t GetNextVertexIndex() const
    {
        return (uint16_t)Vertices.GetSize();
    }

    uint16_t AddVertex(const Vertex& v)
    {
        OVR_ASSERT(!VertexBuffer && !IndexBuffer);
        uint16_t index = (uint16_t)Vertices.GetSize();
        Vertices.PushBack(v);
        return index;
    }

    void AddTriangle(uint16_t a, uint16_t b, uint16_t c)
    {
        Indices.PushBack(a);
        Indices.PushBack(b);
        Indices.PushBack(c);
    }

    // Uses texture coordinates for uniform world scaling (must use a repeat sampler).
    void  AddSolidColorBox(float x1, float y1, float z1,
                           float x2, float y2, float z2,
                           Color c);
};


// Container stores a collection of rendering nodes (Models or other containers).
class Container : public Node
{
public:
    Array<Ptr<Node> > Nodes;

    Container()  { }
    ~Container() { }

    virtual NodeType GetType() const { return Node_Container; }

    virtual void Render(const Matrix4f& ltw, RenderDevice* ren);

    void Add(Node *n)  { Nodes.PushBack(n); }	
    void Clear()       { Nodes.Clear(); }	
};


// Scene combines a collection of model 
class Scene : public NewOverrideBase
{
public:
    Container			World;
    Vector4f			LightPos[8];
    LightingParams		Lighting;

public:
    void Render(RenderDevice* ren, const Matrix4f& view);

    void SetAmbient(Vector4f color)
    {
        Lighting.Ambient = color;
    }

    void AddLight(Vector3f pos, Vector4f color)
    {
        int n = (int)Lighting.LightCount;
        OVR_ASSERT(n < 8);
        LightPos[n] = pos;
        Lighting.LightColor[n] = color;
        Lighting.LightCount++;
    }

    void Clear()
    {
        World.Clear();
        Lighting.Ambient = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
        Lighting.LightCount = 0;
    }
};

//-----------------------------------------------------------------------------------

class RenderDevice : public RefCountBase<RenderDevice>
{
    Ptr<Shader>					VertexShaders[VShader_Count];
    Ptr<Shader>					FragShaders[FShader_Count];

    Ptr<ShaderFill>				DefaultFill;

	GLuint						Vao;

    friend BOOL CALLBACK		MonitorEnumFunc(HMONITOR hMonitor, HDC, LPRECT, LPARAM dwData);

    HWND						Window;
    HGLRC						WglContext;
    Recti						PreFullscreen;
    Recti						FSDesktop;
    HMONITOR					HMonitor;

protected:
    Ptr<Texture>				CurRenderTarget;
    Array<Ptr<Texture> >		DepthBuffers;
    GLuint						CurrentFbo;
    GLVersionAndExtensions		GLVersionInfo;

    const LightingParams*		Lighting;

protected:
    int							WindowWidth, WindowHeight;
    RendererParams				Params;
    Recti						VP;

    Matrix4f					Proj;
    Ptr<Buffer>					pTextVertexBuffer;

    // For rendering with lens warping
    PostProcessType				PostProcessingType;

    Ptr<ShaderSet>				pPostProcessShader;
    Ptr<ShaderSet>				pPostProcessHeightmapShader;
    Ptr<Buffer>					pFullScreenVertexBuffer;
    Color						DistortionClearColor;
    size_t						TotalTextureMemoryUsage;
    float						FadeOutBorderFraction;
    
    int							DistortionMeshNumTris[2];
    Ptr<Buffer>					pDistortionMeshVertexBuffer[2];
    Ptr<Buffer>					pDistortionMeshIndexBuffer[2];

    int							HeightmapMeshNumTris[2];
    Ptr<Buffer>					pHeightmapMeshVertexBuffer[2];
    Ptr<Buffer>					pHeightmapMeshIndexBuffer[2];

    // For lighting on platforms with uniform buffers
    Ptr<Buffer>					LightingBuffer;

    RenderTarget				HeightmapTimewarpRTs[2];  // one for each eye

public:
    
	// GL context and utility variables.
    RenderParams				RParams;   

    enum CompareFunc
    {
        Compare_Always  = 0,
        Compare_Less    = 1,
        Compare_Greater = 2,
        Compare_Count
    };

    RenderDevice(const RendererParams& p);
    RenderDevice(const RendererParams& p, HWND win, HGLRC gl);
	virtual ~RenderDevice();

	void InitRenderDevice(const RendererParams& p);

    virtual void Shutdown();
	
    virtual void FillTexturedRect(float left, float top, float right, float bottom, float ul, float vt, float ur, float vb, Color c, Ptr<Texture> tex);

    virtual void SetViewport(const Recti& vp);
	void         SetViewport(int x, int y, int w, int h) { SetViewport(Recti(x,y,w,h)); }
	virtual void SetFullViewport();
	
    virtual void WaitUntilGpuIdle();
    virtual void Flush();

    virtual void Clear(float r = 0, float g = 0, float b = 0, float a = 1, float depth = 1,
                       bool clearColor = true, bool clearDepth = true);
    virtual void Rect(float left, float top, float right, float bottom) { OVR_UNUSED4(left,top,right,bottom); }

	void  InitShaders( const char * vertex_shader, const char * pixel_shader, ShaderSet ** pShaders);

    virtual void SetDepthMode(bool enable, bool write, CompareFunc func = Compare_Less);
	virtual void SetProjection(const Matrix4f& proj);
    virtual void SetWorldUniforms(const Matrix4f& proj);

    Texture* GetDepthBuffer(int w, int h, int ms);

    // Rendering

    // Begin drawing directly to the currently selected render target, no post-processing.
    virtual void BeginRendering();
    // Begin drawing the primary scene, starting up whatever post-processing may be needed.
    virtual void BeginScene(PostProcessType pp = PostProcess_None);
    // Finish scene.
    virtual void FinishScene();
    // Texture must have been created with Texture_RenderTarget. Use NULL for the default render target.
    // NULL depth buffer means use an internal, temporary one.
    void SetRenderTarget(const RenderTarget& renderTarget)
    {
        SetRenderTarget(renderTarget.pColorTex, renderTarget.pDepthTex);
    }
    // go to back buffer
    void SetDefaultRenderTarget() { SetRenderTarget(NULL, NULL); }

    virtual void SetRenderTarget(Texture* color, Texture* depth = NULL, Texture* stencil = NULL);

    virtual void SetLighting(const LightingParams* lt);

	virtual void SetExtraShaders(ShaderSet* s) { OVR_UNUSED(s); }

    virtual void Render(const Matrix4f& matrix, Model* model);
    virtual void Render(const Fill* fill, Buffer* vertices, Buffer* indices,
                        const Matrix4f& matrix, int offset, int count, PrimitiveType prim = Prim_Triangles, MeshType meshType = Mesh_Scene);
	void Render(const ShaderFill* fill, Buffer* vertices, Buffer* indices);
    virtual void RenderWithAlpha(const Fill* fill, Buffer* vertices, Buffer* indices,
                                 const Matrix4f& matrix, int offset, int count, PrimitiveType prim = Prim_Triangles);

    virtual Buffer* CreateBuffer();
    virtual Texture* CreateTexture(int format, int width, int height, const void* data, int mipcount=1);
    virtual ShaderSet* CreateShaderSet() { return new ShaderSet; }

    virtual Fill *CreateSimpleFill(int flags = Fill::F_Solid);
	Fill *        CreateTextureFill(Texture* tex, bool useAlpha = false);

    virtual Shader *LoadBuiltinShader(ShaderStage stage, int shader);

    void SetTexture(ShaderStage, int slot, const Texture* t);

    // Implement static initializer function to create this class.
    static RenderDevice* CreateDevice(const RendererParams& rp, void* oswnd);

	virtual ovrRenderAPIConfig Get_ovrRenderAPIConfig() const;

    virtual void Present(bool withVsync);
	bool SetParams(const RendererParams& newParams);
	const RendererParams& GetParams() const { return Params; }

    virtual bool SetFullscreen(DisplayMode fullscreen);

    enum PostProcessShader
    {
        PostProcessShader_DistortionAndChromAb              = 0,
        PostProcessShader_MeshDistortionAndChromAb,
        PostProcessShader_MeshDistortionAndChromAbTimewarp,
        PostProcessShader_MeshDistortionAndChromAbPositionalTimewarp,
        PostProcessShader_MeshDistortionAndChromAbHeightmapTimewarp,
        PostProcessShader_Count
    };

    PostProcessShader GetPostProcessShader()
    {
        return PostProcessShaderActive;
    }

    void SetPostProcessShader(PostProcessShader newShader)
    {
        PostProcessShaderRequested = newShader;
    }

protected:
    // Stereo & post-processing
    virtual bool  initPostProcessSupport(PostProcessType pptype);

private:
    PostProcessShader   PostProcessShaderRequested;
    PostProcessShader   PostProcessShaderActive;
};

int GetNumMipLevels(int w, int h);
int GetTextureSize(int format, int w, int h);

// Filter an rgba image with a 2x2 box filter, for mipmaps.
// Image size must be a power of 2.
void FilterRgba2x2(const uint8_t* src, int w, int h, uint8_t* dest);

}}


//Anything including this file, uses these
using namespace OVR;
using namespace OVR::RenderTiny;


#endif
