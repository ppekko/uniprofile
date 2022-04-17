/*

        uniprofile - pipewarp (github.com/pipewarp/uniprofile)

        Requires C++17 as a minimum (because im lazy and i dont want to add a proper sorting algo)

        Insert the line
            #define PROFILER_IMPLEMENTATION
        before including this header in *one* C++ file to create the implementation.

        Insert the line
            #define PROFILER_DEBUGTEXT
        before including this header in *one* C++ file to get debug text in the console.

        ----------------------------------------------------

        Copyright 2022 pipewarp

        Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
        to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
        and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
        WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


*/

#pragma once
#ifdef UNIPROFILER_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <fstream>

typedef struct ProfileBlock
{
    float startT;
    float endT;
    float resultT;
    char *name;
} ProfileBlock;

class uniprofile
{
public:
    std::vector<ProfileBlock> profile;
    void setTimerFetchCallBack(double (*ptr)())
    {
        getTime = ptr;
    }
    void startProfile(const char *name)
    {
        ProfileBlock prf;
        prf.startT = (*getTime)();
        prf.name = (char *)name;
        profile.push_back(prf);
#ifdef UNIPROFILER_DEBUGTEXT
        printf("%s added to profiler\n", name);
        fflush(NULL);
#endif
    }
    void endProfile(const char *name)
    {
        for (int i = 0; i < (int)profile.size(); i++)
        {
            if (!strcmp(profile[i].name, name))
            {
                profile[i].endT = (*getTime)();
                profile[i].resultT = profile[i].endT - profile[i].startT;
#ifdef UNIPROFILER_DEBUGTEXT
                printf("%s took %f sec (started at %f and ended at %f)\n", name, profile[i].resultT, profile[i].startT, profile[i].endT);
                fflush(NULL);
#endif
                return;
            }
        }
#ifdef UNIPROFILER_DEBUGTEXT
        printf("%s not found in Profilier!\n", name);
        fflush(NULL);
#endif
    }
    void dumpAllProfiles(const char *filename)
    {
#ifdef UNIPROFILER_DEBUGTEXT
        printf("Dumping Profiler to %s...", filename);
        fflush(NULL);
#endif

        // sort logged times
        std::vector<float> logtime;
        for (int i = 0; i < (int)profile.size(); i++)
        {
            logtime.push_back(profile[i].startT);
            logtime.push_back(profile[i].endT);
        }
        std::sort(logtime.begin(), logtime.end(), std::greater<float>());
        logtime.erase(unique(logtime.begin(), logtime.end()), logtime.end());

        // actual logging
        std::ofstream file;
        file.open(filename);
        for (int i = (int)logtime.size() - 1; i > -1; i--)
        {
            for (int z = 0; z < (int)profile.size(); z++)
            {
                if (profile[z].startT == logtime[i])
                {
                    file << profile[z].name << " was started at " << profile[z].startT << "sec\n";
                }
                if (profile[z].endT == logtime[i])
                {
                    file << profile[z].name << " ended at " << profile[z].endT << "sec and took " << profile[z].resultT << "sec to complete.\n";
                }
            }
        }
        file.close();
#ifdef UNIPROFILER_DEBUGTEXT
        printf("Dumped!\n");
        fflush(NULL);
#endif
    }

private:
    double (*getTime)();
};
#endif
