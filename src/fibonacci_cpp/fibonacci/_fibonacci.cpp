#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include <iostream>

#include "fib.h"

static PyObject* pyfib(PyObject* self, PyObject* args) {
    unsigned int n;

    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    auto result = fibonacci(n);
    npy_intp dims[1]; dims[0] = n;
    auto arr = PyArray_SimpleNewFromData(1, dims, NPY_INT32, result);
    PyArray_ENABLEFLAGS((PyArrayObject*) arr, NPY_ARRAY_OWNDATA);
    return arr;
}

static PyMethodDef methods[] = {
    {"fibonacci", pyfib, METH_VARARGS, "Returns the first n Fibonacci numbers, computed with maximum efficiency!"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef module = {
   PyModuleDef_HEAD_INIT,
   "_fibonacci",   /* name of module */
   "Provides a single method to compute fibonacci numbers", /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   methods
};

PyMODINIT_FUNC PyInit__fibonacci(void) {
    import_array(); // Initialise Numpy
    if (PyErr_Occurred()) {
        return NULL;
    }
    return PyModule_Create(&module);
}