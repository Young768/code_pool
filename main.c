#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char **argv){

    Py_Initialize();

    if(!Py_IsInitialized()){
            printf("Python init failed!\n");
            return -1;
        }

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    PyObject *pName = NULL;
    PyObject *pModule = NULL;
    PyObject *pDict = NULL;
    PyObject *pFunc = NULL;
    PyObject *pArgs = NULL;
    PyObject *result = NULL;
    int tmp;
    char policy;

    //FILE *fp;
    //fp=fopen("test", "wb");
    //const char *ptr;
 
    pName = PyUnicode_FromString("py_add");
    pModule = PyImport_Import(pName);
    if(!pModule){
            printf("Load py_add.py failed!\n");
            getchar();
            return -1;
        }
    pDict = PyModule_GetDict(pModule);
    if(!pDict){
            printf("Can't find dict in py_add!\n");
            return -1;
        }
    pFunc = PyDict_GetItemString(pDict,"add");
    if(!pFunc || !PyCallable_Check(pFunc)){
            printf("Can't find function!\n");
            getchar();
            return -1;
        }

    pArgs = PyTuple_New(1);

    PyTuple_SetItem(pArgs,0,Py_BuildValue("i",3));
    result = PyEval_CallObject(pFunc, pArgs);

    PyArg_Parse(result, "i", &tmp);
    //printf("a+b=%d\n", c);
    policy = tmp +'0';
    int filedesc = open("test", O_WRONLY | O_CREAT,0666);
    write(filedesc, &policy , 1);
    close(filedesc);
    if(pName){
        Py_DECREF(pName);
        }
    if(pArgs){
        Py_DECREF(pArgs);
        }
    if(pModule){
        Py_DECREF(pModule);
        }
    Py_Finalize();
    return 0;
}
