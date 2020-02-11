#include<windows.h>
#include<iostream>
#include<cctype>

using namespace std;
HANDLE clip;

void HideConsole()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth,0);
}

void pasteCB(string x) //paste to clipboard
{
        char output[x.length()];
        strcpy(output,x.c_str());
        const size_t len = strlen(output) + 1;
        HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), output, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
}


boolean checkUP(string x) //check uppercase for string
{
    boolean yes=1;
    for(int i=0;i<x.length();i++)
    {
        if(isupper(x[i]) || isspace(x[i])|| isdigit(x[i]))
        {
            yes=1;
        }
        else
        {
            yes=0;
            break;
        }
    }
    return yes;
}

boolean checkLO(string x) //check lowercase for string
{
    boolean yes=1;
    for(int i=0;i<x.length();i++)
    {
        if(islower(x[i]) || isspace(x[i]) || isdigit(x[i]))
        {
            yes=1;
        }
        else
        {
            yes=0;
            break;
        }
    }
    return yes;
}

string makeLO(string x) //make string lowercase
{
    
    for (int i = 0; i < x.length(); i++)
    {
        if(isalpha(x[i]))
        {
            x[i]=tolower(x[i]);
        }
        else
        {
            x[i]=x[i];
        }

        
    }
    return x;
    
}

string makeUP(string x) //make string uppercase 
{
    
    for (int i = 0; i < x.length(); i++)
    {
        if(isalpha(x[i]))
        {
            x[i]=toupper(x[i]);
        }
        else
        {
            x[i]=x[i];
        }
        
    }
    return x;
    
}
void paste() //keybord event to simulate paste 
{  
        keybd_event(0x11, 0, 0, 0); //Press down the 'Ctrl' Key
        keybd_event(0x56, 0, 0, 0); //Press down the 'V' Key
        keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0); //Release the 'V'Key
        keybd_event(0x11, 0, KEYEVENTF_KEYUP, 0); //Release the 'Ctrl' Key
}
int main()
{
    HideConsole();
    while(true)
    {
        if(GetAsyncKeyState(VK_RCONTROL) & 1)
        {
            if (OpenClipboard(NULL)) {              //open clipboard & check availability
                clip = GetClipboardData(CF_TEXT);   //get clipboard data
                CloseClipboard();                   //close clipboard
            }
            string fromCB=(char*)clip;              //cast to character * from void *null
            if(checkUP(fromCB))
            {
                    string toCB=makeLO(fromCB);
                    pasteCB(toCB);
            }
            else if(checkLO(fromCB))
            {
                string toCB=makeUP(fromCB);
                pasteCB(toCB);
            }
                paste();
            }
    }
}