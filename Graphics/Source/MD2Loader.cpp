#include "MD2Loader.h"

#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned char BYTE; 

const int MD2_IDENT = (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I');

const int MD2_VERSION = 8;

struct Md2Header
{
		int indent;// The magic number used to identify the file.
		int version;// The file version number (must be 8).
		int skinWidth;// The width in pixels of our image.
		int skinHeight;// The height in pixels of our image.
		int frameSize;// The size in bytes the frames are.
		int numSkins;// The number of skins associated with the model.
		int numVertices;// The number of vertices.
		int numTexCoords;// The number of texture coordinates.
		int numTriangles;// The number of faces (polygons).
		int numGlCommands;// The number of gl commands.
		int numFrames;// The number of animated frames.
		int offsetSkins;// The offset in the file for the skin data.
		int offsetTexCoords;// The offset in the file for the texture data.
		int offsetTriangles;// The offset in the file for the face data.
		int offsetFrames;// The offset in the file for the frames data.
		int offsetGlCommands;// The offset in the file for the gl commands data.
		int offsetEnd;// The end of the file offset.
};

struct Md2Triangle
{
	short vertexIndex[3];// Vertex indices of the triangle
	short uvIndex[3]; // Texture coordinate indices 
};

struct Md2Vertex
{
	BYTE v[3];// Compressed vertex (x, y, z) coordinates
	BYTE lightNormalIndex;// Index to a normal vector for the lighting
};

struct Md2Frame
{
	float scale[3];// Scale values
	float translate[3];// Translation vector
	char name[16];// Frame name
	Md2Vertex verts[1];// First vertex of this frame
};

//load model method
bool MD2Loader::Load_Model(const char* md2model, Model& model)
{
	ifstream   file;           
	Md2Header header;

	file.open(md2model, ios::in | ios::binary);//Open model file
	if (file.fail())
	{
		return false;
	}
	file.read(reinterpret_cast<char*>(&header), sizeof(Md2Header));//Read header
		
	if ((header.indent != MD2_IDENT) && (header.version != MD2_VERSION))//Check md2 file
	{
		file.close();
		return false;
	}

	Md2Triangle* triangles = new Md2Triangle[header.numTriangles];//Memory allocation
	BYTE* frameBuffer = new BYTE[header.frameSize];//Memory buffer
	Md2Frame* frame = reinterpret_cast<Md2Frame*>(frameBuffer);

	file.seekg(header.offsetTriangles, ios::beg);//Polygon data
	file.read(reinterpret_cast<char*>(triangles), sizeof(Md2Triangle) * header.numTriangles);	
		
	file.seekg(header.offsetFrames, ios::beg);//Frame data
	file.read(reinterpret_cast<char*>(frame), header.frameSize);	
		
	file.close();

	model.Clear();//Clear model
	for ( int i = 0; i < header.numTriangles; ++i )
	{
		model.AddTriangle(triangles[i].vertexIndex[0], triangles[i].vertexIndex[1], triangles[i].vertexIndex[2]);//Add polygons to the list
	}

	for( int i = 0; i < header.numVertices; ++i )//Vertex array
	{	
		model.AddVertex(static_cast<float>((frame->verts[i].v[0] * frame->scale[0]) + frame->translate[0]),
					    static_cast<float>((frame->verts[i].v[2] * frame->scale[2]) + frame->translate[2]),
						static_cast<float>((frame->verts[i].v[1] * frame->scale[1]) + frame->translate[1]));
	}

	delete [] triangles;//Free memory
	triangles = 0;

	delete [] frameBuffer;
	frameBuffer = 0;
	frame = 0;

	return true;
}
