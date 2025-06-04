#include <bits/stdc++.h>
#include <windows.h>
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

std::string versionNum="6.0";

bool checkStartUp();

int width, height;
int blackR, blackG, blackB;
int pixX, pixY;
int startX, startY;
int stepX, stepY;
int scanningTime;
int debugMode;

long long int getTimeStamp();

void left_click(int, int);
void right_click(int, int);

COLORREF GetColor(int, int);
void PrintColor(COLORREF);

bool ScrBlk();

std::string getPath(bool fileName=false);

void autoShutdown();

int main(){
	if(!checkStartUp()){
		system(".\\SetStartUp.exe");
	}
	freopen("config_in.txt", "r", stdin);
		scanf("%d %d %d", &blackR, &blackG, &blackB);
		scanf("%d %d", &pixX, &pixY);
		scanf("%d %d", &startX, &startY);
		scanf("%d %d", &stepX, &stepY);
		scanf("%d", &scanningTime);
		scanf("%d", &debugMode);
	fclose(stdin);
	
	freopen("config_out.txt", "w", stdout);
		printf("[Config]  Files are under: ");
		std::cout<<getPath()<<std::endl;
	
		if(blackR&&blackG&&blackB){
			printf("[Success] Scanned the RGB code of black: %d %d %d\n", blackR, blackG, blackB);
		}
		else{
			fclose(stdout);
			freopen("config_in.txt", "a", stdout);
			blackR=blackG=blackB=5;
			printf("%d %d %d\n", blackR, blackG, blackB);
			fclose(stdout);
			freopen("config_out.txt", "a", stdout);
			printf("[Error]   Didn't get the RGB code of black, created one successfully: %d %d %d\n", blackR, blackG, blackB);
		}
	
		HDC screen_dc=GetDC(NULL);
    	width=GetDeviceCaps(screen_dc, DESKTOPHORZRES);
    	height=GetDeviceCaps(screen_dc, DESKTOPVERTRES);
    	ReleaseDC(NULL, screen_dc);
		printf("[Success] Scanned the width and height of the screen: %d %d\n", width, height);
	
		if(pixX&&pixY){
			printf("[Success] Scanned the CLOSE button's coordinate: (%d, %d)\n", pixX, pixY);
		}
		else{
			pixX=width-40;
			pixY=40;
			fclose(stdout);
			freopen("config_in.txt", "a", stdout);
			printf("%d %d\n", pixX, pixY);
			fclose(stdout);
			freopen("config_out.txt", "a", stdout);
			printf("[Error]   Didn't get the CLOSE button's coordinate, created one successfully: (%d, %d)\n", pixX, pixY);
		}
		
		if(startX&&startY){
			printf("[Success] Scanned the start coordinate: (%d, %d)\n", startX, startY);
		}
		else{
			fclose(stdout);
			freopen("config_in.txt", "a", stdout);
			startX=startY=100;
			printf("%d %d\n", startX, startY);
			fclose(stdout);
			freopen("config_out.txt", "a", stdout);
			printf("[Error]   Didn't get the start coordinate, created one successfully: (%d, %d)\n", startX, startY);
		}
		
		if(stepX&&stepY){
			printf("[Success] Scanned the step of each time: %d %d\n", stepX, stepY);
		}
		else{
			fclose(stdout);
			freopen("config_in.txt", "a", stdout);
			stepX=stepY=200;
			printf("%d %d\n", stepX, stepY);
			fclose(stdout);
			freopen("config_out.txt", "a", stdout);
			printf("[Error]   Didn't get the step of each time, created one successfully: %d %d\n", stepX, stepY);
		}
		
		if(scanningTime){
			printf("[Success] Set the scanning time: %d\n", scanningTime);
		}
		else{
			scanningTime=2000;
			fclose(stdout);
			freopen("config_in.txt", "a", stdout);
			printf("%d\n", scanningTime);
			fclose(stdout);
			freopen("config_out.txt", "a", stdout);
			printf("[Error]   Didn't get the scanning time, set it successfully: %d\n", scanningTime);
		}

		if(debugMode){
			printf("[Debug]   Debug Mode\n");
		}
		else{
			debugMode=0;
			printf("[UnDebug] UnDebug Mode\n");
			ShowWindow(GetConsoleWindow(), SW_HIDE);
		}
		
		printf("[%lld] Started checking\n", getTimeStamp());
		
	fclose(stdout);
	
    while(1){
    	autoShutdown();
    	freopen("config_out.txt", "a", stdout);
    	if(ScrBlk()){
    		printf("[%lld] Solved once\n", getTimeStamp());
    		left_click(pixX, pixY);
		}
    	fclose(stdout);
		Sleep(scanningTime);
	}
	fclose(stdout);
	return 0;
}

bool checkStartUp(){
	std::ifstream file("StartUpSet.txt");
	return file.good();
}

long long int getTimeStamp(){
	std::time_t now = std::time(0);
    long long int timeStamp = now;
    return timeStamp;
}

void left_click(int x, int y){
	POINT last;
	GetCursorPos(&last);
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
    SetCursorPos(last.x, last.y);
    return;
}
void right_click(int x, int y){
	POINT last;
	GetCursorPos(&last);
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
    SetCursorPos(last.x, last.y);
    return;
}

COLORREF GetColor(int x, int y){
	COLORREF color;
	HDC screen=GetDC(NULL);
    color=GetPixel(screen,x,y);
    ReleaseDC(NULL,screen);
    return color;
}
void PrintColor(COLORREF color){
	freopen("config_out.txt","a",stdout);
	printf("[Testing] Get the color of: %d %d %d\n", GetRValue(color), GetGValue(color), GetBValue(color));
	fclose(stdout);
	return;
}

bool ScrBlk(){
	bool ifBlack=true;
	if(debugMode){
		freopen("config_out.txt", "a", stdout);
		printf("\n\n\n");
		fclose(stdout);
	}
	for(int i=startX;i<width;i+=stepX){
		for(int j=startY;j<height;j+=stepY){
			COLORREF color=GetColor(i,j);
			int r=GetRValue(color);
			int g=GetGValue(color);
			int b=GetBValue(color);
			if(debugMode){
				freopen("config_out.txt", "a", stdout);
				printf("(%3d,%3d,%3d)\t", r, g, b);
				fclose(stdout);
			}
			if(r>blackR&&g>blackG&&b>blackB){
				if(ifBlack){
					ifBlack=false;
				}
			}
		}
		if(debugMode){
			freopen("config_out.txt", "a", stdout);
			printf("\n");
			fclose(stdout);
		}
	}
	if(debugMode){
		freopen("config_out.txt", "a", stdout);
		printf("\n\n\n");
		fclose(stdout);
	}
	return ifBlack;
}

std::string getPath(bool fileName){
	char path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	int end;
	for(int i=1; i<MAX_PATH; i++){
		if(path[i]=='\0'){
			end=i-1;
			break;
		}
	}
	if(!fileName){
		for(int i=end; i>=0; i--){
			if(path[i]=='\\'){
				end=i;
				break;
			}
		}
	}
	std::string strPath="";
	for(int i=0; i<=end; i++){
		strPath+=path[i];
	}
	return strPath;
}

void autoShutdown(){
	SYSTEMTIME st;
	GetLocalTime(&st);
	freopen("autoShutdown.txt", "r", stdin);
	int hour, minute;
	while(scanf("%d %d", &hour, &minute)!=EOF){
		if(st.wHour==hour&&st.wMinute==minute){
			system("shutdown -s -t 0");
		}
	}
	fclose(stdin);
	return;
}
