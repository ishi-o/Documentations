#define _CRT_SECURE_NO_WARNINGS 1
#include<Windows.h>
#include<time.h>
#include<iostream>
#include<conio.h>
using namespace std;
#define COLS 100		// �᳤
#define LINES 20		// ����
int ifood = 1, checkline = 1;  // ʳ���������ת��Ŀ����
char ch[2] = { 'd', 'a' }, now_ch[2] = { 'd', 'a' }, userNow[20]; // now_ch�洢 Ĭ���ƶ�����
struct SNAKE { COORD coord[50]; int len; }snake[2]{ {3, 1}, {COLS - 3, LINES - 1} }; // ��λ���Լ�����
COORD foodposition[10];//ʳ��λ��

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
	srand(time(NULL));	// ��ʱ��Ϊ����ֵ
	system("mode con cols=120 lines=50");		// ���ÿ���̨����
	for (i = 0; i < 10; i++) {		// ��ʼ��ʳ��λ��
		foodposition[i].X = rand() % (COLS - 1) + 1;
		foodposition[i].Y = rand() % (LINES - 1) + 1;
	}
	login(score, userNow);		// �����¼ϵͳ������¼����ʷ���ݴ���score��
	startUI(score);	// ���뿪ʼ�˵�
	Sleep(300);
	while (1) {
		if (_kbhit()) {		// ͨ���ж� tch �Ƿ�ı������ 1P��2P
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
		if (GetAsyncKeyState(VK_LBUTTON))	// ������Ҽ�������ͣ�˵�
			stopUI(score);
		move();		// �����ƶ���ʳ�ﺯ���ı��߲���
		food();
		printgame();		// ��ӡ��Ϸ����
		if (is_die() != 0) {		// ���������������
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
	POINT mouseCoord;	// ���ڻ�ȡ�������
	SetConsoleTitle(TEXT("game"));	// ���ô�����Ϊ"game"��Debugʱ��������������ѭ�������ûᱻ����
	LPRECT consoleCoord = (LPRECT)malloc(sizeof(RECT) + 64);	// ���ڴ洢����̨���ڵ���Ϣ
	HWND hwnd = FindWindow(NULL, TEXT("game"));    //  ���Ҿ��, ��������
	GetWindowRect(hwnd, consoleCoord);     //  ���õ��ľ������ console������
	GetCursorPos(&mouseCoord);     //  ����ڴ��ڵ�����
	*x = (&mouseCoord)->x - consoleCoord->left;      //  ����������
	*y = (&mouseCoord)->y - consoleCoord->top;
}
void color(int num) {  // �ı���ɫ
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), num);
}
void hidecursor() {  // ���ع��
	CONSOLE_CURSOR_INFO cursor;		// �����Ϣ
	cursor.bVisible = 0;		// ���ɼ�
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void cursor(int x, int y) {  // �ƶ����
	COORD coord;		// �������
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	hidecursor();		// ���ع��
}
char arrowMove(char tch) {  // �ü�ͷ�ƶ�	���Ǽ�ͷ���򷵻ض�Ӧ��wsad�����Ǽ�ͷ������ԭֵ
	switch (tch) {		// �������Ҽ�ͷ��Ϊ����ASCII��¼��
	case 72:tch = 'w'; return tch;
	case 80:tch = 's'; return tch;
	case 75:tch = 'a'; return tch;
	case 77:tch = 'd'; return tch;
	default:return tch;
	}
}
void printgame() {  // ��ӡ��Ϸ����
	system("cls");	// ����
	// ������Ļ�����е� (X, Y)
	int X, Y, body, i;    // ����XY, ����, ���
	for (X = 0; X < COLS; X++) {
		for (Y = 0; Y < LINES; Y++) {
			for (i = 0; i < 2; i++)
				for (body = 0; body < snake[i].len; body++)
					if (X == snake[i].coord[body].X && Y == snake[i].coord[body].Y)
						if (body) {     //  ��ӡ����
							cursor(X, Y);
							cout << "O";
						}
						else if (i) {   //  ��ӡ P2 ����ͷ, ��ɫΪ��ɫ
							cursor(X, Y);
							cout << "\033[31m" << "O" << "\033[37m";
						}
						else {       //  ��ӡ P1 ����ͷ, ��ɫΪ��ɫ
							cursor(X, Y);
							cout << "\033[33m" << "O" << "\033[37m";
						}
			for (i = 0; i < ifood; i++)      //  ��ӡʳ��
				if (X == foodposition[i].X && Y == foodposition[i].Y) {
					cursor(X, Y);
					cout << "Q";
				}
			if (!X) {            //  ��ӡ���߽�
				cursor(0, Y);			cout << "*";
				cursor(COLS, Y);		cout << "*";
			}
		}
		cursor(X, 0);		cout << "*";   //  ��ӡ��߽�
		cursor(X, LINES);		cout << "*";
	}
	cursor(COLS / 2, LINES + 1);
	cout << "username:" << userNow;
}
void move() {    //  �ƶ�, ���ݷ���ı��߽ṹ��Ĳ���
	int i, body;
	for (i = 0; i < 2; i++) {
		// ��ֹ��ҷ������ƶ�
		if (now_ch[i] == 'd' && ch[i] == 'a' || now_ch[i] == 'a' && ch[i] == 'd' || now_ch[i] == 'w' && ch[i] == 's' || now_ch[i] == 's' && ch[i] == 'w')
			ch[i] = now_ch[i];
		else now_ch[i] = ch[i];
		// �Զ���ǰ�����ƶ�
		for (body = snake[i].len; body; body--) {  //  �ƶ�����
			snake[i].coord[body].X = snake[i].coord[body - 1].X;
			snake[i].coord[body].Y = snake[i].coord[body - 1].Y;
		}
		switch (ch[i]) {   //  �ƶ���ͷ
		case 'w':snake[i].coord[0].Y--; break;
		case 's':snake[i].coord[0].Y++; break;
		case 'a':snake[i].coord[0].X--; break;
		case 'd':snake[i].coord[0].X++; break;
		}
	}
}
int is_die() {  //  �ж��Ƿ�����
	int body, i,
		check[2] = { 0 };
	for (i = 0; i < 2; i++)
		for (body = 1; body < snake[0].len * snake[1].len; body++)
			// �� �Ե����� �� �����߽� �� �Ե��Է����� �ж�Ϊ����
			if ((snake[i].coord[0].X == snake[1 - i].coord[body % snake[1 - i].len + 1].X && snake[i].coord[0].Y == snake[1 - i].coord[body % snake[1 - i].len + 1].Y) || (snake[i].coord[body / snake[i].len + 1].X == snake[i].coord[0].X && snake[i].coord[body / snake[i].len + 1].Y == snake[i].coord[0].Y) || snake[i].coord[0].X == 0 || snake[i].coord[0].X == COLS || snake[i].coord[0].Y == 0 || snake[i].coord[0].Y == LINES)
				check[i] = 1;
	// ��Ϊ �����ͬʱ��(2) �� ֻ��1P��(-1) �� ֻ��2P��(1)
	if (check[0] && check[1] || (snake[0].coord[0].X == snake[1].coord[0].X && snake[0].coord[0].Y == snake[1].coord[0].Y && snake[0].len == snake[1].len))
		return 2;
	else if (check[0] && !check[1] || (snake[0].coord[0].X == snake[1].coord[0].X && snake[0].coord[0].Y == snake[1].coord[0].Y && snake[0].len < snake[1].len))
		return -1;
	// 1P��������1�����򷵻� 0
	return (!check[0] && check[1] || (snake[0].coord[0].X == snake[1].coord[0].X && snake[0].coord[0].Y == snake[1].coord[0].Y && snake[0].len > snake[1].len));	
}
void food() {  //  �Ե�ʳ����������ˢ��ʳ��λ��
	int i, j, longer;
	longer = (snake[0].len > snake[1].len) ? snake[0].len : snake[1].len;    //  ���������������ʳ������
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
				snake[j].len++;		// �߳�����
				// �������һ�ڵĲ���
				snake[j].coord[snake[j].len - 1].X = 2 * snake[j].coord[snake[j].len - 2].X - snake[j].coord[snake[j].len - 3].X;
				snake[j].coord[snake[j].len - 1].Y = 2 * snake[j].coord[snake[j].len - 2].Y - snake[j].coord[snake[j].len - 3].Y;
				// ʳ��λ�ø���
				foodposition[i].X = rand() % (COLS - 1) + 1;
				foodposition[i].Y = rand() % (LINES - 1) + 1;
			}
}
void speed() {  //  �����߳��ı��ߵ��ٶ� (ͨ�� Sleep() ʱ���ı��Ӿ�Ч��)
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
void endwrite(const char* strsh) {     //  ��Ϸ����ʱ���ļ�д�����ݻ���������
	int i, start = 0, newscore[2] = { snake[0].len - 3 , snake[1].len - 3 };
	FILE* data = fopen("data.txt", "rb+");
	fseek(data, (checkline - 2) * 6, SEEK_SET);
	if (strcmp(strsh, "save") == 0)		// �û�����Ϊ "����"
		for (i = 0; i < 2; i++) {
			fwrite(&newscore[i], sizeof(int), 1, data);
			fwrite("\r\n", 1, 2, data);
		}
	else if (strcmp(strsh, "restart") == 0) {		// �û�����Ϊ "�ؿ�"
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
void printLine(int y) {  //  ��ӡѡ����
	int i;
	cursor(0, y);
	for (i = 0; i < COLS; i++)
		cout << "-";
	cursor(0, y + 2);
	for (i = 0; i < COLS; i++)
		cout << "-";
}
void logon() {  //  ע�Ṧ��
	int count = 1,        // count ������ע����û���
		X, Y;
	char tstr[20] = {"\0"}, username[20] = {"\0"}, password[20] = {"\0"},          // �洢���ļ���ȡ���û���Ϣ
		newuser[20] = { "\0" }, check_password[20] = { "\0" };          // �洢���û��������Ϣ
	Sleep(300);
	while (1) {
		system("cls");
		cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "�û���:" << newuser;
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << "����:" << password;
		cursor(COLS / 2 - 10, LINES / 2 + 3);	cout << "��ȷ������:" << check_password;
		cursor(COLS / 2 - 10, LINES / 2 + 5);	cout << "ע��";
		cursor(COLS / 2 - 10, LINES / 2 + 7);	cout << "����";
		mouseCursor(&X, &Y);		// ��ȡ���λ��
		if (Y <= 250) {
			printLine(LINES / 2 - 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y >= 220) {	// ������
				checkline = 1;		// ���������û���������Ҫ���²���
				cursor(COLS / 2 - 3, LINES / 2 - 1);
				color(3);
				fgets(tstr, sizeof(tstr), stdin);
				color(7);
				if (strcmp(tstr, "\n") == 0)	// ���뵥�����з��˳�����
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
				while (fgets(tstr, sizeof(tstr), user)) {	// ���б�������
					if (count++ % 2) {		// countΪ����֤�����û���������
						sscanf(tstr, "%s", username);		// �����ַ���
						if (strcmp(username, newuser) == 0) {   // �û����� ���û�
							checkline = 0;		// �񶨸��û�
							cursor(COLS / 2 - 3, LINES / 2 - 1);
							cout << "\033[31m" << "���û��Ѵ��ڣ�" << "\033[37m";
							Sleep(1000);
						}
					}
				}
				fclose(user);
				if (checkline) {    //  ȷ��Ϊ���û�
					if (newuser[0] == '\0') {	// �û���Ϊ��
						cursor(COLS / 2 - 3, LINES / 2 - 1);
						cout << "\033[31m" << "�û�������Ϊ�գ�" << "\033[37m";
						Sleep(1000);
						continue;
					}
					else if (password[0] == '\0') {
						cursor(COLS / 2 - 3, LINES / 2 + 1);
						cout << "\033[31m" << "���벻��Ϊ�գ�" << "\033[37m";
						Sleep(1000);
						continue;
					}
					else if (strcmp(password, check_password) == 0) {    // ��������Ƿ�һ��
						// ׷��ģʽд���ʼ����
						FILE* word = fopen("user.txt", "a+");	// д���û��������룬�����û�����������
						fprintf(user, "%s", newuser);
						fprintf(word, "%s", password);
						fclose(word);
						FILE* data = fopen("data.txt", "ab+");	// д���ʼ���ݣ�1P �� 2P ��ʼ���ȶ�Ϊ 3
						for (int i = 0, start = 0; i < 2; i++) {
							fwrite(&start, sizeof(int), 1, data);
							fwrite("\r\n", 1, 2, data);
						}
						fclose(data);
						system("cls");
						cursor(COLS / 2 - 2, LINES / 2 - 1);
						cout << "\033[32m" << "ע��ɹ���" << "\033[37m";
						Sleep(1000);
						return;
					}
					else {
						cursor(COLS / 2 + 2, LINES / 2 + 3);
						cout << "\033[31m" << "�������벻һ�£�" << "\033[37m";
						Sleep(1000);
					}
				}
			}
		}
		else if (Y > 360) {		// ���ص�¼ҳ��
			printLine(LINES / 2 + 6);
			if (GetAsyncKeyState(VK_LBUTTON) && Y <= 390)
				return;
		}
		Sleep(100);
	}
}
void login(int* score, char* a) {  //  ��¼
	int haveUser = 0, chance = 3, Tcheckline = 1,
		X, Y;
	char	tstr[20] = { "\0" }, username[20] = { "\0" }, password[20] = { "\0" },          // �û����������
		check_username[20], check_password[20],         // ���ļ��ж�ȡ������
		freeze[20] = { "\0" };            // ������û�
	Sleep(300);
	while (1) {
		system("cls");
		cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "�û���:" << username;
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << "����:" << password;
		cursor(COLS / 2 - 5, LINES / 2 + 3);		cout << "��¼";
		cursor(COLS / 2 - 5, LINES / 2 + 5);		cout << "ע��";
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
					cout << "\033[31m" << "�û�������Ϊ�գ�" << "\033[37m";
					Sleep(1000);
					continue;
				}
				else if (password[0] == '\0') {
					cursor(COLS / 2 - 5, LINES / 2 + 1);
					cout << "\033[31m" << "���벻��Ϊ�գ�" << "\033[37m";
					Sleep(1000);
					continue;
				}
				haveUser = 0;
				FILE* user = fopen("user.txt", "r");	// ���ļ��жϸ��û��Ƿ����
				while (fgets(check_username, sizeof(check_username), user))
					if (Tcheckline++ % 2 && strcmp(username, check_username) == 0) {
						haveUser = 1;
						break;
					}
				fclose(user);
				if (haveUser) {	// �û��������ж������Ƿ���ȷ
					FILE* frez = fopen("frez.txt", "r");
					while (fgets(freeze, sizeof(freeze), frez) != NULL)
						if (strcmp(username, freeze) == 0) {
							haveUser = 0;
							Tcheckline = 1;
							cursor(COLS / 2 - 3, LINES / 2 - 1);
							cout << "\033[31m" << "���û��ѱ����ᣡ" << "\033[37m";
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
							cout << "\033[32m" << "����ɹ���" << "\033[37m";
							Sleep(1000);
							break;
						}
						else {
							cursor(COLS / 2 - 5, LINES / 2 + 1);
							cout << "\033[31m" << "�������������㻹ʣ" << --chance << "�λ��ᣡ" << "\033[37m";
							Sleep(1000);
							if (chance <= 0) {
								chance = 3;
								FILE* frez = fopen("frez.txt", "a+");
								fprintf(frez, "%s", username);
								fclose(frez);
								cout << "\033[31m" << "���û����ᣡ" << "\033[37m";
								Sleep(1000);
							}
							fclose(pass);
						}
					}
				}
				else {	// ����ʧ��
					Tcheckline = 1;		// ������
					cursor(COLS / 2 - 3, LINES / 2 - 1);
					cout << "\033[31m" << "���û������ڣ�" << "\033[37m";
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
	FILE* data = fopen("data.txt", "rb");		// ����ɹ����ȡ��ʷ���ݴ���score��
	for (int i = 0; i < 2; i++) {
		fseek(data, (checkline - 2 + i) * 6, SEEK_SET);	// �ƶ��ļ�ָ�뵽�ӿ�ͷ�����Ŀ����
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
		cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "��ʼ����Ϸ";
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << "��ȡ��ʷ����";
		cursor(COLS / 2 - 10, LINES / 2 + 3);	cout << "���µ�¼";
		cursor(COLS / 2 - 10, LINES / 2 + 5);	cout << "����";
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
					snake[i].len = score[i] + 3;	// ����ȡ�����ݸ��� len
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
		cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "������Ϸ";
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << "���ز˵�";
		cursor(COLS / 2 - 10, LINES / 2 + 3);	cout << "������Ϸ";
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
			cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "��Ϸ������1P��ʤ����ϲ��";
		}
		else if (flag == -1) {
			cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "��Ϸ������2P��ʤ����ϲ��";
		}
		else {
			cursor(COLS / 2 - 10, LINES / 2 - 1);		cout << "��Ϸ������ƽ�֣�";
		}
		cursor(COLS / 2 - 10, LINES / 2 + 1);	cout << " ���¿�ʼ";
		cursor(COLS / 2 - 10, LINES / 2 + 3);	cout << " �˳���Ϸ";
		mouseCursor(&X, &Y);
		if (Y <= 290) {
			printLine(LINES / 2);
			if (GetAsyncKeyState(VK_LBUTTON) && Y > 250) { // �������ݣ���ʼ����Ϸ
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