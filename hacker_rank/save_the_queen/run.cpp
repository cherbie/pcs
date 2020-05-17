#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <unistd.h>
#include <sys/wait.h>

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
int run(map<int, string>&, map<int, string>&);
int exec_test(ifstream&, ifstream&);
void read_from_pipe(int&);
void write_to_pipe(int&);

int main(void) {
  map<int, string> inputPaths;
  map<int, string> outputPaths;

  if(readDirContents(INPUT_DIR, inputPaths, true) != 0)
    throw runtime_error("Could not process input file paths.");
  if(readDirContents(OUTPUT_DIR, outputPaths, false) != 0)
    throw runtime_error("Could not process output file paths.");
  
  // run tests
  if(run(inputPaths, outputPaths) != 0)
    cerr << "Not all tests successful!" << endl;
  
  freeMemory(inputPaths, outputPaths);

  return EXIT_SUCCESS;
}

/**
 * Procedural logic to start child process and execute test
 */
int run(map<int, string>& inputPaths, map<int, string>& outputPaths) {
  for(map<int,string>::iterator it = inputPaths.begin(); it != inputPaths.end(); ++it) {
    cout << "Test No. " << it->first << endl;
    ifstream finput;
    ifstream foutput;
    finput.open(it->second, ifstream::in);
    foutput.open(outputPaths[it->first], ifstream::in);
    char* ibuf = (char*) calloc(sizeof(char), 10);
    char* obuf = (char*) calloc(sizeof(char), 10);

    if(exec_test(finput, foutput) == 1)
	return 0; // return as this is the child process
    
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

int exec_test(ifstream& test_input, ifstream& test_output) {
  int* pipestreams = (int*) malloc(sizeof(int) * 2);

  if(pipe(pipestreams) != 0)
    throw runtime_error("Unable to communicate to child process using pipes.");
  pid_t pid = fork();
  switch(pid) {
    case -1: { // fork error
      throw runtime_error("Error spawning child process.");
    }
    case 0: { // child process
      close(pipestreams[0]);
      dup2(pipestreams[1], 1); // read output of the child process and place in pipe
      //write_to_pipe(pipestreams[1]);
      close(pipestreams[1]);

      //char* args[] = {"."};
      if(execlp("pwd", "pwd") != 0)
        cerr << "Error executing child process" << endl;
      return 1; // return 1 if you are the child process
    }
    default: { // parent process
      // pipestreams[0] // contains the read end of the pipe
      close(pipestreams[1]); // don't want to write;

      cout << "parents waiting" << endl;
      int status;
      wait(&status);
      
      if(status == 0)
        read_from_pipe(pipestreams[0]);

      close(pipestreams[0]);
    }
  }

  free(pipestreams);
  return 0;
}

void read_from_pipe(int& fd) {
  char* buf = (char*) calloc(sizeof(char), 20);

  if(read(fd, buf, sizeof(char) * 18) < 0) {
    cerr << "Error reading pipe." << endl;
  }

  buf[19] = '\n';
  cout << buf << endl;
  free(buf);
}

void write_to_pipe(int& fd) {
  char* buf =  (char*) calloc(sizeof(char), 20);
  buf = strncpy(buf, "Hello World", 19);
  if(write(fd, buf, sizeof(char) * 19) < 0)
    cerr << "Error writing to pipe" << endl;
  
  free(buf);
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
