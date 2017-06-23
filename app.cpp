#include <dirent.h>
#include "sys/stat.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void listDir(const string& path, const string& newDir)
{
    DIR *dir;
    struct dirent *ent;
    struct stat s;
    system((string("mkdir -p ") + newDir).c_str());
    if((dir = opendir (path.c_str())) != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            stat(ent->d_name, &s);
            string str(ent->d_name);
            if (str.compare(".") == 0 || str.compare("..") == 0 || str.find_first_of(".") == 0) {
                continue;
            }

            if((s.st_mode & S_IFMT) == S_IFREG)
            {
                ofstream oFile;
                ifstream iFile((path+str).c_str());
                oFile.open((newDir+str).c_str(), ios::out);
                
                string line;
                while(getline(iFile, line)) {
                    size_t idx = line.rfind('\r');
                    if (idx != string::npos) {
                        line.erase(idx, string::npos);
                    }
                    oFile<<line<<endl;
                }

                cout<<"File - "<< str.c_str() << endl;
            }
            else
            {
                string nextDir = path + string(ent -> d_name) + "/";
                string newNextDir = newDir + string(ent -> d_name) + "/";
                cout <<"Dir - "<<  nextDir << endl;

                listDir(nextDir, newNextDir);
            }
        }
    }

    closedir (dir);
}

int main(int param, char **args)
{
    string path = string(args[1]);
    cout<<"\n Path = "<<path.c_str()<<"\n";

    listDir(path, path+"../new-dir/");

    return 0;
}
