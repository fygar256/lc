/*
	文字列のアルファベットを数字に
	直して加算して出力する

	filename : lc.c
	Usage1 : lc alice pleasance liddell
	Usage2 : echo alice pleasance liddell | lc

	output : alice pleasance liddell 160

	to complie : cc lc.c -o lc
*/
#include	<stdio.h>
#include	<stdlib.h>

int	pv(char *sp) {
	int	s=0;
	while(*sp!='\0'&&*sp!='\n') {
		if (*sp>='A' && *sp<='Z')
			s+=*sp-'A'+1;
	else if (*sp>='a' && *sp<='z')
			s+=*sp-'a'+1;
		++sp;
		}
	printf("%d\n",s);
}

int	main(int argc,char *argv[])
{
	char	*sp;
	char	sentence[65536];
	int		i,s,cnt,ch;

	if (argc==1) {
		sp=sentence;
		while(1) {
			ch=fgetc((FILE *)stdin);
			if (ch==EOF) exit(0);
			if (ch=='\n') {
				*sp='\0';
				pv(sentence);
				sp=sentence;
				}
			else *sp++=ch;
			}
		}
	else {
		for(i=0,cnt=1;cnt<argc;cnt++) {
			sp=*++argv;
			while(*sp!=0) {
				sentence[i++]=*sp++;
				}
			*sp='\0';
			}
		}
	
	pv(sentence);
	exit(0);
}
