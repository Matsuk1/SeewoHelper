#include <bits/stdc++.h>
#include <windows.h>

void checkStartUp();
bool ElevatePrivileges();
std::string getPath(bool filename=false);

int main(){
	checkStartUp();
	if(!ElevatePrivileges()){
		printf("Please run in root.");
		Sleep(5000);
		return 0;
	}
	std::string cmd = "cmd /k \"reg add HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /v SeewoHelper /t REG_SZ /d \"\\\""+getPath()+"SeewoHelper.exe\\\" /start /background\" /f\"";
	std::cout<<"Running: "<<cmd<<std::endl;
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".");
	Sleep(1000);
	printf(".\n");
	Sleep(1000);
	system(cmd.c_str());
	std::ofstream file("StartUpSet.txt");
	file<<"110001000010001 110011000101111 1001000000000110 1000011101110110";
	file.close();
	return 0;
}

void checkStartUp(){
	HKEY hKey;
	LSTATUS status;
	DWORD dwType = REG_SZ;
	TCHAR szBuffer[256];
	DWORD dwBufferSize = sizeof(szBuffer);
	
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_READ, &hKey);
	status = RegGetValue(hKey, NULL, TEXT("SeewoHelper"), RRF_RT_REG_SZ, &dwType, szBuffer, &dwBufferSize);
	std::wcout << "KEY: " << szBuffer << std::endl;
	if(status == ERROR_SUCCESS){
		printf("StartUp already set.\n");
		std::ofstream file("StartUpSet.txt");
		file<<"110001000010001 110011000101111 1001000000000110 1000011101110110";
		file.close();
		Sleep(5000);
		exit(0);
	}
}

bool ElevatePrivileges(){
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return false;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue)) {
		CloseHandle(hToken);
		return false;
    }

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, NULL)) {
		CloseHandle(hToken);
		return false;
	}
	
	if (GetLastError() != ERROR_SUCCESS) {
		CloseHandle(hToken);
		return false;
	}

	CloseHandle(hToken);
	return true;
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
