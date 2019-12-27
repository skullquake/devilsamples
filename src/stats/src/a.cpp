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
	std::chrono::milliseconds t2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	/*
	int x=0;
	int y=0;
	for (int i=0;i<N;i++){
		x+=A[i]/N;
		int b=A[i]%N;
		if (y>=N-b){
			x++;
			y-=N-b;
		} else {
			y+=b;
		}
	}
	// Average is exactly x + y / N, 0 <= y < N. 
	*/
	int max_r=0;
	int max_g=0;
	int max_b=0;
	int min_r=255;
	int min_g=255;
	int min_b=255;
	long avg_r=0;
	long avg_g=0;
	long avg_b=0;
	for(int i=0;i<height;i++){
	   for(int j=0;j<width;j++){
		ILubyte r=bytes[(i*width+j)*bpp+0];
		ILubyte g=bytes[(i*width+j)*bpp+1];
		ILubyte b=bytes[(i*width+j)*bpp+2];
		avg_r+=r;
		avg_g+=g;
		avg_b+=b;
		max_r=max_r<r?r:max_r;
		max_g=max_r<g?g:max_g;
		max_b=max_r<b?b:max_b;
		min_r=min_r>r?r:min_r;
		min_g=min_r>g?g:min_g;
		min_b=min_r>b?b:min_b;
	   }
	}
	avg_r/=(width*height);
	avg_g/=(width*height);
	avg_b/=(width*height);
	std::cout<<"min_r:   "<<min_r<<std::endl;
	std::cout<<"min_g:   "<<min_g<<std::endl;
	std::cout<<"min_b:   "<<min_b<<std::endl;
	std::cout<<"max_r:   "<<max_r<<std::endl;
	std::cout<<"max_g:   "<<max_g<<std::endl;
	std::cout<<"max_b:   "<<max_b<<std::endl;
	std::cout<<"avg_r:   "<<avg_r<<std::endl;
	std::cout<<"avg_g:   "<<avg_g<<std::endl;
	std::cout<<"avg_b:   "<<avg_b<<std::endl;
	std::chrono::milliseconds t3=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::cout<<"Load:    "<<(t1-t0).count()<<" ms"<<std::endl;;
	std::cout<<"Process: "<<(t3-t2).count()<<" ms"<<std::endl;;
	return 0;
}

