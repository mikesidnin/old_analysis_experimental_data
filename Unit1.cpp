//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <ComObj.hpp>
#include <utilcls.h>
#include <math.h>
#include <stdio.h>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int i,j,k,n;
float nm,nn;
int jj,ii;
float sp[768][574];
float ssp[768][574];
float sssp[255][574];
float a,a1,d[768][574],dd[255][574],ddd[768][574],xsr;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 Memo1->Clear();
if (OpenDialog1->Execute())
 { FILE *f;
  AnsiString s = OpenDialog1->FileName;
  f = fopen(s.c_str(),"r");
  for (i = 0; i<768; i++)
  {
	for (j = 0; j<574; j++)
   {
	fscanf(f,"%e",&sp[i][j]);
   }
  }
fclose(f);
 }

}
//Основная замена---------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	 nn=0;
	for (i = 1; i<768; i++)
  { jj=0;
	 for (j = 1; j<574; j++)
   { ssp[i][j]=0;
	 a = 0;
	 a1 = 0;
	 a = (sp[i][j]+sp[i+1][j]+sp[i-1][j]+sp[i][j+1]+sp[i][j-1]+sp[i+1][j+1]+sp[i-1][j-1]+sp[i-1][j+1]+sp[i+1][j-1])/9;
	 a1 = (sp[i+1][j]+sp[i-1][j]+sp[i][j+1]+sp[i][j-1]+sp[i+1][j+1]+sp[i-1][j-1]+sp[i-1][j+1]+sp[i+1][j-1])/8;
		 if (a+2<sp[i][j])
	 {
	  ssp[i][j]=sp[i][j]-a;
	  sp[i][j]=a1;
	  jj=jj+1;
	  nn=nn+1;
	 }
   }
  Memo1->Text = Memo1->Text+IntToStr(i)+" "+IntToStr(jj);
  Memo1->Lines->Add(" ");
   }
  nm=i*j;
  Edit1->Text = FloatToStr(nm);
  Edit2->Text = FloatToStr(nn);
//Циклиы для дисперсии-----------------------------------------------------------
  for (i = 1; i < 768; i++)
  {
   for (j = 1; j < 574; j++)
   { d[i][j]=0;
	 xsr = (sp[i][j]+sp[i+1][j]+sp[i-1][j]+sp[i][j+1]+sp[i][j-1]+sp[i+1][j+1]+sp[i-1][j-1]+sp[i-1][j+1]+sp[i+1][j-1])/9;
	 ddd[i][j] = ((sp[i][j]-xsr)*(sp[i][j]-xsr)+(sp[i+1][j]-xsr)*(sp[i+1][j]-xsr)+(sp[i-1][j]-xsr)*(sp[i-1][j]-xsr)+(sp[i][j+1]-xsr)*(sp[i][j+1]-xsr)+(sp[i][j-1]-xsr)*(sp[i][j-1]-xsr)+(sp[i+1][j+1]-xsr)*(sp[i+1][j+1]-xsr)+(sp[i-1][j-1]-xsr)*(sp[i-1][j-1]-xsr)+(sp[i-1][j+1]-xsr)*(sp[i-1][j+1]-xsr)+(sp[i+1][j-1]-xsr)*(sp[i+1][j-1]-xsr))/72;
	 d[i][j] = sqrt(ddd[i][j]);
	 }
  }
//формирование массивов 3 на 3-----------------------------------------------------


  for (k = 0; k < 255; k++)
  {
   for( j = 0; j < 574; j++)
   {
   sssp[k][j] = (sp[k*3][j]+sp[k*3+1][j]+sp[k*3+2][j])/3;
   dd[k][j] = (d[k*3][j]+d[k*3+1][j]+d[k*3+2][j])/3;
   }
  }
 for( k = 0; k<255; k++)
 { for(n=0;n<189;n++)
   {
	sssp[k][n]=(sssp[k][n*3]+sssp[k][n*3+1]+sssp[k][n*3+2])/3;
	dd[k][n]=(dd[k][n*3]+dd[k][n*3+1]+dd[k][n*3+2])/3;
   }
 }

//Построчная запись-------------------------------------------------------------

  for (k = 0; k < 255; k++)
  {
  FILE *f;
  AnsiString b;
  b = "D:\x"+IntToStr(k+1)+".dat";
  f = fopen(b.c_str(),"w");
	for (n = 0; n < 189; n++)
   {
	fprintf(f,"%f ",sssp[k][n]);
	fprintf(f,"\n");
   }

   fclose(f);
 }
  for (k = 0; k < 255; k++)
  {
  FILE *f;
  AnsiString h;
  h = "D:\d"+IntToStr(k+1)+".dat";
  f = fopen(h.c_str(),"w");
	for (n = 0; n < 189; n++)
   {
	fprintf(f,"%f ",dd[k][n]);
	fprintf(f,"\n");
   }

   fclose(f);
 }

  for (n = 0; n< 189; n++)
  {
  FILE *f;
  AnsiString bb;
  bb = "D:\y"+IntToStr(n+1)+".dat";
  f = fopen(bb.c_str(),"w");
	for (k = 0; k < 255; k++)
   {
	fprintf(f,"%f ",sssp[k][n]);
	fprintf(f,"\n");
   }

   fclose(f);
 }
  for (n = 0; n < 189; n++)
  {
  FILE *f;
  AnsiString hh;
  hh = "D:\dd"+IntToStr(n+1)+".dat";
  f = fopen(hh.c_str(),"w");
	for (k = 0; k < 255; k++)
   {
	fprintf(f,"%f ",dd[k][n]);
	fprintf(f,"\n");
   }

   fclose(f);
 }


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
if (SaveDialog1->Execute())
 { FILE *f;
  AnsiString s = SaveDialog1->FileName;
  f = fopen(s.c_str(),"w");

  for (k = 0; k<255; k++)
  {
	for (n = 0; n<189; n++)
   {
	fprintf(f,"%f",sssp[k][n]);
	fprintf(f," ");
   }

   fprintf(f,"\n");
  }
fclose(f);
 }
}
//---------------------------------------------------------------------------
