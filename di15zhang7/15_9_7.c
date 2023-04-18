#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
typedef unsigned long ulong;

static ulong ft = 0x00001180;

const char* state[4] = { "off", "on" };
const char* alignment[7] = { "left", "center", "right" };

/*转换成二进制后的字符串保存的地址 */
static char itbos[CHAR_BIT * sizeof(long) + 1];

/*转换数字为二进制的函数*/
void chang_num_bit(int n, char*);

/*输出转换后的二进制字符串 4位 输出*/
void show_bit(const char*);

/*输出菜单栏 */
char show_menu();

/*去除多余的输入 */
void eating();

/*change_font*/
void change_font();
int main() {
	char chioce;
	while ((chioce = show_menu())   != 'q')
	{
		switch (chioce)
		{
		case 'a':
			change_font();
			break;
		default:
			break;
		}
	}
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
	////从右往左数, 第1位表示U, 第2位表示I, 第3位表示B, 
	/// 第4至5位表示ALIGNMENT, 第6至第12位表示SIZE, 第13至20位表示ID
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
	/*从str末尾开始存放 数值n的每个位，从最低位开始*/
	for (int  i = n_bit_size - 1; i >= 0 ; i--, n >>= 1 )
	{
		str[i] = (1 & n) + '0';					// 将n除了第一位保持不变其他全部清零
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
