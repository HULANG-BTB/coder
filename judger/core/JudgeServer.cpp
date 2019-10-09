#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <cstdlib>
#include <csignal>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <cstring>
#include <cstdarg>
#include <csignal>
#include <sys/file.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctime>
#include <mysql/mysql.h>

using namespace std;

#define BUFF_SIZE 1024

map<string, string> settings;
MYSQL *mysqlConn;
MYSQL_RES *mysqlRes;
MYSQL_ROW mysqlRow;

stringstream sstream;
string query;

/**
 * 删除字符串首尾空白字符 
 */
void trimString(string & val) {
  size_t last = val.find_last_not_of(" \r\n\t\'\",");
  if (last != val.npos) {
    val = val.substr(0, last+1);
    
  }
  size_t first = val.find_first_not_of(" \r\n\t\'\",");
  if (first != val.npos) {
    val = val.substr(first, val.size());
  }
}

/**
 * 获得PHP配置属性值 
 */
void readSetOption(string & line, string & key, string & val) {
  size_t one_t = line.find("=>");
  key = line.substr(0, one_t);
  val = line.substr(one_t+2, line.size()-1);
  trimString(key);
  trimString(val);
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

/**
 * 日志写入程序 
 */
void vlog(const char* fmt, ...) {
  va_list ap;
  char log_buffer[4096];
  time_t current;
  time(&current);
  char time_buffter[100];
  strftime(time_buffter, sizeof(time_buffter), " [ %Y-%m-%d %H:%M:%S ] ",localtime(&current) );
  fstream file;
  file.open(getWorkDir("/log/JudgeServer.log"), ios::out | ios::app | ios::ate);
  va_start(ap, fmt);
  sprintf(log_buffer, fmt, ap);
  file << time_buffter << log_buffer << endl;
  va_end(ap);
  file.close();
}


/**
 * 创建守护程序
 */
int daemon_init() {

  // 检测是否重复运行
  //    暂未实现
  // --------------

  pid_t pidApp;
  pidApp = fork();
  if (pidApp < 0) {
    cout << "Fork创建进程失败！" << endl;
    return -1;
  }
  if (0 != pidApp) {
    cout << "服务启动成功！" << endl;
    cout << "Pid: " << pidApp << endl;
    // 父进程退出
    exit(0);
  }
  // 子进程继续
  setsid(); // 脱离父进程 
  chdir(getWorkDir().c_str());// 修改工作目录
  umask(0); // 清除文件属性
  close(0); // 关闭stdin
  close(1); // 关闭stdout
  close(2); // 关闭stderr
  fstream pidFile;
  pidFile.open(getWorkDir("/etc/JudgeServer.pid"));
  pidFile << pidApp ;
  pidFile.close();

  int fd = open( getWorkDir("/log/log.log").c_str() , O_RDWR );
	dup2( fd, 0 );
	dup2( fd, 1 );
	dup2( fd, 2 );
	if ( fd > 2 ){
		close( fd );
	}

  return 0;
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
 * 从数据库获取任务列表 
 * 参数 数组 接收任务列表
 * 返回值 int 返回任务条数
 */
int getJobList(int *jobList) {
  int solution = 0;
  sstream.str("");
  sstream << "SELECT `sid` FROM `solution` WHERE `result`=0 OR `result`=1 ORDER BY `create_time` ASC LIMIT " << settings["OJ_RUN_MAX"] << " ;";
  query = sstream.str();
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  mysqlRes = mysql_store_result(mysqlConn);
  while ((mysqlRow = mysql_fetch_row(mysqlRes)) != NULL) jobList[solution++] = atoi(mysqlRow[0]);
  return solution;
}

void goWork() {
  int *jobList = new int[atoi(settings["OJ_RUN_MAX"].c_str())+5];
  int jobs = getJobList(jobList);
  int finished = 0;
  cout << "Jobs: " << jobs << endl; 
  // 启动子任务
  for (int i = 0; i < jobs; i++)
  {
    sstream.str("");
    cout << jobList[i] << endl;
    sstream << getWorkDir("/core/JudgeClient") << " " << jobList[i] << " " << i << " ";
    cout << sstream.str() << endl;
    pid_t pidApp = fork();
    if (pidApp == 0) {
      run_cmd_argv(sstream.str());
      exit(0);
    }
    sstream.str("");
  }
  while (finished < jobs) {
    pid_t pidApp = 0;
    while ((pidApp = waitpid(-1, NULL, WNOHANG)) > 0) {
      finished++;
    }
  }
  cout << "任务完成!" << endl;
  delete jobList;
}

void initMysql() {

  char buffer[BUFF_SIZE];
  string workPath;
  getcwd(buffer, BUFF_SIZE);
  workPath = buffer;
  string configFilePath = workPath + "/../../config/database.php";
  ifstream in;
  cout << "读取数据库配置信息..." << endl;
  in.open(configFilePath, ios::in);
  while(!in.eof()) {
    string line;
    getline(in, line);
    if (line.find("hostname") != line.npos || line.find("username") != line.npos || line.find("password") != line.npos || line.find("hostport") != line.npos || line.find("database") != line.npos) {
      string key, val;
      readSetOption(line, key, val);
      settings[key] = val;
    }
  }
  in.close();
  cout << "读取数据库配置成功！" << endl;
  cout << "初始化数据库..." << endl;
  mysqlConn = mysql_init(NULL);
  if (mysql_real_connect(mysqlConn, settings["hostname"].c_str(), settings["username"].c_str(), settings["password"].c_str(), settings["database"].c_str(), atoi(settings["hostport"].c_str()), NULL, 0) == NULL) {
    cout << "连接数据库失败..." << endl;
    cout << "服务启动失败！" << endl;
    exit(0);
  }
  cout << "连接数据库成功！" << endl;
  cout << "读取数据库配置..." << endl;
  query = "SELECT * FROM `option` WHERE 1";
  mysql_real_query(mysqlConn, query.c_str(), query.size());
  mysqlRes = mysql_store_result(mysqlConn);
  while (NULL != mysqlRes && (mysqlRow = mysql_fetch_row(mysqlRes)) != NULL) {
    settings[mysqlRow[0]] = mysqlRow[1];
  }
  cout << "读取数据库配置成功！" << endl;
}

int main(int argc, char* argv[]) {

  // daemon_init();

  initMysql();


  // for (map<string, string>::iterator it = settings.begin(); it != settings.end(); it++)
  // {
  //   cout << it->first << " ---- " << it->second << endl;
  // }
  
  // cout << getWorkDir() << endl;

  while (1) {

    goWork();
    cout << "Sleep " << atoi(settings["OJ_SLEEP_TIME"].c_str()) << " ms" << endl;
    vlog("Sleep %d ms ... ", atoi(settings["OJ_SLEEP_TIME"].c_str()));
    sleep(atoi(settings["OJ_SLEEP_TIME"].c_str()));
  };

}