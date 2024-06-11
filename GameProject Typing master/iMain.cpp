# include "iGraphics.h"
#include <time.h>
#include <iostream>
#include <windows.h>
#include<bits/stdc++.h>
using namespace std;

//game base is 145px up
const int totalblock=20;//total block to be created
int createblock[totalblock];//to check if block is created or not
int bx[totalblock];//x axis of block
int by[totalblock];//y axis of block
int arrofPage[20];//to check which page to show
int countingTIME=0;//to count the time for game start
int GAMESTARTED=0;
int timerOFblockChange=40,timerOFblockCreate=550;//timer for block change and create
int musicOnOff=0;//to check if music is on or off
int blockShouldChange=0;//to check if block should change or not
int gametargetscore=-1;
int yourscore=0;
float gameTIME=0;
int keyPERscore=10;
float keyperTime=0;
int TIMEOVER=0;
int gameinitialsSETED=0;
clock_t gamestartingTICKS , currentTimeTICKS,casualstartingTICKS;
double TIMEshowinTHEdisplay;
char yourscoreCHAR[100];
char gametargetscoreCHAR[100];
char TIMEshowinTHEdisplayCHAR[100];
int currentletters[totalblock];
int typedWORD=0;
int keyperMIN=0;
int tutorialpageno=1;
int casuali=0;
int casualj=0;
int typedi=0;
int typedj=0;
char typingtextCHAR[20][100];
char typingtext_typed[20][100];
int casual_tractLASTj[20];
int casualWrong=0;
int casualwrongfliter=0;
int casualwrongcount=0;
int text_tractLASTj[10];
const int typingfile=5;//no of text file to practice
int fileextracted=0;
const int tutorialTotalSlide=6;//total slide of tutorial
int correcticon=610;
int speedEnhance=0;
char historyExtractedText[8][10];
int gamehardnessMode=0;
int updatedDATA=0;
const int topLetterCount=13;//how many letters should be count to slected practice
int topLetter[topLetterCount];
typedef struct{
	int count=0;
	int charidx;
}wronghistoryidx;//
wronghistoryidx wronghistorystruct[26];
int pageno=2;//which page to go after game win or loss

char historyText[4][35]={{"historytext\\easyhistory.txt"},{"historytext\\mediumhistory.txt"},{"historytext\\hardhistory.txt"},{"historytext\\typedhistory.txt"}};

char letterBlock[26][25]={{"image\\letters\\a.bmp"},{"image\\letters\\b.bmp"},{"image\\letters\\c.bmp"},{"image\\letters\\d.bmp"},
{"image\\letters\\e.bmp"},{"image\\letters\\f.bmp"},{"image\\letters\\g.bmp"},{"image\\letters\\h.bmp"},{"image\\letters\\i.bmp"},
{"image\\letters\\j.bmp"},{"image\\letters\\k.bmp"},{"image\\letters\\l.bmp"},{"image\\letters\\m.bmp"},{"image\\letters\\n.bmp"},
{"image\\letters\\o.bmp"},{"image\\letters\\p.bmp"},{"image\\letters\\q.bmp"},{"image\\letters\\r.bmp"},{"image\\letters\\s.bmp"},
{"image\\letters\\t.bmp"},{"image\\letters\\u.bmp"},{"image\\letters\\v.bmp"},{"image\\letters\\w.bmp"},{"image\\letters\\x.bmp"},
{"image\\letters\\y.bmp"},{"image\\letters\\z.bmp"}};

char filetext[typingfile][20]={{"text\\text1.txt"},{"text\\text2.txt"},{"text\\text3.txt"},{"text\\text4.txt"},{"text\\text5.txt"}};

char tutorialSlide[tutorialTotalSlide][30]={{"image\\tutorial\\Slide1.bmp"},{"image\\tutorial\\Slide2.bmp"},
{"image\\tutorial\\Slide3.bmp"},{"image\\tutorial\\Slide4.bmp"},{"image\\tutorial\\Slide5.bmp"},{"image\\tutorial\\Slide6.bmp"}};

int compare1(const void *a, const void *b) {
    const wronghistoryidx *lhs = (const wronghistoryidx *)a;
    const wronghistoryidx *rhs = (const wronghistoryidx *)b;
    return rhs->count-lhs->count;
}

int compare2(const void *a, const void *b) {
    const wronghistoryidx *lhs = (const wronghistoryidx *)a;
    const wronghistoryidx *rhs = (const wronghistoryidx *)b;
    return lhs->charidx - rhs->charidx;
}

void findTopLetter(){
	qsort(wronghistorystruct, 26, sizeof(wronghistorystruct[0]), compare1);
	for(int i=0;i<topLetterCount;i++){
		// cout<<wronghistorystruct[i].charidx<<endl;
		topLetter[i]=wronghistorystruct[i].charidx;
	}
	qsort(wronghistorystruct, 26, sizeof(wronghistorystruct[0]), compare2);
}

void wrongHistoryRead(){
	FILE* file=fopen("historytext\\wronghistory.txt","r");
	char historyData[26][20];
	for(int i=0;!feof(file);i++){
		fgets(historyData[i],20,file);
	}
	fclose(file);
	for(int i=0;i<26;i++){
		sscanf(historyData[i],"%d",&wronghistorystruct[i].count);
		wronghistorystruct[i].charidx=i;
	}
}

void wrongHistoryWrite(){
	FILE* file=fopen("historytext\\wronghistory.txt","w");
	char historyData[26][20];
	for(int i=0;i<26;i++){
		sprintf(historyData[i],"%d",wronghistorystruct[i].count);
	}
	for(int i=0;i<26;i++){
		fputs(historyData[i],file);
      	fputs("\n",file);
	}
	fclose(file);
}

void clear2DArray(char array[20][100]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 100; j++) {
            array[i][j] = '\0'; 
        }
    }
}

void makeALLzero(int arr[],int checkout=0){
	if(checkout==0){
		for(int i=0;i<totalblock;i++){
			arr[i]=0;
		}
	}
	else{
		for(int i=0;i<totalblock;i++){
			arr[i]=rand()%26;
		}
	}
	
}

void makeInitialsZERO(){
	makeALLzero(createblock);
	makeALLzero(bx);
	makeALLzero(bx);
	makeALLzero(currentletters,1);
	countingTIME=0;
	iResumeTimer(0);
	iPauseTimer(1);
	iPauseTimer(2);
	gametargetscore=-1;//-1 set so that game donot exit as because gametargetscore and yourscore is not same
	yourscore=0;
	gameTIME=0;
	keyPERscore=10;
	keyperTime=0;
	TIMEOVER=0;
	GAMESTARTED=0;
	gameinitialsSETED=0;
	typedWORD=0;
	keyperMIN=0;
	casuali=0;
	casualj=0;
	typedi=0;
	typedj=0;
	// casual_tractLASTj=0;//should be zero;
	casualWrong=0;
	casualwrongfliter=0;
	fileextracted=0;
	clear2DArray(typingtextCHAR);
	clear2DArray(typingtext_typed);
	memset(yourscoreCHAR, '\0', sizeof(yourscoreCHAR));
	memset(gametargetscoreCHAR, '\0', sizeof(gametargetscoreCHAR));
	memset(TIMEshowinTHEdisplayCHAR, '\0', sizeof(TIMEshowinTHEdisplay));
	memset(casual_tractLASTj, '\0', sizeof(casual_tractLASTj));
	updatedDATA=0;
	wrongHistoryRead();
	findTopLetter();
	wrongHistoryWrite();
}

void welcomedraw(){
	//arrofPage[1]
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(282,445,"image\\welcome.bmp",0);
	iShowBMP2(420,350,"image\\playnow.bmp",0);
	iShowBMP2(420,280,"image\\practice.bmp",0);
	iShowBMP2(420,210,"image\\tutorial.bmp",0);
	iShowBMP2(420,140,"image\\setting.bmp",0);	
}

void welcomemouse(int mx,int my){
	if(mx>420 && mx<575 && my>350 && my<410){
		//clicked in playnow
		arrofPage[1]=0;
		arrofPage[2]=1;
		makeInitialsZERO();
	}
	else if(mx>420 && mx<575 && my>280 && my<340){
		//clicked in prectice
		arrofPage[1]=0;
		arrofPage[7]=1;
		makeInitialsZERO();
	}
	else if(mx>420 && mx<575 && my>210 && my<270){
		//clicked in tutorial
		arrofPage[1]=0;
		arrofPage[8]=1;
		tutorialpageno=1;
	}
	else if(mx>420 && mx<575 && my>140 && my<200){
		//setting page
		arrofPage[1]=0;
		arrofPage[9]=1;
	}
}

void blockXaxisChange(int i){
	if(createblock[i]==1){
		// bx[i]+=(5+float((speedEnhance/10)*2.5));
		if(speedEnhance==0){
			bx[i]+=6;
		}
		else if(speedEnhance==10){
			bx[i]+=8;
		}
		else if(speedEnhance==20){
			bx[i]+=10;
		}
	}
}

void blockchange(){
	for(int i=0;i<totalblock;i++){
		blockXaxisChange(i);
	}
}

void blockcreate(){
	for(int i=0;i<totalblock;i++){
		if(createblock[i]==0){
			createblock[i]=1;
			break;
		}
	}
}

void showcountingOFgameTIME(){
	if(countingTIME==6){
		GAMESTARTED=1;
		iPauseTimer(0);
		iResumeTimer(1);
		iResumeTimer(2);
		iResumeTimer(4);
		gamestartingTICKS=clock();
	}
	else if(countingTIME<=5){
		iResumeTimer(0);
		iPauseTimer(1);
		iPauseTimer(2);
		countingTIME++;
	}
}

void showcountingOFgame(){
	if(countingTIME==1){
		iShowBMP2(310,225,"image\\counting\\5.bmp",0);
	}
	else if(countingTIME==2){
		iShowBMP2(310,225,"image\\counting\\4.bmp",0);
	}
	else if(countingTIME==3){
		iShowBMP2(310,225,"image\\counting\\3.bmp",0);
	}
	else if(countingTIME==4){
		iShowBMP2(310,225,"image\\counting\\2.bmp",0);
	}
	else if(countingTIME==5){
		iShowBMP2(310,225,"image\\counting\\1.bmp",0);
	}
}

void changeTHEarrayidx(int arr[]){
	for(int i=0;i<totalblock-1;i++){
		swap(arr[i],arr[i+1]);
	}
	createblock[totalblock-1]=0;
	bx[totalblock-1]=0;
	by[totalblock-1]=0;
	// currentletters[10]=0;
	currentletters[totalblock-1]=rand()%26;
}


void SetgameTargetTime(){
	gametargetscore=rand()%150+300;
	gametargetscore=gametargetscore-gametargetscore%10;
	keyperTime=(rand()%2+1);
	if(keyperTime==1){
		keyperTime+=float((rand()%3)/10 +.3);
	}
	else if(keyperTime==2){
		keyperTime-=(float((rand()%3)/10)+.4);
	}
	keyperTime-=speedEnhance*.02;
	gameTIME=float((gametargetscore/10)*(keyperTime));
}

void recordgame(int flag,int fileNO){
	FILE *fileRead=fopen(historyText[fileNO],"r");
	char gameData[3][20];
	for(int i=0;!feof(fileRead);i++){
		fgets(gameData[i],20,fileRead);
	}
	fclose(fileRead);
	int wincount,losscount;
	sscanf(gameData[0],"%d",&wincount);
	sscanf(gameData[1],"%d",&losscount);
	if(flag==1){
		wincount++;
	}
	else if(flag==0){
		losscount++;
	}
	char gameDatashow[3][20];
	FILE *fileWrite=fopen(historyText[fileNO],"w");
	sprintf(gameDatashow[0],"%d",wincount);
	sprintf(gameDatashow[1],"%d",losscount);
	fputs(gameDatashow[0],fileWrite);
	fputs("\n",fileWrite);
	fputs(gameDatashow[1],fileWrite);
	fclose(fileWrite);
}

void gamedraw(){
	if(GAMESTARTED==1 && gameinitialsSETED==0){
		SetgameTargetTime();
		gameinitialsSETED=1;
		musicOnOff=1;
	}
	//arrofpage[2]
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(5,535,"image\\home.bmp",0);
	iShowBMP2(10,145,"image\\longobstackle.bmp",0);
	// iShowBMP(400,145,"image\\midobstacle.bmp");
	iShowBMP2(840,535,"image\\scoreboard.bmp",0);
	iShowBMP2(680,535,"image\\yourscore.bmp",0);
	iShowBMP2(520,535,"image\\target.bmp",0);
	iShowBMP2(75,535,"image\\yourtime.bmp",0);
	if(GAMESTARTED==1){
		currentTimeTICKS=clock();
		TIMEshowinTHEdisplay=int(gameTIME-(double(currentTimeTICKS-gamestartingTICKS)/CLOCKS_PER_SEC));
		int timeremaining=int(TIMEshowinTHEdisplay);
		if(timeremaining==0){
			TIMEOVER=1;
		}
		snprintf(gametargetscoreCHAR, 100, "%d", gametargetscore);
		snprintf(TIMEshowinTHEdisplayCHAR, 100, "%d",timeremaining);
		snprintf(yourscoreCHAR, 100, "%d", yourscore);
		iText(625,560,gametargetscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(160,560,TIMEshowinTHEdisplayCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(900,560,yourscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	
	if((bx[0]>=865 || yourscore>=gametargetscore || TIMEOVER==1 ) && GAMESTARTED==1){
		musicOnOff=0;
		if(yourscore>=gametargetscore){
			//record win
			recordgame(1,gamehardnessMode);
			//may be removed
			arrofPage[3]=1;
			arrofPage[2]=0;
		}
		else{
			recordgame(0,gamehardnessMode);
			arrofPage[4]=1;
			arrofPage[2]=0;
		}
	}

	if(blockShouldChange==1){
		changeTHEarrayidx(createblock);
		changeTHEarrayidx(bx);
		changeTHEarrayidx(by);
		changeTHEarrayidx(currentletters);
		blockShouldChange=0;
		// iPauseTimer(3);
	}
	for(int i=0;i<totalblock;i++){
		if(createblock[i]==1){
			if(by[i]==0){
				by[i]=rand()%270+195;
				currentletters[i]=rand()%26;
			}
			iShowBMP(1000-bx[i],by[i],letterBlock[currentletters[i]]);
		}
	}
	if(countingTIME<6){
		showcountingOFgame();
	}
}

void gamedrawmouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		arrofPage[2]=0;
		arrofPage[1]=1;
		wrongHistoryWrite();
	}
}

void GameWin(){//40-120 up// 160-237 width
	//arrofpage[3]
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(5,535,"image\\home.bmp",0);
	iShowBMP2(300,62,"image\\gamewin.bmp",0);
	iSetColor(255,255,255);
	iText(485,212,yourscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
}

void GameWinmouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		arrofPage[3]=0;
		arrofPage[1]=1;
	}
	else if(mx>460 && mx<537 && my>102 && my<182){
		arrofPage[3]=0;
		arrofPage[pageno]=1;
		pageno=2;
		makeInitialsZERO();
	}
}

void GameLoss(){//40-120 up// 160-237 width
	//arrofpage[4]
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(5,535,"image\\home.bmp",0);
	iShowBMP2(300,62,"image\\gameloss.bmp",0);
	iSetColor(255,255,255);
	iText(485,212,yourscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
}

void GameLossmouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		arrofPage[4]=0;
		arrofPage[1]=1;
	}
	else if(mx>460 && mx<537 && my>102 && my<182){
		arrofPage[4]=0;
		arrofPage[pageno]=1;
		pageno=2;
		makeInitialsZERO();
	}
}

void gamePracticemode(){
	//arrofPage[5]
	if(GAMESTARTED==1){
		musicOnOff=1;
	}
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(5,535,"image\\home.bmp",0);
	iShowBMP2(10,145,"image\\longobstackle.bmp",0);
	// iShowBMP(400,145,"image\\midobstacle.bmp");
	iShowBMP2(840,535,"image\\scoreboard.bmp",0);
	iShowBMP2(680,535,"image\\yourscore.bmp",0);
	iShowBMP2(520,535,"image\\keypermin.bmp",0);
	iShowBMP2(75,535,"image\\yourtime.bmp",0);
	if(GAMESTARTED==1){
		currentTimeTICKS=clock();
		TIMEshowinTHEdisplay=double(currentTimeTICKS-gamestartingTICKS)/CLOCKS_PER_SEC;
		int timeremaining=int(TIMEshowinTHEdisplay);
		if(timeremaining!=0){
			keyperMIN=(typedWORD*60)/timeremaining;
		}
		snprintf(gametargetscoreCHAR, 100, "%d", keyperMIN);
		snprintf(TIMEshowinTHEdisplayCHAR, 100, "%d",timeremaining);
		snprintf(yourscoreCHAR, 100, "%d", yourscore);
		iText(625,560,gametargetscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(160,560,TIMEshowinTHEdisplayCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(900,560,yourscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	
	if(bx[0]>=865 && GAMESTARTED==1){
		musicOnOff=0;
		pageno=5;
		arrofPage[4]=1;
		arrofPage[5]=0;
	}
	if(blockShouldChange==1){
		changeTHEarrayidx(createblock);
		changeTHEarrayidx(bx);
		changeTHEarrayidx(by);
		changeTHEarrayidx(currentletters);
		blockShouldChange=0;
	}
	for(int i=0;i<totalblock;i++){
		if(createblock[i]==1){
			if(by[i]==0){
				by[i]=rand()%270+195;
				currentletters[i]=rand()%26;
			}
			iShowBMP(1000-bx[i],by[i],letterBlock[currentletters[i]]);
		}
	}
	if(countingTIME<6){
		showcountingOFgame();
	}
}

void gamePracticemodemouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		arrofPage[5]=0;
		arrofPage[1]=1;
		wrongHistoryWrite();
	}
}

void allpracticeMODE(){
	//arrofpage[7]
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(282,445,"image\\welcome.bmp",0);
	iShowBMP2(420,350,"image\\gamepractice.bmp",0);
	iShowBMP2(420,280,"image\\selectivePractice.bmp",0);
	iShowBMP2(420,210,"image\\casualpractice.bmp",0);
	iShowBMP2(5,535,"image\\home.bmp",0);
}

void allpracticeMODEmouse(int mx,int my){
	if(mx>420 && mx<575 && my>350 && my<410){
		//clicked in game mode practice
		arrofPage[7]=0;
		arrofPage[5]=1;
		makeInitialsZERO();
	}
	else if(mx>420 && mx<575 && my>280 && my<340){
		//clicked in selective practice mode
		arrofPage[7]=0;
		arrofPage[11]=1;
		//add
		makeInitialsZERO();
		findTopLetter();
		//remove
		for(int i=0;i<topLetterCount;i++){
			cout<<topLetter[i]<<" ";
		}
		cout<<endl<<"-----------------------"<<endl;
		//remove
	}
	else if(mx>420 && mx<575 && my>210 && my<260){
		//clicked in casual mode practice
		arrofPage[7]=0;
		arrofPage[6]=1;
		casualstartingTICKS=clock();
		makeInitialsZERO();
		GAMESTARTED=1;
	}

	else if(mx>5 && mx<65  && my>535 && my<595){
		//clicked home
		arrofPage[7]=0;
		arrofPage[1]=1;
	}
}

void tutorialdraw(){
	//arrofPage[8]
	iSetColor(255,255,255);
	iFilledRectangle(0,0,1000,600);
	iShowBMP2(5,535,"image\\home.bmp",0);
	
	if(tutorialpageno>1){
		iShowBMP2(870,535,"image\\back.bmp",0);
	}
	if(tutorialpageno<tutorialTotalSlide){
		iShowBMP2(935,535,"image\\forward.bmp",0);
	}

	iShowBMP(56,17,tutorialSlide[tutorialpageno-1]);
}

void tutorialdrawmouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		arrofPage[8]=0;
		arrofPage[1]=1;
	}
	else if(mx>870 && mx<930 && my>535 && my<595 && tutorialpageno>1){
		tutorialpageno--;
	}
	else if(mx>935 && mx<995 && my>535 && my<595 && tutorialpageno<tutorialTotalSlide){
		tutorialpageno++;
	}
}

void FileExtractWord(){
	FILE *file=fopen(filetext[rand()%typingfile],"r");
	for(int i=0;!feof(file);i++){
		fgets(typingtextCHAR[i],100,file);
	}
	fclose(file);
}

void showWrongalert(){
	if(casualwrongfliter==0){
		casualwrongfliter=1;
	}
	else if(casualwrongfliter==1){
		casualwrongfliter=0;
	}
}

void recordCasualPractice(int keyperMIN){
	FILE *fileRead=fopen(historyText[3],"r");
	char gameData[3][20];
	for(int i=0;!feof(fileRead);i++){
		fgets(gameData[i],20,fileRead);
	}
	fclose(fileRead);
	int typecount,keypermincount;
	sscanf(gameData[0],"%d",&typecount);
	sscanf(gameData[1],"%d",&keypermincount);
	keypermincount=(keyperMIN+keypermincount)/2;
	typecount++;
	char gameDatashow[3][20];
	FILE *fileWrite=fopen(historyText[3],"w");
	sprintf(gameDatashow[0],"%d",typecount);
	sprintf(gameDatashow[1],"%d",keypermincount);
	fputs(gameDatashow[0],fileWrite);
	fputs("\n",fileWrite);
	fputs(gameDatashow[1],fileWrite);
	fclose(fileWrite);
}

void casualpracticedraw(){
	iShowBMP(0,0,"image\\casualpracticeBG.bmp");
	iShowBMP2(5,535,"image\\home.bmp",0);
	iShowBMP2(75,535,"image\\back.bmp",0);
	iShowBMP2(840,535,"image\\keypermin.bmp",0);
	iShowBMP2(145,535,"image\\yourtime.bmp",0);
	iShowBMP2(675,535,"image\\whatshouldtype.bmp",0);
	if(GAMESTARTED==1){
		currentTimeTICKS=clock();
	}
	TIMEshowinTHEdisplay=double(currentTimeTICKS-casualstartingTICKS)/CLOCKS_PER_SEC;
	int timeremaining=int(TIMEshowinTHEdisplay);
	if(timeremaining!=0){
		keyperMIN=(typedWORD*60)/timeremaining;
	}
	else{
		keyperMIN=0;
	}
	snprintf(gametargetscoreCHAR, 100, "%d", keyperMIN);
	snprintf(TIMEshowinTHEdisplayCHAR, 100, "%d",timeremaining);
	iText(945,560,gametargetscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(230,560,TIMEshowinTHEdisplayCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
	if(fileextracted==0){
		FileExtractWord();
		fileextracted=1;
	}
	
	for(int i=0;i<10;i++){
		iText(35,420-24*i,typingtextCHAR[i],GLUT_BITMAP_HELVETICA_18);
	}

	char typechar[5];
	if(typingtextCHAR[casuali][casualj]==char(10)){
		iText(760,560,"Enter/space",GLUT_BITMAP_HELVETICA_18);
	}
	else if(typingtextCHAR[casuali][casualj]==' '){
		iText(760,560,"Space",GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else{
		snprintf(typechar, 5, "%c", typingtextCHAR[casuali][casualj]);
		iText(760,560,typechar,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	

	typingtext_typed[typedi][typedj]='_';
	for(int i=0;i<20;i++){
		iText(515,420-24*i,typingtext_typed[i],GLUT_BITMAP_HELVETICA_18);
	}

	if(casualWrong==1){
		iResumeTimer(3);
		if(casualwrongfliter==0){
			iShowBMP2(422,535,"image\\wrong.bmp",0);
		}
		else if(casualwrongfliter==1){
			iShowBMP(422,535,"image\\wrongfliter.bmp");
		}
	}
	else if(casualWrong==0){
		iPauseTimer(3);
	}
	
	if(casuali==9 && typingtextCHAR[casuali][casualj]=='\0'){
		if(updatedDATA==0){
			recordCasualPractice(keyperMIN);
			updatedDATA=1;
		}
		iShowBMP2(275,245,"image\\welldone.bmp",0);
		GAMESTARTED=0;
	}	
}

void casualpracticedrawkeyboard(unsigned char key){
	//checking typed word
	if(key=='\b' && typingtextCHAR[casuali][casualj]==' '){
		typedWORD--;
	}

	int forceEnterForSpace=0;
	if(key=='\b' && casualwrongcount==0){
		
		if(casualj>0){
			casualj--;
		}
		else if(casualj==0 && casuali>0){
			casualj=text_tractLASTj[--casuali];
		}
		casualWrong=0;
		// typedWORD--;
		// if(typingtextCHAR[casuali][casualj]==' ')typedWORD--;
	}
	else if(typingtextCHAR[casuali][casualj]==char(10) && (key==char(13) || key==' ') && casualwrongcount==0){
		text_tractLASTj[casuali]=casualj;
		casuali++;
		casualj=0;
		// typedWORD++;
		casualWrong=0;
		if(key==' '){
			forceEnterForSpace=1;
		}
	}
	else if(key==typingtextCHAR[casuali][casualj] && casualwrongcount==0){
		casualj++;
		// typedWORD++;
		casualWrong=0;
	}
	else{
		if(int(key)>=97 && int(key)<=122){
			if(isupper(typingtextCHAR[casuali][casualj])){
				wronghistorystruct[int(typingtextCHAR[casuali][casualj])-65].count+=1;
			}
			else{
				wronghistorystruct[int(typingtextCHAR[casuali][casualj])-97].count+=1;
			}
		}
	
		if(key=='\b' && casualwrongcount!=0){
			casualwrongcount--;
		}
		else{
			casualwrongcount++;
		}
		casualWrong=1;
	}

	//showing typed word
	if(key==char(8)){
		if(typedj>0){
			typingtext_typed[typedi][typedj]='\0';
			typingtext_typed[typedi][--typedj]='\0';
		}
		else if(typedj==0 && typedi!=0){
			typingtext_typed[typedi--][typedj]='\0';
			typedj=casual_tractLASTj[typedi];
		}
		
	}
	else if(key==char(13) || forceEnterForSpace==1){
		typingtext_typed[typedi][typedj]='\0';
		casual_tractLASTj[typedi]=typedj;
		typedi++;
		typedj=0;
		forceEnterForSpace=0;
	}
	else{
		typingtext_typed[typedi][typedj++]=key;
	}

	//alert
	if(casualwrongcount==0){
		casualWrong=0;
	}

	if(typedi==0 && typedj==0){
		typedWORD=0;
	}

	//try
	if((typingtextCHAR[casuali][casualj]==' ' || typingtextCHAR[casuali][casualj]==char(10)) && key!='\b'){
		typedWORD++;
	}
}

void casualpracticedrawmouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		arrofPage[6]=0;
		arrofPage[1]=1;
		wrongHistoryWrite();
	}
	else if(mx>70 && mx<130  && my>535 && my<595){
		arrofPage[6]=0;
		arrofPage[7]=1;
		wrongHistoryWrite();
	}
}

void settingdraw(){
	//arrofPage[9]==1
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(5,535,"image\\home.bmp",0);	
	iShowBMP2(282,445,"image\\welcome.bmp",0);
	iShowBMP2(420,350,"image\\gamemode.bmp",0);
	iShowBMP2(590,350,"image\\gamemodeEasy.bmp",0);
	iShowBMP2(660,350,"image\\gamemodeMedium.bmp",0);
	iShowBMP2(730,350,"image\\gamemodeHard.bmp",0);
	//easy-610,medium-680,hard-750
	iShowBMP2(correcticon,400,"image\\correct.bmp",0);
	iShowBMP2(420,280,"image\\Gamerecord.bmp",0);
}

void settingdrawmouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		//clicked home
		arrofPage[9]=0;
		arrofPage[1]=1;
	}
	else if(mx>590 && mx<650 && my>350 && my<410){
		correcticon=610;
		speedEnhance=0;
		gamehardnessMode=0;
	}
	else if(mx>660 && mx<720 && my>350 && my<410){
		correcticon=680;
		speedEnhance=10;
		gamehardnessMode=1;
		// timerOFblockChange-=10;
	}
	else if(mx>730 && mx<790 && my>350 && my<410){
		correcticon=750;
		speedEnhance=20;
		gamehardnessMode=2;
		// timerOFblockChange-=20;
	}
	else if(mx>420 && mx<575 && my>280 && my<340){
		//clicked in game record
		fileextracted=0;
		arrofPage[9]=0;
		arrofPage[10]=1;
	}
}

void extracthistory(){
	FILE *fileRead1=fopen("historytext\\easyhistory.txt","r");
	for(int i=0;i<2;i++){
		fgets(historyExtractedText[i],20,fileRead1);
	}
	fclose(fileRead1);
	FILE *fileRead2=fopen("historytext\\mediumhistory.txt","r");
	for(int i=0;i<2;i++){
		fgets(historyExtractedText[i+2],20,fileRead2);
	}
	fclose(fileRead2);
	FILE *fileRead3=fopen("historytext\\hardhistory.txt","r");
	for(int i=0;i<2;i++){
		fgets(historyExtractedText[i+4],20,fileRead3);
	}
	fclose(fileRead3);
	FILE *fileRead4=fopen("historytext\\typedhistory.txt","r");
	for(int i=0;i<2;i++){
		fgets(historyExtractedText[i+6],20,fileRead4);
	}
	fclose(fileRead4);
}

void gameRecord(){
	//arrofPage[10]=1;
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(5,535,"image\\home.bmp",0);
	iShowBMP2(75,535,"image\\back.bmp",0);

	iShowBMP2(25,430,"image\\gamemode.bmp",0);
	iShowBMP2(200,430,"image\\easyTable.bmp",0);
	iShowBMP2(200,360,"image\\mediumTable.bmp",0);
	iShowBMP2(200,290,"image\\hardTable.bmp",0);
	iShowBMP2(365,430,"image\\scoreboard.bmp",0);
	iShowBMP2(530,430,"image\\scoreboard.bmp",0);
	iShowBMP2(365,360,"image\\scoreboard.bmp",0);
	iShowBMP2(530,360,"image\\scoreboard.bmp",0);
	iShowBMP2(365,290,"image\\scoreboard.bmp",0);
	iShowBMP2(530,290,"image\\scoreboard.bmp",0);
	iShowBMP2(530,290,"image\\scoreboard.bmp",0);
	iShowBMP2(365,500,"image\\winTable.bmp",0);
	iShowBMP2(530,500,"image\\lossTable.bmp",0);

	iShowBMP2(35,220,"image\\casualpracticeTable.bmp",0);
	iShowBMP2(200,220,"image\\totalParagraphTypedTable.bmp",0);
	iShowBMP2(530,220,"image\\scoreboard.bmp",0);
	iShowBMP2(200,150,"image\\avaragewordpermin.bmp",0);
	iShowBMP2(530,150,"image\\scoreboard.bmp",0);

	if(fileextracted==0){
		extracthistory();
		fileextracted==1;
	}

	iText(415,455,historyExtractedText[0],GLUT_BITMAP_TIMES_ROMAN_24);
	iText(580,450,historyExtractedText[1],GLUT_BITMAP_TIMES_ROMAN_24);
	iText(415,385,historyExtractedText[2],GLUT_BITMAP_TIMES_ROMAN_24);
	iText(580,385,historyExtractedText[3],GLUT_BITMAP_TIMES_ROMAN_24);
	iText(415,315,historyExtractedText[4],GLUT_BITMAP_TIMES_ROMAN_24);
	iText(580,315,historyExtractedText[5],GLUT_BITMAP_TIMES_ROMAN_24);
	iText(580,245,historyExtractedText[6],GLUT_BITMAP_TIMES_ROMAN_24);
	iText(580,175,historyExtractedText[7],GLUT_BITMAP_TIMES_ROMAN_24);
	// iShowBMP2(695,200,"image\\qouteofMe.bmp",0);
}

void gameRecordMouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		arrofPage[10]=0;
		arrofPage[1]=1;
	}
	else if(mx>75 && mx<135  && my>535 && my<595){
		arrofPage[10]=0;
		arrofPage[9]=1;
	}
}

void selectivePractice(){
//arrofPage[11]
	if(GAMESTARTED==1){
		musicOnOff=1;
	}
	iShowBMP(0,0,"image\\gamebackground.bmp");
	iShowBMP2(5,535,"image\\home.bmp",0);
	iShowBMP2(10,145,"image\\longobstackle.bmp",0);
	// iShowBMP(400,145,"image\\midobstacle.bmp");
	iShowBMP2(840,535,"image\\scoreboard.bmp",0);
	iShowBMP2(680,535,"image\\yourscore.bmp",0);
	iShowBMP2(520,535,"image\\keypermin.bmp",0);
	iShowBMP2(75,535,"image\\yourtime.bmp",0);
	if(GAMESTARTED==1){
		currentTimeTICKS=clock();
		TIMEshowinTHEdisplay=double(currentTimeTICKS-gamestartingTICKS)/CLOCKS_PER_SEC;
		int timeremaining=int(TIMEshowinTHEdisplay);
		if(timeremaining!=0){
			keyperMIN=(typedWORD*60)/timeremaining;
		}
		snprintf(gametargetscoreCHAR, 100, "%d", keyperMIN);
		snprintf(TIMEshowinTHEdisplayCHAR, 100, "%d",timeremaining);
		snprintf(yourscoreCHAR, 100, "%d", yourscore);
		iText(625,560,gametargetscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(160,560,TIMEshowinTHEdisplayCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(900,560,yourscoreCHAR,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	
	if(bx[0]>=865 && GAMESTARTED==1){
		musicOnOff=0;
		pageno=11;
		arrofPage[4]=1;
		arrofPage[5]=0;
	}
	if(blockShouldChange==1){
		changeTHEarrayidx(createblock);
		changeTHEarrayidx(bx);
		changeTHEarrayidx(by);
		changeTHEarrayidx(currentletters);
		blockShouldChange=0;
	}
	for(int i=0;i<totalblock;i++){
		if(createblock[i]==1){
			if(by[i]==0){
				by[i]=rand()%270+195;
				currentletters[i]=topLetter[rand()%topLetterCount];
			}
			iShowBMP(1000-bx[i],by[i],letterBlock[currentletters[i]]);
		}
	}
	if(countingTIME<6){
		showcountingOFgame();
	}
}

void selectivePracticeMouse(int mx,int my){
	if(mx>5 && mx<65  && my>535 && my<595){
		arrofPage[5]=0;
		arrofPage[1]=1;
		wrongHistoryWrite();
	}
}

void iDraw() {
	iClear();
	if(arrofPage[1]==1){
		welcomedraw();
	}
	else if(arrofPage[2]==1){
		gamedraw();
	}
	else if(arrofPage[3]==1){
		GameWin();
	}
	else if(arrofPage[4]==1){
		GameLoss();
	}
	else if(arrofPage[5]==1){
		gamePracticemode();
	}
	else if(arrofPage[6]==1){
		casualpracticedraw();
	}
	else if(arrofPage[7]==1){
		allpracticeMODE();
	}
	else if(arrofPage[8]==1){
		tutorialdraw();
	}
	else if(arrofPage[9]==1){
		settingdraw();
	}
	else if(arrofPage[10]==1){
		gameRecord();
	}
	else if(arrofPage[11]==1){
		selectivePractice();
	}

	if(arrofPage[8]!=1){
		// iShowBMP2(685,5,"image\\copyright.bmp",0);
	}
}

void iMouseMove(int mx, int my) {
	
}

void iMouse(int button, int state, int mx, int my) {
	if(arrofPage[1]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		welcomemouse(mx,my);
	}
	else if(arrofPage[2]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		gamedrawmouse(mx,my);
	}
	else if(arrofPage[3]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		GameWinmouse(mx,my);
	}
	else if(arrofPage[4]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		GameLossmouse(mx,my);
	}
	else if((arrofPage[5]==1) && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		gamePracticemodemouse(mx,my);
	}
	else if(arrofPage[6]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		casualpracticedrawmouse(mx,my);
	}
	else if(arrofPage[7]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		allpracticeMODEmouse(mx,my);
	}
	else if(arrofPage[8]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		tutorialdrawmouse(mx,my);
	}
	else if(arrofPage[9]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		settingdrawmouse(mx,my);
	}
	else if(arrofPage[10]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		gameRecordMouse(mx,my);
	}
	else if(arrofPage[11]==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		selectivePracticeMouse(mx,my);
	}
}

void iKeyboard(unsigned char key) {
	if(arrofPage[2]==1 || arrofPage[5]==1 || arrofPage[11]==1){
		if(key==char(97+currentletters[0])){
			blockShouldChange=1;
			yourscore+=10;
			if(arrofPage[5]==1){
				typedWORD+=1;
			}
		}
		else{
			yourscore-=(5+speedEnhance/2);
			wronghistorystruct[currentletters[0]].count+=1;
		}
	}
	else if(arrofPage[6]==1){
		casualpracticedrawkeyboard(key);
	}
}

void iSpecialKeyboard(unsigned char key) {
	
}

int main() {
	arrofPage[1]=1;
	srand(time(NULL));
	int initcheckd_mark=1;
	if(initcheckd_mark==1){
		wrongHistoryRead();
		initcheckd_mark=0;
	}
	iSetTimer(500,showcountingOFgameTIME);//timer[0]
	iSetTimer(timerOFblockChange,blockchange);//delay for block movement//timer[1]
	iSetTimer(timerOFblockCreate,blockcreate);//delay for creating new block//timer[2]
	iPauseTimer(1);
	iPauseTimer(2);
	iSetTimer(200,showWrongalert);
	iPauseTimer(3);
	iInitialize(1000, 600, "Floating Word");

	return 0;
}

// for new line=10
// for enter=13

//extra long obstacle is 10px
//for one song: SND_ASYNC
//for loop song: SND_LOOP

//exit(0);
//button == GLUT_LEFT_BUTTON && state == GLUT_DOWN
//button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN
/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/