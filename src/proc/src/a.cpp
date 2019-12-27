#include<IL/devil_cpp_wrapper.hpp>
#include<iostream>
#include<chrono>
#include<math.h>
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
	//iterate pixels
	/*
	for(int i=0;i<height;i++){
	   for(int j=0;j<width;j++){
	   	for(int k=0;k<bpp;k++){
			if(k==0)std::cout<<"[";
			std::cout<<static_cast<int>(bytes[(i*width+j)*bpp+k]);
			if(k<bpp-1)std::cout<<",";
			if(k==bpp-1)std::cout<<"]";
		}
		std::cout
			<<std::endl
		;
	   }
	}
	*/
	//write pixels
	std::chrono::milliseconds t2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	for(int i=0;i<height;i++){
	   for(int j=0;j<width;j++){
		//acquire
		ILubyte r_in=static_cast<ILubyte>(bytes[(i*width+j)*bpp+0]);
		ILubyte g_in=static_cast<ILubyte>(bytes[(i*width+j)*bpp+1]);
		ILubyte b_in=static_cast<ILubyte>(bytes[(i*width+j)*bpp+2]);
		//process
		ILubyte r_out;
		ILubyte g_out;
		ILubyte b_out;
		r_out=fmin(fmax(r_in-b_in,0),255);
		g_out=fmin(fmax(r_in-g_in,0),255);
		b_out=fmin(fmax(b_in,0),255);
		//write
		bytes[(i*width+j)*bpp+0]=r_out;
		bytes[(i*width+j)*bpp+1]=g_out;
		bytes[(i*width+j)*bpp+2]=b_out;
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

