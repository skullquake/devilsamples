#include<IL/devil_cpp_wrapper.hpp>
#include<iostream>
int main(int argc, char **argv){
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
	ilImage Image(argv[1]);
	std::cout
		<<Image.Width()
		<<'x'
		<<Image.Height()
		<<'@'
		<<(ILuint)Image.Bpp()
		<<std::endl
	;
	ilEnable(IL_FILE_OVERWRITE);
	Image.Save(argv[2]);
	return 0;
}

