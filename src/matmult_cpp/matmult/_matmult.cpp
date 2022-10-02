#define PY_SSIZE_T_CLEAN
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#include "libmatmult.h"

static PyObject* py_matmult(PyObject* self, PyObject* args) {
    PyArrayObject *m1py;
    PyArrayObject *m2py;

    double *m1, *m2;

    if (!PyArg_ParseTuple(args, "O!O!", &PyArray_Type, &m1py, &PyArray_Type, &m2py))
        return NULL;

    if(PyArray_NDIM(m1py) != 2 || PyArray_NDIM(m2py) != 2) return NULL;

    if(!PyArray_ISCONTIGUOUS(m1py)) {
        auto tmp = (PyArrayObject*)PyArray_Copy(m1py);
        Py_DECREF(m1py);
        m1py = tmp;
    }
    if(!PyArray_ISCONTIGUOUS(m2py)) {
        auto tmp = (PyArrayObject*)PyArray_Copy(m2py);
        Py_DECREF(m2py);
        m2py = tmp;
    }

    // TODO handle wrong data types

    npy_intp* dims1 = PyArray_DIMS(m1py);
    npy_intp* dims2 = PyArray_DIMS(m2py);

    if(dims1[1] != dims2[0]) return NULL;

    m1 = (double*)PyArray_DATA(m1py);
    m2 = (double*)PyArray_DATA(m2py);

    auto result = mat_mult(m1, m2, dims1[0], dims1[1], dims2[1]);

    npy_intp dims[2]; dims[0] = dims1[0]; dims[1] = dims2[1];
    auto arr = PyArray_SimpleNewFromData(2, dims, NPY_FLOAT64, result);
    PyArray_ENABLEFLAGS((PyArrayObject*) arr, NPY_ARRAY_OWNDATA);
    return arr;
}

static PyMethodDef methods[] = {
    {"matmult", py_matmult, METH_VARARGS, "Multiplies two arrays"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef module = {
   PyModuleDef_HEAD_INIT,
   "_matmult",   /* name of module */
   "Provides a single method to multiply matrices", /* module documentation, may be NULL */
   -1,       /* size of per-interpreter state of the module,
                or -1 if the module keeps state in global variables. */
   methods
};

PyMODINIT_FUNC PyInit__matmult(void) {
    import_array(); // Initialise Numpy
    if (PyErr_Occurred()) {
        return NULL;
    }
    return PyModule_Create(&module);
}