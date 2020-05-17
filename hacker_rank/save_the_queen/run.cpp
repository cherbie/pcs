#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>

#define INPUT_DIR "testcases/input"
#define OUTPUT_DIR "testcases/output"
#define INPUT_SUBSTR_L 5
#define POS_SUBSTR_LEN 2
#define OUTPUT_SUBSTR_L 6
#define POS_SUBSTR_LEN 2

using namespace std;

int readDirContents(const char*, map<int, string>&, bool);
string resolvePath(const char*, const char*);
void freeMemory(map<int, string>&, map<int, string>&);
int runTests(map<int, string>&, map<int, string>&);

int main(void) {
  map<int, string> inputPaths;
  map<int, string> outputPaths;

  if(readDirContents(INPUT_DIR, inputPaths, true) != 0)
    throw runtime_error("Could not process input file paths.");
  if(readDirContents(OUTPUT_DIR, outputPaths, false) != 0)
    throw runtime_error("Could not process output file paths.");
  
  // run tests
  if(runTests(inputPaths, outputPaths) != 0)
    cerr << "Not all tests successful!" << endl;
  
  freeMemory(inputPaths, outputPaths);

  return EXIT_SUCCESS;
}

/**
 * Procedural logic to start child process and execute test
 */
int runTests(map<int, string>& inputPaths, map<int, string>& outputPaths) {
  for(map<int,string>::iterator it = inputPaths.begin(); it != inputPaths.end(); ++it) {
    cout << "Test No. " << it->first << endl;
    ifstream finput;
    ifstream foutput;
    finput.open(it->second, ifstream::in);
    foutput.open(outputPaths[it->first], ifstream::in);
    char* ibuf = (char*) calloc(sizeof(char), 10);
    char* obuf = (char*) calloc(sizeof(char), 10);
    finput.read(ibuf, 9);
    foutput.read(obuf, 9);

    cout << " ---\n" << ibuf << "\n ---\n" << obuf << endl;

    free(ibuf);
    free(obuf);
    finput.close();
    foutput.close();
  }

  return 0;
}

int readDirContents(const char* dirname, map<int, string>& contents, bool input) {
  //string path;
  DIR* dirp;
  struct dirent* dp;
  char* pos_str = (char*) malloc((POS_SUBSTR_LEN+1)*sizeof(char));
  int lower;
  
  if(input) {
    dirp = opendir(INPUT_DIR);
    lower = INPUT_SUBSTR_L;
  } else {
    dirp = opendir(OUTPUT_DIR);
    lower = OUTPUT_SUBSTR_L;
  }

  while((dp = readdir(dirp)) != NULL) { // read files in directory
    if(dp->d_name[0] == '.')
      continue; // skip hidden files and directories
    pos_str = strncpy(pos_str, &(dp->d_name[lower]), POS_SUBSTR_LEN); // copy 2 characters
    pos_str[POS_SUBSTR_LEN] = '\n'; // manual nul-byte character
    int pos_num = atoi(pos_str);
    string path = resolvePath(dirname, dp->d_name);
    contents[pos_num] = path;
    cout << "path: " << pos_num << " -> " << path << endl;
  }
 
  closedir(dirp); // close directory
  free(pos_str);
  free(dp);
  return 0;
}

string resolvePath(const char* basepath, const char* filepath) {
  char* cpath = (char*) calloc(sizeof(char), strlen(basepath) + strlen(filepath) + 2);
  if(cpath == NULL)
    throw runtime_error("Could not allocate memory to resolve file path.");
  cpath = strcpy(cpath, basepath);
  cpath = strcat(cpath, "/");
  string path = string(strcat(cpath, filepath));
  free(cpath);
  return path;
}

void freeMemory(map<int, string>& inputMap, map<int, string>& outputMap) {
  inputMap.clear();
  outputMap.clear();
}