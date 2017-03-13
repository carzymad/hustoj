/*********************************************************
 * Author			: crazy_mad
 * Last modified	: 2017-03-05 17:48
 * Filename			: algorithm.cc
 * Description		: 配合hustoj使用的algorithm模块，用于
 *					  检查语法
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 5120

MYSQL *conn;				// 预留的mysql连接指针
static char oj_home[BUFFER_SIZE];
static char host_name[BUFFER_SIZE];
static char user_name[BUFFER_SIZE];
static char password[BUFFER_SIZE];
static char db_name[BUFFER_SIZE];
static int port_number;
static int p_id;			// 题目编号
static int statu = 0;					// 当前读取的状态（注释、括号、引号）
/*
 * 1 单行注释
 * 2 多行注释 
 * 3 小括号
 * 4 中括号 
 * 5 大括号
 * 6 空白字符
 * 7 双引号状态
 */

void init_parameters(int argc, char *argv[], char *file_name) {
	if (argc <= 1) {
		printf("缺少命令行参数!\n");
		exit(-1);
	} else if (argc > 1) {
		strcpy(file_name, argv[1]);
		if (argc > 2) {
			sscanf(argv[2], "%d", &p_id);
			if (argc > 3) {
				strcpy(oj_home, argv[3]);
			}
		}
	}
}
int after_equal(char * c) {
	int i = 0;
	for (; c[i] != '\0' && c[i] != '='; i++)
		;
	return ++i;
}
void trim(char * c) {
	char buf[BUFFER_SIZE];
	char * start, *end;
	strcpy(buf, c);
	start = buf;
	while (isspace(*start))
		start++;
	end = start;
	while (!isspace(*end))
		end++;
	*end = '\0';
	strcpy(c, start);
}
bool read_buf(char * buf, const char * key, char * value) {
	if (strncmp(buf, key, strlen(key)) == 0) {				// 如果参数1字符串等于参数2字符串，则将参数3字符串赋值为参数2
		strcpy(value, buf + after_equal(buf));
		trim(value);
		//if (DEBUG)
		//	printf("%s\n", value);
		return 1;
	}
	return 0;
}
void read_int(char * buf, const char * key, int * value) {
	char buf2[BUFFER_SIZE];
	if (read_buf(buf, key, buf2))
		sscanf(buf2, "%d", value);

}
void init_mysql_conf() {
	FILE *fp = NULL;
	char buf[BUFFER_SIZE];
	host_name[0] = 0;
	user_name[0] = 0;
	password[0] = 0;
	db_name[0] = 0;
	port_number = 3306;
	sprintf(buf, "%s/etc/judge.conf", oj_home);
	fp = fopen(buf, "re");
	if (fp != NULL) {					// crazy_mad注释：读取配置文件并给相关字符串变量赋值
		while (fgets(buf, BUFFER_SIZE - 1, fp)) {
			read_buf(buf, "OJ_HOST_NAME", host_name);
			read_buf(buf, "OJ_USER_NAME", user_name);
			read_buf(buf, "OJ_PASSWORD", password);
			read_buf(buf, "OJ_DB_NAME", db_name);
			read_int(buf, "OJ_PORT_NUMBER", &port_number);
		}
		fclose(fp);
	}
	//printf("%s\n%s\n%s\n%s\n%d\n", host_name, user_name, password, db_name, port_number);
}
int init_mysql_conn() {
	conn = mysql_init(NULL);
	const char timeout = 30;
	mysql_options(conn, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);

	if (!mysql_real_connect(conn, host_name, user_name, password, db_name, port_number, 0, 0)) {
		return 0;
	}
	const char *utf8sql = "set names utf8";
	if (mysql_real_query(conn, utf8sql, strlen(utf8sql))) {
		return 0;
	}
	return 1;
}
void get_keyword_mysql() {
	char sql[BUFFER_SIZE];
	MYSQL_RES *res;
	MYSQL_ROW row;
	sprintf(sql, "SELECT key_word from key_words where problem_id=%d", p_id);
	mysql_real_query(conn, sql, strlen(sql));
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	printf("%s\n", row[0]);
	//mysql_free_result(res);
}
// 寻找line中非标识符的位置在哪里
int find_no_identifier(char *line) {
	if (isspace(line[0]) && line[0] != '\n') {	// 空格、制表符之类的空白字符
		statu = 6;
		return 0;
	}
	int i, len = strlen(line);
	for (i = 0; i < len; i++) {
		if (line[i] < '0' || line[i] > '9') {	// 非数字
			if (!((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z'))) { 	// 非字母
				if (line[i] != '_')	{			// 非下划线
					if (line[i] == '/' && i != len-1 && line[i+1] == '/') {		// 单行注释
						statu = 1;
						return len-1;			// 这里随便返回几都可以，但是为了逻辑通顺，我这里返回了长度
					} else if (line[i] == '/' && i != len-1 && line[i+1] == '*') {	// 多行注释
						statu = 2;
						return i;
					} else if (line[i] == '"' && line[i-1] != '\\' && statu != 7) {	// 字符串
						statu = 7;
						return i;
					}
					if (i == 0) {
						return 0;
					} else {
						return i-1;
					}
				}
			}
		}
	}
	return i-1;
}
// 注释、字符串处理
char *find_notes_end(FILE *s_code, char *line, char *ptr) {
	do {
		int len = strlen(line);
		for (int i = 0; i < len; i++) {
			if (statu == 2 && ptr[i] == '*' && i != len-1 && ptr[i+1] == '/') {
				statu = 0;
				return (ptr+i+2);
			} else if (statu == 7 && ptr[i] == '"' && ptr[i-1] != '\\') {
				statu = 0;
				return (ptr+i+1);
			}
		}
	} while (fgets(line, 256, s_code));
	return NULL;
}

void check_algorithm(FILE *s_code) {
	char line[256] = { 0 };
	char body[256] = { 0 };
	char *ptr;
	int ret, len;
	//while (fscanf(s_code, "%s", line) != EOF) {
	while (fgets(line, 256, s_code)) {
		ptr = line;
		len = strlen(line);
		while (ptr <= (char*)line+len-1) {
			statu = 0;
			ret = find_no_identifier(ptr);
			if (statu == 1) {
				break;
			} else if (statu == 2 || statu == 7) {
				ptr = find_notes_end(s_code, line, ptr+1);		// 找到注释结束部分
				if (!ptr) {			// 如果返回值是NULL的话，说明已经读到文件尾了
					break;
				}
				len = strlen(line);					// 重新为line的长度赋值
			} else if (statu == 6) {	// 如果读取到空白字符的话，直接跳过去，不做处理
				ptr += 1;
				continue;
			}
			strcpy(body, ptr);
			body[ret+1] = '\0';
			//printf("%s\t", body);
			if (!strcmp(body, "switch")) {
				printf("使用了swtich语句\n");
				exit(0);
			}
			ptr += (ret+1);			// 因为ptr[ret]是终止符，所以还要往后挪一格
		}
		//printf("\n");
	}
}

// argv[1]:file_path，argv[2]:p_id
int main(int argc, char* argv[]) {
	FILE *s_code;			// 源代码文件指针
	char file_name[256] = { 0 };			// 源代码文件名
	printf("\nalgorithm begin...\n\n");

	init_parameters(argc, argv, file_name);
	init_mysql_conf();
	if (!init_mysql_conn()) {
		printf("mysql connect error:%s", mysql_error(conn));
		exit(1);
	}
	get_keyword_mysql();

	s_code = fopen(file_name, "r");

	if (s_code == NULL) {
		printf("代开文件失败!\n");
		perror("file open error:");
		exit(2);
	}

	check_algorithm(s_code);
	fclose(s_code);
	mysql_close(conn);

	return 1;
}

/*
 * 返回值说明
 * 0 代码符合要求
 * 1 代码不符合要求
 * 2 打开文件失败
 */
