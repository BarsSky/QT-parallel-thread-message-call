#include "mainwindow.h"
#include "SomeParallelprocess.h"

SomeParallelprocess::SomeParallelprocess()
{
    StartThread();
}

void SomeParallelprocess::configure()
{
    text = "Paralell process stop and you see message from gui\n"
           "press Ok and process end";
}

void SomeParallelprocess::start()
{
    MessageBox(text);
}
