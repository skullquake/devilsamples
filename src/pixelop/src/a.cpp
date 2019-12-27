#include<IL/devil_cpp_wrapper.hpp>
#include<iostream>
#include<chrono>
#include<math.h>
void putpixel(ilImage*,int,int,int,int,int);
void getpixel(ilImage*,int,int,int&,int&,int&);
int main(int argc, char **argv){
	std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()<<":start"<<std::endl;
	if(argc<2){
		std::cout
			<<"Please specify input file."
			<<std::endl
		;
		return 1;
	}
	if(argc<3){
		std::cout
			<<"Please specify output file."
			<<std::endl
		;
		return 1;
	}
	std::chrono::milliseconds t0=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	ilImage Image(argv[1]);
	std::chrono::milliseconds t1=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	//info
	ILubyte* bytes=Image.GetData();
	ILuint width;
	ILuint height;
	ILuint bpp;
	ILuint bitpp;
	ILuint nimg;
	ILuint nmip;
	ILuint depth;
	width=Image.Width();
	height=Image.Height();
	bpp=Image.Bpp();
	nimg=Image.NumImages();
	nmip=Image.NumMipmaps();
	bitpp=Image.Bitpp();
	depth=Image.Depth();
	std::cout
		<<"w:"
		<<width
		<<":h:"
		<<height
		<<":bpp:"
		<<bpp
		<<":bitpp:"
		<<bpp
		<<":nimg:"
		<<nimg
		<<":nmip:"
		<<nmip
		<<":d:"
		<<depth
		<<std::endl
	;
	//write pixels
	std::chrono::milliseconds t2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	int stride=32;
	int r;
	int g;
	int b;
	for(int i=0;i<height;i+=stride){
		for(int j=0;j<width;j++){
			getpixel(&Image,j,i,r,g,b);
			r=fmin(255,r*2);
			g=fmin(255,g*2);
			b=fmin(255,b*2);
			putpixel(&Image,j,i,r,g,b);
		}
	}
	for(int j=0;j<width;j+=stride){
		for(int i=0;i<height;i+=1){
			getpixel(&Image,j,i,r,g,b);
			r=fmin(255,r*2);
			g=fmin(255,g*2);
			b=fmin(255,b*2);
			putpixel(&Image,j,i,r,g,b);
		}
	}

	std::chrono::milliseconds t3=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	//save
	ilEnable(IL_FILE_OVERWRITE);
	std::chrono::milliseconds t4=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	Image.Save(argv[2]);
	std::chrono::milliseconds t5=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()<<":end"<<std::endl;
	std::cout<<"Load:    "<<(t1-t0).count()<<" ms"<<std::endl;;
	std::cout<<"Process: "<<(t3-t2).count()<<" ms"<<std::endl;;
	std::cout<<"Save:    "<<(t5-t4).count()<<" ms"<<std::endl;;
	return 0;
}
void putpixel(
	ilImage* Image,
	int x,
	int y,
	int r,
	int g,
	int b
){
	ILubyte* bytes=Image->GetData();
	ILuint bpp=Image->Bpp();
	ILuint width=Image->Width();
	ILuint height=Image->Height();
	bytes[(y*width+x)*bpp+0]=r;
	bytes[(y*width+x)*bpp+1]=g;
	bytes[(y*width+x)*bpp+2]=b;
}
void getpixel(
	ilImage* Image,
	int x,
	int y,
	int &r,
	int &g,
	int &b
){
	ILubyte* bytes=Image->GetData();
	ILuint bpp=Image->Bpp();
	ILuint width=Image->Width();
	ILuint height=Image->Height();
	r=static_cast<ILubyte>(bytes[(y*width+x)*bpp+0]);
	g=static_cast<ILubyte>(bytes[(y*width+x)*bpp+1]);
	b=static_cast<ILubyte>(bytes[(y*width+x)*bpp+2]);
}
