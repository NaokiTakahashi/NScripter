#include <windows.h>
#include <stdio.h>
//----------------------------
//�G�N�X�|�[�g�����֐�
//----------------------------
extern "C" {
	__declspec(dllexport) void Font(unsigned char *bits,int w,int h,const char *param);
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved);

BOOL APIENTRY DllMain( HANDLE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved) {
	return TRUE;
}

void Font(unsigned char *bits,int w,int h,const char *param) {
	//�e�N�X�`���Ƀt�H���g����������DLL�B�T���v���ł��B
	//���̃\�[�X�̒��쌠�͎咣���܂���̂ōD���ɘM���Ă��������B

	//�p�����[�^��ǂݍ���
	int fw,fh,cr=255,cg=255,cb=255;
	const unsigned char *str;
	if (param==NULL) {
		MessageBox(NULL,"�t�H���g��DLL�Ƀp�����[�^��n���Ă��܂���B","�G���[",MB_OK);
		return;
	} else {
		int i=0;
		fw=atoi(param);
		while (param[i]!=',') {
			if (param[i]=='\0') {
				goto param_error;
			}
			i++;
		}
		i++;
		fh=atoi(param+i);
		while (param[i]!=',') {
			if (param[i]=='\0') {
				goto param_error;
			}
			i++;
		}
		str=(const unsigned char *)param+i+1;
	}
	//�t�H���g�𓾂�
	HDC fontdc;
	HFONT font;
	LOGFONT lf;
	memset(&lf,0,sizeof(lf));
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfEscapement=0;
	strcpy(lf.lfFaceName,"�l�r �S�V�b�N");
	lf.lfHeight=fh;
	lf.lfItalic=0;
	lf.lfOrientation=0;
	lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
	lf.lfPitchAndFamily=FIXED_PITCH;
	lf.lfQuality=DEFAULT_QUALITY;
	lf.lfStrikeOut=0;
	lf.lfUnderline=0;
	lf.lfWeight=FW_NORMAL;
	lf.lfWidth=fw;
	font=CreateFontIndirect(&lf);
	fontdc=CreateCompatibleDC(NULL);
	SelectObject(fontdc,font);
	TEXTMETRIC tm;
	GetTextMetrics(fontdc, &tm);

	//��������
	int x=0,y=0,ll;
	unsigned l=0;
	size_t len=strlen((const char *)str);
	while(1) {
		if (l>=len) break;
		DWORD chr;
		if (str[l]=='\n') {
			x=0;
			y=y+fh;
			l++;
			continue;
		}
		if (str[l]=='%') {
			//����
			l++;
			switch (str[l]) {
				case '%':
					//%���̂��̂�\���������炵���B���̂܂ܕ\�����ցB
					break;
				case '#':
					l++;
					char temp[7];
					strncpy(temp,(const char *)str+l,6);
					temp[6]='\0';
					unsigned col;
					sscanf(temp,"%x",&col);
					cr=col/0x10000;
					col%=0x10000;
					cg=col/0x100;
					cb=col%0x100;
					l+=6;
					break;
				default:
					//������
					DeleteObject(font);
					DeleteDC(fontdc);
					goto param_error;
					return;
			}
		}
		if (str[l]>=0x81 && str[l]<=0x9f || str[l]>=0xe0 && str[l]<=0xef) {
			chr=str[l]*256+str[l+1];
			ll=2;
		} else {
			chr=str[l];
			ll=1;
		}
		GLYPHMETRICS gm;
		const MAT2 mat={{0,1},{0,0},{0,0},{0,1}};
		int size=GetGlyphOutline(fontdc,chr,GGO_GRAY8_BITMAP,&gm,0,NULL,&mat);
		if (size<0) {
			x=x+fw*ll;
			l+=ll;
			continue;
		}
		int lwd=(int)gm.gmBlackBoxX;
		int lht=(int)gm.gmBlackBoxY;
		int pitch = ((gm.gmBlackBoxX+3)&0xfffc);
		size=lht*pitch;//�A���Ă��鐔�l������܂蓖�ĂɂȂ�Ȃ��ۂ�

		BYTE *sp=new BYTE[size];
		memset(sp,0,size);
		unsigned char *p=sp;
		GetGlyphOutline(fontdc,chr,GGO_GRAY8_BITMAP,&gm,size,sp,&mat);
		int leftx=gm.gmptGlyphOrigin.x;
		int lefty=tm.tmAscent-gm.gmptGlyphOrigin.y;
		if (leftx<0) {lwd+=leftx;p=p-leftx;leftx=0;}
		if (lefty<0) {lht+=lefty;p=p-lefty*pitch;lefty=0;}
		if (leftx+lwd>fw*ll) {
			lwd=fw*ll-leftx;
		}
		if (lefty+lht>fh) {
			lht=fh-lefty;
		}

		if ((int)gm.gmBlackBoxX>=w || (int)gm.gmBlackBoxY>=h) {
			delete [] sp;
			DeleteObject(font);
			DeleteDC(fontdc);
			MessageBox(NULL,"�e�N�X�`�����當�����͂ݏo�܂����B","�G���[",MB_OK);
			return;
		}

		if (x+leftx+lwd>w) {
			x=0;y=y+fh;
			if (y+lefty+lht>h) {
				delete [] sp;
				DeleteObject(font);
				DeleteDC(fontdc);
				MessageBox(NULL,"�e�N�X�`�����當�����͂ݏo�܂����B","�G���[",MB_OK);
				return;
			}
		}
		unsigned char *destp=bits+(x+leftx)*4+(y+lefty)*w*4;
		for (int j=0;j<lht;j++) {
			int i2=0;
			for (int i=0;i<lwd;i++) {
				if (p[i]) {
					if (destp[i2+3]==0) {
						//���X�����ȂƂ���ɂ͂��̂܂܏����B
						destp[i2]=cb;
						destp[i2+1]=cg;
						destp[i2+2]=cr;
						destp[i2+3]=p[i]*255/64;
					} else {
						int a=p[i]*255/64;
						//�s�����ȏꍇ�A���n�ɑ΂��ď����B���̓��ߓx�͕ۑ�
						destp[i2]=(cb-destp[i2])*a/255+destp[i2];
						destp[i2+1]=(cg-destp[i2+1])*a/255+destp[i2+1];
						destp[i2+2]=(cr-destp[i2+2])*a/255+destp[i2+2];
					}
				}
				i2+=4;
			}
			destp+=w*4;
			p+=pitch;
		}
		delete [] sp;
		x=x+fw*ll;
		l+=ll;
	}
	DeleteObject(font);
	DeleteDC(fontdc);
	return;
	//�G���[����
param_error:
	MessageBox(NULL,"�t�H���g��DLL�̃p�����[�^���s���ł��B","�G���[",MB_OK);
	return;
}

