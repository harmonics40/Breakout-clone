//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
brick *br[77];     //磚塊
block *blo[10];    //檔板
ball *ba[1000];    //球
bool start=false;  //判斷遊戲是否開始
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

brick::brick():TShape(Form1){
  Parent=Form1->Panel1;              //磚塊在Panel1中顯示
  Pen->Style=psInsideFrame;
  Pen->Width=5;
  Height=35;
  Width=70;

  hp=random(3)+1;                    //隨機生命值
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
  Parent=Form1->Panel1;                   //球在Panel1中顯示
  Brush->Color=clRed;
  Shape=stCircle;
  Height=20;
  Width=20;
  Top=blo[0]->Top-18;                    //高度位置在第一個檔板上面

  engine=new TTimer(Form1);              //新增Timer engine
  engine->OnTimer=move;                  //OnTimer事件函式寫在move中
  engine->Interval=1;                    //每隔0.001秒跑一次Timer
  engine->Enabled=false;                 //一開始Timer關掉

  speedx=2;                             //速度2
  speedy=-2;
  power=1;                              //球威力值=1
}

__fastcall ball::~ball(){
  delete engine;                        //刪掉engine
}

block::block():TShape(Form1){
  Parent=Form1->Panel1;                 //檔板在Panel1中顯示
  Brush->Color=clGreen;
  Pen->Style=psInsideFrame;
  Pen->Width=5;
  Width=80;
  Height=20;
  Top=Form1->Panel1->Height-22;         //高度位置在Panel1底部

  life=2;                               //檔板承受度=2

}

__fastcall block::~block(){

}

void __fastcall ball::move(TObject *Sender){
   if(Top<=0) speedy=-speedy;                                                                 //球碰到上面邊界反彈
   if(Left+Width>=Form1->Panel1->Width||Left<=0) speedx=-speedx;                              //左右邊界反彈
   if(Top>=Form1->Panel1->Height){                                                            //球掉下去
     Enabled=false;                                                                           //功能關掉
     engine->Enabled=false;                                                                   //Timer關掉
     Top=Form1->Panel1->Top-100;                                                              //先放到Panel1上面
     delebaN--;                                                                               //目前球數-1
   }

   for(int i=0;i<br[0]->brN;i++){                                                               //判斷所有磚塊有沒有被撞到
     for(int m=0;m<deleN;m++){                                                                  //判斷是否為已刪除的磚塊
       if(dele[m]==i) deleB=true;
     }
     if(deleB){                                                                                 //若為已刪除的磚塊 跳過不繼續判斷碰撞
       deleB=false;
       continue;
     }

     if(Top<br[i]->Top&&Top+20>=br[i]->Top&&Left<=br[i]->Left+65&&Left>=br[i]->Left-15){        //球的位置在磚塊上方 且 球觸碰到磚塊 且 球在此磚塊左右範圍之內
       if(speedy>0){
         speedy=-speedy;                                                                        //高度=負高度 反彈
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
     ShowMessage("YA~恭喜你獲勝囉!!!");
   }

   if(bloNN==0||delebaN==0){
     for(int i=0;i<baN;i++){
       ba[i]->engine->Enabled=false;
     }
     ShowMessage("你輸啦~再來一局吧");
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

