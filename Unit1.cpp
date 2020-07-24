//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
brick *br[77];     //�j��
block *blo[10];    //�ɪO
ball *ba[1000];    //�y
bool start=false;  //�P�_�C���O�_�}�l
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

brick::brick():TShape(Form1){
  Parent=Form1->Panel1;              //�j���bPanel1�����
  Pen->Style=psInsideFrame;
  Pen->Width=5;
  Height=35;
  Width=70;

  hp=random(3)+1;                    //�H���ͩR��
  switch (hp){
    case 1:
      Brush->Color=clYellow;
      break;
    case 2:
      Brush->Color=clRed;
      break;
    case 3:
      Brush->Color=clMaroon;
      break;
  }
}

__fastcall brick::~brick(){

}


ball::ball():TShape(Form1){
  Parent=Form1->Panel1;                   //�y�bPanel1�����
  Brush->Color=clRed;
  Shape=stCircle;
  Height=20;
  Width=20;
  Top=blo[0]->Top-18;                    //���צ�m�b�Ĥ@���ɪO�W��

  engine=new TTimer(Form1);              //�s�WTimer engine
  engine->OnTimer=move;                  //OnTimer�ƥ�禡�g�bmove��
  engine->Interval=1;                    //�C�j0.001���]�@��Timer
  engine->Enabled=false;                 //�@�}�lTimer����

  speedx=2;                             //�t��2
  speedy=-2;
  power=1;                              //�y�¤O��=1
}

__fastcall ball::~ball(){
  delete engine;                        //�R��engine
}

block::block():TShape(Form1){
  Parent=Form1->Panel1;                 //�ɪO�bPanel1�����
  Brush->Color=clGreen;
  Pen->Style=psInsideFrame;
  Pen->Width=5;
  Width=80;
  Height=20;
  Top=Form1->Panel1->Height-22;         //���צ�m�bPanel1����

  life=2;                               //�ɪO�Ө���=2

}

__fastcall block::~block(){

}

void __fastcall ball::move(TObject *Sender){
   if(Top<=0) speedy=-speedy;                                                                 //�y�I��W����ɤϼu
   if(Left+Width>=Form1->Panel1->Width||Left<=0) speedx=-speedx;                              //���k��ɤϼu
   if(Top>=Form1->Panel1->Height){                                                            //�y���U�h
     Enabled=false;                                                                           //�\������
     engine->Enabled=false;                                                                   //Timer����
     Top=Form1->Panel1->Top-100;                                                              //�����Panel1�W��
     delebaN--;                                                                               //�ثe�y��-1
   }

   for(int i=0;i<br[0]->brN;i++){                                                               //�P�_�Ҧ��j�����S���Q����
     for(int m=0;m<deleN;m++){                                                                  //�P�_�O�_���w�R�����j��
       if(dele[m]==i) deleB=true;
     }
     if(deleB){                                                                                 //�Y���w�R�����j�� ���L���~��P�_�I��
       deleB=false;
       continue;
     }

     if(Top<br[i]->Top&&Top+20>=br[i]->Top&&Left<=br[i]->Left+65&&Left>=br[i]->Left-15){        //�y����m�b�j���W�� �B �yĲ�I��j�� �B �y�b���j�����k�d�򤧤�
       if(speedy>0){
         speedy=-speedy;                                                                        //����=�t���� �ϼu
         br[i]->hp-=power;
         if(br[i]->hp<=0){
           delete br[i];
           br[i]=NULL;
           dele[deleN++]=i;
           op();
         }else{
           if(br[i]->hp==2) br[i]->Brush->Color=clRed;
           if(br[i]->hp==1) br[i]->Brush->Color=clYellow;
         }
       }
     }else{
       if(Top+20>br[i]->Top+35&&Top<=br[i]->Top+35&&Left<=br[i]->Left+65&&Left>=br[i]->Left-15){
         if(speedy<0){
           speedy=-speedy;
           br[i]->hp-=power;
           if(br[i]->hp<=0){
             delete br[i];
             br[i]=NULL;
             dele[deleN++]=i;
             op();
           }else{
             if(br[i]->hp==2) br[i]->Brush->Color=clRed;
             if(br[i]->hp==1) br[i]->Brush->Color=clYellow;
           }
         }
       }else{
         if(Left<br[i]->Left&&Left+20>=br[i]->Left&&Top<br[i]->Top+30&&Top>br[i]->Top-15){
           if(speedx>0){
             speedx=-speedx;
             br[i]->hp-=power;
             if(br[i]->hp<=0){
               delete br[i];
               br[i]=NULL;
               dele[deleN++]=i;
               op();
             }else{
               if(br[i]->hp==2) br[i]->Brush->Color=clRed;
               if(br[i]->hp==1) br[i]->Brush->Color=clYellow;
             }
           }
         }else{
           if(Left+20>br[i]->Left+70&&Left<=br[i]->Left+70&&Top<br[i]->Top+30&&Top>br[i]->Top-15){
             if(speedx<0){
               speedx=-speedx;
               br[i]->hp-=power;
               if(br[i]->hp<=0){
                 delete br[i];
                 br[i]=NULL;
                 dele[deleN++]=i;
                 op();
               }else{
                 if(br[i]->hp==2) br[i]->Brush->Color=clRed;
                 if(br[i]->hp==1) br[i]->Brush->Color=clYellow;
               }
             }
           }
         }
       }
     }
   }
   for(int i=0;i<ba[0]->bloN;i++){
     for(int m=0;m<delebloN;m++){
       if(deleblo[m]==i) deleBlo=true;
     }
     if(deleBlo){
       deleBlo=false;
       continue;
     }

     if(Top<blo[i]->Top&&Top+20>=blo[i]->Top&&Left<=blo[i]->Left+blo[i]->Width&&Left>=blo[i]->Left-Width/2){
       if(speedy>0){
         speedy=-speedy;
         if(blo[i]->life<=power){
           blo[i]->Visible=false;
           deleblo[delebloN++]=i;
           bloNN--;
         }
       }
     }else{
       if(Top+20>blo[i]->Top+20&&Top<=blo[i]->Top+20&&Left<=blo[i]->Left+blo[i]->Height&&Left>=blo[i]->Left-Width/2){
         if(speedy<0){
           speedy=-speedy;
           if(blo[i]->life<=power){
             blo[i]->Visible=false;
             deleblo[delebloN++]=i;
             bloNN--;
           }
         }
       }else{
         if(Left<blo[i]->Left&&Left+Width>=blo[i]->Left&&Top<blo[i]->Top+20&&Top>blo[i]->Top-Height/2){
           if(speedx>0){
             speedx=-speedx;
             if(blo[i]->life<=power){
               blo[i]->Visible=false;
               deleblo[delebloN++]=i;
               bloNN--;
             }
           }
         }else{
           if(Left+20>blo[i]->Left+blo[i]->Width&&Left<=blo[i]->Left+blo[i]->Width&&Top<blo[i]->Top+20&&Top>blo[i]->Top-Height/2){
             if(speedx<0){
               speedx=-speedx;
               if(blo[i]->life<=power){
                 blo[i]->Visible=false;
                 deleblo[delebloN++]=i;
                 bloNN--;
               }
             }
           }
         }
       }
     }
   }

   Top+=speedy; Left+=speedx;
   if(deleN==77){
     for(int i=0;i<baN;i++){
       ba[i]->engine->Enabled=false;
     }
     engine->Enabled=false;
     ShowMessage("YA~���ߧA����o!!!");
   }

   if(bloNN==0||delebaN==0){
     for(int i=0;i<baN;i++){
       ba[i]->engine->Enabled=false;
     }
     ShowMessage("�A���~�A�Ӥ@���a");
   }
}

void ball::op(){
  int a=random(4);
  if(a==0){
    int x=random(baN);
    int y=random(baN);
    switch (random(7)){
      case 0:
        for(int i=baN;i<baN+3;i++){
          ba[i]=new ball();
          ba[i]->engine->Enabled=true;
          ba[i]->Left=random(Form1->Panel1->Width-100);
          ba[i]->Top=random(Form1->Panel1->Top)+400;
        }
        baN+=3;
        delebaN+=3;
        break;
      case 1:
        for(int i=baN;i<baN+2;i++){
          ba[i]=new ball();
          ba[i]->power=2;
          ba[i]->engine->Enabled=true;
          ba[i]->Left=random(Form1->Panel1->Width-100);
          ba[i]->Top=random(Form1->Panel1->Top)+400;
          ba[i]->Brush->Color=clBlue;
          ba[i]->Width=25;
          ba[i]->Height=25;
        }
        baN+=2;
        delebaN+=2;
        break;
      case 2:
        ba[baN]=new ball();
        ba[baN]->power=3;
        ba[baN]->engine->Enabled=true;
        ba[baN]->Left=random(Form1->Panel1->Width-100);
        ba[baN]->Top=random(Form1->Panel1->Top)+400;
        ba[baN]->Brush->Color=clPurple;
        ba[baN]->Width=30;
        ba[baN]->Height=30;
        baN++;
        delebaN++;
        break;
      case 3:
        ba[x]->speedx=ba[x]->speedx*2;         
        ba[x]->speedy=ba[x]->speedy*2;
        break;
      case 4:
        ba[y]->speedx=ba[y]->speedx/2;
        ba[y]->speedy=ba[y]->speedy/2;
        break;
      case 5:
        blo[bloN]=new block();
        blo[bloN]->Top=blo[0]->Top-21*bloNN;
        blo[bloN]->Left=blo[0]->Left-20;
        blo[bloN]->Width=120;
        int b=random(2);
        if(b==0){
          blo[bloN]->life=3;
          blo[bloN]->Brush->Color=clBlue;
        }else{
          blo[bloN]->life=2;
          blo[bloN]->Brush->Color=clAqua;
        }
        bloN++;
        bloNN++;
    }
  }
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  Panel1->DoubleBuffered = true;
  randomize();
  int L=0,T=0;
  for(int i=0;i<77;i++){
    br[i]=new brick();
    if(L*70>=Panel1->Width){L=0;T++;}
    br[i]->Left=(L++)*70;
    br[i]->Top=35*T;
  }
  blo[0]=new block();
  ba[0]=new ball();

/*  for(int i=1;i<5;i++){
    ba[i]=new ball();
    ba[i]->engine->Enabled=true;
    ba[i]->Left=random(Panel1->Width);
    ba[i]->Top=random(Panel1->Top+400);
  }
  ba[0]->baN+=4;
  ba[0]->delebaN+=4;  */
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  blo[0]->Left=X;
  for(int i=1;i<ba[0]->bloN;i++){
    blo[i]->Left=X-20;
  }
  if(start==false) ba[0]->Left=X+30;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel1Click(TObject *Sender)
{
  start=true;
  ba[0]->engine->Enabled=true;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
  for(int i=0;i<ba[0]->baN;i++){
    ba[i]->engine->Enabled=false;
    delete ba[i];
    ba[i]=NULL;
  }

  for(int i=0;i<ba[0]->bloN;i++){
    delete blo[i];
    blo[i]=NULL;
  }

  for(int i=0;i<77;i++){
    for(int m=0;m<ba[0]->deleN;m++){
       if(ba[0]->dele[m]==i) ba[0]->deleB=true;
     }
     if(ba[0]->deleB){
       ba[0]->deleB=false;
       continue;
     }
     delete br[i];
     br[i]=NULL;
  }


  int L=0,T=0;
  for(int i=0;i<77;i++){
    br[i]=new brick();
    if(L*70>=Panel1->Width){L=0;T++;}
    br[i]->Left=(L++)*70;
    br[i]->Top=35*T;
  }
  blo[0]=new block();
  ba[0]=new ball();

  ba[0]->baN=1;
  ba[0]->deleN=0;
  ba[0]->deleB=false;
  ba[0]->deleBlo=false;
  ba[0]->bloN=1;
  ba[0]->bloNN=1;
  ba[0]->delebloN=0;
  ba[0]->delebaN=1;

  start=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
  for(int i=0;i<ba[0]->baN;i++){
    ba[i]->engine->Enabled=false;
    delete ba[i];
    ba[i]=NULL;
  }

  for(int i=0;i<ba[0]->bloN;i++){
    delete blo[i];
    blo[i]=NULL;
  }

  for(int i=0;i<77;i++){
    for(int m=0;m<ba[0]->deleN;m++){
       if(ba[0]->dele[m]==i) ba[0]->deleB=true;
     }
     if(ba[0]->deleB){
       ba[0]->deleB=false;
       continue;
     }
     delete br[i];
     br[i]=NULL;
  }
}
//---------------------------------------------------------------------------
