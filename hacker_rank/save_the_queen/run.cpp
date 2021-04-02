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
#define BUFFER_SIZE 255

using namespace std;

int read_dir_contents(const char*, map<int, string>&, bool);
string resolve_path(const char*, const char*);
void free_memory(map<int, string>&, map<int, string>&);
int run(map<int, string>&, map<int, string>&);
int exec_test(ifstream&, ifstream&);
void read_from_pipe(int&, string&);
void write_to_pipe(int&, const char*, size_t);
int cmp_test_output(ifstream&, string&);

int main(void) {
  map<int, string> input_paths; // input
  map<int, string> output_paths; // output

  if(read_dir_contents(INPUT_DIR, input_paths, true) != 0)
    throw runtime_error("Could not process input file paths.");
  if(read_dir_contents(OUTPUT_DIR, output_paths, false) != 0)
    throw runtime_error("Could not process output file paths.");
  
  // run tests
  if(run(input_paths, output_paths) != 0)
    cerr << "Not all tests successful!" << endl;
  
  free_memory(input_paths, output_paths);

  return EXIT_SUCCESS;
}

/**
 * Procedural logic to start child process and execute test
 */
int run(map<int, string>& input_paths, map<int, string>& output_paths) {
  for(map<int,string>::iterator it = input_paths.begin(); it != input_paths.end(); ++it) {
		// it -> first - contains test number
		// it -> second - contains input file path
    cout << "Test No: " << it->first << endl;
    
		ifstream finput;
    ifstream foutput;
    finput.open(it->second);
    foutput.open(output_paths[it->first]);

    char* ibuf = (char*) calloc(BUFFER_SIZE+1, sizeof(char));
    char* obuf = (char*) calloc(BUFFER_SIZE+1, sizeof(char));

		// -- Read test case files
    //finput.read(ibuf, BUFFER_SIZE * sizeof(char));
    //foutput.read(obuf, BUFFER_SIZE * sizeof(char));

		//cout << " --- Test Input --- \n" << ibuf << "\n --- Test Output --- \n" << obuf << endl;
		
		// Child process error returns 1
    if(exec_test(finput, foutput) == 1)
	    return 0; // return as this is the child process

    free(ibuf);
    free(obuf);

    finput.close();
    foutput.close();
  }

  return 0;
}

/**
 * Spawn child processes and execute test on the child process.
 *
 */ 
int exec_test(ifstream& ifile, ifstream& ofile) {
  int p2c[2]; // pipestreams[0] -> parent to child
	int c2p[2]; // pipestreams[1] -> child to parent
	char* input = (char*) calloc(BUFFER_SIZE+1, sizeof(char));

	ifile.read(input, BUFFER_SIZE); // read the input file stream

	cout << "-->" <<  input << endl;

	/*
	 * Just need to implement p2c pipe communication and run app in child.
	 */
  if(pipe(c2p) != 0)
    throw runtime_error("Unable to communicate to from child to parent using pipes");
	if(pipe(p2c) != 0)
    throw runtime_error("Unable to communicate to from child to parent using pipes");

  pid_t pid = fork(); // spawn child process
  switch(pid) {
    case -1: { // fork error
      throw runtime_error("Error spawning child process.");
    }
    case 0: { // child process
      close(c2p[0]); // close read end of the stream
			close(p2c[1]); // close write end of stream

      dup2(1, c2p[1]); // duplicate stdout to the write end of pipe1
			dup2(p2c[0], 0); // duplicate reading end to the input stream of child


      //char* args[] = {"."};
      if(execlp("cat", "") != 0)
        cerr << "Error executing child process" << endl;
			
			// -- Deallocate memory --
			free(input);
      return 1; // return 1 if you are the child process
    }
    default: {
			// parent process
      // c2p[0] // contains the read-end of the pipe
      close(c2p[1]); // close write end of stream pipe1
			close(p2c[0]); // close read end of stream

      cout << "Parents waiting" << endl;
			
			write_to_pipe(p2c[1], input, BUFFER_SIZE); 

      int status;
      wait(&status);
      
      if(status == 0) {
				string ostr;
        read_from_pipe(c2p[0], ostr);
				if(cmp_test_output(ofile, ostr) == 0)
					cout << "-- CORRECT --" << endl;
				else
					cout << "-- INCORRECT --" << endl;
			}

      close(c2p[0]); // close the read-end of the pipe
    }
  }

	// -- Deallocate Memory --
	free(input);
  return 0;
}

/**
 * Compare the expected and observed program string output.
 * @return int - 0 if the are equivalent
 */
int cmp_test_output(ifstream& ofile, string& ostr) {
	char* correct_output = (char*) calloc(BUFFER_SIZE+1, sizeof(char*));
	
	ofile.read(correct_output, BUFFER_SIZE); // read from file

	cout << "Expected: " << correct_output << '\n' << "Actual: " << ostr << endl;

	// Deep copies :(
	string str_theory(correct_output);

	free(correct_output);
	return str_theory.compare(ostr);
}

void read_from_pipe(int& fd, string& ostr) {
  char* buf = (char*) calloc(sizeof(char), BUFFER_SIZE+1);

  if(read(fd, buf, sizeof(char) * BUFFER_SIZE) < 0) {
    cerr << "Error reading pipe." << endl;
  }

  buf[BUFFER_SIZE] = '\n';
  cout << buf << endl;

	// assign to string
	ostr.assign(buf);

	// -- Deallocate Memory --
  free(buf);
}

void write_to_pipe(int& fd, const char* input, size_t size) {
	if(write(fd, input, sizeof(char) * size) < 0)
    cerr << "Error writing to pipe" << endl;
}

/**
 * Read the directory contents and save location of files in the directory.
 *
 * @return int - 0 to indicate success and  -1 to indicate failure
 */
int read_dir_contents(const char* dirname, map<int, string>& contents, bool is_input) {

  DIR* dirp;
  struct dirent* dp;
  char* pos_str = (char*) malloc((POS_SUBSTR_LEN+1)*sizeof(char));
  int lower_index;
  
	// Input directory
  if(is_input) {
    dirp = opendir(INPUT_DIR);
    lower_index = INPUT_SUBSTR_L;
  } else {
    dirp = opendir(OUTPUT_DIR);
    lower_index = OUTPUT_SUBSTR_L;
  }

  while((dp = readdir(dirp)) != NULL) { // read files in directory
		if(dp->d_name[0] == '.') // skip hidden files and directories
      continue;
		
    pos_str = strncpy(pos_str, &(dp->d_name[lower_index]), POS_SUBSTR_LEN); // copy 2 characters
    pos_str[POS_SUBSTR_LEN] = '\n'; // manual nul-byte character
    int pos_num = atoi(pos_str);
    string path = resolve_path(dirname, dp->d_name); // store file path
    contents[pos_num] = path; // map number to file patt
    cout << "path: " << pos_num << " -> " << path << endl;
  }
 
  closedir(dirp); // close directory
  free(pos_str);
  free(dp);
  return 0;
}

string resolve_path(const char* basepath, const char* filepath) {
  char* cpath = (char*) calloc(sizeof(char), strlen(basepath) + strlen(filepath) + 2);
  if(cpath == NULL)
    throw runtime_error("Could not allocate memory to resolve file path.");
  cpath = strcpy(cpath, basepath);
  cpath = strcat(cpath, "/");
  string path = string(strcat(cpath, filepath));
  free(cpath);
  return path;
}

void free_memory(map<int, string>& inputMap, map<int, string>& outputMap) {
  inputMap.clear();
  outputMap.clear();
}
