#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
typedef unsigned long ulong;

static ulong ft = 0x00001180;

const char* state[4] = { "off", "on" };
const char* alignment[7] = { "left", "center", "right" };

/*ת���ɶ����ƺ���ַ�������ĵ�ַ */
static char itbos[CHAR_BIT * sizeof(long) + 1];

/*ת������Ϊ�����Ƶĺ���*/
void chang_num_bit(int n, char*);

/*���ת����Ķ������ַ��� 4λ ���*/
void show_bit(const char*);

/*����˵��� */
char show_menu();

/*ȥ����������� */
void eating();

/*change_font*/
void change_font();

/*change_size*/
void change_size();

/*chang_alignment*/
void chang_alignment();

/*change_toggle*/
void change_toggle(ch);

int main() {
	char chioce;
	while ((chioce = show_menu())   != 'q')
	{
		switch (chioce)
		{
		case 'f':
			change_font();
			break;
		case 's':
			change_size();
			break;
		case 'a':
			chang_alignment();
			break;
		case 'b':
		case 'i':
		case 'u':
			change_toggle(chioce);
			eating();
			break;
		default:
			break;
		}
	}
	puts("bye!");
}

void change_toggle(char ch) {
	if (ch == 'b') {
		if (ft & 0x4) {			//��������λ����Ϊ0   4��λ���ֲ���
			ft &= ~(ulong)0x4;
		}
		else {
			ft |= (ulong)0x4;		//����ǹر� �ͽ�4��λ����Ϊ1 �������ֲ���
		}
	}
	else if (ch == 'i') {
		if (ft & 0x2) {
			ft &= ~(ulong)0x2;
		}
		else {
			ft |= (ulong)0x2;
		}
	}
	else
	{
		if (ft & 0x01)
		{
			ft &= ~(ulong)(0x01);
		}
		else
		{
			ft |= (ulong)(0x01);
		}
	}
}

void chang_alignment() {
	char ch; 
	printf("Select alignment:\n");
	printf("l) left    c) center    r) right\n");
	while ((ch = getchar()),(NULL == strchr("lcr",ch)) || getchar() != '\n')
	{
		printf("Please enter with l, c or r: ");
	}
	puts("ft");
	chang_num_bit(ft, itbos);
	show_bit(itbos);
	ft &= ~(1 << 3), ft &= ~(1 << 4);
	ft = ft | (ch == 'l' ? 0 : ch == 'c' ? (1 << 3) : (1 << 4));
	puts("after ft");
	chang_num_bit(ft, itbos);
	show_bit(itbos);
}


void change_size() {
	int size; 
	puts("enter 0 - 127 ");
	while (scanf_s("%d",&size) != 1 || getchar() != '\n')
	{
		puts("err 0 - 127 ");
		eating();
	}
	puts("not change ==== size");
	chang_num_bit(size, itbos);
	show_bit(itbos);
	puts("ft");
	chang_num_bit(ft, itbos);
	show_bit(itbos);
	size &= 0x7f;
	size <<= 5;
	puts("change ==== size");
	chang_num_bit(size, itbos);
	show_bit(itbos);
	for (int i = 5; i < 12; i++) {
		ft &=	~(1 << i);					//�ı�ft�� 6-12λ Ϊ0
	}
	ft |= size;
	puts("after ft");
	chang_num_bit(ft, itbos);
	show_bit(itbos);
}

void change_font() {
	int id;
	puts("enter 0  -  255");
	while (scanf_s("%d",&id) != 1 || getchar() != '\n')
	{
		printf("err---- 0 - 255\n");
		eating();
	}
	
	puts("not change ==== id");
	chang_num_bit(id, itbos);
	show_bit(itbos);
	puts("ft");
	chang_num_bit(ft, itbos);
	show_bit(itbos);
	id &= 0xff; 
	id <<= 12;
	puts("change ==== id");
	chang_num_bit(id, itbos);
	show_bit(itbos);
	for (int i = 12; i < 20; i++) {
		ft &= ~(1 << i);
	}
	ft |= id;
	puts("change ====ft");
	chang_num_bit(ft, itbos);
	show_bit(itbos);
}


char show_menu() {
	////����������, ��1λ��ʾU, ��2λ��ʾI, ��3λ��ʾB, 
	/// ��4��5λ��ʾALIGNMENT, ��6����12λ��ʾSIZE, ��13��20λ��ʾID
	printf("ID    SIZE    ALIGNMENT      B       I       U\n");
	printf("%-7u%-9u%-12s", ft >> 12 & 0xff,ft >> 5 & 0x7f, alignment[ft >> 3 & 0x3]);
	printf("%-8s%-8s%-8s\n", state[ft >> 2 & 0x1] , state[ft >> 1 & 0x1] , state[ft & 0x1]);
	printf("f) change font        s) change size        a) change alignment\n");
	printf("b) toggle bold        i) toggle italic      u) toggle underline\n");
	printf("q) quit\n");
	
	char ch; 
	printf("Please enter with f, s, a, b, i, u or q: ");
	ch = getchar();
	while ((NULL == strchr("fsabiuq",ch)))
	{
		eating();
		printf("Please enter with f, s, a, b, i, u or q: \n");
		ch = getchar();
	}
	return ch;
}
void  chang_num_bit(int n, char* str) {
	static int n_bit_size = CHAR_BIT * sizeof(int);
	/*��strĩβ��ʼ��� ��ֵn��ÿ��λ�������λ��ʼ*/
	for (int  i = n_bit_size - 1; i >= 0 ; i--, n >>= 1 )
	{
		str[i] = (1 & n) + '0';					// ��n���˵�һλ���ֲ�������ȫ������
	}
	str[n_bit_size] = '\0';
	return;
} 

void show_bit(const char * str){
	int i = 0; 
	while (str[i])
	{
		putchar(str[i]);
		if (++i % 4 == 0 && str[i]) {
			putchar(' ');
		}
		
	}
	putchar('\n');
	return;
}

void eating(){
	while (getchar() != '\n')
	{
		continue;
	}
	return;
}
