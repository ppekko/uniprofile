#include <GLFW/glfw3.h>
#include <unistd.h>

#define UNIPROFILER_IMPLEMENTATION //implementation
#define UNIPROFILER_DEBUGTEXT      //get debug text
#include "../include/uniprofile.h"

int main()
{
    glfwInit();
    uniprofile profile;

    profile.setTimerFetchCallBack(&glfwGetTime); // set timer to GLFW timer

    profile.startProfile("Function 1");
    usleep(2*1000000); // sleep for 2 seconds
    profile.endProfile("Function 1");

    profile.startProfile("Function 2");
    usleep(5*1000000); // sleep for 5 seconds]
    profile.endProfile("Function 2");

    profile.dumpAllProfiles("log.txt");

    glfwTerminate();
}
