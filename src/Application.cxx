//
//
// C++ Implementation file for application
//
// Description: includes the main(...) function
//
// exa
//
//

#include "General.hxx"


char line_chars[256];

string str;
istrstream *in = 0;
ifstream input_file;

istrstream& parse()
{
  if (in && ! (*in).eof())
    return *in; 

  if (in)
    delete in;
  in = 0;

  if (input_file.eof())
        exit(0);
  //    throw("all right");

  input_file.getline(line_chars, 256);
  
  str.assign(line_chars);

  // strip all comments
  int pos = str.find_first_of("#");
  if (pos != string::npos)
    str.erase(pos);

  if (str.find_first_of("0123456789")==string::npos)
    return parse();
  else
    return *(in = new istrstream(str.c_str()));
}

void main(int argc, char *argv[])
{

   string input_filename(argv[1]);
   string output_filename(argv[2]);
   
   string magic_number;
   
   input_file.open(input_filename.c_str());
   
   parse() >> magic_number;
   
   if (magic_number!="P1") {
      cerr << "Not in PBM file format" << endl;
      exit(-1);
   }
   
   int width, height;
   parse() >> width >> height >> ws;

   cout << width << " " << height << endl;
   
//    int max_component_value;
//    parse() >> max_component_value;
   
   // create arrf header
   ofstream out(output_filename.c_str());
   out << "@relation output_filename" << endl
       << "@attribute x numeric" << endl
       << "@attribute y numeric" << endl
       << "@attribute color numeric" << endl
       << "@data" <<endl;
   
//    try {
     for (int y=0; y<height; y++)
       for (int x=0; x<width; x++) {
	 int color;
	 parse() >> color >> ws;
	 if (color)
	   out << x << ',' << y << ',' << color << endl;
       }
//    }
//    catch (string s) {
//      cout << s;
//    }
}
