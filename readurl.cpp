
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */   
/*ver 1.0*/
using namespace std;


class readurl{
public:
 string hyperLink="";//line taken from file

  readurl( char *input):inputfile(input){//open file and take name of file
    cout <<"open url-file: "<<inputfile<<endl;
    file_read_des.open(inputfile , std::ios::in );
    if (file_read_des.fail() ){
    cout <<"error open the url-file : "<<inputfile<<endl<<flush; //clean the buffer

   }
 }
 void openbrowser(){ //open browser with hyperlink
     string sys = exec("xdg-settings get default-web-browser");
 try{
     browser.insert(0,sys,0, sys.size()-9); //cut .desktop
     browserLink = browser+" "+hyperLink;//make commend
     if (!system(NULL)) throw std::runtime_error("error command processor is not present ");
     system(browserLink.c_str());//use system commend//const char *cstring =browserLink.c_str();convert to cstring for system
    }catch (...){
     throw std::runtime_error("error with opening default browser ");
    }
 }

 void readHyperlink(){//read the line where url is contained
    string tekst;
    bool endfind=false;
    int i;
 try{
    while( !file_read_des.eof() ){// work until descryptor riches  the end of file
       getline(file_read_des,hyperLink);
       for (i=4;i<hyperLink.size();i++ ){
         tekst="";
         if (tekst.insert( 0, hyperLink, i-4, 4 )=="http" ) {//take and insert to tekst every next 4 chars
            endfind=true;
            break;
         }

      }


    if (endfind)  {
      hyperLink.erase(0,i-4);//remove until http
      break;
    }

   }
 if (endfind==false ){throw std::runtime_error("can't find any http link ");}

 }catch (...)  {
      throw std::runtime_error("syntax error http link ");
    }
 }



 ~readurl(){
  cout <<endl<<"close url-file: "<<inputfile<< endl;
  file_read_des.close();
  }

  string exec(const char* command) {//get the result system command and return
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(command, "r");//open descrytor to read output of command
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {//catch an error

        throw std::runtime_error("error getting result");
    }

    pclose(pipe);
    return result;
  }
private:

  fstream file_read_des; //  files's descryptor (or ifstream)
  string browser="";//name of brower
  string browserLink=""; //name sent to browser
  string inputfile=""; //name of url file
};


int main(int argc, char *argv[]){


if (argc<2) {cout <<"no url file specified :"; return 10;}

 readurl readhyper(argv[1]);
 readhyper.readHyperlink();
 readhyper.openbrowser();


return 0;
}


