/*
与えられた数値に対応する英単語を見つける
	Usage: cl [-d=dicfile] <Number>
	usage ex. 1: cl 76
       usage ex. 2: echo 76 | cl

	to compile: cl.c -o cl
*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>

char defaultdic[]="/home/user/dic/EIJIRO-SAMPLE-1442.TXT";
FILE *fp,*so;

void wayout() {
	fclose(so);
	fclose(fp);
	system("sort ol.tmp |uniq && rm ol.tmp");
	exit(0);
}

int ffgetc(FILE *fp) {
	int c;
	c=fgetc(fp);
	if (c==EOF) wayout();
	return(c);
}

char *getword(FILE *fp) {
	int idx;
	int c;
static	char word[1024];

	idx=0;
	c=ffgetc(fp);
	if (c==0x81) ffgetc(fp);
		else ungetc(c,fp);

	while(1) {
		c=ffgetc(fp);

		if (c==' ') {
			int	c2;
			c2=ffgetc(fp);
			if (c2==' ') c='\n';
			else ungetc(c2,fp);
			}
		if (c=='(') {
			while(1) {
				c=ffgetc(fp);
				if (c=='\n') break;
				if (c==')') continue;
				}
			}
		if ((!isalpha(c))&&(c!=' ')) break;
		word[idx]=(unsigned char)c;
		idx++;
		}
		word[idx]='\0';
		ungetc(c,fp);
		while(ffgetc(fp)!='\n');
		if (word[idx-1]==' ')
			word[idx-1]='\0';
		return(word);
}

int cwv(char *s) {
	int n=0;
	while(1) {
		if (*s=='\0') return(n);
		if (*s>='A' && *s<='Z')
				n+=*s-'A'+1;
		else if (*s>='a' && *s<='z')
				n+=*s-'a'+1;
		s++;
		}
	return(n);
}

int	main(int argc,char *argv[])
{
	int	n;
	int wv;
	char *word;
	char *dicfile=defaultdic;

	if (argc>=2&&strncmp(*(argv+1),"-d=",3)==0) {
			dicfile=&((*(++argv))[3]);
			argc--;
			}

	if (argc==1)
		fscanf((FILE *)stdin,"%d",&n);
	else
		sscanf(*(++argv),"%d",&n);

	if (n<=0) exit(1);
	fp=fopen(dicfile,"r");
	so=fopen("ol.tmp","w");
	if ((fp==NULL)||(so==NULL)) exit(1);
	while((word=getword(fp))!=NULL) {
		wv=cwv(word);
		if (wv==n)
			fprintf(so,"%s\n",word);
		}
	wayout();
}
