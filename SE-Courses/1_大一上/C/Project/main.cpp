#define _CRT_SECURE_NO_WARNINGS 1
#include<Windows.h>
#include<time.h>
#include<iostream>
#include<conio.h>
using namespace std;
#define COLS 100		// 横长
#define LINES 20		// 竖高
int ifood = 1, checkline = 1;  // 食物个数，跳转至目标行
char ch[2] = { 'd', 'a' }, now_ch[2] = { 'd', 'a' }, userNow[20]; // now_ch存储 默认移动方向
struct SNAKE { COORD coord[50]; int len; }snake[2]{ {3, 1}, {COLS - 3, LINES - 1} }; // 蛇位置以及长度
COORD foodposition[10];//食物位置

void mouseCursor(int*, int*);
void color(int);
void hidecursor();
void cursor(int, int);

void printgame();
void move();
int is_die();
void food();
char arrowMove(char);
void speed();

void printLine(int);
void logon();
void login(int*, char*);
void startUI(int*);
void stopUI(int*);
void deadUI(int);
void endwrite(const char*);

int main() {
	int i, score[2];
	char Tch;
	srand(time(NULL));	// 以时间为种子值
	system("mode con cols=120 lines=50");		// 设置控制台长宽
	for (i = 0; i < 10; i++) {		// 初始化食物位置
		foodposition[i].X = rand() % (COLS - 1) + 1;
		foodposition[i].Y = rand() % (LINES - 1) + 1;
	}
	login(score, userNow);		// 进入登录系统，将记录的历史数据存入score里
	startUI(score);	// 进入开始菜单
	Sleep(300);
	while (1) {
		if (_kbhit()) {		// 通过判断 tch 是否改变来辨别 1P和2P
			Tch = _getch();
			if (Tch == arrowMove(Tch)) {		// 1P
				ch[0] = Tch;
				if (ch[0] != 'a' && ch[0] != 's' && ch[0] != 'd' && ch[0] != 'w')
					ch[0] = now_ch[0];
			}
			else {		// 2P
				ch[1] = arrowMove(Tch);
				if (ch[1] != 'a' && ch[1] != 's' && ch[1] != 'd' && ch[1] != 'w')
					ch[1] = now_ch[1];
			}
		}
		if (GetAsyncKeyState(VK_LBUTTON))	// 按鼠标右键进入暂停菜单
			stopUI(score);
		move();		// 调用移动，食物函数改变蛇参数
		food();
		printgame();		// 打印游戏界面
		if (is_die() != 0) {		// 死亡进入结束界面
			for (i = 0; i < 3; i++) {
				Sleep(300);
				system("cls");
				Sleep(300);
				printgame();
			}
			deadUI(is_die());
		}
		endwrite("save");
		speed();
	}
	return 0;
}
void mouseCursor(int* x, int* y) {
	POINT mouseCoord;	// 用于获取鼠标坐标
	SetConsoleTitle(TEXT("game"));	// 设置窗口名为"game"，Debug时发现若在主函数循环外设置会被改名
	LPRECT consoleCoord = (LPRECT)malloc(sizeof(RECT) + 64);	// 用于存储控制台窗口的信息
	HWND hwnd = FindWindow(NULL, TEXT("game"));    //  查找句柄, 返回坐标
	GetWindowRect(hwnd, consoleCoord);     //  将得到的句柄存在 console坐标里
	GetCursorPos(&mouseCoord);     //  鼠标在窗口的坐标
	*x = (&mouseCoord)->x - consoleCoord->left;      //  获得相对坐标
	*y = (&mouseCoord)->y - consoleCoord->top;
}
void color(int num) {  // 改变颜色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
void hidecursor() {  // 隐藏光标
	CONSOLE_CURSOR_INFO cursor;		// 光标信息
	cursor.bVisible = 0;		// 不可见
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void cursor(int x, int y) {  // 移动光标
	COORD coord;		// 光标坐标
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	hidecursor();		// 隐藏光标
}
char arrowMove(char tch) {  // 用箭头移动	若是箭头，则返回对应的wsad，若非箭头，返回原值
	switch (tch) {		// 上下左右箭头分为两次ASCII码录入
	case 72:tch = 'w'; return tch;
	case 80:tch = 's'; return tch;
	case 75:tch = 'a'; return tch;
	case 77:tch = 'd'; return tch;
	default:return tch;
	}
}
void printgame() {  // 打印游戏界面
	system("cls");	// 清屏
	// 遍历屏幕内所有的 (X, Y)
	int X, Y, body, i;    // 坐标XY, 蛇身, 玩家
	for (X = 0; X < COLS; X++) {
		for (Y = 0; Y < LINES; Y++) {
			for (i = 0; i < 2; i++)
				for (body = 0; body < snake[i].len; body++)
					if (X == snake[i].coord[body].X && Y == snake[i].coord[body].Y)
						if (body) {     //  打印蛇身
							cursor(X, Y);
							cout << "O";
						}
						else if (i) {   //  打印 P2 的蛇头, 颜色为红色
							cursor(X, Y);
							cout << "\033[31m" << "O" << "\033[37m";
						}
						else {       //  打印 P1 的蛇头, 颜色为黄色
							cursor(X, Y);
							cout << "\033[33m" << "O" << "\033[37m";
						}
			for (i = 0; i < ifood; i++)      //  打印食物
				if (X == foodposition[i].X && Y == foodposition[i].Y) {
					cursor(X, Y);
					cout << "Q";
				}
			if (!X) {            //  打印竖边界
				cursor(0, Y);			cout << "*";
				cursor(COLS, Y);		cout << "*";
			}
		}
		cursor(X, 0);		cout << "*";   //  打印横边界
		cursor(X, LINES);		cout << "*";
	}
	cursor(COLS / 2, LINES + 1);
	cout << "username:" << userNow;
}
void move() {    //  移动, 根据方向改变蛇结构体的参数
	int i, body;
	for (i = 0; i < 2; i++) {
		// 防止玩家反方向移动
		if (now_ch[i] == 'd' && ch[i] == 'a' || now_ch[i] == 'a' && ch[i] == 'd' || now_ch[i] == 'w' && ch[i] == 's' || now_ch[i] == 's' && ch[i] == 'w')
			ch[i] = now_ch[i];
		else now_ch[i] = ch[i];
		// 自动向当前方向移动
		for (body = snake[i].len; body; body--) {  //  移动蛇身
			snake[i].coord[body].X = snake[i].coord[body - 1].X;
			snake[i].coord[body].Y = snake[i].coord[body - 1].Y;
		}
		switch (ch[i]) {   //  移动蛇头
		case 'w':snake[i].coord[0].Y--; break;
		case 's':snake[i].coord[0].Y++; break;
		case 'a':snake[i].coord[0].X--; break;
		case 'd':snake[i].coord[0].X++; break;
		}
	}
}
int is_die() {  //  判断是否死亡
	int body, i,
		check[2] = { 0 };
	for (i = 0; i < 2; i++)
		for (body = 1; body < snake[0].len * snake[1].len; body++)
			// 蛇 吃到自身 或 碰到边界 或 吃到对方身体 判定为死亡
			if ((snake[i].coord[0].X == snake[1 - i].coord[body % snake[1 - i].len + 1].X && snake[i].coord[0].Y == snake[1 - i].coord[body % snake[1 - i].len + 1].Y) || (snake[i].coord[body / snake[i].len + 1].X == snake[i].coord[0].X && snake[i].coord[body / snake[i].len + 1].Y == snake[i].coord[0].Y) || snake[i].coord[0].X == 0 || snake[i].coord[0].X == COLS || snake[i].coord[0].Y == 0 || snake[i].coord[0].Y == LINES)
				check[i] = 1;
	// 分为 两玩家同时死(2) 或 只有1P死(-1) 或 只有2P死(1)
	if (check[0] && check[1] || (snake[0].coord[0].X == snake[1].coord[0].X && snake[0].coord[0].Y == snake[1].coord[0].Y && snake[0].len == snake[1].len))
		return 2;
	else if (check[0] && !check[1] || (snake[0].coord[0].X == snake[1].coord[0].X && snake[0].coord[0].Y == snake[1].coord[0].Y && snake[0].len < snake[1].len))
		return -1;
	// 1P死，返回1，否则返回 0
	return (!check[0] && check[1] || (snake[0].coord[0].X == snake[1].coord[0].X && snake[0].coord[0].Y == snake[1].coord[0].Y && snake[0].len > snake[1].len));	
}
void food() {  //  吃到食物增长蛇身并刷新食物位置
	int i, j, longer;
	longer = (snake[0].len > snake[1].len) ? snake[0].len : snake[1].len;    //  根据最长的蛇来决定食物数量
	if (longer < 5)
		ifood = 1;
	else if (longer < 10)
		ifood = 4;
	else if (longer < 15)
		ifood = 6;
	else if (longer < 18)
		ifood = 8;
	else if (longer < 49)
		ifood = 10;
	else
		ifood = 0;
	for (j = 0; j < 2; j++)
		for (i = 0; i < ifood; i++)
			if (snake[j].coord[0].X == foodposition[i].X && snake[j].coord[0].Y == foodposition[i].Y) {
				snake[j].len++;		// 蛇长增加
				// 更新最后一节的参数
				snake[j].coord[snake[j].len - 1].X = 2 * snake[j].coord[snake[j].len - 2].X - snake[j].coord[snake[j].len - 3].X;
				snake[j].coord[snake[j].len - 1].Y = 2 * snake[j].coord[snake[j].len - 2].Y - snake[j].coord[snake[j].len - 3].Y;
				// 食物位置更换
				foodposition[i].X = rand() % (COLS - 1) + 1;
				foodposition[i].Y = rand() % (LINES - 1) + 1;
			}
}
void speed() {  //  根据蛇长改变蛇的速度 (通过 Sleep() 时长改变视觉效果)
	int slower = (snake[0].len > snake[1].len) ? snake[0].len : snake[1].len;
	if (slower < 5)
		Sleep(150);
	else if (slower < 10)
		Sleep(250);
	else if (slower < 15)
		Sleep(350);
	else if (slower < 18)
		Sleep(400);
	else Sleep(500);
}
void endwrite(const char* strsh) {     //  游戏结束时向文件写入数据或重置数据
	int i, start = 0, newscore[2] = { snake[0].len - 3 , snake[1].len - 3 };
	FILE* data = fopen("data.txt", "rb+");
	fseek(data, (checkline - 2) * 6, SEEK_SET);
	if (strcmp(strsh, "save") == 0)		// 用户命令为 "保存"
		for (i = 0; i < 2; i++) {
			fwrite(&newscore[i], sizeof(int), 1, data);
			fwrite("\r\n", 1, 2, data);
		}
	else if (strcmp(strsh, "restart") == 0) {		// 用户命令为 "重开"
		snake[0].len = snake[1].len = 3;
		snake[0].coord[0].X = 3;
		snake[0].coord[0].Y = 1;
		snake[1].coord[0].X = COLS - snake[1].len;
		snake[1].coord[0].Y = LINES - 1;
		ch[0] = now_ch[0] = 'd';
		ch[1] = now_ch[1] = 'a';
		ifood = 1;
		for (i = 0; i < 2; i++) {
			fwrite(&start, sizeof(int), 1, data);
			fwrite("\r\n", 1, 2, data);
		}
	}
	fclose(data);
}
void printLine(int y) {  //  打印选项行
	int i;
	cursor(0, y);
	for (i = 0; i < COLS; i++)
		cout << "-";
	cursor(0, y + 2);
	for (i = 0; i < COLS; i++)
		cout << "-";
}
void logon() {  //  注册功能
	int count = 1,        // count 遍历已注册的用户名
		X, Y;
	char tstr[20] = {"\0"}, username[20] = {"\0"}, password[20] = {"\0"},          // 存储从文件读取的用户信息
		newuser[20] = { "\0" }, check_password[20] = { "\0" };          // 存储新用户输入的信息
	Sleep(300);
	while (1) {
		system("cls");
		cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "用户名:" << newuser;
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << "密码:" << password;
		cursor(COLS / 2 - 10, LINES / 2 + 3);	cout << "请确认密码:" << check_password;
		cursor(COLS / 2 - 10, LINES / 2 + 5);	cout << "注册";
		cursor(COLS / 2 - 10, LINES / 2 + 7);	cout << "返回";
		mouseCursor(&X, &Y);		// 获取鼠标位置
		if (Y <= 250) {
			printLine(LINES / 2 - 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y >= 220) {	// 点击左键
				checkline = 1;		// 重新输入用户名，则需要重新查找
				cursor(COLS / 2 - 3, LINES / 2 - 1);
				color(3);
				fgets(tstr, sizeof(tstr), stdin);
				color(7);
				if (strcmp(tstr, "\n") == 0)	// 输入单个换行符退出输入
					continue;
				strcpy(newuser, tstr);
			}
		}
		else if (Y > 250 && Y <= 290) {
			printLine(LINES / 2);
			if (GetAsyncKeyState(VK_LBUTTON)) {
				cursor(COLS / 2 - 5, LINES / 2 + 1);
				color(3);
				fgets(tstr, sizeof(tstr), stdin);
				color(7);
				if (strcmp(tstr, "\n") != 0)
					strcpy(password, tstr);
			}
		}
		else if (Y > 290 && Y <= 330) {
			printLine(LINES / 2 + 2);
			if (GetAsyncKeyState(VK_LBUTTON)) {
				cursor(COLS / 2 + 1, LINES / 2 + 3);
				color(3);
				fgets(tstr, sizeof(tstr), stdin);
				color(7);
				if (strcmp(tstr, "\n") == 0)
					continue;
				strcpy(check_password, tstr);
			}
		}
		else if (Y > 330 && Y <= 360) {
			printLine(LINES / 2 + 4);
			if (GetAsyncKeyState(VK_LBUTTON)) {
				FILE* user = fopen("user.txt", "a+");
				while (fgets(tstr, sizeof(tstr), user)) {	// 逐行遍历数据
					if (count++ % 2) {		// count为奇数证明是用户名所在行
						sscanf(tstr, "%s", username);		// 解析字符串
						if (strcmp(username, newuser) == 0) {   // 用户不是 新用户
							checkline = 0;		// 否定该用户
							cursor(COLS / 2 - 3, LINES / 2 - 1);
							cout << "\033[31m" << "该用户已存在！" << "\033[37m";
							Sleep(1000);
						}
					}
				}
				fclose(user);
				if (checkline) {    //  确认为新用户
					if (newuser[0] == '\0') {	// 用户名为空
						cursor(COLS / 2 - 3, LINES / 2 - 1);
						cout << "\033[31m" << "用户名不能为空！" << "\033[37m";
						Sleep(1000);
						continue;
					}
					else if (password[0] == '\0') {
						cursor(COLS / 2 - 3, LINES / 2 + 1);
						cout << "\033[31m" << "密码不能为空！" << "\033[37m";
						Sleep(1000);
						continue;
					}
					else if (strcmp(password, check_password) == 0) {    // 检查密码是否一致
						// 追加模式写入初始数据
						FILE* word = fopen("user.txt", "a+");	// 写入用户名和密码，其中用户名在奇数行
						fprintf(user, "%s", newuser);
						fprintf(word, "%s", password);
						fclose(word);
						FILE* data = fopen("data.txt", "ab+");	// 写入初始数据，1P 和 2P 初始长度都为 3
						for (int i = 0, start = 0; i < 2; i++) {
							fwrite(&start, sizeof(int), 1, data);
							fwrite("\r\n", 1, 2, data);
						}
						fclose(data);
						system("cls");
						cursor(COLS / 2 - 2, LINES / 2 - 1);
						cout << "\033[32m" << "注册成功！" << "\033[37m";
						Sleep(1000);
						return;
					}
					else {
						cursor(COLS / 2 + 2, LINES / 2 + 3);
						cout << "\033[31m" << "两次密码不一致！" << "\033[37m";
						Sleep(1000);
					}
				}
			}
		}
		else if (Y > 360) {		// 返回登录页面
			printLine(LINES / 2 + 6);
			if (GetAsyncKeyState(VK_LBUTTON) && Y <= 390)
				return;
		}
		Sleep(100);
	}
}
void login(int* score, char* a) {  //  登录
	int haveUser = 0, chance = 3, Tcheckline = 1,
		X, Y;
	char	tstr[20] = { "\0" }, username[20] = { "\0" }, password[20] = { "\0" },          // 用户输入的数据
		check_username[20], check_password[20],         // 从文件中读取的数据
		freeze[20] = { "\0" };            // 冻结的用户
	Sleep(300);
	while (1) {
		system("cls");
		cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "用户名:" << username;
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << "密码:" << password;
		cursor(COLS / 2 - 5, LINES / 2 + 3);		cout << "登录";
		cursor(COLS / 2 - 5, LINES / 2 + 5);		cout << "注册";
		mouseCursor(&X, &Y);
		if (Y <= 250) {
			printLine(LINES / 2 - 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y >= 220) {
				cursor(COLS / 2 - 3, LINES / 2 - 1);
				color(3);
				fgets(tstr, sizeof(tstr), stdin);
				color(7);
				if (strcmp(tstr, "\n") == 0)
					continue;
				chance = 3;
				strcpy(username, tstr);
			}
		}
		else if (Y <= 290 && Y > 250) {
			printLine(LINES / 2);
			if (GetAsyncKeyState(VK_LBUTTON)) {
				cursor(COLS / 2 - 5, LINES / 2 + 1);
				color(3);
				fgets(tstr, sizeof(tstr), stdin);
				color(7);
				if (strcmp(tstr, "\n") == 0)
					continue;
				strcpy(password, tstr);
			}
		}
		else if (Y > 290 && Y <= 330) {
			printLine(LINES / 2 + 2);
			if (GetAsyncKeyState(VK_LBUTTON)) {
				if (username[0] == '\0') {
					cursor(COLS / 2 - 3, LINES / 2 - 1);
					cout << "\033[31m" << "用户名不能为空！" << "\033[37m";
					Sleep(1000);
					continue;
				}
				else if (password[0] == '\0') {
					cursor(COLS / 2 - 5, LINES / 2 + 1);
					cout << "\033[31m" << "密码不能为空！" << "\033[37m";
					Sleep(1000);
					continue;
				}
				haveUser = 0;
				FILE* user = fopen("user.txt", "r");	// 打开文件判断该用户是否存在
				while (fgets(check_username, sizeof(check_username), user))
					if (Tcheckline++ % 2 && strcmp(username, check_username) == 0) {
						haveUser = 1;
						break;
					}
				fclose(user);
				if (haveUser) {	// 用户存在则判断密码是否正确
					FILE* frez = fopen("frez.txt", "r");
					while (fgets(freeze, sizeof(freeze), frez) != NULL)
						if (strcmp(username, freeze) == 0) {
							haveUser = 0;
							Tcheckline = 1;
							cursor(COLS / 2 - 3, LINES / 2 - 1);
							cout << "\033[31m" << "该用户已被冻结！" << "\033[37m";
							Sleep(1000);
						}
					if (fgets(freeze, sizeof(freeze), frez) == NULL) {
						fclose(frez);
						FILE* pass = fopen("user.txt", "r");
						checkline = Tcheckline;
						while (Tcheckline-- > 0 && fgets(check_password, sizeof(check_username), pass));
						if (strcmp(check_password, password) == 0) {
							system("cls");
							cursor(COLS / 2 - 2, LINES / 2 - 1);
							cout << "\033[32m" << "登入成功！" << "\033[37m";
							Sleep(1000);
							break;
						}
						else {
							cursor(COLS / 2 - 5, LINES / 2 + 1);
							cout << "\033[31m" << "输入的密码错误！你还剩" << --chance << "次机会！" << "\033[37m";
							Sleep(1000);
							if (chance <= 0) {
								chance = 3;
								FILE* frez = fopen("frez.txt", "a+");
								fprintf(frez, "%s", username);
								fclose(frez);
								cout << "\033[31m" << "该用户冻结！" << "\033[37m";
								Sleep(1000);
							}
							fclose(pass);
						}
					}
				}
				else {	// 查找失败
					Tcheckline = 1;		// 重置行
					cursor(COLS / 2 - 3, LINES / 2 - 1);
					cout << "\033[31m" << "该用户不存在！" << "\033[37m";
					Sleep(1000);
				}
			}
		}
		else  if (Y > 330) {
			printLine(LINES / 2 + 4);
			if (GetAsyncKeyState(VK_LBUTTON) && Y <= 360)
				logon();
		}
		Sleep(100);
	}
	FILE* data = fopen("data.txt", "rb");		// 登入成功则读取历史数据存入score里
	for (int i = 0; i < 2; i++) {
		fseek(data, (checkline - 2 + i) * 6, SEEK_SET);	// 移动文件指针到从开头数起的目标行
		fread(&score[i], sizeof(int), 1, data);
	}
	fclose(data);
	strcpy(a, username);
}
void startUI(int* score) {
	int i, X, Y;
	Sleep(300);
	while (1) {
		system("cls");
		cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "开始新游戏";
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << "读取历史数据";
		cursor(COLS / 2 - 10, LINES / 2 + 3);	cout << "重新登录";
		cursor(COLS / 2 - 10, LINES / 2 + 5);	cout << "帮助";
		mouseCursor(&X, &Y);
		if (Y <= 250) {
			printLine(LINES / 2 - 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y >= 220) {
				endwrite("restart");
				return;
			}
		}
		else if (Y > 250 && Y <= 290) {
			printLine(LINES / 2);
			if (GetAsyncKeyState(VK_LBUTTON)) {
				for (i = 0; i < 2; i++)
					snake[i].len = score[i] + 3;	// 将读取的数据赋给 len
				snake[0].coord[0].X = 3;
				snake[0].coord[0].Y = 1;
				snake[1].coord[0].X = COLS - snake[1].len;
				snake[1].coord[0].Y = LINES - 1; 
				ch[0] = now_ch[0] = 'd';
				ch[1] = now_ch[1] = 'a';
				return;
			}
		}
		else if (Y > 290 && Y <= 320) {
			printLine(LINES / 2 + 2);
			if (GetAsyncKeyState(VK_LBUTTON))
				login(score, userNow);
		}
		else if (Y > 320) {
			printLine(LINES / 2 + 4);
			if (GetAsyncKeyState(VK_LBUTTON) && Y <= 350) {
				system("cls");
				char line[50];
				FILE* help = fopen("help.txt", "r");
				while (fgets(line, sizeof(line), help) != NULL)
					fputs(line, stdout);
				fclose(help);
				cout << endl;
				system("pause");
			}
		}
		Sleep(100);
	}
}
void stopUI(int *score) {
	int X, Y;
	Sleep(300);
	while (1) {
		system("cls");
		cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "继续游戏";
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << "返回菜单";
		cursor(COLS / 2 - 10, LINES / 2 + 3);	cout << "结束游戏";
		mouseCursor(&X, &Y);
		if (Y <= 250) {
			printLine(LINES / 2 - 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y >= 210)
				return;
		}
		else if (Y > 250 && Y <= 290) {
			printLine(LINES / 2);
			if (GetAsyncKeyState(VK_LBUTTON)) {
				startUI(score);
				return;
			}
		}
		else if (Y > 290) {
			printLine(LINES / 2 + 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y <= 330) {
				endwrite("save");
				exit(EXIT_SUCCESS);
			}
		}
		Sleep(100);
	}
}
void deadUI(int flag) {
	int X, Y;
	Sleep(1000);
	while (1) {
		system("cls");
		if (flag == 1) {
			cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "游戏结束！1P获胜！恭喜！";
		}
		else if (flag == -1) {
			cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "游戏结束！2P获胜！恭喜！";
		}
		else {
			cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "游戏结束！平局！";
		}
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << " 重新开始";
		cursor(COLS / 2 - 10, LINES / 2 + 3);	cout << " 退出游戏";
		mouseCursor(&X, &Y);
		if (Y <= 290) {
			printLine(LINES / 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y > 250) { // 重置数据，开始新游戏
				endwrite("restart");
				return;
			}
		}
		else if (Y > 290) {
			printLine(LINES / 2 + 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y <= 330) {
				endwrite("save");
				exit(EXIT_SUCCESS);
			}
		}
		Sleep(100);
	}
}