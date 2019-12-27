#include<mongoose-cpp/Server.h>
#include<mongoose-cpp/WebController.h>
#include<algorithm>
#include<cstddef>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<iterator>
#include<json/json.h>
#include<numeric>
#include<signal.h>
#include<sstream>
#include<string.h>
#include<string>
#include<unistd.h>
#include<utility>
#include<vector>
#include<IL/devil_cpp_wrapper.hpp>
#include<iostream>
#include<chrono>
#include<math.h>
#include<filesystem>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<string>
#include<SQLiteCpp/SQLiteCpp.h>
#include<SQLiteCpp/VariadicBind.h>
using namespace std;
using namespace Mongoose;
void putpixel(ilImage*,int,int,int,int,int);
void getpixel(ilImage*,int,int,int&,int&,int&);
class CtlMain:public WebController{
	public: 
		void home(Request &request,StreamResponse &response){
			response.setHeader("Content-type","text/html");
			response<<R"(<!DOCTYPE html>
<html>
	<head>
		<style>
			*{
				background:#000000;
			}
		</style>
	</head>
	<body>
		<img src="/devil" id="img"></img>
		<script>
			setInterval(
				function(){
					var el=document.getElementById('img');
					el.src='/devil?cachebust='+(new Date().getTime());
				},
				10000
			);
		</script>
	</body>
</html>)";
		}
		void devil(Request &request,StreamResponse &response){
			std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()<<":start"<<std::endl;
			std::chrono::milliseconds t0=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			ilImage Image("../res/b.jpg");
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
			int stride=8;
			int r;
			int g;
			int b;
			int r2;
			int g2;
			int b2;
			for(int j=0;j<width;j++){
				for(int i=0;i<height;i+=stride){
					getpixel(&Image,j,i,r,g,b);
					r=fmax(0,fmin(255,(r*2)));
					g=fmax(0,fmin(255,(g*2)));
					b=fmax(0,fmin(255,(b*2)));
					putpixel(&Image,j,i,r,g,b);

				}
			}
			for(int i=0;i<height;i++){
				for(int j=0;j<width;j+=stride){
					getpixel(&Image,j,i,r,g,b);
					r=fmax(0,fmin(255,(r*2)));
					g=fmax(0,fmin(255,(g*2)));
					b=fmax(0,fmin(255,(b*2)));
					putpixel(&Image,j,i,r,g,b);
				}
			}
			std::chrono::milliseconds t3=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			//save
			ilEnable(IL_FILE_OVERWRITE);
			std::chrono::milliseconds t4=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			Image.Save("./spool/a.jpg");
			std::chrono::milliseconds t5=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			std::cout<<std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()<<":end"<<std::endl;
			std::cout<<"Load:    "<<(t1-t0).count()<<" ms"<<std::endl;;
			std::cout<<"Process: "<<(t3-t2).count()<<" ms"<<std::endl;;
			std::cout<<"Save:    "<<(t5-t4).count()<<" ms"<<std::endl;;
			response.setHeader("Content-type","image/jpeg");
			fstream ifs;
			ifs.open("./spool/a.jpg");
			response<<ifs.rdbuf();
		}
		void sqlitepp(Request &request,StreamResponse &response){
			SQLite::Database db("./db/a.db",SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
			try{
				{
					SQLite::Transaction txn(db);
					db.exec(R"(DROP TABLE IF EXISTS A)");
					txn.commit();
				}
				{
					SQLite::Transaction txn(db);
					db.exec(R"(
						CREATE TABLE A
						(
							val		TEXT
						))");
					txn.commit();
				}
				{
					SQLite::Transaction txn(db);
					SQLite::Statement stmt(
						db,
						R"(
							INSERT INTO A
							(
								val
							)
							VALUES
							(
								?
							)
						)"
					);
					stmt.bind(1,std::string("a")+std::to_string(0));
					stmt.exec();
					txn.commit();
				}
				{
					SQLite::Statement q0(
						db,
						R"(
							SELECT 
							*
							FROM A
						)"
						
					);
					while(q0.executeStep()){
						std::cout<<"(";
						for(int colidx=0;colidx<q0.getColumnCount();colidx++){
							 std::cout<<q0.getColumn(colidx)<<",";
						}
						std::cout<<")"<<std::endl;
					}
				}
			}catch(std::exception e){
				std::cerr<<e.what()<<std::endl;
			}
		}
		void setup(){
			addRoute(
				"GET",
				"/home",
				CtlMain,
				home
			);
			addRoute(
				"GET",
				"/devil",
				CtlMain,
				devil
			);
			addRoute(
				"GET",
				"/sqlitepp",
				CtlMain,
				sqlitepp
			);

		}
};
int main(int argc,char** argv){
	CtlMain ctlMain;
	Server server(8080);
	server.registerController(&ctlMain);
	server.setOption("enable_directory_listing","yes");
	server.setOption("document_root","./pub");
	server.setOption("access_log_file","./log.txt");
	server.start(); 
	while(1){
		sleep(10000);
	}
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
	if(x<width&&y<height){
		bytes[(y*width+x)*bpp+0]=r;
		bytes[(y*width+x)*bpp+1]=g;
		bytes[(y*width+x)*bpp+2]=b;
	}
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
	if(x<width&&y<height){
		r=static_cast<ILubyte>(bytes[(y*width+x)*bpp+0]);
		g=static_cast<ILubyte>(bytes[(y*width+x)*bpp+1]);
		b=static_cast<ILubyte>(bytes[(y*width+x)*bpp+2]);
	}
}

