#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <csignal>
#include <string>
#include <sstream>
#include <fstream>
#include <codecvt>
#include <map>
#include <set>
#include <cstring>
#include <cstdarg>
#include <csignal>
#include <algorithm>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <ctime>
#include <dirent.h>
#include <mysql/mysql.h>

using namespace std;

#define BUFF_SIZE 1024 // 缓冲大小 1024
#define STD_MB 1048576LL // 标准1MB数据长度

map<string, string> settings;
MYSQL *mysqlConn;
MYSQL_RES *mysqlRes;
MYSQL_ROW mysqlRow;

stringstream sstream;
string query;

map<string, int> testFileList;

int time_limit, memory_limit;
int spj, solved, submit;
int sid, pid, uid, cid;
string code;
string WORK_DIR;
int time_used, memory_used, result;
int language;
float pass_rate;
int mode;

string LAZYOJ_RESULT = "AC";
float LAZYOJ_AC_NUM = 0.0;
int LAZYOJ_AC_TIME = 0;

static string OJ_DATA_HOME;
static string OJ_CORE_HOME;
static string OJ_RUN_HOME;
static string OJ_WORK_HOME;

struct user_regs_struct {
        unsigned long long uregs[38];
};

/**
 * 删除字符串首尾空白字符 
 */
void trimString(string &val)
{
  size_t last = val.find_last_not_of(" \r\n\t\'\",");
  if (last != val.npos)
  {
    val = val.substr(0, last + 1);
  }
  size_t first = val.find_first_not_of(" \r\n\t\'\",");
  if (first != val.npos)
  {
    val = val.substr(first, val.size());
  }
}

void deleteAllMark(string &val, string mark = " ") {
  size_t pos = val.find_first_of(mark);
  while (pos != val.npos) {
    val.replace(pos, mark.size(), "");
    pos = val.find_first_of(mark);
  }
}

/**
 * 获得PHP配置属性值 
 */
void readSetOption(string &line, string &key, string &val)
{
  size_t one_t = line.find("=>");
  key = line.substr(0, one_t);
  val = line.substr(one_t + 2, line.size() - 1);
  trimString(key);
  trimString(val);
}

void encodeString(string & val) {
  string::size_type index;
  while((index = val.find("\r", index)) != val.npos) {
    val = val.substr(0, index) + "\\r" + val.substr(index+1, val.size() - (index+1));
    index += 2;
  }
  index = 0;
  while((index = val.find("\n", index)) != val.npos) {
    val = val.substr(0, index) + "\\n" + val.substr(index+1, val.size() - (index+1));
    index += 2;
  }
  index = 0;
  while((index = val.find("\'", index)) != val.npos) {
    val = val.substr(0, index) + "\\'" + val.substr(index+1, val.size() - (index+1));
    index += 2;
  }
  index = 0;
  while((index = val.find("\"", index)) != val.npos) {
    val = val.substr(0, index) + "\\\"" + val.substr(index+1, val.size() - (index+1));
    index += 2;
  }
}

void getProblemInfo()
{
  sstream << "SELECT `time`, `memory`, `spj` FROM `problem` WHERE `pid`=" << pid << "";
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  mysqlRes = mysql_store_result(mysqlConn);
  while (NULL != mysqlRes && (mysqlRow = mysql_fetch_row(mysqlRes)) != NULL)
  {
    time_limit = atoi(mysqlRow[0]);
    memory_limit = atoi(mysqlRow[1]);
    spj = atoi(mysqlRow[2]);
    // submit = atoi(mysqlRow[3]);
    // solved = atoi(mysqlRow[4]);
  }
  sstream.str("");
}
void setProblemInfo()
{
  sstream << "UPDATE `problem` SET `sloved`=" << solved << " `submit`=" << submit << " WHERE `pid`=" << pid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void getSolutionInfo()
{
  sstream << "SELECT `pid`, `uid`, `cid`, `code`, `language` FROM `solution` WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  mysqlRes = mysql_store_result(mysqlConn);
  while (NULL != mysqlRes && (mysqlRow = mysql_fetch_row(mysqlRes)) != NULL)
  {
    pid = atoi(mysqlRow[0]);
    uid = atoi(mysqlRow[1]);
    cid = atoi(mysqlRow[2]);
    code = string(mysqlRow[3]);
    language = atoi(mysqlRow[4]);
  }
  sstream.str("");
}
void getJudgeMode()
{
  sstream << "SELECT `type` FROM `contest` WHERE `cid`=" << cid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  mysqlRes = mysql_store_result(mysqlConn);
  while (NULL != mysqlRes && (mysqlRow = mysql_fetch_row(mysqlRes)) != NULL)
  {
    mode = atoi(mysqlRow[0]);
  }
  sstream.str("");
}
void changeToBuild()
{
  sstream << "UPDATE `solution` SET `result`=2 WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToIO()
{
  sstream << "UPDATE `solution` SET `result`=3 WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToAC()
{
  sstream << "UPDATE `solution` SET `result`=4, `time`=" << time_used << ", `memory`=" << memory_used << ", `pass_rate`=" << pass_rate << " WHERE `sid`=" << sid;
  query = sstream.str();
  cout << query << endl;
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
  sstream << "UPDATE `problem` SET `solved`=`solved`+1 WHERE `pid`=" << pid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToPE()
{
  fstream file;
  file.open(WORK_DIR+"/runtimeinfo.txt", ios::in);
  sstream << file.rdbuf();
  file.close();
  string runtimeInfo = sstream.str();
  sstream.str("");
  encodeString(runtimeInfo);
  sstream << "UPDATE `solution` SET `result`=5, `time`=" << time_used << ", `memory`=" << memory_used << ", `pass_rate`=" << pass_rate << ", `compile_info`='" << runtimeInfo << "' WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToWA()
{
  fstream file;
  file.open(WORK_DIR+"/runtimeinfo.txt", ios::in);
  sstream << file.rdbuf();
  file.close();
  string runtimeInfo = sstream.str();
  sstream.str("");
  encodeString(runtimeInfo);
  sstream << "UPDATE `solution` SET `result`=6, `time`=" << time_used << ", `memory`=" << memory_used << ", `pass_rate`=" << pass_rate << ", `compile_info`='" << runtimeInfo << "' WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToTLE()
{
  sstream << "UPDATE `solution` SET `result`=7, `time`=" << time_used << ", `memory`=" << memory_used << ", `pass_rate`=" << pass_rate << " WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToMLE()
{
  sstream << "UPDATE `solution` SET `result`=8, `time`=" << time_used << ", `memory`=" << memory_used << ", `pass_rate`=" << pass_rate << " WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToOLE()
{
  sstream << "UPDATE `solution` SET `result`=9, `time`=" << time_used << ", `memory`=" << memory_used << ", `pass_rate`=" << pass_rate << " WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToRE()
{
  sstream << "UPDATE `solution` SET `result`=10, `time`=" << time_used << ", `memory`=" << memory_used << ", `pass_rate`=" << pass_rate << " WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}
void changeToCE()
{
  fstream file;
  file.open(WORK_DIR+"/compile.txt", ios::in);
  sstream << file.rdbuf();
  file.close();
  string conpileInfo = sstream.str();
  sstream.str("");
  encodeString(conpileInfo);
  sstream << "UPDATE `solution` SET `result`=11, compile_info='" << conpileInfo << "' WHERE `sid`=" << sid;
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  sstream.str("");
}

/**
 * 初始化数据库配置 
 */
void initMysql()
{
  char buffer[BUFF_SIZE];
  string workPath;
  getcwd(buffer, BUFF_SIZE);
  workPath = buffer;
  string configFilePath = workPath + "/../../config/database.php";
  ifstream in;
  cout << "读取数据库配置信息..." << endl;
  in.open(configFilePath, ios::in);
  while (!in.eof())
  {
    string line;
    getline(in, line);
    if (line.find("hostname") != line.npos || line.find("username") != line.npos || line.find("password") != line.npos || line.find("hostport") != line.npos || line.find("database") != line.npos)
    {
      string key, val;
      readSetOption(line, key, val);
      settings[key] = val;
    }
  }
  in.close();
  cout << "读取数据库配置成功！" << endl;
  cout << "尝试连接数据库..." << endl;
  mysqlConn = mysql_init(NULL);
  if (mysql_real_connect(mysqlConn, settings["hostname"].c_str(), settings["username"].c_str(), settings["password"].c_str(), settings["database"].c_str(), atoi(settings["hostport"].c_str()), NULL, 0) == NULL)
  {
    cout << "连接数据库失败..." << endl;
    cout << "服务启动失败！" << endl;
    exit(0);
  }
  cout << "连接数据库成功！" << endl;
  cout << "读取数据库配置..." << endl;
  query = "SELECT * FROM `option` WHERE 1";
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  mysqlRes = mysql_store_result(mysqlConn);
  while (NULL != mysqlRes && (mysqlRow = mysql_fetch_row(mysqlRes)) != NULL)
  {
    settings[mysqlRow[0]] = mysqlRow[1];
  }
  cout << "读取数据库配置成功！" << endl;
}

/**
 * 获取当前工作目录 
 * 参数1 附加目录
 */
string getWorkDir(string append = "") {
  char buffer[BUFF_SIZE];
  getcwd(buffer, BUFF_SIZE);
  string workPath = buffer;
  workPath = workPath.substr(0, workPath.find_last_of('/')) + append;
  return workPath;
}

void initWorkDir(int argc,char *argv[]) {
  OJ_CORE_HOME = getWorkDir("/core");

  sstream << getWorkDir("/data/") << pid ;
  OJ_DATA_HOME = sstream.str();
  sstream.str("");

  OJ_RUN_HOME = getWorkDir("/run");
  OJ_WORK_HOME = getWorkDir("/run/node_") + argv[2];
}

void releaseWorkDir(int argc,char *argv[]) {
  string dirPath = OJ_WORK_HOME + "/*";
  sstream << "rm -rf " << dirPath ;
  system(sstream.str().c_str());
  sstream.str("");
}

bool run_cmd(const char *fmt, ...) {
  va_list ap;
  bool flag = false;
  char cmd_buffer[BUFF_SIZE];
  va_start(ap, fmt);
  vsprintf(cmd_buffer, fmt, ap);
  flag = system(cmd_buffer);
  va_end(ap);
  return flag;
}

bool run_cmd_argv(string cmd) {
  trimString(cmd);
  cmd.push_back(' ');
  char* vlist[30];
  memset((void*)vlist, 0, sizeof(vlist));
  string::size_type start = 0;
  string::size_type index = cmd.find_first_of(' ', start);
  int t = 0;
  while (index != cmd.npos)
  {
    string param = cmd.substr(start, index-start);
    char *temp = new char[param.size()+1];
    strcpy(temp, param.c_str());
    vlist[t++] = temp;
    start = index + 1;
    index = cmd.find_first_of(' ', start);
  }
  execvp(vlist[0], (char *const *)vlist);
  return true;
}


/**
 * 创建运行目录 
 */
void makeWorkSpace(char *jobId) {
  sstream << getWorkDir("/run/node_") << jobId;
  WORK_DIR = sstream.str();
  sstream.str("");
  // 创建目录
  run_cmd("mkdir -p %s/", WORK_DIR.c_str());
  // 清空目录
  run_cmd("rm -rf %s/*", WORK_DIR.c_str());
  // 修改当前目录
  chdir(WORK_DIR.c_str());
  cout << "当前工作目录: " << WORK_DIR << endl;
}

/**
 * 是否为输入文件 标志:文件名含有.in 
 */
bool isInFile(string filename) {
  return filename.find(".in") != filename.npos;
}

/**
 * 是否为输入文件 标志:文件名含有.out 
 */
bool isOutFile(string filename) {
  return filename.find(".out") != filename.npos;
}

void saveProblemToFile() {
  sstream << "OJ_LANG_EXT_" << language;
  fstream file;
  file.open(WORK_DIR + "/Main." + settings[sstream.str()], ios::ate | ios::out);
  cout << "写入用户代码文件: " << WORK_DIR << "/Main." + settings[sstream.str()] << endl;
  file << code;
  file.close();
  sstream.str("");
}

/**
 * 编译文件
 */
int compile() {
  sstream << "OJ_COMPILE_" << language ;
  string compile_cmd = settings[sstream.str()];
  sstream.str("");

  pid_t pidApp = fork();

  if (pidApp == 0) {
    // 子进程 执行编译

    struct rlimit LIMIT;
    // 限制CPU 使用时间 最大5秒
    LIMIT.rlim_cur = 5;
    LIMIT.rlim_max = 5;
    setrlimit(RLIMIT_CPU, &LIMIT);
    alarm(5);

    // 限制可以创建的文件的最大字节 最大长度 50MB
    LIMIT.rlim_cur = 50 * STD_MB;
    LIMIT.rlim_max = 50 * STD_MB;
    setrlimit(RLIMIT_FSIZE, &LIMIT);

    // 限制子程序内存 最大512M
    LIMIT.rlim_cur = 512 * STD_MB;
    LIMIT.rlim_max = 512 * STD_MB;
    setrlimit(RLIMIT_AS, &LIMIT);

    // 重定向输入输出到文件 
    freopen("compile.txt", "w+", stdout);
    freopen("compile.txt", "w+", stderr);

    // 执行编译
    run_cmd_argv(compile_cmd);

    // 子进程退出
    exit(0);
  } else {
    // 父进程 收集信息

    // 等待子进程执行完毕
    int status = 0;
    waitpid(pidApp, &status, 0);
    cout << "编译执行结束..." << endl;
    cout << "编译状态: " << status << endl;
    return status;
  }
  return 0;
}

/**
 * 获取测试文件列表 
 */
void get_test_file() {
  DIR *dir;
  struct dirent * ptr;
  // cout << OJ_DATA_HOME << endl;
  dir = opendir(OJ_DATA_HOME.c_str());
  while ((ptr = readdir(dir)) != NULL) {
    // cout << "file -----> " << ptr->d_name << endl;
    if (isInFile(ptr->d_name)) {
      string fullName = ptr->d_name;
      string fileName = fullName.substr(0, fullName.find_last_of(".in") - 2);
      testFileList.find(fileName) == testFileList.end() ? testFileList[fileName] = 1 : testFileList[fileName] = 2;
    }
    if (isOutFile(ptr->d_name)) {
      string fullName = ptr->d_name;
      string fileName = fullName.substr(0, fullName.find_last_of(".out") - 3);
      testFileList.find(fileName) == testFileList.end() ? testFileList[fileName] = 1 : testFileList[fileName] = 2;
    }
  }
  closedir(dir);
  /*
  for (map<string, int>::iterator it = testFileList.begin(); it != testFileList.end(); it++)
  {
    cout << it->first << " ---> " << it->second << endl;
  }
  */
}

/**
 * 连接测试文件 
 */

void copy_test_file(string filename) {
  // 为测试点复制文件
  cout << "为测试点复制文件: " << filename << endl;
  string inFilePath = OJ_DATA_HOME + "/" + filename + ".in";
  string outFilePath = OJ_DATA_HOME + "/" + filename + ".out";
  string toInFilePath = OJ_WORK_HOME + "/" + filename + ".in";
  string toOutFilePath = OJ_WORK_HOME + "/" + filename + ".out";
  sstream << "cp " << inFilePath << " " << toInFilePath;
  system(sstream.str().c_str());
  sstream.str("");
  sstream << "cp " << outFilePath << " " << toOutFilePath;
  system(sstream.str().c_str());
  sstream.str("");
}

void del_test_file(string filename) {
  // 测试完成删除测试文件
  cout << "删除完成的测试点文件: " << filename << endl;
  string stdInFilePath = OJ_WORK_HOME + "/" + filename + ".in";
  string stdOutFilePath = OJ_WORK_HOME + "/" + filename + ".out";
  string userOutFilePath = OJ_WORK_HOME + "/" + filename + ".user.out";
  sstream << "rm -rf " << stdInFilePath ;
  system(sstream.str().c_str());
  sstream.str("");
  sstream << "rm -rf " << stdOutFilePath ;
  system(sstream.str().c_str());
  sstream.str("");
  sstream << "rm -rf " << userOutFilePath ;
  system(sstream.str().c_str());
  sstream.str("");
}

int get_proc_status(pid_t pidApp, string key) {
  sstream << "/proc/" << pidApp << "/status";
  string filename = sstream.str();
  sstream.str("");
  int ret = 0;
  fstream file;
  file.open(filename, ios::in | ios::binary);
  if (!file.is_open()) return 0;
  while(!file.eof()) {
    string line;
    getline(file, line);
    if (line.find(key) != line.npos) {
      sscanf(line.c_str() + line.find_first_of(key) + key.size() + 1, "%d", &ret);
    }
  }
  file.close();
  return ret;
}

bool get_file_size(string filename) {
  fstream file;
  file.open(filename, ios::in);
  if (!file.is_open()) return 0;
  file.seekg(0, file.end);
  size_t fileSize = file.tellg();
  return fileSize;
}

void run_solution(string filename) {

  // 设置优先级最高
  nice(19);

  // 执行命令
  string cmd = "./Main"; 
  chdir(OJ_WORK_HOME.c_str());

  // 设置跟随
  ptrace(PTRACE_TRACEME, 0, NULL, NULL);
  
  struct rlimit LIMIT;
  // 限制CPU 使用时间 
  LIMIT.rlim_cur = time_limit * 3 / 2;
  LIMIT.rlim_max = time_limit * 3 / 2;
  setrlimit(RLIMIT_CPU, &LIMIT);
  alarm(time_limit);
  cout << "时间限制: " << LIMIT.rlim_cur << endl;

  // 限制可以创建的文件的最大字节 最大长度 50MB
  LIMIT.rlim_cur = 50 * STD_MB / 2 * 3;
  LIMIT.rlim_max = 50 * STD_MB / 2 * 3;
  setrlimit(RLIMIT_FSIZE, &LIMIT);
  cout << "文件限制: " << LIMIT.rlim_cur << endl;

  // 限制子程序内存 最大512M
  LIMIT.rlim_cur = memory_limit * STD_MB / 2 * 3;
  LIMIT.rlim_max = memory_limit * STD_MB / 2 * 3;
  setrlimit(RLIMIT_AS, &LIMIT);
  cout << "内存限制: " << LIMIT.rlim_cur << endl;

  // 限制子程序进程 最大进程数 1 
  LIMIT.rlim_cur = 1;
  LIMIT.rlim_max = 1;
  setrlimit(RLIMIT_NPROC, &LIMIT);
  cout << "进程限制: " << LIMIT.rlim_cur << endl;
  
  // 限制堆栈
	LIMIT.rlim_cur = STD_MB << 7;
	LIMIT.rlim_max = STD_MB << 7;
	setrlimit(RLIMIT_STACK, &LIMIT);
  cout << "堆栈限制: " << LIMIT.rlim_cur << endl;
  
  // 重定向输入输出到文件 
  string inFile = filename + ".in";
  string outFile = filename + ".user.out";
  string errFile = filename + ".user.err";

  freopen(inFile.c_str(), "r+", stdin);
  freopen(outFile.c_str(), "w+", stdout);
  freopen(errFile.c_str(), "w+", stderr);

  // 启动进程
  run_cmd_argv(cmd);

  // 清空错误缓冲区
  fflush(stderr);
  // 退出进程
  exit(0);
}

bool compare_solution(string stdFileName, string userFileName) {

  fstream stdFile, userFile, reInfoFile;
  stdFile.open(stdFileName, ios::in);
  userFile.open(userFileName, ios::in);
  reInfoFile.open("runtimeinfo.txt", ios::ate | ios::app);
  if (!stdFile.is_open() || !userFile.is_open()) return false;
  string lineStd, lineUser;
  int count = 1;
  while (true) {
    lineStd.clear();
    lineUser.clear();
    if (stdFile.eof() && userFile.eof()) {
      LAZYOJ_RESULT = "AC";
      return true;
    }
    if (stdFile.eof() && !userFile.eof()) {
      reInfoFile << "=============" << stdFileName << "=============" << endl;
        reInfoFile << "Solution: " << sid << " Line: " << count << " Result:WA" << endl << "Expected:" << endl;
      reInfoFile << lineStd << endl;
      reInfoFile << "Yours:" << endl;
      reInfoFile << lineUser << endl;
      reInfoFile << "=============" << stdFileName << "=============" << endl;
      reInfoFile << endl;
      LAZYOJ_RESULT = "PE";
      return false;
    }
    if (!stdFile.eof() && userFile.eof()) {
      reInfoFile << "=============" << stdFileName << "=============" << endl;
        reInfoFile << "Solution: " << sid << " Line: " << count << " Result:WA" << endl << "Expected:" << endl;
      reInfoFile << lineStd << endl;
      reInfoFile << "Yours:" << endl;
      reInfoFile << lineUser << endl;
      reInfoFile << "=============" << stdFileName << "=============" << endl;
      reInfoFile << endl;
      LAZYOJ_RESULT = "PE";
      return false;
    }
    getline(stdFile, lineStd);
    getline(userFile, lineUser);
    deleteAllMark(lineStd, "\r");
    deleteAllMark(lineUser, "\r");
    deleteAllMark(lineStd, "\n");
    deleteAllMark(lineUser, "\n");
    if (lineStd != lineUser) {
      string newLineStd = lineStd;
      string newLineUser = lineUser;
      deleteAllMark(newLineStd, " ");
      deleteAllMark(newLineUser, " ");
      if (newLineStd == newLineUser) {
        reInfoFile << "=============" << stdFileName << "=============" << endl;
        reInfoFile << "Solution: " << sid << " Line: " << count << " Result:PE" << endl << "Expected:" << endl;
        reInfoFile << lineStd << endl;
        reInfoFile << "Yours:" << endl;
        reInfoFile << lineUser << endl;
        reInfoFile << "=============" << stdFileName << "=============" << endl;
        reInfoFile << endl;
        LAZYOJ_RESULT = "PE";
        return false;
      } else {
        reInfoFile << "=============" << stdFileName << "=============" << endl;
        reInfoFile << "Solution: " << sid << " Line: " << count << " Result:WA" << endl << "Expected:" << endl;
        reInfoFile << lineStd << endl;
        reInfoFile << "Yours:" << endl;
        reInfoFile << lineUser << endl;
        reInfoFile << "=============" << stdFileName << "=============" << endl;
        reInfoFile << endl;
        LAZYOJ_RESULT = "WA";
        return false;
      }
    }
    count++;
  }
  return true;
}

void listen_solution(pid_t pidApp, string filename) {

  int status = 0;
  bool flag = true;
  struct rusage rused;
  while (true) {
    wait4(pidApp, &status, __WALL, &rused);
    if (flag) {
      // 跟踪 禁止子进程调用服务
      ptrace(PTRACE_SETOPTIONS, pidApp, NULL, PTRACE_O_TRACESYSGOOD
                                              | PTRACE_O_TRACEEXIT
                                              | PTRACE_O_EXITKILL 
                                              | PTRACE_O_TRACECLONE
                                              | PTRACE_O_TRACEFORK
                                              | PTRACE_O_TRACEVFORK
			);
      flag = false;
    }
    
    // 内存超限
    memory_used = max(memory_used, get_proc_status(pidApp, "VmPeak:"));
    if (memory_used > memory_limit * STD_MB * 1024) {
      cout << "内存超限" << endl;
      LAZYOJ_RESULT = "MLE";
      // 发送结束信号
      ptrace(PTRACE_KILL, pidApp, NULL, NULL);
      break;
    }

    // 正常结束
    if (WIFEXITED(status)) {
      break;
    }

    // 接收到信号
    if (WEXITSTATUS(status)) {
      int sig = WEXITSTATUS(status);
      if (sig != 5 && sig != 133 && sig != 0) {
        switch (sig)
        {
        case SIGCHLD:
        case SIGALRM:
          alarm(0);
        case SIGKILL:
        case SIGXCPU:
          cout << "时间超限" << endl;
          LAZYOJ_RESULT = "TLE";
          break;
        case SIGXFSZ:
          cout << "输出超限" << endl;
          LAZYOJ_RESULT = "OLE";
          break;
        default:
          cout << "运行错误" << endl;
          LAZYOJ_RESULT = "RE";
          break;
        }
        // 发送结束信号
        ptrace(PTRACE_KILL, pidApp, NULL, NULL);
        break;
      }
    }

    // 运行时错误
    if (get_file_size(filename + ".user.err")) {
      cout << "运行错误" << endl;
      LAZYOJ_RESULT = "RE";
      // 发送结束信号
      ptrace(PTRACE_KILL, pidApp, NULL, NULL);
      break;
    }

    // 输出超限
    if (get_file_size(filename + ".user.out") > get_file_size(filename + ".out") * 2 + 1024) {
      cout << "输出超限" << endl;
      LAZYOJ_RESULT = "OLE";
      // 发送结束信号
      ptrace(PTRACE_KILL, pidApp, NULL, NULL);
      break;
    }

    // 异常退出
    if (WIFSIGNALED(status)) {
      int sig = WTERMSIG(status);
      switch (sig)
      {
      case SIGCHLD:
			case SIGALRM:
        alarm(0);
			case SIGKILL:
			case SIGXCPU:
				LAZYOJ_RESULT = "TLE";
				break;
			case SIGXFSZ:
				LAZYOJ_RESULT = "OLE";
				break;
			default:
				LAZYOJ_RESULT = "RE";
        break;
      }
      break;
    }
    ptrace(PTRACE_SYSCALL, pidApp, NULL, NULL);
  }
  long long usedTime = rused.ru_utime.tv_sec * 1000 + rused.ru_utime.tv_usec / 1000;
  usedTime += rused.ru_stime.tv_sec * 1000 + rused.ru_stime.tv_usec / 1000;
  time_used += usedTime;
  cout << "测试结束: " << filename << endl;
  cout << "时间: " << usedTime  << endl;
  if (LAZYOJ_RESULT == "AC") {
    LAZYOJ_AC_NUM += 1.0;
  }
}

void judge_sulution() {

  for (map<string, int>::iterator it = testFileList.begin(); it != testFileList.end(); it++)
  {
    // cout << it->first << " ---> " << it->second << endl;

    if (it->second == 2) {
      string filename = it->first;
      string stdInFileName = OJ_DATA_HOME + "/" + filename + ".in";
      string stdOutFileName = OJ_DATA_HOME + "/" + filename + ".out";
      // 复制测试点文件
      copy_test_file(filename);

      // cout << "标志1" << endl;
      pid_t pidApp = fork();
      if (pidApp == 0) {
        // 子进程执行
        cout << "开始测试: " << filename << endl;
        run_solution(filename);
      } else {
        // 父进程监控
        cout << "Pid: " << pidApp << endl;
        listen_solution(pidApp, filename);
      }
      // 对比输出文件
      bool flag = compare_solution(filename + ".out", filename + ".user.out");
      cout << "结果: " << LAZYOJ_RESULT << endl;
      // 删除测试点文件
      // del_test_file(filename);

      if (flag == false && LAZYOJ_RESULT != "AC" && mode != 1) {
        break;
      }
    }
  }
}

bool update_solution() {
  
  pass_rate = LAZYOJ_AC_NUM / testFileList.size();

  if (LAZYOJ_RESULT == "AC") {
    changeToAC();
  }
  else if (LAZYOJ_RESULT == "RE") {
    changeToRE();
  }
  else if (LAZYOJ_RESULT == "PE") {
    changeToPE();
  }
  else if (LAZYOJ_RESULT == "OLE") {
    changeToOLE();
  }
  else if (LAZYOJ_RESULT == "MLE") {
    changeToMLE();
  }
  else if (LAZYOJ_RESULT == "TLE") {
    changeToTLE();
  }
  else {
    changeToWA();
  }

  return true;
}

void Judge() {
  // 编译文件
  int compileStatus = compile();
  if (compileStatus != 0) {
    // 修改状态 编译失败
    changeToCE();
    exit(0);
  }
  // 修改状态 评测中
  changeToIO();

  // 复制测试文件
  get_test_file();

  // 开始测试
  judge_sulution();

  // 更新信息
  update_solution();

}

void initialize(int argc, char* argv[])
{
  getSolutionInfo();
  getProblemInfo();
  initWorkDir(argc,argv);
  makeWorkSpace(argv[2]);
  saveProblemToFile();
  getJudgeMode();
  Judge();
  // releaseWorkDir(argc, argv);

}

int main(int argc, char *argv[])
{
  sid = atoi(argv[1]);
  initMysql();
  initialize(argc, argv);

  

  return 0;
}