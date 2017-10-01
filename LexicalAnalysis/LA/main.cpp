#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int main(){
	FILE* fp=fopen("in.txt","r");
	char c;//��ŵ�ǰ�������ַ�
	char C[2];
	enum MemSymbol
	{
		BEGINSY, ENDSY, IFSY, THENSY, ELSESY, IDSY, INTSY, PLUSSY, MINUSSY,
		STARSY, DIVISY, LPARSY, RPARSY, COMMASY, SEMISY, COLONSY, ASSIGNSY, EQUSY
	} symbol;//���浱ǰʶ�𵥴ʵ�����
	char reserver[] = "begin end if then else         ";//������
	char token[20];//��ŵ��ʵ��ַ���
	int num = 0;//��ŵ�ǰ�����������ֵ
	memset(token, 0, sizeof(token));//cleantoken()
	memset(C, 0, sizeof(C));//cleanC
	c = fgetc(fp);
	C[0] = c;
	while (!feof(fp)) {
		if (isblank(c) || iscntrl(c)) {
			//if (c == '\n') printf("\n");
			memset(token, 0, sizeof(token));//cleantoken()
			memset(C, 0, sizeof(C));//cleanC
			c = fgetc(fp);
			C[0] = c;
			continue;
		}
		//ʶ���Ƿ��Ǳ�ʶ��
		if (isalpha(c)) {
			while (isalpha(c) || isdigit(c)) {
				strcat_s(token, C);
				c = fgetc(fp);
				memset(C, 0, sizeof(C));//cleanC
				C[0] = c;
			}
			fseek(fp, -1, SEEK_CUR);//ָ�����һ���ַ�
			if (strcmp(token, "begin") == 0) {
				printf("BEGINSY ");
			}
			else if (strcmp(token, "end") == 0) {
				printf("ENDSY ");
			}
			else if (strcmp(token, "if") == 0) {
				printf("IFSY ");
			}
			else if (strcmp(token, "then") == 0) {
				printf("THENSY ");
			}
			else if (strcmp(token, "else") == 0) {
				printf("ELSESY ");
			}
			else {
				printf("IDSY(%s) ", token);
			}
		}
		//ʶ���Ƿ�������
		else if (isdigit(c)) {
			while (isdigit(c)) {
				strcat_s(token, C);
				c = fgetc(fp);
				memset(C, 0, sizeof(C));//cleanC
				C[0] = c;
			}
			fseek(fp, -1, SEEK_CUR);//ָ�����һ���ַ�
			for (int i = 0; i < strlen(token); i++) {
				num = num * 10 + ((int)(token[i]) - (int)('0'));
			}
			memset(C, 0, sizeof(C));//cleanC
			memset(token, 0, sizeof(token));//cleantoken()
			printf("INTSY(%d) ", num);
			num = 0;//����numֵ
		}
		//ʶ���Ƿ���ð�ţ����߸�ֵ����
		else if (c == ':') {
			c = fgetc(fp);
			if (c == '=') {
				printf("ASSIGNSY ");
			}
			else {
				fseek(fp, -1, SEEK_CUR);//ָ�����һ���ַ�
				printf("COLONSY ");
			}			
		}
		//ʶ���Ƿ��������ָ���
		else if (c == '+') { printf("PLUSSY "); }
		else if (c == '=') { printf("EQUSSY "); }
		else if (c == '-') { printf("MINUSSY ");}
		else if (c == '*') { printf("STARSY "); }
		else if (c == '(') { printf("LPARSY "); }
		else if (c == ')') { printf("RPARSY "); }
		else if (c == ',') { printf("COMMASY ");}
		else if (c == ';') { printf("SEMISY "); }
		else if (c == '/') {
			c = fgetc(fp); 
			if (c == '*') {
				//˵����ע��
				do {
					do { c = fgetc(fp); } while (c != '*');
					do { c = fgetc(fp); if (c == '/') goto finish; } while (c == '*');
				} while (c != '*');
			}
			else {
				fseek(fp, -1, SEEK_CUR);//ָ�����һ���ַ�
				printf("DIVISY ");
			}
		}
		//���������Ƿ��ַ�
		else {
			printf("\n------ find illegal symbol! ------\n");
		}

		if ((feof(fp))) {
			break;
		}
		else {
		finish:
			memset(token, 0, sizeof(token));//cleantoken()
			memset(C, 0, sizeof(C));//cleanC
			c = fgetc(fp);
			C[0] = c;
		}
	}
	fclose(fp);
}